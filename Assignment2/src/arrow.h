#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick();
    float up;
    int arr_dir;
    double speed;
    float scl_x, scl_y, scl_z;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *island;
};

#endif // ARROW_H
