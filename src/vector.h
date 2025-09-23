#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <cmath>

using namespace std;

class Vector{
    public:
    float x,y;

    Vector(float x, float y);

    Vector();

    void display() const;

    void normalize();

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

Vector trunc(const Vector &v);

std::ostream& operator<<(ostream& os, const Vector& v);

float dotProduct(const Vector &v1, const Vector &v2);

#endif