/*
 *  Material.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/3/09.
 *
 */

#ifndef NHZ_MATERIAL_H
#define NHZ_MATERIAL_H

class Material {
    public:
        void setAmbientMaterial(const float (& material)[4]);
        void setDiffuseMaterial(const float (& material)[4]);
        void setSpecularMaterial(const float (& material)[4]);
        void setShininess(const float shininess);
    protected:
        void initialize();
        void useMaterial(); // use in child classes when rendering materials
    private:
        float _ambient[4], _diffuse[4], _specular[4];
        float _shininess;
};

#endif
