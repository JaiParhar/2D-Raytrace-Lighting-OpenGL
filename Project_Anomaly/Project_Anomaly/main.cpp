#include <stdio.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "gfx_render.h"
#include "gfx_utils.h"

#include "lighting.h"

#define WINDOW_NAME "Project_Anomaly"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 786

int init();
void close();

GLFWwindow* window;

int main(int argc, char* args[])
{
	int initErr = init();
	if (initErr)
	{
		return initErr;
	}

	GLuint quadVAO = genBlankQuadVAO();
	GLuint basicShader = loadShaders("shaders/basic.vert", "shaders/basic.frag");

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render and update area -- TODO: make this proper

		glUseProgram(basicShader);
		renderBlankVAO(quadVAO, 6);


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