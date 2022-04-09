//--------------------
//ba ba blah sheep
//--------------------

#ifndef QUATERNION4F_H
#define QUATERNION4F_H

#include "vector3f.h"
#include "mathObjsRsrcs.h"

namespace mathObjs
{
	
	struct Quaternion4f
	{
		float w, x, y, z; //floats

		//got some constructors
		Quaternion4f();
		Quaternion4f(float W, float X, float Y, float Z);
		Quaternion4f(float W, const Vector3f& V);
		Quaternion4f(TaitBryanType tbType, angleType angleType, const Vector3f& eulerAngles);//for conversion to quaternion from euler angles (uses transendentals (gross)). using ZYX convention (x applied first, z is the twist). also check for going negative angles in the opposite direction
		Quaternion4f(angleType angleType, const Vector3f& eulerAngles); //quickYPR, this is the actually the same as TaitBryan YPR

		//even more constructors
		Quaternion4f(const Vector3f& A, const Vector3f& B);
		Quaternion4f(float T, float Z, float P, float Y, float R, float X);
		~Quaternion4f();
		
		//need for copy or move constructor

		Quaternion4f operator*(const Quaternion4f& that) const; //tried with definition in header, no benifit
		Quaternion4f& operator*=(const Quaternion4f& that);

		Quaternion4f operator*(float scaler) const;
		Quaternion4f& operator*=(float scaler);

		Quaternion4f operator/(float scaler) const;//handedness in quaternion division is unkown so we don't actually have q/q2, use reciprical and multiply instead
		Quaternion4f& operator/=(float scaler);

		float norm() const;
		Quaternion4f normalized() const;
		Quaternion4f& normalize();

		Quaternion4f conjugate() const;
		Quaternion4f reciprical() const;
		Quaternion4f& recipricate();

		//need to check id this is correct
		Quaternion4f half() const;
		//need to check if this correct
		Quaternion4f& halved();

		//need more smart stuff here
	};

	float difference(const Quaternion4f& q, const Quaternion4f& p); //just for testing
	
	Vector3f rotate(const Vector3f& v, const Quaternion4f& q); //rotate your owl. FOR SCIENCE!

	Vector3f notate(const Vector3f& v, const Quaternion4f& q);

}
#endif