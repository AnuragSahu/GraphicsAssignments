#include "main.h"

#ifndef SEA_H
#define SEA_H


class Sea {
public:
    Sea() {}
    Sea(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float x, float z);
    void tick1();
    double speed;
    float scl_x, scl_y, scl_z;
private:
    VAO *object[9];
};

#endif // SEA_H
