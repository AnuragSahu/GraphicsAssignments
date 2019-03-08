
#include "main.h"

#ifndef DISPLAY_H
#define DISPLAY_H


class Display {
public:
    Display() {}
    Display(float x, float y, color_t color);
    glm::vec3 position;
    void digits(float mov);
    float rotation;
    void draw(glm::mat4 VP, int score, int altitude,int speed);
    void set_position(float x, float y,float z, float rotate);
    void tick(float x, float y,float z, float rotate, float altitude, float fuel, float health);
    void activate(int opt);
    float fuel, health;
    int altitude;
    int score;
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
    float scl_x_digit, scl_y_digit, scl_z_digit;
    float mov_y_digit;
    float compass_mov_x;
    float compass_mov_y;
private:
    VAO *speed1[10];
    VAO *speed10[10];
    VAO *speed100[10];
    VAO *score1[10];
    VAO *score10[10];
    VAO *score100[10];
    VAO *altitude1[10];
    VAO *altitude10[10];
    VAO *altitude100[10];
    VAO *blank;
    VAO *fuel_meter;
    VAO *fuel_meter_full;
    VAO *score_meter;
    VAO *score_meter_full;
    VAO *altitude_meter;
    VAO *altitude_meter_full;
    VAO *health_meter;
    VAO *health_meter_full;
    VAO *compass_red;
    VAO *compass_white;
    VAO *compass_cover;
};

#endif // DISPLAY_H
