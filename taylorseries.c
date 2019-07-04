#include<stdbool.h>

#include"memoizationfactorials.h"
#include"taylorseries.h"

factorials facs;

// --------------------------------------------------------
// FUNCTION taylor_init
// --------------------------------------------------------
bool taylor_init(int degree)
{
    return factorials_calculate(&facs, degree);
}

// --------------------------------------------------------
// FUNCTION taylor_free
// --------------------------------------------------------
void taylor_free()
{
    factorials_free(&facs);
}

// --------------------------------------------------------
// FUNCTION taylor_sin_rad
// --------------------------------------------------------
double taylor_sin_rad(double radians, int degree)
{
    int multiplier = -1.0;
    double sine = radians;

    for(int currentdegree = 3; currentdegree <= degree; currentdegree += 2)
    {
        sine += ((pow(radians, currentdegree) / facs.calculated[currentdegree]) * multiplier);

        multiplier *= -1;
    }

    return sine;
}

// --------------------------------------------------------
// FUNCTION taylor_cos_rad
// --------------------------------------------------------
double taylor_cos_rad(double radians, int degree)
{
    return taylor_sin_rad(radians - (90 / DEGREES_IN_RADIAN), degree + 1);
}
