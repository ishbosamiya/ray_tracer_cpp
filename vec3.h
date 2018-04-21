#ifndef VEC3_H
#define VEC3_H

#include <math.h>

class Vec3
{
    float m_elements[3];
    public:
        Vec3();
        Vec3(float e0, float e1, float e2);

        float x() { return m_elements[0];}
        float y() { return m_elements[1];}
        float z() { return m_elements[2];}
        float r() { return m_elements[0];}
        float g() { return m_elements[1];}
        float b() { return m_elements[2];}

        float operator[] (int i) {return m_elements[i];}

        Vec3& operator+= (const Vec3 &v3);
        Vec3& operator-= (const Vec3 &v3);
        Vec3& operator*= (const Vec3 &v3);
        Vec3& operator/= (const Vec3 &v3);
        Vec3& operator*= (const float scalar);
        Vec3& operator/= (const float scalar);

        float length();
        float squaredLength();
        Vec3 normalized();

        Vec3 operator+ (const Vec3 &v3_1);
        Vec3 operator- (const Vec3 &v3_1);
        Vec3 operator* (const Vec3 &v3_1);
        Vec3 operator/ (const Vec3 &v3_1);
        Vec3 operator* (const float scalar);
        Vec3 operator/ (const float scalar);

        float dot(const Vec3 &v3_1, const Vec3 &v3_2);
        float dot(const Vec3 &v3_1);
        Vec3 cross(const Vec3 &v3_1, const Vec3 &v3_2);
        Vec3 cross(const Vec3 &v3_1);

        virtual ~Vec3();
};

#endif // VEC3_H
