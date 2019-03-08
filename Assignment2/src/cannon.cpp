#define GLM_ENABLE_EXPERIMENTAL
#include "cannon.h"
#include "main.h"

using namespace::std;
Cannon::Cannon(float x, float z, color_t color) {
    this->position = glm::vec3(x, 0.001, z);
    this->rotation_y = 0;
    this->rotation_z = 0;
    speed = 0.01;
    scl_x = scl_y = scl_z = 1;
    float breadth = 50.0f;
    float length = 3 * scl_x;
    float width =  3 * scl_z;
    float height = 3 * scl_y;

    this->length_c = 3 * scl_x;
    this->width_c  = 0.2 * scl_z;
    this->height_c = 0.2 * scl_y;
    this->mov_x_c = length_c, mov_y_c = 1.2*length_c, mov_z_c = 0;
    this->cannon_ball_release = 0;

    this->length_b = 0.2 * scl_x;
    this->width_b  = 0.2 * scl_z;
    this->height_b = 0.2 * scl_y;
    this->mov_x_b = 2.1*length_c, mov_y_b = 1.2*length_c, mov_z_b = 0;
    this->cannon_ball_speed = 0.05;
    this->appear = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data_cannon[] = {
       length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,     length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,    length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,
       length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,     length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,    length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,
      -length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,    -length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,   -length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,
      -length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,    -length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,   -length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,
      -length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,     length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,   -length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,
       length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,     length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,   -length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,
      -length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,     length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,   -length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,
       length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,     length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,   -length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,
      -length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,     length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,   -length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,
       length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,     length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,   -length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c,  width_c*scl_z+mov_z_c,
      -length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,     length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,   -length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,
       length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,     length_c*scl_x+mov_x_c, -height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,   -length_c*scl_x+mov_x_c,  height_c*scl_y+mov_y_c, -width_c*scl_z+mov_z_c,   
    };
    this->cannon = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_cannon, { 255, 255, 255 }, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    
    Matrices.model = glm::mat4(1.0f);
    
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_1    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate   = glm::rotate((float) (this->rotation_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate_1 );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->appear)  draw3DObject(this->cannon);
}

void Cannon::set_position(float x, float z) {
    this->position = glm::vec3(x, 0.001, z);
}

void Cannon::tick(float x, float y, float z) {
    float sin ,cos;
    if(this->cannon_ball_release = 0){
      this->cannon_ball_release = 1;
      sin = ((this->position.x-x)*(this->position.x-x))/(((this->position.x-x)*(this->position.x-x)) + ((this->position.z-z)*(this->position.z-z)));
    } cos = ((this->position.z-z)*(this->position.z-z))/(((this->position.x-x)*(this->position.x-x)) + ((this->position.z-z)*(this->position.z-z)));
    this->mov_x_b += this->cannon_ball_speed * sin;
    //mov_y_b = 1.2*length_c;
    this->mov_z_b -= this->cannon_ball_speed * cos;
    //cout << "ticking\n";
    if((((this->position.x-x)*(this->position.x-x)) + ((this->position.z-z)*(this->position.z-z)))!= 0)
    {
      this->rotation_y = acos(((this->position.x-x)*(this->position.x-x))/(((this->position.x-x)*(this->position.x-x)) + ((this->position.z-z)*(this->position.z-z)))) * 180.0/M_PI;
      this->rotation_z = acos(((this->position.x-x)*(this->position.x-x))/(((this->position.x-x)*(this->position.x-x)) + ((this->position.y-y)*(this->position.y-y)))) * 180.0/M_PI;
    }
}

bounding_box_t Cannon::bounding_box(){
    bounding_box_t box = {this->position.x,this->position.y,this->position.z,this->length_b, this->width_b, this->height_b};
    return box;
}