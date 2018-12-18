#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "resource_manager.h"
#include "stb_image.h"
#include "Camera.h"

// ######### TEMP INCLUDES ##########
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Lab
{
public:
	//static GLboolean	Keys[1024];
	static GLuint		Width, Height;
	static Camera*		Cam;
	static bool			FirstMouseMovement;
	static float		DeltaTime, LastFrameTime;
	static float		LastMouseX, LastMouseY;

	// Destructor
	static void Clear();

	// Initialize game state (load all shaders/textures/levels)
	static void Init(GLuint width, GLuint height);

	// GameLoop
	static void ProcessInput();
	static void Update();
	static void Render();

private:
	static GLFWwindow* window;

	Lab();
	static int DrawWindow();
};
