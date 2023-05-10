#include <GL/glew.h>

#include <iostream>

class Debugger {

#define ASSERT(x) if (!(x)) __debugbreak();

};
