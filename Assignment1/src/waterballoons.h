
#include "main.h"

#ifndef WATERBALLOONS_H
#define WATERBALLOONS_H


class Waterballoons {
public:
    Waterballoons() {}
    Waterballoons(float x, float y,GLfloat scl, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void activate(float x, float y);
    bounding_box_t bounding_box();
    bounding_box_t bitcoin_bounding_box;
    double speed_y;
    double speed_x;
    GLfloat waterballoons_w, shift, waterballoons_h, scl;
    GLfloat shift_y, shift_x;
    GLfloat scl_x, scl_y, scl_z;
    double x,y;
    int appear;
private:
    VAO *object;
};

#endif // WATERBALLOONS_H
