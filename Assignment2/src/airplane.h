#include "main.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H


class Airplane {
public:
    Airplane() {}
    Airplane(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 rotation_about;
    float health;
    float rotation_x, rotation_y, rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void tick1();
    float speed, speed_y, speed_z, angular_speed;
    float scl_x, scl_y, scl_z;
    bounding_box_t bounding_box();
    int manoevers;

private:
    VAO *object;
};

#endif // AIRPLANE_H
