#ifndef VEC3_H
#define VEC3_H

#include <math.h>

class Vec3
{
    float m_elements[3];
    public:
        Vec3();
        Vec3(float e0, float e1, float e2);

        float x() const { return m_elements[0];}
        float y() const { return m_elements[1];}
        float z() const { return m_elements[2];}
        float r() const { return m_elements[0];}
        float g() const { return m_elements[1];}
        float b() const { return m_elements[2];}

        float operator[] (int i) const {return m_elements[i];}
        float& operator[](int i) { return m_elements[i]; }

        Vec3& operator+= (const Vec3 &v3);
        Vec3& operator-= (const Vec3 &v3);
        Vec3& operator*= (const Vec3 &v3);
        Vec3& operator/= (const Vec3 &v3);
        Vec3& operator*= (const float scalar);
        Vec3& operator/= (const float scalar);

        float length() const;
        float squaredLength() const;
        Vec3 normalized() const;

        Vec3 operator+ (const Vec3 &v3_1) const;
        Vec3 operator- (const Vec3 &v3_1) const;
        Vec3 operator* (const Vec3 &v3_1) const;
        Vec3 operator/ (const Vec3 &v3_1) const;
        Vec3 operator* (const float scalar) const;
        Vec3 operator/ (const float scalar) const;

        float dot(const Vec3 &v3_1, const Vec3 &v3_2) const;
        float dot(const Vec3 &v3_1) const;
        Vec3 cross(const Vec3 &v3_1, const Vec3 &v3_2) const;
        Vec3 cross(const Vec3 &v3_1) const;

        virtual ~Vec3();
};

#endif // VEC3_H
