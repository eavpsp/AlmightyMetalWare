 #version 330 core

    in vec3 ourColor;
    in vec2 v_TexCoord;
    in vec3 v_Normal;
    in vec3 crntPos;
  

    uniform sampler2D u_Texture;
    uniform vec3 u_LightPos;
    uniform vec4 u_LightColor;
    uniform vec3 camPos;

    out vec4 FragColor;

    void main()
    {

      float ambient = 0.20f;

      // diffuse lighting
      vec3 normal = normalize(v_Normal);
      vec3 lightDirection = normalize(u_LightPos - crntPos);
      float diffuse = max(dot(normal, lightDirection), 0.0f);

      // specular lighting
      float specularLight = 0.50f;
      vec3 viewDirection = normalize(camPos - crntPos);
      vec3 reflectionDirection = reflect(-lightDirection, normal);
      float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
      float specular = specAmount * specularLight;
      vec3 lightVec;

      vec4 texColor = texture(u_Texture, v_TexCoord);
       
      if (texColor.a == 0.0) 
      {
        FragColor = u_LightColor * (diffuse + ambient + specular);
      }
      else
      {
        FragColor = texture(u_Texture, v_TexCoord) * u_LightColor * (diffuse + ambient + specular);
      }

    };