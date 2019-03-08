#define GLM_ENABLE_EXPERIMENTAL
#include "cannon_chkpoint.h"
#include "main.h"
#include "cannon.h"
#include "cannon_ball.h"

CheckPoint::CheckPoint(float x, float z, color_t color) {
    this->cannon = Cannon(x,z,color);
    this->cannon_ball = CannonBall(x,z,color);
    this->position = glm::vec3(x, 0.001, z);
    this->rotation = 0;
    speed = 0.01;
    scl_x = scl_y = scl_z = 1;
    float breadth = 50.0f;
    this->length = 3 * scl_x;
    this->width =  3 * scl_z;
    this->height = 3 * scl_y;
    this->appear = 1;
    this->active = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.5f*scl_x, 0 * scl_y,  -1.5f * scl_z,   1.5f*scl_x, 0 * scl_y,  -1.5f * scl_z,  0 *scl_x, 4 * scl_y,  0 * scl_z,      
        -1.5f*scl_x, 0 * scl_y,  -1.5f * scl_z,  -1.5f*scl_x, 0 * scl_y,   1.5f * scl_z,  0 *scl_x, 4 * scl_y,  0 * scl_z,      
         1.5f*scl_x, 0 * scl_y,   1.5f * scl_z,  -1.5f*scl_x, 0 * scl_y,   1.5f * scl_z,  0 *scl_x, 4 * scl_y,  0 * scl_z,      
         1.5f*scl_x, 0 * scl_y,   1.5f * scl_z,   1.5f*scl_x, 0 * scl_y,  -1.5f * scl_z,  0 *scl_x, 4 * scl_y,  0 * scl_z,      
    };

    static const GLfloat vertex_buffer_data_island[] = {
        0 *scl_x, 3* scl_y,  0 * scl_z,    -7 *scl_x, 0 * scl_y,  -7 * scl_z,     0 *scl_x, 0 * scl_y,  -8 * scl_z,
        0 *scl_x, 3* scl_y,  0 * scl_z,    -7 *scl_x, 0 * scl_y,  -7 * scl_z,    -9 *scl_x, 0 * scl_y,  -6 * scl_z,
        0 *scl_x, 3* scl_y,  0 * scl_z,    -8 *scl_x, 0 * scl_y,   5 * scl_z,    -9 *scl_x, 0 * scl_y,  -6 * scl_z,
        0 *scl_x, 3* scl_y,  0 * scl_z,    -8 *scl_x, 0 * scl_y,   5 * scl_z,    -9 *scl_x, 0 * scl_y,   6 * scl_z,
        0 *scl_x, 3* scl_y,  0 * scl_z,    -9 *scl_x, 0 * scl_y,   7 * scl_z,    -9 *scl_x, 0 * scl_y,   6 * scl_z,
        0 *scl_x, 3* scl_y,  0 * scl_z,    -9 *scl_x, 0 * scl_y,   7 * scl_z,    -5 *scl_x, 0 * scl_y,  10 * scl_z,
        0 *scl_x, 3* scl_y,  0 * scl_z,     9 *scl_x, 0 * scl_y,   8 * scl_z,    -5 *scl_x, 0 * scl_y,  10 * scl_z,
        0 *scl_x, 3* scl_y,  0 * scl_z,     9 *scl_x, 0 * scl_y,   8 * scl_z,     7 *scl_x, 0 * scl_y,   9 * scl_z,
        0 *scl_x, 3* scl_y,  0 * scl_z,     7 *scl_x, 0 * scl_y,  10 * scl_z,     7 *scl_x, 0 * scl_y,   9 * scl_z,
        0 *scl_x, 3* scl_y,  0 * scl_z,     7 *scl_x, 0 * scl_y,  10 * scl_z,     9 *scl_x, 0 * scl_y,   5 * scl_z,
        0 *scl_x, 3* scl_y,  0 * scl_z,     9 *scl_x, 0 * scl_y,   8 * scl_z,     9 *scl_x, 0 * scl_y,   5 * scl_z,
        0 *scl_x, 3* scl_y,  0 * scl_z,     9 *scl_x, 0 * scl_y,   8 * scl_z,     0 *scl_x, 0 * scl_y,  -8 * scl_z,
    };

    static const GLfloat vertex_buffer_data_cannon_base[] = {
       length*scl_x, -height*scl_y, -width*scl_z,     length*scl_x, -height*scl_y,  width*scl_z,    length*scl_x,  height*scl_y, -width*scl_z,
       length*scl_x,  height*scl_y,  width*scl_z,     length*scl_x, -height*scl_y,  width*scl_z,    length*scl_x,  height*scl_y, -width*scl_z,
      -length*scl_x, -height*scl_y, -width*scl_z,    -length*scl_x, -height*scl_y,  width*scl_z,   -length*scl_x,  height*scl_y, -width*scl_z,
      -length*scl_x,  height*scl_y,  width*scl_z,    -length*scl_x, -height*scl_y,  width*scl_z,   -length*scl_x,  height*scl_y, -width*scl_z,
      -length*scl_x,  height*scl_y, -width*scl_z,     length*scl_x,  height*scl_y, -width*scl_z,   -length*scl_x,  height*scl_y,  width*scl_z,
       length*scl_x,  height*scl_y,  width*scl_z,     length*scl_x,  height*scl_y, -width*scl_z,   -length*scl_x,  height*scl_y,  width*scl_z,
      -length*scl_x, -height*scl_y, -width*scl_z,     length*scl_x, -height*scl_y, -width*scl_z,   -length*scl_x, -height*scl_y,  width*scl_z,
       length*scl_x, -height*scl_y,  width*scl_z,     length*scl_x, -height*scl_y, -width*scl_z,   -length*scl_x, -height*scl_y,  width*scl_z,
      -length*scl_x, -height*scl_y,  width*scl_z,     length*scl_x, -height*scl_y,  width*scl_z,   -length*scl_x,  height*scl_y,  width*scl_z,
       length*scl_x,  height*scl_y,  width*scl_z,     length*scl_x, -height*scl_y,  width*scl_z,   -length*scl_x,  height*scl_y,  width*scl_z,
      -length*scl_x, -height*scl_y, -width*scl_z,     length*scl_x, -height*scl_y, -width*scl_z,   -length*scl_x,  height*scl_y, -width*scl_z,
       length*scl_x,  height*scl_y, -width*scl_z,     length*scl_x, -height*scl_y, -width*scl_z,   -length*scl_x,  height*scl_y, -width*scl_z,
    };
    this->cannon_base = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_cannon_base, { 75, 83, 32 }, GL_FILL);
    this->island = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_island, {139,69,19}, GL_FILL);
}

void CheckPoint::draw(glm::mat4 VP) {
    this->cannon.draw(VP);
    if(this->active)  this->cannon_ball.draw(VP);
    Matrices.model = glm::mat4(1.0f);
    
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->appear)  draw3DObject(this->cannon_base);
    draw3DObject(this->island);
    //draw3DObject(this->cannon);
}

void CheckPoint::set_position(float x, float z) {
    this->position = glm::vec3(x, 0.001, z);
}

void CheckPoint::tick(float x, float y, float z) {
  this->cannon.appear = this->appear;
  this->cannon.tick(x,y,z);
  this->cannon_ball.tick(x,y,z);
  this->cannon_ball.appear = this->appear;
}

bounding_box_t CheckPoint::bounding_box(){
    bounding_box_t box = {this->position.x,this->position.y,this->position.z,this->length, this->height, this->width};
    return box;
}

bounding_box_t CheckPoint::bounding_box_cannon(){
  bounding_box_t box = this->cannon_ball.bounding_box();
  return box;
}