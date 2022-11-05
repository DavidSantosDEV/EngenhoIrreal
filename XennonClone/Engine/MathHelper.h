#pragma once

class MathHelper
{
public:
	static void ClampInt(int& value, const int& min, const int& max)
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

	static void MapClampRangedInt(int& value, const int& oldMin, const int& oldMax, 
		const int& newMin, const int& newMax)
	{
		float oldRange = (oldMax - oldMin);
		float NewRange = (newMax- newMin);
		value = (((value- oldMin) * NewRange) / oldRange) + newMin;
	}
};
