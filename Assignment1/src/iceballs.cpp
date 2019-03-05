#define GLM_ENABLE_EXPERIMENTAL
#include "iceballs.h"
#include "main.h"

#define len 25
#define wid 9

Iceballs::Iceballs(float x, float y,GLfloat scl, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->x = x;
    this->y = y;
    speed_x = 0;
    speed_y = 0;
    iceballs_w = 2.7f;
    iceballs_h = 2.7f;
    scl_x = 0.1f;
    scl_y = 0.1f;
    scl_z = 1.0f;
    this->appear = 0;
    this->y_set = 0;
    this->bitcoin_bounding_box.height = 24.0f*scl_y;
    this->bitcoin_bounding_box.width = 10.0f*scl_x;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static GLfloat vertex_buffer_data[] = {
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
    this->object = create3DObject(GL_TRIANGLES, 9*3, vertex_buffer_data, color, GL_FILL);
}

void Iceballs::draw(glm::mat4 VP) {
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

void Iceballs::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Iceballs::set_y(float y) {
    if(y_set == 0){
        this->position.y = y;
        y_set = 1;
    }
}
void Iceballs::tick() {
    //this->rotation += speed;
    if(this->appear == 1){
        speed_x = 0.08f;
        this->position.x += speed_x;
        if(this->position.x > 12.0f){
            this->position.x = this->x;
        }
    }
    this->position.y -= speed_y;
}

bounding_box_t Iceballs::bounding_box(){
    bounding_box_t box = {this->position.x, this->position.y, this->bitcoin_bounding_box.width, this->bitcoin_bounding_box.height };
    return box;
}
