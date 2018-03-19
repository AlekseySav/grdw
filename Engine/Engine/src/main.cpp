//OPENGL including
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>
int main(void)
{
	GLFWwindow *window;
	if (!glfwInit())
		return -1;

	//this line of code creating a full screen window (fuction glfwGetPrimaryMonitor make a full screen window, but if u'll put NULL there you will have 1920x1080 window)
	window = glfwCreateWindow(1920, 1080, "Element Masters", glfwGetPrimaryMonitor(), NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;
	
	std::cout << glGetString(GL_VERSION) << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}