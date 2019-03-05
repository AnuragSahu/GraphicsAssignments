
#include "main.h"

#ifndef LIFE1_H
#define LIFE1_H


class Life1 {
public:
    Life1() {}
    Life1(float x, float y,GLfloat scl, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    double speed_y;
    double speed_x;
    GLfloat life1_w, shift, life1_h, scl;
    GLfloat shift_y, shift_x;
    GLfloat scl_x, scl_y, scl_z;
    double x,y;
    int dir;
    float tick_time, x_org, y_org;
    int appear;

private:
    VAO *object;
};

#endif // LIFE1_H
