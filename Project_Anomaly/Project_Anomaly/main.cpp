#include <stdio.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "gfx_render.h"
#include "gfx_utils.h"

#include "lighting.h"

#define WINDOW_NAME "Project_Anomaly"

#define WINDOW_WIDTH 2048
#define WINDOW_HEIGHT 1572

int init();
void close();

GLFWwindow* window;

LightMap lm;

int main(int argc, char* args[])
{
	int initErr = init();
	if (initErr)
	{
		return initErr;
	}


	lm.walls.push_back(seg2(-0.75, 0, -0.75, 0.5));
	lm.walls.push_back(seg2(0.75, 0.64, 0.75, 0.5));

	lm.walls.push_back(seg2(-0.75, -0.75, -0.75, -0.5));
	lm.walls.push_back(seg2(-0.75, -0.5, -0.95, -0.5));
	lm.walls.push_back(seg2(-0.75, -0.75, -0.95, -0.75));


	// TODO - LIGHTING
	// MAKE A SINGLE VAO FOR THE LIGHTING TRIS, THEN JUST UPDATE THE VERTEX DATA FOR IT
	GLuint lightingVAO = genVAO();
	glBindVertexArray(lightingVAO);
	GLuint lightingVBO = genVBO();
	storeVBOData(lightingVBO, 0, QUAD_VERTEX_DATA, sizeof(QUAD_VERTEX_DATA));
	
	GLfloat TEST_DATA[] = {
	-0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,

	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
	};

	GLuint basic_shader = loadShaders("shaders/basic.vert", "shaders/basic.frag");
	
	double mX, mY;
	glfwGetCursorPos(window, &mX, &mY);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render and update area -- TODO: make this proper

		glfwGetCursorPos(window, &mX, &mY);

		std::vector<Triangle> lightingTris = getVisionTris(lm,
			glm::vec2(float(2 * (mX - WINDOW_WIDTH / 2) / (WINDOW_WIDTH)), 
				float(-2 * (mY - WINDOW_HEIGHT / 2) / (WINDOW_HEIGHT))),
			glm::vec2(0, 0), 2.0f, 2.0f);
		std::vector<GLfloat> meshData = trisToMeshData(lightingTris);
		storeVBOData(lightingVBO, 0, meshData.data(), meshData.size() * sizeof(GLfloat));


		glUseProgram(basic_shader);

		renderBlankVAO(lightingVAO, lightingTris.size() * 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	close();
	return 0;
}

int init()
{
	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW.\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Needed only for macOS
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use modern OpenGL 

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW.\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	return 0;
}

void close()
{

}