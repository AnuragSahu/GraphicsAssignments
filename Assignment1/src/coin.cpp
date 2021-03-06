#define GLM_ENABLE_EXPERIMENTAL
#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y,int points ,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->appear = 1;
    speed = 0.0;
    this->appear = 1;
    this->score = points;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    scl_x = 0.05f;
    scl_y = 0.05f;
    scl_z = 1.0f;
    width = 0.5f;
    speed_x = 0;
    speed_y = 0;
    color_t COLOR_GOLD = { 212,175,55 };
    this->coin_bounding_box.x = x;
    this->coin_bounding_box.y = y;
    this->coin_bounding_box.width = 4 * scl_x;
    this->coin_bounding_box.height = 4 * scl_y;

    static const GLfloat vertex_buffer_data[] = {
        -2*scl_x,     -1*scl_y,     scl_z,
        -1*scl_x,     -2*scl_y,     scl_z,
         0*scl_x,      0*scl_y,     scl_z,

        -2*scl_x,     -1*scl_y,     scl_z,
        -2*scl_x,      1*scl_y,     scl_z,
        0*scl_x,       0*scl_y,     scl_z,
        
        -2*scl_x,      1*scl_y,     scl_z,
        -1*scl_x,      2*scl_y,     scl_z,
         0*scl_x,      0*scl_y,     scl_z,

         1*scl_x,      2*scl_y,     scl_z,
        -1*scl_x,      2*scl_y,     scl_z,
         0*scl_x,      0*scl_y,     scl_z,
        
         1*scl_x,      2*scl_y,     scl_z,
         2*scl_x,      1*scl_y,     scl_z,
         0*scl_x,      0*scl_y,     scl_z,
 
         2*scl_x,     -1*scl_y,     scl_z,
         2*scl_x,      1*scl_y,     scl_z,
         0*scl_x,      0*scl_y,     scl_z,
 
         2*scl_x,     -1*scl_y,     scl_z,
         1*scl_x,     -2*scl_y,     scl_z,
         0*scl_x,      0*scl_y,     scl_z,

        -1*scl_x,     -2*scl_y,     scl_z,
         1*scl_x,     -2*scl_y,     scl_z,
         0*scl_x,      0*scl_y,     scl_z,
    };

    this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


void Coin::tick() {
    this->position.x += speed_x;
}

bounding_box_t Coin::bounding_box(){
    bounding_box_t box = {this->position.x, this->position.y, this->coin_bounding_box.height, this->coin_bounding_box.width };
    return box;
}
