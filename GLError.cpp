#include "GLError.h"

void GLClearErrors(void) {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogErrors(std::string fct, std::string fileName, int lineNumber) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpengGL Error] <" << error << "> at function " << fct << " in " << fileName << " : " << lineNumber << std::endl;
		return false;
	}
	return true;
}