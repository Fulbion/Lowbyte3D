#include "Application/Cube.hpp"

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::onCreate()
{
	this->m_entity = this->getEntitySystem()->createEntity<Entity>();
}

void Cube::onUpdate(float i_deltaTime)
{
	this->m_elapsedTime += i_deltaTime;

	if (this->m_entity && this->m_elapsedTime >= 3)
	{
		this->m_entity->release();
		this->m_entity = nullptr;
	}
}




