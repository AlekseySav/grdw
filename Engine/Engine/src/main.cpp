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

	//it's a buffer
	float poses[6] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f	};

	unsigned int buf;
	glGenBuffers(1, &buf);
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), poses, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		//render starts here
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}