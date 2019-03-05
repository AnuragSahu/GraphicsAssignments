
#include "main.h"

#ifndef ICEBALLS_H
#define ICEBALLS_H


class Iceballs {
public:
    Iceballs() {}
    Iceballs(float x, float y,GLfloat scl, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void set_y(float y);
    int y_set;
    bounding_box_t bounding_box();
    bounding_box_t bitcoin_bounding_box;
    double speed_y;
    double speed_x;
    GLfloat iceballs_w, shift, iceballs_h, scl;
    GLfloat shift_y, shift_x;
    GLfloat scl_x, scl_y, scl_z;
    double x,y;
    int appear;
private:
    VAO *object;
};

#endif // ICEBALLS_H
