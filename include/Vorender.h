#ifndef VORENDER_H
#define VORENDER_H

#include <string>

#include "glad/glad.h"

#include <SDL3/SDL.h>

class Vorender {
public:
	Vorender();
	~Vorender();

	SDL_GLContext glContext;
	GLuint shaderProgram;
	
	void init(SDL_GLContext context);
	void use() const;
	void render();

	GLuint getLocation(const std::string& name) const;

	void setMat4(const std::string& name, const float* mat) const;
};

#endif // !VORENDER_H
