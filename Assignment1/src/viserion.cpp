#define GLM_ENABLE_EXPERIMENTAL
#include "viserion.h"
#include "main.h"

#define len 25
#define wid 9

Viserion::Viserion(float x, float y,GLfloat scl, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->x = x;
    this->y = y;
    speed_x = 0;
    speed_y = 0;
    y_set = 0;
    viserion_w = 2.7f;
    viserion_h = 2.7f;
    scl_x = 0.2f;
    scl_y = 0.2f;
    scl_z = 1.0f;
    this->appear = 0;
    this->bitcoin_bounding_box.height = 24.0f*scl_y;
    this->bitcoin_bounding_box.width = 10.0f*scl_x;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static GLfloat vertex_buffer_data[] = {
        0.0f*scl_x,  3.0f*scl_y,  scl_z,    1.0f*scl_x,  0.0f*scl_y,  scl_z,    1.0f*scl_x,  2.0f*scl_y, scl_z,
        1.0f*scl_x,  0.0f*scl_y,  scl_z,    1.0f*scl_x,  2.0f*scl_y,  scl_z,    3.5f*scl_x,  1.0f*scl_y, scl_z,
        3.5f*scl_x,  3.0f*scl_y,  scl_z,    1.0f*scl_x,  2.0f*scl_y,  scl_z,    3.5f*scl_x,  1.0f*scl_y, scl_z,
        3.0f*scl_x,  5.0f*scl_y,  scl_z,    4.5f*scl_x,  5.0f*scl_y,  scl_z,    3.0f*scl_x,  3.2f*scl_y, scl_z,
        3.5f*scl_x,  4.0f*scl_y,  scl_z,    4.5f*scl_x,  4.0f*scl_y,  scl_z,    4.5f*scl_x,  5.0f*scl_y, scl_z,
        3.0f*scl_x,  4.0f*scl_y,  scl_z,    3.5f*scl_x,  4.0f*scl_y,  scl_z,    3.5f*scl_x,  2.0f*scl_y, scl_z,
        3.0f*scl_x,  4.0f*scl_y,  scl_z,    3.0f*scl_x,  2.0f*scl_y,  scl_z,    3.5f*scl_x,  2.0f*scl_y, scl_z,
        
        1.0f*scl_x,  0.0f*scl_y,  scl_z,    0.9f*scl_x, -1.0f*scl_y,  scl_z,    1.1f*scl_x, -1.0f*scl_y, scl_z,
        3.0f*scl_x,  1.0f*scl_y,  scl_z,    2.9f*scl_x, -1.0f*scl_y,  scl_z,    3.1f*scl_x, -1.0f*scl_y, scl_z, // Legs
    };
    this->object = create3DObject(GL_TRIANGLES, 9*3, vertex_buffer_data, color, GL_FILL);
}

void Viserion::draw(glm::mat4 VP) {
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

void Viserion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Viserion::set_y(float y) {
    this->position.y = y;
}
void Viserion::tick() {
    //this->rotation += speed;
    this->position.x += speed_x;
    this->position.y -= speed_y;
}

bounding_box_t Viserion::bounding_box(){
    bounding_box_t box = {this->position.x, this->position.y, this->bitcoin_bounding_box.width, this->bitcoin_bounding_box.height };
    return box;
}
