#include "Vorender.h"

#include "utils/glUtils.h"

#include <string>
#include <fstream>

// #include <direct.h>

std::string loadShaderFile(const std::string& filepath);

Vorender::Vorender() {};

Vorender::~Vorender() {
	SDL_GL_DestroyContext(glContext);
}

void Vorender::init(SDL_GLContext context) {
	glContext = context;

	glClearColor(.3f, .3f, .3f, 1.0f);

	//Build shader program
	std::string vrt = loadShaderFile("./assets/shaders/fullscreen.vert");
	std::string frag = loadShaderFile("./assets/shaders/voro.frag");
	const char* vertexShaderSource = vrt.c_str();
	const char* fragmentShaderSource = frag.c_str();
	// std::cout << "Vertex: " << std::endl <<vertexShaderSource << std::endl
	// << "Fragment: "<< std::endl << fragmentShaderSource << std::endl;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkShaderCompile(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompile(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkProgramLink(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Vorender::use() const {
	glUseProgram(shaderProgram);
}

void Vorender::render() {

}

GLuint Vorender::getLocation(const std::string& name) const {
	return glGetUniformLocation(shaderProgram, name.c_str());
}

void Vorender::setMat4(const std::string& name, const float* mat) const {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, mat);
}