#define GLM_ENABLE_EXPERIMENTAL
#include "subdesign.h"
#include "main.h"

SubDesign::SubDesign(float x, float y,GLfloat scl, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->x = x;
    this->y = y;
    speed_x = 0;
    speed_y = 0;
    subdesign_w = 2.7f;
    subdesign_h = 2.7f;
    //scl = 0.6f;
    shift_x = -2.58f;
    shift_y = -2.48f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        0*scl+shift_x, 1*scl+shift_y, 0, 1*scl+shift_x, 0*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        0*scl+shift_x, 1*scl+shift_y, 0, 0*scl+shift_x, 3*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        1*scl+shift_x, 4*scl+shift_y, 0, 0*scl+shift_x, 3*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        1*scl+shift_x, 4*scl+shift_y, 0, 1*scl+shift_x, 5*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        0*scl+shift_x, 6*scl+shift_y, 0, 1*scl+shift_x, 5*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        0*scl+shift_x, 6*scl+shift_y, 0, 0*scl+shift_x, 8*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        1*scl+shift_x, 9*scl+shift_y, 0, 0*scl+shift_x, 8*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        1*scl+shift_x, 9*scl+shift_y, 0, 3*scl+shift_x, 9*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        4*scl+shift_x, 8*scl+shift_y, 0, 3*scl+shift_x, 9*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        4*scl+shift_x, 8*scl+shift_y, 0, 5*scl+shift_x, 8*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        6*scl+shift_x, 9*scl+shift_y, 0, 5*scl+shift_x, 8*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        6*scl+shift_x, 9*scl+shift_y, 0, 8*scl+shift_x, 9*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        9*scl+shift_x, 8*scl+shift_y, 0, 8*scl+shift_x, 9*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        9*scl+shift_x, 8*scl+shift_y, 0, 9*scl+shift_x, 6*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        8*scl+shift_x, 5*scl+shift_y, 0, 9*scl+shift_x, 6*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        8*scl+shift_x, 5*scl+shift_y, 0, 8*scl+shift_x, 4*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        9*scl+shift_x, 3*scl+shift_y, 0, 8*scl+shift_x, 4*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        9*scl+shift_x, 3*scl+shift_y, 0, 9*scl+shift_x, 1*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        8*scl+shift_x, 0*scl+shift_y, 0, 9*scl+shift_x, 1*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        8*scl+shift_x, 0*scl+shift_y, 0, 6*scl+shift_x, 0*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        5*scl+shift_x, 1*scl+shift_y, 0, 6*scl+shift_x, 0*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        5*scl+shift_x, 1*scl+shift_y, 0, 4*scl+shift_x, 1*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        3*scl+shift_x, 0*scl+shift_y, 0, 4*scl+shift_x, 1*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0,
        3*scl+shift_x, 0*scl+shift_y, 0, 1*scl+shift_x, 0*scl+shift_y, 0, 4*scl+shift_x, 4*scl+shift_y, 0
        
    };

    this->object = create3DObject(GL_TRIANGLES, 25*3, vertex_buffer_data, color, GL_FILL);
}

void SubDesign::draw(glm::mat4 VP) {
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

void SubDesign::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void SubDesign::tick() {
    //this->rotation += speed;
    this->position.x += speed_x;
    this->position.y -= speed_y;

    if(this->position.x <-8  /*+this->x*/)
        this->position.x = 8 /*-this->x*/;
    if(this->position.x > 8   /*-this->x*/)
        this->position.x =-8 /*+this->x*/;
    
}
