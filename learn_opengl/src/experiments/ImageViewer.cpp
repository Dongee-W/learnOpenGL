#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#ifndef STB_IMAGE_IMPLEMENTATION_
#define STB_IMAGE_IMPLEMENTATION_
#include "stb_image.h"
#endif /* STB_IMAGE_IMPLEMENTATION_ */
#include "../opengl/Shader.h"

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

    unsigned char* cvMat2TexInput(cv::Mat& img)
    {
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        cv::flip(img, img, -1);
        return img.data;
    }
}

int runImageViewer() {
    //int width, height, nrChannels;

    // OpenGL texture's y coordinate the opposite of image representation
    //stbi_set_flip_vertically_on_load(true);
    //unsigned char* data = stbi_load("../resources/nature.jpg", &width, &height,
    //    &nrChannels, 0);

    std::string path = "../resources/nature.jpg";
    cv::Mat originalImg = cv::imread(path);
    //cv::imshow("Original", originalImg);
    cv::line(originalImg, cv::Point(40, 20), cv::Point(100, 200), cv::Scalar(255, 0, 0), 5);

    std::cout << "Image width: " << originalImg.size().width << std::endl;
    std::cout << "Image height: " << originalImg.size().height << std::endl;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(originalImg.size().width, originalImg.size().height, "Image Viewer", NULL, NULL);
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

    glViewport(0, 0, originalImg.size().width, originalImg.size().height);
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



    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and 
    // set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
        GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
        (void*)0);
    glEnableVertexAttribArray(0);
    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
        (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Note that this is allowed, the call to glVertexAttribPointer 
    // registered VBO as the vertex attribute's bound vertex buffer 
    // object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't 
    // accidentally modify this VAO, but this rarely happens. 
    // Modifying other VAOs requires a call to glBindVertexArray anyways 
    // so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, originalImg.size().width, originalImg.size().height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, cvMat2TexInput(originalImg));
    glGenerateMipmap(GL_TEXTURE_2D);

    //stbi_image_free(data); // Free memory

    shaderProgram.use();
    shaderProgram.setInt("textureImage", 0);


    while (!glfwWindowShouldClose(window))
    {
        /* Process user input */
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        shaderProgram.use();

        glBindVertexArray(VAO);

        /* Model View Projection Matrices*/
        glm::mat4 model{1.0f};
        //model = glm::rotate(model, glm::radians(0.0f),
        //    glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 view{1.0f};
        // note that we¡¦re translating the scene in the reverse direction
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

        glm::mat4 projection{ 1.0f };

        projection = glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, 0.1f, 100.0f);

        // get their uniform location and set matrix (using glm::value_ptr)
        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}