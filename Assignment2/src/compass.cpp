#define GLM_ENABLE_EXPERIMENTAL
#include "compass.h"
#include "main.h"

using namespace std;

 Compass:: Compass(float x, float y, color_t color) {
    //this->position = glm::vec3(x, y, 0);
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->x = x;
    this->y = y;
    this->appear = 0;
    speed_x = 0;
    speed_y = 0;
    this->dir = 0;
    this->tick_time = 1;
    compass_w = 2.7f;
    compass_h = 2.7f;
    scl_x = 0.5f;
    scl_y = 0.04f;
    int len = 1, width = 8;
    this->color = color;
    this->score = 500;
    this->altitude = 0;
    this->fuel = 100;
    scl_z = 2.0f;
    float mov =  -3.5f*scl_x;
    float mov1 = -3.4f*scl_x;
    float mov3 = -3.3f*scl_x;
    float altitude_mov,altitude_mov1, altitude_mov3;
    
    altitude_mov =  -0.80f*scl_x;
    altitude_mov1 = -0.70f*scl_x;
    altitude_mov3 = -0.60f*scl_x;
    
    float score_mov =  -3.90f*scl_x;
    float score_mov1 = -3.80f*scl_x;
    float score_mov3 = -3.70f*scl_x;

    this->compass_mov_x = -1.0f*scl_x;
    //float scl_x_digit, scl_y_digit, scl_z_digit;
    scl_x_digit = 0.01f;
    scl_y_digit = 0.03f;
    //scl_z_digit = 0.0f*scl_z+3.005;
    scl_z = 0;
    scl_z_digit = -1;
    color_t color_digits = { 173,255,47 };
    float mov_y_digit = -2.0f;
    float score_mov_y_digit = mov_y_digit;
    this->compass_mov_y = mov_y_digit;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat compass_data[] = {
       2*scl_x_digit+compass_mov_x,   2*scl_y_digit+mov_y_digit, scl_z_digit,
       2*scl_x_digit+compass_mov_x,  -2*scl_y_digit+mov_y_digit, scl_z_digit, // this is for the Needle in compass
    }; this->compass = create3DObject(GL_LINES, 4, compass_data, color_digits, GL_FILL);
}

void Compass::digits(float mov){
    
}

void  Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    //glm::mat4 MVP = glm::mat4(1.0f);//*/  VP * Matrices.model;
    glm::mat4 MVP =  Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->compass);
    //cout << "drawing\n";
  }


void Compass::activate(int opt){
    this->appear = opt;
}

void  Compass::tick(float rotate) {
    scl_x_digit = 0.01f;
    scl_y_digit = 0.03f;
    scl_z_digit = -1.001;
    compass_mov_x = -1*scl_x;
    static const GLfloat compass_data_1[] = {
       2*(scl_x_digit)*(float)sin(rotate*3.14/180)+this->compass_mov_x,   2*scl_y_digit*(float)cos(rotate*3.14/180)+this->compass_mov_y, scl_z_digit,
       0*(scl_x_digit)*(float)sin(rotate*3.14/180)+this->compass_mov_x,   -2*scl_y_digit*(float)cos(rotate*3.14/180)+this->compass_mov_y, scl_z_digit, // this is for the Needle in compass
    }; this->compass = create3DObject(GL_LINES, 4, compass_data_1, {255,125,255}, GL_FILL);
    //cout << "ticking\n";
}
