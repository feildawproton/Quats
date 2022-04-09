#include "quaternion4f.h"
#include "mathObjsRsrcs.h"
#include <cmath> 

namespace mathObjs
{
	Quaternion4f::Quaternion4f()
	{
		w = 1;
		x = 0;
		y = 0;
		z = 0;
	}
	Quaternion4f::Quaternion4f(float W, float X, float Y, float Z)
	{
		w = W;
		x = X;
		y = Y;
		z = Z;
	}
	Quaternion4f::Quaternion4f(float W, const Vector3f& V)
	{
		w = W;
		x = V.x;
		y = V.y;
		z = V.z;
	}
	Quaternion4f::Quaternion4f(TaitBryanType tbType, angleType angleType, const Vector3f& eulerAngles)
	{
		float roll;
		float pitch;
		float yaw;

		if (angleType == degrees)
		{
			roll = eulerAngles.x * DegreesToRadians;
			pitch = eulerAngles.y * DegreesToRadians;
			yaw = eulerAngles.z * DegreesToRadians;
		}
		else
		{
			roll = eulerAngles.x;
			pitch = eulerAngles.y;
			yaw = eulerAngles.z;
		}

		if (tbType == ZXZ)
		{
			//why you do this?
			w = cos((yaw + roll) / 2) * cos(pitch / 2);
			x = cos((yaw - roll) / 2) * sin(pitch / 2);
			y = sin((yaw - roll) / 2) * sin(pitch / 2);
			y = sin((yaw + roll) / 2) * cos(pitch / 2);
		}
		else
		{
			w = cos(yaw / 2) * cos(pitch / 2) * cos(roll / 2) + sin(yaw / 2) * sin(pitch / 2) * sin(roll / 2);
			x = cos(yaw / 2) * cos(pitch / 2) * sin(roll / 2) - sin(yaw / 2) * sin(pitch / 2) * cos(roll / 2);
			y = cos(yaw / 2) * sin(pitch / 2) * cos(roll / 2) + sin(yaw / 2) * cos(pitch / 2) * sin(roll / 2);
			z = sin(yaw / 2) * cos(pitch / 2) * cos(roll / 2) - cos(yaw / 2) * sin(pitch / 2) * sin(roll / 2);
		}

		//normalize(); instead of call to normalize do in here
		float mag = sqrt(w*w + x*x + y*y + z*z);

		w /= mag;
		x /= mag;
		y /= mag;
		z /= mag;
	}
	Quaternion4f::Quaternion4f(angleType angleType, const Vector3f& eulerAngles)
	{
		float roll;
		float pitch;
		float yaw;

		if (angleType == degrees)
		{
			roll = eulerAngles.x * DegreesToRadians;
			pitch = eulerAngles.y * DegreesToRadians;
			yaw = eulerAngles.z * DegreesToRadians;
		}
		else
		{
			roll = eulerAngles.x;
			pitch = eulerAngles.y;
			yaw = eulerAngles.z;
		}

		float T = cos(yaw/2); float Z = sin(yaw/2);
		float P = cos(pitch/2); float Y = sin(pitch/2);
		float R = cos(roll/2); float X = sin(roll/2);

		w = T*P*R + Z*Y*X;
		x = T*P*X - Z*Y*R;
		y = T*Y*R + Z*P*X;
		z = -T*Y*X + Z*P*R;

		//normalize(); instead of call to normalize do in here
		float mag = sqrt(w*w + x*x + y*y + z*z);

		w /= mag;
		x /= mag;
		y /= mag;
		z /= mag;
	}



	Quaternion4f::Quaternion4f(const Vector3f& A, const Vector3f& B)
	{
		float AA = A.x*A.x + A.y*A.y + A.z*A.z;
		float BB = B.x*B.x + B.y*B.y + B.z*B.z;

		float magAB = sqrt(AA*BB);

		float AB = A.x*B.x + A.y*B.y + A.z*B.z;

		float COSTHETA = AB / magAB;

		w = sqrt((1 + COSTHETA) / 2); //cosine of half angle

		float denom = 2 * w * magAB; //for the right side

		x = (A.y*B.z - A.z*B.y) / denom;
		y = (A.z*B.x - A.x*B.z) / denom;
		z = (A.x*B.y - A.y*B.x) / denom;
	}

	Quaternion4f::Quaternion4f(float T, float Z, float P, float Y, float R, float X)
	{
		w = T*P*R + Z*Y*X;
		x = T*P*X - Z*Y*R;
		y = T*Y*R + Z*P*X;
		z = -T*Y*X + Z*P*R;
	}

	Quaternion4f::~Quaternion4f()
	{
	}

	Quaternion4f Quaternion4f::operator*(const Quaternion4f& that) const
	{
		//notice the pattern: going right (ex i*j) sign is + and going left (left handed) sign is - (ex: k*j)
		float W = (w * that.w) - (x * that.x) - (y * that.y) - (z * that.z);
		float X = ((w * that.x) + (x * that.w)) + (y * that.z) - (z * that.y);
		float Y = ((w * that.y) + (y * that.w)) + (z * that.x) - (x * that.z);
		float Z = ((w * that.z) + (z * that.w)) + (x * that.y) - (y * that.x);

		return Quaternion4f(W, X, Y, Z);
	}
	Quaternion4f& Quaternion4f::operator*=(const Quaternion4f& that)
	{
		//have to hold temps because original values are reused thorughout the calculation
		float W = (w * that.w) - (x * that.x) - (y * that.y) - (z * that.z);
		float X = ((w * that.x) + (x * that.w)) + (y * that.z) - (z * that.y);
		float Y = ((w * that.y) + (y * that.w)) + (z * that.x) - (x * that.z);
		float Z = ((w * that.z) + (z * that.w)) + (x * that.y) - (y * that.x);

		w = W;
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	Quaternion4f Quaternion4f::operator*(float scaler) const
	{
		float W = w*scaler;
		float X = x*scaler;
		float Y = y*scaler;
		float Z = z*scaler;

		return Quaternion4f(W, X, Y, Z);
	}
	Quaternion4f& Quaternion4f::operator*=(float scaler)
	{
		w *= scaler;
		x *= scaler;
		y *= scaler;
		z *= scaler;

		return *this;
	}

	Quaternion4f Quaternion4f::operator/(float scaler) const
	{
		float W = w*scaler;
		float X = x*scaler;
		float Y = y*scaler;
		float Z = z*scaler;

		return Quaternion4f(W, X, Y, Z);
	}
	Quaternion4f& Quaternion4f::operator/=(float scaler)
	{
		w /= scaler;
		x /= scaler;
		y /= scaler;
		z /= scaler;

		return *this;
	}

	float Quaternion4f::norm() const
	{
		return sqrt(w*w + x*x + y*y + z*z);
	}

	Quaternion4f Quaternion4f::normalized() const
	{
		//could have called mag() but lets not
		float mag = sqrt(w*w + x*x + y*y + z*z);

		return Quaternion4f(w / mag, x / mag, y / mag, z / mag);
	}
	Quaternion4f& Quaternion4f::normalize()
	{
		float mag = sqrt(w*w + x*x + y*y + z*z);

		w /= mag;
		x /= mag;
		y /= mag;
		z /= mag;

		return *this;
	}

	Quaternion4f Quaternion4f::conjugate() const
	{
		return Quaternion4f(w, -x, -y, -z);
	}

	Quaternion4f Quaternion4f::reciprical() const
	{
		Quaternion4f conj = Quaternion4f(w, -x, -y, -z);
		float normSqrd = w*w + x*x + y*y + z*z;
		//could have called /= overload but lets not
		conj.w /= normSqrd;
		conj.x /= normSqrd;
		conj.y /= normSqrd;
		conj.z /= normSqrd;

		return conj;
	}
	Quaternion4f& Quaternion4f::recipricate()
	{
		x *= -1;
		y *= -1;
		z *= -1;

		float normSqrd = w*w + x*x + y*y + z*z;

		w /= normSqrd;
		x /= normSqrd;
		y /= normSqrd;
		z /= normSqrd;

		return *this;
	}

	float difference(const Quaternion4f& q, const Quaternion4f& p)
	{
		double wSqrd = (p.w - q.w)*(p.w - q.w);
		double xSqrd = (p.x - q.x)*(p.x - q.x);
		double ySqrd = (p.y - q.y)*(p.y - q.y);
		double zSqrd = (p.z - q.z)*(p.z - q.z);

		return sqrt(wSqrd + xSqrd + ySqrd + zSqrd);
	}

	Vector3f rotate(const Vector3f& v, const Quaternion4f& q)
	{
		Quaternion4f p = Quaternion4f(0, v);

		float normSqrd = q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z;
		Quaternion4f qReciprical = Quaternion4f(q.w, -q.x, -q.y, -q.z); //q conugate
		qReciprical.w /= normSqrd;
		qReciprical.x /= normSqrd;
		qReciprical.y /= normSqrd;
		qReciprical.z /= normSqrd;

		//replace these function calls?
		Quaternion4f pPrime = q * p * qReciprical;

		return Vector3f(pPrime.x, pPrime.y, pPrime.z);
	}

	//Vector3f notate(const Vector3f& v, const Quaternion4f& q)
	//{
	//	Quaternion4f p = Quaternion4f(0, v);

	//	float normSqrd = q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z;
	//	Quaternion4f three = Quaternion4f(q.w, -q.x, -q.y, -q.z); //q conugate
	//	qReciprical.w /= normSqrd;
	//	qReciprical.x /= normSqrd;
	//	qReciprical.y /= normSqrd;
	//	qReciprical.z /= normSqrd;

	//	//Quaternion4f pPrime = q * p * qReciprical;

	//	float W = q.w()

	//	return Vector3f(pPrime.x, pPrime.y, pPrime.z);
	//}

	//Quaternion4f rotate3Trad(Quaternion4f three, Quaternion4f two, Quaternion4f one)
	//{
	//	return three * two * one;
	//}

	//Quaternion4f mult3Quick(Quaternion4f three, Quaternion4f two, Quaternion4f one)
	//{
	//	float W = three.w*(two.w*one.w - two.x*one.x - two.y*one.y - two.z*one.z)
	//		- three.x*(two.w*one.x + two.x*one.w + two.y*one.z - two.z*one.y)
	//		- 
	//}
}

