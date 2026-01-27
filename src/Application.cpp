#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// global vars
float x_off = 0.0f;
float y_off = 0.0f;

static unsigned int CompileShader(unsigned int type,const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader,const std::string& fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
} 

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

    const std::string vertexShader = R"glsl(
        #version 330 core
        layout(location = 0) in vec4 position;
        void main(){
            gl_Position = position;
        }
    )glsl";
    
    const std::string fragmentShader = R"glsl(
        #version 330 core
        layout(location = 0) out vec4 color;
        void main(){
            color = vec4(1.0, 0.0, 1.0, 1.0);;
        }
    )glsl";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Getting Keyboard input before rendering */
        bool moved = false;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {x_off += 0.01f; moved = true;}; 
        if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS) {x_off -= 0.01f; moved = true;};
        if (glfwGetKey(window, GLFW_KEY_UP   ) == GLFW_PRESS) {y_off += 0.01f; moved = true;};
        if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS) {y_off -= 0.01f; moved = true;};
        
        if (moved){
            float positions[8] = {
                -0.1f + x_off,  -0.1f + y_off,
                -0.1f + x_off,   0.1f + y_off,
                 0.1f + x_off,   0.1f + y_off,
                 0.1f + x_off,  -0.1f + y_off
            };
            // store the data in the GPU memory 
            glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), positions, GL_DYNAMIC_DRAW);
        }
        
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