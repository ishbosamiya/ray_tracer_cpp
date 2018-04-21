#include "vec3.h"

Vec3::Vec3() {
    m_elements[0] = 0;
    m_elements[1] = 0;
    m_elements[2] = 0;
}

Vec3::Vec3(float e0, float e1, float e2) {
    m_elements[0] = e0;
    m_elements[1] = e1;
    m_elements[2] = e2;
}

Vec3& Vec3::operator+= (const Vec3 &v3) {
    m_elements[0] += v3.m_elements[0];
    m_elements[1] += v3.m_elements[1];
    m_elements[2] += v3.m_elements[2];
    return *this;
}

Vec3& Vec3::operator-= (const Vec3 &v3) {
    m_elements[0] -= v3.m_elements[0];
    m_elements[1] -= v3.m_elements[1];
    m_elements[2] -= v3.m_elements[2];
    return *this;
}

Vec3& Vec3::operator*= (const Vec3 &v3) {
    m_elements[0] *= v3.m_elements[0];
    m_elements[1] *= v3.m_elements[1];
    m_elements[2] *= v3.m_elements[2];
    return *this;
}

Vec3& Vec3::operator/= (const Vec3 &v3) {
    m_elements[0] /= v3.m_elements[0];
    m_elements[1] /= v3.m_elements[1];
    m_elements[2] /= v3.m_elements[2];
    return *this;
}

Vec3& Vec3::operator*= (const float scalar) {
    m_elements[0] *= scalar;
    m_elements[1] *= scalar;
    m_elements[2] *= scalar;
    return *this;
}

Vec3& Vec3::operator/= (const float scalar) {
    m_elements[0] /= scalar;
    m_elements[1] /= scalar;
    m_elements[2] /= scalar;
    return *this;
}


float Vec3::length() {
    return sqrt(m_elements[0]*m_elements[0] + m_elements[1]*m_elements[1] + m_elements[2]*m_elements[2]);
}

float Vec3::squaredLength() {
    return (m_elements[0]*m_elements[0] + m_elements[1]*m_elements[1] + m_elements[2]*m_elements[2]);
}

Vec3 Vec3::normalized() {
    float one_over_l = 1.0/length();
    return Vec3(m_elements[0]*one_over_l, m_elements[1]*one_over_l, m_elements[2]*one_over_l);
}


Vec3 Vec3::operator+ (const Vec3 &v3_1) {
    return Vec3(m_elements[0] + v3_1.m_elements[0]
                ,m_elements[1] + v3_1.m_elements[1]
                ,m_elements[2] + v3_1.m_elements[2]);
}

Vec3 Vec3::operator- (const Vec3 &v3_1) {
    return Vec3(m_elements[0] - v3_1.m_elements[0]
                ,m_elements[1] - v3_1.m_elements[1]
                ,m_elements[2] - v3_1.m_elements[2]);
}

Vec3 Vec3::operator* (const Vec3 &v3_1) {
    return Vec3(m_elements[0] * v3_1.m_elements[0]
                ,m_elements[1] * v3_1.m_elements[1]
                ,m_elements[2] * v3_1.m_elements[2]);
}

Vec3 Vec3::operator/ (const Vec3 &v3_1) {
    return Vec3(m_elements[0] / v3_1.m_elements[0]
                ,m_elements[1] / v3_1.m_elements[1]
                ,m_elements[2] / v3_1.m_elements[2]);
}

Vec3 Vec3::operator* (const float scalar) {
    return Vec3(m_elements[0] * scalar
                ,m_elements[1] * scalar
                ,m_elements[2] * scalar);
}

Vec3 Vec3::operator/ (const float scalar) {
    return Vec3(m_elements[0] / scalar
                ,m_elements[1] / scalar
                ,m_elements[2] / scalar);
}


float Vec3::dot(const Vec3 &v3_1, const Vec3 &v3_2) {
    return (v3_1.m_elements[0] * v3_2.m_elements[0]
            + v3_1.m_elements[1] * v3_2.m_elements[1]
            + v3_1.m_elements[2] * v3_2.m_elements[2]);
}

float Vec3::dot(const Vec3 &v3_1) {
    return dot(*this, v3_1);
}

Vec3 Vec3::cross(const Vec3 &v3_1, const Vec3 &v3_2) {
    return Vec3((v3_1.m_elements[1]*v3_2.m_elements[2])-(v3_1.m_elements[2]*v3_2.m_elements[1])
                ,(v3_1.m_elements[2]*v3_2.m_elements[0])-(v3_1.m_elements[0]*v3_2.m_elements[2])
                ,(v3_1.m_elements[0]*v3_2.m_elements[1])-(v3_1.m_elements[1]*v3_2.m_elements[0]));
}

Vec3 Vec3::cross(const Vec3 &v3_1) {
    return cross(*this, v3_1);
}

Vec3::~Vec3()
{
    //dtor
}
