#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define WIDTH 800
#define HEIGHT 600

void drawTriangle();

int main()
{
    system("clear");
    glfwInit();


    GLFWwindow* wnd = glfwCreateWindow(WIDTH, HEIGHT, "Shaders", 0, 0);

    if (wnd == nullptr)
    {
        std::cout << "GLFW Error!\n";
        return -1;
    }
    glfwMakeContextCurrent(wnd);
    gladLoadGL();

    glMatrixMode(GL_PROJECTION);
    glFrustum(-1, 1, -1, 1, 1, 100);
    //glOrtho(-1, 1, -1, 1, 0, 500);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.f, 0.f, -5.f);

    while (!glfwWindowShouldClose(wnd))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glRotatef(5, 1, 0, 0);

        glBegin(GL_TRIANGLES);
            glColor3f(1.f, 0.f, 0.f);
            glVertex3f(-0.5f, -0.5f, 0.f);
            glVertex3f(0.f, 0.5f, 0.f);
            glVertex3f(0.5f, -0.5f, 0.f);
        glEnd();
        
        //glFlush();

        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}

void drawTriangle()
{

}
