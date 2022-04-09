#include "vector3f.h"
#include <cmath>

namespace mathObjs
{
	Vector3f::Vector3f()
	{
		x = 0; y = 0; z = 0;
	}

	Vector3f::Vector3f(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}

	Vector3f::Vector3f(char axis)
	{
		if (axis == 'x' || axis == 'X')
		{
			x = 1; y = 0; z = 0;
		}
		else if (axis == 'y' || axis == 'Y')
		{
			x = 0; y = 1; z = 0;
		}
		else if (axis == 'z' || axis == 'Z')
		{
			x = 0; y = 0; z = 1;
		}
		else
		{
			x = 0; y = 0; z = 0;
		}
	}

	Vector3f::~Vector3f()
	{
	}

	Vector3f Vector3f::operator+(const Vector3f& that) const
	{
		float tempx = x + that.x;
		float tempy = y + that.y;
		float tempz = z + that.z;

		return Vector3f(tempx, tempy, tempz);
	}
	Vector3f& Vector3f::operator+=(const Vector3f& that)
	{
		x += that.x;
		y += that.y;
		z += that.z;

		return *this;
	}

	Vector3f Vector3f::operator-(const Vector3f& that) const
	{
		float tempx = x - that.x;
		float tempy = y - that.y;
		float tempz = z - that.z;

		return Vector3f(tempx, tempy, tempz);
	}
	Vector3f& Vector3f::operator-=(const Vector3f& that)
	{
		x -= that.x;
		y -= that.y;
		z -= that.z;

		return *this;
	}

	Vector3f Vector3f::operator*(float scaler) const
	{
		float tempx = x * scaler;
		float tempy = y * scaler;
		float tempz = z * scaler;

		return Vector3f(tempx, tempy, tempz);
	}
	Vector3f& Vector3f::operator*=(float scaler)
	{
		x *= scaler;
		y *= scaler;
		z *= scaler;

		return *this;
	}

	Vector3f Vector3f::operator*(const Vector3f& that) const
	{
		//go to the right of current
		float X = y*that.z - z*that.y;
		float Y = z*that.x - x*that.z;
		float Z = x*that.y - y*that.x;

		return Vector3f(X, Y, Z);
	}
	Vector3f& Vector3f::operator*=(const Vector3f& that)
	{
		//go to the right of current
		x = (y*that.z - z*that.y);
		y = (z*that.x - x*that.z);
		z = (x*that.y - y*that.x);

		return *this;
	}

	Vector3f Vector3f::operator/(float scaler) const
	{
		float tempx = x / scaler;
		float tempy = y / scaler;
		float tempz = z / scaler;

		return Vector3f(tempx, tempy, tempz);
	}
	Vector3f& Vector3f::operator/=(float scaler)
	{
		x /= scaler;
		y /= scaler;
		z /= scaler;

		return *this;
	}

	float Vector3f::magnitude() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	Vector3f Vector3f::normalized() const
	{
		float mag = magnitude();

		return Vector3f(x / mag, y / mag, z / mag);
	}
	Vector3f& Vector3f::normalize()
	{
		float mag = magnitude();

		x /= mag;
		y /= mag;
		z /= mag;

		return *this;
	}

	Vector3f Vector3f::inverted() const
	{
		return Vector3f(-x, -y, -z);
	}
	Vector3f& Vector3f::invert()
	{
		x = -x;
		y = -y;
		z = -z;

		return *this;
	}



	Vector3f average(const Vector3f& A, const Vector3f& B)
	{
		float X = ((A.x - B.x) / 2) + B.x;
		float Y = ((A.y - B.y) / 2) + B.y;
		float Z = ((A.z - B.z) / 2) + B.z;

		return Vector3f(X, Y, Z);
	}

	Vector3f projection(const Vector3f& A, const Vector3f& B)//project A onto B
	{
		float AB = A.x*B.x + A.y*B.y + A.z*B.z;
		float BB = B.x*B.x + B.y*B.y + B.z*B.z;

		float ABoverBB = AB / BB;

		float X = B.x * ABoverBB;
		float Y = B.y * ABoverBB;
		float Z = B.z * ABoverBB;

		return Vector3f(X, Y, Z);

		////slower version because of sqrt but common way of doing this
		//float AB = A.x*B.x + A.y*B.y + A.z*B.z;
		//float magB = sqrt(B.x*B.x + B.y*B.y + B.z*B.z);

		//float alpha = AB / magB;
		//float X = (B.x / magB)*alpha;
		//float Y = (B.y / magB)*alpha;
		//float Z = (B.z / magB)*alpha;

		//return Vector3f(X, Y, Z);
	}

	Vector3f rejection(const Vector3f& A, const Vector3f& B)//rejection B from A
	{
		float AB = A.x*B.x + A.y*B.y + A.z*B.z;
		float BB = B.x*B.x + B.y*B.y + B.z*B.z;

		float ABoverBB = AB / BB;

		float X = A.x - (B.x * ABoverBB);
		float Y = A.y - (B.y * ABoverBB);
		float Z = A.z - (B.z * ABoverBB);

		return Vector3f(X, Y, Z);
	}

	float dot(const Vector3f& A, const Vector3f& B)
	{
		return (A.x*B.x + A.y*B.y + A.z*B.z);
	}

	float cosTheta(const Vector3f& A, const Vector3f& B)
	{
		float AA = A.x*A.x + A.y*A.y + A.z*A.z;
		float BB = B.x*B.x + B.y*B.y + B.z*B.z;

		float magAB = sqrt(AA*BB);

		float AB = A.x*B.x + A.y*B.y + A.z*B.z;

		return AB / magAB;
	}

	float distanceMagnitude(const Vector3f& A, const Vector3f& B)
	{
		Vector3f C = A - B;

		return C.magnitude();
	}
}

