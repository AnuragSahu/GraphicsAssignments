#define GLM_ENABLE_EXPERIMENTAL
#include "ring.h"
#include "main.h"

Ring::Ring(float x, float z, color_t color) {
    this->position = glm::vec3(x, 8, z);
    this->rotation = 0;
    speed = 0.01;
    scl_x = scl_y = scl_z = 1;
    float breadth = 50.0f;
    this->appear = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
   static GLfloat vertex_buffer_data[906];
    int i=0;
    int number_0f_vertices_in_circle = 300;       
    for(; i <= number_0f_vertices_in_circle; i+=3){ 
        double angle = 2 * 3.14 * i / number_0f_vertices_in_circle;
        double x_in =  5*cos(angle);
        double y_in =  5*sin(angle);   
        vertex_buffer_data[i+0] = x_in;
        vertex_buffer_data[i+1] = y_in;
        vertex_buffer_data[i+2] = 0 * scl_z;
        
     }
    this->object = create3DObject(GL_LINE_STRIP, number_0f_vertices_in_circle, vertex_buffer_data, { 150, 141, 153}, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->appear) draw3DObject(this->object);
}

void Ring::set_position(float x, float z) {
    this->position = glm::vec3(x, 1, z);
}

void Ring::tick() {
    //this->position.x = 0.0f;
    //this->position.y = 0.0f;
    //this->position.z += 122.0f;

}

bounding_box_t Ring::bounding_box(){
    bounding_box_t box = {this->position.x,this->position.y,this->position.z,10,10,5};
    return box;
}