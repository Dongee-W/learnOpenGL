#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#ifndef STB_IMAGE_IMPLEMENTATION_
#define STB_IMAGE_IMPLEMENTATION_
#include "stb_image.h"
#endif /* STB_IMAGE_IMPLEMENTATION_ */
#include "../opengl/Shader.h"
#include "../opengl/Texture.h"
#include "../opengl/VertexArray.h"
#include "../opengl/VertexBuffer.h"
#include "../opengl/IndexBuffer.h"
#include "../opengl/Renderer.h"

namespace {

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

int runImageViewer() {
    //int width, height, nrChannels;

    // OpenGL texture's y coordinate the opposite of image representation
    //stbi_set_flip_vertically_on_load(true);
    //unsigned char* data = stbi_load("../resources/nature.jpg", &width, &height,
    //    &nrChannels, 0);
    /*
    std::string path = "../resources/nature.jpg";
    cv::Mat originalImg = cv::imread(path);
    //cv::imshow("Original", originalImg);
    cv::line(originalImg, cv::Point(40, 20), cv::Point(100, 200), cv::Scalar(255, 0, 0), 5);

    std::cout << "Image width: " << originalImg.size().width << std::endl;
    std::cout << "Image height: " << originalImg.size().height << std::endl;*/

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 700, "Image Viewer", NULL, NULL);
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

    Texture texture{ "../resources/nature.jpg" };
    glfwSetWindowSize(window, texture.getWidth(), texture.getHeight());
    glViewport(0, 0, texture.getWidth(), texture.getHeight());
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    

    Shader shaderProgram("../resources/shaders/ImageViewer.vs", 
        "../resources/shaders/ImageViewer.fs");

    float vertices[] = {
        // positions // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };



    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, 6);

    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    va.addBuffer(vb, layout);

    Renderer renderer;

    texture.bind();

    shaderProgram.setInt("u_Texture", 0);

    texture.bind(0);

    //stbi_image_free(data); // Free memory
    /* Model View Projection Matrices*/
    glm::mat4 model{ 1.0f };
    //model = glm::rotate(model, glm::radians(0.0f),
    //    glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view{ 1.0f };
    // note that we¡¦re translating the scene in the reverse direction
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

    glm::mat4 projection{ 1.0f };

    projection = glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, 0.1f, 100.0f);

    shaderProgram.use();
    shaderProgram.setInt("textureImage", 0);
    shaderProgram.setMat4("model", model);
    shaderProgram.setMat4("view", view);
    shaderProgram.setMat4("projection", projection);


    while (!glfwWindowShouldClose(window))
    {
        /* Process user input */
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.clear();

        renderer.draw(va, ib, shaderProgram);


        // Check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}