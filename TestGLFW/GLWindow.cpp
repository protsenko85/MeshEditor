#include "GLWindow.h"
#include <iostream>

GLWindow::GLWindow(const std::string& title, uint32_t width, uint32_t height) : width(width), height(height)
{
	handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
	glfwMakeContextCurrent(handle);
	static bool initGLAD = false;
	if (!initGLAD)
	{
		initGLAD = true;
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
	glfwSetWindowUserPointer(handle, this);

	glfwSetKeyCallback(handle, [](GLFWwindow* handle, int key, int scancode, int action, int mode)
	{
		((GLWindow*)glfwGetWindowUserPointer(handle))->getKeyCallback()((KeyCode)key, (Action)action, (Modifier)mode);
	});

	glfwSetCursorPosCallback(handle, [](GLFWwindow* handle, double x, double y)
	{
		((GLWindow*)glfwGetWindowUserPointer(handle))->getCursorCallback()(x, y);
	});

	glfwSetMouseButtonCallback(handle, [](GLFWwindow* handle, int btn, int action, int mode)
	{
		((GLWindow*)glfwGetWindowUserPointer(handle))->getMouseCallback()((ButtonCode)btn, (Action)action, (Modifier)mode);
	});

	glfwSetScrollCallback(handle, [](GLFWwindow* handle, double x, double y)
	{
		((GLWindow*)glfwGetWindowUserPointer(handle))->getScrollCallback()(x, y);
	});
}

GLWindow::~GLWindow()
{
	glfwDestroyWindow(handle);
}

uint32_t GLWindow::getWidth() const
{
	return width;
}

uint32_t GLWindow::getHeight() const
{
	return height;
}

void GLWindow::setKeyCallback(const KeyCallback& callback)
{
	keyCallBack = callback;
}

GLWindow::KeyCallback GLWindow::getKeyCallback() const
{
	return keyCallBack;
}

GLWindow::MouseCallback GLWindow::getMouseCallback() const
{
	return mouseCallback;
}

GLWindow::CursorPosCallback GLWindow::getCursorCallback() const
{
	return cursorCallback;
}

GLWindow::ScrollCallback GLWindow::getScrollCallback() const
{
	return scrollCallback;
}

void GLWindow::setCursorPosCallback(const CursorPosCallback& callback)
{
	cursorCallback = callback;
}

void GLWindow::setMouseCallback(const MouseCallback& callback)
{
	mouseCallback = callback;
}

void GLWindow::setScrollCallback(const ScrollCallback& callback)
{
	scrollCallback = callback;
}

GLFWwindow* GLWindow::getGLFWHandle() const
{
	return handle;
}

