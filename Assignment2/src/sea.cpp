#define GLM_ENABLE_EXPERIMENTAL
#include "sea.h"
#include "main.h"

Sea::Sea(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    scl_x = scl_z = 0.3f;
    scl_y = 0.3f;
    float breadth = 500.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -breadth*scl_x,  0.01f*scl_y,   -breadth*scl_z,
         breadth*scl_x,  0.01f*scl_y,    breadth*scl_z,
         breadth*scl_x,  0.01f*scl_y,   -breadth*scl_z, 
        -breadth*scl_x,  0.01f*scl_y,   -breadth*scl_z,
         breadth*scl_x,  0.01f*scl_y,    breadth*scl_z,
        -breadth*scl_x,  0.01f*scl_y,    breadth*scl_z,  
    };
    /*static const GLfloat vertex_buffer_data_1[] = {
        -breadth*scl_x*2,  0.009f*scl_y,   -breadth*scl_z*2,
         breadth*scl_x*2,  0.009f*scl_y,    breadth*scl_z*2,
         breadth*scl_x*2,  0.009f*scl_y,   -breadth*scl_z*2, 
        -breadth*scl_x*2,  0.009f*scl_y,   -breadth*scl_z*2,
         breadth*scl_x*2,  0.009f*scl_y,    breadth*scl_z*2,
        -breadth*scl_x*2,  0.009f*scl_y,    breadth*scl_z*2, 
    };
    static const GLfloat vertex_buffer_data_2[] = {
        -breadth*scl_x * 4,  0.008f*scl_y,   -breadth*scl_z*4,
         breadth*scl_x * 4,  0.008f*scl_y,    breadth*scl_z*4,
         breadth*scl_x * 4,  0.008f*scl_y,   -breadth*scl_z*4, 
        -breadth*scl_x * 4,  0.008f*scl_y,   -breadth*scl_z*4,
         breadth*scl_x * 4,  0.008f*scl_y,    breadth*scl_z*4,
        -breadth*scl_x * 4,  0.008f*scl_y,    breadth*scl_z*4, 
    };
    static const GLfloat vertex_buffer_data_3[] = {
        -breadth*scl_x * 8,  0.007f*scl_y,   -breadth*scl_z*8,
         breadth*scl_x * 8,  0.007f*scl_y,    breadth*scl_z*8,
         breadth*scl_x * 8,  0.007f*scl_y,   -breadth*scl_z*8, 
        -breadth*scl_x * 8,  0.007f*scl_y,   -breadth*scl_z*8,
         breadth*scl_x * 8,  0.007f*scl_y,    breadth*scl_z*8,
        -breadth*scl_x * 8,  0.007f*scl_y,    breadth*scl_z*8, 
    };
    static const GLfloat vertex_buffer_data_4[] = {
        -breadth*scl_x * 16,  0.006f*scl_y,   -breadth*scl_z*16,
         breadth*scl_x * 16,  0.006f*scl_y,    breadth*scl_z*16,
         breadth*scl_x * 16,  0.006f*scl_y,   -breadth*scl_z*16, 
        -breadth*scl_x * 16,  0.006f*scl_y,   -breadth*scl_z*16,
         breadth*scl_x * 16,  0.006f*scl_y,    breadth*scl_z*16,
        -breadth*scl_x * 16,  0.006f*scl_y,    breadth*scl_z*16, 
    };*/
    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data,  {0,68,148}, GL_FILL);
    //this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_1,{0,80,148}, GL_FILL);
    //this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2,{0,93,148}, GL_FILL);
    //this->object[3] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_3,{0,105,148}, GL_FILL);
    //this->object[4] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_4,{0,117,148}, GL_FILL);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    /*for(int i=0;i<5;i++){
        draw3DObject(this->object[i]);
    }*/
    draw3DObject(this->object[0]);
}

void Sea::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Sea::tick(float x, float z) {
    this->position.x = x;
    this->position.z = z;
    //this->position.x = 0.0f;
    //this->position.y = 0.0f;
    //this->position.z += 122.0f;

}
