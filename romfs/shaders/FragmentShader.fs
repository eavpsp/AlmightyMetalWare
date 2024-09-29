#version 330 core

    in vec3 ourColor;
    uniform sampler2D u_Texture;
    in vec2 v_TexCoord;
    layout (location = 0) out vec4 fragColor;

    void main()
    {
        vec4 texColor = texture(u_Texture, v_TexCoord);
        fragColor = texColor;
    }