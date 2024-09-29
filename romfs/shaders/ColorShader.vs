 #version 330 core

    layout (location = 0) in vec3 aVertexPosition;
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTexCoord;

    out vec3 ourColor;
    out vec2 v_TexCoord;
    void main()
    {
        gl_Position = vec4(aVertexPosition.x, aVertexPosition.y, aVertexPosition.z, 1.0);
        ourColor = aColor;
        v_TexCoord = aTexCoord;
    }