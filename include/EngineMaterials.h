#ifndef ENGINE_MATERIALS_H
#define ENGINE_MATERIALS_H

#include "ShaderMaterialInterface.h"
#include "CustomList.h"
class EngineMaterials
{
    private: 
      ColorMaterial _colorMaterial;
      LightMaterial _lightMaterial;
    public:
        ShaderMaterialInterface *getLightMaterial();
        ShaderMaterialInterface *getColorMaterial();
        void initEngineMaterials();
        static EngineMaterials &getEngineMaterialsClass();
        EngineMaterials() { }
        ~EngineMaterials() { }


};  


#endif 

