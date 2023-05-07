#pragma once
#include <string>

namespace ShaderDrawUtil
{

    void Draw(float *positions, unsigned int length);
    void DrawWithIndices(float *positions, unsigned int posLen, unsigned int *indices, unsigned int indLen);
}
