#include "StdAfx.h"
#include "Util.h"

float Util::PI =  3.14159265f;

Util::Util(void)
{
}


Util::~Util(void)
{
}

int Util::FloatToInt_SSE(float x)
{
    return _mm_cvt_ss2si( _mm_load_ss(&x) );
}

