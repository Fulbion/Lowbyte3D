#include <Windows.h>
#include <chrono>

#include "OpenGL/Game/Game.hpp"
#include "OpenGL/Graphics/VertexArrayObject.hpp"
#include "OpenGL/Graphics/ShaderProgram.hpp"
#include "OpenGL/Graphics/UniformBuffer.hpp"
#include "OpenGL/Graphics/Graphics.hpp"
#include "OpenGL/Window/Window.hpp"

#define MATRIX_ROTATION_X_AXIS glm::vec3(1, 0, 0)
#define MATRIX_ROTATION_Y_AXIS glm::vec3(0, 1, 0)
#define MATRIX_ROTATION_Z_AXIS glm::vec3(0, 0, 1)

struct UniformData
{
	glm::mat4x4 world;
	glm::mat4x4 projection;
};

glm::mat4x4 orthoLH(float i_width, float i_height, float i_nearPlane, float i_farPlane)
{
	glm::mat4x4 output = glm::identity<glm::mat4x4>();
	output[0][0] = 2.0f / i_width;
	output[1][1] = 2.0f / i_height;
	output[2][2] = 1.0f / (i_farPlane - i_nearPlane);
	output[3][2] = -(i_nearPlane / (i_farPlane - i_nearPlane));
	return output;
}

Game::Game()
{
	this->m_graphics = std::make_unique<Graphics>();
	this->m_window = std::make_unique<Window>();

	this->m_window->makeCurrentContext();

	this->m_graphics->setViewport(this->m_window->getSize());
}

Game::~Game()
{
}

void Game::onCreate()
{
	glm::vec3 cubeVertices[] =
	{
		{ -0.5f, -0.5f, -0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },

		{  0.5f, -0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f },
		{ -0.5f, -0.5f,  0.5f },
	};

	UINT cubeIndices[] =
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		1, 6, 5,
		5, 2, 1,

		7, 0, 3,
		3, 4, 7,

		3, 2, 5,
		5, 4, 3,

		7, 6, 1,
		1, 0, 7
	};

	// const GLfloat polygonVertices[] =
	// {
	// 	-0.5f, -0.5f, 0.0f,
	// 	1.0f, 0.0f, 0.0f,
	// 
	// 	-0.5f, 0.5f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 
	// 	0.5f, -0.5f, 0.0f,
	// 	0.0f, 0.0f, 1.0f,
	// 
	// 	0.5f, 0.5f, 0.0f,
	// 	1.0f, 1.0f, 0.0f,
	// };

	VertexAttribute attribsList[] =
	{
		sizeof(glm::vec3) / sizeof(GLfloat), // Position
		// 3  // Color
	};

	this->m_vao = this->m_graphics->createVAO({ (void*)cubeVertices, sizeof(glm::vec3), sizeof(cubeVertices) / sizeof(glm::vec3), attribsList, sizeof(attribsList) / sizeof(VertexAttribute) }, { (void*)cubeIndices, sizeof(cubeIndices) });
	this->m_uniform = this->m_graphics->createUniformBuffer({ sizeof(UniformData) });
	this->m_shader = this->m_graphics->createShaderProgram({ L"../../../resources/shaders/vertex.vert", L"../../../resources/shaders/fragment.frag" });
	this->m_shader->setUniformBufferSlot("UniformData", 0);
}

void Game::onUpdate()
{
	auto currentTime = std::chrono::system_clock::now();
	auto elapsedTime = std::chrono::duration<double>();

	if (this->m_previousTime.time_since_epoch().count())
		elapsedTime = currentTime - this->m_previousTime;
	this->m_previousTime = currentTime;

	float deltaTime = static_cast<float>(elapsedTime.count());

	this->m_scale += 3.14159f * deltaTime;
	float currentScale = abs(sin(this->m_scale));

	glm::mat4x4 world = glm::identity<glm::mat4x4>();
	glm::mat4x4 temp;
	glm::mat4x4 projection = glm::identity<glm::mat4x4>();

	temp = glm::identity<glm::mat4x4>();
	temp = glm::rotate(temp, (float)(this->m_scale * 0.5), MATRIX_ROTATION_X_AXIS);

	world *= temp;

	temp = glm::identity<glm::mat4x4>();
	temp = glm::rotate(temp, (float)(this->m_scale * 0.5), MATRIX_ROTATION_Y_AXIS);

	world *= temp;

	temp = glm::identity<glm::mat4x4>();
	temp = glm::rotate(temp, (float)(this->m_scale * 0.5), MATRIX_ROTATION_Z_AXIS);

	world *= temp;

	Rect<UINT> displaySize = this->m_window->getSize();
	// The glm::orthoLH function was setting the cube at the top-left of the window.
	// I created a new one so it's set to the center.
	projection = orthoLH(displaySize.width * 0.004f, displaySize.height * 0.004f, 0.01f, 100.f);

	UniformData data = { world, projection };
	this->m_uniform->setData(&data);

	this->m_graphics->clear(0.0, 0.0f, 0.0f, 1.0f);

	this->m_graphics->setVAO(this->m_vao);
	this->m_graphics->setUniformBuffer(this->m_uniform, 0);
	this->m_graphics->setShaderProgram(this->m_shader);
	this->m_graphics->drawIndexedTriangles(TriangleType::TriangleStrip, 36);

	this->m_window->present(false);
}

void Game::onQuit()
{
}

void Game::run()
{
	this->onCreate();

	while (this->m_isRunning)
	{
		MSG msg;

		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				#ifdef NDEBUG
				if (MessageBox(this->m_window->getHWND(), L"Do you want to quit the application?", L"Lowbyte 3D - OpenGL", MB_ICONQUESTION | MB_YESNO) == IDYES)
				#endif // NDEBUG
				this->m_isRunning = false;
			}

			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		this->onUpdate();
	}

	this->onQuit();
}

void Game::quit()
{
	this->m_isRunning = false;
}
