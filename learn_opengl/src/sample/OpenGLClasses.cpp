#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../opengl/VertexBuffer.h"
#include "../opengl/IndexBuffer.h"
#include "../opengl/VertexArray.h"
#include "../opengl/Shader.h"
#include "../opengl/Renderer.h"
#include "../opengl/Texture.h"

namespace {

	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	/* glfw: whenever the window size changed (by OS or user resize)
		this callback function executes */
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}


	/* Process all input: query GLFW whether relevant keys are
		pressed/released this frame and react accordingly */
	void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
}

int demoOpenGLClasses() {
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* GLAD Initialization after Opengl context has been set*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* Build and compile shader program */
	Shader shaderProgram("../resources/shaders/OpenGLClassesTest.vs", 
		"../resources/shaders/OpenGLClassesTest.fs");

	{
		
		float vertices[] = {
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f // top left
		};
		/*
		float vertices[] = {
			0.5f, 0.5f, 0.0f, // top right
			0.5f, -0.5f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, // bottom left
			-0.5f, 0.5f, 0.0f,  // top left
		};*/
		unsigned int indices[] = { // note that we start from 0!
			0, 1, 3, // first triangle
			1, 2, 3 // second triangle
		};

		VertexArray va;
		VertexBuffer vb(vertices, sizeof(vertices));
		IndexBuffer ib(indices, 6);

		VertexBufferLayout layout;
		layout.push<float>(3);
		layout.push<float>(2);
		va.addBuffer(vb, layout);

		Renderer renderer;

		Texture texture("../resources/container.jpg");
		texture.bind();

		shaderProgram.setInt("u_Texture", 0);

		while (!glfwWindowShouldClose(window))
		{
			/* Process user input */
			processInput(window);

			renderer.clear();

			renderer.draw(va, ib, shaderProgram);

			// Check and call events and swap the buffers
			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}
	glfwTerminate();
	return 0;
}