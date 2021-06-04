#include "GLRenderSystem.h"

void GLRenderSystem::init()
{
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void GLRenderSystem::setViewport(double x, double y, double width, double height)
{
	glViewport(x, y, width, height);
}

void GLRenderSystem::clearDisplay(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderSystem::renderTriangleSoup(const std::vector <Vertex>& vertices)
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i++) 
	{
		glVertex3f(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z);
	}
	glEnd();
}

void GLRenderSystem::setupLight(uint32_t index, glm::vec3 position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is)
{
	int indexl = 16384 + index;
	if (lightCount < 8)
	{
		glLightfv(indexl, GL_POSITION, glm::value_ptr(position));
		glLightfv(indexl, GL_AMBIENT, glm::value_ptr(Ia));
		glLightfv(indexl, GL_DIFFUSE, glm::value_ptr(Id));
		glLightfv(indexl, GL_SPECULAR, glm::value_ptr(Is));
		lightCount++;
	}
}

void GLRenderSystem::turnLight(uint32_t index, bool enable)
{
	int indexl = 16384 + index;
	if (enable) 
	{
		glEnable(indexl);
	}
	else
	{
		glDisable(indexl);
	}
}

void GLRenderSystem::setWorldMatrix(const glm::mat4& matrix)
{
	WorldMatrix = matrix;
}


glm::mat4 GLRenderSystem::getWorldMatrix()
{
	return WorldMatrix;
}


void GLRenderSystem::setViewMatrix(const glm::mat4& matrix)
{
	ViewMatrix = matrix;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(ViewMatrix * ModelMatrix));
}


glm::mat4& GLRenderSystem::getViewMatrix()
{
	return ViewMatrix;
}

void GLRenderSystem::setProjMatrix(const glm::mat4& matrix)
{
	ProjMatrix = matrix;
 	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(ProjMatrix));

}

glm::mat4& GLRenderSystem::getProjMatrix()
{
	return ProjMatrix;
}

void GLRenderSystem::setupPointLight(uint32_t index, glm::vec3 position, glm::vec3 def, float Const, float Linear, float Quadratic)
{
	int indexl = 16384 + index;
	if (lightCount < 8)
	{
		glLightfv(indexl, GL_DIFFUSE, glm::value_ptr(def));
		glLightfv(indexl, GL_POSITION, glm::value_ptr(position));
		glLightf(indexl, GL_CONSTANT_ATTENUATION, Const);
		glLightf(indexl, GL_LINEAR_ATTENUATION, Linear);
		glLightf(indexl, GL_QUADRATIC_ATTENUATION, Quadratic);
		lightCount++;
	}
}

void GLRenderSystem::setupSpotLight(uint32_t index, glm::vec3 Pos, glm::vec3 Direction, glm::vec3 Diffuse,
	float Cutoff, float Exponent)
{
	int indexl = 16384 + index;
	if (lightCount < 8)
	{
		glLightfv(indexl, GL_DIFFUSE, glm::value_ptr(Diffuse));
		glLightfv(indexl, GL_POSITION, glm::value_ptr(Pos));
		glLightfv(index, GL_SPOT_DIRECTION, glm::value_ptr(Direction));
		glLightf(indexl, GL_SPOT_CUTOFF, Cutoff);
		glLightf(indexl, GL_SPOT_EXPONENT, Exponent);
		lightCount++;
	}
}

void GLRenderSystem::phongMaterial()
{
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr((glm::vec4(0.9, 0.9, 0.9, 1.0))));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.9, 0.9, 0.9, 1.0)));
	glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(glm::vec4(0.8, 0.8, 0.8, 1.0)));
	glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(glm::vec4(0.4, 0.4, 0.4, 0.4)));
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
}

GLRenderSystem::GLRenderSystem()
{
}

GLRenderSystem::~GLRenderSystem()
{
}