#pragma once

#include "OpenGL/Common.hpp"

class Component
{
public:
	Component();
	virtual ~Component();

private:
	size_t m_id;
	Entity* m_entity = nullptr;

	friend class Entity;
};
