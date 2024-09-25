 #version 330 core

    in vec4 vtxColor;
    in vec4 vtxNormalQuat;
    in vec3 vtxView;

    out vec4 fragColor;

    uniform vec4 lightPos;
    uniform vec3 ambient;
    uniform vec3 diffuse;
    uniform vec4 specular; // w component is shininess

    // Rotate the vector v by the quaternion q
    vec3 quatrotate(vec4 q, vec3 v)
    {
        return v + 2.0*cross(q.xyz, cross(q.xyz, v) + q.w*v);
    }

    void main()
    {
        // Extract normal from quaternion
        vec4 normquat = normalize(vtxNormalQuat);
        vec3 normal = quatrotate(normquat, vec3(0.0, 0.0, 1.0));

        vec3 lightVec;
        if (lightPos.w != 0.0)
            lightVec = normalize(lightPos.xyz + vtxView);
        else
            lightVec = normalize(lightPos.xyz);

        vec3 viewVec = normalize(vtxView);
        vec3 halfVec = normalize(viewVec + lightVec);
        float diffuseFactor = max(dot(lightVec, normal), 0.0);
        float specularFactor = pow(max(dot(normal, halfVec), 0.0), specular.w);

        vec3 fragLightColor = ambient + diffuseFactor*diffuse + specularFactor*specular.xyz;

        fragColor = vec4(min(fragLightColor, 1.0), 1.0);
    }