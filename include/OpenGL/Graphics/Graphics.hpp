#pragma once

#include <glad/glad_wgl.h>
#include <glad/glad.h>

#include "OpenGL/Common.hpp"
#include "OpenGL/Math/Rect.hpp"

class Graphics
{
public:
	Graphics();
	~Graphics();

	VertexArrayObjectPtr createVAO(const VertexBufferDesc& i_vbDesc);
	ShaderProgramPtr createShaderProgram(const ShaderProgramDesc& i_desc);

	void clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);;
	void setViewport(const Rect<UINT>& i_size);
	void setVAO(const VertexArrayObjectPtr& i_vao);
	void setShaderProgram(const ShaderProgramPtr& i_shaderProgram);
	void drawTriangles(GLsizei i_vertexCount, GLuint i_offset);

private:

};
