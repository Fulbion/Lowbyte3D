#include <stdexcept>

#include "OpenGL/Graphics/Graphics.hpp"
#include "OpenGL/Graphics/VertexArrayObject.hpp"
#include "OpenGL/Graphics/ShaderProgram.hpp"

Graphics::Graphics()
{
	const wchar_t* CLASS_NAME = L"OpenGL Dummy Window";
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = CLASS_NAME;
	wc.style = CS_CLASSDC;

	ATOM classID = RegisterClassEx(&wc);

	HWND dummyWindow = CreateWindowEx(
		NULL,                           // Optional window styles
		MAKEINTATOM(classID),           // Window class
		L"OpenGL Dummy Window",         // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		NULL,       // Instance handle
		NULL        // Additional application data
	);

	HDC dummyDC = GetDC(dummyWindow);

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;

	int pixelFormat = ChoosePixelFormat(dummyDC, &pfd);
	SetPixelFormat(dummyDC, pixelFormat, &pfd);

	HGLRC dummyGLRC = wglCreateContext(dummyDC);
	wglMakeCurrent(dummyDC, dummyGLRC);

	if (!gladLoadWGL(dummyDC))
		throw std::runtime_error("Graphics | Error: gladLoadWGL failed");

	if (!gladLoadGL())
		throw std::runtime_error("Graphics | Error: gladLoadGL failed");

	wglMakeCurrent(dummyDC, nullptr);
	wglDeleteContext(dummyGLRC);
	ReleaseDC(dummyWindow, dummyDC);
	DestroyWindow(dummyWindow);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}

Graphics::~Graphics()
{
}

VertexArrayObjectPtr Graphics::createVAO(const VertexBufferDesc& i_vbDesc)
{
	return std::make_shared<VertexArrayObject>(i_vbDesc);
}

ShaderProgramPtr Graphics::createShaderProgram(const ShaderProgramDesc& i_desc)
{
	return std::make_shared<ShaderProgram>(i_desc);
}

void Graphics::clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::setViewport(const Rect<UINT>& i_size)
{
	glViewport(i_size.left, i_size.top, i_size.width, i_size.height);
}

void Graphics::setVAO(const VertexArrayObjectPtr& i_vao)
{
	glBindVertexArray(i_vao->getID());
}

void Graphics::setShaderProgram(const ShaderProgramPtr& i_shaderProgram)
{
	glUseProgram(i_shaderProgram->getID());
}

void Graphics::drawTriangles(GLsizei i_vertexCount, GLuint i_offset)
{
	glDrawArrays(GL_TRIANGLES, i_offset, i_vertexCount);
}
