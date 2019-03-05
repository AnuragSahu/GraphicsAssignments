#include "main.h"

#ifndef ANURAG_H
#define ANURAG_H


class Anurag {
public:
    Anurag() {}
    Anurag(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void jump();
    int insideSemi;
    int shield;
    float tick_time;
    bounding_box_t anurag_bounding_box;
    void upthrust(int up);
    bounding_box_t bounding_box();
    double speed_x, speed_y, jump_speed, x_org, y_org; 
    double gravity;
    double time, shield_time, speedup_time;
    GLfloat scl_x, scl_y, scl_z, width;
    int jumping, speedup;
    color_t COLOR_SKIN;
private:
    VAO *object;
    VAO *object1;
    VAO *head;
    VAO *neck;
    VAO *body;
    VAO *legs;
    VAO *hand;
    VAO *jetpack;
    VAO *fire;
};

#endif // ANURAG_H
