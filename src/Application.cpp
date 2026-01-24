#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// global vars
float x_off = 0.0f;
float y_off = 0.0f;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "window", NULL, NULL);
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

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Getting Keyboard input before rendering */
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) x_off += 0.01f; 
        if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS) x_off -= 0.01f;
        if (glfwGetKey(window, GLFW_KEY_UP   ) == GLFW_PRESS) y_off += 0.01f;
        if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS) y_off -= 0.01f;
        
        float positions[8] = {
            -0.1f + x_off,  -0.1f + y_off,
            -0.1f + x_off,   0.1f + y_off,
             0.1f + x_off,   0.1f + y_off,
             0.1f + x_off,  -0.1f + y_off
        };
        
        glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), positions, GL_DYNAMIC_DRAW);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_QUADS, 0, 4);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    std::cout << "========================= Application Closed =========================" << std::endl; 
    return 0;
}