#define GLM_ENABLE_EXPERIMENTAL
#include "speedup.h"
#include "main.h"

using namespace std;

#define len 25
#define wid 9

 SpeedUp:: SpeedUp(float x, float y,GLfloat scl, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->x_org = x;
    this->y_org = y;
    this->x = x;
    this->y = y;
    speed_x = 0;
    speed_y = 0;
    this->dir = 0;
    this->tick_time = 1;
    speedup_w = 2.7f;
    speedup_h = 2.7f;
    scl_x = 0.2f;
    scl_y = 0.2f;
    scl_z =1.0f;
    this->appear = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static GLfloat vertex_buffer_data[] = {
      -2.0f*scl_x,  2.0f*scl_y,  scl_z,    -2.0f*scl_x,-2.0f*scl_y, scl_z, -1.0f*scl_x, 2.0f*scl_y, scl_z,
      -1.0f*scl_x, -2.0f*scl_y,  scl_z,    -2.0f*scl_x,-2.0f*scl_y, scl_z, -1.0f*scl_x, 2.0f*scl_y, scl_z,
      -2.0f*scl_x,  2.0f*scl_y,  scl_z,     1.0f*scl_x, 0.0f*scl_y, scl_z,  2.0f*scl_x, 2.0f*scl_y, scl_z,
       2.0f*scl_x, -2.0f*scl_y,  scl_z,     1.0f*scl_x, 0.0f*scl_y, scl_z,  2.0f*scl_x, 2.0f*scl_y, scl_z,
      -2.0f*scl_x, -2.0f*scl_y,  scl_z,     1.0f*scl_x, 0.0f*scl_y, scl_z,  2.0f*scl_x,-2.0f*scl_y, scl_z,
    };
    
    this->object = create3DObject(GL_TRIANGLES, 5*3, vertex_buffer_data, color, GL_FILL);
}

void  SpeedUp::draw(glm::mat4 VP) {
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

void  SpeedUp::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void  SpeedUp::tick() {
    this->position.x = this->x_org;
    this->position.x += speed_x;
    this->x_org = this->position.x;
    //this->position.x = 2*sin(this->tick_time);
    if(cos(this->tick_time)>0){
        this->position.x = this->x_org + sin(this->tick_time);
        this->position.y = this->y_org + cos(this->tick_time);
    }else if(cos(this->tick_time)<=0){
        this->position.x = this->x_org + sin(this->tick_time);
        this->position.y = this->y_org - cos(this->tick_time);
    }

    if(this->tick_time > 50)  this->tick_time = 0;
    this->tick_time += 0.05;
}

bounding_box_t SpeedUp::bounding_box(){
    bounding_box_t box = {this->position.x,this->position.y,2*scl_x,2*scl_y};
    return box;
}
