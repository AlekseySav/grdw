//OPENGL including
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//get ver of shaders on that computer on what will work our game and use file for that shader version (shader vers: 410, 330, 250)
struct shaderProgSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static shaderProgSource ShParser(const std::string& shaderfile)
{
	std::ifstream stream(shaderfile);

	enum class shaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	shaderType type = shaderType::NONE;
	while(getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("#version 410") != std::string::npos) {
				int version = 410;
				//here will put version of shaders to a literal and do an if statment after opening shader file down (same int two versions)
				//and here we need to parse 410 shader
			}
			else if (line.find("#version 330") != std::string::npos) {
				int version = 330;

				if (line.find("vertex") != std::string::npos)
					type = shaderType::VERTEX;
				else if (line.find("fragments") != std::string::npos)
					type = shaderType::FRAGMENT;

			}
			else {
				std::string version = "VERSION NOT FOUND";
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

//shader_compiler
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char* message = (char*)alloca(len * sizeof(char));
		glGetShaderInfoLog(id, len, &len, message);
		std::cout << "Error! Compilation failed: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}
//shader_creating
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main(void)
{
	GLFWwindow *window;
	if (!glfwInit())
		return -1;

	//this line of code creating a full screen window (fuction glfwGetPrimaryMonitor make a full screen window, but if u'll put NULL there you will have 1920x1080 window)
	window = glfwCreateWindow(640 /*1920*/, 480/*1080*/, "Element Masters", NULL /*for a full-screen here need to be glfwGetPrimaryMonitor()*/, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	//it's a vertex buffer
	float poses[6] = { -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f };

	unsigned int buf;
	glGenBuffers(1, &buf);
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), poses, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	shaderProgSource shaderSource = ShParser("res/shaders/default.shader");
	unsigned int shader = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource );
	glUseProgram(shader);

	//rendering here
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}