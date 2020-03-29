#include "GlfwWindow.h"

GlfwWindow::GlfwWindow(int width, int height, std::string windowName, bool fullscreen, Camera* cam) throw(std::string) : screenWidth(width), screenHeight(height), name(windowName), isFullscreen(fullscreen), camera(cam) {
	try {
		initializeWindow();
		setDisplayWindow();
		glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallback);
		glfwSetCursorPosCallback(this->window, mouse_callback);
		glfwSetScrollCallback(this->window, scroll_callback);
		glfwSetKeyCallback(this->window, key_callback);
		initializeGlad();
		glfwSetWindowUserPointer(this->window, this);
	}
	catch (std::string& e) {
		glfwDestroyWindow(window);
		throw e;
	}
}

GlfwWindow::~GlfwWindow(){
	glfwDestroyWindow(window);
	glfwTerminate();
}

Camera* GlfwWindow::getCamera(void) const {
	return this->camera;
}

bool GlfwWindow::isMouseInitialized(void) const {
	return this->mousePosInitialized;
}

void GlfwWindow::setMouseInitialized(bool b) {
	this->mousePosInitialized = b;
}

glm::vec2 GlfwWindow::getLastMousePos(void) const {
	return this->lastMousePos;
}

void GlfwWindow::setLastMousePos(glm::vec2 newPos) {
	this->lastMousePos = newPos;
}

bool GlfwWindow::isMouseCaptured(void) const {
	return this->captureMouse;
}

void GlfwWindow::toggleCaptureMouse(void) {
	this->captureMouse = !this->captureMouse;
	glfwSetInputMode(this->window, GLFW_CURSOR, this->captureMouse ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool GlfwWindow::areAxisXYZDisplayed(void) const {
	return this->axisXYZShown;
}

void GlfwWindow::toggleAxisXYZ(void) {
	this->axisXYZShown = !this->axisXYZShown;
}

void GlfwWindow::initializeGlad(void) throw(std::string) {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::string("Failed to initialize GLAD");
	}
}

void GlfwWindow::initializeWindow(void) throw(std::string) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (this->isFullscreen) {
		this->window = glfwCreateWindow(this->screenWidth, this->screenHeight, this->name.c_str(), glfwGetPrimaryMonitor(), NULL);
	}
	else {
		this->window = glfwCreateWindow(this->screenWidth, this->screenHeight, this->name.c_str(), NULL, NULL);
	}

	if (window == NULL) {
		glfwTerminate();
		throw std::string("Failed to create GLFW window");
	}
}

void GlfwWindow::stop(void) {
	glfwSetWindowShouldClose(this->window, true);
}

bool GlfwWindow::shouldStop(void) const {
	return glfwWindowShouldClose(window);
}

void GlfwWindow::setDisplayWindow(void) {
	glfwMakeContextCurrent(window);
}

void GlfwWindow::swapBuffers(void) {
	glfwSwapBuffers(this->window);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void GlfwWindow::lookForEvents(void) {
	glfwPollEvents();
}

#include <glm/glm/gtx/string_cast.hpp>
void GlfwWindow::processEvents(void) {
	float cameraSpeed = camera->getVelocity();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		glm::vec3 cameraDir = this->camera->getDirection();
		this->camera->move(glm::normalize(glm::vec3(cameraDir.x, cameraDir.y, 0.0f)) * cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		glm::vec3 cameraDir = this->camera->getDirection();
		this->camera->move(-glm::normalize(glm::vec3(cameraDir.x, cameraDir.y, 0.0f)) * cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		this->camera->move(glm::vec3(-this->camera->getRightVector()) * cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		this->camera->move(glm::vec3(this->camera->getRightVector()) * cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		this->camera->move(glm::vec3(0.0f, 0.0f, 1.0f) * cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		this->camera->move(glm::vec3(0.0f, 0.0f, -1.0f) * cameraSpeed);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	GlfwWindow* windowHandler = reinterpret_cast<GlfwWindow*> (glfwGetWindowUserPointer(window));
	if (!windowHandler->isMouseInitialized()) {
		windowHandler->setLastMousePos(glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos)));
		windowHandler->setMouseInitialized(true);
	}
	if (windowHandler->isMouseCaptured()) {
		glm::vec2 lastMousePos = windowHandler->getLastMousePos();
		float offsetX = static_cast<float>(xpos) - lastMousePos.x;
		if (offsetX != 0) {
			windowHandler->getCamera()->selfRotate(windowHandler->getCamera()->getRotationSensitivity() * -offsetX, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		/*float offsetY = static_cast<float>(ypos) - lastMousePos.y;
		if (offsetY != 0) {
			windowHandler->getCamera()->selfRotate(windowHandler->getCamera()->getRotationSensitivity() * -offsetY, windowHandler->getCamera()->getRightVector());
			std::cout << glm::to_string(windowHandler->getCamera()->getRightVector()) << std::endl;
		}*/
		windowHandler->setLastMousePos(glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos)));
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	GlfwWindow* windowHandler = reinterpret_cast<GlfwWindow*> (glfwGetWindowUserPointer(window));
	if (yoffset < 0) {
		windowHandler->getCamera()->setVelocity(windowHandler->getCamera()->getVelocity() / 1.5f);
	}
	else {
		windowHandler->getCamera()->setVelocity(windowHandler->getCamera()->getVelocity() * 1.5f);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	GlfwWindow* windowHandler = reinterpret_cast<GlfwWindow*> (glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
		std::cout << glm::to_string(windowHandler->getCamera()->getPosition()) << std::endl;

	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		windowHandler->toggleCaptureMouse();
		windowHandler->setMouseInitialized(false);
	}
	if ((key == GLFW_KEY_1 || key == GLFW_KEY_KP_1) && action == GLFW_PRESS) {
		windowHandler->toggleAxisXYZ();
	}
}