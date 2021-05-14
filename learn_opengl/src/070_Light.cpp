#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include "opengl/VertexBuffer.h"
#include "opengl/IndexBuffer.h"
#include "opengl/VertexArray.h"
#include "opengl/Shader.h"
#include "opengl/Renderer.h"
#include "opengl/Texture.h"
#include "opengl/Mesh.h"
#include "Camera.h"

namespace {

	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;


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


		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		camera.ProcessMouseScroll(yoffset);
	}
}

int demoLightingScene() {
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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* GLAD Initialization after Opengl context has been set*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* Build and compile shader program */
	Shader shaderProgram("../resources/shaders/Lighting.vs",
		"../resources/shaders/Lighting.fs");

	

	{

		float vertices[] = {
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // top left
			0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // top right
			0.5f, -0.5f, 1.0f, 0.0f, 1.0f, // bottom right
			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // bottom left
			-0.5f, 0.5f, 1.0f, 1.0f, 0.0f // top left
		};

		unsigned int indices[] = { // note that we start from 0!
			0, 1, 3, // first triangle
			1, 2, 3, // second triangle
			0, 1, 5,
			0, 5, 4,
			0, 3, 7,
			0, 7, 4,
			2, 3, 6,
			3, 6, 7,
			1, 2, 6,
			1, 6, 5,
			5, 6, 7,
			4, 5, 7
		};

		VertexArray va;
		VertexBuffer vb(vertices, sizeof(vertices));
		IndexBuffer ib(indices, 36);

		VertexBufferLayout layout;
		layout.push<float>(3);
		layout.push<float>(2);
		va.addBuffer(vb, layout);

		Renderer renderer;

		Texture texture("../resources/container.jpg");
		texture.bind();

		shaderProgram.setInt("uTexture", 0);

		/* Enable depth test */
		glCall(glEnable(GL_DEPTH_TEST));

		while (!glfwWindowShouldClose(window))
		{
			/* Process user input */
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			/* Process user input */
			processInput(window);

			renderer.clear();

			glm::mat4 model = glm::mat4(1.0f);

			glm::mat4 view;
			view = camera.GetViewMatrix();

			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
				(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

			// get their uniform location and set matrix (using glm::value_ptr)
			shaderProgram.setMat4("model", model);
			shaderProgram.setMat4("view", view);
			shaderProgram.setMat4("projection", projection);

			renderer.draw(va, ib, shaderProgram);

			// Check and call events and swap the buffers
			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}
	glfwTerminate();
	return 0;
}