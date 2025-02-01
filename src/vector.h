#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

class Vector{
    public:
    float x,y;

    Vector(float x, float y);

    void display() const;

    // Operators

    Vector operator+(const Vector &v2) const;

    Vector operator+(float val) const;

    Vector operator-(const Vector &v2) const;

    Vector operator-(float val) const;

    Vector operator*(float val) const;

    Vector operator/(float val) const;

    void operator+=(const Vector &v2);

    void operator+=(float val);

    void operator-=(const Vector &v2);

    void operator-=(float val);

    void operator*=(float val);

    void operator/=(float val);
};



float dotProduct(const Vector &v1, const Vector &v2);

#endif