#include "gfx_render.h"

void renderBlankVAO(GLuint VAO_ID, GLuint num_vertices)
{
	glBindVertexArray(VAO_ID);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, num_vertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void renderTexturedVAO(GLuint VAO_ID, GLuint num_vertices)
{
	glBindVertexArray(VAO_ID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, num_vertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}