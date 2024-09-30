 #version 330 core

    layout (location = 0) in vec3 inPos;
    layout (location = 1) in vec3 inNormal;
    layout (location = 2) in vec2 aTexCoord;

    out vec2 v_TexCoord;

    uniform mat4 camMatrix;
    void main()
    {

        vec4 pos = camMatrix * vec4(inPos, 1.0);
        gl_Position = pos;
        v_TexCoord = aTexCoord;
    }