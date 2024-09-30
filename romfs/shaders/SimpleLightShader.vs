 #version 330 core

    layout (location = 0) in vec3 inPos;
    layout (location = 1) in vec3 inNormal;
    layout (location = 2) in vec2 aTexCoord;

    out vec2 v_TexCoord;

    uniform mat4 mdlvMtx;
    uniform mat4 projMtx;
    uniform mat4 viewMtx;
    
    void main()
    {

        vec4 pos = mdlvMtx * vec4(inPos, 1.0);
        gl_Position = projMtx * pos * viewMtx;
        v_TexCoord = aTexCoord;
    }