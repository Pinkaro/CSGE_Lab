#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Lab
{
public:
	GLboolean              Keys[1024];
	GLuint                 Width, Height;

	// Constructor/Destructor
	Lab(GLuint width, GLuint height);
	~Lab();

	// Initialize game state (load all shaders/textures/levels)
	void Init();

	// GameLoop
	void ProcessInput();
	void Update();
	void Render();

private:
	GLFWwindow* window;

	int DrawWindow();
	
};
