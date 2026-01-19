/* Some notes:
- glfw: window + context + input helper 
- opengl: specification implemented by GPU drivers allows cross platform development
- context ? i think of it like a state machine that keeps track of all the necessary state to allow me to draw stuff
- Basic steps:
    1. init 
    2. create window
    3. make context current (this threads holds the context) 
    4. clear, begin ---- end
    5. swap buffers (front <-> back)
    6. poll events
    7. terminate
*/
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize the GLEW */
    GLenum err = glewInit();
    if (GLEW_OK != err){
        std::cout << "Error : " << glewGetErrorString(err) << std::endl;
    }

    std::cout << "Status: Using GLFW version: " << glewGetString(GLEW_VERSION) << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2d(-0.5f,-0.5f);
        glVertex2d( 0.0f, 0.5f);
        glVertex2d( 0.5f,-0.5f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}