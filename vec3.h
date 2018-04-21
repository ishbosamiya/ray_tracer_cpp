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

        inline Vec3& operator+= (const Vec3 &v3);
        inline Vec3& operator-= (const Vec3 &v3);
        inline Vec3& operator*= (const Vec3 &v3);
        inline Vec3& operator/= (const Vec3 &v3);
        inline Vec3& operator*= (const float scalar);
        inline Vec3& operator/= (const float scalar);

        inline float length();
        inline float squaredLength();
        inline Vec3 normalized();

        inline Vec3 operator+ (const Vec3 &v3_1);
        inline Vec3 operator- (const Vec3 &v3_1);
        inline Vec3 operator* (const Vec3 &v3_1);
        inline Vec3 operator/ (const Vec3 &v3_1);
        inline Vec3 operator* (const float scalar);
        inline Vec3 operator/ (const float scalar);

        inline float dot(const Vec3 &v3_1, const Vec3 &v3_2);
        inline float dot(const Vec3 &v3_1);
        inline Vec3 cross(const Vec3 &v3_1, const Vec3 &v3_2);
        inline Vec3 cross(const Vec3 &v3_1);

        virtual ~Vec3();
};

#endif // VEC3_H
