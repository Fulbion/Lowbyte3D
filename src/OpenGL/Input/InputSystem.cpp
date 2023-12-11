#include "OpenGL/Input/InputSystem.hpp"

#include <Windows.h>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	if (GetKeyboardState(this->m_keysState))
	{
		for (UINT i = 0; i < 256; i++)
		{
			if (this->m_keysState[i] & 0x80)
			{
				auto it = this->m_listeners.begin();

				while (it != this->m_listeners.end())
				{
					it->second->onKeyPressed(i);
					++it;
				}
			}

			else
			{
				if (this->m_keysState[i] != this->m_oldKeysState[i])
				{
					auto it = this->m_listeners.begin();

					while (it != this->m_listeners.end())
					{
						it->second->onKeyReleased(i);
						++it;
					}
				}
			}
		}

		memcpy(this->m_oldKeysState, this->m_keysState, sizeof(BYTE) * 256);
	}
}

void InputSystem::addListener(InputListener* i_listener)
{
	this->m_listeners.insert(std::make_pair<InputListener*, InputListener*>(std::forward<InputListener*>(i_listener), std::forward<InputListener*>(i_listener)));
}

void InputSystem::removeListener(InputListener* i_listener)
{
	auto it = this->m_listeners.find(i_listener);

	if (it != this->m_listeners.end())
	{
		this->m_listeners.erase(it);
	}
}
