#define GLM_ENABLE_EXPERIMENTAL
#include "ring.h"
#include "main.h"

using namespace std;

#define len 25
#define wid 9

 Ring:: Ring(float x, float y,GLfloat scl, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->x_org = x;
    this->y_org = y;
    this->x = x;
    this->y = y;
    speed_x = 0;
    speed_y = 0;
    this->dir = 0;
    this->tick_time = 1;
    ring_w = 2.7f;
    ring_h = 2.7f;
    scl_x = 0.1f;
    scl_y = 0.1f;
    scl_z = 1.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[906];
    int i;
    for(i = 0; i <= 150; i+=3){
        double angle = 2 * 3.14 * i / 300;
        double x =  2*cos(angle);
        double y = -2*sin(angle);
        vertex_buffer_data[i+0] = x;
        vertex_buffer_data[i+1] = y;
        vertex_buffer_data[i+2] = scl_z;
     }
     vertex_buffer_data[i+0] = x;
     vertex_buffer_data[i+2] = x_org;
     vertex_buffer_data[i+3] = y;

    this->object = create3DObject(GL_LINE_STRIP, 50, vertex_buffer_data, color, GL_FILL);
}
void  Ring::draw(glm::mat4 VP) {
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

void  Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void  Ring::tick() {
    this->position.x += speed_x;
}

