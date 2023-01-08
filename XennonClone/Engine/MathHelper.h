#pragma once

class MathHelper
{
public:

	static float SquareRoot(float val);

	/* Clamps the given input value. No return value */
	static void ClampIntRef(int& value, const int& min, const int& max)
	{
		if (value < min)
		{
			value = min;
		}
		if (value > max)
		{
			value = max;
		}
	}

	/* Returns the inputed value as clamped (doesn't change the input directly) */
	static int ClampInt(int value, const int& min, const int& max)
	{
		if (value < min)
		{
			value = min;
		}
		if (value > max)
		{
			value = max;
		}
		return value;
	}

	static float ClampFloat(float value, const float& min, const float& max) 
	{	
		if (value < min)
		{
			value = min;
		}
		if (value > max)
		{
			value = max;
		}
		return value;
	}

	static float Clamp01(float value) 
	{
		if (value < 0)
		{
			return 0;
		}
		if (value > 1)
		{
			return 1;
		}
		return value;
	}

	/* Map Clamp Ranged the input value. No return value */
	static void MapClampRangedIntRef(int& value, const int& oldMin, const int& oldMax,
		const int& newMin, const int& newMax)
	{
		float oldRange = (oldMax - oldMin);
		float NewRange = (newMax - newMin);
		value = (((value - oldMin) * NewRange) / oldRange) + newMin;
	}

	/* Returns the absolute result of the given value. (Eg: -5 returns 5 and 5 returns 5)*/
	static int Abs(const int value)
	{
		int inverse = -value;
		return value > inverse ? value : inverse;
		//return value ? value > inverse : inverse;
	}

	/* Swaps two vector elements (pointers) */
	static void SwapVectorElement(int* a, int* b)
	{
		int aux = *a;
		*a = *b;
		*b = aux;
	}

	static int GetRandomInRange(int min, int max);

};