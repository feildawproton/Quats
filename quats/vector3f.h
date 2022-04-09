//--------------------
//stuff
//--------------------

#ifndef VECTOR3F_H
#define VECTOR3F_H

namespace mathObjs
{
	struct Vector3f
	{

		float x, y, z;  //single precision float because reasons. Do you want to waste on conversion to glFloat? 

		Vector3f(); //returns all zero
		Vector3f(float X, float Y, float Z);
		Vector3f(char axis); //for unit axis vectors. char 'x', 'v', or 'z'

		~Vector3f();

		//no need for copy constructor

		Vector3f operator+(const Vector3f& that) const;
		Vector3f& operator+=(const Vector3f& that);

		Vector3f operator-(const Vector3f& that) const;
		Vector3f& operator-=(const Vector3f& that);

		Vector3f operator*(float scaler) const; //scalling
		Vector3f& operator*=(float scaler); //scallings

		Vector3f operator*(const Vector3f& that) const; //cross product
		Vector3f& operator*=(const Vector3f& that); //cross product

		Vector3f operator/(float scaler) const;
		Vector3f& operator/=(float scaler);

		float magnitude() const;
		Vector3f normalized() const;
		Vector3f& normalize();

		Vector3f inverted() const;
		Vector3f& invert();
	};

	Vector3f average(const Vector3f& A, const Vector3f& B); //why I do this?

	Vector3f projection(const Vector3f& A, const Vector3f& B);//project A onto B

	Vector3f rejection(const Vector3f& A, const Vector3f& B);//rejection B from A

	float dot(const Vector3f& A, const Vector3f& B);

	float cosTheta(const Vector3f& A, const Vector3f& B);

	float distanceMagnitude(const Vector3f& A, const Vector3f& B); //super lazy
}
#endif
