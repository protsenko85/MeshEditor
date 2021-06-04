#pragma once
#include <glad/glad.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glfw/glfw3.h>
#include <glut.h>
#include <vector>
#include "Camera.h"
using namespace std;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

class GLRenderSystem
{
public:
	GLRenderSystem();
	~GLRenderSystem();
	void init();
	void clearDisplay(float r, float g, float b);
	void setViewport(double x, double y, double width, double height);
	void turnLight(uint32_t index, bool enable);
	void renderTriangleSoup(const std::vector <Vertex>& vertices);
	void setWorldMatrix(const glm::mat4& matrix);
	glm::mat4 getWorldMatrix();
	void setupLight(uint32_t index, glm::vec3 position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is);
	void setupPointLight(uint32_t index, glm::vec3 position, glm::vec3 def, float Const, float Linear, float Quadratic);
	void setupSpotLight(uint32_t index, glm::vec3 Pos, glm::vec3 Direction, glm::vec3 Diffuse, float Cutoff, float Exponent);
	void setViewMatrix(const glm::mat4& matrix);
	glm::mat4& getViewMatrix();
	void setProjMatrix(const glm::mat4& matrix);
	glm::mat4& getProjMatrix();

	void phongMaterial();
private:
	glm::mat4 WorldMatrix = glm::mat4(1.0f);
	glm::mat4 ViewMatrix = glm::mat4(0.0f);
	glm::mat4 ProjMatrix = glm::mat4(0.0f);
	glm::mat4 ModelMatrix = glm::mat4(1.0f);
	int lightCount = 0;
};

