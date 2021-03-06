#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y,int points ,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    int appear;
    double speed, speed_x, speed_y;
    GLfloat scl_x, scl_y, scl_z, width;
    bounding_box_t coin_bounding_box;
    double score;
private:
    VAO *object;
};

#endif // COIN_H
