#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float direction;
    void tick();
    float up;
    double speed;
    float scl_x, scl_y, scl_z;
    bounding_box_t bounding_box();
    int appear;
    float len,bre,hit;
    void drop_missile(float x, float y, float z, float rotation);
private:
    VAO *object;
    VAO *island;
};

#endif // MISSILE_H
