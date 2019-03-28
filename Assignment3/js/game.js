// This JS Script Has been written by Anurag Sahu as a part of Graphics Assignment 3 A webGL openGmae

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
};

var deg2Rad = Math.PI / 180;
var shifting = 1200;

// Make a new world when the page is loaded.
window.addEventListener('load', function(){
	new World();
});


// This class has the main Game engine Start from Here.

function World() {
	var self = this;
	var element, scene, camera, character, police, renderer, light,
		objects, paused, keysAllowed, score, difficulty,
		treePresenceProb, maxTreeSize, fogDistance, gameOver,
		player_speed, coins_objects;
	init();
	function init() {
		element = document.getElementById('world');
		renderer = new THREE.WebGLRenderer({ alpha: true, antialias: true });
		renderer.setSize(element.clientWidth/1, element.clientHeight);
		renderer.shadowMap.enabled = true;
		element.appendChild(renderer.domElement);
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
		var ground = createBox(5000, 20, 120000, Colors.sand, 0, -400, -60000);
		scene.add(ground);
		objects = [];
		coins_objects = [];
		player_speed = 80;
		treePresenceProb = 0.2;
		maxTreeSize = 0.5;
		for (var i = 10; i < 15; i++) {
			createRowOfTrees(i * -3000, treePresenceProb, 0.5, maxTreeSize);
		}
		for(var i = 10; i < 15; i++){
			createRowOfCoins( i * -3000, treePresenceProb, 0.5, 0.5);
		}
		gameOver = false;
		paused = true;

		// Before Adding any key for Input Lookup the Encoding of that Key online
		var left = 37;
		var up = 38;
		var right = 39;
		var p = 80;
		var space = 32;
		
		keysAllowed = {};
		document.addEventListener(
			'keydown',
			function(e) {
				if (!gameOver) {
					var key = e.keyCode;
					if (keysAllowed[key] === false) return;
					keysAllowed[key] = false;
					if (paused && !collisionsDetectedTrees() && key > 18) {
						paused = false;
						character.onUnpause();
						police.onUnpause();
						document.getElementById("variable-content").style.visibility = "hidden";
						//document.getElementById("controls").style.display = "none";
					} else {
						if (key == p) {
							paused = true;
							character.onPause();
							police.onPause();
							document.getElementById(
								"variable-content").style.visibility = "visible";
							document.getElementById(
								"variable-content").innerHTML = 
								"Game is paused. Press any key to resume.";
						}
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
						}
						if (key == right && !paused) {
							character.onRightKeyPressed();
							police.onRightKeyPressed();
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
		if (!paused) {  // Update the Game if Not paused
			treePresenceProb = 0.55;
			createRowOfTrees(-120000, treePresenceProb, 0.5, 0.5);
			createRowOfCoins(-120000, treePresenceProb, 0.5, 0.5);
			scene.fog.far = fogDistance;

			// Move the trees closer to the character.
			objects.forEach(function(object) {
				object.mesh.position.z += character.speed;
			});
			coins_objects.forEach(function(object){
				object.mesh.position.z += character.speed;
			});
			police.dist_from_player += 5;

			// Remove trees that are outside of the world.
			objects = objects.filter(function(object) {
				return object.mesh.position.z < 0;
			});
			coins_objects = coins_objects.filter(function(object){
				return object.mesh.position.z < 0;
			})

			// Make the character move according to the controls.
			character.update();
			police.update();

			// Check for collisions between the character and objects.
			if (collisionsDetectedTrees()) {

				// This part is for collision with Coins
				score += 1;

				//This part is for collision with Obstacles
				//document.addEventListener(
        		//	'keydown',
        		//	function(e) {
        		//		if (e.keycode == 32)
            	//		document.location.reload(true);
        		//	}
    			//);
    			//var variableContent = document.getElementById("variable-content");
    			//variableContent.style.visibility = "visible";
    			//variableContent.innerHTML =  "Hey Pal! look where you are running or you will be caught by the Police Men";
    			//if(police.dist_from_player < 1000){ police.dist_from_player -=70; }
    			//else { police.dist_from_player = 800; }
    			//if( police.dist_from_player < 500){
    			//	console.log("Game Over\n");
    			//	variableContent.innerHTML =  "Game Over !!!";
				//	paused = true;
				//	gameOver = true;
				//}
			}

			// Update the scores.
			document.getElementById("score").innerHTML = score;

		}

		// Render the page and repeat.
		renderer.render(scene, camera);
		requestAnimationFrame(loop);
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

	function createRowOfCoins(position,probability, minScale, maxScale){
		for (var lane = -1; lane < 2; lane++) {
			var randomNumber = Math.random();
			if (randomNumber < probability) {
				var scale = minScale + (maxScale - minScale) * Math.random();
				var coin = new Coin(lane * 1200, -400, position, scale);
				coins_objects.push(coin);
				scene.add(coin.mesh);
			}
		}
	}
	/**
	 * Returns true if and only if the character is currently colliding with
	 * an object on the map.
	 */
 	function collisionsDetectedTrees() {
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
 		//for (var i = 0; i < objects.length; i++) {
 			if (coins_objects[i].collides(charMinX, charMaxX, charMinY, charMaxY, charMinZ, charMaxZ)) {
 				return true;
 			}
 		//}
 		return false;
 	}
	
}

function Character() {
	var self = this;
	var speed;
	this.skinColor = Colors.brown;
	this.hairColor = Colors.black;
	this.shirtColor = Colors.yellow;
	this.shortsColor = Colors.olive;
	this.jumpDuration = 0.6;
	this.jumpHeight = 1000;
	init();
	function init() {
		self.speed = 80;
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

	this.update = function() {
		var currentTime = new Date() / 1000;

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

}

// The Dog's Character in the game
function dog(){

}


// the Character of Police man in Game 
function Police() {
	var self = this;
	var speed;
	var dist_from_player;
	this.skinColor = Colors.brown;
	this.hairColor = Colors.black;
	this.policeShirtColor = Colors.black;
	this.shortsColor = Colors.olive;
	this.jumpDuration = 0.6;
	this.jumpHeight = 1000;
	init();
	function init() {
		self.speed = 80;
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
		self.element = createGroup(0, 0, -4000 + self.dist_from_player); // default value for payer 0 0 -4000
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

		//self.element = createGroup(0, 0, -4000 + self.dist_from_player); // default value for payer 0 0 -4000
		self.element.position.set(0, 0, -4000 + self.dist_from_player);
		var currentTime = new Date() / 1000;

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

function Coin(x,y,z,s){
	// Explicit binding.
	var self = this;

	// The object portrayed in the scene.
	this.mesh = new THREE.Object3D();
    var top = createCylinder(1, 300, 300, 4, Colors.yellow, 0, 1000, 0);
    var mid = createCylinder(1, 400, 400, 4, Colors.yellow, 0, 800, 0);
    var bottom = createCylinder(1, 500, 500, 4, Colors.yellow, 0, 500, 0);
    var trunk = createCylinder(100, 100, 250, 32, Colors.yellow, 0, 125, 0);
    this.mesh.add(top);
    this.mesh.add(mid);
    this.mesh.add(bottom);
    this.mesh.add(trunk);
    this.mesh.position.set(x, y, z);
	this.mesh.scale.set(s, s, s);
	this.scale = s;

	/**
	 * A method that detects whether this tree is colliding with the character,
	 * which is modelled as a box bounded by the given coordinate space.
	 */
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

function Tree(x, y, z, s) {

	// Explicit binding.
	var self = this;

	// The object portrayed in the scene.
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

	/**
	 * A method that detects whether this tree is colliding with the character,
	 * which is modelled as a box bounded by the given coordinate space.
	 */
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

/** 
 *
 * UTILITY FUNCTIONS
 * 
 * Functions that simplify and minimize repeated code.
 *
 */

/**
 * Utility function for generating current values of sinusoidally
 * varying variables.
 *
 * @param {number} FREQUENCY The number of oscillations per second.
 * @param {number} MINIMUM The minimum value of the sinusoid.
 * @param {number} MAXIMUM The maximum value of the sinusoid.
 * @param {number} PHASE The phase offset in degrees.
 * @param {number} TIME The time, in seconds, in the sinusoid's scope.
 * @return {number} The value of the sinusoid.
 *
 */
function sinusoid(frequency, minimum, maximum, phase, time) {
	var amplitude = 0.5 * (maximum - minimum);
	var angularFrequency = 2 * Math.PI * frequency;
	var phaseRadians = phase * Math.PI / 180;
	var offset = amplitude * Math.sin(
		angularFrequency * time + phaseRadians);
	var average = (minimum + maximum) / 2;
	return average + offset;
}

/**
 * Creates an empty group of objects at a specified location.
 *
 * @param {number} X The x-coordinate of the group.
 * @param {number} Y The y-coordinate of the group.
 * @param {number} Z The z-coordinate of the group.
 * @return {Three.Group} An empty group at the specified coordinates.
 *
 */
function createGroup(x, y, z) {
	var group = new THREE.Group();
	group.position.set(x, y, z);
	return group;
}

/**
 * Creates and returns a simple box with the specified properties.
 *
 * @param {number} DX The width of the box.
 * @param {number} DY The height of the box.
 * @param {number} DZ The depth of the box.
 * @param {color} COLOR The color of the box.
 * @param {number} X The x-coordinate of the center of the box.
 * @param {number} Y The y-coordinate of the center of the box.
 * @param {number} Z The z-coordinate of the center of the box.
 * @param {boolean} NOTFLATSHADING True iff the flatShading is false.
 * @return {THREE.Mesh} A box with the specified properties.
 *
 */
function createBox(dx, dy, dz, color, x, y, z, notFlatShading) {
    var geom = new THREE.BoxGeometry(dx, dy, dz);
    var mat = new THREE.MeshPhongMaterial({
		color:color, 
    	flatShading: notFlatShading != true
    });

    //var loader = new THREE.ImageBitmapLoader();
    //loader.load('./imag1.png',function(imageBitmap){
    //	var texture = new THREE.CanvasTexture(imagebitmap);
    //	var material = new THREE.MeshBasicMaterial({map: texture});
    //},
    //undefined,
    //function(err){
    //	console.log("An error happened");
    //});

    var box = new THREE.Mesh(geom, mat);
    box.castShadow = true;
    box.receiveShadow = true;
    box.position.set(x, y, z);
    return box;
}

/**
 * Creates and returns a (possibly asymmetrical) cyinder with the 
 * specified properties.
 *
 * @param {number} RADIUSTOP The radius of the cylinder at the top.
 * @param {number} RADIUSBOTTOM The radius of the cylinder at the bottom.
 * @param {number} HEIGHT The height of the cylinder.
 * @param {number} RADIALSEGMENTS The number of segmented faces around 
 *                                the circumference of the cylinder.
 * @param {color} COLOR The color of the cylinder.
 * @param {number} X The x-coordinate of the center of the cylinder.
 * @param {number} Y The y-coordinate of the center of the cylinder.
 * @param {number} Z The z-coordinate of the center of the cylinder.
 * @return {THREE.Mesh} A box with the specified properties.
 */
function createCylinder(radiusTop, radiusBottom, height, radialSegments, color, x, y, z) {
    var geom = new THREE.CylinderGeometry( radiusTop, radiusBottom, height, radialSegments);
    //var mat = new THREE.MeshPhongMaterial({ color: color, flatShading: true });
    var mat = new THREE.ShaderMaterial({ 
    	vertexShader: document.getElementById('vertexShader').textContent,
        fragmentShader: document.getElementById('fragmentShader').textContent
    });
    console.log("Debug");
    var cylinder = new THREE.Mesh(geom, mat);
    cylinder.castShadow = true;
    cylinder.receiveShadow = true;
    cylinder.position.set(x, y, z);
    return cylinder;
}
