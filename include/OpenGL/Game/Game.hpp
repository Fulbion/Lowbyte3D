#pragma once

#include <memory>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "OpenGL/Common.hpp"

class EntitySystem;
class Graphics;
class Window;
class Game
{
public:
	Game();
	~Game();

	void run();
	void quit();

	inline EntitySystem* getEntitySystem() const
	{
		return this->m_entitySystem.get();
	}

protected:
	virtual void onCreate();
	virtual void onUpdate(float i_deltaTime) {}
	virtual void onQuit();

private:
	void onUpdateInternal();

	bool m_isRunning = true;

	std::unique_ptr<Graphics> m_graphics;
	std::unique_ptr<Window> m_window;
	std::unique_ptr<EntitySystem> m_entitySystem;

	VertexArrayObjectPtr m_vao;
	ShaderProgramPtr m_shader;
	UniformBufferPtr m_uniform;

	std::chrono::system_clock::time_point m_previousTime;

	float m_scale = 0.0f;
};
