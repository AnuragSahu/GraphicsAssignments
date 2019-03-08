#include "main.h"

#ifndef CANNON_BALL_H
#define CANNON_BALL_H


class CannonBall {
public:
    CannonBall() {}
    CannonBall(float x, float z, color_t color);
    glm::vec3 position;
    glm::vec3 position_temp;
    float rotation_y, rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick(float x, float y, float z);
    void tick1();
    double speed;
    float scl_x, scl_y, scl_z;
    bounding_box_t bounding_box();
    void reset();
    float length_b;
    float width_b  ;
    float height_b ;
    float mov_x_b, mov_y_b, mov_z_b;
    float cannon_ball_speed;
    float cannon_ball_release;
    float sin ,cos;
    float target_x;
    float target_y;
    float target_z;
    int ball_tick;
    int appear;
    float speed_x;
    float speed_z;
    float speed_y;
    

private:
    VAO *cannon_ball;
    VAO *cannon;
    VAO *object;
    VAO *island;
};

#endif // CANNON_BALL_H
