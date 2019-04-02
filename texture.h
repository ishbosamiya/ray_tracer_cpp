#ifndef TEXTURE_H
#define TEXTURE_H

#include <math.h>

#include "vec3.h"
#include "hitable.h"
#include "material_functions.h"
#include "perlin.h"

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
    float grid_size;

    public:
        Checker_Texture() {}
        Checker_Texture(Texture *texture0, Texture *texture1, float grid_size = 10.0) {
            this->texture0 = texture0;
            this->texture1 = texture1;
            this->grid_size = grid_size;
        }

        virtual Vec3 value(Vec3 uv, Hit_Record &record) const {
            float sines = sin(grid_size*record.point.x())*sin(grid_size*record.point.y())*sin(grid_size*record.point.z());
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
            float data = fresnelDielectric(refractive_index, record);
            return Vec3(data, data, data);
        }
};

class Noise_Texture: public Texture {
    Perlin noise;
    float scale;
    public:
        Noise_Texture(float scale) { this->scale = scale;}
        virtual Vec3 value(Vec3 uv, Hit_Record &record) const {
            //return Vec3(1.0, 1.0, 1.0)*noise.noise(record.point * scale);
            //return Vec3(1.0, 1.0, 1.0) * 0.5 * (1.0 + noise.turbulence(record.point * scale));
            return Vec3(1.0, 1.0, 1.0) * 0.5 * (1.0 + sin(scale * record.point.z() + 10.0*noise.turbulence(record.point)));
        }
};

#endif // TEXTURE_H
