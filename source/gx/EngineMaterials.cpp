///set up engine materials and add to custom list

#include <EngineMaterials.h>
#include "../debug/debug.h"

ShaderMaterialInterface *EngineMaterials::getLightMaterial()
{
    return  &_lightMaterial;
}

ShaderMaterialInterface *EngineMaterials::getColorMaterial()
{
    return &_colorMaterial;
}

void EngineMaterials::initEngineMaterials()
{
    
    ShaderInterface *color_shader = new ShaderInterface("romfs:/shaders/ColorShader.vs", "romfs:/shaders/FragmentShader.fs");
    ShaderInterface *light_shader = new ShaderInterface("romfs:/shaders/SimpleLightShader.vs", "romfs:/shaders/SimpleLightShader.fs");
    _colorMaterial.SetUpShader("ColorMaterial", color_shader);
    _lightMaterial.SetUpShader("LightMaterial", light_shader);
   
}

EngineMaterials &EngineMaterials::getEngineMaterialsClass()
{
   static EngineMaterials *engineMaterials = nullptr;
    if(engineMaterials == nullptr)
    {
        engineMaterials = new EngineMaterials();
    }
    return *engineMaterials;
}


