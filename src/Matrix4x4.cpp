#include "../include/Matrix4x4.h"

Matrix4x4::Matrix4x4() {}
Matrix4x4::Matrix4x4 (float v00, float v01, float v02, float v03,
            float v10, float v11, float v12, float v13,
            float v20, float v21, float v22, float v23,
            float v30, float v31, float v32, float v33){
    m[0][0] = v00;
    m[0][1] = v01;
    m[0][2] = v02;
    m[0][3] = v03;
    m[1][0] = v10;
    m[1][1] = v11;
    m[1][2] = v12;
    m[1][3] = v13;
    m[2][0] = v20;
    m[2][1] = v21;
    m[2][2] = v22;
    m[2][3] = v23;
    m[3][0] = v30;
    m[3][1] = v31;
    m[3][2] = v32;
    m[3][3] = v33;
}
const float* Matrix4x4::operator[](uint8_t i) const { return m[i]; }
float* Matrix4x4::operator[](uint8_t i) { return m[i]; }

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& n) const
{
    Matrix4x4 mult;
    for(uint8_t i = 0; i < 4; i++){
        for(uint8_t j = 0; j < 4; j++){
            mult[i][j] = m[i][0] * n[0][j] +
                         m[i][1] * n[1][j] +
                         m[i][2] * n[2][j] +
                         m[i][3] * n[3][j];
        }
    }

    return mult;
}

Matrix4x4 Matrix4x4::transpose() const{
    Matrix4x4 transpMat;
    for(uint8_t i=0; i<4; i++){
        for(uint8_t j=0; j<4; j++){
            transpMat[i][j] = m[j][i];
        }
    }
    return transpMat;
}

void Matrix4x4::multPointMatrix(const Vector3& src, Vector3& dst) const{
    float a, b, c, w;

        a = src[0] * m[0][0] + src[1] * m[1][0] + src[2] * m[2][0] + m[3][0];
        b = src[0] * m[0][1] + src[1] * m[1][1] + src[2] * m[2][1] + m[3][1];
        c = src[0] * m[0][2] + src[1] * m[1][2] + src[2] * m[2][2] + m[3][2];
        w = src[0] * m[0][3] + src[1] * m[1][3] + src[2] * m[2][3] + m[3][3];

        dst.x = a / w;
        dst.y = b / w;
        dst.z = c / w;
}
void Matrix4x4::multVectorMatrix(const Vector3& src, Vector3& dst) const{
    float a, b, c; 

    a = src[0] * m[0][0] + src[1] * m[1][0] + src[2] * m[2][0]; 
    b = src[0] * m[0][1] + src[1] * m[1][1] + src[2] * m[2][1]; 
    c = src[0] * m[0][2] + src[1] * m[1][2] + src[2] * m[2][2]; 

    dst.x = a; 
    dst.y = b; 
    dst.z = c; 
}
Matrix4x4 Matrix4x4::inverse() const{
    int i, j, k;
    Matrix4x4 s;
    Matrix4x4 t (*this);

    // Forward elimination
    for (i = 0; i < 3 ; i++) {
        int pivot = i;

        float pivotsize = t[i][i];

        if (pivotsize < 0)
            pivotsize = -pivotsize;

        for (j = i + 1; j < 4; j++) {
            float tmp = t[j][i];

            if (tmp < 0)
                tmp = -tmp;

            if (tmp > pivotsize) {
                pivot = j;
                pivotsize = tmp;
            }
        }

    if (pivotsize == 0) {
        // Cannot invert singular matrix
        return Matrix4x4();
    }

    if (pivot != i) {
        for (j = 0; j < 4; j++) {
            float tmp;

            tmp = t[i][j];
            t[i][j] = t[pivot][j];
            t[pivot][j] = tmp;

            tmp = s[i][j];
            s[i][j] = s[pivot][j];
            s[pivot][j] = tmp;
        }
    }

    for (j = i + 1; j < 4; j++) {
        float f = t[j][i] / t[i][i];

        for (k = 0; k < 4; k++) {
            t[j][k] -= f * t[i][k];
            s[j][k] -= f * s[i][k];
            }
        }
    }

    // Backward substitution
    for (i = 3; i >= 0; --i) {
        float f;

        if ((f = t[i][i]) == 0) {
            // Cannot invert singular matrix
            return Matrix4x4();
        }

        for (j = 0; j < 4; j++) {
            t[i][j] /= f;
            s[i][j] /= f;
        }

        for (j = 0; j < i; j++) {
            f = t[j][i];

            for (k = 0; k < 4; k++) {
                t[j][k] -= f * t[i][k];
                s[j][k] -= f * s[i][k];
            }
        }
    }

    return s;
}

// \brief set current matrix to its inverse
const Matrix4x4& Matrix4x4::invert()
{
    *this = inverse();
    return *this;
}
