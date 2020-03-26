#ifndef GLERROR_H
#define GLERROR_H

#include <glad/glad.h>
#include <iostream>
#include <string>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearErrors();x;ASSERT(GLLogErrors(#x, __FILE__, __LINE__));
void GLClearErrors(void);
bool GLLogErrors(std::string fct, std::string fileName, int lineNumber);

#endif