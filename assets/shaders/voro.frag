#version 460 core

in vec2 uv;

//
uniform float aspect;

// Nodes
uniform vec2 nodes[64];
uniform vec3 regioncolors[64];
uniform int size;

// Drawing properties
uniform float pointradius;
uniform float frontierwidth;
uniform vec3 pointcolor;
uniform vec3 frontiercolor;

out vec4 FragColor;

float sq(float x) {
    return x*x;
}

float scal(int index) {
    return sq(aspect*(nodes[index].x - uv.x)) + sq(nodes[index].y - uv.y);
}

void main() {
    vec3 color;
    int min1=0, min2=1, i;
    float dst1, dst2, dst;
    
    // Find closest two nodes

        // Initialize minimal distances
    dst1 = scal(min1);
    dst2 = scal(min2);

    if (dst1 > dst2 && size > 1) {
        i = min2;
        dst = dst2;
        
        min2 = min1;
        dst2 = dst1;

        min1 = i;
        dst1 = dst;
    }

        // First two nodes have been treated in initialization
    for (i=2; i<size; i++) {
        dst = scal(i);
        if (dst < dst1) {
            min2 = min1;
            dst2 = dst1;

            min1 = i;
            dst1 = dst; 
        } else if (dst < dst2) {
            min2 = i;
            dst2 = i;
        }
    }

    // Compute colors
    if (dst1 < pointradius && size > 0) { // if inside a point, draw a point
        color = pointcolor;
    } else if (abs(dst1 - dst2) < frontierwidth && size > 1) { // if on a frontier, draw a frontier
        color = frontiercolor;
    } else {
        color = regioncolors[min1]; // otherwise, draw the color set for the closest neighboring point
    }

    FragColor = vec4(color, 1.0);
}