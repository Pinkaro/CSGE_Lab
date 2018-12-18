#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <map>

#include "Shader.h"
#include "texture2d.h"

class ResourceManager
{
public:
	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Texture2d> Textures;

	static Shader LoadShader(const GLchar *vertexShaderFile, const GLchar *fragmentShaderFile, std::string name);
	static Shader GetShader(std::string name);

	static Texture2d LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
	static Texture2d GetTexture(std::string name);
	
	static void Init();
	static void Clear();
private:
	static char* m_shaderPath;
	static char* m_texturePath;

	ResourceManager() {};

	static std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);
	static Shader loadShaderFromFile(const GLchar *vertexShaderFile, const GLchar *fragmentShaderFile);
	static Texture2d loadTextureFromFile(const GLchar *file, GLboolean alpha);
	static const char* GetShaderPath(const GLchar* filename);
	static const char* GetTexturePath(const GLchar* filename);
};