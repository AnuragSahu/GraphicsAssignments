#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float z, color_t color);
    glm::vec3 position;
    float rotation_y, rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick(float x, float y, float z);
    void tick1();
    double speed;
    float scl_x, scl_y, scl_z;
    bounding_box_t bounding_box();
    float length_c;
    float width_c  ;
    float height_c ;
    float mov_x_c , mov_y_c, mov_z_c ;
    float length_b;
    float width_b  ;
    float height_b ;
    float mov_x_b, mov_y_b, mov_z_b;
    float cannon_ball_speed;
    float cannon_ball_release;
    int appear;
    

private:
    VAO *cannon_ball;
    VAO *cannon;
    VAO *object;
    VAO *island;
};

#endif // CANNON_H
