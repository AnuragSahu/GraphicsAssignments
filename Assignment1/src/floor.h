#include "main.h"

#ifndef FLOOR_H
#define FLOOR_H


class Floor {
public:
    Floor() {}
    Floor(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed_y;
    double speed_x;
    GLfloat floor_w, shift, floor_h;

private:
    VAO *object;
};

#endif // FLOOR_H
