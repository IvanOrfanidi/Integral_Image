#pragma once

#include <iostream>

#define MSG(msg) std::cout << msg << std::endl

#define ERR_MSG(msg) std::cerr << msg << std::endl

#ifndef NDEBUG
#define DEB_MSG(msg) std::cout << msg << std::endl
#else
#define DEB_MSG(msg)
#endif