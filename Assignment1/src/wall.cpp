#define GLM_ENABLE_EXPERIMENTAL
#include "wall.h"
#include "main.h"

Wall::Wall(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed_x = 0;
    speed_y = 0;
    wall_w = 4.0f;
    wall_h = 3.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -wall_w,    wall_h,    0.0f, // triangle 1 : begin
         wall_w,    wall_h,    0.0f,
        -wall_w,   -wall_h,    0.0f, // triangle 1 : end
        -wall_w,   -wall_h,    0.0f, // triangle 2 : begin
         wall_w,   -wall_h,    0.0f,
         wall_w,    wall_h,    0.0f, // triangle 2 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Wall::draw(glm::mat4 VP) {
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

void Wall::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Wall::tick() {
    //this->rotation += speed;
    this->position.x += speed_x;
    this->position.y -= speed_y;

    if(this->position.x <-8)
        this->position.x = 8;
    if(this->position.x > 8)
        this->position.x = -8;
}
