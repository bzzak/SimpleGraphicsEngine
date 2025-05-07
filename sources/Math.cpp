#include "../headers/Math.h"

#define M_PI 3.14159265358979323846
#include <cmath>
#include <iostream>
#include <string.h>
#include <valarray>
#include <algorithm>

namespace Math {
    // INTEGER3

    std::ostream &operator<<(std::ostream &os, const Integer3 &v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }


    // POINT

    std::ostream &operator<<(std::ostream &os, const Point &p) {
        os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
        return os;
    }

    // FLOAT2

    float2::float2() : x(0), y(0) {
    }

    float2::float2(float _x, float _y) : x(_x), y(_y) {
    }

    void float2::operator+=(const float2 &v) {
        this->x += v.x;
        this->y += v.y;
    }

    void float2::operator-=(const float2 &v) {
        this->x -= v.x;
        this->y -= v.y;
    }

    float2 float2::operator+(const float2 &v) const {
        return {this->x + v.x, this->y + v.y};
    }

    float2 float2::operator-(const float2 &v) const {
        return {this->x - v.x, this->y - v.y};
    }

    void float2::operator*=(float o) {
        this->x *= o;
        this->y *= o;
    }

    void float2::operator/=(float o) {
        if (o == 0) throw std::invalid_argument("Divide by 0");

        this->x /= o;
        this->y /= o;
    }

    float2 float2::operator*(float o) const {
        return {this->x * o, this->y * o};
    }

    float2 operator*(float o, const float2 &v) {
        return {o * v.x, o * v.y};
    }

    float2 operator/(float o, const float2 &v) {
        if (v.x == 0 || v.y == 0) throw std::invalid_argument("Divide by 0");

        return {o / v.x, o / v.y};
    }

    float2 float2::operator/(float o) const {
        if (o == 0) throw std::invalid_argument("Divide by 0");

        return {this->x / o, this->y / o};
    }

    float float2::len() const {
        return static_cast<float>(std::sqrt(pow(this->x, 2) + pow(this->y, 2)));
    }

    void float2::normalize() {
        float n = this->len();
        if (n != 0) {
            this->x /= n;
            this->y /= n;
        } else throw std::invalid_argument("Divide by 0");
    }

    float2 float2::getNormalized() const {
        float n = this->len();
        float2 result;
        if (n != 0) {
            result = {
                this->x / n,
                this->y / n
            };
        } else throw std::invalid_argument("Divide by 0");

        return result;
    }

    float float2::dot(const float2 &v) const {
        float2 result;
        result.x = this->x * v.x;
        result.y = this->y * v.y;

        return result.x + result.y;
    }

    float float2::getAngle(const float2 &v) const {
        if (this->len() == 0 || v.len() == 0) return 0;
        return static_cast<float>(acos(this->dot(v) / (this->len() * v.len())) * (180.0 / 3.141592653589793238463));
    }

    std::ostream &operator<<(std::ostream &os, const float2 &v) {
        os << "[" << v.x << ", " << v.y << "]";
        return os;
    }

    // FLOAT3

    float3::float3() : x(0), y(0), z(0) {
    }

    float3::float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {
    }

    void float3::operator+=(const float3 &v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
    }

    void float3::operator-=(const float3 &v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
    }

    float3 float3::operator+(const float3 &v) const {
        return {this->x + v.x, this->y + v.y, this->z + v.z};
    }

    float3 float3::operator-(const float3 &v) const {
        return {this->x - v.x, this->y - v.y, this->z - v.z};
    }

    void float3::operator*=(float o) {
        this->x *= o;
        this->y *= o;
        this->z *= o;
    }

    void float3::operator/=(float o) {
        if (o == 0) throw std::invalid_argument("Divide by 0");

        this->x /= o;
        this->y /= o;
        this->z /= o;
    }

    float3 float3::operator*(float o) const {
        return {this->x * o, this->y * o, this->z * o};
    }

    float3 operator*(float o, const float3 &v) {
        return {o * v.x, o * v.y, o * v.z};
    }

    float3 float3::operator/(float o) const {
        if (o == 0) throw std::invalid_argument("Divide by 0");

        return {this->x / o, this->y / o, this->z / o};
    }

    float3 operator/(float o, const float3 &v) {
        if (v.x == 0 || v.y == 0) throw std::invalid_argument("Divide by 0");

        return {o / v.x, o / v.y, o / v.z};
    }

    float float3::len() const {
        return static_cast<float>(std::sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
    }

    void float3::normalize() {
        float n = this->len();
        if (n != 0) {
            this->x /= n;
            this->y /= n;
            this->z /= n;
        } else throw std::invalid_argument("Divide by 0");
    }

    float3 float3::getNormalized() const {
        float n = this->len();
        float3 result;
        if (n != 0) {
            result = {
                this->x / n,
                this->y / n,
                this->z / n
            };
        } else throw std::invalid_argument("Divide by 0");

        return result;
    }

    float float3::dot(const float3 &v) const {
        float3 result;
        result.x = this->x * v.x;
        result.y = this->y * v.y;
        result.z = this->z * v.z;

        return result.x + result.y + result.z;
    }

    float3 float3::cross(const float3 &v) const {
        return {
            this->y * v.z - this->z * v.y,
            this->z * v.x - this->x * v.z,
            this->x * v.y - this->y * v.x
        };
    }

    float float3::getAngle(const float3 &v) const {
        if (this->len() == 0 || v.len() == 0) return 0;
        return static_cast<float>(acos(this->dot(v) / (this->len() * v.len())) * (180.0 / 3.141592653589793238463));
    }

    std::ostream &operator<<(std::ostream &os, const float3 &v) {
        os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
        return os;
    }

    // FLOAT4

    float4::float4() : x(0), y(0), z(0), w(0) {
    }

    float4::float4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {
    }

    void float4::operator+=(const float4 &v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        this->w += v.w;
    }

    void float4::operator-=(const float4 &v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        this->w -= v.w;
    }

    float4 float4::operator+(const float4 &v) const {
        return {this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w};
    }

    float4 float4::operator-(const float4 &v) const {
        return {this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w};
    }

    void float4::operator*=(float o) {
        this->x *= o;
        this->y *= o;
        this->z *= o;
        this->w *= o;
    }

    void float4::operator/=(float o) {
        if (o == 0) throw std::invalid_argument("Divide by 0");

        this->x /= o;
        this->y /= o;
        this->z /= o;
        this->w /= o;
    }

    float4 float4::operator*(float o) const {
        return {this->x * o, this->y * o, this->z * o, this->w * o};
    }

    float4 operator*(float o, const float4 &v) {
        return {o * v.x, o * v.y, o * v.z, o * v.w};
    }

    float4 float4::operator/(float o) const {
        if (o == 0) throw std::invalid_argument("Divide by 0");

        return {this->x / o, this->y / o, this->z / o, this->w / o};
    }

    float4 operator/(float o, const float4 &v) {
        if (v.x == 0 || v.y == 0) throw std::invalid_argument("Divide by 0");

        return {o / v.x, o / v.y, o / v.z, o / v.w};
    }

    float float4::len() const {
        return static_cast<float>(std::sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2)));
    }

    void float4::normalize() {
        float n = this->len();
        if (n != 0) {
            this->x /= n;
            this->y /= n;
            this->z /= n;
            this->w /= n;
        } else throw std::invalid_argument("Divide by 0");
    }

    float4 float4::getNormalized() const {
        float n = this->len();
        float4 result;
        if (n != 0) {
            result = {
                this->x / n,
                this->y / n,
                this->z / n,
                this->w / n
            };
        } else throw std::invalid_argument("Divide by 0");

        return result;
    }


    float float4::dot(const float4 &v) const {
        float4 result;
        result.x = this->x * v.x;
        result.y = this->y * v.y;
        result.z = this->z * v.z;
        result.w = this->w * v.w;

        return result.x + result.y + result.z + result.w;
    }

    std::ostream &operator<<(std::ostream &os, const float4 &v) {
        os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
        return os;
    }

    // FLOAT 3x3

    float3x3::float3x3(float3 vec1, float3 vec2, float3 vec3) {
        this->m[0] = vec1.x;
        this->m[1] = vec1.y;
        this->m[2] = vec1.z;
        this->m[3] = vec2.x;
        this->m[4] = vec2.y;
        this->m[5] = vec2.z;
        this->m[6] = vec3.x;
        this->m[7] = vec3.y;
        this->m[8] = vec3.z;
    }

    float3x3::float3x3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8) {
        this->m[0] = m0;
        this->m[1] = m1;
        this->m[2] = m2;
        this->m[3] = m3;
        this->m[4] = m4;
        this->m[5] = m5;
        this->m[6] = m6;
        this->m[7] = m7;
        this->m[8] = m8;
    }

    float3x3::float3x3(const float *f) {
        memcpy(this->m, f, sizeof(float) * 9);
    }

    float3x3::float3x3(const float3x3 &mat) {
        memcpy(this->m, mat.m, sizeof(float) * 9);
    }

    void float3x3::operator+=(const float3x3 &mat) {
        this->m[0] += mat.m[0];
        this->m[1] += mat.m[1];
        this->m[2] += mat.m[2];
        this->m[3] += mat.m[3];
        this->m[4] += mat.m[4];
        this->m[5] += mat.m[5];
        this->m[6] += mat.m[6];
        this->m[7] += mat.m[7];
        this->m[8] += mat.m[8];
    }

    void float3x3::operator-=(const float3x3 &mat) {
        this->m[0] -= mat.m[0];
        this->m[1] -= mat.m[1];
        this->m[2] -= mat.m[2];
        this->m[3] -= mat.m[3];
        this->m[4] -= mat.m[4];
        this->m[5] -= mat.m[5];
        this->m[6] -= mat.m[6];
        this->m[7] -= mat.m[7];
        this->m[8] -= mat.m[8];
    }

    float3x3 float3x3::operator+(const float3x3 &mat) const {
        return {
            this->m[0] + mat.m[0],
            this->m[1] + mat.m[1],
            this->m[2] + mat.m[2],
            this->m[3] + mat.m[3],
            this->m[4] + mat.m[4],
            this->m[5] + mat.m[5],
            this->m[6] + mat.m[6],
            this->m[7] + mat.m[7],
            this->m[8] + mat.m[8]
        };
    }

    float3x3 float3x3::operator-(const float3x3 &mat) const {
        return {
            this->m[0] - mat.m[0],
            this->m[1] - mat.m[1],
            this->m[2] - mat.m[2],
            this->m[3] - mat.m[3],
            this->m[4] - mat.m[4],
            this->m[5] - mat.m[5],
            this->m[6] - mat.m[6],
            this->m[7] - mat.m[7],
            this->m[8] - mat.m[8]
        };

    }

    void float3x3::operator*=(float o) {
        this->m[0] *= o;
        this->m[1] *= o;
        this->m[2] *= o;
        this->m[3] *= o;
        this->m[4] *= o;
        this->m[5] *= o;
        this->m[6] *= o;
        this->m[7] *= o;
        this->m[8] *= o;
    }

    void float3x3::operator/=(float o) {
        if (o != 0) {
            this->m[0] /= o;
            this->m[1] /= o;
            this->m[2] /= o;
            this->m[3] /= o;
            this->m[4] /= o;
            this->m[5] /= o;
            this->m[6] /= o;
            this->m[7] /= o;
            this->m[8] /= o;
        } else throw std::invalid_argument("Divide by 0");
    }

    float3x3 float3x3::operator*(float o) const {
        return {
            this->m[0] * o,
            this->m[1] * o,
            this->m[2] * o,
            this->m[3] * o,
            this->m[4] * o,
            this->m[5] * o,
            this->m[6] * o,
            this->m[7] * o,
            this->m[8] * o
        };
    }

    float3x3 operator*(float o, const float3x3 &mat) {
        return {
            o * mat.m[0],
            o * mat.m[1],
            o * mat.m[2],
            o * mat.m[3],
            o * mat.m[4],
            o * mat.m[5],
            o * mat.m[6],
            o * mat.m[7],
            o * mat.m[8]
        };
    }

    float3x3 float3x3::operator/(float o) const {
        if (o == 0) throw std::invalid_argument("Divide by 0");

        return {
            this->m[0] / o,
            this->m[1] / o,
            this->m[2] / o,
            this->m[3] / o,
            this->m[4] / o,
            this->m[5] / o,
            this->m[6] / o,
            this->m[7] / o,
            this->m[8] / o
        };
    }

    float3 float3x3::operator*(const float3 &v) const {
        return {
            this->m[0] * v.x + this->m[3] * v.y + this->m[6] * v.z,
            this->m[1] * v.x + this->m[4] * v.y + this->m[7] * v.z,
            this->m[2] * v.x + this->m[5] * v.y + this->m[8] * v.z
            };
    }

    float3 operator*(const float3 &v, const float3x3 &mat) {
        return {
            v.x * mat.m[0] + v.y * mat.m[1] + v.z * mat.m[2],
            v.x * mat.m[3] + v.y * mat.m[4] + v.z * mat.m[5],
            v.x * mat.m[6] + v.y * mat.m[7] + v.z * mat.m[8]
            };
    }

    void float3x3::operator*=(const float3x3 &mat) {
        float3x3 tempMat = {
            this->m[0] * mat.m[0] + this->m[3] * mat.m[1] + this->m[6] * mat.m[2],
            this->m[1] * mat.m[0] + this->m[4] * mat.m[1] + this->m[7] * mat.m[2],
            this->m[2] * mat.m[0] + this->m[5] * mat.m[1] + this->m[8] * mat.m[2],
            this->m[0] * mat.m[3] + this->m[3] * mat.m[4] + this->m[6] * mat.m[5],
            this->m[1] * mat.m[3] + this->m[4] * mat.m[4] + this->m[7] * mat.m[5],
            this->m[2] * mat.m[3] + this->m[5] * mat.m[4] + this->m[8] * mat.m[5],
            this->m[0] * mat.m[6] + this->m[3] * mat.m[7] + this->m[6] * mat.m[8],
            this->m[1] * mat.m[6] + this->m[4] * mat.m[7] + this->m[7] * mat.m[8],
            this->m[2] * mat.m[6] + this->m[5] * mat.m[7] + this->m[8] * mat.m[8]
        };

        std::ranges::copy(tempMat.m, std::begin(this->m));
    }

    float3x3 float3x3::operator*(const float3x3 &mat) const {
        return {
            this->m[0] * mat.m[0] + this->m[3] * mat.m[1] + this->m[6] * mat.m[2],
            this->m[1] * mat.m[0] + this->m[4] * mat.m[1] + this->m[7] * mat.m[2],
            this->m[2] * mat.m[0] + this->m[5] * mat.m[1] + this->m[8] * mat.m[2],
            this->m[0] * mat.m[3] + this->m[3] * mat.m[4] + this->m[6] * mat.m[5],
            this->m[1] * mat.m[3] + this->m[4] * mat.m[4] + this->m[7] * mat.m[5],
            this->m[2] * mat.m[3] + this->m[5] * mat.m[4] + this->m[8] * mat.m[5],
            this->m[0] * mat.m[6] + this->m[3] * mat.m[7] + this->m[6] * mat.m[8],
            this->m[1] * mat.m[6] + this->m[4] * mat.m[7] + this->m[7] * mat.m[8],
            this->m[2] * mat.m[6] + this->m[5] * mat.m[7] + this->m[8] * mat.m[8]
            };
    }

    float3 float3x3::operator[](int i) const {
        float3 vector;

        if (i <= 2 && i >= 0) {
            vector.x = this->m[0+i*3];
            vector.y = this->m[1+i*3];
            vector.z = this->m[2+i*3];
        }
        else throw std::out_of_range("Float3x3: out of range");

        return vector;
    }

    void float3x3::loadIdentity() {
        memset(this->m, 0, sizeof(float) * 9);
        this->m[0] = 1.0f;
        this->m[4] = 1.0f;
        this->m[8] = 1.0f;
    }

    float float3x3::det() const {
        float t1 = this->m[0] * this->m[4];
        float t2 = this->m[0] * this->m[7];
        float t3 = this->m[3] * this->m[1];
        float t4 = this->m[6] * this->m[1];
        float t5 = this->m[3] * this->m[2];
        float t6 = this->m[6] * this->m[2];

        return t1 * this->m[8] - t2 * this->m[5] - t3 * this->m[8] + t4 * this->m[5] + t5 * this->m[7] - t6 * this->m[4];
    }

    void float3x3::setMatrixAsInverseOfGivenMatrix(const float3x3 &mat) {
        float t1 = this->m[0] * this->m[4];
        float t2 = this->m[0] * this->m[7];
        float t3 = this->m[3] * this->m[1];
        float t4 = this->m[6] * this->m[1];
        float t5 = this->m[3] * this->m[2];
        float t6 = this->m[6] * this->m[2];

        float det = mat.det();
        if (det == 0) return;

        float invd = 1.0f / det;

        float m0 = (mat.m[4] * mat.m[8] - mat.m[7] * mat.m[5]) * invd;
        float m3 = -(mat.m[3] * mat.m[8] - mat.m[6] * mat.m[5]) * invd;
        float m6 = (mat.m[3] * mat.m[7] - mat.m[6] * mat.m[4]) * invd;
        float m1 = -(mat.m[1] * mat.m[8] - mat.m[7] * mat.m[2]) * invd;
        float m4 = (mat.m[0] * mat.m[8] - mat.m[6] * mat.m[2]) * invd;
        float m7 = -(mat.m[0] * mat.m[7] - mat.m[6] * mat.m[1]) * invd;
        float m2 = (mat.m[1] * mat.m[5] - mat.m[4] * mat.m[2]) * invd;
        float m5 = -(mat.m[0] * mat.m[5] - mat.m[3] * mat.m[2]) * invd;
        float m8 = (mat.m[0] * mat.m[4] - mat.m[3] * mat.m[1]) * invd;

        this->m[0] = m0;
        this->m[3] = m3;
        this->m[6] = m6;

        this->m[1] = m1;
        this->m[4] = m4;
        this->m[7] = m7;

        this->m[2] = m2;
        this->m[5] = m5;
        this->m[8] = m8;

    }

    float3x3 float3x3::getInverseOfMatrix() const {
        float3x3 result;
        result.setMatrixAsInverseOfGivenMatrix(*this);
        return result;
    }

    void float3x3::invert() {
        auto mat = float3x3(*this);
        setMatrixAsInverseOfGivenMatrix(mat);
    }

    void float3x3::setMatrixAsTransposeOfGivenMatrix(const float3x3 &mat) {
        this->m[0] = mat.m[0];
        this->m[3] = mat.m[1];
        this->m[6] = mat.m[2];

        this->m[1] = mat.m[3];
        this->m[4] = mat.m[4];
        this->m[7] = mat.m[5];

        this->m[2] = mat.m[6];
        this->m[5] = mat.m[7];
        this->m[8] = mat.m[8];
    }

    float3x3 float3x3::getTransposeOfMatrix() const {
        float3x3 result;
        result.setMatrixAsTransposeOfGivenMatrix(*this);
        return result;
    }

    void float3x3::transpose() {
        auto mat = float3x3(*this);
        setMatrixAsTransposeOfGivenMatrix(mat);
    }

    std::ostream & operator<<(std::ostream &os, const float3x3 &mat) {
        for (int i=0; i < 3; i++) {
            for (int j=0; j < 3; j++) {
                if (j == 0) os << " | ";
                os << mat.m[i + j * 3];
                if (j != 2) os << " , ";
                else os << " | " << std::endl;
            }
        }
        return os;
    }

    // FLOAT 4x4

    // Column Proxy constructor
    float4x4::ColumnProxy::ColumnProxy(float* ptr) : col_ptr(ptr) {}

    // Column proxy read access

    float4x4::ColumnProxy::operator float4() const {
        return float4{col_ptr[0], col_ptr[1], col_ptr[2], col_ptr[3]};
    }

    // Column proxy write access

    float4x4::ColumnProxy& float4x4::ColumnProxy::operator=(const float4& vec) {
        col_ptr[0] = vec.x;
        col_ptr[1] = vec.y;
        col_ptr[2] = vec.z;
        col_ptr[3] = vec.w;
        return *this;
    }


    float4x4::float4x4(float4 vector1, float4 vector2, float4 vector3, float4 vector4) {
        this->m[0] = vector1.x;
        this->m[1] = vector1.y;
        this->m[2] = vector1.z;
        this->m[3] = vector1.w;
        this->m[4] = vector2.x;
        this->m[5] = vector2.y;
        this->m[6] = vector2.z;
        this->m[7] = vector2.w;
        this->m[8] = vector3.x;
        this->m[9] = vector3.y;
        this->m[10] = vector3.z;
        this->m[11] = vector3.w;
        this->m[12] = vector4.x;
        this->m[13] = vector4.y;
        this->m[14] = vector4.z;
        this->m[15] = vector4.w;
    }


    float4x4::float4x4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9,
                       float m10, float m11, float m12, float m13, float m14, float m15) {
        this->m[0] = m0;
        this->m[1] = m1;
        this->m[2] = m2;
        this->m[3] = m3;
        this->m[4] = m4;
        this->m[5] = m5;
        this->m[6] = m6;
        this->m[7] = m7;
        this->m[8] = m8;
        this->m[9] = m9;
        this->m[10] = m10;
        this->m[11] = m11;
        this->m[12] = m12;
        this->m[13] = m13;
        this->m[14] = m14;
        this->m[15] = m15;
    }

    float4x4::float4x4(const float *f) {
        memcpy(this->m, f, sizeof(float) * 16);
    }

    float4x4::float4x4(const float4x4 &mat) {
        memcpy(this->m, mat.m, sizeof(float) * 16);
    }

    void float4x4::operator+=(const float4x4 &mat) {
        this->m[0] += mat.m[0];
        this->m[1] += mat.m[1];
        this->m[2] += mat.m[2];
        this->m[3] += mat.m[3];
        this->m[4] += mat.m[4];
        this->m[5] += mat.m[5];
        this->m[6] += mat.m[6];
        this->m[7] += mat.m[7];
        this->m[8] += mat.m[8];
        this->m[9] += mat.m[9];
        this->m[10] += mat.m[10];
        this->m[11] += mat.m[11];
        this->m[12] += mat.m[12];
        this->m[13] += mat.m[13];
        this->m[14] += mat.m[14];
        this->m[15] += mat.m[15];
    }

    void float4x4::operator-=(const float4x4 &mat) {
        this->m[0] -= mat.m[0];
        this->m[1] -= mat.m[1];
        this->m[2] -= mat.m[2];
        this->m[3] -= mat.m[3];
        this->m[4] -= mat.m[4];
        this->m[5] -= mat.m[5];
        this->m[6] -= mat.m[6];
        this->m[7] -= mat.m[7];
        this->m[8] -= mat.m[8];
        this->m[9] -= mat.m[9];
        this->m[10] -= mat.m[10];
        this->m[11] -= mat.m[11];
        this->m[12] -= mat.m[12];
        this->m[13] -= mat.m[13];
        this->m[14] -= mat.m[14];
        this->m[15] -= mat.m[15];
    }

    float4x4 float4x4::operator+(const float4x4 &mat) const {
        return {
            this->m[0] + mat.m[0],
            this->m[1] + mat.m[1],
            this->m[2] + mat.m[2],
            this->m[3] + mat.m[3],
            this->m[4] + mat.m[4],
            this->m[5] + mat.m[5],
            this->m[6] + mat.m[6],
            this->m[7] + mat.m[7],
            this->m[8] + mat.m[8],
            this->m[9] + mat.m[9],
            this->m[10] + mat.m[10],
            this->m[11] + mat.m[11],
            this->m[12] + mat.m[12],
            this->m[13] + mat.m[13],
            this->m[14] + mat.m[14],
            this->m[15] + mat.m[15]
        };
    }

    float4x4 float4x4::operator-(const float4x4 &mat) const {
        return {
            this->m[0] - mat.m[0],
            this->m[1] - mat.m[1],
            this->m[2] - mat.m[2],
            this->m[3] - mat.m[3],
            this->m[4] - mat.m[4],
            this->m[5] - mat.m[5],
            this->m[6] - mat.m[6],
            this->m[7] - mat.m[7],
            this->m[8] - mat.m[8],
            this->m[9] - mat.m[9],
            this->m[10] - mat.m[10],
            this->m[11] - mat.m[11],
            this->m[12] - mat.m[12],
            this->m[13] - mat.m[13],
            this->m[14] - mat.m[14],
            this->m[15] - mat.m[15]
        };
    }

    void float4x4::operator*=(float o) {
        this->m[0] *= o;
        this->m[1] *= o;
        this->m[2] *= o;
        this->m[3] *= o;
        this->m[4] *= o;
        this->m[5] *= o;
        this->m[6] *= o;
        this->m[7] *= o;
        this->m[8] *= o;
        this->m[9] *= o;
        this->m[10] *= o;
        this->m[11] *= o;
        this->m[12] *= o;
        this->m[13] *= o;
        this->m[14] *= o;
        this->m[15] *= o;
    }

    void float4x4::operator/=(float o) {
        if (o != 0) {
            this->m[0] /= o;
            this->m[1] /= o;
            this->m[2] /= o;
            this->m[3] /= o;
            this->m[4] /= o;
            this->m[5] /= o;
            this->m[6] /= o;
            this->m[7] /= o;
            this->m[8] /= o;
            this->m[9] /= o;
            this->m[10] /= o;
            this->m[11] /= o;
            this->m[12] /= o;
            this->m[13] /= o;
            this->m[14] /= o;
            this->m[15] /= o;
        } else throw std::invalid_argument("Divide by 0");
    }

    float4x4 float4x4::operator*(float o) const {
        return {
            this->m[0] * o,
            this->m[1] * o,
            this->m[2] * o,
            this->m[3] * o,
            this->m[4] * o,
            this->m[5] * o,
            this->m[6] * o,
            this->m[7] * o,
            this->m[8] * o,
            this->m[9] * o,
            this->m[10] * o,
            this->m[11] * o,
            this->m[12] * o,
            this->m[13] * o,
            this->m[14] * o,
            this->m[15] * o
        };
    }

    float4x4 operator*(float o, const float4x4 &mat) {
        return {
            o * mat.m[0],
            o * mat.m[1],
            o * mat.m[2],
            o * mat.m[3],
            o * mat.m[4],
            o * mat.m[5],
            o * mat.m[6],
            o * mat.m[7],
            o * mat.m[8],
            o * mat.m[9],
            o * mat.m[10],
            o * mat.m[11],
            o * mat.m[12],
            o * mat.m[13],
            o * mat.m[14],
            o * mat.m[15]
        };
    }

    float4x4 float4x4::operator/(float o) const {
        if (o == 0) throw std::invalid_argument("Divide by 0");

        return {
            this->m[0] / o,
            this->m[1] / o,
            this->m[2] / o,
            this->m[3] / o,
            this->m[4] / o,
            this->m[5] / o,
            this->m[6] / o,
            this->m[7] / o,
            this->m[8] / o,
            this->m[9] / o,
            this->m[10] / o,
            this->m[11] / o,
            this->m[12] / o,
            this->m[13] / o,
            this->m[14] / o,
            this->m[15] / o
        };
    }


    float4 float4x4::operator*(const float4 &v) const {
        if (this->m[3] == 0.0f && this->m[7] == 0.0f && this->m[11] == 0.0f && this->m[15] == 1.0f) {
            return {
                this->m[0] * v.x + this->m[4] * v.y + this->m[8] * v.z + this->m[12] * v.w,
                this->m[1] * v.x + this->m[5] * v.y + this->m[9] * v.z + this->m[13] * v.w,
                this->m[2] * v.x + this->m[6] * v.y + this->m[10] * v.z + this->m[14] * v.w,
                v.w
            };
        } else {
            return {
                this->m[0] * v.x + this->m[4] * v.y + this->m[8] * v.z + this->m[12] * v.w,
                this->m[1] * v.x + this->m[5] * v.y + this->m[9] * v.z + this->m[13] * v.w,
                this->m[2] * v.x + this->m[6] * v.y + this->m[10] * v.z + this->m[14] * v.w,
                this->m[3] * v.x + this->m[7] * v.y + this->m[11] * v.z + this->m[15] * v.w
            };
        }
    }

    float4 operator*(const float4 &v, const float4x4 &mat) {
        if (mat.m[3] == 0.0f && mat.m[7] == 0.0f && mat.m[11] == 0.0f && mat.m[15] == 1.0f) {
            return {
                mat.m[0] * v.x + mat.m[1] * v.y + mat.m[2] * v.z + mat.m[3] * v.w,
                mat.m[4] * v.x + mat.m[5] * v.y + mat.m[6] * v.z + mat.m[7] * v.w,
                mat.m[8] * v.x + mat.m[9] * v.y + mat.m[10] * v.z + mat.m[11] * v.w,
                v.w
            };
        } else {
            return {
                mat.m[0] * v.x + mat.m[1] * v.y + mat.m[2] * v.z + mat.m[3] * v.w,
                mat.m[4] * v.x + mat.m[5] * v.y + mat.m[6] * v.z + mat.m[7] * v.w,
                mat.m[8] * v.x + mat.m[9] * v.y + mat.m[10] * v.z + mat.m[11] * v.w,
                mat.m[12] * v.x + mat.m[13] * v.y + mat.m[14] * v.z + mat.m[15] * v.w
            };
        }
    }


    void float4x4::operator*=(const float4x4 &mat) {
        float4x4 tempMat;

        if (this->m[3] == 0.0f && this->m[7] == 0.0f && this->m[11] == 0.0f && this->m[15] == 1.0f &&
            mat.m[3] == 0.0f && mat.m[7] == 0.0f && mat.m[11] == 0.0f && mat.m[15] == 1.0f) {
            tempMat = {
                this->m[0] * mat.m[0] + this->m[4] * mat.m[1] + this->m[8] * mat.m[2],
                this->m[1] * mat.m[0] + this->m[5] * mat.m[1] + this->m[9] * mat.m[2],
                this->m[2] * mat.m[0] + this->m[6] * mat.m[1] + this->m[10] * mat.m[2],
                0.0f,
                this->m[0] * mat.m[4] + this->m[4] * mat.m[5] + this->m[8] * mat.m[6],
                this->m[1] * mat.m[4] + this->m[5] * mat.m[5] + this->m[9] * mat.m[6],
                this->m[2] * mat.m[4] + this->m[6] * mat.m[5] + this->m[10] * mat.m[6],
                0.0f,
                this->m[0] * mat.m[8] + this->m[4] * mat.m[9] + this->m[8] * mat.m[10],
                this->m[1] * mat.m[8] + this->m[5] * mat.m[9] + this->m[9] * mat.m[10],
                this->m[2] * mat.m[8] + this->m[6] * mat.m[9] + this->m[10] * mat.m[10],
                0.0f,
                this->m[0] * mat.m[12] + this->m[4] * mat.m[13] + this->m[8] * mat.m[14] + this->m[12],
                this->m[1] * mat.m[12] + this->m[5] * mat.m[13] + this->m[9] * mat.m[14] + this->m[13],
                this->m[2] * mat.m[12] + this->m[6] * mat.m[13] + this->m[10] * mat.m[14] + this->m[14],
                1.0f
            };
            } else {
                tempMat = {
                    this->m[0] * mat.m[0] + this->m[4] * mat.m[1] + this->m[8] * mat.m[2] + this->m[12] * mat.m[3],
                    this->m[1] * mat.m[0] + this->m[5] * mat.m[1] + this->m[9] * mat.m[2] + this->m[13] * mat.m[3],
                    this->m[2] * mat.m[0] + this->m[6] * mat.m[1] + this->m[10] * mat.m[2] + this->m[14] * mat.m[3],
                    this->m[3] * mat.m[0] + this->m[7] * mat.m[1] + this->m[11] * mat.m[2] + this->m[15] * mat.m[3],
                    this->m[0] * mat.m[4] + this->m[4] * mat.m[5] + this->m[8] * mat.m[6] + this->m[12] * mat.m[7],
                    this->m[1] * mat.m[4] + this->m[5] * mat.m[5] + this->m[9] * mat.m[6] + this->m[13] * mat.m[7],
                    this->m[2] * mat.m[4] + this->m[6] * mat.m[5] + this->m[10] * mat.m[6] + this->m[14] * mat.m[7],
                    this->m[3] * mat.m[4] + this->m[7] * mat.m[5] + this->m[11] * mat.m[6] + this->m[15] * mat.m[7],
                    this->m[0] * mat.m[8] + this->m[4] * mat.m[9] + this->m[8] * mat.m[10] + this->m[12] * mat.m[11],
                    this->m[1] * mat.m[8] + this->m[5] * mat.m[9] + this->m[9] * mat.m[10] + this->m[13] * mat.m[11],
                    this->m[2] * mat.m[8] + this->m[6] * mat.m[9] + this->m[10] * mat.m[10] + this->m[14] * mat.m[11],
                    this->m[3] * mat.m[8] + this->m[7] * mat.m[9] + this->m[11] * mat.m[10] + this->m[15] * mat.m[11],
                    this->m[0] * mat.m[12] + this->m[4] * mat.m[13] + this->m[8] * mat.m[14] + this->m[12] * mat.m[15],
                    this->m[1] * mat.m[12] + this->m[5] * mat.m[13] + this->m[9] * mat.m[14] + this->m[13] * mat.m[15],
                    this->m[2] * mat.m[12] + this->m[6] * mat.m[13] + this->m[10] * mat.m[14] + this->m[14] * mat.m[15],
                    this->m[3] * mat.m[12] + this->m[7] * mat.m[13] + this->m[11] * mat.m[14] + this->m[15] * mat.m[15]
                };
            }

        std::ranges::copy(tempMat.m, std::begin(this->m));
    }

    float4x4 float4x4::operator*(const float4x4 &mat) const {
        if (this->m[3] == 0.0f && this->m[7] == 0.0f && this->m[11] == 0.0f && this->m[15] == 1.0f &&
            mat.m[3] == 0.0f && mat.m[7] == 0.0f && mat.m[11] == 0.0f && mat.m[15] == 1.0f) {
            return {
                this->m[0] * mat.m[0] + this->m[4] * mat.m[1] + this->m[8] * mat.m[2],
                this->m[1] * mat.m[0] + this->m[5] * mat.m[1] + this->m[9] * mat.m[2],
                this->m[2] * mat.m[0] + this->m[6] * mat.m[1] + this->m[10] * mat.m[2],
                0.0f,
                this->m[0] * mat.m[4] + this->m[4] * mat.m[5] + this->m[8] * mat.m[6],
                this->m[1] * mat.m[4] + this->m[5] * mat.m[5] + this->m[9] * mat.m[6],
                this->m[2] * mat.m[4] + this->m[6] * mat.m[5] + this->m[10] * mat.m[6],
                0.0f,
                this->m[0] * mat.m[8] + this->m[4] * mat.m[9] + this->m[8] * mat.m[10],
                this->m[1] * mat.m[8] + this->m[5] * mat.m[9] + this->m[9] * mat.m[10],
                this->m[2] * mat.m[8] + this->m[6] * mat.m[9] + this->m[10] * mat.m[10],
                0.0f,
                this->m[0] * mat.m[12] + this->m[4] * mat.m[13] + this->m[8] * mat.m[14] + this->m[12],
                this->m[1] * mat.m[12] + this->m[5] * mat.m[13] + this->m[9] * mat.m[14] + this->m[13],
                this->m[2] * mat.m[12] + this->m[6] * mat.m[13] + this->m[10] * mat.m[14] + this->m[14],
                1.0f
            };
            } else
                return {
                    this->m[0] * mat.m[0] + this->m[4] * mat.m[1] + this->m[8] * mat.m[2] + this->m[12] * mat.m[3],
                    this->m[1] * mat.m[0] + this->m[5] * mat.m[1] + this->m[9] * mat.m[2] + this->m[13] * mat.m[3],
                    this->m[2] * mat.m[0] + this->m[6] * mat.m[1] + this->m[10] * mat.m[2] + this->m[14] * mat.m[3],
                    this->m[3] * mat.m[0] + this->m[7] * mat.m[1] + this->m[11] * mat.m[2] + this->m[15] * mat.m[3],
                    this->m[0] * mat.m[4] + this->m[4] * mat.m[5] + this->m[8] * mat.m[6] + this->m[12] * mat.m[7],
                    this->m[1] * mat.m[4] + this->m[5] * mat.m[5] + this->m[9] * mat.m[6] + this->m[13] * mat.m[7],
                    this->m[2] * mat.m[4] + this->m[6] * mat.m[5] + this->m[10] * mat.m[6] + this->m[14] * mat.m[7],
                    this->m[3] * mat.m[4] + this->m[7] * mat.m[5] + this->m[11] * mat.m[6] + this->m[15] * mat.m[7],
                    this->m[0] * mat.m[8] + this->m[4] * mat.m[9] + this->m[8] * mat.m[10] + this->m[12] * mat.m[11],
                    this->m[1] * mat.m[8] + this->m[5] * mat.m[9] + this->m[9] * mat.m[10] + this->m[13] * mat.m[11],
                    this->m[2] * mat.m[8] + this->m[6] * mat.m[9] + this->m[10] * mat.m[10] + this->m[14] * mat.m[11],
                    this->m[3] * mat.m[8] + this->m[7] * mat.m[9] + this->m[11] * mat.m[10] + this->m[15] * mat.m[11],
                    this->m[0] * mat.m[12] + this->m[4] * mat.m[13] + this->m[8] * mat.m[14] + this->m[12] * mat.m[15],
                    this->m[1] * mat.m[12] + this->m[5] * mat.m[13] + this->m[9] * mat.m[14] + this->m[13] * mat.m[15],
                    this->m[2] * mat.m[12] + this->m[6] * mat.m[13] + this->m[10] * mat.m[14] + this->m[14] * mat.m[15],
                    this->m[3] * mat.m[12] + this->m[7] * mat.m[13] + this->m[11] * mat.m[14] + this->m[15] * mat.m[15],
                };
    }

    // Access column i as a proxy
    float4x4::ColumnProxy float4x4::operator[](int i) {
        return {&m[i * 4]};
    }

    // Optional const version for read-only access
    float4 float4x4::operator[](int i) const {
        float4 vector;

        if (i <= 3 && i >= 0) {
            vector.x = this->m[0+i*4];
            vector.y = this->m[1+i*4];
            vector.z = this->m[2+i*4];
            vector.w = this->m[3+i*4];
        }
        else throw std::out_of_range("Float4x4: out of range");

        return vector;
    }

    void float4x4::loadIdentity() {
        memset(this->m, 0, sizeof(float) * 16);
        this->m[0] = 1.0f;
        this->m[5] = 1.0f;
        this->m[10] = 1.0f;
        this->m[15] = 1.0f;
    }

    float float4x4::det() const {
        // Laplace
        if (this->m[3] == 0.0f && this->m[7] == 0.0f && this->m[11] == 0.0f && this->m[15] == 1.0f) {
            float t1 = this->m[0] * this->m[5]  * this->m[10];
            float t2 = this->m[1] * this->m[6] * this->m[8];
            float t3 = this->m[2] * this->m[4] * this->m[9];
            float t4 = this->m[2] * this->m[5] * this->m[8];
            float t5 = this->m[0] * this->m[6] * this->m[9];
            float t6 = this->m[1] * this->m[4] * this->m[10];

            return t1 + t2 + t3 - t4 - t5 - t6;
        } else {
            float t1 = this->m[0] * this->m[5] * this->m[10]  * this->m[15];
            float t2 = this->m[0] * this->m[6] * this->m[11] * this->m[13];
            float t3 = this->m[0] * this->m[7] * this->m[9] * this->m[14];
            float t4 = this->m[0] * this->m[7] * this->m[10] * this->m[13];
            float t5 = this->m[0] * this->m[5] * this->m[11] * this->m[14];
            float t6 = this->m[0] * this->m[6] * this->m[9] * this->m[15];

            float t7 = this->m[4] * this->m[1] * this->m[10]  * this->m[15];
            float t8 = this->m[4] * this->m[2] * this->m[11] * this->m[13];
            float t9 = this->m[4] * this->m[3] * this->m[9] * this->m[14];
            float t10 = this->m[4] * this->m[3] * this->m[10] * this->m[13];
            float t11 = this->m[4] * this->m[1] * this->m[11] * this->m[14];
            float t12 = this->m[4] * this->m[2] * this->m[9] * this->m[15];

            float t13 = this->m[8] * this->m[1] * this->m[6]  * this->m[15];
            float t14 = this->m[8] * this->m[2] * this->m[7] * this->m[13];
            float t15 = this->m[8] * this->m[3] * this->m[5] * this->m[14];
            float t16 = this->m[8] * this->m[3] * this->m[6] * this->m[13];
            float t17 = this->m[8] * this->m[1] * this->m[7] * this->m[14];
            float t18 = this->m[8] * this->m[2] * this->m[5] * this->m[15];

            float t19 = this->m[12] * this->m[1] * this->m[6]  * this->m[11];
            float t20 = this->m[12] * this->m[2] * this->m[7] * this->m[9];
            float t21 = this->m[12] * this->m[3] * this->m[5] * this->m[10];
            float t22 = this->m[12] * this->m[3] * this->m[6] * this->m[9];
            float t23 = this->m[12] * this->m[1] * this->m[7] * this->m[10];
            float t24 = this->m[12] * this->m[2] * this->m[5] * this->m[11];


            return (t1 + t2 + t3 - t4 - t5 - t6) - (t7 + t8 + t9 - t10 - t11 - t12) + (t13 + t14 + t15 - t16 - t17 - t18) - (t19 + t20 + t21 - t22 - t23 - t24);
        }
    }

    void float4x4::setMatrixAsInverseOfGivenMatrix(const float4x4 &mat) {
        float det = mat.det();
        if (det == 0) return;

        float invd = 1.0f / det;

        float m0 = float3x3(mat.m[5], mat.m[6], mat.m[7], mat.m[9], mat.m[10], mat.m[11], mat.m[13], mat.m[14], mat.m[15]).det() * invd;
        float m4 = -float3x3(mat.m[1], mat.m[2], mat.m[3], mat.m[9], mat.m[10], mat.m[11], mat.m[13], mat.m[14], mat.m[15]).det() * invd;
        float m8 = float3x3(mat.m[1], mat.m[2], mat.m[3], mat.m[5], mat.m[6], mat.m[7], mat.m[13], mat.m[14], mat.m[15]).det() * invd;
        float m12 = -float3x3(mat.m[1], mat.m[2], mat.m[3], mat.m[5], mat.m[6], mat.m[7], mat.m[9], mat.m[10], mat.m[1]).det() * invd;
        float m1 = -float3x3(mat.m[4], mat.m[6], mat.m[7], mat.m[8], mat.m[10], mat.m[11], mat.m[12], mat.m[14], mat.m[15]).det() * invd;
        float m5 = float3x3(mat.m[0], mat.m[2], mat.m[3], mat.m[8], mat.m[10], mat.m[11], mat.m[12], mat.m[14], mat.m[15]).det() * invd;
        float m9 = -float3x3(mat.m[0], mat.m[2], mat.m[3], mat.m[4], mat.m[6], mat.m[7], mat.m[12], mat.m[14], mat.m[15]).det() * invd;
        float m13 = float3x3(mat.m[0], mat.m[2], mat.m[3], mat.m[4], mat.m[6], mat.m[7], mat.m[8], mat.m[10], mat.m[11]).det() * invd;
        float m2 = float3x3(mat.m[4], mat.m[5], mat.m[7], mat.m[8], mat.m[9], mat.m[11], mat.m[12], mat.m[13], mat.m[15]).det() * invd;
        float m6 = -float3x3(mat.m[0], mat.m[1], mat.m[3], mat.m[8], mat.m[9], mat.m[11], mat.m[12], mat.m[13], mat.m[15]).det() * invd;
        float m10 = float3x3(mat.m[0], mat.m[1], mat.m[3], mat.m[4], mat.m[5], mat.m[7], mat.m[12], mat.m[13], mat.m[15]).det() * invd;
        float m14 = -float3x3(mat.m[0], mat.m[1], mat.m[3], mat.m[4], mat.m[5], mat.m[7], mat.m[8], mat.m[9], mat.m[11]).det() * invd;
        float m3 = -float3x3(mat.m[4], mat.m[5], mat.m[6], mat.m[8], mat.m[9], mat.m[10], mat.m[12], mat.m[13], mat.m[14]).det() * invd;
        float m7 = float3x3(mat.m[0], mat.m[1], mat.m[2], mat.m[8], mat.m[9], mat.m[10], mat.m[12], mat.m[13], mat.m[14]).det() * invd;
        float m11 = -float3x3(mat.m[0], mat.m[1], mat.m[2], mat.m[4], mat.m[5], mat.m[6], mat.m[12], mat.m[13], mat.m[14]).det() * invd;
        float m15 = float3x3(mat.m[0], mat.m[1], mat.m[2], mat.m[4], mat.m[5], mat.m[6], mat.m[8], mat.m[9], mat.m[10]).det() * invd;


        this->m[0] = m0;
        this->m[1] = m4;
        this->m[2] = m8;
        this->m[3] = m12;

        this->m[4] = m1;
        this->m[5] = m5;
        this->m[6] = m9;
        this->m[7] = m13;

        this->m[8] = m2;
        this->m[9] = m6;
        this->m[10] = m10;
        this->m[11] = m14;

        this->m[12] = m3;
        this->m[13] = m7;
        this->m[14] = m11;
        this->m[15] = m15;
    }

    float4x4 float4x4::getInverseOfMatrix() const {
        float4x4 result;
        result.setMatrixAsInverseOfGivenMatrix(*this);
        return result;
    }

    void float4x4::invert() {
        auto mat = float4x4(*this);
        setMatrixAsInverseOfGivenMatrix(mat);
    }

    void float4x4::setMatrixAsTransposeOfGivenMatrix(const float4x4 &mat) {
        this->m[0] = mat.m[0];
        this->m[4] = mat.m[1];
        this->m[8] = mat.m[2];
        this->m[12] = mat.m[3];

        this->m[1] = mat.m[4];
        this->m[5] = mat.m[5];
        this->m[9] = mat.m[6];
        this->m[13] = mat.m[7];

        this->m[2] = mat.m[8];
        this->m[6] = mat.m[9];
        this->m[10] = mat.m[10];
        this->m[14] = mat.m[11];

        this->m[3] = mat.m[12];
        this->m[7] = mat.m[13];
        this->m[11] = mat.m[14];
        this->m[15] = mat.m[15];
    }

    float4x4 float4x4::getTransposeOfMatrix() const {
        float4x4 result;
        result.setMatrixAsTransposeOfGivenMatrix(*this);
        return result;
    }

    void float4x4::transpose() {
        auto mat = float4x4(*this);
        setMatrixAsTransposeOfGivenMatrix(mat);
    }

    void float4x4::setTranslation(const float3 &translation) {
        this->m[12] = translation.x;
        this->m[13] = translation.y;
        this->m[14] = translation.z;
    }

    void float4x4::setScale(const float3 &scaleFactor) {
        this->loadIdentity();

        this->m[0] = scaleFactor.x;
        this->m[5] = scaleFactor.y;
        this->m[10] = scaleFactor.z;
    }

    void float4x4::setUniformScale(float scaleFactor) {
        this->loadIdentity();

        this->m[0] = this->m[5] = this->m[10] = scaleFactor;
    }

    void float4x4::setRotationAxis(double angle, const float3 &axis) {
        float3 u = axis.getNormalized();

        auto sinAngle = static_cast<float>(sin(M_PI * angle / 180.0));
        auto cosAngle = static_cast<float>(cos(M_PI * angle / 180.0));
        float oneMinusCosAngle = 1.0f - cosAngle;

        this->loadIdentity();

        this->m[0] = (u.x) * (u.x) + (cosAngle) * (1 - (u.x) * (u.x));
        this->m[4] = (u.x) * (u.y) * (oneMinusCosAngle) - (sinAngle) * u.z;
        this->m[8] = (u.x) * (u.z) * (oneMinusCosAngle) + (sinAngle) * u.y;

        this->m[1] = (u.x) * (u.y) * (oneMinusCosAngle) + (sinAngle) * u.z;
        this->m[5] = (u.y) * (u.y) + (cosAngle) * (1 - (u.y) * (u.y));
        this->m[9] = (u.y) * (u.z) * (oneMinusCosAngle) - (sinAngle) * u.x;

        this->m[2] = (u.x) * (u.z) * (oneMinusCosAngle) - (sinAngle) * u.y;
        this->m[6] = (u.y) * (u.z) * (oneMinusCosAngle) + (sinAngle) * u.x;
        this->m[10] = (u.z) * (u.z) + (cosAngle) * (1 - (u.z) * (u.z));
    }

    void float4x4::setRotationX(double angle) {
        this->loadIdentity();

        this->m[5] = static_cast<float>(cos(M_PI * angle / 180.0));
        this->m[6] = static_cast<float>(sin(M_PI * angle / 180.0));

        this->m[9] = -this->m[6];
        this->m[10] = this->m[5];
    }

    void float4x4::setRotationY(double angle) {
        this->loadIdentity();

        this->m[0] = static_cast<float>(cos(M_PI * angle / 180.0));
        this->m[2] = -static_cast<float>(sin(M_PI * angle / 180.0));

        this->m[8] = -this->m[2];
        this->m[10] = this->m[0];
    }

    void float4x4::setRotationZ(double angle) {
        this->loadIdentity();

        this->m[0] = static_cast<float>(cos(M_PI * angle / 180.0));
        this->m[1] = static_cast<float>(sin(M_PI * angle / 180.0));

        this->m[4] = -this->m[1];
        this->m[5] = this->m[0];
    }

    std::ostream & operator<<(std::ostream &os, const float4x4 &mat) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (j == 0) os << " | ";
                os << mat.m[i + j * 4] << " ";
                if (j != 3) os << " , ";
                else os << " | " << std::endl;
            }
        }
        return os;
    }
}

