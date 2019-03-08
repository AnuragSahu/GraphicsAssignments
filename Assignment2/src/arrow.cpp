#define GLM_ENABLE_EXPERIMENTAL
#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float z, color_t color) {
    this->up = 20;
    this->position = glm::vec3(x, this->up, z);
    this->rotation = 0;
    speed = 0.01;
    scl_x = scl_y = scl_z = 1;
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

       -1.0f*scl_x+mov_x, +2.0f*scl_y+mov_y, +0.0f*scl_z+mov_z,  -1.0f*scl_x+mov_x, -2.0f*scl_y+mov_y, -0.0f*scl_z+mov_z,  1.0f*scl_x+mov_x,  2.0f*scl_y+mov_y,  0.0f*scl_z+mov_z,
        1.0f*scl_x+mov_x, -2.0f*scl_y+mov_y, -0.0f*scl_z+mov_z,  -1.0f*scl_x+mov_x, -2.0f*scl_y+mov_y, -0.0f*scl_z+mov_z,  1.0f*scl_x+mov_x,  2.0f*scl_y+mov_y,  0.0f*scl_z+mov_z,
       -3.0f*scl_x+mov_x, -2.0f*scl_y+mov_y, -0.0f*scl_z+mov_z,   0.0f*scl_x+mov_x, -4.0f*scl_y+mov_y, -0.0f*scl_z+mov_z,  3.0f*scl_x+mov_x, -2.0f*scl_y+mov_y, -0.0f*scl_z+mov_z, 
       +0.0f*scl_x+mov_x, +2.0f*scl_y+mov_y, -1.0f*scl_z+mov_z,  -0.0f*scl_x+mov_x, -2.0f*scl_y+mov_y, -1.0f*scl_z+mov_z,  0.0f*scl_x+mov_x,  2.0f*scl_y+mov_y,  1.0f*scl_z+mov_z,
       -0.0f*scl_x+mov_x, -2.0f*scl_y+mov_y,  1.0f*scl_z+mov_z,  -0.0f*scl_x+mov_x, -2.0f*scl_y+mov_y, -1.0f*scl_z+mov_z,  0.0f*scl_x+mov_x,  2.0f*scl_y+mov_y,  1.0f*scl_z+mov_z,
       -0.0f*scl_x+mov_x, -2.0f*scl_y+mov_y, -3.0f*scl_z+mov_z,  -0.0f*scl_x+mov_x, -4.0f*scl_y+mov_y,  0.0f*scl_z+mov_z, -0.0f*scl_x+mov_x, -2.0f*scl_y+mov_y,  3.0f*scl_z+mov_z, 

    };

    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, {254, 50, 50}, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
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

void Arrow::set_position(float x,float z) {
    this->position = glm::vec3(x, this->up, z);
}

void Arrow::tick() {
    float arrow_vertcal_speed = 0.8f;
    if(this->arr_dir==1){
      this->position.y += arrow_vertcal_speed;
      if(this->position.y > 40) this->arr_dir = 0;
    }
    else{
      this->position.y -= arrow_vertcal_speed;
      if(this->position.y < 15) this->arr_dir = 1;
    }
    this->rotation += 3;
}

bounding_box_t Arrow::bounding_box(){
    bounding_box_t box = {this->position.x,this->position.y,this->position.z,5,5,5000};
    return box;
}