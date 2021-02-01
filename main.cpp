#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
// settings
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

float visibility = 0.2f;

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

    float vertices[] = {
            -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.f, 1.f,
            0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.f, 1.f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.f, 0.f
    };

    unsigned int indices[] = {
            0, 1, 2,
            1, 2, 3
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, channels;
    unsigned char* data = stbi_load("../container.jpg", &width, &height, &channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("../awesomeface.png", &width, &height, &channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    one.use();
    one.setInt("texture1", 0);
    one.setInt("texture2", 1);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.4f, 0.5f, 0.7f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glm::mat4 matrix(1.0f);
        matrix = glm::translate(matrix, glm::vec3(0.5f, -0.5f, 0.0f));
        matrix = glm::rotate(matrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));



        one.use();
        one.setMat4("transform", matrix);
        glBindVertexArray(VAO);

        auto time = static_cast<float>(glfwGetTime());
        float green = 1.f; //std::sin(time) / 2 + 0.5f;
        one.setFloat("offset", green);
        one.setFloat("vis", visibility);

        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 projection(1.0f);
        model = glm::rotate(model, glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f));
        view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
        projection = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.f);
        one.setMat4("model", model);
        one.setMat4("view", view);
        one.setMat4("projection", projection);
        /**int vertexColorLocation = glGetUniformLocation(shaderProgram, "OurColor");
        glUniform4f(vertexColorLocation, 0.0f, green, 0.0f, 0.0f);
        */
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glm::mat4 scaler(1.0f);
        scaler = glm::translate(scaler, glm::vec3(-0.5f, 0.5f, 0.0f));
        auto scale = sin(glfwGetTime());
        scaler = glm::scale(scaler, glm::vec3(scale, scale, scale));
        one.setMat4("transform", scaler);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        visibility += 0.01f;
        if (visibility > 1.f)
        {
            visibility = 1.f;
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        visibility -= 0.01f;
        if (visibility < 0.f)
        {
            visibility = 0.f;
        }
    }
}
