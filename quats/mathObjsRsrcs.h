#ifndef MATHOBJSRSRCS_H
#define MATHOBJSRSRCS_H

namespace mathObjs
{
	const float DegreesToRadians = 0.0174532925199433f; //if you need angles in degrees
	const float sqrt2over2 = 0.707106781186548f;

	//so many options
	enum TaitBryanType{ ZYX, ZXZ, ZYXqat }; //ZYXqat is the way I do it. CHECKS OUT
	enum angleType{ radians, degrees };

	struct pair
	{
		float a, b; //b is imaginary part
	};
}

#endif