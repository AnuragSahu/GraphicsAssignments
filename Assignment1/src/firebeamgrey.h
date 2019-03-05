
#include "main.h"

#ifndef FIREBEAMGREY_H
#define FIREBEAMGREY_H


class Firebeamgrey {
public:
    Firebeamgrey() {}
    Firebeamgrey(float x, float y,GLfloat scl, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed_y;
    double speed_x;
    GLfloat firebeamgrey_w, shift, firebeamgrey_h, scl;
    GLfloat shift_y, shift_x;
    GLfloat scl_x, scl_y, scl_z;
    double x,y;
    int dir;
    int tick_time;
private:
    VAO *object;
};

#endif // FIREBEAMGREY_H
