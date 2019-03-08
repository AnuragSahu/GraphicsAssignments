#define GLM_ENABLE_EXPERIMENTAL
#include "display.h"
#include "main.h"

using namespace std;

 Display:: Display(float x, float y, color_t color) {
    //this->position = glm::vec3(x, y, 0);
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
    scl_x = 0.5f;
    scl_y = 0.04f;
    int len = 1, width = 8;
    this->color = color;
    this->score = 500;
    this->altitude = 0;
    this->fuel = 100;
    scl_z = 2.0f;
    float mov =  -3.5f*scl_x;
    float mov1 = -3.4f*scl_x;
    float mov3 = -3.3f*scl_x;
    float altitude_mov,altitude_mov1, altitude_mov3;
    
    altitude_mov =  -0.80f*scl_x;
    altitude_mov1 = -0.70f*scl_x;
    altitude_mov3 = -0.60f*scl_x;
    
    float score_mov =  -3.90f*scl_x;
    float score_mov1 = -3.80f*scl_x;
    float score_mov3 = -3.70f*scl_x;

    this->compass_mov_x = -1.2f*scl_x;

    

    //float scl_x_digit, scl_y_digit, scl_z_digit;
    scl_x_digit = 0.01f;
    scl_y_digit = 0.03f;
    //scl_z_digit = 0.0f*scl_z+3.005;
    scl_z = 0;
    scl_z_digit = -1;
    color_t color_digits = { 173,255,47 };
    mov_y_digit = -2.0f;
    float score_mov_y_digit = mov_y_digit;
    this->compass_mov_y = mov_y_digit;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static GLfloat speed_buffer_data_3rd_0[] = {
       -2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       // speed_buffer_data_3rd_ 0 use 5 points
    }; this->speed100[0] = create3DObject(GL_LINE_STRIP, 5, speed_buffer_data_3rd_0, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_3rd_1[] = {
        0*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
        0*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit, //speed_buffer_data_3rd_ 1 use 2 points
    }; this->speed100[1] = create3DObject(GL_LINE_STRIP, 2, speed_buffer_data_3rd_1, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_3rd_2[] = {
       -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit, //speed_buffer_data_3rd_ 2 use 7 points
    }; this->speed100[2] = create3DObject(GL_LINE_STRIP, 6, speed_buffer_data_3rd_2, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_3rd_3[] = {
       -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,  //speed_buffer_data_3rd_ 3 use 7 points
    }; this->speed100[3] = create3DObject(GL_LINE_STRIP, 7, speed_buffer_data_3rd_3, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_3rd_4[] = {
       -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit, //speed_buffer_data_3rd_ 4 use 6 points and GL_LINES
     }; this->speed100[4] = create3DObject(GL_LINES, 6, speed_buffer_data_3rd_4, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_3rd_5[] = {
        2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,    -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit, 
       -2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,    -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,     2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,     2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,    -2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,            //speed_buffer_data_3rd_ 5 use 7 points GL_LINE_STRIP
    }; this->speed100[5] = create3DObject(GL_LINE_STRIP, 5*2, speed_buffer_data_3rd_5, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_3rd_6[] = {
        2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,     
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,   //speed_buffer_data_3rd_ 6 use 8 points GL_LINE_STRIP
    }; this->speed100[6] = create3DObject(GL_LINE_STRIP, 7, speed_buffer_data_3rd_6, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_3rd_7[] = {
       -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov, 2*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // speed_buffer_data_3rd_ 7 use 3 points GL_LINE_STRIP
    }; this->speed100[7] = create3DObject(GL_LINE_STRIP, 3, speed_buffer_data_3rd_7, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_3rd_8[] = {
       -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // speed_buffer_data_3rd_ 8 use 10 points GL_LINE
    }; this->speed100[8] = create3DObject(GL_LINES, 12, speed_buffer_data_3rd_8, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_3rd_9[] = {
       -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // speed_buffer_data_3rd_ 8 use 10 points GL_LINE
    }; this->speed100[9] = create3DObject(GL_LINES, 10, speed_buffer_data_3rd_9, color_digits, GL_FILL);




    static GLfloat speed_buffer_data_2nd_0[] = {
       -2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
       // speed_buffer_data_2nd_ 0 use 5 points
    }; this->speed10[0] = create3DObject(GL_LINE_STRIP, 5, speed_buffer_data_2nd_0, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_2nd_1[] = {
        0*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,   
        0*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit, //speed_buffer_data_2nd_ 1 use 2 points
    }; this->speed10[1] = create3DObject(GL_LINES, 2, speed_buffer_data_2nd_1, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_2nd_2[] = {
       -2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit, //speed_buffer_data_2nd_ 2 use 7 points
    }; this->speed10[2] = create3DObject(GL_LINE_STRIP, 6, speed_buffer_data_2nd_2, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_2nd_3[] = {
       -2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,  //speed_buffer_data_2nd_ 3 use 7 points
    }; this->speed10[3] = create3DObject(GL_LINE_STRIP, 7, speed_buffer_data_2nd_3, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_2nd_4[] = {
       -2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit, //speed_buffer_data_2nd_ 4 use 6 points and GL_LINES
     }; this->speed10[4] = create3DObject(GL_LINES, 6, speed_buffer_data_2nd_4, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_2nd_5[] = {
        2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,     
        2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,     //speed_buffer_data_2nd_ 5 use 7 points GL_LINE_STRIP
    }; this->speed10[5] = create3DObject(GL_LINE_STRIP, 6, speed_buffer_data_2nd_5, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_2nd_6[] = {
        2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,     
        2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,   //speed_buffer_data_2nd_ 6 use 8 points GL_LINE_STRIP
    }; this->speed10[6] = create3DObject(GL_LINE_STRIP, 7, speed_buffer_data_2nd_6, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_2nd_7[] = {
       -2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov1, 2*scl_y_digit + mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
        // speed_buffer_data_2nd_ 7 use 3 points GL_LINE_STRIP
    }; this->speed10[7] = create3DObject(GL_LINE_STRIP, 3, speed_buffer_data_2nd_7, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_2nd_8[] = {
       -2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
        // speed_buffer_data_2nd_ 8 use 10 points GL_LINE
    }; this->speed10[8] = create3DObject(GL_LINES, 12, speed_buffer_data_2nd_8, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_2nd_9[] = {
       -2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
        // speed_buffer_data_2nd_ 8 use 10 points GL_LINE
    }; this->speed10[9] = create3DObject(GL_LINES, 10, speed_buffer_data_2nd_9, color_digits, GL_FILL);





    

    static GLfloat speed_buffer_data_1st_0[] = {
       -2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       // speed_buffer_data_1st_ 0 use 5 points
    }; this->speed1[0] = create3DObject(GL_LINE_STRIP, 5, speed_buffer_data_1st_0, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_1st_1[] = {
        0*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
        0*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit, //speed_buffer_data_1st_ 1 use 2 points
    }; this->speed1[1] = create3DObject(GL_LINE_STRIP, 2, speed_buffer_data_1st_1, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_1st_2[] = {
       -2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit, //speed_buffer_data_1st_ 2 use 7 points
    }; this->speed1[2] = create3DObject(GL_LINE_STRIP, 6, speed_buffer_data_1st_2, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_1st_3[] = {
       -2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,  //speed_buffer_data_1st_ 3 use 7 points
    }; this->speed1[3] = create3DObject(GL_LINE_STRIP, 7, speed_buffer_data_1st_3, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_1st_4[] = {
       -2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit, //speed_buffer_data_1st_ 4 use 6 points and GL_LINES
     }; this->speed1[4] = create3DObject(GL_LINES, 6, speed_buffer_data_1st_4, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_1st_5[] = {
        2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,     
        2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,     //speed_buffer_data_1st_ 5 use 7 points GL_LINE_STRIP
    }; this->speed1[5] = create3DObject(GL_LINE_STRIP, 6, speed_buffer_data_1st_5, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_1st_6[] = {
        2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,     
        2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,   //speed_buffer_data_1st_ 6 use 8 points GL_LINE_STRIP
    }; this->speed1[6] = create3DObject(GL_LINE_STRIP, 7, speed_buffer_data_1st_6, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_1st_7[] = {
       -2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+mov3, 2*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // speed_buffer_data_1st_ 7 use 3 points GL_LINE_STRIP
    }; this->speed1[7] = create3DObject(GL_LINE_STRIP, 3, speed_buffer_data_1st_7, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_1st_8[] = {
       -2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // speed_buffer_data_1st_ 8 use 10 points GL_LINE
    }; this->speed1[8] = create3DObject(GL_LINES, 12, speed_buffer_data_1st_8, color_digits, GL_FILL);
    static GLfloat speed_buffer_data_1st_9[] = {
       -2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // speed_buffer_data_1st_ 8 use 10 points GL_LINE
    }; this->speed1[9] = create3DObject(GL_LINES, 10, speed_buffer_data_1st_9, color_digits, GL_FILL);



////////////////////////////////////////////////////////////////////////////////////////////for speed//////////////////////////////////////////////////////////////

static GLfloat score_buffer_data_3rd_0[] = {
       -2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       // score_buffer_data_3rd_ 0 use 5 points
    }; this->score100[0] = create3DObject(GL_LINE_STRIP, 5, score_buffer_data_3rd_0, color_digits, GL_FILL);
    static GLfloat score_buffer_data_3rd_1[] = {
        0*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        0*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit, //score_buffer_data_3rd_ 1 use 2 points
    }; this->score100[1] = create3DObject(GL_LINE_STRIP, 2, score_buffer_data_3rd_1, color_digits, GL_FILL);
    static GLfloat score_buffer_data_3rd_2[] = {
       -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit, //score_buffer_data_3rd_ 2 use 7 points
    }; this->score100[2] = create3DObject(GL_LINE_STRIP, 6, score_buffer_data_3rd_2, color_digits, GL_FILL);
    static GLfloat score_buffer_data_3rd_3[] = {
       -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,  //score_buffer_data_3rd_ 3 use 7 points
    }; this->score100[3] = create3DObject(GL_LINE_STRIP, 7, score_buffer_data_3rd_3, color_digits, GL_FILL);
    static GLfloat score_buffer_data_3rd_4[] = {
       -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit, //score_buffer_data_3rd_ 4 use 6 points and GL_LINES
     }; this->score100[4] = create3DObject(GL_LINES, 6, score_buffer_data_3rd_4, color_digits, GL_FILL);
    static GLfloat score_buffer_data_3rd_5[] = {
        2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,    -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit, 
       -2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,    -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,     2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,     2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,    -2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,            //score_buffer_data_3rd_ 5 use 7 points GL_LINE_STRIP
    }; this->score100[5] = create3DObject(GL_LINE_STRIP, 5*2, score_buffer_data_3rd_5, color_digits, GL_FILL);
    static GLfloat score_buffer_data_3rd_6[] = {
        2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,     
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,   //score_buffer_data_3rd_ 6 use 8 points GL_LINE_STRIP
    }; this->score100[6] = create3DObject(GL_LINE_STRIP, 7, score_buffer_data_3rd_6, color_digits, GL_FILL);
    static GLfloat score_buffer_data_3rd_7[] = {
       -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov, 2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        // score_buffer_data_3rd_ 7 use 3 points GL_LINE_STRIP
    }; this->score100[7] = create3DObject(GL_LINE_STRIP, 3, score_buffer_data_3rd_7, color_digits, GL_FILL);
    static GLfloat score_buffer_data_3rd_8[] = {
       -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        // score_buffer_data_3rd_ 8 use 10 points GL_LINE
    }; this->score100[8] = create3DObject(GL_LINES, 12, score_buffer_data_3rd_8, color_digits, GL_FILL);
    static GLfloat score_buffer_data_3rd_9[] = {
       -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        // score_buffer_data_3rd_ 8 use 10 points GL_LINE
    }; this->score100[9] = create3DObject(GL_LINES, 10, score_buffer_data_3rd_9, color_digits, GL_FILL);




    static GLfloat score_buffer_data_2nd_0[] = {
       -2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,
       // score_buffer_data_2nd_ 0 use 5 points
    }; this->score10[0] = create3DObject(GL_LINE_STRIP, 5, score_buffer_data_2nd_0, color_digits, GL_FILL);
    static GLfloat score_buffer_data_2nd_1[] = {
        0*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,   
        0*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit, //score_buffer_data_2nd_ 1 use 2 points
    }; this->score10[1] = create3DObject(GL_LINES, 2, score_buffer_data_2nd_1, color_digits, GL_FILL);
    static GLfloat score_buffer_data_2nd_2[] = {
       -2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit, //score_buffer_data_2nd_ 2 use 7 points
    }; this->score10[2] = create3DObject(GL_LINE_STRIP, 6, score_buffer_data_2nd_2, color_digits, GL_FILL);
    static GLfloat score_buffer_data_2nd_3[] = {
       -2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,  //score_buffer_data_2nd_ 3 use 7 points
    }; this->score10[3] = create3DObject(GL_LINE_STRIP, 7, score_buffer_data_2nd_3, color_digits, GL_FILL);
    static GLfloat score_buffer_data_2nd_4[] = {
       -2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit, //score_buffer_data_2nd_ 4 use 6 points and GL_LINES
     }; this->score10[4] = create3DObject(GL_LINES, 6, score_buffer_data_2nd_4, color_digits, GL_FILL);
    static GLfloat score_buffer_data_2nd_5[] = {
        2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,     
        2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,     //score_buffer_data_2nd_ 5 use 7 points GL_LINE_STRIP
    }; this->score10[5] = create3DObject(GL_LINE_STRIP, 6, score_buffer_data_2nd_5, color_digits, GL_FILL);
    static GLfloat score_buffer_data_2nd_6[] = {
        2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,     
        2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,   //score_buffer_data_2nd_ 6 use 8 points GL_LINE_STRIP
    }; this->score10[6] = create3DObject(GL_LINE_STRIP, 7, score_buffer_data_2nd_6, color_digits, GL_FILL);
    static GLfloat score_buffer_data_2nd_7[] = {
       -2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov1, 2*scl_y_digit + score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,
        // score_buffer_data_2nd_ 7 use 3 points GL_LINE_STRIP
    }; this->score10[7] = create3DObject(GL_LINE_STRIP, 3, score_buffer_data_2nd_7, color_digits, GL_FILL);
    static GLfloat score_buffer_data_2nd_8[] = {
       -2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,
        // score_buffer_data_2nd_ 8 use 10 points GL_LINE
    }; this->score10[8] = create3DObject(GL_LINES, 12, score_buffer_data_2nd_8, color_digits, GL_FILL);
    static GLfloat score_buffer_data_2nd_9[] = {
       -2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov1,  0*scl_y_digit + score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov1,  2*scl_y_digit + score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov1, -2*scl_y_digit + score_mov_y_digit, scl_z_digit,
        // score_buffer_data_2nd_ 8 use 10 points GL_LINE
    }; this->score10[9] = create3DObject(GL_LINES, 10, score_buffer_data_2nd_9, color_digits, GL_FILL);





    

    static GLfloat score_buffer_data_1st_0[] = {
       -2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       // score_buffer_data_1st_ 0 use 5 points
    }; this->score1[0] = create3DObject(GL_LINE_STRIP, 5, score_buffer_data_1st_0, color_digits, GL_FILL);
    static GLfloat score_buffer_data_1st_1[] = {
        0*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        0*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit, //score_buffer_data_1st_ 1 use 2 points
    }; this->score1[1] = create3DObject(GL_LINE_STRIP, 2, score_buffer_data_1st_1, color_digits, GL_FILL);
    static GLfloat score_buffer_data_1st_2[] = {
       -2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit, //score_buffer_data_1st_ 2 use 7 points
    }; this->score1[2] = create3DObject(GL_LINE_STRIP, 6, score_buffer_data_1st_2, color_digits, GL_FILL);
    static GLfloat score_buffer_data_1st_3[] = {
       -2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,  //score_buffer_data_1st_ 3 use 7 points
    }; this->score1[3] = create3DObject(GL_LINE_STRIP, 7, score_buffer_data_1st_3, color_digits, GL_FILL);
    static GLfloat score_buffer_data_1st_4[] = {
       -2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit, //score_buffer_data_1st_ 4 use 6 points and GL_LINES
     }; this->score1[4] = create3DObject(GL_LINES, 6, score_buffer_data_1st_4, color_digits, GL_FILL);
    static GLfloat score_buffer_data_1st_5[] = {
        2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,     
        2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,     //score_buffer_data_1st_ 5 use 7 points GL_LINE_STRIP
    }; this->score1[5] = create3DObject(GL_LINE_STRIP, 6, score_buffer_data_1st_5, color_digits, GL_FILL);
    static GLfloat score_buffer_data_1st_6[] = {
        2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,     
        2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,   //score_buffer_data_1st_ 6 use 8 points GL_LINE_STRIP
    }; this->score1[6] = create3DObject(GL_LINE_STRIP, 7, score_buffer_data_1st_6, color_digits, GL_FILL);
    static GLfloat score_buffer_data_1st_7[] = {
       -2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,   
        2*scl_x_digit+score_mov3, 2*scl_y_digit+score_mov_y_digit, scl_z_digit,    
        2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        // score_buffer_data_1st_ 7 use 3 points GL_LINE_STRIP
    }; this->score1[7] = create3DObject(GL_LINE_STRIP, 3, score_buffer_data_1st_7, color_digits, GL_FILL);
    static GLfloat score_buffer_data_1st_8[] = {
       -2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        // score_buffer_data_1st_ 8 use 10 points GL_LINE
    }; this->score1[8] = create3DObject(GL_LINES, 12, score_buffer_data_1st_8, color_digits, GL_FILL);
    static GLfloat score_buffer_data_1st_9[] = {
       -2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
       -2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+score_mov3,  0*scl_y_digit+score_mov_y_digit, scl_z_digit,
        2*scl_x_digit+score_mov3,  2*scl_y_digit+score_mov_y_digit, scl_z_digit,  
        2*scl_x_digit+score_mov3, -2*scl_y_digit+score_mov_y_digit, scl_z_digit,
        // score_buffer_data_1st_ 8 use 10 points GL_LINE
    }; this->score1[9] = create3DObject(GL_LINES, 10, score_buffer_data_1st_9, color_digits, GL_FILL);



/////////////////////////////////////////////////////////////////////////////////////////////for altitude//////////////////////////////////////////////////////////




 static GLfloat altitude_buffer_data_3rd_0[] = {
       -2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       // altitude_buffer_data_3rd_ 0 use 5 points
    }; this->altitude100[0] = create3DObject(GL_LINE_STRIP, 5, altitude_buffer_data_3rd_0, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_3rd_1[] = {
        0*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
        0*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit, //altitude_buffer_data_3rd_ 1 use 2 points
    }; this->altitude100[1] = create3DObject(GL_LINE_STRIP, 2, altitude_buffer_data_3rd_1, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_3rd_2[] = {
       -2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit, //altitude_buffer_data_3rd_ 2 use 7 points
    }; this->altitude100[2] = create3DObject(GL_LINE_STRIP, 6, altitude_buffer_data_3rd_2, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_3rd_3[] = {
       -2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,  //altitude_buffer_data_3rd_ 3 use 7 points
    }; this->altitude100[3] = create3DObject(GL_LINE_STRIP, 7, altitude_buffer_data_3rd_3, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_3rd_4[] = {
       -2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit, //altitude_buffer_data_3rd_ 4 use 6 points and GL_LINES
     }; this->altitude100[4] = create3DObject(GL_LINES, 6, altitude_buffer_data_3rd_4, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_3rd_5[] = {
        2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,     
        2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,     //altitude_buffer_data_3rd_ 5 use 7 points GL_LINE_STRIP
    }; this->altitude100[5] = create3DObject(GL_LINE_STRIP, 6, altitude_buffer_data_3rd_5, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_3rd_6[] = {
        2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,     
        2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,   //altitude_buffer_data_3rd_ 6 use 8 points GL_LINE_STRIP
    }; this->altitude100[6] = create3DObject(GL_LINE_STRIP, 7, altitude_buffer_data_3rd_6, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_3rd_7[] = {
       -2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov, 2*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // altitude_buffer_data_3rd_ 7 use 3 points GL_LINE_STRIP
    }; this->altitude100[7] = create3DObject(GL_LINE_STRIP, 3, altitude_buffer_data_3rd_7, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_3rd_8[] = {
       -2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // altitude_buffer_data_3rd_ 8 use 10 points GL_LINE
    }; this->altitude100[8] = create3DObject(GL_LINES, 12, altitude_buffer_data_3rd_8, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_3rd_9[] = {
       -2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov,  0*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // altitude_buffer_data_3rd_ 8 use 10 points GL_LINE
    }; this->altitude100[9] = create3DObject(GL_LINES, 10, altitude_buffer_data_3rd_9, color_digits, GL_FILL);




    static GLfloat altitude_buffer_data_2nd_0[] = {
       -2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
       // altitude_buffer_data_2nd_ 0 use 5 points
    }; this->altitude10[0] = create3DObject(GL_LINE_STRIP, 5, altitude_buffer_data_2nd_0, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_2nd_1[] = {
        0*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,   
        0*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit, //altitude_buffer_data_2nd_ 1 use 2 points
    }; this->altitude10[1] = create3DObject(GL_LINES, 2, altitude_buffer_data_2nd_1, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_2nd_2[] = {
       -2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit, //altitude_buffer_data_2nd_ 2 use 7 points
    }; this->altitude10[2] = create3DObject(GL_LINE_STRIP, 6, altitude_buffer_data_2nd_2, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_2nd_3[] = {
       -2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,  //altitude_buffer_data_2nd_ 3 use 7 points
    }; this->altitude10[3] = create3DObject(GL_LINE_STRIP, 7, altitude_buffer_data_2nd_3, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_2nd_4[] = {
       -2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit, //altitude_buffer_data_2nd_ 4 use 6 points and GL_LINES
     }; this->altitude10[4] = create3DObject(GL_LINES, 6, altitude_buffer_data_2nd_4, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_2nd_5[] = {
        2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,     
        2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,     //altitude_buffer_data_2nd_ 5 use 7 points GL_LINE_STRIP
    }; this->altitude10[5] = create3DObject(GL_LINE_STRIP, 6, altitude_buffer_data_2nd_5, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_2nd_6[] = {
        2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,     
        2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,   //altitude_buffer_data_2nd_ 6 use 8 points GL_LINE_STRIP
    }; this->altitude10[6] = create3DObject(GL_LINE_STRIP, 7, altitude_buffer_data_2nd_6, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_2nd_7[] = {
       -2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov1, 2*scl_y_digit + mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
        // altitude_buffer_data_2nd_ 7 use 3 points GL_LINE_STRIP
    }; this->altitude10[7] = create3DObject(GL_LINE_STRIP, 3, altitude_buffer_data_2nd_7, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_2nd_8[] = {
       -2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
        // altitude_buffer_data_2nd_ 8 use 10 points GL_LINE
    }; this->altitude10[8] = create3DObject(GL_LINES, 12, altitude_buffer_data_2nd_8, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_2nd_9[] = {
       -2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov1,  0*scl_y_digit + mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov1,  2*scl_y_digit + mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov1, -2*scl_y_digit + mov_y_digit, scl_z_digit,
        // altitude_buffer_data_2nd_ 8 use 10 points GL_LINE
    }; this->altitude10[9] = create3DObject(GL_LINES, 10, altitude_buffer_data_2nd_9, color_digits, GL_FILL);





    

    static GLfloat altitude_buffer_data_1st_0[] = {
       -2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       // altitude_buffer_data_1st_ 0 use 5 points
    }; this->altitude1[0] = create3DObject(GL_LINE_STRIP, 5, altitude_buffer_data_1st_0, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_1st_1[] = {
        0*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
        0*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit, //altitude_buffer_data_1st_ 1 use 2 points
    }; this->altitude1[1] = create3DObject(GL_LINE_STRIP, 2, altitude_buffer_data_1st_1, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_1st_2[] = {
       -2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit, //altitude_buffer_data_1st_ 2 use 7 points
    }; this->altitude1[2] = create3DObject(GL_LINE_STRIP, 6, altitude_buffer_data_1st_2, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_1st_3[] = {
       -2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,  //altitude_buffer_data_1st_ 3 use 7 points
    }; this->altitude1[3] = create3DObject(GL_LINE_STRIP, 7, altitude_buffer_data_1st_3, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_1st_4[] = {
       -2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit, //altitude_buffer_data_1st_ 4 use 6 points and GL_LINES
     }; this->altitude1[4] = create3DObject(GL_LINES, 6, altitude_buffer_data_1st_4, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_1st_5[] = {
        2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,     
        2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,     //altitude_buffer_data_1st_ 5 use 7 points GL_LINE_STRIP
    }; this->altitude1[5] = create3DObject(GL_LINE_STRIP, 6, altitude_buffer_data_1st_5, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_1st_6[] = {
        2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
       -2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,     
        2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,    
       -2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,   //altitude_buffer_data_1st_ 6 use 8 points GL_LINE_STRIP
    }; this->altitude1[6] = create3DObject(GL_LINE_STRIP, 7, altitude_buffer_data_1st_6, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_1st_7[] = {
       -2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,   
        2*scl_x_digit+altitude_mov3, 2*scl_y_digit+mov_y_digit, scl_z_digit,    
        2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // altitude_buffer_data_1st_ 7 use 3 points GL_LINE_STRIP
    }; this->altitude1[7] = create3DObject(GL_LINE_STRIP, 3, altitude_buffer_data_1st_7, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_1st_8[] = {
       -2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // altitude_buffer_data_1st_ 8 use 10 points GL_LINE
    }; this->altitude1[8] = create3DObject(GL_LINES, 12, altitude_buffer_data_1st_8, color_digits, GL_FILL);
    static GLfloat altitude_buffer_data_1st_9[] = {
       -2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
       -2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
       -2*scl_x_digit+altitude_mov3,  0*scl_y_digit+mov_y_digit, scl_z_digit,
        2*scl_x_digit+altitude_mov3,  2*scl_y_digit+mov_y_digit, scl_z_digit,  
        2*scl_x_digit+altitude_mov3, -2*scl_y_digit+mov_y_digit, scl_z_digit,
        // altitude_buffer_data_1st_ 8 use 10 points GL_LINE
    }; this->altitude1[9] = create3DObject(GL_LINES, 10, altitude_buffer_data_1st_9, color_digits, GL_FILL);


    static const GLfloat compass_data[] = {
       2*scl_x_digit+compass_mov_x,   2*scl_y_digit+mov_y_digit, scl_z_digit,
       2*scl_x_digit+compass_mov_x,  -2*scl_y_digit+mov_y_digit, scl_z_digit, // this is for the Needle in compass
    }; this->compass_red = create3DObject(GL_LINES, 4, compass_data, color_digits, GL_FILL);
    this->compass_white = create3DObject(GL_LINES, 4, compass_data, color_digits, GL_FILL);

    static GLfloat blank[] = {
       -4*scl_x+0,  -2*scl_y-2,   0.0f*scl_z,  
        4*scl_x+0,   2*scl_y-2,   0.0f*scl_z,  
        4*scl_x+0,  -2*scl_y-2,   0.0f*scl_z, 
       -4*scl_x+0,  -2*scl_y-2,   0.0f*scl_z,  
        4*scl_x+0,   2*scl_y-2,   0.0f*scl_z,  
       -4*scl_x+0,   2*scl_y-2,   0.0f*scl_z, 
    }; this->blank = create3DObject(GL_TRIANGLES, 2*3, blank, color, GL_FILL);

    scl_x = 0.2f;
    scl_y = 0.025f;
    GLfloat fuel[] = {
         1*scl_x-1, -1*scl_y-1.955f, 0.01f*scl_z+0,   -1*scl_x-1, ((this->fuel/50) -1)*scl_y-1.955f, 0.01f*scl_z+0 ,    1*scl_x-1, ((this->fuel/50) -1)*scl_y-1.955f, 0.01f*scl_z+0,
        -1*scl_x-1, -1*scl_y-1.955f, 0.01f*scl_z+0,    1*scl_x-1,                   -1*scl_y-1.955f, 0.01f*scl_z+0,    -1*scl_x-1, ((this->fuel/50) -1)*scl_y-1.955f, 0.01f*scl_z+0,
    }; this->fuel_meter = create3DObject(GL_TRIANGLES, 2*3, fuel, {5,5,5}, GL_FILL);
    this->fuel_meter_full = create3DObject(GL_TRIANGLES, 2*3, fuel, {5,5,5}, GL_FILL);

    GLfloat health[] = {
         1*scl_x-1, -1*scl_y-2.025f, 0.001f*scl_z+0,   -1*scl_x-1, ((this->fuel/50) -1)*scl_y-2.025f, 0.001f*scl_z+0 ,    1*scl_x-1, ((this->fuel/50) -1)*scl_y-2.025f, 0.001f*scl_z+0,
        -1*scl_x-1, -1*scl_y-2.025f, 0.001f*scl_z+0,    1*scl_x-1,                   -1*scl_y-2.025f, 0.001f*scl_z+0,    -1*scl_x-1, ((this->fuel/50) -1)*scl_y-2.025f, 0.001f*scl_z+0,
    }; this->health_meter = create3DObject(GL_TRIANGLES, 2*3, health, {255,255,255}, GL_FILL);
    this->health_meter_full = create3DObject(GL_TRIANGLES, 2*3, health, {5,5,5}, GL_FILL);
    this->scl_x_digit = 0.02f;
    this->scl_y_digit = 0.03f;
    this->scl_z_digit = -1;
    GLfloat compass_cover_data[] = {
      -2*scl_x_digit+compass_mov_x,     -1*scl_y_digit+mov_y_digit,     scl_z_digit,
      -1*scl_x_digit+compass_mov_x,     -2*scl_y_digit+mov_y_digit,     scl_z_digit,
       0*scl_x_digit+compass_mov_x,      0*scl_y_digit+mov_y_digit,     scl_z_digit,
      -2*scl_x_digit+compass_mov_x,     -1*scl_y_digit+mov_y_digit,     scl_z_digit,
      -2*scl_x_digit+compass_mov_x,      1*scl_y_digit+mov_y_digit,     scl_z_digit,
       0*scl_x_digit+compass_mov_x,      0*scl_y_digit+mov_y_digit,     scl_z_digit,
      -2*scl_x_digit+compass_mov_x,      1*scl_y_digit+mov_y_digit,     scl_z_digit,
      -1*scl_x_digit+compass_mov_x,      2*scl_y_digit+mov_y_digit,     scl_z_digit,
       0*scl_x_digit+compass_mov_x,      0*scl_y_digit+mov_y_digit,     scl_z_digit,
       1*scl_x_digit+compass_mov_x,      2*scl_y_digit+mov_y_digit,     scl_z_digit,
      -1*scl_x_digit+compass_mov_x,      2*scl_y_digit+mov_y_digit,     scl_z_digit,
       0*scl_x_digit+compass_mov_x,      0*scl_y_digit+mov_y_digit,     scl_z_digit,
       1*scl_x_digit+compass_mov_x,      2*scl_y_digit+mov_y_digit,     scl_z_digit,
       2*scl_x_digit+compass_mov_x,      1*scl_y_digit+mov_y_digit,     scl_z_digit,
       0*scl_x_digit+compass_mov_x,      0*scl_y_digit+mov_y_digit,     scl_z_digit,
       2*scl_x_digit+compass_mov_x,     -1*scl_y_digit+mov_y_digit,     scl_z_digit,
       2*scl_x_digit+compass_mov_x,      1*scl_y_digit+mov_y_digit,     scl_z_digit,
       0*scl_x_digit+compass_mov_x,      0*scl_y_digit+mov_y_digit,     scl_z_digit,
       2*scl_x_digit+compass_mov_x,     -1*scl_y_digit+mov_y_digit,     scl_z_digit,
       1*scl_x_digit+compass_mov_x,     -2*scl_y_digit+mov_y_digit,     scl_z_digit,
       0*scl_x_digit+compass_mov_x,      0*scl_y_digit+mov_y_digit,     scl_z_digit,
      -1*scl_x_digit+compass_mov_x,     -2*scl_y_digit+mov_y_digit,     scl_z_digit,
       1*scl_x_digit+compass_mov_x,     -2*scl_y_digit+mov_y_digit,     scl_z_digit,
       0*scl_x_digit+compass_mov_x,      0*scl_y_digit+mov_y_digit,     scl_z_digit,
    };  this->compass_cover = create3DObject(GL_LINE_STRIP, 8*3, compass_cover_data, {0,0,0}, GL_FILL);
}

void Display::digits(float mov){
    
}

void  Display::draw(glm::mat4 VP, int score, int altitude, int speed) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    //glm::mat4 MVP = glm::mat4(1.0f);//*/  VP * Matrices.model;
    glm::mat4 MVP =  Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->blank);
    draw3DObject(this->fuel_meter_full);
    draw3DObject(this->fuel_meter);
    draw3DObject(this->health_meter);
    draw3DObject(this->health_meter_full);
    draw3DObject(this->speed1[speed%10]);
    speed =speed /10;
    draw3DObject(this->speed10[speed%10]);
    speed =speed /10;
    draw3DObject(this->speed100[speed%10]);
    
    draw3DObject(this->score1[score%10]);
    score =score /10;
    draw3DObject(this->score10[score%10]);
    score =score /10;
    draw3DObject(this->score100[score%10]);
    draw3DObject(this->altitude1[altitude%10]);
    altitude = altitude /10;
    draw3DObject(this->altitude10[altitude%10]);
    altitude =altitude /10;
    draw3DObject(this->altitude100[altitude%10]);
    draw3DObject(this->compass_red);
    draw3DObject(this->compass_white);
    draw3DObject(this->compass_cover);
}

void  Display::set_position(float x, float y,float z, float rotate) {
    this->position = glm::vec3(1, 1, 0);
}

void Display::activate(int opt){
    this->appear = opt;
}

void  Display::tick(float x, float y,float z, float rotate, float altitude, float fuel, float health) {
    //this->position = glm::vec3(x, y, z);
    this->position = glm::vec3(1, 2.92, 0);
    //this->rotation = rotate;
    this->altitude = altitude;
    this->fuel = fuel;
    GLfloat fuel_1[] = {
        -((this->fuel/50.0f) -1)*scl_x-1, -1*scl_y-1.955f, 0.011f*scl_z+0,                          1*scl_x-1, -1*scl_y-1.955f, 0.011f*scl_z+0,    -((this->fuel/50.0f) -1)*scl_x-1, 1*scl_y-1.955f, 0.011f*scl_z+0,
                               1*scl_x-1, -1*scl_y-1.955f, 0.011f*scl_z+0,   -((this->fuel/50.0f) -1)*scl_x-1,  1*scl_y-1.955f, 0.011f*scl_z+0 ,                          1*scl_x-1, 1*scl_y-1.955f, 0.011f*scl_z+0,         
    };
    this->fuel_meter = create3DObject(GL_TRIANGLES, 2*3, fuel_1, {255,165,0}, GL_FILL);
    if(health>100) health = 100;
    this->health = health;
    GLfloat health_1[] = {
        -((this->health/50.0f)-1)*scl_x-1, -1*scl_y-2.025f, 0.011f*scl_z-0.001f,                            1*scl_x-1, -1*scl_y-2.025f, 0.011f*scl_z-0.001f,    -((this->health/50.0f) -1)*scl_x-1, 1*scl_y-2.025f, 0.011f*scl_z-0.001f,
                                1*scl_x-1, -1*scl_y-2.025f, 0.011f*scl_z-0.001f,   -((this->health/50.0f) -1)*scl_x-1,  1*scl_y-2.025f, 0.011f*scl_z-0.001f ,                            1*scl_x-1, 1*scl_y-2.025f, 0.011f*scl_z-0.001f,         
    }; this->health_meter = create3DObject(GL_TRIANGLES, 2*3, health_1, {5,165,0}, GL_FILL);
    this->scl_x_digit = 0.02f;
    this->scl_y_digit = 0.03f;
    this->scl_z_digit = -1;
    GLfloat compass_data_2[] = {
      2*scl_x_digit*(float)sin(rotate*3.14/180)+compass_mov_x,   2*scl_y_digit*(float)cos(rotate*3.14/180)+mov_y_digit, scl_z_digit,
      0*scl_x_digit*(float)sin(rotate*3.14/180)+compass_mov_x,   0*scl_y_digit*(float)cos(rotate*3.14/180)+mov_y_digit, scl_z_digit,
    };this->compass_red = create3DObject(GL_LINES, 4, compass_data_2, {255,5,5}, GL_FILL);
    GLfloat compass_data_1[] = {
        0*scl_x_digit*(float)sin(rotate*3.14/180)+compass_mov_x,   0*scl_y_digit*(float)cos(rotate*3.14/180)+mov_y_digit, scl_z_digit,
     -2*scl_x_digit*(float)sin(rotate*3.14/180)+compass_mov_x,  -2*scl_y_digit*(float)cos(rotate*3.14/180)+mov_y_digit, scl_z_digit, // this is for the Needle in compass
    }; this->compass_white = create3DObject(GL_LINES, 4, compass_data_1, {255,255,255}, GL_FILL);
}
