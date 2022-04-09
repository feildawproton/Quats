#include <iostream>
#include "vector3f.h"
#include "quaternion4f.h"
#include <cmath>
#include <ctime>
#include <vector>
#include "mathObjsRsrcs.h"

using namespace mathObjs;

void printV(const Vector3f& ref)
{
	std::cout << "[ " << ref.x << ", " << ref.y << ", " << ref.z << " ]" << std::endl;
}

void printQ(const Quaternion4f& ref)
{
	std::cout << "[ " << ref.w << ", " << ref.x << ", " << ref.y << ", " << ref.z << " ]" << std::endl;
}

Quaternion4f rPart(const Vector3f& A, const Vector3f& B)
{
	float AB = A.x*B.x + A.y*B.y + A.z*B.z;
	float AA = A.x*A.x + A.y*A.y + A.z*A.z;
	float BB = B.x*B.x + B.y*B.y + B.z*B.z;
	float magAB = sqrt(AA*BB);

	float cosTheta = AB / magAB;

	float w = sqrt((1 + cosTheta) / 2); //cosine of half angle

	Vector3f cross = A * B;
	
	float demon = 2 * w * magAB;

	cross *= (1/demon);

	return Quaternion4f(w, cross);
}

Quaternion4f rPart2(const Vector3f& A, const Vector3f& B)
{
	float AB = A.x*B.x + A.y*B.y + A.z*B.z;
	float AA = A.x*A.x + A.y*A.y + A.z*A.z;
	float BB = B.x*B.x + B.y*B.y + B.z*B.z;
	float magAB = sqrt(AA*BB);

	float cosTheta = AB / magAB;

	float W = sqrt((1 + cosTheta) / 2);
	float n = sqrt((1 - cosTheta) / 2); //cosine of half angle

	Vector3f cross = A * B;

	cross.normalize();
	cross *= n;
	return Quaternion4f(W, cross);
}

float check(const Vector3f& A, const Vector3f& B)
{
	float AA = A.x*A.x + A.y*A.y + A.z*A.z;
	float BB = B.x*B.x + B.y*B.y + B.z*B.z;
	float magAB = sqrt(AA*BB);

	float magA = A.magnitude();
	float magB = B.magnitude();

	return magAB - (magA*magB);
}
int main()
{
	float ex = rand() % 360 - 180;
	int why = rand() % 360 - 180;
	int zed = rand() % 360 - 180;

	Vector3f euler(ex, why, zed);

	int x = rand() % 360 - 180;
	int y = rand() % 360 - 180;
	int z = rand() % 360 - 180;

	Vector3f euler2(x, y, z);

	//lets just multiply over and over again
	Quaternion4f one(degrees, euler);
	Quaternion4f two(degrees, euler2);
	Quaternion4f three;

	std::clock_t start;
	std::clock_t end;

	//for (int i = 0; i < 10; i++)
	//{
	//	start = std::clock();

	//	for (int i = 0; i < 10000000; i++)
	//	{
	//		one.recipricate();
	//	}
	//	end = std::clock();
	//	int numtick = end - start;

	//	start = std::clock();

	//	for (int i = 0; i < 10000000; i++)
	//	{
	//		//one.inlineRecipricate();
	//	}
	//	end = std::clock();
	//	int numtick2 = end - start;

	//	std::cout << "regular " << numtick << "inline " << numtick2 << std::endl;
	//}

	int count0 = 0;
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int count4 = 0;
	int count5 = 0;
	int count6 = 0;

	int num = 10000;

	for (int i = 0; i < num; i++)
	{
		int countThisRound = 0;
		int one = rand() % 2 - 0;
		if (one >= 1) countThisRound++;
		int two = rand() % 2 - 0;
		if (two >= 1) countThisRound++;
		int three = rand() % 2 - 0;
		if (three >= 1) countThisRound++;
		int four = rand() % 2 - 0;
		if (four >= 1) countThisRound++;
		int five = rand() % 2 - 0;
		if (five >= 1) countThisRound++;
		int six = rand() % 2 - 0;
		if (six >= 1) countThisRound++;

		if (countThisRound == 0) count0++;
		else if (countThisRound == 1) count1++;
		else if (countThisRound == 2) count2++;
		else if (countThisRound == 3) count3++;
		else if (countThisRound == 4) count4++;
		else if (countThisRound == 5) count5++;
		else if (countThisRound == 6) count6++;
	}

	float zeroFrac = (float)count0 / (float)num;
	float oneFrac = (float)count1 / (float)num;
	float twoFrac = (float)count2 / (float)num;
	float threeFrac = (float)count3 / (float)num;
	float fourFrac = (float)count4 / (float)num;
	float fiveFrac = (float)count5 / (float)num;
	float sixFrac = (float)count6 / (float)num;

	std::cout << "zero " << zeroFrac << " one " << oneFrac << " two " << twoFrac << " three " << threeFrac << " four " << fourFrac << " five " << fiveFrac << " six " << sixFrac << std::endl;
	system("pause");

	return 0;
}

