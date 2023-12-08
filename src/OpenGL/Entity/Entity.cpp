#include "OpenGL/Entity/Entity.hpp"
#include "OpenGL/Entity/EntitySystem.hpp"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::release()
{
	this->m_entitySystem->removeEntity(this);
}
