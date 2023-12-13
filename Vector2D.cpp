#include "Vector2D.h"


float Vector2D::gety()
{
	return y;
}

float Vector2D::getx()
{
	return x;
}

void Vector2D::sety(float y)
{
	this->y = y;
}

void Vector2D::setx(float x)
{
	this->x = x;
}

Vector2D& Vector2D::Add(const Vector2D& vec){
	x += vec.x;
	y += vec.y;
	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec){
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec){
	x *= vec.x;
	y *= vec.y;
	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec){
	x /= vec.x;
	y /= vec.y;
	return *this;
}


Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
	return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
	return v1.Divide(v2);
}


Vector2D& Vector2D::operator+=(const Vector2D& vec) {
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
	return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec) {
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec) {
	return this->Divide(vec);
}

ostream& operator<<(ostream& stream, const Vector2D& vec) {
	stream << "("<< vec.x<<", "<<vec.y<<")";
	return stream;
}