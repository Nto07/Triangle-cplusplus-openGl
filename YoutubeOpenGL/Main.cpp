#include <iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";


int main()
{
	//Comment: inisialize glfw so we can use its functions
	glfwInit();

	
	//Comment: Give the version we use for OpenGL, give the minor version also 3, 
	//which profil we want to use (core : contain all the modern functions, compatilbility modern and outaded functions)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Comment: create the window, the width and height, the name, the fullscreen, and share ressources
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	
	//Comment: if the window is NULL it will print int the console
	if (window == NULL)
	{
		std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	//Comment: We want to use the window
	glfwMakeContextCurrent(window);

	//Comment: initialize glad
	gladLoadGL();
	
	//Comment: tell opengl the window size we want, bottom left-top right corner.
	glViewport(0, 0, 800, 800);
	
	//Comment:
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Comment:
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	//Comment: 
	glCompileShader(vertexShader);

	//Comment:
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	//Comment:
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	
	//Comment:
	glCompileShader(fragmentShader);

	//Comment:
	GLuint shaderProgram = glCreateProgram();

	//Comment:
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	
	//Comment:
	glLinkProgram(shaderProgram);

	//Comment: 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Comment:
	GLfloat verticies[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 1.5f * float(sqrt(3)) / 2 / 3, 0.0f

	};

	//Comment:
	GLuint VAO, VBO;

	//Comment:
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	//Comment:
	glBindVertexArray(VAO);

	//Comment:
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Comment:
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	
	//Comment:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	//Comment:
	glEnableVertexAttribArray(0);

	//Comment:
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Comment: Close the window if we want too with the "X" on the top window, tell to gl to process all events
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	//Comment: We want to delete the window
	glfwDestroyWindow(window);

	//Comment: End the functions
	glfwTerminate();

}