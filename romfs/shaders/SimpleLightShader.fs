 #version 330 core

    in vec3 ourColor;
    in vec2 v_TexCoord;



    uniform sampler2D u_Texture;
    layout (location = 0) out vec4 FragColor;
    void main()
    {

      FragColor = texture(u_Texture, v_TexCoord);

    };