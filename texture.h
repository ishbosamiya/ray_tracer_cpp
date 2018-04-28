#ifndef TEXTURE_H
#define TEXTURE_H

#include <math.h>

#include "vec3.h"
#include "hitable.h"
#include "material_functions.h"

class Texture
{
    public:
        virtual Vec3 value(Vec3 uv, Hit_Record &record) const = 0;
};

class Constant_Texture: public Texture {
    Vec3 color;

    public:
        Constant_Texture() {}
        Constant_Texture(Vec3 color) { this->color = color;}

        virtual Vec3 value(Vec3 uv, Hit_Record &record) const {
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

        virtual Vec3 value(Vec3 uv, Hit_Record &record) const {
            float sines = sin(10.0*record.point.x())*sin(10.0*record.point.y())*sin(10.0*record.point.z());
            if(sines < 0) {
                return texture1->value(uv, record);
            }
            else {
                return texture0->value(uv, record);
            }
        }
};

class Fresnel_Texture: public Texture {
    float refractive_index;
    public:
        Fresnel_Texture(float refractive_index) {
            this->refractive_index = refractive_index;
        }

        virtual Vec3 value(Vec3 uv, Hit_Record &record) const {
            float cosine = -record.ray.directionVector().normalized().dot(record.normal);
            float data = schlick(cosine, refractive_index);
            return Vec3(data, data, data);
        }
};

#endif // TEXTURE_H
