#pragma once

#include <memory>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "OpenGL/Common.hpp"

class Graphics;
class Window;
class Game
{
public:
	Game();
	~Game();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();

	void run();
	void quit();

private:
	bool m_isRunning = true;

	std::unique_ptr<Graphics> m_graphics;
	std::unique_ptr<Window> m_window;

	VertexArrayObjectPtr m_vao;
	ShaderProgramPtr m_shader;
	UniformBufferPtr m_uniform;

	std::chrono::system_clock::time_point m_previousTime;

	float m_scale = 0.0f;
};
