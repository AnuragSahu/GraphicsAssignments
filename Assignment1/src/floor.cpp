#define GLM_ENABLE_EXPERIMENTAL
#include "floor.h"
#include "main.h"

Floor::Floor(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 1;
    speed_x = 0;
    speed_y = 0;
    floor_w = 8.0f;
    floor_h = 2.8f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -floor_w + 0.5f,    -4.0f,   floor_h,    // triangle 1 : begin
         floor_w + 0.5f,    -4.0f,   floor_h,   
        -floor_w,           -3.0f,      0.0f,    // triangle 1 : end
        -floor_w,           -3.0f,      0.0f,    // triangle 2 : begin
         floor_w,           -3.0f,      0.0f,   
         floor_w + 0.5f,    -4.0f,   floor_h,    // triangle 2 : end

        /*2.0f,-2.0f, 2.0f,
        -2.0f,-2.0f,-2.0f,
        2.0f,-2.0f,-2.0f,
        2.0f, 2.0f,-2.0f,
        2.0f,-2.0f,-2.0f,
        -2.0f,-2.0f,-2.0f,
        -2.0f,-2.0f,-2.0f,
        -2.0f, 2.0f, 2.0f,
        -2.0f, 2.0f,-2.0f,
        2.0f,-2.0f, 2.0f,
        -2.0f,-2.0f, 2.0f,
        -2.0f,-2.0f,-2.0f,
        -2.0f, 2.0f, 2.0f,
        -2.0f,-2.0f, 2.0f,
        2.0f,-2.0f, 2.0f,
        2.0f, 2.0f, 2.0f,
        2.0f,-2.0f,-2.0f,
        2.0f, 2.0f,-2.0f,
        2.0f,-2.0f,-2.0f,
        2.0f, 2.0f, 2.0f,
        2.0f,-2.0f, 2.0f,
        2.0f, 2.0f, 2.0f,
        2.0f, 2.0f,-2.0f,
        -2.0f, 2.0f,-2.0f,
        2.0f, 2.0f, 2.0f,
        -2.0f, 2.0f,-2.0f,
        -2.0f, 2.0f, 2.0f,
        2.0f, 2.0f, 2.0f,
        -2.0f, 2.0f, 2.0f,
        2.0f,-2.0f, 2.0f*/
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Floor::draw(glm::mat4 VP) {
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

void Floor::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Floor::tick() {
    //this->rotation += 0.1;
    this->position.x += speed_x;
    this->position.y -= speed_y;

    if(this->position.x <-8)
        this->position.x = 8;
    if(this->position.x >8)
        this->position.x = -8;
    
}

