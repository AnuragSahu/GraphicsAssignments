
#include "main.h"

#ifndef DESIGN_H
#define DESIGN_H


class Design {
public:
    Design() {}
    Design(float x, float y,GLfloat scl, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed_y;
    double speed_x;
    GLfloat design_w, shift, design_h, scl;
    GLfloat shift_y, shift_x;
    double x,y;
private:
    VAO *object;
};

#endif // DESIGN_H
