#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"
#include "timer.h"
#include "ball.h"


#include "airplane.h"
#include "sea.h"
#include "volcano.h"
#include "display.h"
#include "arrow.h"
#include "direction.h"
#include "cannon_chkpoint.h"
#include "cannon_ball.h"
#include "ring.h"
#include "fuelup.h"
#include "bomb.h"
#include "missile.h"
#include "para.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
int width  = 1600;
int height = 900;

// colors DEFINED AS PER CHOICE
extern const color_t COLOR_GOLD = { 212,175,55 };
extern const color_t COLOR_FIRE = { 230, 167, 31};
extern const color_t COLOR_FIRE_BALLS = {132, 132, 130};
extern const color_t COLOR_BITCOIN_GOLD = {255,215,0};
extern const color_t COLOR_L3_GREY = {79,91,102};
extern const color_t COLOR_L1_GREY = {52,61,70};
extern const color_t COLOR_GREENYELLOW = {173,255,47};
extern const color_t COLOR_BLUE = {0,119,190};


/**************************
* Customizable functions *
**************************/

Ball ball;
Airplane airplane;
Sea sea;
Volcano volcano[3];
Display display;
Arrow arrow;
Direction direction;
CheckPoint checkpoint[10];
Ring ring[10];
FuelUp fuelup[10];
Bomb bomb;
Para para[50];
Missile missile;


int follow_view = 1;
int top_view = 0, plane_view = 0, tower_view = 0, helicopter_view = 0 ;
int temp_for_helicopter_view = 1;
int score = 0;
float altitude = 10;
float fuel = 100;
float health = 100;
float speed = 0;
int life = 1;
int c_changed = 0;
float radius_helicopter_view = width / 2;
double xoffset, yoffset;

float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;

float follow_x,follow_y, follow_z;
float camera_x ,camera_z, camera_y;
int up_x = 0, up_y = 1, up_z = 0;
float plane_x, plane_y, plane_z;
float xoffset_global, yoffset_global;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0.0f;

Timer t60(1.0 / 60);

void scroll_callback_helicopter(GLFWwindow* window, double xoffset, double yoffset){
			xoffset_global = xoffset;
			yoffset_global += yoffset;
		}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    
    // Eye - Location of camera. Don't change unless you are sure!!
    // follow view
    plane_x = airplane.position.x;
    plane_y = airplane.position.y;
    plane_z = airplane.position.z;
    if(follow_view){
        camera_rotation_angle = -airplane.rotation_y + 90;
        camera_x = 5*cos(camera_rotation_angle*M_PI/180.0f);
        camera_y = 0;
        camera_z = 5*sin(camera_rotation_angle*M_PI/180.0f);
        follow_x = airplane.position.x + camera_x;
        follow_y = airplane.position.y + camera_y+2;
        follow_z = airplane.position.z + camera_z;
        up_z = 0;   up_y = 1;   up_x = 0;
    }
    else if(top_view){
    	camera_rotation_angle = -airplane.rotation_y + 90;
        camera_x = 5*cos(camera_rotation_angle*M_PI/180.0f);
        camera_y = 0;
        camera_z = 5*sin(camera_rotation_angle*M_PI/180.0f);
        follow_x = airplane.position.x + camera_x/100;
        follow_y = airplane.position.y+15;
        follow_z = airplane.position.z + camera_z/100;
        up_z = -1;    up_y = 0;   up_x = 0;
    }
    else if(plane_view){
    	camera_rotation_angle = -airplane.rotation_y + 90;
        camera_x = 5*cos(camera_rotation_angle*M_PI/180.0f);
        camera_y = 0;
        camera_z = 5*sin(camera_rotation_angle*M_PI/180.0f);
    	follow_x = airplane.position.x ;
        follow_y = airplane.position.y - 1;
        follow_z = airplane.position.z;
        plane_y = plane_y - 3;
        plane_x = plane_x - camera_x;
        plane_z = plane_z - camera_z;
        up_z = 0;     up_y = 1;     up_x = 0;
    }
    else if (tower_view){
    	follow_x = airplane.position.x + camera_x*2 + 0;
        follow_y = airplane.position.y/* + camera_y*/ + 10;
        follow_z = airplane.position.z + camera_z + 0;
        plane_x = airplane.position.x;
    	plane_y = airplane.position.y;
    	plane_z = airplane.position.z;
        up_z = 0;     up_y = 1;     up_x = 0;
	}
	else if (helicopter_view){
		double xpos = width / 2, ypos = height / 2;
		glfwSetScrollCallback(window,scroll_callback_helicopter);
		
		if(temp_for_helicopter_view==1){
			glfwSetCursorPos(window, xpos, ypos);
			temp_for_helicopter_view = 0;
		}
		glfwGetCursorPos(window, &xpos, &ypos);

		float x_t = (xpos - width/2);
		float y_t = -(ypos - height/2);
		follow_x = airplane.position.x + ((x_t)*2*5/width);
		follow_z = airplane.position.z + (5 - abs(x_t)*2*5/width);
		follow_y = airplane.position.y + 3 + (y_t)*2*5/height;
		if(follow_z - yoffset_global/10 > 0){
			follow_z -= (yoffset_global/10)*cos(airplane.rotation_y*3.14/180);
			follow_x += (yoffset_global/10)*sin(airplane.rotation_y*3.14/180);
		}
        plane_y = airplane.position.y;
        plane_x = airplane.position.x;
        plane_z = airplane.position.z;
        up_z = 0;     up_y = 1;     up_x = 0;
	}
	

    glm::vec3 eye ( follow_x, follow_y, follow_z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (plane_x, plane_y, plane_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (up_x, up_y, up_z);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    //Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * Matrices.view * Model;

    // Scene render
    //ball.draw(VP);
    airplane.draw(VP);
    sea.draw(VP);
    display.draw(VP,score,(int)altitude, int(abs(airplane.speed * 100)));
    arrow.draw(VP);
    direction.draw(VP);
    for(int i =0 ;i<3;i++){  volcano[i].draw(VP);	}
    for(int i=0;i<10;i++){	if(checkpoint[i].appear)  checkpoint[i].draw(VP);	}
    for(int i=0;i<10;i++){ 	if(ring[i].appear)  ring[i].draw(VP);	}
	for(int i=0;i<10;i++){	if(fuelup[i].appear)  fuelup[i].draw(VP);	}
    if(bomb.appear)	bomb.draw(VP);
	for(int i=0;i<50;i++){	if(para[i].appear) para[i].draw(VP);	}
    if(missile.appear)	missile.draw(VP);
}


void tick_input(GLFWwindow *window) {
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int w_pressed = glfwGetKey(window, GLFW_KEY_W);
    int s_pressed = glfwGetKey(window, GLFW_KEY_S);
    int a_pressed = glfwGetKey(window, GLFW_KEY_A);
    int d_pressed = glfwGetKey(window, GLFW_KEY_D);
    int q_pressed = glfwGetKey(window, GLFW_KEY_Q);
    int e_pressed = glfwGetKey(window, GLFW_KEY_E);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int b_pressed = glfwGetKey(window, GLFW_KEY_B);
    int c_pressed = glfwGetKey(window, GLFW_KEY_C);
    int m_pressed = glfwGetKey(window, GLFW_KEY_M);
    int n_pressed = glfwGetKey(window, GLFW_KEY_N);
    int left_clicked = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
    int right_clicked = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2);
    float acceleration = 0.01;
    float speed = 0.1f;
    
    if(a_pressed){ airplane.rotation_y += 1; }
    else if(d_pressed){ airplane.rotation_y -= 1; }
    else {  /*airplane.angular_speed = 0.0f;*/}

    if(space){ airplane.speed_y = speed; altitude += speed; }
    else if(b_pressed) { airplane.speed_y = -speed; altitude -= speed; }
    else{ airplane.speed_y = 0.0f; }

    if(w_pressed){ airplane.speed += -acceleration;}
    else if(s_pressed){ airplane.speed += acceleration/2;}
    else { if(airplane.speed<0) airplane.speed += 0.005f; }

    if(q_pressed){ airplane.rotation_x += 1; }
    else if(e_pressed){ airplane.rotation_x -= 1; }
    else{ /*airplane.angular_speed = 0;*/}

    if(right_clicked) { bomb.drop_bomb(airplane.position.x, airplane.position.y, airplane.position.z);}
    if(left_clicked) { missile.drop_missile(airplane.position.x, airplane.position.y, airplane.position.z, airplane.rotation_y);}

    if(m_pressed) { airplane.manoevers = 1;}
    else if(n_pressed) { airplane.manoevers = 0;}

    if(c_pressed && c_changed > 30){ if(follow_view== 1) {top_view = 1; follow_view = 0;}
    	else if(top_view==1) { plane_view = 1; top_view = 0; }
    	else if(plane_view==1) { tower_view = 1; plane_view = 0; }
    	else if(tower_view==1) {tower_view = 0; helicopter_view = 1; temp_for_helicopter_view = 1;}
    	else if(helicopter_view==1) {helicopter_view = 0; follow_view = 1;}
    	c_changed = 0;
    }
}

void tick_elements() {
		if(fuel > 0) fuel-=0.05;
		if(fuel < 0.1 ){
			cout << "\n\n Fuel is Over ::::::\n\n Your Score : " << score <<  "\n\n\n";
			quit(window);
		}
		else if(health < 1 ){
			cout << "\n\n health is Over ::::::\n\n Your Score : " << score <<  "\n\n\n";
			quit(window);
		}
		else if(airplane.position.y < 0.1){
			cout << "\n\n crashed in water ::::::\n\n Your Score : " << score <<  "\n\n\n";
			quit(window);
		}
    	airplane.tick();
    	sea.tick(airplane.position.x, airplane.position.z);
    	display.tick(airplane.position.x, airplane.position.y, airplane.position.z, airplane.rotation_y, altitude, fuel, airplane.health);
    	for(int i=0;i<3;i++){ volcano[i].tick();	}
    	arrow.tick();
    	direction.tick(airplane.position.x, airplane.position.y, airplane.position.z);
    	c_changed++; if(c_changed > 10000) c_changed = 100;
    	for(int i=0; i< 10; i++){
    		if(checkpoint[i].active){
		    	checkpoint[i].tick(airplane.position.x, airplane.position.y, airplane.position.z);
		    }
		}
    	for(int i=0;i<10;i++){ 	ring[i].tick();	}
    	for(int i=0;i<10;i++){ 	fuelup[i].tick();	}
    	bomb.tick();
    	for(int i=0;i<50;i++){	para[i].tick();	}
    	missile.tick();
    	for(int i=0; i< 10; i++){
    		if(checkpoint[i].active){
    			if(checkpoint[i].appear && detect_collision( airplane.bounding_box(), checkpoint[i].bounding_box_cannon())){
    				checkpoint[i].cannon_ball.reset();
    				if(airplane.health>= 20)
    				airplane.health -= 20;
    			}
    		}
    	}
    	for(int i=0;i<10;i++){
    		if(ring[i].appear && detect_collision( airplane.bounding_box(), ring[i].bounding_box())){
    			ring[i].appear = 0;
    			score += 20;
    		}
    	}
    	for(int i=0;i<10;i++){
    		if(fuelup[i].appear && detect_collision( airplane.bounding_box(), fuelup[i].bounding_box())){
    			fuelup[i].appear = 0;
    			score += 20;
    			fuel = 100;
    		}
    	}
    	for(int i=0; i<3;i++){
    		if(detect_collision(airplane.bounding_box(), volcano[i].bounding_box())){
    			score -= 10;
    			cout << "\n\n Got into a volcano Area DANger	 ::::::\n\n Your Score : " << score <<  "\n\n\n";
    			quit(window);
    		}
    	}
    	for(int i=0; i< 50; i++){
    		if(para[i].appear){
    			if(bomb.appear && para[i].appear && detect_collision(bomb.bounding_box(), para[i].bounding_box())){
    				para[i].appear = 0;
    				bomb.appear = 0;
    				score += 30;
    			}
    			if(missile.appear && para[i].appear && detect_collision(missile.bounding_box(), para[i].bounding_box())){
    				para[i].appear = 0;
    				missile.appear = 0;
    				score += 30;
    			}
    		}
    	}

    	for(int i=0; i< 10; i++){
    		if(checkpoint[i].active){
    			if(bomb.appear && checkpoint[i].appear && detect_collision(bomb.bounding_box(), checkpoint[i].bounding_box())){
    				checkpoint[i].appear = 0;
    				bomb.appear = 0;
    				checkpoint[i].active = 0;
    				if(i==9){
    					cout << "\n\n Completed Game CheckPoints ::::::\n\n Your Score : " << score <<  "\n\n\n";
    					quit(window);
    				}
    				checkpoint[i+1].active = 1;
    				arrow.set_position(checkpoint[i+1].position.x, checkpoint[i+1].position.z);
    				direction.set_dir(checkpoint[i+1].position.x, checkpoint[i+1].position.z);
    				score += 50;
    			}
    			if(missile.appear && checkpoint[i].appear && detect_collision(missile.bounding_box(), checkpoint[i].bounding_box())){
    				checkpoint[i].appear = 0;
    				missile.appear = 0;
    				checkpoint[i].active = 0;
    				if(i==9){
    					cout << "\n\n Completed Game CheckPoints ::::::\n\n Your Score : " << score <<  "\n\n\n";
    					quit(window);
    				}
    				checkpoint[i+1].active = 1;
    				arrow.set_position(checkpoint[i+1].position.x, checkpoint[i+1].position.z);
    				direction.set_dir(checkpoint[i+1].position.x, checkpoint[i+1].position.z);
    				score += 50;
    			}
    		}
    	}
    }

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball = Ball(-3, 0, COLOR_RED);
    airplane = Airplane(1,3,COLOR_L1_GREY);
    sea = Sea(0,0,COLOR_BLUE);
    display = Display(0,0,COLOR_BLACK);
    //for(int i=0;i<10;i++)	checkpoint[i] = CheckPoint(15*i+5,-12*i,COLOR_GREENYELLOW);
    int ch = 0;
    float scl_x = 7;
    float scl_z = 7;
    checkpoint[ch++] = CheckPoint( 15*scl_x, -12*scl_z, COLOR_GREENYELLOW);
    checkpoint[ch++] = CheckPoint( 25*scl_x, -22*scl_z, COLOR_GREENYELLOW);
    checkpoint[ch++] = CheckPoint( -2*scl_x, -32*scl_z, COLOR_GREENYELLOW);
    checkpoint[ch++] = CheckPoint(-13*scl_x, -22*scl_z, COLOR_GREENYELLOW);
    checkpoint[ch++] = CheckPoint(-43*scl_x,  -8*scl_z, COLOR_GREENYELLOW);
    checkpoint[ch++] = CheckPoint(-48*scl_x, -12*scl_z, COLOR_GREENYELLOW);
    checkpoint[ch++] = CheckPoint( 23*scl_x,   8*scl_z, COLOR_GREENYELLOW);
    checkpoint[ch++] = CheckPoint(  8*scl_x, -14*scl_z, COLOR_GREENYELLOW);
    checkpoint[ch++] = CheckPoint( 18*scl_x, -44*scl_z, COLOR_GREENYELLOW);
    checkpoint[ch++] = CheckPoint( 48*scl_x, -44*scl_z, COLOR_GREENYELLOW);
    checkpoint[ch++] = CheckPoint( 58*scl_x, -42*scl_z, COLOR_GREENYELLOW);
    checkpoint[0].active = 1;
    arrow = Arrow(checkpoint[0].position.x,checkpoint[0].position.z,COLOR_RED);
    direction = Direction(checkpoint[0].position.x,checkpoint[0].position.z,COLOR_GOLD);
    direction.set_dir(checkpoint[0].position.x, checkpoint[0].position.z);
    //for(int i=0;i<10;i++){	ring[i] = Ring(-10*i, -5*i , COLOR_GREENYELLOW);  }
    ch = 0;
    ring[ch++] = Ring( -5*scl_x,  -5*scl_z, COLOR_GREENYELLOW);
    ring[ch++] = Ring(-25*scl_x,  -7*scl_z, COLOR_GREENYELLOW);
    ring[ch++] = Ring(-15*scl_x, -18*scl_z, COLOR_GREENYELLOW);
    ring[ch++] = Ring(-25*scl_x, -48*scl_z, COLOR_GREENYELLOW);
    ring[ch++] = Ring( -3*scl_x, -28*scl_z, COLOR_GREENYELLOW);
    ring[ch++] = Ring( 13*scl_x, -18*scl_z, COLOR_GREENYELLOW);
    ring[ch++] = Ring( 23*scl_x, -48*scl_z, COLOR_GREENYELLOW);
    ring[ch++] = Ring( 43*scl_x, -48*scl_z, COLOR_GREENYELLOW);
    ring[ch++] = Ring( 52*scl_x, -36*scl_z, COLOR_GREENYELLOW);
    ring[ch++] = Ring(  5*scl_x, -36*scl_z, COLOR_GREENYELLOW);

    ch = 0;
    volcano[ch++] = Volcano(  0*scl_x, -12*scl_z, COLOR_GREENYELLOW);
    volcano[ch++] = Volcano(-25*scl_x, -20*scl_z, COLOR_GREENYELLOW);
    volcano[ch++] = Volcano( 25*scl_x, -20*scl_z, COLOR_GREENYELLOW);

    ch = 0;
    fuelup[ch++] = FuelUp(  21*scl_x, -22*scl_z, COLOR_GREENYELLOW);
    fuelup[ch++] = FuelUp(  18*scl_x, -49*scl_z, COLOR_GREENYELLOW);
    fuelup[ch++] = FuelUp( -19*scl_x, -28*scl_z, COLOR_GREENYELLOW);
    fuelup[ch++] = FuelUp( -15*scl_x, -24*scl_z, COLOR_GREENYELLOW);
    fuelup[ch++] = FuelUp( -48*scl_x,   0*scl_z, COLOR_GREENYELLOW);
    fuelup[ch++] = FuelUp( -39*scl_x,  -8*scl_z, COLOR_GREENYELLOW);
    fuelup[ch++] = FuelUp( -11*scl_x, -15*scl_z, COLOR_GREENYELLOW);
    fuelup[ch++] = FuelUp( -41*scl_x,  -2*scl_z, COLOR_GREENYELLOW);
    fuelup[ch++] = FuelUp( -25*scl_x, -48*scl_z, COLOR_GREENYELLOW);
    fuelup[ch++] = FuelUp( -52*scl_x, -48*scl_z, COLOR_GREENYELLOW);

    missile = Missile(airplane.position.x, airplane.position.y,airplane.position.z,COLOR_BLACK);
    bomb = Bomb(airplane.position.x, airplane.position.y,airplane.position.z,COLOR_BLACK);
    for(int i=0;i<50;i++) {	para[i] = Para((rand()%50-25)*scl_x , (rand()%100 + 20)*10  , -(rand()%50)*scl_z, COLOR_GREENYELLOW);	}
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniformpersperspers
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
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.length + b.length));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(1.1f,((float)width/height),-1.0f, 1.0f);
}
