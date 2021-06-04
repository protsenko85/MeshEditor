#pragma once
#include <glad/glad.h>
#include <iostream>
#include "GLWindow.h"
#define GLFW_INCLUDE_NONE
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLRenderSystem.h"
#include "Camera.h"
#include <vector>
#include "Viewport.h"

GLRenderSystem rs;
Camera c;
Viewport viewport;

std::vector <Vertex> Cube = {
{ {0.0, 0.0,  0.0}, {0, 0, 0}},
{ { 1.0, 0.0,  0.0}, {0, 0, 0}},
{ {0.0, 1.0, 0.0}, {0, 0, 0}},

{ {1.0, 0.0,  0.0}, {0, 0, 0}},
{ {1.0, 1.0,  0.0}, {0, 0, 0}},
{ {0.0, 1.0, 0.0}, {0, 0, 0}},

{ {0.0, 0.0,  0.0}, {0, 0, 0}},
{ {0.0, 0.0,  1.0}, {0, 0, 0}},
{ {1.0, 0.0,  1.0}, {0, 0, 0}},

{ {0.0, 0.0,  0.0}, {0, 0, 0}},
{ {1.0, 0.0,  0.0}, {0, 0, 0}},
{ {1.0, 0.0,  1.0}, {0, 0, 0}},

{ {0.0, 0.0,  0.0}, {0, 0, 0}},
{ {0.0, 0.0,  1.0}, {0, 0, 0}},
{ {0.0, 1.0,  1.0}, {0, 0, 0}},

{ {0.0, 0.0,  0.0}, {0, 0, 0}},
{ {0.0, 1.0,  0.0}, {0, 0, 0}},
{ {0.0, 1.0,  1.0}, {0, 0, 0}},

{ {0.0, 0.0,  1.0}, {0, 0, 0}},
{ {1.0, 0.0,  1.0}, {0, 0, 0}},
{ {0.0, 1.0,  1.0}, {0, 0, 0}},

{ {1.0, 0.0,  1.0}, {0, 0, 0}},
{ {1.0, 1.0,  1.0}, {0, 0, 0}},
{ {0.0, 1.0,  1.0}, {0, 0, 0}},

{ {0.0, 1.0,  0.0}, {0, 0, 0}},
{ {0.0, 1.0,  1.0}, {0, 0, 0}},
{ {1.0, 1.0,  1.0}, {0, 0, 0}},

{ {0.0, 1.0,  0.0}, {0, 0, 0}},
{ {1.0, 1.0,  0.0}, {0, 0, 0}},
{ {1.0, 1.0,  1.0}, {0, 0, 0}},

{ {1.0, 0.0,  0.0}, {0, 0, 0}},
{ {1.0, 0.0,  1.0}, {0, 0, 0}},
{ {1.0, 1.0,  1.0}, {0, 0, 0}},

{ {1.0, 0.0,  0.0}, {0, 0, 0}},
{ {1.0, 1.0,  0.0}, {0, 0, 0}},
{ {1.0, 1.0,  1.0}, {0, 0, 0}}, };

void moveCube(GLRenderSystem& rs, glm::vec3 offset)
{
	rs.setViewMatrix(glm::translate(rs.getViewMatrix(), offset));
}

void moveCamera(Camera& camera, glm::vec3 offset)
{
	camera.translate(offset);
}

void renderScene(GLRenderSystem& rs)
{
	rs.renderTriangleSoup(Cube);
}

int main()
{
	glfwInit();
	GLWindow window("myWindow", 1920, 1080);

	double xpos, ypos; // mouse pos
	double u0, v0; // pan mouse pos
	bool isLeftMouseButtonPressed = false; // is LMB pressed
	glm::vec3 a, b; // orbit mouse pos
	bool isRightMouseButtonPressed = false; // is RMB pressed

	window.setKeyCallback([&](KeyCode key, Action action, Modifier mods)
		{
			if (key == KeyCode::Key_W && action == Action::Press)
				moveCamera(viewport.getCamera(), { 0, -1, 0 });

			if (key == KeyCode::Key_S && action == Action::Press)
				moveCamera(viewport.getCamera(), { 0,1,0 });

			if (key == KeyCode::Key_D && action == Action::Press)
				moveCamera(viewport.getCamera(), { -1,0,0 });

			if (key == KeyCode::Key_A && action == Action::Press)
				moveCamera(viewport.getCamera(), { 1,0,0 });

			if (key == KeyCode::Escape)
				glfwSetWindowShouldClose(window.getGLFWHandle(), GL_TRUE);

			if (key == KeyCode::Up)
				moveCube(rs, { 0, 0.1, 0 });

			if (key == KeyCode::Down)
				moveCube(rs, { 0, -0.1, 0 });

			if (key == KeyCode::Left)
				moveCube(rs, { 0.1, 0, 0 });

			if (key == KeyCode::Right)
				moveCube(rs, { -0.1, 0, 0 });


			if (key >= (KeyCode)290 && key <= (KeyCode)296 && action == Action::Press)
			{
				switch ((int)key)
				{
				case 290:
					viewport.getCamera().setFrontView();
					break;
				case 291:
					viewport.getCamera().setRearView();
					break;
				case 292:
					viewport.getCamera().setTopView();
					break;
				case 293:
					viewport.getCamera().setBottomView();
					break;
				case 294:
					viewport.getCamera().setLeftView();
					break;
				case 295:
					viewport.getCamera().setRightView();
					break;
				case 296:
					viewport.getCamera().setIsoView();
					break;
				}
			}

			if (key == KeyCode::Key_F8 && action == Action::Press)
			{
				if (viewport.isParallelProjection())
					viewport.setParallelProjection(false);
				else
					viewport.setParallelProjection(true);
			}
		});

	window.setCursorPosCallback([&](double x, double y)
		{
			xpos = x;
			ypos = y;
			if (isLeftMouseButtonPressed)
			{
				xpos = xpos - (window.getWidth() - xpos);
				ypos = ypos - (window.getHeight() - ypos);

				double du = u0 - xpos;
				double dv = v0 - ypos;
				viewport.getCamera().pan(du / 200, -dv / 200);
				u0 = xpos;
				v0 = ypos;
			}
			else if (isRightMouseButtonPressed)
			{
				b.x = xpos / viewport.getHeight() - (viewport.calcAspectRatio() - xpos / viewport.getHeight());
				ypos = ypos - (viewport.getHeight() - ypos);
				b.y = -ypos / viewport.getHeight();

				if (glm::length(b) >= 1.0f)
					b = glm::normalize(b);
				else
					b.z = sqrt(1.0 - pow(b.x, 2) - pow(b.y, 2));

				viewport.getCamera().orbit(a, b);
				a = b;
			}
		});

	window.setMouseCallback([&](ButtonCode btn, Action action, Modifier mods)
		{
			if (btn == ButtonCode::Button_0)
			{
				if (action == Action::Press)
				{
					u0 = xpos - (window.getWidth() - xpos);
					v0 = ypos - (window.getHeight() - ypos);
					isLeftMouseButtonPressed = true;
				}
				else if (action == Action::Release)
				{
					isLeftMouseButtonPressed = false;
				}
			}
			if (btn == ButtonCode::Button_1)
			{
				if (action == Action::Press)
				{
					a.x = xpos / viewport.getHeight() - (viewport.calcAspectRatio() - xpos / viewport.getHeight());
					ypos = ypos - (viewport.getHeight() - ypos);
					a.y = -ypos / viewport.getHeight();

					if (glm::length(a) >= 1.0)
						a = glm::normalize(a);
					else
						a.z = sqrt(1.0 - pow(a.x, 2) - pow(a.y, 2));

					isRightMouseButtonPressed = true;
				}
				else if (action == Action::Release)
				{
					isRightMouseButtonPressed = false;
				}
			}
		});

	window.setScrollCallback([&](double x, double y)
		{
			if (y >= 1)
				viewport.getCamera().zoom(y - 0.1);
			else
				viewport.getCamera().zoom(y + 2.1);
		});

	rs.init();
	rs.phongMaterial();
	while (!glfwWindowShouldClose(window.getGLFWHandle()))
	{
		rs.setupLight(0, { 0., 0., 50. }, { 7., 0., 0. }, { 5., 1., 0. }, { 1., 1., 1. });
		rs.turnLight(0, true);

		rs.setViewport(0, 0, window.getWidth(), window.getHeight());
		rs.clearDisplay(0.5f, 0.5f, 0.5f);

		rs.setViewMatrix(viewport.getCamera().calcViewMatrix());
		rs.setProjMatrix(viewport.calcProjectionMatrix());
		renderScene(rs);

		glfwSwapBuffers(window.getGLFWHandle());
		glfwWaitEvents();
	}
	glfwTerminate();
	return 0;
}