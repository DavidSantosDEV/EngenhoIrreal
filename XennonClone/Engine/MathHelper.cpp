#include "MathHelper.h"
#include <cmath>
#include <random>

float MathHelper::SquareRoot(float val)
{
    return sqrt(val);
}

int MathHelper::GetRandomInRange(int min, int max)
{
    return (rand() % max + min);
}
