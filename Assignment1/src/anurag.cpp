#define GLM_ENABLE_EXPERIMENTAL
#include "anurag.h"
#include "main.h"

using namespace std;

Anurag::Anurag(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed_y = 0;
    this->speed_x = 0.05f; //Change here for game speed
    this->speedup = 0;
    this->gravity = 10.0f;
    this->insideSemi = 0;
    this->time = -1.0f;
    this->shield_time = 0.0f;
    this->tick_time = 0.0f;
    this->jump_speed = 300.0f;
    this->jumping = 0;
    this->y_org = 0;
    this->shield = 0;
    this->COLOR_SKIN = {255, 227, 159};

    scl_x = 0.1f;
    scl_y = 0.1f;
    scl_z = 1.0f;
    width = 0.5f;
    this->anurag_bounding_box.height = 6.0f*scl_y;
    this->anurag_bounding_box.width = 6.0f*scl_x;
    static const GLfloat vertex_buffer_data[] = {
        /* -1.0f*scl_x,    1.0f*scl_y,   scl_z, // triangle 1 : begin
         -1.0f*scl_x,   -1.0f*scl_y,   scl_z,
          1.0f*scl_x,    0.0f*scl_y,   scl_z, // triangle 1 : end*/
        0.0f*scl_x,  6.0f*scl_y,  scl_z,  3.0f*scl_x,  6.0f*scl_y,  scl_z,   3.0f*scl_x,  3.0f*scl_y,  scl_z,
        0.0f*scl_x,  6.0f*scl_y,  scl_z,  0.0f*scl_x,  3.0f*scl_y,  scl_z,   3.0f*scl_x,  3.0f*scl_y,  scl_z,//head, 2
        1.0f*scl_x,  3.0f*scl_y,  scl_z,  1.0f*scl_x,  2.0f*scl_y,  scl_z,   2.0f*scl_x,  2.0f*scl_y,  scl_z,
        1.0f*scl_x,  3.0f*scl_y,  scl_z,  2.0f*scl_x,  3.0f*scl_y,  scl_z,   2.0f*scl_x,  2.0f*scl_y,  scl_z,//neck, 2
        0.0f*scl_x,  2.0f*scl_y,  scl_z,  3.0f*scl_x,  2.0f*scl_y,  scl_z,   3.0f*scl_x, -3.0f*scl_y,  scl_z,
        0.0f*scl_x,  2.0f*scl_y,  scl_z,  0.0f*scl_x, -3.0f*scl_y,  scl_z,   3.0f*scl_x, -3.0f*scl_y,  scl_z,//body, 2
        1.5f*scl_x, -3.0f*scl_y,  scl_z,  2.0f*scl_x, -5.0f*scl_y,  scl_z,   1.0f*scl_x, -5.0f*scl_y,  scl_z,//legs, 1
        3.0f*scl_x,  1.0f*scl_y,  scl_z,  3.0f*scl_x,  0.0f*scl_y,  scl_z,   5.0f*scl_x,  0.0f*scl_y,  scl_z,
        3.0f*scl_x,  1.0f*scl_y,  scl_z,  5.0f*scl_x,  1.0f*scl_y,  scl_z,   5.0f*scl_x,  0.0f*scl_y,  scl_z,//hand, 2
       -3.0f*scl_x,  1.0f*scl_y,  scl_z,  0.0f*scl_x,  1.0f*scl_y,  scl_z,   0.0f*scl_x,  0.0f*scl_y,  scl_z,
       -3.0f*scl_x,  1.0f*scl_y,  scl_z,  0.0f*scl_x, -2.0f*scl_y,  scl_z,   0.0f*scl_x,  0.0f*scl_y,  scl_z,//jetat, 2
       -3.5f*scl_x,  4.0f*scl_y,  scl_z, -5.0f*scl_x,  2.0f*scl_y,  scl_z,  -2.0f*scl_x,  2.0f*scl_y,  scl_z,
       -2.0f*scl_x, -2.0f*scl_y,  scl_z, -5.0f*scl_x,  2.0f*scl_y,  scl_z,  -2.0f*scl_x,  2.0f*scl_y,  scl_z,
       -2.0f*scl_x, -2.0f*scl_y,  scl_z, -5.0f*scl_x,  2.0f*scl_y,  scl_z,  -5.0f*scl_x, -2.0f*scl_y,  scl_z,// jetpk, 3
       -5.0f*scl_x, -2.0f*scl_y,  scl_z, -6.0f*scl_x, -4.0f*scl_y,  scl_z,  -2.0f*scl_x, -2.0f*scl_y,  scl_z,
       -5.0f*scl_x, -2.0f*scl_y,  scl_z, -3.5f*scl_x, -5.0f*scl_y,  scl_z,  -2.0f*scl_x, -2.0f*scl_y,  scl_z,
       -5.0f*scl_x, -2.0f*scl_y,  scl_z, -1.0f*scl_x, -4.0f*scl_y,  scl_z,  -2.0f*scl_x, -2.0f*scl_y,  scl_z,// fire, 3
    };

    const color_t COLOR_L1_GREY = {52,61,70};
    const color_t COLOR_FIRE = {230, 167, 31};
    static const GLfloat head_buffer_data[] = {
        //0.0f*scl_x,  6.0f*scl_y,  scl_z,  3.0f*scl_x,  6.0f*scl_y,  scl_z,   3.0f*scl_x,  3.0f*scl_y,  scl_z,
        //0.0f*scl_x,  6.0f*scl_y,  scl_z,  0.0f*scl_x,  3.0f*scl_y,  scl_z,   3.0f*scl_x,  3.0f*scl_y,  scl_z,//head, 2
        0.0f*scl_x,  5.0f*scl_y,  scl_z,    1.0f*scl_x,  6.0f*scl_y,  scl_z,    2.0f*scl_x,  4.0f*scl_y,  scl_z,
        2.0f*scl_x,  6.0f*scl_y,  scl_z,    1.0f*scl_x,  6.0f*scl_y,  scl_z,    2.0f*scl_x,  4.0f*scl_y,  scl_z,
        2.0f*scl_x,  6.0f*scl_y,  scl_z,    3.0f*scl_x,  5.0f*scl_y,  scl_z,    2.0f*scl_x,  4.0f*scl_y,  scl_z,
        3.0f*scl_x,  4.0f*scl_y,  scl_z,    3.0f*scl_x,  5.0f*scl_y,  scl_z,    2.0f*scl_x,  4.0f*scl_y,  scl_z,
        3.0f*scl_x,  4.0f*scl_y,  scl_z,    2.0f*scl_x,  3.0f*scl_y,  scl_z,    2.0f*scl_x,  4.0f*scl_y,  scl_z,
        1.0f*scl_x,  3.0f*scl_y,  scl_z,    2.0f*scl_x,  3.0f*scl_y,  scl_z,    2.0f*scl_x,  4.0f*scl_y,  scl_z,
        1.0f*scl_x,  3.0f*scl_y,  scl_z,    0.0f*scl_x,  4.0f*scl_y,  scl_z,    2.0f*scl_x,  4.0f*scl_y,  scl_z,
        0.0f*scl_x,  5.0f*scl_y,  scl_z,    0.0f*scl_x,  4.0f*scl_y,  scl_z,    2.0f*scl_x,  4.0f*scl_y,  scl_z,
        

        };this->head = create3DObject(GL_TRIANGLE_STRIP, 8*3, head_buffer_data,COLOR_SKIN,GL_FILL);

    static const GLfloat neck_buffer_data[] = {
        1.0f*scl_x,  3.0f*scl_y,  scl_z,  1.0f*scl_x,  2.0f*scl_y,  scl_z,   2.0f*scl_x,  2.0f*scl_y,  scl_z,
        1.0f*scl_x,  3.0f*scl_y,  scl_z,  2.0f*scl_x,  3.0f*scl_y,  scl_z,   2.0f*scl_x,  2.0f*scl_y,  scl_z,//neck, 2
         3.0f*scl_x,  1.0f*scl_y,  scl_z,  3.0f*scl_x,  0.0f*scl_y,  scl_z,   5.0f*scl_x,  0.0f*scl_y,  scl_z,
        3.0f*scl_x,  1.0f*scl_y,  scl_z,  5.0f*scl_x,  1.0f*scl_y,  scl_z,   5.0f*scl_x,  0.0f*scl_y,  scl_z,//hand, 2
    };this->neck = create3DObject(GL_TRIANGLES, 4*3, neck_buffer_data,COLOR_SKIN,GL_FILL);

    static const GLfloat hand_buffer_data[] = {
        3.0f*scl_x,  1.0f*scl_y,  scl_z,  3.0f*scl_x,  0.0f*scl_y,  scl_z,   5.0f*scl_x,  0.0f*scl_y,  scl_z,
        3.0f*scl_x,  1.0f*scl_y,  scl_z,  5.0f*scl_x,  1.0f*scl_y,  scl_z,   5.0f*scl_x,  0.0f*scl_y,  scl_z,//hand, 2
    };this->hand = create3DObject(GL_TRIANGLES, 2*3, hand_buffer_data,COLOR_SKIN,GL_FILL);

    static const GLfloat jetpack_buffer_data[] = {
        -3.0f*scl_x,  1.0f*scl_y,  scl_z,  0.0f*scl_x,  1.0f*scl_y,  scl_z,   0.0f*scl_x,  0.0f*scl_y,  scl_z,
       -3.0f*scl_x,  1.0f*scl_y,  scl_z,  0.0f*scl_x, -2.0f*scl_y,  scl_z,   0.0f*scl_x,  0.0f*scl_y,  scl_z,//jetat, 2

       -3.5f*scl_x,  4.0f*scl_y,  scl_z, -5.0f*scl_x,  2.0f*scl_y,  scl_z,  -2.0f*scl_x,  2.0f*scl_y,  scl_z,
       -2.0f*scl_x, -2.0f*scl_y,  scl_z, -5.0f*scl_x,  2.0f*scl_y,  scl_z,  -2.0f*scl_x,  2.0f*scl_y,  scl_z,
       -2.0f*scl_x, -2.0f*scl_y,  scl_z, -5.0f*scl_x,  2.0f*scl_y,  scl_z,  -5.0f*scl_x, -2.0f*scl_y,  scl_z,// jetpk, 3
    };this->jetpack = create3DObject(GL_TRIANGLES, 5*3, jetpack_buffer_data,COLOR_L1_GREY,GL_FILL);
    static const GLfloat body_buffer_data[] = {
       0.0f*scl_x,  2.0f*scl_y,  scl_z,  3.0f*scl_x,  2.0f*scl_y,  scl_z,   3.0f*scl_x, -3.0f*scl_y,  scl_z,
        0.0f*scl_x,  2.0f*scl_y,  scl_z,  0.0f*scl_x, -3.0f*scl_y,  scl_z,   3.0f*scl_x, -3.0f*scl_y,  scl_z,//body, 2
    };this->body = create3DObject(GL_TRIANGLES, 2*3, body_buffer_data,{192,192,192},GL_FILL);

    static const GLfloat fire_buffer_data[] = {
        -5.0f*scl_x, -2.0f*scl_y,  scl_z, -6.0f*scl_x, -4.0f*scl_y,  scl_z,  -2.0f*scl_x, -2.0f*scl_y,  scl_z,
       -5.0f*scl_x, -2.0f*scl_y,  scl_z, -3.5f*scl_x, -5.0f*scl_y,  scl_z,  -2.0f*scl_x, -2.0f*scl_y,  scl_z,
       -5.0f*scl_x, -2.0f*scl_y,  scl_z, -1.0f*scl_x, -4.0f*scl_y,  scl_z,  -2.0f*scl_x, -2.0f*scl_y,  scl_z,// fire, 3
    };this->hand = create3DObject(GL_TRIANGLES, 3*3, fire_buffer_data,COLOR_FIRE,GL_FILL);
    static const GLfloat legs_buffer_data[] = {
               1.5f*scl_x, -3.0f*scl_y,  scl_z,  2.0f*scl_x, -5.0f*scl_y,  scl_z,   1.0f*scl_x, -5.0f*scl_y,  scl_z,//legs, 1
    };this->legs = create3DObject(GL_TRIANGLES, 1*3, legs_buffer_data,{192,192,192},GL_FILL);
    
    static const GLfloat vertex_buffer_data1[] = {
        -6.0f*scl_x,  -6.0f*scl_y,  scl_z,    -6.0f*scl_x,   6.0f*scl_y,  scl_z,
         6.0f*scl_x,   6.0f*scl_y,  scl_z,     6.0f*scl_x,  -6.0f*scl_y, scl_z,  
        -6.0f*scl_x,  -6.0f*scl_y,  scl_z,
    };
    this->y_org = this->position.y;
    this->object1 = create3DObject(GL_LINE_STRIP, 5, vertex_buffer_data1, color, GL_FILL);
    this->object = create3DObject(GL_TRIANGLES, 17*3, vertex_buffer_data, {255,255,255}, GL_FILL);
}

void Anurag::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object);
    draw3DObject(this->head);
    draw3DObject(this->neck);
    draw3DObject(this->hand);
    draw3DObject(this->body);
    draw3DObject(this->legs);
    //draw3DObject(this->hand);
    draw3DObject(this->body);
    draw3DObject(this->legs);
    draw3DObject(this->jetpack);
    draw3DObject(this->fire);

    if(this->shield)    draw3DObject(this->object1);
}

void Anurag::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Anurag::jump(){
    if(this->jumping == 0){
        this->speed_y = this->jump_speed;
        this->time = 0.0f;
        this->jumping = 1;
        this->y_org = this->position.y;
    }
}

void Anurag::upthrust(int up){
    if(up==1){
        this->jumping = 1;
    }
    else if(up == 0){
        this->jumping = 0;
    }
}

void Anurag::tick() {
    if(insideSemi){
        this->position.y = 0;
        this->tick_time += 0.01;
        this->x_org = -0.02*sin(this->tick_time);
        this->position.y = -2*sin(this->tick_time);
        if(this->tick_time > 3.2){
            this->insideSemi = 0;
            this->tick_time = 0;
        }
    }else{
        if(this->jumping==1 && this->position.y <= 2.0f){
            this->position.y += 0.1f;
        }
        if(this->jumping==0 && this->position.y > this->y_org){
            this->speed_y += 0.001f; //acceleration
            this->position.y -= this->speed_y;
            if(this->position.y <= this->y_org){
                this->position.y = this->y_org;
                this->speed_y = 0;
            }
        }
    }
    if(this->shield){
        this->shield_time += 1;
        if(this->shield_time > 1500){
            this->shield = 0;
            this->shield_time = 0;
        }
    }
    if(this->speedup){
        this->speedup_time +=1;
        this->speed_x = 0.6f;
        if(this->speedup_time > 300){
            this->speedup = 0;
            this->speedup_time = 0;
            this->speed_x = 0.05f;
        }
    }
}

bounding_box_t Anurag::bounding_box(){
    bounding_box_t box;
    if(this->shield == 0)
        box = { this->position.x, this->position.y,this->anurag_bounding_box.height, this->anurag_bounding_box.width };
    else if(this->shield == 1)
        box = { this->position.x, this->position.y,this->anurag_bounding_box.height, this->anurag_bounding_box.width };
    return box;
}
