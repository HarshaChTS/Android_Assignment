# Party on Demand 🎉 (Interactive Firework Explosions)
## Demo

For my final project, I have created OpenGL interactive firework explosion spawner that creates a firework based on user's mouse click. 
![Demo](fireworks.gif)

To create this particle effect, I have created one particle system class that simulates firework explosion and a dynamically sized vector array that holds all particle systems that we want to spawn. My program's work can be conceptually divided into 2 sections -- particle system *spawning* and particle system *animation*.

### Particle System Spawning

Once ```mouse_button_callback()``` function gets triggered (aka when the user left-clicks on the screen), my program:
1. picks up the coordinates of the click (aka explosion point) and normalizes them in order to work with the particle system positioning
2. creates a MyParticleSystem object, passing the explosion point, trail offset, and color as a property of the created object
3. adds the newly created particle system to the global array which holds all particle systems that we need to "fire"
4. initializes the particle system

### Particle System Animation
As ```mouse_button_callback()``` function keeps adding new particle systems to the queue of those that need to be animated on the background, the main while loop is where all the systems actually get updated and drawn. With every iteration of the main ```while()``` loop, we go through the global array of particle systems, updating and redrawing each of them one by one.

### Individual Particle Animation
Because the firework first shoots the "sparks" up in the air and only then explodes, each individual particle has two stages of animation: *initial trailing* and *explosion*. Also, particles are animated with gravity and mass.
- **initial trailing**: particle's initial position is getting passed from ```mouse_button_callback()``` function to ensure the firework explodes where we want it to explode. Initial velocity is set to shoot the particles upward.
- **explosion**: every particle system has a ```counter``` property that gets updated in the main ```while()``` loop and lets the ```update()``` function know when to start the explosion. Once ```counter``` reaches a certain number, ```explodeParticles()``` function goes through each particle and changes their positions and velocities from shooting upwards to shooting along the randomized unit square vectors, which simulates the explosion.

### Future improvements
- Setting velocities and offsets in the *explosion* stage of the particle to be animated to trail along a fixed number of lines, just like the firefor does, and not just randomly.
- Reusing particles systems that have already exploded and are out of the frame, instead of infinitely creating new ones.

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
CG-final-project $ mkdir build
CG-final-project $ cd build
CG-final-project/build $ cmake -G "Visual Studio 16 2019" ..
CG-final-project/build $ start CS312-Particles.sln
```

Your solution file should contain multiple projects, such as `CG-final-project`.
To run from the git bash command shell,

```
CG-final-project/build $ ../bin/Debug/CG-final-project
```

*macOS*

Open terminal to the directory containing this repository.

```
CG-final-project $ mkdir build
CG-final-project $ cd build
CG-final-project/build $ cmake ..
CG-final-project/build $ make
```

To run each program from build, you would type

```
CG-final-project/build $ ../bin/CG-final-project
```
