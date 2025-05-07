
#ifndef MATH_H
#define MATH_H

#include <ostream>
#define M_PI 3.14159265358979323846

namespace Math {

    struct Integer3 {
        int x, y, z;

        Integer3() = default;
        Integer3(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

        friend std::ostream &operator<<(std::ostream &os, const Integer3 &v);
    };


    struct Point {
        float x, y, z=0;
        Point(float _x, float _y, float _z = 0) : x(_x), y(_y), z(_z) {}
        friend std::ostream &operator<<(std::ostream &os, const Point &p);
    };

    class float2 {
    public:
        float x, y;

        float2();

        float2(float _x, float _y);

        float2 &operator=(const float2 &v) = default;

        float2(const float2 &v) = default;

        ~float2() = default;

        void operator+=(const float2 &v);

        void operator-=(const float2 &v);

        float2 operator+(const float2 &v) const;

        float2 operator-(const float2 &v) const;

        void operator*=(float o);

        void operator/=(float o);

        float2 operator*(float o) const;

        friend float2 operator*(float o, const float2 &v);

        float2 operator/(float o) const;

        friend float2 operator/(float o, const float2 &v);

        float len() const;

        void normalize();

        float2 getNormalized() const;

        float dot(const float2 &v) const;

        float getAngle(const float2 &v) const;

        friend std::ostream &operator<<(std::ostream &os, const float2 &v);
    };

    class float3 {
    public:
        float x, y, z;

        float3();

        float3(float _x, float _y, float _z);

        float3 &operator=(const float3 &v) = default;

        float3(const float3 &v) = default;

        ~float3() = default;

        void operator+=(const float3 &v);

        void operator-=(const float3 &v);

        float3 operator+(const float3 &v) const;

        float3 operator-(const float3 &v) const;

        void operator*=(float o);

        void operator/=(float o);

        float3 operator*(float o) const;

        friend float3 operator*(float o, const float3 &v);

        float3 operator/(float o) const;

        friend float3 operator/(float o, const float3 &v);

        float len() const;

        void normalize();

        float3 getNormalized() const;

        float dot(const float3 &v) const;

        float3 cross(const float3 &v) const;

        float getAngle(const float3 &v) const;

        friend std::ostream &operator<<(std::ostream &os, const float3 &v);
    };

    class float4 {
    public:
        float x, y, z, w;

        float4();

        float4(float _x, float _y, float _z, float _w);

        float4 &operator=(const float4 &v) = default;

        float4(const float4 &v) = default;

        ~float4() = default;

        void operator+=(const float4 &v);

        void operator-=(const float4 &v);

        float4 operator+(const float4 &v) const;

        float4 operator-(const float4 &v) const;

        void operator*=(float o);

        void operator/=(float o);

        float4 operator*(float o) const;

        friend float4 operator*(float o, const float4 &v);

        float4 operator/(float o) const;

        friend float4 operator/(float o, const float4 &v);

        float len() const;

        void normalize();

        float4 getNormalized() const;

        float dot(const float4 &v) const;

        friend std::ostream &operator<<(std::ostream &os, const float4 &v);
    };

    class float3x3 {
    private:
        float m[9] = {0.0f};

    public:

        float3x3() = default;

        float3x3(float3 vec1, float3 vec2, float3 vec3);

        float3x3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8);

        explicit float3x3(const float *f);

        float3x3(const float3x3 &mat);

        float3x3 &operator=(const float3x3 &mat) = default;

        ~float3x3() = default;

        void operator+=(const float3x3 &mat);

        void operator-=(const float3x3 &mat);

        float3x3 operator+(const float3x3 &mat) const;

        float3x3 operator-(const float3x3 &mat) const;

        void operator*=(float o);

        void operator/=(float o);

        float3x3 operator*(float o) const;

        friend float3x3 operator*(float o, const float3x3 &mat);

        float3x3 operator/(float o) const;

        float3 operator*(const float3 &v) const;

        friend float3 operator*(const float3 &v, const float3x3 &mat);

        void operator*=(const float3x3 &mat);

        float3x3 operator*(const float3x3 &mat) const;

        float3 operator[](int i) const;

        void loadIdentity();

        float det() const;

        void setMatrixAsInverseOfGivenMatrix(const float3x3 &mat);

        float3x3 getInverseOfMatrix() const;

        void invert();

        void setMatrixAsTransposeOfGivenMatrix(const float3x3 &mat);

        float3x3 getTransposeOfMatrix() const;

        void transpose();

        friend std::ostream &operator<<(std::ostream &os, const float3x3 &mat);
    };

    class float4x4 {
    private:
        float m[16] = {0.0f};

    public:
        class ColumnProxy {
        private:
            float* col_ptr;

        public:
            ColumnProxy(float* ptr);

            // Read access
            operator float4() const;

            // Write access
            ColumnProxy& operator=(const float4& vec);
        };

        float4x4() = default;

        float4x4(float4 vec1, float4 vec2, float4 vec3, float4 vec4);

        float4x4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8,
                 float m9, float m10, float m11, float m12, float m13, float m14, float m15);

        explicit float4x4(const float *f);

        float4x4(const float4x4 &mat);

        float4x4 &operator=(const float4x4 &mat) = default;

        ~float4x4() = default;

        void operator+=(const float4x4 &mat);

        void operator-=(const float4x4 &mat);

        float4x4 operator+(const float4x4 &mat) const;

        float4x4 operator-(const float4x4 &mat) const;

        void operator*=(float o);

        void operator/=(float o);

        float4x4 operator*(float o) const;

        friend float4x4 operator*(float o, const float4x4 &mat);

        float4x4 operator/(float o) const;

        float4 operator*(const float4 &v) const;

        friend float4 operator*(const float4 &v, const float4x4 &mat);

        void operator*=(const float4x4 &mat);

        float4x4 operator*(const float4x4 &mat) const;

        // Access column i as a proxy
        ColumnProxy operator[](int i);

        // Optional const version for read-only access
        float4 operator[](int i) const;

        void loadIdentity();

        float det() const;

        void setMatrixAsInverseOfGivenMatrix(const float4x4 &mat);

        float4x4 getInverseOfMatrix() const;

        void invert();

        void setMatrixAsTransposeOfGivenMatrix(const float4x4 &mat);

        float4x4 getTransposeOfMatrix() const;

        void transpose();

        void setTranslation(const float3 &translation);

        void setScale(const float3 &scaleFactor);

        void setUniformScale(float scaleFactor);

        void setRotationAxis(double angle, const float3 &axis);

        void setRotationX(double angle);

        void setRotationY(double angle);

        void setRotationZ(double angle);

        friend std::ostream &operator<<(std::ostream &os, const float4x4 &mat);
    };

}

#endif //MATH_H
