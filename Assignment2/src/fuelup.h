#include "main.h"

#ifndef FUEL_UP
#define FUEL_UP


class FuelUp {
public:
    FuelUp() {}
    FuelUp(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick();
    void tick1();
    double speed;
    int appear;
    float scl_x, scl_y, scl_z;
    bounding_box_t bounding_box();
private:
    
    VAO *object;
    VAO *island;
};

#endif // FUEL_UP
