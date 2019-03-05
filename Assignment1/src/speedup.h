
#include "main.h"

#ifndef SPEEDUP_H
#define SPEEDUP_H


class SpeedUp {
public:
    SpeedUp() {}
    SpeedUp(float x, float y,GLfloat scl, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    int appear;
    double speed_y;
    double speed_x;
    GLfloat speedup_w, shift, speedup_h, scl;
    GLfloat shift_y, shift_x;
    GLfloat scl_x, scl_y, scl_z;
    double x,y;
    int dir;
    float tick_time, x_org, y_org;

private:
    VAO *object;
};

#endif // SPEEDUP_H
