#include "OpenGL/Entity/EntitySystem.hpp"
#include "OpenGL/Entity/Entity.hpp"

EntitySystem::EntitySystem()
{
}

EntitySystem::~EntitySystem()
{
}

bool EntitySystem::createEntityInternal(Entity* i_entity, size_t i_id)
{
	std::unique_ptr<Entity> ptr = std::unique_ptr<Entity>(i_entity);
	m_entities[i_id].emplace(i_entity, std::move(ptr));

	i_entity->onCreate();

	return true;
}
