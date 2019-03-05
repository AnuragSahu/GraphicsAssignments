
#include "main.h"

#ifndef SUBDESIGN_H
#define SUBDESIGN_H


class SubDesign {
public:
    SubDesign() {}
    SubDesign(float x, float y,GLfloat scl, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed_y;
    double speed_x;
    GLfloat subdesign_w, shift, subdesign_h, scl;
    GLfloat shift_y, shift_x;
    double x,y;
private:
    VAO *object;
};

#endif // SUBDESIGN_H
