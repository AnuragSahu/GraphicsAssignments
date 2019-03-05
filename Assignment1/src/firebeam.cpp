#define GLM_ENABLE_EXPERIMENTAL
#include "firebeam.h"
#include "main.h"

#define len 25
#define wid 9

Firebeam::Firebeam(float x, float y,GLfloat scl, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->x = x;
    this->y = y;
    speed_x = 0;
    speed_y = 0;
    this->tick_time = 0;
    firebeam_w = 2.7f;
    firebeam_h = 2.7f;
    scl_x = 0.1f;
    scl_y = 0.1f;
    scl_z = 1.0f;
    int appear = 1;
    this->bitcoin_bounding_box.width = 24.0f*scl_y;
    this->bitcoin_bounding_box.height = 10.0f*scl_x;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static GLfloat vertex_buffer_data[] = {
         11*scl_x,  4*scl_y, scl_z,     11*scl_x,  -4*scl_y,  scl_z,   -11*scl_x,  4*scl_y, scl_z,
        -11*scl_x, -4*scl_y, scl_z,     11*scl_x,  -4*scl_y,  scl_z,   -11*scl_x,  4*scl_y, scl_z,
        -12*scl_x, -5*scl_y, scl_z,    -11*scl_x,  -4*scl_y,  scl_z,   -11*scl_x, -3*scl_y, scl_z,
        -10*scl_x, -5*scl_y, scl_z,    -11*scl_x,  -4*scl_y,  scl_z,    -9*scl_x, -4*scl_y, scl_z,
         -8*scl_x, -5*scl_y, scl_z,     -7*scl_x,  -4*scl_y,  scl_z,    -9*scl_x, -4*scl_y, scl_z,
         -6*scl_x, -5*scl_y, scl_z,     -7*scl_x,  -4*scl_y,  scl_z,    -5*scl_x, -4*scl_y, scl_z,
         -4*scl_x, -5*scl_y, scl_z,     -3*scl_x,  -4*scl_y,  scl_z,    -5*scl_x, -4*scl_y, scl_z,
         -2*scl_x, -5*scl_y, scl_z,     -3*scl_x,  -4*scl_y,  scl_z,    -1*scl_x, -4*scl_y, scl_z,
          0*scl_x, -5*scl_y, scl_z,      1*scl_x,  -4*scl_y,  scl_z,    -1*scl_x, -4*scl_y, scl_z,
          2*scl_x, -5*scl_y, scl_z,      1*scl_x,  -4*scl_y,  scl_z,     3*scl_x, -4*scl_y, scl_z,
          4*scl_x, -5*scl_y, scl_z,      5*scl_x,  -4*scl_y,  scl_z,     3*scl_x, -4*scl_y, scl_z, 
          6*scl_x, -5*scl_y, scl_z,      5*scl_x,  -4*scl_y,  scl_z,     7*scl_x, -4*scl_y, scl_z,
          8*scl_x, -5*scl_y, scl_z,      9*scl_x,  -4*scl_y,  scl_z,     7*scl_x, -4*scl_y, scl_z,
         10*scl_x, -5*scl_y, scl_z,      9*scl_x,  -4*scl_y,  scl_z,    11*scl_x, -4*scl_y, scl_z,
         12*scl_x, -5*scl_y, scl_z,     11*scl_x,  -4*scl_y,  scl_z,    11*scl_x, -3*scl_y, scl_z,
         12*scl_x, -2*scl_y, scl_z,     11*scl_x,  -1*scl_y,  scl_z,    11*scl_x, -3*scl_y, scl_z,
         12*scl_x,  0*scl_y, scl_z,     11*scl_x,  -1*scl_y,  scl_z,    11*scl_x,  1*scl_y, scl_z,
         12*scl_x,  2*scl_y, scl_z,     11*scl_x,   3*scl_y,  scl_z,    11*scl_x,  1*scl_y, scl_z,
         12*scl_x,  5*scl_y, scl_z,     11*scl_x,   3*scl_y,  scl_z,    11*scl_x,  4*scl_y, scl_z,
         11*scl_x,  4*scl_y, scl_z,     10*scl_x,   5*scl_y,  scl_z,     9*scl_x,  4*scl_y, scl_z,
          7*scl_x,  4*scl_y, scl_z,      8*scl_x,   5*scl_y,  scl_z,     9*scl_x,  4*scl_y, scl_z,
          7*scl_x,  4*scl_y, scl_z,      6*scl_x,   5*scl_y,  scl_z,     5*scl_x,  4*scl_y, scl_z,
          3*scl_x,  4*scl_y, scl_z,      4*scl_x,   5*scl_y,  scl_z,     5*scl_x,  4*scl_y, scl_z,
          3*scl_x,  4*scl_y, scl_z,      2*scl_x,   5*scl_y,  scl_z,     1*scl_x,  4*scl_y, scl_z,
         -1*scl_x,  4*scl_y, scl_z,      0*scl_x,   5*scl_y,  scl_z,     1*scl_x,  4*scl_y, scl_z, 
         -1*scl_x,  4*scl_y, scl_z,     -2*scl_x,   5*scl_y,  scl_z,    -3*scl_x,  4*scl_y, scl_z, 
         -5*scl_x,  4*scl_y, scl_z,     -4*scl_x,   5*scl_y,  scl_z,    -3*scl_x,  4*scl_y, scl_z, 
         -5*scl_x,  4*scl_y, scl_z,     -6*scl_x,   5*scl_y,  scl_z,    -7*scl_x,  4*scl_y, scl_z, 
         -9*scl_x,  4*scl_y, scl_z,     -8*scl_x,   5*scl_y,  scl_z,    -7*scl_x,  4*scl_y, scl_z, 
         -9*scl_x,  4*scl_y, scl_z,    -10*scl_x,   5*scl_y,  scl_z,   -11*scl_x,  4*scl_y, scl_z, 
        -11*scl_x,  3*scl_y, scl_z,    -12*scl_x,   5*scl_y,  scl_z,   -11*scl_x,  4*scl_y, scl_z,
        -11*scl_x,  3*scl_y, scl_z,    -12*scl_x,   2*scl_y,  scl_z,   -11*scl_x,  1*scl_y, scl_z,
        -11*scl_x, -1*scl_y, scl_z,    -12*scl_x,   0*scl_y,  scl_z,   -11*scl_x,  1*scl_y, scl_z,
        -11*scl_x, -1*scl_y, scl_z,    -12*scl_x,  -2*scl_y,  scl_z,   -11*scl_x, -3*scl_y, scl_z,
    };
    this->object = create3DObject(GL_TRIANGLES, 34*3, vertex_buffer_data, color, GL_FILL);
}

void Firebeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(2.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam::tick() {
    this->position.x += speed_x;
    if(this->tick_time <= 20){ this->position.y += 0.1f; }
    else if(this->tick_time <= 40){ this->position.y -= 0.1f; }
    else { 
        this->tick_time = 1;
        this->position.y = this->y;
    }
    this->tick_time += 1;
}

bounding_box_t Firebeam::bounding_box(){
    bounding_box_t box = {this->position.x, this->position.y, this->bitcoin_bounding_box.width, this->bitcoin_bounding_box.height };
    return box;
}
