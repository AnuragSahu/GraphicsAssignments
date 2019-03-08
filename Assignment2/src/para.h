#include "main.h"

#ifndef PARA_H
#define PARA_H


class Para {
public:
    Para() {}
    Para(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float up;
    double speed;
    float scl_x, scl_y, scl_z;
    bounding_box_t bounding_box();
    int appear;
    float len,bre,hit;
    float gravity;
    void reset();
private:
    VAO *object;
    VAO *island;
};

#endif // PARA_H
