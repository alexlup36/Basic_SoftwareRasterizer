#pragma once
#include <intrin.h>

// Small value used to compare float numbers
#define EPSILON (float)(1E-3)
// Compare floats macro
#define FCMP(a,b) ( (fabs(a-b) < EPSILON) ? 1 : 0)

class Util
{
public:
	Util(void);
	~Util(void);

	static int FloatToInt_SSE(float x);
	static float PI;
};



