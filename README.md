# Graphics Assignments
 >This Repo consists of all the assignments I did as part of graphics Assignment
 >There are certain Libraries common for all the Assignment they are -
 ```sh
 sudo apt-get update
sudo apt-get install build-essential 
sudo apt-get install pkg-config
sudo apt-get install libglfw3 libglfw3-dev
sudo apt-get install libglew-dev
 ```

- Please make sure the above commands are executed before you try to run the any of the assignments.
 
 # Graphics Assingment 1
 - The Assignment was to make a 2d Game just like Jet-Pack Joyride.
 - Basic Controls:
1) Zoom in\out with the mouse wheel.
2) The player can move left with the left key, right with right key and
propulsion with space.
3) Throw water balloons with down key.
- Implemented in the game:
1) Wall, Platform.
2) Coins of different colors.
3) Magnet.
4) Special flying object.
5) Ring.
6) Fire Lines.
7) Fire Beams.
8) Boomerangs.
9) Viserion (Dragon from GOT).
10) Water Balloons
11) Collision detection.
12) Zooming in and out
13) Special Shield for player.
14) Score Display (7 Segment).
- How to run the assignment - 
```sh
cd Assignment1/build
cmake .. && make all
./graphics_asgn1
```
 - These are some of the screenshots <br>
 ![Alt text](Assignment1/ScreenShots/screen_rec.gif?raw=true "Game Start")
 
# Graphics Assignment 2
- Basic Controls -
1. increase speed in front direction -> W
2. decrease the speed in front direction - > S
3. turn right -> D
4. turn left -> A
5.  rotate clockwise -> E
6. rotate anti-clockwise -> Q
7. Go up -> Space
8. Go down -> B
9. start manuever -> M
10. end manuever -> N 
11.  Change camera View -> C
- Implemented -
12. Plane , Basic Controls, Sea, Score Board with 7 Segment Display
13. Obstackle course, check points, enemy cannons,
14. Smoke Rings, Fuel ups, Volcano NO FLYING ZONE, Emnemy parachute
15. All the Views
i. Plane View
ii. Top View
iii. Tower View
iv. Follow_cam view
v. Helicopter view
16. Manoevers, Compass
17. a directional Arrow that guides the airplane towards the new checkpoint

- How to run the game :-
```sh
cd Assignment2/build
cmake .. && make all
./grapics_asgn1
```


 - These are some of the screenshots <br>
 ![Alt text](Assignment2/ScreenShots/screen_rec.gif?raw=true "Game Start")



# Graphics Assignment 3
- Name of the game is InfiSkyRunnner
>- This has the following things implemented
    - Basic world which consists of 
       - Track
        - Walls
        - Player
        - Police
        - Police Dog
        - Coins
        - Trees (Type 1 Obstacle)
        - Slower (Type 2 Obstacle)
        - Jumpy Jumpy (Boots)
        - Boosted Board
        - shader tasks
    - Controls
        - Jump - space or Up arrow
        - left - left key
        - right - right key
        - grayscale - G
        - flicker - F
>

# How to Run this code 
- Make sure that you have firefox (an Open Source Browser) 
```sh
    firefox --version
```
- if the output is like 
```sh
    Mozilla Firefox 60.0.1
```
- else Install Firefox
```sh
    sudo apt-get install firefox
```
- go to the directory and then run the index.html file in browser
```sh
    firefox index.html
```

- Or you can just double click the index.html and if default it will open in any of the browser.
- Some Sample Gameplay Displaying all the features<br>
 ![Alt text](Assignment3/ScreenShots/screen_rec.gif?raw=true "Game Play")
