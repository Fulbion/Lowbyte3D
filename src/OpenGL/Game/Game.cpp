#include <Windows.h>

#include "OpenGL/Game/Game.hpp"
#include "OpenGL/Graphics/VertexArrayObject.hpp"
#include "OpenGL/Graphics/Graphics.hpp"
#include "OpenGL/Window/Window.hpp"

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
	const GLfloat triangleVertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.5f, -0.5f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 0.5f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	VertexAttribute attribsList[] =
	{
		3, // Position
		3  // Color
	};

	this->m_vao = this->m_graphics->createVAO({ (void*)triangleVertices, sizeof(GLfloat) * (3 + 3), 3, attribsList, 2 });
	this->m_shader = this->m_graphics->createShaderProgram({ L"../../../resources/shaders/vertex.vert", L"../../../resources/shaders/fragment.frag" });
}

void Game::onUpdate()
{
	this->m_graphics->clear(0.0, 0.0f, 0.0f, 1.0f);

	this->m_graphics->setVAO(this->m_vao);
	this->m_graphics->setShaderProgram(this->m_shader);
	this->m_graphics->drawTriangles(this->m_vao->getVertexBufferSize(), 0);

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
