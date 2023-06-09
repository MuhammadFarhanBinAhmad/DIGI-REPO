#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <string>

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 400, "WIndowName", NULL, NULL);

	//standard check for window is not null
	if (window == NULL)
	{
		glfwTerminate();
		std::cout << "error window" << std::endl;
	}
	glfwMakeContextCurrent(window);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) != true)
	{
		std::cout << "fail" << std::endl;
	}

	GLuint vertex_Buffer;
	glCreateBuffers(1, &vertex_Buffer);
	GLuint vertex_Array;
	glCreateVertexArrays(1, &vertex_Array);

	glBindVertexArray(vertex_Array);

	std::string vertex_shdr_text{ R"(

#version 450

void main()
{
gl_Position = vec4(0.5,0.0,0.0,1.0);
}
)"
	};
	std::string fragment_shdr_text{ R"(

#version 450

out vec4 fragmentcolour;

void main()
{
fragmentcolour = vec4(1.0,0.0,0.0,1.0);
}
)"
	};

	GLuint shaderProgram = glCreateProgram();

	GLchar const* gl_vertex[]{ vertex_shdr_text.c_str() };

	GLuint vertexShaderHdl = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderHdl, 1, gl_vertex, NULL);
	glAttachShader(shaderProgram,vertexShaderHdl);

	GLchar const* gl_frag[]{ fragment_shdr_text.c_str() };
	GLuint FragmentShaderHdl = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderHdl, 1, gl_frag, NULL);
	glCompileShader(FragmentShaderHdl);
	glAttachShader(shaderProgram, FragmentShaderHdl);

	glGetShaderInfoLog(FragmentShaderHdl, 1024, &len, buffer);




	//draw window with colour
	while (glfwWindowShouldClose(window) == false)
	{
		glfwPollEvents();

		float col = 0.3f;
		int width, height;
		glClear(GL_COLOR_BUFFER_BIT);

		glPointSize(30.f);
		glDrawArrays(GL_POINTS, 1, 0);

		glClearColor(col, col, col, 1.0);
		glClear(GL_CLEAR_BUFFER);


		glfwPollEvents(); // check for inputs
		glfwSwapBuffers(window); // show what you rendered 
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	// Do stuff
	std::cout << "Hello world!" << std::endl;

	return 0;
}
