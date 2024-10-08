#ifndef ENGINE_MATERIALS_H
#define ENGINE_MATERIALS_H

#include "ShaderMaterialInterface.h"
#include "CustomList.h"
//once made these materials should be cloned to each vertexbuffer object
class EngineMaterials
{
    private: 
      ColorMaterial _colorMaterial;
      LitMaterial *_lightMaterial;
      LightObjectMaterial _lightObjectMaterial;
      GameFontMaterial *_gameFontMaterial;
      ParticleFX3DMaterial *_particleFX3DMaterial;
      ImageMaterial *_imageMaterial;
    public:
        Material *getLightMaterial();
        ImageMaterial *getImageMaterial();
        ShaderMaterialInterface *getColorMaterial();
        ShaderMaterialInterface *getLightObjectMaterial();
        GameFontMaterial *getGameFontMaterial();
        ParticleFX3DMaterial *getGet3DParticleFXMaterial();
        
        void initEngineMaterials();
        static EngineMaterials &getEngineMaterialsClass();
        EngineMaterials() { }
        ~EngineMaterials() { }


};  


#endif 

