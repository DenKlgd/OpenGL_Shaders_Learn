#include <iostream>
#include <chrono>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
void inputCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

Shader shader;

glm::mat4 trans(1.f);

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


    //glm::vec4 worldOffset(0.f, 0.f, 0.f, 1.f);
    
    trans = glm::translate(trans, glm::vec3(0.f, 0.f, -2.f));
    trans = glm::transpose(trans);
    //worldOffset = trans * worldOffset;
    

    shader.reload("Shaders/shader.frag", "Shaders/shader.vert");
    GLint transformID = shader.getUniformAttr("transform");
    GLint timeID = shader.getUniformAttr("time");

    glUniformMatrix4fv(transformID, 1, GL_FALSE, glm::value_ptr(trans));
    glUniform1f(timeID, 0.f);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    using Clock = std::chrono::steady_clock;
    auto timer = Clock::now();

    while (!glfwWindowShouldClose(wnd))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float timeElapsed = std::chrono::duration_cast< std::chrono::duration <float, std::ratio<1i64, 1i64>> >(Clock::now() - timer).count();
        // if (timeElapsed > 60)
        //     timer = Clock::now();

        //printf("Time elapsed %f\n", timeElapsed);
        
        glUniformMatrix4fv(transformID, 1, GL_FALSE, glm::value_ptr(trans));
        glUniform1f(timeID, timeElapsed);

        glBegin(GL_TRIANGLE_FAN);
            //glColor3f(1.f, 0.f, 0.f);
            glVertex3f( -1.f, -1.f,  0.f);
            glVertex3f( -1.f,  1.f,  0.f);
            glVertex3f(  1.f,  1.f,  0.f);
            glVertex3f(  1.f, -1.f,  0.f);
            glVertex3f( -1.f, -1.f,  0.f);
        glEnd();
        
        //glFlush();

        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}

void resizeWnd(GLFWwindow* wnd, int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float k = (float) width / height;
    glFrustum(-k, k, -1, 1, 1, 1000);
    glMatrixMode(GL_MODELVIEW);

    std::cout << shader.getUniformAttr("screen") << '\n';
    std::cout << width << "x" << height << '\n';

    glUniform3ui(shader.getUniformAttr("screen"), width, height, 1000);
}

void inputCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    constexpr float angleRadian = 2 * (M_PI / 180.f);

    switch (key)
    {

    case GLFW_KEY_ENTER:
    {
        shader.reload("Shaders/shader.frag", "Shaders/shader.vert");

        GLint transformID = shader.getUniformAttr("transform");
        GLint timeID = shader.getUniformAttr("time");

        glUniformMatrix4fv(transformID, 1, GL_FALSE, glm::value_ptr(trans));
        break;
    }

    }

    if (key == GLFW_KEY_LEFT)
    {
        trans = glm::rotate(trans, angleRadian, glm::vec3(0.f, 0.f, 1.f));
    }
    else if (key == GLFW_KEY_RIGHT)
    {
        trans = glm::rotate(trans, -angleRadian, glm::vec3(0.f, 0.f, 1.f));
    }

    if (key == GLFW_KEY_UP)
    {
        trans = glm::rotate(trans, angleRadian, glm::vec3(1.f, 0.f, 0.f));
    }
    else if (key == GLFW_KEY_DOWN)
    {
        trans = glm::rotate(trans, -angleRadian, glm::vec3(1.f, 0.f, 0.f));
    }

}
