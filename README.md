# opengl
Goal: explore and experiment with opengl

Pre-req: 
    
    sudo apt-get install libglfw3-dev

Build and Compile cmd: 

    g++ main.cpp -lglfw -lGLEW -lGL -o main

Debug Build:

    g++ -ggdb3 -O0 -Wall -Wextra main.cpp -lglfw -lGLEW -lGL -o main

Run cmd:
    
    ./main