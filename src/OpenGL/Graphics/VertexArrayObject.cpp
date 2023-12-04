#include <glad/glad.h>

#include "OpenGL/Graphics/VertexArrayObject.hpp"

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& i_vbDesc)
{
	glGenVertexArrays(1, &this->m_vaoID);
	glBindVertexArray(this->m_vaoID);
	
	glGenBuffers(1, &this->m_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_vboID);
	glBufferData(GL_ARRAY_BUFFER, i_vbDesc.vertexSize * i_vbDesc.listSize, i_vbDesc.verticesList, GL_STATIC_DRAW);

	for (UINT i = 0; i < i_vbDesc.attributesListSize; i++)
	{
		glVertexAttribPointer(i, i_vbDesc.attributesList[i].numElements, GL_FLOAT, GL_FALSE, i_vbDesc.vertexSize, (void*)((i == 0) ? 0 : i_vbDesc.attributesList[i - 1].numElements * sizeof(GLfloat)));
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);

	this->m_vbDesc = i_vbDesc;
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &this->m_vboID);
	glDeleteVertexArrays(1, &this->m_vaoID);
}