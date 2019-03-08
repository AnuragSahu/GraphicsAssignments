#define GLM_ENABLE_EXPERIMENTAL
#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float z, color_t color) {
    this->position = glm::vec3(x, 1, z);
    this->rotation = 0;
    speed = 0.01;
    scl_x = scl_y = scl_z = 1;
    float breadth = 50.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.5f*scl_x, 0 * scl_y,  -1.5f * scl_z,   1.5f*scl_x, 0 * scl_y,  -1.5f * scl_z,  0 *scl_x, 4 * scl_y,  0 * scl_z,      
        -1.5f*scl_x, 0 * scl_y,  -1.5f * scl_z,  -1.5f*scl_x, 0 * scl_y,   1.5f * scl_z,  0 *scl_x, 4 * scl_y,  0 * scl_z,      
         1.5f*scl_x, 0 * scl_y,   1.5f * scl_z,  -1.5f*scl_x, 0 * scl_y,   1.5f * scl_z,  0 *scl_x, 4 * scl_y,  0 * scl_z,      
         1.5f*scl_x, 0 * scl_y,   1.5f * scl_z,   1.5f*scl_x, 0 * scl_y,  -1.5f * scl_z,  0 *scl_x, 4 * scl_y,  0 * scl_z,      
    };

    static const GLfloat vertex_buffer_data_island[] = {
        0*scl_x, 0*scl_y,  0*scl_z,    -3*scl_x, 0*scl_y,  -3*scl_z,     0*scl_x, 0*scl_y,  -4*scl_z,
        0*scl_x, 0*scl_y,  0*scl_z,    -3*scl_x, 0*scl_y,  -3*scl_z,    -5*scl_x, 0*scl_y,  -2*scl_z,
        0*scl_x, 0*scl_y,  0*scl_z,    -4*scl_x, 0*scl_y,   1*scl_z,    -5*scl_x, 0*scl_y,  -2*scl_z,
        0*scl_x, 0*scl_y,  0*scl_z,    -4*scl_x, 0*scl_y,   1*scl_z,    -5*scl_x, 0*scl_y,   2*scl_z,
        0*scl_x, 0*scl_y,  0*scl_z,    -5*scl_x, 0*scl_y,   3*scl_z,    -5*scl_x, 0*scl_y,   2*scl_z,
        0*scl_x, 0*scl_y,  0*scl_z,    -5*scl_x, 0*scl_y,   3*scl_z,    -1*scl_x, 0*scl_y,   6*scl_z,
        0*scl_x, 0*scl_y,  0*scl_z,     5*scl_x, 0*scl_y,   4*scl_z,    -1*scl_x, 0*scl_y,   6*scl_z,
        0*scl_x, 0*scl_y,  0*scl_z,     5*scl_x, 0*scl_y,   4*scl_z,     3*scl_x, 0*scl_y,   5*scl_z,
        0*scl_x, 0*scl_y,  0*scl_z,     3*scl_x, 0*scl_y,   6*scl_z,     3*scl_x, 0*scl_y,   5*scl_z,
        0*scl_x, 0*scl_y,  0*scl_z,     3*scl_x, 0*scl_y,   6*scl_z,     5*scl_x, 0*scl_y,   1*scl_z,
        0*scl_x, 0*scl_y,  0*scl_z,     5*scl_x, 0*scl_y,   4*scl_z,     5*scl_x, 0*scl_y,   1*scl_z,
        0*scl_x, 0*scl_y,  0*scl_z,     5*scl_x, 0*scl_y,   4*scl_z,     0*scl_x, 0*scl_y,  -4*scl_z,
    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, { 150, 141, 153}, GL_FILL);
    this->island = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_island, {139,69,19}, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->island);
}

void Volcano::set_position(float x, float z) {
    this->position = glm::vec3(x, 1, z);
}

void Volcano::tick() {
    //this->position.x = 0.0f;
    //this->position.y = 0.0f;
    //this->position.z += 122.0f;

}

bounding_box_t Volcano::bounding_box(){
    bounding_box_t box = {this->position.x,this->position.y,this->position.z,5,5000,5};
    return box;
}