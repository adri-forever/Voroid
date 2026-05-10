#ifndef Game_h
#define Game_h

//SDL
#include <SDL3/SDL.h>

//std
#include <iostream>
#include <vector>

//OpenGL
#include "glad/glad.h"
#include "glm/glm.hpp"

//Project classes
#include "Vorender.h"
#include "utils/glUtils.h"

const size_t totsize = 64;

class Game {
private:

public:
	Game();
	~Game();

	SDL_Window* window;

	static Vorender glRenderer;
	static std::vector<SDL_Event> events;

	bool relativeState = false;
	bool isRunning = false;
	glm::ivec2 windowSize;
	float aspect;

	int age = 0; //Age in frames

	GLuint vao; // Dummy vao

	// Voro
	glm::vec2 nodes[totsize];
	glm::vec3 regioncolors[totsize];
	int size = 0;

	float pointradius = .01f;
	float frontierwidth = .01f;
	glm::vec3 pointcolor = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 frontiercolor = glm::vec3(.1f, .1f, .1f);

	void addnode(float x, float y);

	void init(const char* title, int width, int height, SDL_WindowFlags flags);
	void clean();

	void handleEvents();
	void update(int framelength);
	void render();
	
	void toggleCursor();
	void toggleCursor(bool state);
	//also lock mouse in the window when hidden

};

#endif //Game_h