#define GLM_ENABLE_EXPERIMENTAL
#include "display.h"
#include "main.h"

using namespace std;

 Display:: Display(float x, float y,GLfloat scl, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->x = x;
    this->y = y;
    this->appear = 0;
    speed_x = 0;
    speed_y = 0;
    this->dir = 0;
    this->tick_time = 1;
    display_w = 2.7f;
    display_h = 2.7f;
    scl_x = 0.1f;
    scl_y = 0.2f;
    int len = 1, width = 8;
    this->color = color;

    scl_z = 2.0f;
    float mov = 5.0f*scl_x;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    //static GLfloat vertex_buffer_data[] = {
    //   -2*scl_x+mov,-2*scl_y,scl_z,   -2*scl_x+mov,2*scl_y,scl_z,  2*scl_x+mov,2*scl_y,scl_z,  2*scl_x+mov,-2*scl_y,scl_z,  -2*scl_x+mov,-2*scl_y,scl_z, // for 1
    //};
    //
    //this->object = create3DObject(GL_LINE_STRIP, 5, vertex_buffer_data, color, GL_FILL);
    static GLfloat for0[] = {
       -2*scl_x+mov, -2*scl_y,scl_z,   -2*scl_x+mov,2*scl_y,scl_z,
        2*scl_x+mov,  2*scl_y,scl_z,    2*scl_x+mov, -2*scl_y,scl_z,   
       -2*scl_x+mov,-2*scl_y,scl_z, // for 0 use 5 points
    }; this->object[0] = create3DObject(GL_LINE_STRIP, 5, for0, color, GL_FILL);
    static GLfloat for1[] = {
        0*scl_x+mov, -2*scl_y, scl_z,   0*scl_x+mov, 2*scl_y,scl_z, //for 1 use 2 points
    }; this->object[1] = create3DObject(GL_LINE_STRIP, 2, for1, color, GL_FILL);
    static GLfloat for2[] = {
       -2*scl_x+mov,  2*scl_y, scl_z,     2*scl_x+mov,  2*scl_y, scl_z,   
        2*scl_x+mov,  0*scl_y, scl_z,    -2*scl_x+mov,  0*scl_y, scl_z,    
       -2*scl_x+mov, -2*scl_y, scl_z,   
        2*scl_x+mov, -2*scl_y, scl_z, //for 2 use 7 points
    }; this->object[2] = create3DObject(GL_LINE_STRIP, 7, for2, color, GL_FILL);
    static GLfloat for3[] = {
       -2*scl_x+mov, 2*scl_y, scl_z,   2*scl_x+mov, 2*scl_y,scl_z,   
        2*scl_x+mov, 0*scl_y,scl_z,   -2*scl_x+mov, 0*scl_y,scl_z,    
        2*scl_x+mov, 0*scl_y,scl_z,    2*scl_x+mov, -2*scl_y,scl_z,  
       -2*scl_x+mov, -2*scl_y,scl_z,  //for 3 use 7 points
    }; this->object[3] = create3DObject(GL_LINE_STRIP, 7, for3, color, GL_FILL);
    static GLfloat for4[] = {
       -2*scl_x+mov, 2*scl_y, scl_z,   -2*scl_x+mov, 0*scl_y,scl_z,
        2*scl_x+mov, 2*scl_y,scl_z,     2*scl_x+mov, -2*scl_y,scl_z,
       -2*scl_x+mov, 0*scl_y,scl_z,     2*scl_x+mov,  0*scl_y,scl_z, //for 4 use 6 points and GL_LINES
     }; this->object[4] = create3DObject(GL_LINES, 6, for4, color, GL_FILL);
    static GLfloat for5[] = {
        2*scl_x+mov,  2*scl_y, scl_z,    -2*scl_x+mov,  2*scl_y, scl_z,   
       -2*scl_x+mov,  0*scl_y, scl_z,     2*scl_x+mov,  0*scl_y, scl_z,     
        2*scl_x+mov, -2*scl_y, scl_z,    -2*scl_x+mov, -2*scl_y, scl_z,     //for 5 use 7 points GL_LINE_STRIP
    }; this->object[5] = create3DObject(GL_LINE_STRIP, 7, for5, color, GL_FILL);
    static GLfloat for6[] = {
        2*scl_x+mov,  2*scl_y, scl_z,    -2*scl_x+mov,  2*scl_y, scl_z,   
       -2*scl_x+mov,  0*scl_y, scl_z,     2*scl_x+mov,  0*scl_y, scl_z,     
        2*scl_x+mov, -2*scl_y, scl_z,    -2*scl_x+mov, -2*scl_y, scl_z,    
       -2*scl_x+mov,  0*scl_y, scl_z,   //for 6 use 8 points GL_LINE_STRIP
    }; this->object[6] = create3DObject(GL_LINE_STRIP, 8, for6, color, GL_FILL);
    static GLfloat for7[] = {
        -2*scl_x+mov,  2*scl_y, scl_z,   2*scl_x+mov, 2*scl_y, scl_z,    
         2*scl_x+mov, -2*scl_y, scl_z,
        // for 7 use 3 points GL_LINE_STRIP
    }; this->object[7] = create3DObject(GL_LINE_STRIP, 3, for7, color, GL_FILL);
    static GLfloat for8[] = {
        -2*scl_x+mov,  2*scl_y, scl_z,   2*scl_x+mov,  2*scl_y, scl_z,
        -2*scl_x+mov,  0*scl_y, scl_z,   2*scl_x+mov,  0*scl_y, scl_z,
        -2*scl_x+mov, -2*scl_y, scl_z,   2*scl_x+mov, -2*scl_y, scl_z,
        -2*scl_x+mov,  2*scl_y, scl_z,  -2*scl_x+mov, -2*scl_y, scl_z,
        2*scl_x+mov,   2*scl_y, scl_z,   2*scl_x+mov, -2*scl_y, scl_z,
        // for 8 use 10 points GL_LINE
    }; this->object[8] = create3DObject(GL_LINES, 12, for8, color, GL_FILL);
    static GLfloat for9[] = {
        -2*scl_x+mov,  2*scl_y, scl_z,   2*scl_x+mov,  2*scl_y, scl_z,
        -2*scl_x+mov,  0*scl_y, scl_z,   2*scl_x+mov,  0*scl_y, scl_z,
        -2*scl_x+mov, -2*scl_y, scl_z,   2*scl_x+mov, -2*scl_y, scl_z,
        -2*scl_x+mov,  2*scl_y, scl_z,  -2*scl_x+mov,  0*scl_y, scl_z,
         2*scl_x+mov,  2*scl_y, scl_z,   2*scl_x+mov, -2*scl_y, scl_z,
        // for 8 use 10 points GL_LINE
    }; this->object[9] = create3DObject(GL_LINES, 10, for9, color, GL_FILL);
}

void Display::digits(float mov){
    
}

void  Display::draw(glm::mat4 VP,int myscr) {
    Matrices.model = glm::mat4(2.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[myscr]);
}

void  Display::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Display::activate(int opt){
    this->appear = opt;
}

void  Display::tick() {
    
}
