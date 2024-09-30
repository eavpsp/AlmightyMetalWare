 #version 330 core

    layout (location = 0) in vec3 inPos;
    layout (location = 1) in vec3 inNormal;
    layout (location = 2) in vec2 aTexCoord;
 
    
    out vec2 v_TexCoord;
    out vec3 v_Normal;
    out vec3 crntPos;


    uniform mat4 camMatrix;
    uniform mat4 model;

    void main()
    {

        crntPos = vec3(model * vec4(inPos, 1.0f));
	    gl_Position = camMatrix * vec4(crntPos, 1.0);
        v_TexCoord = aTexCoord;
        v_Normal = inNormal;
     
    }

