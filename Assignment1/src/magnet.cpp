#define GLM_ENABLE_EXPERIMENTAL
#include "magnet.h"
#include "main.h"

using namespace std;

#define len 25
#define wid 9

 Magnet:: Magnet(float x, float y,GLfloat scl, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->x = x;
    this->y = y;
    this->appear = 0;
    speed_x = 0;
    speed_y = 0;
    this->dir = 0;
    this->tick_time = 1;
    magnet_w = 2.7f;
    magnet_h = 2.7f;
    scl_x = 0.5f;
    scl_y = 0.5f;
    scl_z = 2.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static GLfloat vertex_buffer_data[] = {
       1.0f*scl_x, 0.0f*scl_y, scl_z,   3.0f*scl_x, 0.0f*scl_y, scl_z,    3.0f*scl_x, 1.0f*scl_y, scl_z,
       1.0f*scl_x, 0.0f*scl_y, scl_z,   1.0f*scl_x, 1.0f*scl_y, scl_z,    3.0f*scl_x, 1.0f*scl_y, scl_z,
       1.0f*scl_x, 0.0f*scl_y, scl_z,   0.0f*scl_x, 1.0f*scl_y, scl_z,    1.0f*scl_x, 1.0f*scl_y, scl_z,
       1.0f*scl_x, 3.0f*scl_y, scl_z,   0.0f*scl_x, 1.0f*scl_y, scl_z,    1.0f*scl_x, 1.0f*scl_y, scl_z,
       1.0f*scl_x, 3.0f*scl_y, scl_z,   0.0f*scl_x, 1.0f*scl_y, scl_z,    0.0f*scl_x, 3.0f*scl_y, scl_z,
       1.0f*scl_x, 3.0f*scl_y, scl_z,   1.0f*scl_x, 4.0f*scl_y, scl_z,    0.0f*scl_x, 3.0f*scl_y, scl_z,
       1.0f*scl_x, 3.0f*scl_y, scl_z,   1.0f*scl_x, 4.0f*scl_y, scl_z,    3.0f*scl_x, 3.0f*scl_y, scl_z,
       3.0f*scl_x, 4.0f*scl_y, scl_z,   1.0f*scl_x, 4.0f*scl_y, scl_z,    3.0f*scl_x, 3.0f*scl_y, scl_z,
    };
    
    this->object = create3DObject(GL_TRIANGLES, 9*3, vertex_buffer_data, color, GL_FILL);
}

void  Magnet::draw(glm::mat4 VP) {
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

void  Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::activate(int opt){
    this->appear = opt;
}

void  Magnet::tick() {
    this->position.x += speed_x;
    if(this->appear == 1)  { this->tick_time += 1; this->position.x -= speed_x; }
    if(this->tick_time > 500)  {this->appear = 0; this->tick_time = 1; }
}
