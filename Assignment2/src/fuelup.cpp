#define GLM_ENABLE_EXPERIMENTAL
#include "fuelup.h"
#include "main.h"

FuelUp::FuelUp(float x, float z, color_t color) {
    this->position = glm::vec3(x, 8, z);
    this->rotation = 0;
    speed = 0.01;
    scl_x = scl_y = scl_z = 1;
    float breadth = 50.0f;
    this->appear = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
   static GLfloat vertex_buffer_data[] = {
        -3.00f*scl_x,     2.00f*scl_y,   0.00f*scl_z,   -3.00f*scl_x,    -2.00f*scl_y,    0.00f*scl_z,    1.00f*scl_x,    -2.00f*scl_y,    0.00f*scl_z,
        -3.00f*scl_x,     2.00f*scl_y,   0.00f*scl_z,    1.00f*scl_x,     2.00f*scl_y,    0.00f*scl_z,    1.00f*scl_x,    -2.00f*scl_y,    0.00f*scl_z,
         3.00f*scl_x,     2.00f*scl_y,   0.00f*scl_z,    2.00f*scl_x,     2.00f*scl_y,    0.00f*scl_z,    1.00f*scl_x,    -2.00f*scl_y,    0.00f*scl_z,
         1.00f*scl_x,    -1.00f*scl_y,   0.00f*scl_z,    2.00f*scl_x,     2.00f*scl_y,    0.00f*scl_z,    1.00f*scl_x,    -2.00f*scl_y,    0.00f*scl_z,

        
     }; this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, { 250, 14, 13}, GL_FILL);
}

void FuelUp::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->appear) draw3DObject(this->object);
}

void FuelUp::set_position(float x, float z) {
    this->position = glm::vec3(x, 1, z);
}

void FuelUp::tick() {
    this->rotation += 1;
}

bounding_box_t FuelUp::bounding_box(){
    bounding_box_t box = {this->position.x,this->position.y,this->position.z,3.00f*scl_x,3.00f*scl_y,3.00f*scl_z};
    return box;
}