#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick();
    void tick1();
    double speed;
    float scl_x, scl_y, scl_z;
    bounding_box_t bounding_box();
private:
    
    VAO *object;
    VAO *island;
};

#endif // VOLCANO_H
