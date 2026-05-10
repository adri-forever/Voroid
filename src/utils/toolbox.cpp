#include "utils/toolbox.h"

#include <bits/stdc++.h>

// Do proper randomization, this is deterministic
float random01() {
    return (float)std::rand() / (float)(RAND_MAX);
}

glm::vec3 parseHexColor(std::string colorstr) {
    //parse string #XXXXXX to hex color (if alpha is provided, will be ignored)
    //will break if you pass an invalid hex string
    glm::vec3 color;

    if ((colorstr.length()>=7) && colorstr[0]=='#') {
        /* Without the #, the string must be of length 6 at least (from the 4th group on everything will be ignored) */
        for (int i=0; i < 3; i++) {
            color[i] = std::stoi(colorstr.substr(2*i+1, 2), 0, 16)/255.;
        }
    }

    return color;
}

glm::vec3 parseHexColor_json(json colordata) {
    glm::vec3 color = glm::vec3(0.f);
    if (colordata.is_string()) {
        color = parseHexColor((std::string)colordata);
    } else if (colordata.is_array() && colordata.size()>=3) {
        for (int i=0; i<3; i++) {
            if (colordata[i].is_number()) { //later smartly detect if we have range 0-255 or 0. 1. range 
                color[i] = (float)colordata[i]/255.f;
            }
        }
    }
    return color;
}

float hue_to_rgb(float p, float q, float t) {
  if (t < 0.f) t += 1.f;
  if (t > 1.f) t -= 1.f;
  if (t < 1.f/6.f) return p + (q - p) * 6.f * t;
  if (t < 1.f/2.f) return q;
  if (t < 2.f/3.f) return p + (q - p) * (2.f/3.f - t) * 6.f;
  return p;
}

glm::vec3 hsl_to_rgb(glm::vec3 hsl) {
	glm::vec3 rgb;
	float q, p;

	if (hsl.y == 0) {
		rgb = glm::vec3(hsl.z); // achromatic
	} else {
		if (hsl.z < .5f) {
			q = hsl.z * (1.f + hsl.y);
		} else {
			q = hsl.z + hsl.y - hsl.z * hsl.y;
		}
		p = 2.f * hsl.z - q;
		rgb.x = hue_to_rgb(p, q, hsl.x + 1.f/3.f);
		rgb.y = hue_to_rgb(p, q, hsl.x);
		rgb.z = hue_to_rgb(p, q, hsl.x - 1.f/3.f);
	}

	return rgb;
}

bool checkVector(json data, int size) {
    return data.is_array() && (data.size()>=size || size==-1) && data[0].is_number();
}

bool checkVector(json data) {
    return checkVector(data, -1);
}

glm::dvec3 parseDvec3(json data) {
    glm::dvec3 vec = glm::dvec3(0.);
    if (data.is_array() && data.size()>=3) {
        for (int i=0; i<3; i++) {
            if (data[i].is_number()) {
                vec[i] = (double)data[i];
            }
        }
    }
    return vec;
}