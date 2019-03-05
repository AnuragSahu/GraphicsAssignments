
#include "main.h"

#ifndef DISPLAY_H
#define DISPLAY_H


class Display {
public:
    Display() {}
    Display(float x, float y,GLfloat scl, color_t color);
    glm::vec3 position;
    void digits(float mov);
    float rotation;
    void draw(glm::mat4 VP, int myscr);
    void set_position(float x, float y);
    void tick();
    void activate(int opt);
    int magtime;
    int sttime;
    double speed_y;
    double speed_x;
    int appear;
    GLfloat display_w, shift, display_h, scl;
    GLfloat shift_y, shift_x;
    GLfloat scl_x, scl_y, scl_z;
    double x,y;
    int dir;
    int tick_time;
    color_t color;
private:
   /* VAO *object0;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
    VAO *object9;*/
    VAO *object[10];
};

#endif // DISPLAY_H
