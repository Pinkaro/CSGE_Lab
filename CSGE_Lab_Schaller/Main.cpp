#include "Lab.h"

int main()
{
	Lab::Init(800, 600);
	Lab::Render();
	Lab::Clear();
	glfwTerminate();

	return 0;
}
