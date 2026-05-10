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

// Distance functions with overloads
float dist(float x1, float y1, float x2, float y2) {
    return sqrt(sq(aspect*(x2-x1)) + sq(y2-y1)); // we can allow ourselves a sqrt, its not that expensive anymore
}

float dist(vec2 a, vec2 b) { // distance between two vector points
    return dist(a.x, a.y, b.x, b.y);
}

float dist(int i1, int i2) { // distance between to nodes (useful ?)
    return dist(nodes[i1], nodes[i2]);
}

float dist(int index) { // if only one index is given, take distance with uv coordinates
    return dist(uv, nodes[index]);
}

void main() {
    vec3 color;
    int min1=0, min2=1, i;
    // closest point index, second closest point index, iterator/temp variable
    float dst1, dst2, dst, t;
    // closest distance, second closest distance, temp variable, parameter for parametric geometry
    vec2 mpt, seg, prp, prjpt, pt1, pt2;
    // midpoint, segment vector, perpendicular vector, projected point, closest point, second closest point


    // Find closest two nodes

        // Initialize minimal distances
    dst1 = dist(min1);
    dst2 = dist(min2);

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
        dst = dist(i);
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
    color = regioncolors[min1]; // by default, set color based on closest neighboring point
    if (dst1 < pointradius && size > 0) { // if inside a point, draw a point
        color = pointcolor;
    } else  if (size > 1) { // if more than two points, check frontiers
        pt1 = nodes[min1]; // get coordinates of closest points
        pt2 = nodes[min2];
        seg = pt2 - pt1; // vector corresponding to segment from one minimum to the other
        prp.x = -seg.y; // perpendicular vector for seg, colinear to perp bisector
        prp.y = seg.x;
        mpt = .5f * (pt1 + pt2); // midpoint

        // t = 0;
        // parametric geometry to find projection of uv on bisector
        t = (uv.x*(pt1.y - pt2.y) + uv.y*(pt2.x - pt1.x) - pt1.x*pt1.y + pt2.x*pt2.y)
            / (sq(pt1.y-pt2.y)+sq(pt2.x-pt1.x));
        prjpt = mpt + t*prp;

        float dstuv = dist(uv, prjpt);
        float dstm = dist(prjpt, pt1);
        float rat = dstuv / dstm; // necessarily between 0 and 1 
        // color = 1 - ((1-color)*rat);
        // if (false) {
        if (dstuv < frontierwidth) {
            color = frontiercolor;
        }
    }

    FragColor = vec4(color, 1.f);
}