#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "window", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to Create\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init glad\n";
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader one("../shaders/shader.vsh", "../shaders/shader.fsh");
    Shader two("../shaders/shader.vsh", "../shaders/second.fsh");

    float vertices[] = {
            -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    float secondVert[] = {
            -0.5f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f
    };
    unsigned int indices[] = {
            0, 1, 2,
            1, 2, 3
    };

    unsigned int VAO[2], VBO[2], EBO;
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    //glGenBuffers(1, &EBO);


    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondVert), secondVert, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.4f, 0.5f, 0.7f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        one.use();
        glBindVertexArray(VAO[0]);

        auto time = static_cast<float>(glfwGetTime());
        float green = std::sin(time) / 2 + 0.5f;
        one.setFloat("offset", green);
        /**int vertexColorLocation = glGetUniformLocation(shaderProgram, "OurColor");
        glUniform4f(vertexColorLocation, 0.0f, green, 0.0f, 0.0f);
        */
        glDrawArrays(GL_TRIANGLES, 0, 3);
        two.use();
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    //glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
