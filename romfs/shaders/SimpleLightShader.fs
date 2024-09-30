 #version 330 core

    in vec3 ourColor;
    in vec2 v_TexCoord;



    uniform sampler2D u_Texture;
    layout (location = 0) out vec4 FragColor;
    void main()
    {

      FragColor = vec4(vec3(1.0, 1.0, 1.0) * texture(u_Texture, v_TexCoord);

    };