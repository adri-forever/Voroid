#include "utils/glUtils.h"

#include <stdio.h>
#include <string>
#include <fstream>

// Load shader
std::string loadShaderFile(const std::string& filepath) {
	std::string result = "";
	std::string line = "";
	std::ifstream fileStream(filepath.c_str());

	// std::cout << "Current working directory: " << _getcwd(NULL, 0) << std::endl;
	// std::cout<<"Reading file "<<filepath<<std::endl;
	// if (fileStream.fail()) {
	// 	std::cout<<"Stream failed."<<std::endl;
	// }
	if (fileStream.is_open()) {
		while (std::getline(fileStream, line)) {
			result += line+'\n';
			// std::cout<<line<<std::endl;
		}
		fileStream.close();
	}

	// std::cout << "Result: " << result << std::endl;
	return result;
}

//Compile checks
void checkShaderCompile(GLuint shader) {
	char infoLog[512];
	GLint shadertype;
	char typeDesc[64];
	int success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	
	glGetShaderiv(shader, GL_SHADER_TYPE, &shadertype);
	switch (shadertype) {
		case GL_VERTEX_SHADER:
			std::snprintf(typeDesc, sizeof(typeDesc), "Vertex");
			break;
		case GL_FRAGMENT_SHADER:
			std::snprintf(typeDesc, sizeof(typeDesc), "Fragment");
			break;
		default:
			std::snprintf(typeDesc, sizeof(typeDesc), "Unknown");
			break;
	}
	
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << typeDesc << " shader compilation failed: " << infoLog << std::endl;
	}
}

void checkProgramLink(GLuint program) {
	char infoLog[512];
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Program shader linking failed: " << infoLog << std::endl;
	}
}

//Easy vector prints
std::ostream& operator<<(std::ostream& stream, const glm::vec3& v) {
	stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const glm::dvec3& v) {
	stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return stream;
}