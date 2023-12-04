#pragma once

#ifdef DEBUG
#include <iostream>
#endif // DEBUG
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <array>
#include <vector>
#include <unordered_map>
#include <Windows.h>

class VertexArrayObject;
class ShaderProgram;

struct VertexAttribute
{
	UINT numElements = 0;
};

struct VertexBufferDesc
{
	void* verticesList = nullptr;
	size_t vertexSize = 0;
	size_t listSize = 0;

	VertexAttribute* attributesList = nullptr;
	size_t attributesListSize = 0;
};

struct ShaderProgramDesc
{
	const wchar_t* vertexShaderPath;
	const wchar_t* fragmentShaderPath;
};

enum class ShaderType
{
	VertexShader,
	FragmentShader
};

typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;