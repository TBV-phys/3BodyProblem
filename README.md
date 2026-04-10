Three-Body Problem Simulation (Verlet)

This project implements a real-time numerical simulation of a three-body gravitational system using the Verlet integration algorithm (second-order solver). The simulation visualizes the motion of three interacting bodies under Newtonian gravity and displays their trajectories.
The program uses OpenGL (via GLFW) for rendering and provides a continuous visualization of positions and orbital trails.

---

Features

* Newtonian three-body dynamics
* Verlet numerical integration
* Real-time rendering (OpenGL + GLFW)
* Orbital trails
* Energy conservation monitoring

---

Requirements

* C++11 or higher
* OpenGL
* GLFW

---

Structure

* `main.cpp` — simulation loop and setup
* `verlet.*` — integration method
* `draws.*` — rendering utilities
* `stable_inCond.text` - some initial conditions for different configurations


Orbiting objects are initialized in `main.cpp` and stored in a class named `Obj`.

---

How it works (main)

The program performs three main steps:

1. Initialization:

   Defines simulation parameters (dt, G).     
   Initializes the three bodies (mass, position, velocity) as class `Obj`.  
   Computes initial accelerations using Newtonian gravity.  
   Estimates previous positions (pos_prev) required by the Verlet method.  
   Initializes trail buffers for visualization.  
   Computes initial total energy (E0) which is conserved throught the evolution of the system.  

3. Simulation loop (at each frame):
   
   Clears the screen and draws:  
      Bodies as circles.  
      Their trajectories (trails).  
   Updates positions using the Verlet integrator.  
   Recomputes distances and accelerations between bodies.  
   Stores new positions in the trail buffers.  
   Computes the total energy of the system at each step (E) and prints the relative error to E0 as an estimation of the local error in the numerical integration. Note that Verlet algorithm is a locally secod-order solver and, therefore, errors are of order dt^2 at each step, as can be seen by the relative error in the energy conservation.  
   
4. Rendering & events
   
   Swap buffers to display the frame.  
   Poll window events (close, input, etc.).  

The loop runs until the window is closed.
