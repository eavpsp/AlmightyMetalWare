#ifndef ENGINE_MATERIALS_H
#define ENGINE_MATERIALS_H

#include "ShaderMaterialInterface.h"
#include "CustomList.h"
//once made these materials should be cloned to each vertexbuffer object
class EngineMaterials
{
    private: 
      ColorMaterial _colorMaterial;
      LightMaterial _lightMaterial;
      LightObjectMaterial _lightObjectMaterial;
      GameFontMaterial *_gameFontMaterial;
    public:
        ShaderMaterialInterface *getLightMaterial();
        ShaderMaterialInterface *getColorMaterial();
        ShaderMaterialInterface *getLightObjectMaterial();
        GameFontMaterial *getGameFontMaterial();
        
        void initEngineMaterials();
        static EngineMaterials &getEngineMaterialsClass();
        EngineMaterials() { }
        ~EngineMaterials() { }


};  


#endif 

