#pragma once
#include <iostream>
using namespace std;

class Vector2D {
	int x;
	int y;

public:
	Vector2D():x(0), y(0){}
	Vector2D(int x, int y):x(x), y(y){}

	int gety();
	int getx();
	void sety(int);
	void setx(int);

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);
	bool operator==(const Vector2D& vec);
	bool operator!=(const Vector2D& vec);

	Vector2D& operator*(const int& i);
	Vector2D& Zero();

	friend ostream& operator<<(ostream& stream, const Vector2D& vec);
};