Notes:
- Linking order is important
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
- GLEW ? To get the gpu driver specific implementation of open gl (gives us the fpointers to the methods)
- Vertex buffer: data that will live in GPU VRAM 
- Shader: code sections that provides instruction to GPU on how to utilize the memory that we gave it (runs on the  GPU) 
- OpenGl is kinda like a state machine and state is determined based on the buffer and the shader you decide to use.
- Memory layout ? we inform how it is structed 
- Vertex is just a point on your geometry, it can contain more data than just position. It can infact contain a whole lot ! like color, normals, texture coord. Vertex.position is the position but there could be other things that the vertex stores. These are called attributes of the vertex (normal is an attribute, position is an attrib, color is an attrib, texture coord is an attribute of the vertex)
- Vertex {
    attribte1{
        Component1
        Component2
        ..
    }
    attribte2
    ..
}
- Most common shaders: vertex shaders and fragment shader (pixel shaders) and there are many more shaders (computer shaders ? )
- drawCall() for gpu -> vertex shader -> fragment shader -> pixels drawn on our screen  
- well vertex shader simply tells where the vertex needs to be on the screen canvas. 
- vertex shader called say for a triangle three times, pixel shader could be called for hundreds or thousands of times.
- pixel/fragment shader (draw each pixel, iterates over the pixels, decides the color).
- you can pass data from the vertex to the fragment/pixel shader
- you need to understand how to divide the work load between vertex and pixel shader. Pixel/fragment shader are more expensive since they work pixel by pixel and do more work 
- vertex shader -> position on the screen; fragment/pixel shader -> pixel color on the screen 
- some game engines generate shaders on the fly !!! 
