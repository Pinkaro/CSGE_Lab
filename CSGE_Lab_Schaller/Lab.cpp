#include "Lab.h"

// Initialize static variables
GLuint Lab::Height = 0.0f, Lab::Width = 0.0f;
Camera* Lab::Cam = new Camera(glm::vec3(0.0f, 0.0f, 10.0f));
bool Lab::FirstMouseMovement = true;
float Lab::DeltaTime = 0.0f, Lab::LastFrameTime = 0.0f, Lab::LastMouseX = 0.0f, Lab::LastMouseY = 0.0f;
GLFWwindow* Lab::window = NULL;

void Lab::Clear() 
{
	delete Cam;
}

void Lab::Init(GLuint width, GLuint height)
{
	Lab::Width = width;
	Lab::Height = height;
	Lab::LastMouseX = Width / 2.0f;
	Lab::LastMouseY = Height / 2.0f;

	DrawWindow();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // to hide cursor when window is in fox

	ResourceManager::Init();
	ResourceManager::LoadShader("vertexShader.vs", "fragmentShader.fs", "MyShader");
	ResourceManager::LoadTexture("PogChamp.png", true, "PogChamp");
	ResourceManager::LoadTexture("awesomeface.png", true, "AwesomeFace");
}

void Lab::Update()
{

}


void Lab::ProcessInput()
{
	if (glfwGetKey(Lab::window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(Lab::window, true);

	if (glfwGetKey(Lab::window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(Lab::window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	

	if (glfwGetKey(Lab::window, GLFW_KEY_W) == GLFW_PRESS)
		Lab::Cam->ProcessKeyboard(FORWARD, Lab::DeltaTime);

	if (glfwGetKey(Lab::window, GLFW_KEY_S) == GLFW_PRESS)
		Lab::Cam->ProcessKeyboard(BACKWARD, Lab::DeltaTime);

	if (glfwGetKey(Lab::window, GLFW_KEY_A) == GLFW_PRESS)
		Lab::Cam->ProcessKeyboard(LEFT, Lab::DeltaTime);

	if (glfwGetKey(Lab::window, GLFW_KEY_D) == GLFW_PRESS)
		Lab::Cam->ProcessKeyboard(RIGHT, Lab::DeltaTime);
}

void Lab::Render()
{
	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader = ResourceManager::GetShader("MyShader");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = 
	{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// load and create a texture 
	// -------------------------
	Texture2d texture1 = ResourceManager::GetTexture("PogChamp");

	Texture2d texture2 = ResourceManager::GetTexture("AwesomeFace");

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader.Use();
	ourShader.SetInteger("texture1", 0, true);
	ourShader.SetInteger("texture2", 1, true);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		Lab::ProcessInput();

		float currentFrame = glfwGetTime();
		Lab::DeltaTime = currentFrame - Lab::LastFrameTime;
		Lab::LastFrameTime = currentFrame;

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		texture1.Bind();

		glActiveTexture(GL_TEXTURE1);
		texture2.Bind();

		// activate shader
		ourShader.Use();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(Lab::Cam->Zoom), (float)Lab::Width / (float)Lab::Height, 0.1f, 100.0f);
		ourShader.SetMatrix4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.

		glm::mat4 view;
		view = Lab::Cam->GetViewMatrix();
		ourShader.SetMatrix4("view", view);
		// pass transformation matrices to the shader
		
		

		// render box
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;

			if (i % 3 == 0)
				angle = glfwGetTime() * 25.0f;
			
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
						
			ourShader.SetMatrix4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	ResourceManager::Clear();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (Lab::FirstMouseMovement)
	{
		Lab::LastMouseX = xpos;
		Lab::LastMouseY = ypos;
		Lab::FirstMouseMovement = false;
	}

	float xoffset = xpos - Lab::LastMouseX;
	float yoffset = Lab::LastMouseY - ypos; // reversed since y-coordinates go from bottom to top

	Lab::LastMouseX = xpos;
	Lab::LastMouseY = ypos;

	Lab::Cam->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Lab::Cam->ProcessMouseScroll(yoffset);
}

int Lab::DrawWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Lab::window = glfwCreateWindow(Lab::Width, Lab::Height, "CSGE_Lab_Schaller", NULL, NULL);
	if (Lab::window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(Lab::window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//register size callback:
	glfwSetFramebufferSizeCallback(Lab::window, framebuffer_size_callback);

	//register mouse movement event:
	glfwSetCursorPosCallback(window, mouse_callback);

	//register scroll event:
	glfwSetScrollCallback(window, scroll_callback);

	return 0;
}

