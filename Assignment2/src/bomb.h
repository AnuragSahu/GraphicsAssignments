#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y,float z, color_t color);
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
    void drop_bomb(float x, float y, float z);
    float gravity;
    void reset();
private:
    VAO *object;
    VAO *island;
};

#endif // BOMB_H
