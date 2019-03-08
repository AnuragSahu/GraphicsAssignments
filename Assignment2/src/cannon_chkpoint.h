#include "main.h"
#include "cannon.h"
#include "cannon_ball.h"

#ifndef CHECK_POINT_H
#define CHECK_POINT_H


class CheckPoint {
public:
    CheckPoint() {}
    CheckPoint(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick(float x, float y, float z);
    double speed;
    float scl_x, scl_y, scl_z;
    bounding_box_t bounding_box();
    bounding_box_t bounding_box_cannon();
    float length;
    float width;
    float height;
    int appear = 0;
    Cannon cannon;
    CannonBall cannon_ball;
    int active;
private:
    VAO *cannon_base;
    VAO *object;
    VAO *island;
};

#endif // CHECK_POINT_H
