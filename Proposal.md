# Object Shattering Particle Effect


![Example](shatter.gif)
Source: https://youtu.be/w4aMtKeD2w4

### How is it unique from existing demos in our class?
This effect is unique because it is tied directly to the object in the scene that we are trying to destroy, which creates the shattering effect that is more realistic than just the explosion itself.
### Features Timeline 
#### Minimum requirements (finish by May 18th):
1. Adding and animating fire explosion particles 
2. Triangular particles of the color of the object exploding outwards from the object
3. Smoke particles exploding outwards from the object and trailing the shattered particles
#### Good-to-have (finish by May 19th):
4. Creating and animating fire, smoke, and shattered pieces according to the shape and size of the object
5. Adding object's texture to the triangular particles
#### Stretch (finish by May 20th):
6. Turn triangular billboard particles to be 3-dimentional and animated with addition of mass and gravity

### Algorithms, data structures and/or background math:
For this effect, I will be using the general algorithms and data structures that we used for our other particle effects. 
 - for fire explosion: sprite sheet with animation centered mostly at the object itself
 - for shattered pieces: object pool that spawns particle based on the size or shape of the object and uses mass and rotations to make it look more realistic
 - for smoke particles: spawning puff billboards with blending that are (if possible) animated based on the velocities of shattered pieces to create the trailing smoke effect
