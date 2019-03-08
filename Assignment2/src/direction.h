#include "main.h"

#ifndef DIRECTION_H
#define DIRECTION_H


class Direction {
public:
    Direction() {}
    Direction(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 target;
    float rotation;
    void draw(glm::mat4 VP);
    void set_dir(float x, float z);
    void tick(float x, float y, float z);
    float up;
    int arr_dir;
    double speed;
    float scl_x, scl_y, scl_z;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *island;
};

#endif // DIRECTION_H
