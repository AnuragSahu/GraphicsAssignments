#include "main.h"

#ifndef BITCOIN_H
#define BITCOIN_H


class Bitcoin {
public:
    Bitcoin() {}
    Bitcoin(float x, float y, color_t color);
    glm::vec3 position;
    int dir;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    int appear;
    double speed, speed_x, speed_y;
    GLfloat scl_x, scl_y, scl_z, width;
    bounding_box_t bitcoin_bounding_box;
    double score;
private:
    VAO *object;
};

#endif // BITCOIN_H
