
var Colors = {
	cherry: 0xe35d6a,
	blue: 0x1560bd,
	white: 0xd8d0d1,
	black: 0x000000,
	brown: 0x59332e,
	peach: 0xffdab9,
	yellow: 0xffff00,
	olive: 0x556b2f,
	grey: 0x696969,
	sand: 0xd3c280,
	brownDark: 0x23190f,
	green: 0x669900,
	red:0xff0000,

};

var deg2Rad = Math.PI / 180;
var shifting = 1200;
window.addEventListener('load', function(){
	new World();
});
var graying = false;

// This class has the main Game engine Start from Here.
function World() {
	var self = this;
	var element, scene, camera, character, police, renderer, light,
		treePresenceProb, maxTreeSize, fogDistance, gameOver,walls_right,walls_left,
		coin_objects,coin_cont,slower_obstacles, boosted_boards,bright,loper,
		objects, paused, keysAllowed, score, difficulty,grayscale, totaltim,
		timout, timforboard, timforjumpy, boarding, jumpy_bonus,dog,flicker;
	init();
	function init() {
		loper = 0;
		coin_cont = 0;
		timout = 100;
		timforjumpy = 0;
		timforboard = 0;
		boarding = false;
		grayscale = false;
		element = document.getElementById('world_gray');
		renderer = new THREE.WebGLRenderer({ alpha: true, antialias: true });
		//renderer = new THREE.WebGLRenderer();
		renderer.setPixelRatio(window.devicePixelRatio);
		renderer.setSize(element.clientWidth/1, element.clientHeight);
		renderer.shadowMap.enabled = true;
		element.appendChild(renderer.domElement);
		bright = false;
		flicker = false;
		totaltim = 0;
		scene = new THREE.Scene();
		fogDistance = 40000;
		scene.fog = new THREE.Fog(0xbadbe4, 1, fogDistance);
		camera = new THREE.PerspectiveCamera(100, element.clientWidth / element.clientHeight, 1, 100000);
		camera.position.set(0, 1500, -2000);
		camera.lookAt(new THREE.Vector3(0, 600, -5000));
		window.camera = camera;
		window.addEventListener('resize', handleWindowResize, false);
		light = new THREE.HemisphereLight(0xffffff, 0xffffff, 1);
		scene.add(light);
		character = new Character();
		scene.add(character.element);
		police = new Police();
		scene.add(police.element);
		dog = new Dog();
		scene.add(dog.element);
		var ground = loadGroundTexture(5000, 20, 120000, Colors.sand, 0, -400, -60000);//createBox(5000, 20, 120000, Colors.sand, 0, -400, -60000);
		scene.add(ground);
		var walls_right = loadWallTexture(20, 5000, 120000, Colors.sand, 3000, -400, -60000);
		scene.add(walls_right);
		var walls_left = loadWallTexture(20, 5000, 120000, Colors.sand, -3000, -400, -60000);
		scene.add(walls_left);
		objects = [];
		coin_objects = [];
		slower_obstacles = [];
		boosted_boards = [];
		jumpy_bonus = [];
		treePresenceProb = 0.2;
		maxTreeSize = 0.5;
		for (var i = 5; i < 40; i++) {
			createRowOfTrees(i * -3000, treePresenceProb, 0.5, maxTreeSize);
		}
		for (var i = 5; i < 40; i++) {
			createRowOfCoins(i * -3000, treePresenceProb,i);
		}
		for (var i = 5; i < 40 ; i++){
			createRowOftype1(i * -3000, treePresenceProb, i);
		}
		for (var i = 15 ; i < 20 ; i++){
			createRowOfbboards(i * -5000, treePresenceProb - 0.1);
		}
		for (var i = 5; i < 40 ; i++){
			createRowOfjmpy(i * -6000, treePresenceProb);
		}
		gameOver = false;
		paused = true;

		// Before Adding any key for Input Lookup the Encoding of that Key online
		var left = 37;
		var up = 38;
		var right = 39;
		var p = 80;
		var space = 32;
		var g = 71;
		var f = 70;
		
		keysAllowed = {};
		document.addEventListener(
			'keydown',
			function(e) {
				if (!gameOver) {
					var key = e.keyCode;
					if (keysAllowed[key] === false) return;
					keysAllowed[key] = false;
					if (paused && !collisionsDetected() && key > 18) {
						paused = false;
						character.onUnpause();
						dog.onUnpause();
						police.onUnpause();
						document.getElementById("variable-content").style.visibility = "hidden";
						//document.getElementById("controls").style.display = "none";
					} else {
						if (key == p) {
							paused = true;
							character.onPause();
							police.onPause();
							dog.onPause();
							document.getElementById("variable-content").style.visibility = "visible";
							document.getElementById("variable-content").innerHTML = "Game is paused, Refresh the page to Play again or press F5"; }
						if (key == up && !paused) {
							character.onUpKeyPressed();
							police.onUpKeyPressed();
						}
						if (key == space && !paused) {
							character.onUpKeyPressed();
							police.onUpKeyPressed();
						}
						if (key == left && !paused) {
							character.onLeftKeyPressed();
							police.onLeftKeyPressed();
							dog.onLeftKeyPressed();
						}
						if (key == right && !paused) {
							character.onRightKeyPressed();
							police.onRightKeyPressed();
							dog.onRightKeyPressed();

						}
						if(key == g){
							//console.log("G detected");
							changeGray();
						}
						if(key == f){
							console.log("F detected");
							if(flicker == true){
								flicker = false;
								bright = true;
								element = document.getElementById('world');
								element.appendChild(renderer.domElement);
							}
							else {
								flicker = true;
								bright = false;	
							}
						}
					}
				}
			}
		);
		document.addEventListener(
			'keyup',
			function(e) {
				keysAllowed[e.keyCode] = true;
			}
		);
		document.addEventListener(
			'focus',
			function(e) {
				keysAllowed = {};
			}
		);

		// Initialize the scores and difficulty.
		score = 0;
		difficulty = 0;
		document.getElementById("score").innerHTML = score;

		// Begin the rendering loop.
		loop();

	}

	// This is the infinite Loop wher every thing is running
	function loop() {
		totaltim += 1;

		if (!paused) {  // Update the Game if Not paused
			if(totaltim > 10000){
				gameOver = true;
				paused = true;
				console.log("game Over");
				var variableContent = document.getElementById("variable-content");
				variableContent.style.visibility = "visible";
				variableContent.innerHTML =  "Target Achieved";
			}
			police.dist_from_player += 5;
			// Add more trees and increase the difficulty.
			if ((objects[objects.length - 1].mesh.position.z) % 3000 == 0) {
				difficulty += 1;
				var levelLength = 30;
				if (difficulty % levelLength == 0) {
					var level = difficulty / levelLength;
					switch (level) {
						case 1:
							treePresenceProb = 0.35;
							maxTreeSize = 0.5;
							break;
						case 2:
							treePresenceProb = 0.35;
							maxTreeSize = 0.85;
							break;
						case 3:
							treePresenceProb = 0.5;
							maxTreeSize = 0.85;
							break;
						case 4:
							treePresenceProb = 0.5;
							maxTreeSize = 1.1;
							break;
						case 5:
							treePresenceProb = 0.5;
							maxTreeSize = 1.1;
							break;
						case 6:
							treePresenceProb = 0.55;
							maxTreeSize = 1.1;
							break;
						default:
							treePresenceProb = 0.55;
							maxTreeSize = 1.25;
					}
				}
				if ((difficulty >= 5 * levelLength && difficulty < 6 * levelLength)) {
					fogDistance -= (25000 / levelLength);
				} else if (difficulty >= 8 * levelLength && difficulty < 9 * levelLength) {
					fogDistance -= (5000 / levelLength);
				}
				createRowOfTrees(-120000, treePresenceProb, 0.5, maxTreeSize);
				createRowOfCoins(-120000, treePresenceProb);
				createRowOftype1(-120000, treePresenceProb);
				scene.fog.far = fogDistance;
			}

			// Move the trees closer to the character.
			objects.forEach(function(object) {
				object.mesh.position.z += 100;
			});
			coin_objects.forEach(function(object) {
				object.mesh.position.z += 100;
			});
			slower_obstacles.forEach(function(object) {
				object.mesh.position.z += 100;
			});
			boosted_boards.forEach(function(object){
				object.mesh.position.z += 100;
			});
			jumpy_bonus.forEach(function(object){
				object.mesh.position.z += 100;
			});

			
			// Remove trees that are outside of the world.
			objects = objects.filter(function(object) {
				return object.mesh.position.z < 0;
			});
			coin_objects = coin_objects.filter(function(object) {
				return object.mesh.position.z < 0;
			});
			slower_obstacles = slower_obstacles.filter(function(object){
				return object.mesh.position.z < 0;
			});
			boosted_boards = boosted_boards.filter(function(object){
				return object.mesh.position.z < 0;
			});
			jumpy_bonus = jumpy_bonus.filter(function(object){
				return object.mesh.position.z < 0;
			});

			// Make the character move according to the controls.
			character.update();
			police.update();
			dog.update();

			// Check for collisions between the character and objects.
			if (collisionsDetected()) {
				gameOver = true;
				paused = true;
				document.addEventListener(
        			'keydown',
        			function(e) {
        				if (e.keycode == 32)
            			document.location.reload(true);
        			}
    			);
    			var variableContent = document.getElementById("variable-content");
    			variableContent.style.visibility = "visible";
    			variableContent.innerHTML =  "Game Over!!!";  // Collision detection with Trees
			}
			for (var i = 0;i<coin_objects.length; i++){
				if(collisionsDetectedCoins(i)) {  // Collision detection with Coins
					score ++;
					coin_objects[i].moveOut();
					break;
				}
			}
			if(collisionsDetectedForSlow()){   // After collision with the slowers
				var variableContent = document.getElementById("variable-content");
    			variableContent.style.visibility = "visible";
				//variableContent.innerHTML =  "Hey Pal! look where you are running or you will be caught by the Police Men";
    			if(police.dist_from_player < 1000){ police.dist_from_player -= 120; }
    			else { police.dist_from_player = 800; }
    			if( police.dist_from_player < 500){
    				console.log("Game Over\n");
    				variableContent.innerHTML =  "Game Over !!!";
					paused = true;
					gameOver = true;
				}
			}
			for (var i = 0;i<boosted_boards.length; i++){
				if(collisionsDetectedboard(i)) {  // Collision detection with boosted board
					score ++;
					character.onBoard();
					timforboard = 1;
					break;

					
				}
			}
			for (var i = 0; i < jumpy_bonus.length ; i++){
				if(collisionsDetectedjumpy(i)) {  // Collision detection with jumpy jumpy
					//This is for Jumpy Jumpy
					jumpy_bonus[i].moveOut();
					character.jumpDuration = 1.0;
					character.jumpHeight = 2000;
					timforjumpy = 1;
					break;
				}
			}


			if(timforjumpy >= 1 ){
				timforjumpy += 1;
				if(timforjumpy > timout){
					timforjumpy = 0;
					character.jumpDuration = 0.6;
					character.jumpHeight = 1000;
				}
			}

			if(timforboard >= 1 ){
				timforboard += 1;
				if(timforboard > timout * 3){
					timforboard = 0;
					character.offBoard();
				}
			}
			document.getElementById("score").innerHTML = score; // Render the scores in HTML File

		}
		if(bright == false && loper > 10 && flicker){ loper = 0; element = document.getElementById('brightworld'); bright = true; }
		else if(loper > 10 && flicker){ loper = 0; element = document.getElementById('world'); bright = false; console.log("hey"); }
		element.appendChild(renderer.domElement);
		loper += 1;
		requestAnimationFrame(loop);
		renderer.render(scene, camera);
		
	}

	function changeGray() {
		if(grayscale == true){
			//element = document.getElementById('world');
			grayscale = false;
			graying = false;
			console.log("changing the color to gs");
			uniforms = {
				color: {type: 'vec3', value: new THREE.Color(character.torso.color)},
			};
			character.torso.mat = {
				uniform : uniforms,
				vertexShader: document.getElementById('vertexShader').textContent,
    		    fragmentShader: document.getElementById('fragmentShader_gray').textContent
			}
			character.torso.box = new THREE.Mesh(character.torso.geom, character.torso.mat);
		}
		else{ //element = document.getElementById('world1'); 
				grayscale = true; 
				graying = true; 
				//character.onGrayscale();
				//console.log("changing the gs to color");
			}
		//element.appendChild(renderer.domElement);
	}

	/**
	  * A method called when window is resized.
	  */
	function handleWindowResize() {
		renderer.setSize(element.clientWidth, element.clientHeight);
		camera.aspect = element.clientWidth / element.clientHeight;
		camera.updateProjectionMatrix();
	}

	function createRowOfTrees(position, probability, minScale, maxScale) {
		for (var lane = -1; lane < 2; lane++) {
			var randomNumber = Math.random();
			if (randomNumber < probability) {
				var scale = minScale + (maxScale - minScale) * Math.random();
				var tree = new Tree(lane * 1200, -400, position, scale);
				objects.push(tree);
				scene.add(tree.mesh);
			}
		}
	}
	function createRowOfCoins(position, probability,coin_cont) {
		for (var lane = -1; lane < 2; lane++) {
			var randomNumber = Math.random();
			if (randomNumber < probability) {
				var coin = new Coin(lane * 1200, -400, position, 0.5);
				coin_objects.push(coin);
    			//console.log("here");

				scene.add(coin.mesh);
			}
		}
	}
	function createRowOfbboards(position, probability) {
		for (var lane = -1; lane < 2; lane++) {
			var randomNumber = Math.random();
			if (randomNumber < probability) {
				var board = new BoostedBoard(lane * 1200, -400, position, 0.5);
				boosted_boards.push(board);
				scene.add(board.mesh);
			}
		}
	}
	function createRowOftype1(position, probability,coin_cont) {
		for (var lane = -1; lane < 2; lane++) {
			var randomNumber = Math.random();
			if (randomNumber < probability) {
				var slow_down = new SlowHim(lane * 1200, -400, position, 0.5);
				slower_obstacles.push(slow_down);
				//console.log("Added Slowers a");
				scene.add(slow_down.mesh);
			}
		}
	}
	function createRowOfjmpy(position, probability){
		for (var lane = -1; lane < 2; lane++) {
			var randomNumber = Math.random();
			if (randomNumber < probability) {
				var jumpy = new JumpyJumpy(lane * 1200, -400, position, 0.5);
				jumpy_bonus.push(jumpy);
				scene.add(jumpy.mesh);
			}
		}
	}

	/**
	 * Returns true if and only if the character is currently colliding with
	 * an object on the map.
	 */
 	function collisionsDetected() {
 		var charMinX = character.element.position.x - 115;
 		var charMaxX = character.element.position.x + 115;
 		var charMinY = character.element.position.y - 310;
 		var charMaxY = character.element.position.y + 320;
 		var charMinZ = character.element.position.z - 40;
 		var charMaxZ = character.element.position.z + 40;
 		for (var i = 0; i < objects.length; i++) {
 			if (objects[i].collides(charMinX, charMaxX, charMinY, charMaxY, charMinZ, charMaxZ)) {
 				return true;
 			}
 		}
 		return false;
 	}
	function collisionsDetectedCoins(i) {
 		var charMinX = character.element.position.x - 115;
 		var charMaxX = character.element.position.x + 115;
 		var charMinY = character.element.position.y - 310;
 		var charMaxY = character.element.position.y + 320;
 		var charMinZ = character.element.position.z - 40;
 		var charMaxZ = character.element.position.z + 40;
 		//for (var i = 0; i < coin_objects.length; i++) {
 			if (coin_objects[i].collides(charMinX, charMaxX, charMinY, charMaxY, charMinZ, charMaxZ)) {
 				return true;
 			}
 		//}
 		return false;
 	}
 	function collisionsDetectedForSlow(){
 		var charMinX = character.element.position.x - 115;
 		var charMaxX = character.element.position.x + 115;
 		var charMinY = character.element.position.y - 310;
 		var charMaxY = character.element.position.y + 320;
 		var charMinZ = character.element.position.z - 40;
 		var charMaxZ = character.element.position.z + 40;
 		for (var i = 0; i < slower_obstacles.length; i++) {
 			if (slower_obstacles[i].collides(charMinX, charMaxX, charMinY, charMaxY, charMinZ, charMaxZ)) {
 				return true;
 			}
 		}
 		return false;
 	}
 	function collisionsDetectedboard(i){
 		var charMinX = character.element.position.x - 115;
 		var charMaxX = character.element.position.x + 115;
 		var charMinY = character.element.position.y - 310;
 		var charMaxY = character.element.position.y + 320;
 		var charMinZ = character.element.position.z - 40;
 		var charMaxZ = character.element.position.z + 40;
 		//for (var i = 0; i < coin_objects.length; i++) {
 			if (boosted_boards[i].collides(charMinX, charMaxX, charMinY, charMaxY, charMinZ, charMaxZ)) {
 				return true;
 			}
 		//}
 		return false;
 	}
 	function collisionsDetectedjumpy(i){
 		var charMinX = character.element.position.x - 115;
 		var charMaxX = character.element.position.x + 115;
 		var charMinY = character.element.position.y - 310;
 		var charMaxY = character.element.position.y + 320;
 		var charMinZ = character.element.position.z - 40;
 		var charMaxZ = character.element.position.z + 40;
 		//for (var i = 0; i < coin_objects.length; i++) {
 			if (jumpy_bonus[i].collides(charMinX, charMaxX, charMinY, charMaxY, charMinZ, charMaxZ)) {
 				return true;
 			}
 		//}
 		return false;
 	}
}

function Character() {
	var self = this;
	this.skinColor = Colors.brown;
	this.hairColor = Colors.black;
	this.shirtColor = Colors.yellow;
	this.shortsColor = Colors.olive;
	this.jumpDuration = 0.6;
	this.jumpHeight = 1000;
	this.flying = false;
	init();
	function init() {
		self.face = createBox(100, 100, 60, self.skinColor, 0, 0, 0);
		self.hair = createBox(105, 20, 65, self.hairColor, 0, 50, 0);
		self.torso = createBox(150, 190, 40, self.shirtColor, 0, 100, 0);
		self.leftLowerArm = createLimb(20, 120, 30, self.skinColor, 0, -170, 0);
		self.leftArm = createLimb(30, 140, 40, self.skinColor, -100, 190, -10);
		self.rightLowerArm = createLimb(20, 120, 30, self.skinColor, 0, -170, 0);
		self.rightArm = createLimb(30, 140, 40, self.skinColor, 100, 190, -10);
		self.leftLowerLeg = createLimb(40, 200, 40, self.skinColor, 0, -200, 0);
		self.leftLeg = createLimb(50, 170, 50, self.shortsColor, -50, -10, 30);
		self.rightLowerLeg = createLimb(40, 200, 40, self.skinColor, 0, -200, 0);
		self.rightLeg = createLimb(50, 170, 50, self.shortsColor, 50, -10, 30);
		self.element = createGroup(0, 0, -4000);
		self.head = createGroup(0, 260, -25);
		self.head.add(self.face);
		self.head.add(self.hair);
		self.leftArm.add(self.leftLowerArm);
		self.rightArm.add(self.rightLowerArm);
		self.leftLeg.add(self.leftLowerLeg);
		self.rightLeg.add(self.rightLowerLeg);
		self.element.add(self.head);
		self.element.add(self.torso);
		self.element.add(self.leftArm);
		self.element.add(self.rightArm);
		self.element.add(self.leftLeg);
		self.element.add(self.rightLeg);

		self.isJumping = false;
		self.isSwitchingLeft = false;
		self.isSwitchingRight = false;
		self.currentLane = 0;
		self.runningStartTime = new Date() / 1000;
		self.pauseStartTime = new Date() / 1000;
		self.stepFreq = 4;
		self.queuedActions = [];

	}

	function createLimb(dx, dy, dz, color, x, y, z) {
	    var limb = createGroup(x, y, z);
	    var offset = -1 * (Math.max(dx, dz) / 2 + dy / 2);
		var limbBox = createBox(dx, dy, dz, color, 0, offset, 0);
		limb.add(limbBox);
		return limb;
	}
	function createLimb_gray(dx, dy, dz, color, x, y, z) {
	    var limb = createGroup(x, y, z);
	    var offset = -1 * (Math.max(dx, dz) / 2 + dy / 2);
		var limbBox = createBox_gray(dx, dy, dz, color, 0, offset, 0);
		limb.add(limbBox);
		return limb;
	}

	this.update = function() {
		var currentTime = new Date() / 1000;

		//if (!self.isJumping && !self.isSwitchingLeft && !self.isSwitchingRight && self.queuedActions.length > 0) {
		if(self.queuedActions.length > 0) {
			switch(self.queuedActions.shift()) {
				case "up":
					self.isJumping = true;
					self.jumpStartTime = new Date() / 1000;
					break;
				case "left":
					if (self.currentLane != -1) {
						self.isSwitchingLeft = true;
					}
					break;
				case "right":
					if (self.currentLane != 1) {
						self.isSwitchingRight = true;
					}
					break;
			}
		}
		if(self.flying)
			self.element.position.y =1000;
		else{
			if (self.isJumping) {
				var jumpClock = currentTime - self.jumpStartTime;
				self.element.position.y = self.jumpHeight * Math.sin((1 / self.jumpDuration) * Math.PI * jumpClock) + sinusoid(2 * self.stepFreq, 0, 20, 0, self.jumpStartTime - self.runningStartTime);
				if (jumpClock > self.jumpDuration) {
					self.isJumping = false;
					self.runningStartTime += self.jumpDuration;
				}
			} else {
				var runningClock = currentTime - self.runningStartTime;
				self.element.position.y = sinusoid( 2 * self.stepFreq, 0, 20, 0, runningClock);
				self.head.rotation.x = sinusoid( 2 * self.stepFreq, -10, -5, 0, runningClock) * deg2Rad;
				self.torso.rotation.x = sinusoid( 2 * self.stepFreq, -10, -5, 180, runningClock) * deg2Rad;
				self.leftArm.rotation.x = sinusoid( self.stepFreq, -70, 50, 180, runningClock) * deg2Rad;
				self.rightArm.rotation.x = sinusoid( self.stepFreq, -70, 50, 0, runningClock) * deg2Rad;
				self.leftLowerArm.rotation.x = sinusoid( self.stepFreq, 70, 140, 180, runningClock) * deg2Rad;
				self.rightLowerArm.rotation.x = sinusoid( self.stepFreq, 70, 140, 0, runningClock) * deg2Rad;
				self.leftLeg.rotation.x = sinusoid( self.stepFreq, -20, 80, 0, runningClock) * deg2Rad;
				self.rightLeg.rotation.x = sinusoid( self.stepFreq, -20, 80, 180, runningClock) * deg2Rad;
				self.leftLowerLeg.rotation.x = sinusoid( self.stepFreq, -130, 5, 240, runningClock) * deg2Rad;
				self.rightLowerLeg.rotation.x = sinusoid( self.stepFreq, -130, 5, 60, runningClock) * deg2Rad;
			}
		}
		if (self.isSwitchingLeft) {
			self.element.position.x -= 200;
			var offset = self.currentLane * shifting - self.element.position.x;
			if (offset > shifting) {
				self.currentLane -= 1;
				self.element.position.x = self.currentLane * shifting;
				self.isSwitchingLeft = false;
			}
		}
		if (self.isSwitchingRight) {
			self.element.position.x += 200;
			var offset = self.element.position.x - self.currentLane * shifting;
			if (offset > 800) {
				self.currentLane += 1;
				self.element.position.x = self.currentLane * shifting;
				self.isSwitchingRight = false;
			}
		}
	}
	this.onLeftKeyPressed = function() {
		self.queuedActions.push("left");
	}
	this.onUpKeyPressed = function() {
		self.queuedActions.push("up");
	}
	this.onRightKeyPressed = function() {
		self.queuedActions.push("right");
	}
	this.onPause = function() {
		self.pauseStartTime = new Date() / 1000;
	}
	this.onUnpause = function() {
		var currentTime = new Date() / 1000;
		var pauseDuration = currentTime - self.pauseStartTime;
		self.runningStartTime += pauseDuration;
		if (self.isJumping) {
			self.jumpStartTime += pauseDuration;
		}
	}
	this.onBoard = function() {
		this.flying = true;
	}
	this.offBoard = function() {
		this.flying = false;
	}
}

function Dog() {
	var self = this;
	this.skinColor = Colors.brown;
	this.hairColor = Colors.black;
	this.shirtColor = Colors.black;
	this.shortsColor = Colors.olive;
	this.jumpDuration = 0.6;
	this.jumpHeight = 1000;
	this.flying = false;
	this.scl_y = 1;
	init();
	function init() {
		self.face = createBox(100, 100 * self.scl_y, 60, self.skinColor, 0, 0, 0);
		self.hair = createBox(105, 20 * self.scl_y, 65, self.hairColor, 0, 25, 0);
		self.torso = createBox(100, 100 * self.scl_y, 300, self.shirtColor, 0, 50, 100);
		//self.leftLowerArm = createLimb(20, 120, 30, self.skinColor, 0, -170, 0);
		//self.leftArm = createLimb(30, 140, 40, self.skinColor, -100, 190, -10);
		//self.rightLowerArm = createLimb(20, 120, 30, self.skinColor, 0, -170, 0);
		//self.rightArm = createLimb(30, 140, 40, self.skinColor, 100, 190, -10);
		self.leftLowerLeg = createLimb(40, 200 * self.scl_y, 40, self.skinColor, 0, -100, 0 - 10);
		self.leftLowerLegBack = createLimb(40, 200 * self.scl_y, 40, self.skinColor, 0, -100, 0+ 10);
		self.leftLeg = createLimb(50, 170 * self.scl_y, 50, self.shortsColor, -50, -5, 30 - 10);
		self.leftLegBack = createLimb(50, 170 * self.scl_y, 50, self.shortsColor, -50, -5, 30+200);
		self.rightLowerLeg = createLimb(40, 200 * self.scl_y, 40, self.skinColor, 0, -100, 0 - 10);
		self.rightLowerLegBack = createLimb(40, 200 * self.scl_y, 40, self.skinColor, 0, -100, 0+ 10);
		self.rightLeg = createLimb(50, 170 * self.scl_y, 50, self.shortsColor, 50, -5, 30 - 10);
		self.rightLegBack = createLimb(50, 170 * self.scl_y, 50, self.shortsColor, 50, -5, 30+ 10);
		self.element = createGroup(0, 0, -4000 + 1000);
		self.head = createGroup(0, 200, -100);
		self.head.add(self.face);
		self.head.add(self.hair);
		//self.leftArm.add(self.leftLowerArm);
		//self.rightArm.add(self.rightLowerArm);
		self.leftLeg.add(self.leftLowerLeg);
		self.rightLeg.add(self.rightLowerLeg);
		self.leftLegBack.add(self.leftLowerLegBack);
		self.rightLegBack.add(self.rightLowerLegBack);
		self.element.add(self.head);
		self.element.add(self.torso);
		//self.element.add(self.leftArm);
		//self.element.add(self.rightArm);
		self.element.add(self.leftLeg);
		self.element.add(self.rightLeg);
		self.element.add(self.leftLegBack);
		self.element.add(self.rightLegBack);

		self.isJumping = false;
		self.isSwitchingLeft = false;
		self.isSwitchingRight = false;
		self.currentLane = 0;
		self.runningStartTime = new Date() / 1000;
		self.pauseStartTime = new Date() / 1000;
		self.stepFreq = 3;
		self.queuedActions = [];

	}

	function createLimb(dx, dy, dz, color, x, y, z) {
	    var limb = createGroup(x, y, z);
	    var offset = -1 * (Math.max(dx, dz) / 2 + dy / 2);
		var limbBox = createBox(dx, dy, dz, color, 0, offset, 0);
		limb.add(limbBox);
		return limb;
	}

	this.update = function() {
		var currentTime = new Date() / 1000;

		//if (!self.isJumping && !self.isSwitchingLeft && !self.isSwitchingRight && self.queuedActions.length > 0) {
		if(self.queuedActions.length > 0) {
			switch(self.queuedActions.shift()) {
				case "up":
					self.isJumping = true;
					self.jumpStartTime = new Date() / 1000;
					break;
				case "left":
					if (self.currentLane != -1) {
						self.isSwitchingLeft = true;
					}
					break;
				case "right":
					if (self.currentLane != 1) {
						self.isSwitchingRight = true;
					}
					break;
			}
		}
		if(self.flying)
			self.element.position.y =1000;
		else{
			if (self.isJumping) {
				var jumpClock = currentTime - self.jumpStartTime;
				self.element.position.y = self.jumpHeight * Math.sin((1 / self.jumpDuration) * Math.PI * jumpClock) + sinusoid(2 * self.stepFreq, 0, 20, 0, self.jumpStartTime - self.runningStartTime);
				if (jumpClock > self.jumpDuration) {
					self.isJumping = false;
					self.runningStartTime += self.jumpDuration;
				}
			} else {
				var runningClock = currentTime - self.runningStartTime;
				self.element.position.y = sinusoid( 2 * self.stepFreq, 0, 20, 0, runningClock);
				self.head.rotation.x = sinusoid( 2 * self.stepFreq, -10, -5, 0, runningClock) * deg2Rad;
				self.torso.rotation.x = sinusoid( 2 * self.stepFreq, -10, -5, 180, runningClock) * deg2Rad;
				//self.leftArm.rotation.x = sinusoid( self.stepFreq, -70, 50, 180, runningClock) * deg2Rad;
				//self.rightArm.rotation.x = sinusoid( self.stepFreq, -70, 50, 0, runningClock) * deg2Rad;
				//self.leftLowerArm.rotation.x = sinusoid( self.stepFreq, 70, 140, 180, runningClock) * deg2Rad;
				//self.rightLowerArm.rotation.x = sinusoid( self.stepFreq, 70, 140, 0, runningClock) * deg2Rad;
				self.leftLeg.rotation.x = sinusoid( self.stepFreq, -20, 80, 0, runningClock) * deg2Rad;
				self.rightLeg.rotation.x = sinusoid( self.stepFreq, -20, 80, 180, runningClock) * deg2Rad;
				self.leftLowerLeg.rotation.x = sinusoid( self.stepFreq, -130, 5, 240, runningClock) * deg2Rad;
				self.rightLowerLeg.rotation.x = sinusoid( self.stepFreq, -130, 5, 60, runningClock) * deg2Rad;
				self.leftLegBack.rotation.x = sinusoid( self.stepFreq, -20, 80, 0, runningClock) * deg2Rad;
				self.rightLegBack.rotation.x = sinusoid( self.stepFreq, -20, 80, 180, runningClock) * deg2Rad;
				self.leftLowerLegBack.rotation.x = sinusoid( self.stepFreq, -130, 5, 240, runningClock) * deg2Rad;
				self.rightLowerLegBack.rotation.x = sinusoid( self.stepFreq, -130, 5, 60, runningClock) * deg2Rad;
			}
		}
		if (self.isSwitchingLeft) {
			self.element.position.x -= 200;
			var offset = self.currentLane * shifting - self.element.position.x;
			if (offset > shifting) {
				self.currentLane -= 1;
				self.element.position.x = self.currentLane * shifting;
				self.isSwitchingLeft = false;
			}
		}
		if (self.isSwitchingRight) {
			self.element.position.x += 200;
			var offset = self.element.position.x - self.currentLane * shifting;
			if (offset > 800) {
				self.currentLane += 1;
				self.element.position.x = self.currentLane * shifting;
				self.isSwitchingRight = false;
			}
		}
	}
	this.onLeftKeyPressed = function() {
		self.queuedActions.push("left");
	}
	this.onUpKeyPressed = function() {
		self.queuedActions.push("up");
	}
	this.onRightKeyPressed = function() {
		self.queuedActions.push("right");
	}
	this.onPause = function() {
		self.pauseStartTime = new Date() / 1000;
	}
	this.onUnpause = function() {
		var currentTime = new Date() / 1000;
		var pauseDuration = currentTime - self.pauseStartTime;
		self.runningStartTime += pauseDuration;
		if (self.isJumping) {
			self.jumpStartTime += pauseDuration;
		}
	}
	this.onBoard = function() {
		this.flying = true;
	}
	this.offBoard = function() {
		this.flying = false;
	}
}


function Police() {
	var self = this;
	var dist_from_player;
	this.skinColor = Colors.brown;
	this.hairColor = Colors.black;
	this.policeShirtColor = Colors.black;
	this.shortsColor = Colors.olive;
	this.jumpDuration = 0.6;
	this.jumpHeight = 1000;
	init();
	function init() {
		self.dist_from_player = 800;
		self.face = createBox(100, 100, 60, self.skinColor, 0, 0, 0);
		self.hair = createBox(105, 20, 65, self.hairColor, 0, 50, 0);
		self.torso = createBox(150, 190, 40, self.policeShirtColor, 0, 100, 0);
		self.leftLowerArm = createLimb(20, 120, 30, self.skinColor, 0, -170, 0);
		self.leftArm = createLimb(30, 140, 40, self.skinColor, -100, 190, -10);
		self.rightLowerArm = createLimb(20, 120, 30, self.skinColor, 0, -170, 0);
		self.rightArm = createLimb(30, 140, 40, self.skinColor, 100, 190, -10);
		self.leftLowerLeg = createLimb(40, 200, 40, self.skinColor, 0, -200, 0);
		self.leftLeg = createLimb(50, 170, 50, self.shortsColor, -50, -10, 30);
		self.rightLowerLeg = createLimb(40, 200, 40, self.skinColor, 0, -200, 0);
		self.rightLeg = createLimb(50, 170, 50, self.shortsColor, 50, -10, 30);
		self.element = createGroup(0, 0, -3005); // default value for payer 0 0 -4000
		self.head = createGroup(0, 260, -25);
		self.head.add(self.face);
		self.head.add(self.hair);
		self.leftArm.add(self.leftLowerArm);
		self.rightArm.add(self.rightLowerArm);
		self.leftLeg.add(self.leftLowerLeg);
		self.rightLeg.add(self.rightLowerLeg);
		self.element.add(self.head);
		self.element.add(self.torso);
		self.element.add(self.leftArm);
		self.element.add(self.rightArm);
		self.element.add(self.leftLeg);
		self.element.add(self.rightLeg);

		self.isJumping = false;
		self.isSwitchingLeft = false;
		self.isSwitchingRight = false;
		self.currentLane = 0;
		self.runningStartTime = new Date() / 1000;
		self.pauseStartTime = new Date() / 1000;
		self.stepFreq = 2;
		self.queuedActions = [];

	}

	function createLimb(dx, dy, dz, color, x, y, z) {
	    var limb = createGroup(x, y, z);
	    var offset = -1 * (Math.max(dx, dz) / 2 + dy / 2);
		var limbBox = createBox(dx, dy, dz, color, 0, offset, 0);
		limb.add(limbBox);
		return limb;
	}

	this.update = function() {
		var currentTime = new Date() / 1000;
		self.element.position.set(0, 0, -4000 + self.dist_from_player);
		if (!self.isJumping && !self.isSwitchingLeft && !self.isSwitchingRight && self.queuedActions.length > 0) {
			switch(self.queuedActions.shift()) {
				case "up":
					self.isJumping = true;
					self.jumpStartTime = new Date() / 1000;
					break;
				case "left":
					if (self.currentLane != -1) {
						self.isSwitchingLeft = true;
					}
					break;
				case "right":
					if (self.currentLane != 1) {
						self.isSwitchingRight = true;
					}
					break;
			}
		}

		if (self.isJumping) {
			var jumpClock = currentTime - self.jumpStartTime;
			self.element.position.y = self.jumpHeight * Math.sin((1 / self.jumpDuration) * Math.PI * jumpClock) + sinusoid(2 * self.stepFreq, 0, 20, 0, self.jumpStartTime - self.runningStartTime);
			if (jumpClock > self.jumpDuration) {
				self.isJumping = false;
				self.runningStartTime += self.jumpDuration;
			}
		} else {
			var runningClock = currentTime - self.runningStartTime;
			self.element.position.y = sinusoid( 2 * self.stepFreq, 0, 20, 0, runningClock);
			//self.head.rotation.x = sinusoid( 2 * self.stepFreq, -10, -5, 0, runningClock) * deg2Rad;
			//self.torso.rotation.x = sinusoid( 2 * self.stepFreq, -10, -5, 180, runningClock) * deg2Rad;
			self.leftArm.rotation.x = sinusoid( self.stepFreq, -70, 50, 180, runningClock) * deg2Rad;
			self.rightArm.rotation.x = sinusoid( self.stepFreq, -70, 50, 0, runningClock) * deg2Rad;
			self.leftLowerArm.rotation.x = sinusoid( self.stepFreq, 70, 140, 180, runningClock) * deg2Rad;
			self.rightLowerArm.rotation.x = sinusoid( self.stepFreq, 70, 140, 0, runningClock) * deg2Rad;
			self.leftLeg.rotation.x = sinusoid( self.stepFreq, -20, 80, 0, runningClock) * deg2Rad;
			self.rightLeg.rotation.x = sinusoid( self.stepFreq, -20, 80, 180, runningClock) * deg2Rad;
			self.leftLowerLeg.rotation.x = sinusoid( self.stepFreq, -130, 5, 240, runningClock) * deg2Rad;
			self.rightLowerLeg.rotation.x = sinusoid( self.stepFreq, -130, 5, 60, runningClock) * deg2Rad;

			if (self.isSwitchingLeft) {
				self.element.position.x -= 200;
				var offset = self.currentLane * shifting - self.element.position.x;
				if (offset > shifting) {
					self.currentLane -= 1;
					self.element.position.x = self.currentLane * shifting;
					self.isSwitchingLeft = false;
				}
			}
			if (self.isSwitchingRight) {
				self.element.position.x += 200;
				var offset = self.element.position.x - self.currentLane * shifting;
				if (offset > 800) {
					self.currentLane += 1;
					self.element.position.x = self.currentLane * shifting;
					self.isSwitchingRight = false;
				}
			}
		}
	}

	this.onLeftKeyPressed = function() { self.queuedActions.push("left"); }
	this.onUpKeyPressed = function() { self.queuedActions.push("up"); }
	this.onRightKeyPressed = function() { self.queuedActions.push("right"); }
	this.onPause = function() { self.pauseStartTime = new Date() / 1000; }

	this.onUnpause = function() {
		var currentTime = new Date() / 1000;
		var pauseDuration = currentTime - self.pauseStartTime;
		self.runningStartTime += pauseDuration;
		if (self.isJumping) {
			self.jumpStartTime += pauseDuration;
		}
	}
}

function Tree(x, y, z, s) {
	var self = this;
	this.mesh = new THREE.Object3D();
    var top = createCylinder(1, 300, 300, 4, Colors.green, 0, 1000, 0);
    var mid = createCylinder(1, 400, 400, 4, Colors.green, 0, 800, 0);
    var bottom = createCylinder(1, 500, 500, 4, Colors.green, 0, 500, 0);
    var trunk = createCylinder(100, 100, 250, 32, Colors.brownDark, 0, 125, 0);
    this.mesh.add(top);
    this.mesh.add(mid);
    this.mesh.add(bottom);
    this.mesh.add(trunk);
    this.mesh.position.set(x, y, z);
	this.mesh.scale.set(s, s, s);
	this.scale = s;
    this.collides = function(minX, maxX, minY, maxY, minZ, maxZ) {
    	var treeMinX = self.mesh.position.x - this.scale * 250;
    	var treeMaxX = self.mesh.position.x + this.scale * 250;
    	var treeMinY = self.mesh.position.y;
    	var treeMaxY = self.mesh.position.y + this.scale * 1150;
    	var treeMinZ = self.mesh.position.z - this.scale * 250;
    	var treeMaxZ = self.mesh.position.z + this.scale * 250;
    	return treeMinX <= maxX && treeMaxX >= minX
    		&& treeMinY <= maxY && treeMaxY >= minY
    		&& treeMinZ <= maxZ && treeMaxZ >= minZ;
    }
}

function Coin(x, y, z, s) {
	var self = this;
	this.mesh = new THREE.Object3D();
	var top = createCylinder(300, 300, 100, 40, Colors.yellow, 0, 1000, 0);
    //var top = createCoin(1, 300, 300, 4, Colors.yellow, 0, 1000, 0);
    //var top = createCoin(1, 300, 300, 4, Colors.yellow, 0, 1000, 0);
    //var top = loadCoinTexture(1,1,1,Colors.yellow,0, 1000, 0);
    this.mesh.add(top);
    //this.mesh.rotation
    this.mesh.rotation.x = Math.PI / 2;
    this.mesh.position.set(x, y+150, z);
	this.mesh.scale.set(s, s, s);
	this.scale = s;
    this.collides = function(minX, maxX, minY, maxY, minZ, maxZ) {
    	var coinMinX = self.mesh.position.x - this.scale * 250;
    	var coinMaxX = self.mesh.position.x + this.scale * 250;
    	var coinMinY = self.mesh.position.y;
    	var coinMaxY = self.mesh.position.y + this.scale * 1150;
    	var coinMinZ = self.mesh.position.z-250 - this.scale * 250;
    	var coinMaxZ = self.mesh.position.z+250 + this.scale * 250;
    	return coinMinX <= maxX && coinMaxX >= minX
    		&& coinMinY <= maxY && coinMaxY >= minY
    		&& coinMinZ <= maxZ && coinMaxZ >= minZ;
    }
    this.moveOut = function(){
    	self.mesh.position.set(10, 10, 0);
    }
    this.update = function(){
    	self.mesh.rotation.y = Math.PI/180;
    }
}

function JumpyJumpy(x, y, z, s) {
	var self = this;
	this.mesh = new THREE.Object3D();
    var top = createCylinder(200, 300, 300, 400, Colors.blue, 0, 1000, 0);
    this.mesh.add(top);
    this.mesh.position.set(x, y, z);
	this.mesh.scale.set(s, s, s);
	this.scale = s;
    this.collides = function(minX, maxX, minY, maxY, minZ, maxZ) {
    	var coinMinX = self.mesh.position.x - this.scale * 250;
    	var coinMaxX = self.mesh.position.x + this.scale * 250;
    	var coinMinY = self.mesh.position.y;
    	var coinMaxY = self.mesh.position.y + this.scale * 1150;
    	var coinMinZ = self.mesh.position.z - this.scale * 250;
    	var coinMaxZ = self.mesh.position.z + this.scale * 250;
    	return coinMinX <= maxX && coinMaxX >= minX
    		&& coinMinY <= maxY && coinMaxY >= minY
    		&& coinMinZ <= maxZ && coinMaxZ >= minZ;
    }
    this.moveOut = function(){
    	self.mesh.position.set(10, 10, 0);
    }
}

function SlowHim(x, y, z, s) {
	var self = this;
	this.mesh = new THREE.Object3D();
    var mid = createCylinder(200, 800, 400, 400, Colors.red, 0, 800, 0);
    this.mesh.add(mid);
    this.mesh.rotation.x = Math.PI /2;
    this.mesh.position.set(x, y, z);
	this.mesh.scale.set(s, s, s);
	this.scale = s;
    this.collides = function(minX, maxX, minY, maxY, minZ, maxZ) {
    	var slowHimMinX = self.mesh.position.x - this.scale * 250;
    	var slowHimMaxX = self.mesh.position.x + this.scale * 250;
    	var slowHimMinY = self.mesh.position.y;
    	var slowHimMaxY = self.mesh.position.y + this.scale * 1150;
    	var slowHimMinZ = self.mesh.position.z - this.scale * 250;
    	var slowHimMaxZ = self.mesh.position.z + this.scale * 250;
    	return slowHimMinX <= maxX && slowHimMaxX >= minX
    		&& slowHimMinY <= maxY && slowHimMaxY >= minY
    		&& slowHimMinZ <= maxZ && slowHimMaxZ >= minZ;
    }
}
function BoostedBoard(x, y, z, s) {
	var self = this;
	this.mesh = new THREE.Object3D();
    var mid = createCylinder(400, 400, 400, 4, Colors.brownDark, 0, 800, 0);
    this.mesh.add(mid);
    this.mesh.position.set(x, y, z);
	this.mesh.scale.set(s, s, s);
	this.scale = s;
    this.collides = function(minX, maxX, minY, maxY, minZ, maxZ) {
    	var slowHimMinX = self.mesh.position.x - this.scale * 250;
    	var slowHimMaxX = self.mesh.position.x + this.scale * 250;
    	var slowHimMinY = self.mesh.position.y;
    	var slowHimMaxY = self.mesh.position.y + this.scale * 1150;
    	var slowHimMinZ = self.mesh.position.z - this.scale * 250;
    	var slowHimMaxZ = self.mesh.position.z + this.scale * 250;
    	return slowHimMinX <= maxX && slowHimMaxX >= minX
    		&& slowHimMinY <= maxY && slowHimMaxY >= minY
    		&& slowHimMinZ <= maxZ && slowHimMaxZ >= minZ;
    }
    this.moveOut = function(){
    	self.mesh.position.set(10, 10, 0);
    }
}

function sinusoid(frequency, minimum, maximum, phase, time) {
	var amplitude = 0.5 * (maximum - minimum);
	var angularFrequency = 2 * Math.PI * frequency;
	var phaseRadians = phase * Math.PI / 180;
	var offset = amplitude * Math.sin(
		angularFrequency * time + phaseRadians);
	var average = (minimum + maximum) / 2;
	return average + offset;
}
function createGroup(x, y, z) {
	var group = new THREE.Group();
	group.position.set(x, y, z);
	return group;
}
function createBox(dx, dy, dz, color, x, y, z) {
    var geom = new THREE.BoxGeometry(dx, dy, dz);
    //var mat = new THREE.MeshPhongMaterial({
	//	color:color, 
    //	flatShading: notFlatShading != true
    //});
    var uniforms = {
			color: {type: 'vec3', value: new THREE.Color(color)},
		};

    var mat = new THREE.ShaderMaterial({ 
    	uniforms: uniforms,
    	vertexShader: document.getElementById('vertexShader').textContent,
        fragmentShader: document.getElementById('fragmentShader').textContent
    });
    var box = new THREE.Mesh(geom, mat);
    box.castShadow = true;
    box.receiveShadow = true;
    box.position.set(x, y, z);
    return box;
}
function createBox_gray(dx, dy, dz, color, x, y, z) {
    var geom = new THREE.BoxGeometry(dx, dy, dz);
    //var mat = new THREE.MeshPhongMaterial({
	//	color:color, 
    //	flatShading: notFlatShading != true
    //});
    var uniforms = {
			color: {type: 'vec3', value: new THREE.Color(color)},
		};

    var mat = new THREE.ShaderMaterial({ 
    	uniforms: uniforms,
    	vertexShader: document.getElementById('vertexShader').textContent,
        fragmentShader: document.getElementById('fragmentShader_gray').textContent
    });
    var box = new THREE.Mesh(geom, mat);
    box.castShadow = true;
    box.receiveShadow = true;
    box.position.set(x, y, z);
    return box;
}
function createCylinder(radiusTop, radiusBottom, height, radialSegments, color, x, y, z) {
    var geom = new THREE.CylinderGeometry( radiusTop, radiusBottom, height, radialSegments);
    //var mat = new THREE.MeshPhongMaterial({ color: color, flatShading: true });
    
    var uniforms = {
			color: {type: 'vec3', value: new THREE.Color(color)},
		};
    var mat = new THREE.ShaderMaterial({ 
    	uniforms: uniforms,
    	vertexShader: document.getElementById('vertexShader').textContent,
        fragmentShader: document.getElementById('fragmentShader').textContent
    });
    var mat_gray = new THREE.ShaderMaterial({ 
    	uniforms: uniforms,
    	vertexShader: document.getElementById('vertexShader').textContent,
        fragmentShader: document.getElementById('fragmentShader_gray').textContent
    });
    var cylinder = new THREE.Mesh(geom, mat);
    cylinder.castShadow = true;
    cylinder.receiveShadow = true;
    cylinder.position.set(x, y, z);
    return cylinder;
}
function createCylinder(radiusTop, radiusBottom, height, radialSegments, color, x, y, z) {
    var geom = new THREE.CylinderGeometry( radiusTop, radiusBottom, height, radialSegments);
    //var mat = new THREE.MeshPhongMaterial({ color: color, flatShading: true });
    
    var uniforms = {
			color: {type: 'vec3', value: new THREE.Color(color)},
		};
    var mat = new THREE.ShaderMaterial({ 
    	uniforms: uniforms,
    	vertexShader: document.getElementById('vertexShader').textContent,
        fragmentShader: document.getElementById('fragmentShader').textContent
    });
    var mat_gray = new THREE.ShaderMaterial({ 
    	uniforms: uniforms,
    	vertexShader: document.getElementById('vertexShader').textContent,
        fragmentShader: document.getElementById('fragmentShader_gray').textContent
    });
    var cylinder = new THREE.Mesh(geom, mat_gray);
    cylinder.castShadow = true;
    cylinder.receiveShadow = true;
    cylinder.position.set(x, y, z);
    return cylinder;
}
function loadGroundTexture(dx, dy, dz, color, x, y, z, notFlatShading){
	var geom = new THREE.BoxGeometry(dx, dy, dz);
	var loader = new THREE.TextureLoader();
    //var mat = new THREE.MeshPhongMaterial({
	//	color:color, 
    //	flatShading: notFlatShading != true
    //});
    var mat = new THREE.MeshLambertMaterial({
	  map: loader.load('js/cat.jpg')
	});
    var box = new THREE.Mesh(geom, mat);
    
    box.castShadow = true;
    box.receiveShadow = true;
    box.position.set(x, y, z);
    return box;
}
function loadWallTexture(dx, dy, dz, color, x, y, z, notFlatShading){
	var geom = new THREE.BoxGeometry(dx, dy, dz);
	var loader = new THREE.TextureLoader();
    //var mat = new THREE.MeshPhongMaterial({
	//	color:color, 
    //	flatShading: notFlatShading != true
    //});
    var mat = new THREE.MeshLambertMaterial({
	  map: loader.load('js/cat.jpg')
	});
    var box = new THREE.Mesh(geom, mat);
    
    box.castShadow = true;
    box.receiveShadow = true;
    box.position.set(x, y, z);
    return box;
}