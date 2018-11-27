
#include "Lab.h"

int main()
{
	Lab* lab = new Lab(800, 600);
	lab->Init();
	lab->Render();

	glfwTerminate();

	return 0;
}
