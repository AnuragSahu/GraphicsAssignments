#define GLM_ENABLE_EXPERIMENTAL
#include "missile.h"
#include "main.h"

Missile::Missile(float x, float y,float z, color_t color) {
    this->up = 15;
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.01;
    scl_x = scl_y = scl_z = 0.5;
    float breadth = 1.0f;
    float height = 1.0f;
    float length = 1.0f;
    float mov_x = 0.0f;
    float mov_y = 0.0f;
    float mov_z = 0.0f;
    this->appear = 0;
    this->len = length * scl_x;
    this->bre = breadth * scl_y;
    this->hit = height * scl_z;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -length*scl_x,  -height*scl_y,  -breadth*scl_z, // triangle 1 : begin
        -length*scl_x,  -height*scl_y,   breadth*scl_z,
        -length*scl_x,   height*scl_y,   breadth*scl_z, // triangle 1 : end
         length*scl_x,   height*scl_y,  -breadth*scl_z, // triangle 2 : begin
        -length*scl_x,  -height*scl_y,  -breadth*scl_z,
        -length*scl_x,   height*scl_y,  -breadth*scl_z, // triangle 2 : end
         length*scl_x,  -height*scl_y,   breadth*scl_z,
        -length*scl_x,  -height*scl_y,  -breadth*scl_z,
         length*scl_x,  -height*scl_y,  -breadth*scl_z,
         length*scl_x,   height*scl_y,  -breadth*scl_z,
         length*scl_x,  -height*scl_y,  -breadth*scl_z,
        -length*scl_x,  -height*scl_y,  -breadth*scl_z,
        -length*scl_x,  -height*scl_y,  -breadth*scl_z,
        -length*scl_x,   height*scl_y,   breadth*scl_z,
        -length*scl_x,   height*scl_y,  -breadth*scl_z,
         length*scl_x,  -height*scl_y,   breadth*scl_z,
        -length*scl_x,  -height*scl_y,   breadth*scl_z,
        -length*scl_x,  -height*scl_y,  -breadth*scl_z,
        -length*scl_x,   height*scl_y,   breadth*scl_z,
        -length*scl_x,  -height*scl_y,   breadth*scl_z,
         length*scl_x,  -height*scl_y,   breadth*scl_z,
         length*scl_x,   height*scl_y,   breadth*scl_z,
         length*scl_x,  -height*scl_y,  -breadth*scl_z,
         length*scl_x,   height*scl_y,  -breadth*scl_z,
         length*scl_x,  -height*scl_y,  -breadth*scl_z,
         length*scl_x,   height*scl_y,   breadth*scl_z,
         length*scl_x,  -height*scl_y,   breadth*scl_z,
         length*scl_x,   height*scl_y,   breadth*scl_z,
         length*scl_x,   height*scl_y,  -breadth*scl_z,
        -length*scl_x,   height*scl_y,  -breadth*scl_z,
         length*scl_x,   height*scl_y,   breadth*scl_z,
        -length*scl_x,   height*scl_y,  -breadth*scl_z,
        -length*scl_x,   height*scl_y,   breadth*scl_z,
         length*scl_x,   height*scl_y,   breadth*scl_z,
        -length*scl_x,   height*scl_y,   breadth*scl_z,
         length*scl_x,  -height*scl_y,   breadth*scl_z
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missile::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Missile::tick() {
    this->position.x -= 0.3f * sin(this->direction*3.14/180) ;
    this->position.y -= 0.1f;
    this->position.z -= 0.3f * cos(this->direction*3.14/180) ;
   // this->rotation = rotation;
    this->rotation += 1;
    if(this->position.y < -2){
      this->appear = 0;
    }

}

void Missile::drop_missile(float x, float y, float z, float rotation) {
    if(this->appear == 0){
        this->appear = 1;
        this->position.x = x;
        this-> position.y = y - 2;
        this->position.z = z;
        this->direction = rotation;
    }
}


bounding_box_t Missile::bounding_box(){
    bounding_box_t box = {this->position.x,this->position.y,this->position.z,this->len,this->bre,this->hit};
    return box;
}