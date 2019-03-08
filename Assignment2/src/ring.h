#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick();
    void tick1();
    double speed;
    int appear;
    float scl_x, scl_y, scl_z;
    bounding_box_t bounding_box();
private:
    
    VAO *object;
    VAO *island;
};

#endif // RING_H
