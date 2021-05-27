# Computer Graphis Final Project
## Party on Demand (Interactive Firework Explosions)


OpenGL interactive firework explosion spawner that creates a firework based on user's mouse click.

![Demo](fireworks.gif)

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
