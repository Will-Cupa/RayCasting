#include "vector.h"

using namespace std;

Vector::Vector(float x, float y){
    (*this).x = x;
    (*this).y = y;
}

Vector Vector::operator+(const Vector &v2) const{
    return Vector(x + v2.x, y + v2.y);
}

Vector Vector::operator+(float val) const{
    return Vector(x + val, y + val);
}

Vector Vector::operator-(const Vector &v2) const{
    return Vector(x - v2.x, y - v2.y);
}

Vector Vector::operator-(float val) const{
    return Vector(x - val, y - val);
}

Vector Vector::operator*(float val) const{
    return Vector(x * val, y * val);
}

Vector Vector::operator/(float val) const{
    return Vector(x / val, y / val);
}

void Vector::operator+=(const Vector &v2){
    x += v2.x; 
    y += v2.y;
}

void Vector::operator+=(float val){
    x += val; 
    y += val;
}

void Vector::operator-=(const Vector &v2){
    x -= v2.x; 
    y -= v2.y;
}

void Vector::operator-=(float val){
    x -= val; 
    y -= val;
}

void Vector::operator*=(float val){
    x *= val; 
    y *= val;
}

void Vector::operator/=(float val){
    x /= val; 
    y /= val;
}

void Vector::normalize(){
    y /=x;
    x = 1;
}

void Vector::display() const{
    cout << x << " " << y << endl;
}

float dotProduct(const Vector &v1, const Vector &v2){
    return v1.x*v2.x + v1.y * v2.y;
}