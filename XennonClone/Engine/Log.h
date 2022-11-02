#pragma once

/*
* 0 - NO DEBUG
* 1 - DEBUG WITHOUT COLORS
* 2- DEBUG WITH COLORS
*/

#ifndef PONG_DEBUG
	#define PONG_DEBUG 2
#endif

#if PONG_DEBUG == 1
#include <iostream>
#define LOG(x) std::cout << x << std::endl;
#define WARNING(x) std::cout << x << std::endl;
#define ERROR(x) std::cout << x << std::endl;
#elif PONG_DEBUG == 2
#include <iostream>
#include "rlutil.h"
#define LOG(x)\
rlutil::setColor(2);\
std::cout << x << std::endl;\
rlutil::setColor(7);
#define LOG_WARNING(x)\
{\
rlutil::setColor(6);\
std::cout << x << std::endl;\
rlutil::setColor(7);\
}
#define LOG_ERROR(x)\
{\
rlutil::setColor(4);\
std::cout << x << std::endl;\
rlutil::setColor(7);\
}
#elif
#define LOG(x)
#define LOG_WARNING(x)
#define LOG_ERROR(x)
#endif
