#include <iostream>
#include <chrono>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#ifndef _USE_MATH_DEFINES
    #define _USE_MATH_DEFINES
    #include "math.h"
#endif

#define WIDTH 800
#define HEIGHT 600

#ifdef UNIX
    #define CLS system("clear")
#elif _WIN32
    #define CLS system("cls")
#endif

void resizeWnd(GLFWwindow* wnd, int width, int height);
void processInput(GLFWwindow* wnd);
void inputCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void lookAroundCallback(GLFWwindow* window, double xpos, double ypos);

Shader shader, defaultShader;

glm::mat4 transformMat(1.f);
glm::vec3 pos;
glm::vec2 camAngle;
glm::mat4 projectionMat = glm::perspective(glm::radians(45.f), (float)WIDTH / HEIGHT, 0.1f, 1000.f);


float cube[][3] = {
    -1.f, -1.f,  0.f,
    -1.f,  1.f,  0.f,
     1.f,  1.f,  0.f,
     1.f, -1.f,  0.f,
    -1.f, -1.f,  0.f,
    -1.f, -1.f,  3.f,
     1.f, -1.f,  3.f,
     1.f, -1.f,  0.f,
     1.f, 1.f,  0.f,
     1.f, 1.f,  3.f,
     1.f, -1.f,  3.f,
     1.f, -1.f,  3.f,
};

GLfloat axisVert[] = {
    0.f, 0.f, 0.f,
    1.f, 0.f, 0.f,
    0.f, 1.f, 0.f,
};

GLfloat axisColors[] = {
    1.f, 0.f, 0.f,
    0.f, 1.f, 0.f,
    0.f, 0.f, 1.f,
};

GLuint axisInd[] = {
    0, 1, 
    0, 2, 
    1, 2,
};



int main()
{
    CLS;
    glfwInit();


    GLFWwindow* wnd = glfwCreateWindow(WIDTH, HEIGHT, "Shaders", 0, 0);

    if (wnd == nullptr)
    {
        std::cout << "GLFW Error!\n";
        return -1;
    }
    glfwMakeContextCurrent(wnd);
    gladLoadGL();

    glfwSetWindowSizeCallback(wnd, resizeWnd);
    glfwSetKeyCallback(wnd, inputCallback);
    glfwSetCursorPosCallback(wnd, lookAroundCallback);
    glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    shader.reload("Shaders/shader.frag", "Shaders/shader.vert");
    GLint projectionID = shader.getUniformAttr("projection");
    GLint viewID = shader.getUniformAttr("view");
    GLint timeID = shader.getUniformAttr("time");
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projectionMat));
    glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(transformMat));
    glUniform1f(timeID, 0.f);


    defaultShader.reload("Shaders/defaultShader.frag", "Shaders/defaultShader.vert");
    GLint defaultShaderProjectionID = defaultShader.getUniformAttr("projection");
    GLint defaultShaderViewID = defaultShader.getUniformAttr("view");
    //GLint defaultShaderTimeID = defaultShader.getUniformAttr("time");
    glUniformMatrix4fv(defaultShaderProjectionID, 1, GL_FALSE, glm::value_ptr(projectionMat));
    glUniformMatrix4fv(defaultShaderViewID, 1, GL_FALSE, glm::value_ptr(transformMat));
    //glUniform1f(defaultShaderTimeID, 0.f);

    glEnable(GL_DEPTH_TEST);

    GLuint cubeVBO;
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint axisVBO;
    GLuint axisEBO;
    GLuint axisColorVBO;
    GLuint axisVAO;
    glGenBuffers(1, &axisVBO);
    glGenBuffers(1, &axisEBO);
    glGenBuffers(1, &axisColorVBO);
    glGenVertexArrays(1, &axisVAO);

    glBindVertexArray(axisVAO);
            glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(axisVert), axisVert, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexArrayAttrib(axisVAO, 0);

            glBindBuffer(GL_ARRAY_BUFFER, axisColorVBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(axisColors), axisColors, GL_STATIC_DRAW);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexArrayAttrib(axisVAO, 1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axisEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(axisInd), axisInd, GL_STATIC_DRAW);
    glBindVertexArray(0);
    

    tinyobj::LoadObj()


    using Clock = std::chrono::steady_clock;
    auto timer = Clock::now();

    pos.z += -3;

    while (!glfwWindowShouldClose(wnd))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float timeElapsed = std::chrono::duration_cast< std::chrono::duration <float, std::ratio<1i64, 1i64>> >(Clock::now() - timer).count();
        // if (timeElapsed > 60)
        //     timer = Clock::now();

        //printf("Time elapsed %f\n", timeElapsed);

        float radX = glm::radians(camAngle.x + 90);
        transformMat = glm::rotate(glm::radians(camAngle.x), glm::vec3{0, 1, 0});
        transformMat = glm::rotate(transformMat, glm::radians(camAngle.y), glm::vec3{ glm::sin(radX), 0, -1 * glm::cos(radX) });       
        transformMat *= glm::translate(pos);


        shader.use();
        glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projectionMat));
        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(transformMat));
        glUniform1f(timeID, timeElapsed);


        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
            glVertexPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glEnableClientState(GL_VERTEX_ARRAY);
            glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(cube) / sizeof(cube[0]));
        glDisableClientState(GL_VERTEX_ARRAY);
        
        
        defaultShader.use();
        glUniformMatrix4fv(defaultShaderProjectionID, 1, GL_FALSE, glm::value_ptr(projectionMat));
        glUniformMatrix4fv(defaultShaderViewID, 1, GL_FALSE, glm::value_ptr( glm::translate(transformMat, glm::vec3{0, 0, -3}) ));
        //glUniform1f(defaultShaderTimeID, timeElapsed);
        glLineWidth(3);


        glBindVertexArray(axisVAO);
            glDrawElements(GL_LINES, sizeof(axisInd) / sizeof(axisInd[0]), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(wnd);
        glfwPollEvents();

        processInput(wnd);
    }
    
    glDeleteBuffers(1, &cubeVBO);
    glfwTerminate();

    return 0;
}

void resizeWnd(GLFWwindow* wnd, int width, int height)
{
    glViewport(0, 0, width, height);
    float k = (float) width / height;
    projectionMat = glm::perspective(glm::radians(45.f), k, 0.1f, 1000.f);
}

void processInput(GLFWwindow* wnd)
{
    float k = 0.02f;

    float radX = glm::radians(camAngle.x + 90);
    float normRadX = glm::radians(camAngle.x - 90);

    //constexpr short keys[] = {GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D};

    if (glfwGetKey(wnd, GLFW_KEY_LEFT_SHIFT))
    {
        k = 0.06f;
    }

    if (glfwGetKey(wnd, GLFW_KEY_W))
    {
        pos.z += 2.f * k * sin(radX);
        pos.x += 2.f * k * cos(radX);
    }
    else if (glfwGetKey(wnd, GLFW_KEY_S))
    {
        pos.z -= 2.f * k * sin(radX);
        pos.x -= 2.f * k * cos(radX);
    }

    if (glfwGetKey(wnd, GLFW_KEY_A))
    {
        pos.x += 2.f * k * -sin(normRadX);
        pos.z += 2.f * k * cos(normRadX);
    }
    else if (glfwGetKey(wnd, GLFW_KEY_D))
    {
        pos.x -= 2.f * k * -sin(normRadX);
        pos.z -= 2.f * k * cos(normRadX);
    }

    if (glfwGetKey(wnd, GLFW_KEY_SPACE))
    {
        pos.y -= 2.f * k;
    }
    else if (glfwGetKey(wnd, GLFW_KEY_LEFT_CONTROL))
    {
        pos.y += 2.f * k;
    }
}

void inputCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // if (key == GLFW_KEY_LEFT)
    // {
    //     axisInd[1] -= 1;
    // }
    // if (key == GLFW_KEY_RIGHT)
    // {
    //     axisInd[1] += 1;
    // }
    
    if (key == GLFW_KEY_ENTER)
    {
        shader.reload("Shaders/shader.frag", "Shaders/shader.vert");

        GLint projectionID = shader.getUniformAttr("projection");
        GLint viewID = shader.getUniformAttr("view");
        GLint timeID = shader.getUniformAttr("time");
        glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projectionMat));
        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(transformMat));
        glUniform1f(timeID, 0.f);

        defaultShader.reload("Shaders/defaultShader.frag", "Shaders/defaultShader.vert");
        GLint defaultShaderProjectionID = defaultShader.getUniformAttr("projection");
        GLint defaultShaderViewID = defaultShader.getUniformAttr("view");
        glUniformMatrix4fv(defaultShaderProjectionID, 1, GL_FALSE, glm::value_ptr(projectionMat));
        glUniformMatrix4fv(defaultShaderViewID, 1, GL_FALSE, glm::value_ptr(transformMat));
    }
}

void lookAroundCallback(GLFWwindow* window, double xpos, double ypos)
{
    constexpr float k = 0.1f;
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    camAngle.x += (xpos - width / 2) * k;
    camAngle.y += (ypos - height / 2) * k;

    glfwSetCursorPos(window, width / 2, height / 2);
}
