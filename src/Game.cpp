#include "Game.h"

#include "toolbox.h"

Vorender Game::glRenderer;
std::vector<SDL_Event> Game::events;

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int width, int height, SDL_WindowFlags flags) {
	if (!SDL_Init(0)) {
		std::cout << "System initialization error: " << SDL_GetError() << std::endl;
		isRunning = false;
	} else {
		std::cout << "Systems initialized" << std::endl;
		
		windowSize = glm::ivec2(width, height);
		aspect = (float)width/(float)height;
		window = SDL_CreateWindow(title, width, height, flags);
		
		if (window) {
			std::cout << "Window created" << std::endl;
			//SDL_WindowFlags windowFlags = SDL_GetWindowFlags(window);
			//std::cout << "Requested flags: " << windowFlags << std::endl;
		}
		 
		if ((flags & SDL_WINDOW_OPENGL) != 0) {
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

			SDL_GLContext glContext = SDL_GL_CreateContext(window);
			if (glContext) {
				std::cout << "OpenGL context created" << std::endl;
			} else {
				std::cout << "OpenGL context creation error: " << SDL_GetError() << std::endl;
			}
			SDL_GL_SetSwapInterval(1); //VSync

			SDL_GL_MakeCurrent(window, glContext);
			
			if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
				std::cout << "GLAD loading error: " << SDL_GetError() << std::endl;
			}

			glRenderer.init(glContext);
		} else {
			std::cout << "OpenGL not requested" << std::endl;
		}

		isRunning = true;

		//std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

		toggleCursor(relativeState); //sync without changing

		// Bind dummy vao
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Initialize points
		for (size_t i=0; i<totsize; i++) {
			nodes[i] = glm::vec2(0.f, 0.f);
			regioncolors[i] = glm::vec3(1.f, 1.f, 1.f);
		}

		for (size_t i=0; i<25; i++) {
			addnode(random01(), random01());
		}
		// addnode(.5f, .5f);
		// addnode(.25f, .5f);
		// addnode(.5f, .25f);
		// addnode(.75f, .5f);
		// addnode(.5f, .75f);
		// addnode(.9f, .9f);
	}
}

void Game::addnode(float x, float y) {
	// Register positions
	nodes[size].x = x;
	nodes[size].y = y;

	// Generate color
	float hue = random01();
	glm::vec3 hsl = glm::vec3(hue, .9f, .6f);
	glm::vec3 rgb = hsl_to_rgb(hsl);
	// std::cout << hsl << ", " << rgb << std::endl;
	regioncolors[size] = rgb;

	// Increment active size
	size++;
}

void Game::handleEvents() {
	SDL_Event event;	
	std::string message;
	//Clear events vector
	events.clear();

	// std::cout<<"Newframe"<<std::endl;
	while (SDL_PollEvent(&event)) {
		events.push_back(event); //Sends events to registered list for entities to process
		// std::cout<<"polling event "<<event.type<<std::endl;
		
		//Still handle program wide events
		switch (event.type) {
			case SDL_EVENT_QUIT:
				isRunning = false;
				break;

			case SDL_EVENT_WINDOW_RESIZED:
				windowSize = glm::ivec2(event.window.data1, event.window.data2);
				glViewport(0, 0, windowSize.x, windowSize.y); //Synchronize OpenGL viewport size
				aspect = (float)windowSize.x / (float)windowSize.y;
				std::cout << "Window resized to " << windowSize << std::endl;
				break;

			case SDL_EVENT_KEY_DOWN:
				switch (event.key.key) {
				case SDLK_ESCAPE:
					isRunning = false;
					break;
				case SDLK_TAB:
					toggleCursor();
					break;
				default:
					break;
				}
			default:
				break;
		}
	}
}

void Game::update(int framelength) {
	age++;

	// printf("Frame number: %d\n", age);
}

void Game::render() {
	//Set empty color & clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glRenderer.use();

	glBindVertexArray(vao);

	// glUniform1f(glGetUniformLocation(glRenderer.shaderProgram, "time"), (GLfloat)age/(GLfloat)60.f);

	glUniform1f(glRenderer.getLocation("aspect"), aspect);
	glUniform2fv(glRenderer.getLocation("nodes"), totsize, &nodes[0].x);
	glUniform3fv(glRenderer.getLocation("regioncolors"), totsize, &regioncolors[0].x);
	glUniform1i(glRenderer.getLocation("size"), size);
	glUniform1f(glRenderer.getLocation("pointradius"), pointradius);
	glUniform1f(glRenderer.getLocation("frontierwidth"), frontierwidth);
	glUniform3f(glRenderer.getLocation("pointcolor"), pointcolor.x, pointcolor.y, pointcolor.z);
	glUniform3f(glRenderer.getLocation("frontiercolor"), frontiercolor.x, frontiercolor.y, frontiercolor.z);


// Nodes
// uniform vec2 nodes[64];
// uniform vec3 regioncolors[64];
// uniform int size;

// // Drawing properties
// uniform float pointradius;
// uniform float frontierwidth;
// uniform vec3 pointcolor;
// uniform vec3 frontiercolor;

	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(window);
}

void Game::clean() {
	/*glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &VAO);*/

	SDL_DestroyWindow(window);
	//SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Travail termine !" << std::endl;
}

void Game::toggleCursor() {
	toggleCursor(!relativeState);
}

void Game::toggleCursor(bool state) {
	SDL_SetWindowRelativeMouseMode(window, state);
	SDL_WarpMouseInWindow(window, windowSize.x/2, windowSize.y/2);

	relativeState = state;
}