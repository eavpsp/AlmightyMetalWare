 #version 330 core

    layout (location = 0) in vec3 inPos;
    layout (location = 1) in vec3 inNormal;
    layout (location = 2) in vec2 aTexCoord;
 
    
    out vec2 v_TexCoord;
    out vec3 v_Normal;
    out vec3 crntPos;


    uniform mat4 camMatrix;
    uniform mat4 model;
    uniform mat4 translation;
    uniform mat4 rotation;
    uniform mat4 scale;

    void main()
    {

        crntPos = vec3(model * translation * -rotation * scale * vec4(inPos, 1.0f));
	    gl_Position = camMatrix * vec4(crntPos, 1.0);
        v_TexCoord = mat2(0.0, -10., 1.0, 0.0) * aTexCoord;
        v_Normal = inNormal;
     
    }

