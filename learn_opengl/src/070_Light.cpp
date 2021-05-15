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
	Shader shaderObject("../resources/shaders/Lighting.vs",
		"../resources/shaders/Lighting.fs");

	Shader shaderLight("../resources/shaders/Lighting.vs",
		"../resources/shaders/LightSource.fs");

	{

		/*float vertices[] = {
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
		};*/
		float vertices[] = {
			// positions // normals // texture coords
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = { // note that we start from 0!
			0, 1, 2, // first triangle
			3, 4, 5, // second triangle
			6, 7, 8,
			9, 10, 11,
			12, 13, 14,
			15, 16, 17,
			18, 19, 20,
			21, 22, 23,
			24, 25, 26,
			27, 28, 29,
			30, 31, 32,
			33, 34, 35
		};

		VertexArray va;
		VertexBuffer vb(vertices, sizeof(vertices));
		IndexBuffer ib(indices, 36);

		VertexBufferLayout layout;
		layout.push<float>(3);
		layout.push<float>(3);
		layout.push<float>(2);
		va.addBuffer(vb, layout);

		/* Vertex for light bulb */
		VertexArray lightVa;
		VertexBuffer lightVb(vertices, sizeof(vertices)); // More efficient to reuse 
		IndexBuffer lightIb(indices, 36);
		VertexBufferLayout lightLayout;
		lightLayout.push<float>(3);
		lightLayout.push<float>(3);
		lightLayout.push<float>(2);
		lightVa.addBuffer(lightVb, lightLayout);

		Renderer renderer;
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

		shaderObject.use();
		//shaderObject.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		shaderObject.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderObject.setVec3("lightPos", lightPos);
		

		shaderObject.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		shaderObject.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
		shaderObject.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		shaderObject.setFloat("material.shininess", 32.0f);

		shaderObject.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shaderObject.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darkened
		shaderObject.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		
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

			/* Draw cube */
			shaderObject.use();
			shaderObject.setVec3("viewPos", camera.Position);
			shaderObject.setMat4("model", model);
			shaderObject.setMat4("view", view);
			shaderObject.setMat4("projection", projection);

			renderer.draw(va, ib, shaderObject);

			/* Draw light bulb */
			model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f));

			shaderLight.use();
			shaderLight.setMat4("model", model);
			shaderLight.setMat4("view", view);
			shaderLight.setMat4("projection", projection);

			renderer.draw(lightVa, lightIb, shaderLight);

			// Check and call events and swap the buffers
			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}
	glfwTerminate();
	return 0;
}