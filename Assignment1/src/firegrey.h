
#include "main.h"

#ifndef FIREGREY_H
#define FIREGREY_H


class Firegrey {
public:
    Firegrey() {}
    Firegrey(float x, float y,GLfloat scl, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed_y;
    double speed_x;
    GLfloat firegrey_w, shift, firegrey_h, scl;
    GLfloat shift_y, shift_x;
    GLfloat scl_x, scl_y, scl_z;
    double x,y;
private:
    VAO *object;
};

#endif // FIREGREY_H
