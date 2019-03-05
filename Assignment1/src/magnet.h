
#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y,GLfloat scl, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void activate(int opt);
    int magtime;
    int sttime;
    double speed_y;
    double speed_x;
    int appear;
    GLfloat magnet_w, shift, magnet_h, scl;
    GLfloat shift_y, shift_x;
    GLfloat scl_x, scl_y, scl_z;
    double x,y;
    int dir;
    int tick_time;
private:
    VAO *object;
};

#endif // MAGNET_H
