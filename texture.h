#ifndef TEXTURE_H
#define TEXTURE_H

#include <math.h>

#include "vec3.h"
#include "hitable.h"
#include "material_functions.h"

class Texture
{
    public:
        virtual Vec3 value(Vec3 uv, Vec3 &point) const = 0;
};

class Constant_Texture: public Texture {
    Vec3 color;

    public:
        Constant_Texture() {}
        Constant_Texture(Vec3 color) { this->color = color;}

        virtual Vec3 value(Vec3 uv, Vec3 &point) const {
            return color;
        }
};

class Checker_Texture: public Texture {
    Texture *texture0;
    Texture *texture1;

    public:
        Checker_Texture() {}
        Checker_Texture(Texture *texture0, Texture *texture1) {
            this->texture0 = texture0;
            this->texture1 = texture1;
        }

        virtual Vec3 value(Vec3 uv, Vec3 &point) const {
            float sines = sin(10.0*point.x())*sin(10.0*point.y())*sin(10.0*point.z());
            if(sines < 0) {
                return texture1->value(uv, point);
            }
            else {
                return texture0->value(uv, point);
            }
        }
};

#endif // TEXTURE_H
