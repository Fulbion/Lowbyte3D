#pragma once

#include <unordered_map>
#include <memory>

class Entity;
class EntitySystem
{
public:
	EntitySystem();
	~EntitySystem();

	template<typename T>
	T* createEntity()
	{
		static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity class");
		size_t id = typeid(T).hash_code();
		auto e = new T();

		if (this->createEntityInternal(e, id))
			return e;
		return nullptr;
	}

private:
	bool createEntityInternal(Entity* i_entity, size_t i_id);

	std::unordered_map<size_t, std::unordered_map<Entity*, std::unique_ptr<Entity>>> m_entities;
};