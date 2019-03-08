#define GLM_ENABLE_EXPERIMENTAL
#include "airplane.h"
#include "main.h"
using namespace::std;

Airplane::Airplane(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 1);
    this->rotation_y = 0;
    this->rotation_x = 0;
    this->rotation_about = glm::vec3(1,0,0);
    this->angular_speed = 0;
    this->health = 100;
    this->manoevers = 0;

    speed = 0.0f;
    speed_y = 0.0f;
    speed_z = 0.0f;
    scl_x = scl_y = scl_z = 0.3f;
    static const GLfloat vertex_buffer_data[] = {

         0.0f*scl_x,   0.0f*scl_y,  -6.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,
         0.0f*scl_x,   0.0f*scl_y,  -6.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,     0.0f*scl_x,   1.0f*scl_y,  -4.0f*scl_z,
         0.0f*scl_x,   0.0f*scl_y,  -6.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,     0.0f*scl_x,   1.0f*scl_y,  -4.0f*scl_z,  // Front triangle 3

        -2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,
        -2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,
        -2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,     0.0f*scl_x,   1.0f*scl_y,  -4.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,
        -2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,     0.0f*scl_x,   1.0f*scl_y,   4.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,
         2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,     0.0f*scl_x,   1.0f*scl_y,  -4.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,
         2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,     0.0f*scl_x,   1.0f*scl_y,   4.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z, // The main middle part 9

         0.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,    -6.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,    -4.0f*scl_x,   0.0f*scl_y,  -2.0f*scl_z,
         0.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,  -2.0f*scl_z,    -4.0f*scl_x,   0.0f*scl_y,  -2.0f*scl_z,
         0.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,  -2.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,
         0.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,     0.0f*scl_x,   0.0f*scl_y,  -6.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,
         0.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,     6.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,     4.0f*scl_x,   0.0f*scl_y,  -2.0f*scl_z,
         0.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,  -2.0f*scl_z,     4.0f*scl_x,   0.0f*scl_y,  -2.0f*scl_z,
         0.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,  -2.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z,
         0.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,     0.0f*scl_x,   0.0f*scl_y,  -6.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,  -4.0f*scl_z, // Wings front 17

         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,     0.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,
         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,   2.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z, 
         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,   2.0f*scl_z,    -3.0f*scl_x,   0.0f*scl_y,   2.0f*scl_z,  
         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,    -4.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,    -3.0f*scl_x,   0.0f*scl_y,   2.0f*scl_z,  
         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,    -2.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,    -1.0f*scl_x,   0.0f*scl_y,   5.0f*scl_z,  
         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,     0.0f*scl_x,   0.0f*scl_y,   5.0f*scl_z,    -1.0f*scl_x,   0.0f*scl_y,   5.0f*scl_z,  // backwings left 23
         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,     0.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z,
         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,   2.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,   0.0f*scl_z, 
         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,   2.0f*scl_z,     3.0f*scl_x,   0.0f*scl_y,   2.0f*scl_z,  
         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,     4.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,     3.0f*scl_x,   0.0f*scl_y,   2.0f*scl_z,  
         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,     2.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,     1.0f*scl_x,   0.0f*scl_y,   5.0f*scl_z,  
         0.0f*scl_x,   0.0f*scl_y,   4.0f*scl_z,     0.0f*scl_x,   0.0f*scl_y,   5.0f*scl_z,     1.0f*scl_x,   0.0f*scl_y,   5.0f*scl_z,  // backwings left 29

    };
    this->object = create3DObject(GL_TRIANGLES, 29*3, vertex_buffer_data, color, GL_FILL);
}

void Airplane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0,1,0));
    glm::mat4 roll = glm::rotate((float)(this->rotation_x * M_PI / 180.0f), glm::vec3(0,0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Airplane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Airplane::tick() {
    
    this->position.x += speed*sin(rotation_y*M_PI/180.0f);
    this->position.y += speed_y;
    this->position.z += speed*cos(rotation_y*M_PI/180.0f);
    if(this->manoevers) this->rotation_x += 3;
    //this->rotation_x += angular_speed;
   // this->rotation_z += angular_speed_z;
}
bounding_box_t Airplane::bounding_box(){
    bounding_box_t box = {this->position.x,this->position.y,this->position.z,5*scl_x, 1*scl_y, 5*scl_z};
    return box;
}