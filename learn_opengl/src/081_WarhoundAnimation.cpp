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
#include "opengl/Model.h"
#include "utils/SceneGraph.h"

namespace {

	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;
	float accumulatedTime = 0.0f;

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

int animateWarhound() {
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
	Shader shader("../resources/shaders/Model.vs",
		"../resources/shaders/Model.fs");

	
	SceneGraph scene(11);
	scene.addEdge(0, 1);
	scene.addEdge(0, 2);
	scene.addEdge(0, 3);
	scene.addEdge(0, 4);
	scene.addEdge(0, 5);
	scene.addEdge(0, 6);
	scene.addEdge(3, 7);
	scene.addEdge(4, 8);
	scene.addEdge(5, 9);
	scene.addEdge(6, 10);

	auto allPath = scene.bfsHistory(0);

	{
		//Model test("../resources/objects/warhound/warhound.glb");
		Model model0("../resources/objects/warhound/body.obj");
		Model model1("../resources/objects/warhound/head.obj");
		Model model2("../resources/objects/warhound/tail.obj");
		Model model3("../resources/objects/warhound/feet_03.obj");
		Model model4("../resources/objects/warhound/feet_04.obj");
		Model model5("../resources/objects/warhound/feet_05.obj");
		Model model6("../resources/objects/warhound/feet_06.obj");
		Model model7("../resources/objects/warhound/feet_07.obj");
		Model model8("../resources/objects/warhound/feet_08.obj");
		Model model9("../resources/objects/warhound/feet_09.obj");
		Model model10("../resources/objects/warhound/feet_10.obj");
		
		/* Scene setup */
		std::vector<SceneNode> sceneNodes;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
		sceneNodes.push_back(SceneNode{ &model0, model });


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.67f, 0.0f, 0.14f));
		sceneNodes.push_back(SceneNode{ &model1, model });

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.93f, 0.0f, 0.548f));
		sceneNodes.push_back(SceneNode{ &model2, model });

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.77f, 0.82f, -1.0f));
		model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0.0, 1.0, 0.0));
		sceneNodes.push_back(SceneNode{ &model3, model });

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.77f, -0.82f, -1.0f));
		model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0.0, 1.0, 0.0));
		sceneNodes.push_back(SceneNode{ &model4, model });

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.77f, 0.82f, -1.0f));
		model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0.0, 1.0, 0.0));
		sceneNodes.push_back(SceneNode{ &model5, model });

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.77f, -0.82f, -1.0f));
		model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0.0, 1.0, 0.0));
		sceneNodes.push_back(SceneNode{ &model6, model });

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, -0.4f));
		model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0.0, 1.0, 0.0));
		sceneNodes.push_back(SceneNode{ &model7, model });

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, -0.4f));
		model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0.0, 1.0, 0.0));
		sceneNodes.push_back(SceneNode{ &model8, model });

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, -0.4f));
		model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0.0, 1.0, 0.0));
		sceneNodes.push_back(SceneNode{ &model9, model });

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-.1f, 0.0f, -0.4f));
		model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0.0, 1.0, 0.0));
		sceneNodes.push_back(SceneNode{ &model10, model });



		/* Enable depth test */
		glCall(glEnable(GL_DEPTH_TEST));


		while (!glfwWindowShouldClose(window))
		{
			/* Process user input */
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			accumulatedTime += deltaTime;

			/* Process user input */
			processInput(window);
			glCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
			glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			shader.use();

			// view/projection transformations
			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			glm::mat4 view = camera.GetViewMatrix();
			shader.setMat4("projection", projection);
			shader.setMat4("view", view);

			/* Animation update*/
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.2f * deltaTime, 0.0f, 0.0f));
			sceneNodes[0].modelMatrix *= model;

			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, (float)sin(accumulatedTime * 3.14 / 3) * 0.0005f));
			sceneNodes[1].modelMatrix *= model;

			model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians((float)sin(accumulatedTime * 3.14 / 0.5) * 0.2f), glm::vec3(0.0, 1.0, 0.0));
			sceneNodes[2].modelMatrix *= model;


			model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians((float)sin(accumulatedTime * 3.14 / 2) * 0.4f), glm::vec3(0.0, 1.0, 0.0));
			sceneNodes[3].modelMatrix *= model;

			model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians((float)sin(-accumulatedTime * 3.14 / 2) * 0.4f), glm::vec3(0.0, 1.0, 0.0));
			sceneNodes[4].modelMatrix *= model;

			model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians((float)sin(-accumulatedTime * 3.14 / 2) * 0.4f), glm::vec3(0.0, 1.0, 0.0));
			sceneNodes[5].modelMatrix *= model;

			model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians((float)sin(accumulatedTime * 3.14 / 2) * 0.4f), glm::vec3(0.0, 1.0, 0.0));
			sceneNodes[6].modelMatrix *= model;

			model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians((float)sin(accumulatedTime * 3.14 / 2) * 0.2f), glm::vec3(0.0, 1.0, 0.0));
			sceneNodes[7].modelMatrix *= model;

			model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians((float)sin(-accumulatedTime * 3.14 / 2) * 0.2f), glm::vec3(0.0, 1.0, 0.0));
			sceneNodes[8].modelMatrix *= model;

			model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians((float)sin(-accumulatedTime * 3.14 / 2) * 0.2f), glm::vec3(0.0, 1.0, 0.0));
			sceneNodes[9].modelMatrix *= model;

			model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians((float)sin(accumulatedTime * 3.14 / 2) * 0.2f), glm::vec3(0.0, 1.0, 0.0));
			sceneNodes[10].modelMatrix *= model;

			for (auto& path : allPath) {
				model = glm::mat4(1.0f);
				for (auto& node : path) {
					model = model * sceneNodes[node].modelMatrix;
				}
				shader.setMat4("model", model);
				sceneNodes[path.back()].model->draw(shader);
			}


			// Check and call events and swap the buffers
			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}
	glfwTerminate();
	return 0;
}