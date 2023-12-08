#pragma once

class EntitySystem;
class Entity
{
public:
	Entity();
	virtual ~Entity();

	void release();

	inline EntitySystem* getEntitySystem() const
	{
		return this->m_entitySystem;
	}

protected:
	virtual void onCreate() {}
	virtual void onUpdate(float i_deltaTime) {}

private:
	size_t m_id;
	EntitySystem* m_entitySystem = nullptr;

	friend class EntitySystem;
};