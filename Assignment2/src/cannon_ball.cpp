#define GLM_ENABLE_EXPERIMENTAL
#include "cannon_ball.h"
#include "main.h"

using namespace::std;
CannonBall::CannonBall(float x, float z, color_t color) {
    this->position = glm::vec3(x, 0.001, z);
    this->position_temp = this->position;
    this->rotation_y = 0;
    this->rotation_z = 0;
    speed = 0.01;
    scl_x = scl_y = scl_z = 1;
    float breadth = 50.0f;
    float length = 3 * scl_x;
    float width =  3 * scl_z;
    float height = 3 * scl_y;
    this->ball_tick = 0;
    this->target_z = 0;
    this->target_x = 0;
    this->target_y = 0;
    this->appear = 0;
    this->cannon_ball_release = 0;
    this->length_b = 0.2 * scl_x;
    this->width_b  = 0.2 * scl_z;
    this->height_b = 0.2 * scl_y;
    this->mov_x_b = 0, mov_y_b = 0, mov_z_b = 0;
    this->cannon_ball_speed = 0.05;
    this->speed_x = 0;
    this->speed_z = 0;
    this->speed_y = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data_cannon_ball[] = {
       length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,     length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,    length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,
       length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,     length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,    length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,
      -length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,    -length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,   -length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,
      -length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,    -length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,   -length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,
      -length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,     length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,   -length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,
       length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,     length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,   -length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,
      -length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,     length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,   -length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,
       length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,     length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,   -length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,
      -length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,     length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,   -length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,
       length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,     length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,   -length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b,  width_b*scl_z+mov_z_b,
      -length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,     length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,   -length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,
       length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,     length_b*scl_x+mov_x_b, -height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,   -length_b*scl_x+mov_x_b,  height_b*scl_y+mov_y_b, -width_b*scl_z+mov_z_b,   
    };
    this->cannon_ball = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_cannon_ball, { 0,0,0 }, GL_FILL);
}

void CannonBall::draw(glm::mat4 VP) {
    
    Matrices.model = glm::mat4(1.0f);
    
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_yaw    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_pitch   = glm::rotate((float) (this->rotation_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate_pitch *rotate_yaw );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->appear)   draw3DObject(this->cannon_ball);
}

void CannonBall::set_position(float x, float z) {
    this->position = glm::vec3(x, 0.001, z);
}

void CannonBall::reset(){
  this->target_x = 0;
  this->target_y = 0;
  this->target_z = 0;
  this->position = this->position_temp;
  this->ball_tick = 1;
  this->cannon_ball_release = 0;
}

void CannonBall::tick(float x, float y, float z) {
    this->rotation_y+=10;            
    if(this->cannon_ball_release == 0){
      this->cannon_ball_release = 1;
      this->target_x = x;
      this->target_y = y;
      this->target_z = z;
      this->ball_tick = 1;
      this->appear = 1;
      this->speed_x = (this->position.x - target_x)/(5*sqrt((this->position.x - target_x)*(this->position.x - target_x) + (this->position.y - target_y)*(this->position.y - target_y)+(this->position.z - target_z)*(this->position.z - target_z)));
      this->speed_y = (this->position.y - target_y)/(5*sqrt((this->position.x - target_x)*(this->position.x - target_x) + (this->position.y - target_y)*(this->position.y - target_y)+(this->position.z - target_z)*(this->position.z - target_z)));
      this->speed_z = (this->position.z - target_z)/(5*sqrt((this->position.x - target_x)*(this->position.x - target_x) + (this->position.y - target_y)*(this->position.y - target_y)+(this->position.z - target_z)*(this->position.z - target_z)));
    } 
    if(this->ball_tick != 0){ this->ball_tick+= 1;}
    if(this->ball_tick > 200) { 
      this->target_x = 0;
      this->target_y = 0;
      this->target_z = 0;
      this->position = this->position_temp;
      this->ball_tick = 1;
      this->cannon_ball_release = 0;
    }
    this->position.x -= this->speed_x;
    this->position.y -= this->speed_y;
    this->position.z -= this->speed_z;
    //if((abs(this->position.x) > abs(target_x) || abs(this->position.y) > abs(target_y) || abs(this->position.z) > abs(target_z))){
    //  this->position.y -= 1;
    //  if(this->position.y < 0){
    //    reset();
    //  }
    //}
}

bounding_box_t CannonBall::bounding_box(){
    bounding_box_t box = {this->position.x,this->position.y,this->position.z,this->length_b,this->width_b,this->height_b};
    return box;
}