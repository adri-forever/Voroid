#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <string>

#include "glm/glm.hpp"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

float random01();

glm::vec3 parseHexColor(std::string colorstr);
glm::vec3 parseHexColor_json(json colordata);

float hue_to_rgb(float p, float q, float t);
glm::vec3 hsl_to_rgb(glm::vec3 rgbcolor);

bool checkVector(json data, int size);
bool checkVector(json data);

glm::dvec3 parseDvec3(json data);

#endif // TOOLBOX_H