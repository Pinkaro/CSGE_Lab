#include "resource_manager.h"
#include "stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2d> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;
char* ResourceManager::m_shaderPath;
char* ResourceManager::m_texturePath;

Texture2d ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture2d ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

Texture2d ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	// Create Texture object
	Texture2d texture;

	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}

	// Load image
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char *data = stbi_load(GetTexturePath(file), &width, &height, &nrChannels, 0);

	if (data) 
	{
		// Now generate texture
		texture.Generate(width, height, data);
	}
	else
	{
		std::cout << "Failed to load texture " << file << std::endl;
	}

	// And finally free image data
	stbi_image_free(data);
	return texture;	
}

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vertexShaderFile, const GLchar *fragmentShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(GetShaderPath(vertexShaderFile));
		std::ifstream fragmentShaderFile(GetShaderPath(fragmentShaderFile));
		std::stringstream vShaderStream, fShaderStream;

		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();

	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode);
	return shader;
}

std::string ResourceManager::ReplaceAll(std::string str, const std::string& from, const std::string& to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

void ResourceManager::Init()
{
	char result[MAX_PATH];
	std::string sourcePath(result, GetModuleFileName(NULL, result, MAX_PATH));
	std::string shaderPath = ResourceManager::ReplaceAll(sourcePath, "CSGE_Lab_Schaller.exe", "") + "shaders\\";
	std::string texturePath = ResourceManager::ReplaceAll(sourcePath, "CSGE_Lab_Schaller.exe", "") + "textures\\";

	const size_t length_shader = strlen(shaderPath.c_str());
	const size_t length_texture = strlen(texturePath.c_str());

	ResourceManager::m_shaderPath = new char[length_shader + 1u];
#pragma warning(suppress : 4996)
	std::strcpy(ResourceManager::m_shaderPath, shaderPath.c_str());

	ResourceManager::m_texturePath = new char[length_texture + 1u];
#pragma warning(suppress : 4996)
	std::strcpy(ResourceManager::m_texturePath, texturePath.c_str());
}

const char* ResourceManager::GetShaderPath(const GLchar* filename)
{
	const size_t pathLength = std::strlen(ResourceManager::m_shaderPath);
	const size_t fileLength = std::strlen(filename);
	const size_t neededBytes = pathLength + fileLength + 1u;

	char* newString = new char[neededBytes];
	memcpy(newString, ResourceManager::m_shaderPath, pathLength);

	// copies null terminator as well
	memcpy(newString + pathLength, filename, fileLength + 1u);

	return newString;
}

const char* ResourceManager::GetTexturePath(const GLchar* filename)
{
	const size_t pathLength = std::strlen(ResourceManager::m_texturePath);
	const size_t fileLength = std::strlen(filename);
	const size_t neededBytes = pathLength + fileLength + 1u;

	char* newString = new char[neededBytes];
	memcpy(newString, ResourceManager::m_texturePath, pathLength);

	// copies null terminator as well
	memcpy(newString + pathLength, filename, fileLength + 1u);

	return newString;
}

void ResourceManager::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	// (Properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);

	delete m_shaderPath;
	delete m_texturePath;
}