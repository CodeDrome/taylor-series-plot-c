
#include<stdbool.h>

#define PI 3.141592654
#define DEGREES_IN_RADIAN (180.0 / PI)

// --------------------------------------------------------
// FUNCTION PROTOTYPES
// --------------------------------------------------------
bool taylor_init(int degree);
void taylor_free();
double taylor_sin_rad(double radians, int degree);
double taylor_cos_rad(double radians, int degree);
