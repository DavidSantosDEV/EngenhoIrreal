#include "MathHelper.h"
#include <cmath>
#include <random>
#include <time.h>

float MathHelper::SquareRoot(float val)
{
    return sqrt(val);
}

int MathHelper::GetRandomInRange(int min, int max)
{
    srand(time(NULL));
    return (rand() % max + min);
}
