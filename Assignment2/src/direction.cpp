#define GLM_ENABLE_EXPERIMENTAL
#include "direction.h"
#include "main.h"

using namespace::std;
Direction::Direction(float x, float z, color_t color) {
    this->up = 20;
    this->position = glm::vec3(x, this->up, z);
    this->rotation = 0;
    speed = 0.01;
    scl_x = scl_y = scl_z = 0.5;
    float breadth = 50.0f;
    float mov_x = 0.0f;
    float mov_y = 0.0f;
    float mov_z = 0.0f;
    this->arr_dir = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
       //-1.0f *scl_x+mov_x, 0 * scl_y+mov_y,   +2.0f* scl_z+mov_z,  -1.0f*scl_x+mov_x, 0 * scl_y+mov_y,   -2.0f* scl_z+mov_z,    1 *scl_x+mov_x, 0 * scl_y+mov_y,  2 * scl_z+mov_z,
       // 1.0f *scl_x+mov_x, 0 * scl_y+mov_y,   -2.0f* scl_z+mov_z,  -1.0f*scl_x+mov_x, 0 * scl_y+mov_y,   -2.0f* scl_z+mov_z,    1 *scl_x+mov_x, 0 * scl_y+mov_y,  2 * scl_z+mov_z,
       //-3.0f *scl_x+mov_x, 0 * scl_y+mov_y,   -2.0f* scl_z+mov_z,   0.0f*scl_x+mov_x, 0 * scl_y+mov_y,   -4.0f* scl_z+mov_z,    3 *scl_x+mov_x, 0 * scl_y+mov_y, -2 * scl_z+mov_z, 

       -1.0f*scl_x+mov_x, +0.0f*scl_y+mov_y, +2.0f*scl_z+mov_z,  -1.0f*scl_x+mov_x, -0.0f*scl_y+mov_y, -2.0f*scl_z+mov_z,  1.0f*scl_x+mov_x,  0.0f*scl_y+mov_y,  2.0f*scl_z+mov_z,
        1.0f*scl_x+mov_x, -0.0f*scl_y+mov_y, -2.0f*scl_z+mov_z,  -1.0f*scl_x+mov_x, -0.0f*scl_y+mov_y, -2.0f*scl_z+mov_z,  1.0f*scl_x+mov_x,  0.0f*scl_y+mov_y,  2.0f*scl_z+mov_z,
       -3.0f*scl_x+mov_x, -0.0f*scl_y+mov_y, -2.0f*scl_z+mov_z,   0.0f*scl_x+mov_x, -0.0f*scl_y+mov_y, -4.0f*scl_z+mov_z,  3.0f*scl_x+mov_x, -0.0f*scl_y+mov_y, -2.0f*scl_z+mov_z, 
       +0.0f*scl_x+mov_x, -1.0f*scl_y+mov_y, +2.0f*scl_z+mov_z,  -0.0f*scl_x+mov_x, -1.0f*scl_y+mov_y, -2.0f*scl_z+mov_z,  0.0f*scl_x+mov_x,  1.0f*scl_y+mov_y,  2.0f*scl_z+mov_z,
       -0.0f*scl_x+mov_x,  1.0f*scl_y+mov_y, -2.0f*scl_z+mov_z,  -0.0f*scl_x+mov_x, -1.0f*scl_y+mov_y, -2.0f*scl_z+mov_z,  0.0f*scl_x+mov_x,  1.0f*scl_y+mov_y,  2.0f*scl_z+mov_z,
       -0.0f*scl_x+mov_x, -3.0f*scl_y+mov_y, -2.0f*scl_z+mov_z,  -0.0f*scl_x+mov_x,  0.0f*scl_y+mov_y, -4.0f*scl_z+mov_z, -0.0f*scl_x+mov_x,  3.0f*scl_y+mov_y, -2.0f*scl_z+mov_z, 

    };
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, {25, 25, 50}, GL_FILL);
}

void Direction::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    //glm::mat4 MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Direction::set_dir(float x,float z) {
    this->target = glm::vec3(x, 0, z);
}

void Direction::tick(float x, float y, float z) {
    this->position = glm::vec3(x, y + 4, z);
    if(this->position.x - this->target.x > 0)
      this->rotation = 180*acos((this->position.z-this->target.z)/sqrt((this->position.x-this->target.x)*(this->position.x-this->target.x)+(this->position.z-this->target.z)*(this->position.z-this->target.z)))/3.14;
    if(this->position.x - this->target.x <= 0)
      this->rotation = 180*acos((-this->position.z+this->target.z)/sqrt((this->position.x-this->target.x)*(this->position.x-this->target.x)+(this->position.z-this->target.z)*(this->position.z-this->target.z)))/3.14 + 180;
}

bounding_box_t Direction::bounding_box(){
    bounding_box_t box = {this->position.x,this->position.y,this->position.z,5,5,5000};
    return box;
}