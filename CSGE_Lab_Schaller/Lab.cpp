#include "Lab.h"
#include "resource_manager.h"


Lab::Lab(GLuint height, GLuint width)
	: Keys(), Height(height), Width(width)
{

}

Lab::~Lab()
{

}

void Lab::Init()
{
	DrawWindow();	
	ResourceManager::Init();
	ResourceManager::LoadShader("vertexShader.vs", "fragmentShader.fs", "MyShader");
}

void Lab::Update()
{

}


void Lab::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Lab::Render()
{

	Shader shaderProgramm = ResourceManager::GetShader("MyShader");

	float vertices[] =
	{
		0.5f,  0.3f, 0.0f,  // top of right triangle
		0.9f, -0.5f, 0.0f,  // bottom left of right triangle
		0.1f, -0.5f, 0.0f,  // bottom right of right triangle

	};

	float verticesGreen[] =
	{
		-0.5f,  0.3f, 0.0f,   // top of left triangle 
		-0.9f,  -0.5f, 0.0f,   // top of left triangle 
		-0.1f,  -0.5f, 0.0f   // top of left triangle 
	};

	unsigned int indices[] =
	{
		0, 1, 2,   // first triangle
		//3, 4, 5    // second triangle
	};

	unsigned int indicesGreen[]
	{
		0,1,2
	};

	unsigned int vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	unsigned int elementBufferObject;
	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	unsigned int vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesGreen), verticesGreen, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		Lab::ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(shaderProgram);

		glBindVertexArray(vertexArrayObject);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		shaderProgramm.Use();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteBuffers(1, &elementBufferObject);

	ResourceManager::Clear();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int Lab::DrawWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(Lab::Height, Lab::Width, "CSGE_Lab_Schaller", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//register size callback:
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return 0;
}

