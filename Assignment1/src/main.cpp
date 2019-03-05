#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"
#include "timer.h"
#include "ball.h"
#include "anurag.h"
#include "wall.h"
#include "floor.h"
#include "coin.h"
#include "design.h"
#include "subdesign.h"
#include "bitcoin.h"
#include "fireyellow.h"
#include "firegrey.h"
#include "firebeam.h"
#include "firebeamgrey.h"
#include "boomerang.h"
#include "magnet.h"
#include "score.h"
#include "display.h"
#include "life1.h"
#include "speedup.h"
#include "ring.h"
#include "waterballoons.h"
#include "viserion.h"
#include "iceballs.h"
#include "shield.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

// colors DEFINED AS PER CHOICE
extern const color_t COLOR_GOLD = { 212,175,55 };
extern const color_t COLOR_FIRE = {230, 167, 31};
extern const color_t COLOR_FIRE_BALLS = {132, 132, 130};
extern const color_t COLOR_BITCOIN_GOLD = { 255,215,0};
extern const color_t COLOR_L3_GREY = {79,91,102};
extern const color_t COLOR_L1_GREY = {52,61,70};
extern const color_t COLOR_GREENYELLOW = {173,255,47};
extern const color_t COLOR_BLUE = {150,125,255};
extern const color_t COLOR_BROWN = {244,164,96};
extern const color_t COLOR_SNOW = {205,201,201};

//extern const color_t COLOR_RED = {173,2,2};


/**************************
* Customizable functions *
**************************/

Ball ball1;
Ball ball2;
Wall wall1;
Wall wall2;
Design design1;
Design design2;
SubDesign subdesign1;
SubDesign subdesign2;
Coin coin[100];
Bitcoin bitc[10];
Floor floor1;
Floor floor2;
Fireyellow fireyellow[15];
Firegrey firegrey[15];
Boomerang boomerang[2];
Life1 life1;
SpeedUp speedup;
Ring ring;
Magnet magnet;
Score score;
Display display[4];
Firebeam firebeam[3];
Firebeamgrey firebeamgrey[3];
Waterballoons waterballoons;
Anurag anurag;
Viserion viserion;
Iceballs iceballs;
Shield shield[4];

double myscr = 0;
double tick_time = 0;
float cscl_y = 0.8;
float cscl_x = 0.8;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
double distanceTravelled = 0;
float speed = 0.05f;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    //Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    wall1.draw(VP);
    wall2.draw(VP);
    design1.draw(VP);
    design2.draw(VP);
    subdesign1.draw(VP);
    subdesign2.draw(VP);
    floor1.draw(VP);
    floor2.draw(VP);
    //coin.draw(VP);
    for(int looper =0; looper < 100; looper++){
        if(coin[looper].appear){ coin[looper].draw(VP); }
    }
    for(int looper = 0;looper < 10; looper ++){
        if(bitc[looper].appear) bitc[looper].draw(VP);
    }for(int looper = 0;looper < 15; looper ++){
        if(fireyellow[looper].appear)   fireyellow[looper].draw(VP);
        if(fireyellow[looper].appear)   firegrey[looper].draw(VP);
    }
    if(viserion.appear)     viserion.draw(VP);
    if(viserion.appear)     iceballs.draw(VP); // recheck the condition
    for(int looper = 0;looper < 3; looper ++){
        if(firebeam[looper].appear){
            firebeam[looper].draw(VP);
            firebeamgrey[looper].draw(VP);
        }
    }
    //ball1.draw(VP);
    //ball2.draw(VP);
    anurag.draw(VP);
    if(waterballoons.appear)    waterballoons.draw(VP);
    for(int i=0;i<2;i++) boomerang[i].draw(VP);
    if(magnet.appear)   magnet.draw(VP);
    if(life1.appear)    life1.draw(VP);
    if(speedup.appear)  speedup.draw(VP);
    for(int looper = 0;looper<4;looper++)   if(shield[looper].appear)   shield[looper].draw(VP);
    ring.draw(VP);
    score.draw(VP);
    int tmp = myscr;
    if(tmp<0){ tmp = 0; myscr = 0; }
    for(int i = 0;i<4;i++){
        display[i].draw(VP,tmp%10);
        tmp = tmp/10;
    }   
}

void moveAll(float speed){
    if(magnet.appear == 1) speed -= 0.5*speed;
    if(anurag.insideSemi==1){
        speed = anurag.x_org;
    }    
    distanceTravelled += speed;
    if(distanceTravelled < -150.0f*cscl_x){
         viserion.appear = 1;
         iceballs.appear = 1;
         viserion.set_y(anurag.position.y);
         iceballs.set_y(anurag.position.y);
    }if(distanceTravelled < -350.0f*cscl_x){ viserion.appear = 0;}
    if(distanceTravelled < -352.0f*cscl_x) {speed = 0;  cout << "Your Scored : "; cout << myscr; cout << "\n"; exit(0);}
    wall1.speed_x    = speed;
    wall2.speed_x    = speed;
    design1.speed_x  = speed;
    design2.speed_x  = speed;
    subdesign1.speed_x = speed;
    subdesign2.speed_x = speed;
    floor1.speed_x   = speed;
    floor2.speed_x   = speed;
    for(int looper=0;looper<15;looper++){
        fireyellow[looper].speed_x = speed;
        firegrey[looper].speed_x = speed;
    }
    for(int i=0;i<2;i++) boomerang[i].speed_x = speed;
    life1.speed_x = speed;
    speedup.speed_x = speed;
    for(int looper=0;looper<4;looper++)    shield[looper].speed_x = speed;
    ring.speed_x = speed;
    magnet.speed_x = speed;
    for(int looper = 0;looper < 3; looper ++){
        firebeam[looper].speed_x = speed;
        firebeamgrey[looper].speed_x = speed;
    }
    //coin.speed_x     = speed;
    for(int looper =0; looper < 100; looper++){
        coin[looper].speed_x = speed;
    }
    for(int looper =0; looper < 10; looper++){
        bitc[looper].speed_x = speed;
    }
}

void tick_input(GLFWwindow *window) {
    
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    if (right && up && !left) {
        moveAll(-anurag.speed_x);
        anurag.upthrust(1);
    }

    else if (right && !up && !left) {
        moveAll(-anurag.speed_x);
        anurag.upthrust(0);
    }

    else if (left && !up && !right) {
        moveAll(anurag.speed_x);
        anurag.upthrust(0);
    }

    else if (left && up && !right) {
        moveAll(anurag.speed_x);
        anurag.upthrust(1);
    }

    else if(up && !right && !left) {
        anurag.upthrust(1);
        moveAll(0.0);
    }

    else if(!up && !right && !left){
        anurag.upthrust(0);
        moveAll(0.0);
    }
    if(down){ waterballoons.activate(anurag.position.x, anurag.position.y); }
}

void tick_elements() {
    tick_time += 1;
    wall1.tick();
    wall2.tick();
    design1.tick();
    design2.tick();
    subdesign1.tick();
    subdesign2.tick();
    floor1.tick();
    floor2.tick();
    speedup.tick();
    for(int looper = 0;looper<4;looper++)   shield[looper].tick();
    ring.tick();
    //coin.tick();
    for(int looper = 0; looper < 100; looper++) coin[looper].tick();
    for(int looper = 0;looper< 10;looper++) bitc[looper].tick();
    for(int looper=0;looper<15;looper++){
        fireyellow[looper].tick();
        firegrey[looper].tick();
    }
    viserion.tick();
    iceballs.tick();
    for(int i=0;i<2;i++)    boomerang[i].tick();
    magnet.tick();
    //score.tick();
    //display.tick();
    life1.tick();
    for(int looper=0;looper<3;looper++){
        firebeam[looper].tick();
        firebeamgrey[looper].tick();
    }
    anurag.tick();
    waterballoons.tick();
    camera_rotation_angle += 1;
    detect_coll();
    if(ring.position.x < 2 && ring.position.x > 0 && anurag.position.y > 2){
        anurag.insideSemi = 1;
    }
}

void detect_coll(){
    for(int looper = 0; looper < 100; looper++){
        if(coin[looper].appear && detect_collision(anurag.bounding_box(), coin[looper].bounding_box())){
            myscr += coin[looper].score;
            coin[looper].appear = 0;
        }
    } // Collisions with coins
    if(bitc[0].appear && detect_collision(bitc[0].bounding_box(), anurag.bounding_box())){
        myscr += 50;
        bitc[0].appear = 0;
    }
    
    for(int i=0;i<3;i++){
        if(firebeam[i].appear && anurag.insideSemi== 0 && detect_collision(anurag.bounding_box(), firebeam[i].bounding_box())){ 
            if(anurag.shield)   firebeam[i].appear = 0;
            else myscr -= 1; }
        if(waterballoons.appear && firebeam[i].appear && detect_collision(waterballoons.bounding_box(), firebeam[i].bounding_box())){
            firebeam[i].appear = 0;
            waterballoons.appear = 0;
        }
    }
    for(int looper=0;looper<15;looper++){
        if(waterballoons.appear && fireyellow[looper].appear && detect_collision(waterballoons.bounding_box(), fireyellow[looper].bounding_box())){
            fireyellow[looper].appear = 0;
            waterballoons.appear = 0;
        }
    }
    if(bitc[1].appear && detect_collision(bitc[1].bounding_box(), anurag.bounding_box()) ){
        myscr += 50;
        bitc[1].appear = 0;
        magnet.activate(1);;
    }
    if(life1.appear && detect_collision(life1.bounding_box(), anurag.bounding_box())){
        myscr += 100;
        life1.appear = 0;
    }
    if(speedup.appear && detect_collision(speedup.bounding_box(), anurag.bounding_box())){
        myscr += 50;
        anurag.speedup = 1;
        speedup.appear = 0;
    }
    for(int looper=0;looper<4;looper++){
        if(shield[looper].appear && detect_collision(shield[looper].bounding_box(), anurag.bounding_box())){
            shield[looper].appear = 0;
            anurag.shield = 1;
        }
    }
    
    // collision with enemies
    for(int looper=0;looper<15;looper++){
    if(fireyellow[looper].appear && anurag.insideSemi== 0 && detect_collision(anurag.bounding_box(), fireyellow[looper].bounding_box())){
        if(anurag.shield) fireyellow[looper].appear = 0;
        else myscr -= 1;
    }}if(viserion.appear && anurag.insideSemi== 0 && iceballs.appear && detect_collision(iceballs.bounding_box(), anurag.bounding_box())){
        if(anurag.shield) iceballs.appear = 0;
        else myscr -= 5;
        iceballs.appear = 0;
        iceballs.y_set = 0;
        iceballs.position.x = iceballs.x;
        
    }
    for(int i=0;i<2;i++){
    if(anurag.insideSemi== 0 && detect_collision(boomerang[i].bounding_box(), anurag.bounding_box())){
        if(!anurag.shield)
        myscr -= 5;
    }}
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    
    ball1 = Ball(-3, 0, COLOR_RED);
    ball2 = Ball(3,0, COLOR_BLACK);
    anurag = Anurag(0,-2.5,COLOR_GREENYELLOW);
    wall1 = Wall(0,0, COLOR_BLACK);
    design1 = Design(0,0,0.6, COLOR_GREEN);
    subdesign1 = SubDesign(0,0,0.55, COLOR_BLACK);
    wall2 = Wall(8,0, COLOR_BLACK);
    design2 = Design(8,0,0.6, COLOR_GREEN);
    subdesign2 = SubDesign(8,0,0.55, COLOR_BLACK);
    floor1 = Floor(0,0, COLOR_GREEN);
    floor2 = Floor(8,0, COLOR_GREEN);
    score = Score(0,3.5f,1,COLOR_BLACK);
    waterballoons = Waterballoons(0,0,1,COLOR_BLUE);
    viserion = Viserion(-5*cscl_x,0.0*cscl_y,1, COLOR_BROWN);
    iceballs = Iceballs(-5*cscl_x,0.0*cscl_y,1, COLOR_SNOW);
    

    display[3] = Display(-1.5,3.5f,1,COLOR_GREEN);
    display[2] = Display(-1.0,3.5f,1,COLOR_GREEN);
    display[1] = Display(-0.5,3.5f,1,COLOR_GREEN);
    display[0] = Display( 0.0,3.5f,1,COLOR_GREEN);

    coin[0] = Coin(6.0f*cscl_x,3.0*cscl_y,10,COLOR_GOLD);
    coin[1] = Coin(5.0f*cscl_x,2.0*cscl_y,10,COLOR_GOLD);
    coin[2] = Coin(7.0f*cscl_x,2.0*cscl_y,10,COLOR_GOLD);
    magnet = Magnet(-2,0,1,COLOR_FIRE_BALLS);
    
    coin[3] = Coin(4.0f*cscl_x,1.0*cscl_y,10,COLOR_GOLD);
    coin[4] = Coin(6.0f*cscl_x,1.0*cscl_y,10,COLOR_GOLD);
    coin[5] = Coin(8.0f*cscl_x,1.0*cscl_y,10,COLOR_GOLD); // First Triangle

    bitc[0] = Bitcoin(15.0f*cscl_x, 0.0f*cscl_y, COLOR_BITCOIN_GOLD);

    coin[6] = Coin(21.0f*cscl_x,3.0*cscl_y,10,COLOR_GOLD);
    coin[7] = Coin(20.0f*cscl_x,2.0*cscl_y,10,COLOR_GOLD);
    coin[8] = Coin(22.0f*cscl_x,2.0*cscl_y,10,COLOR_GOLD);
    coin[9] = Coin(19.0f*cscl_x,1.0*cscl_y,10,COLOR_GOLD);
    coin[10] = Coin(23.0f*cscl_x,1.0*cscl_y,10,COLOR_GOLD);

    fireyellow[0] = Fireyellow(27*cscl_x,0.0*cscl_y,1, COLOR_FIRE);
    firegrey[0] = Firegrey(27*cscl_x,0.0*cscl_y,1,COLOR_FIRE_BALLS);

    coin[11] = Coin(30.0f*cscl_x, 3.0*cscl_y,20,COLOR_GREEN);
    coin[12] = Coin(31.0f*cscl_x, 3.0*cscl_y,20,COLOR_GREEN);
    coin[13] = Coin(32.0f*cscl_x, 3.0*cscl_y,20,COLOR_GREEN);
    coin[14] = Coin(30.0f*cscl_x, 2.0*cscl_y,20,COLOR_GREEN);
    coin[15] = Coin(31.0f*cscl_x, 2.0*cscl_y,20,COLOR_GREEN);
    coin[16] = Coin(32.0f*cscl_x, 2.0*cscl_y,20,COLOR_GREEN);
    coin[17] = Coin(30.0f*cscl_x, 1.0*cscl_y,20,COLOR_GREEN);
    coin[18] = Coin(31.0f*cscl_x, 1.0*cscl_y,20,COLOR_GREEN);
    coin[19] = Coin(32.0f*cscl_x, 1.0*cscl_y,20,COLOR_GREEN); // Square distribution of coins
    
    firebeam[0] = Firebeam(40.0f*cscl_x,-1*cscl_y,1,COLOR_FIRE);
    firebeamgrey[0] = Firebeamgrey(40.0f*cscl_x,-1*cscl_y,1,COLOR_FIRE_BALLS);

    coin[20] = Coin(44.0f*cscl_x, 2.0*cscl_y,10,COLOR_GOLD);
    coin[21] = Coin(45.0f*cscl_x, 3.0*cscl_y,10,COLOR_GOLD);
    coin[22] = Coin(46.0f*cscl_x, 3.0*cscl_y,10,COLOR_GOLD);
    coin[23] = Coin(47.0f*cscl_x, 3.0*cscl_y,10,COLOR_GOLD);
    coin[24] = Coin(45.0f*cscl_x, 2.0*cscl_y,10,COLOR_GOLD);
    coin[25] = Coin(46.0f*cscl_x, 2.0*cscl_y,10,COLOR_GOLD);
    coin[26] = Coin(47.0f*cscl_x, 2.0*cscl_y,10,COLOR_GOLD);
    coin[27] = Coin(45.0f*cscl_x, 1.0*cscl_y,10,COLOR_GOLD);
    coin[28] = Coin(46.0f*cscl_x, 1.0*cscl_y,10,COLOR_GOLD);
    coin[29] = Coin(47.0f*cscl_x, 1.0*cscl_y,10,COLOR_GOLD);
    coin[30] = Coin(48.0f*cscl_x, 2.0*cscl_y,10,COLOR_GOLD); // hexagon distribution of coins
    
    life1 = Life1(53.0f*cscl_x,-1.0f*cscl_y,1,COLOR_FIRE);
    magnet = Magnet(53.5f*cscl_x,-2.0f,1,COLOR_RED);
    bitc[1] = Bitcoin(59.0f*cscl_x, 0.0f*cscl_y, COLOR_BITCOIN_GOLD);
    firebeam[1] = Firebeam(69.0f*cscl_x,-1*cscl_y,1,COLOR_FIRE);
    firebeamgrey[1] = Firebeamgrey(69.0f*cscl_x,-1*cscl_y,1,COLOR_FIRE_BALLS);
    shield[0] = Shield(74.0f*cscl_x,-2.0f*cscl_y,1,COLOR_FIRE);
    boomerang[0] = Boomerang(79.0f*cscl_x,-0.5*cscl_y,1,COLOR_FIRE_BALLS);
    coin[31] = Coin(84.0f*cscl_x, -1.0*cscl_y,10,COLOR_GOLD);
    coin[32] = Coin(86.0f*cscl_x, 1.0*cscl_y,10,COLOR_GOLD);
    coin[33] = Coin(88.0f*cscl_x, 2.0*cscl_y,10,COLOR_GOLD);
    
    ring = Ring(92.0f*cscl_x,0.0f*cscl_y,1,COLOR_FIRE);
    fireyellow[1] = Fireyellow(92*cscl_x,-1.0*cscl_y,1, COLOR_FIRE);
    firegrey[1] = Firegrey(92*cscl_x,-1.0*cscl_y,1,COLOR_FIRE_BALLS);
    coin[34] = Coin(104.0f*cscl_x, 1.0*cscl_y,10,COLOR_GOLD);
    coin[35] = Coin(106.0f*cscl_x, 1.0*cscl_y,10,COLOR_GOLD);
    fireyellow[2] = Fireyellow(100*cscl_x,0.0*cscl_y,1, COLOR_FIRE);
    firegrey[2] = Firegrey(100*cscl_x,0.0*cscl_y,1,COLOR_FIRE_BALLS);
    firebeam[2] = Firebeam(105.0f*cscl_x,-2*cscl_y,1,COLOR_FIRE);
    firebeamgrey[2] = Firebeamgrey(105.0f*cscl_x,-2*cscl_y,1,COLOR_FIRE_BALLS);
    fireyellow[3] = Fireyellow(110*cscl_x,0.0*cscl_y,1, COLOR_FIRE);
    firegrey[3] = Firegrey(110*cscl_x,0.0*cscl_y,1,COLOR_FIRE_BALLS);

    coin[36] = Coin(114.0f*cscl_x, 2.0*cscl_y,10,COLOR_GOLD);
    coin[37] = Coin(115.0f*cscl_x, 3.0*cscl_y,10,COLOR_GOLD);
    coin[38] = Coin(116.0f*cscl_x, 3.0*cscl_y,10,COLOR_GOLD);
    coin[39] = Coin(117.0f*cscl_x, 3.0*cscl_y,10,COLOR_GOLD);
    coin[40] = Coin(115.0f*cscl_x, 2.0*cscl_y,10,COLOR_GOLD);
    coin[41] = Coin(116.0f*cscl_x, 2.0*cscl_y,10,COLOR_GOLD);
    coin[42] = Coin(117.0f*cscl_x, 2.0*cscl_y,10,COLOR_GOLD);
    coin[43] = Coin(115.0f*cscl_x, 1.0*cscl_y,10,COLOR_GOLD);
    coin[44] = Coin(116.0f*cscl_x, 1.0*cscl_y,10,COLOR_GOLD);
    coin[45] = Coin(117.0f*cscl_x, 1.0*cscl_y,10,COLOR_GOLD);
    coin[46] = Coin(118.0f*cscl_x, 2.0*cscl_y,10,COLOR_GOLD); // hexagon distribution of coins

    shield[1] = Shield(121.0f*cscl_x,-2.0f*cscl_y,1,COLOR_FIRE);
    fireyellow[4] = Fireyellow(125*cscl_x,-1.0*cscl_y,1, COLOR_FIRE);
    firegrey[4] = Firegrey(125*cscl_x,-1.0*cscl_y,1,COLOR_FIRE_BALLS);
    fireyellow[5] = Fireyellow(130*cscl_x,1.0*cscl_y,1, COLOR_FIRE);
    firegrey[5] = Firegrey(130*cscl_x,1.0*cscl_y,1,COLOR_FIRE_BALLS);
    fireyellow[6] = Fireyellow(135*cscl_x,-1.0*cscl_y,1, COLOR_FIRE);
    firegrey[6] = Firegrey(135*cscl_x,-1.0*cscl_y,1,COLOR_FIRE_BALLS);

    coin[57] = Coin(140.0f*cscl_x, 3.0*cscl_y,20,COLOR_GREEN);
    coin[58] = Coin(141.0f*cscl_x, 3.0*cscl_y,20,COLOR_GREEN);
    coin[59] = Coin(142.0f*cscl_x, 3.0*cscl_y,20,COLOR_GREEN);
    coin[60] = Coin(142.0f*cscl_x, 1.0*cscl_y,20,COLOR_GREEN); // Square distribution of coins
    coin[61] = Coin(140.0f*cscl_x, 2.0*cscl_y,20,COLOR_GREEN);
    coin[62] = Coin(141.0f*cscl_x, 2.0*cscl_y,20,COLOR_GREEN);
    coin[63] = Coin(142.0f*cscl_x, 2.0*cscl_y,20,COLOR_GREEN);
    coin[64] = Coin(140.0f*cscl_x, 1.0*cscl_y,20,COLOR_GREEN);
    coin[65] = Coin(141.0f*cscl_x, 1.0*cscl_y,20,COLOR_GREEN);
    boomerang[1] = Boomerang(145.0f*cscl_x,-0.5*cscl_y,1,COLOR_FIRE_BALLS);    
    speedup = SpeedUp(150.0f*cscl_x,-1.0f*cscl_y,1,COLOR_FIRE);
    fireyellow[7] = Fireyellow(180*cscl_x,-1.0*cscl_y,1, COLOR_FIRE);
    firegrey[7] = Firegrey(180*cscl_x,-1.0*cscl_y,1,COLOR_FIRE_BALLS);

    fireyellow[14] = Fireyellow(190*cscl_x,1.0*cscl_y,1, COLOR_FIRE);
    firegrey[14] = Firegrey(190*cscl_x,1.0*cscl_y,1,COLOR_FIRE_BALLS);

    fireyellow[8] = Fireyellow(210*cscl_x,-1.0*cscl_y,1, COLOR_FIRE);
    firegrey[8] = Firegrey(210*cscl_x,-1.0*cscl_y,1,COLOR_FIRE_BALLS);

    fireyellow[9] = Fireyellow(240*cscl_x,1.0*cscl_y,1, COLOR_FIRE);
    firegrey[9] = Firegrey(240*cscl_x,1.0*cscl_y,1,COLOR_FIRE_BALLS);

    fireyellow[10] = Fireyellow(280*cscl_x,-1.0*cscl_y,1, COLOR_FIRE);
    firegrey[10] = Firegrey(280*cscl_x,-1.0*cscl_y,1,COLOR_FIRE_BALLS);

    fireyellow[11] = Fireyellow(310*cscl_x,1.0*cscl_y,1, COLOR_FIRE);
    firegrey[11] = Firegrey(310*cscl_x,1.0*cscl_y,1,COLOR_FIRE_BALLS);

    fireyellow[12] = Fireyellow(320*cscl_x,-1.0*cscl_y,1, COLOR_FIRE);
    firegrey[12] = Firegrey(320*cscl_x,-1.0*cscl_y,1,COLOR_FIRE_BALLS);

    fireyellow[13] = Fireyellow(330*cscl_x,1.0*cscl_y,1, COLOR_FIRE);
    firegrey[13] = Firegrey(330*cscl_x,1.0*cscl_y,1,COLOR_FIRE_BALLS);
    
    //boomerang = Boomerang(80.0f*cscl_x,-0.5*cscl_y,1,COLOR_FIRE_BALLS);
    //ring = Ring(90.0f*cscl_x,0.0f*cscl_y,1,COLOR_FIRE);

    //shield = Shield(0.0f*cscl_x,-2.0f*cscl_y,1,COLOR_FIRE);
    //shield = Shield(55.0f*cscl_x,-2.0f*cscl_y,1,COLOR_FIRE);
    //bitc[2] = Bitcoin(72.0f*cscl_x, 0.0f*cscl_y, COLOR_BITCOIN_GOLD);
    //bitc[3] = Bitcoin(78.0f*cscl_x, 0.0f*cscl_y, COLOR_BITCOIN_GOLD);
    //bitc[4] = Bitcoin(83.0f*cscl_x, 0.0f*cscl_y, COLOR_BITCOIN_GOLD);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0 , COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
