#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H

#pragma warning( disable : 4290 )

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm/glm.hpp>

#include "Camera.h"

class GlfwWindow {
private:
	GLFWwindow* window = nullptr;
	std::string name;
	int screenWidth, screenHeight;
	bool isFullscreen;
	Camera* camera;
	glm::vec2 lastMousePos = glm::vec2(0.0f, 0.0f);
	bool mousePosInitialized = false;
	bool captureMouse = false;
	void initializeGlad(void) throw(std::string);
	void initializeWindow(void) throw(std::string);

public:
	GlfwWindow(int width, int height, std::string windowName, bool fullscreen, Camera* cam) throw(std::string);
	~GlfwWindow();

	Camera* getCamera(void) const;
	bool isMouseInitialized(void) const;
	void setMouseInitialized(bool b);
	glm::vec2 getLastMousePos(void) const;
	void setLastMousePos(glm::vec2 newPos);
	bool isMouseCaptured(void) const;
	void toggleCaptureMouse(void);

	void stop(void);
	bool shouldStop(void) const;
	void setDisplayWindow(void);
	void swapBuffers(void);
	void lookForEvents(void);
	void processEvents(void);
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif