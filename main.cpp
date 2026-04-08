#include <iostream>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

#include "verlet.h"
#include "draws.h"

// Objects
struct Pair{
    double x,y;
};

struct Trail{
    int ptsTrailMax;
    std::vector<double> x;
    std::vector<double> y;
};

struct Obj{
    double mass,radius;
    Pair pos, pos_prev, vel, acc;
    std::array<float,3> colorRGB;
    Trail trail;
    
};

Obj p1, p2, p3;
    
//Main

int main(void)
{
    int winWidth = 800;
    int winHeight = 800;

    float dt = 0.001;
    double G = 0.25;
    
    // P1
    p1.mass = 35;
    p1.pos.x =  -0.8;
    p1.pos.y =  0.0;
    p1.vel.x =  0.0;
    p1.vel.y =  -1.0;


    // P2
    p2.mass = 40;
    p2.pos.x = 1.;
    p2.pos.y = 0;
    p2.vel.x = 0;
    p2.vel.y = 1;

    
    // P3
    p3.mass = 0.02;
    p3.pos.x = 0.5;
    p3.pos.y = 0;
    p3.vel.x = 0;
    p3.vel.y = -0.2+sqrt(G * p2.mass / 0.4);


    
    double d12 = sqrt((p1.pos.x-p2.pos.x)*(p1.pos.x-p2.pos.x) + (p1.pos.y-p2.pos.y)*(p1.pos.y-p2.pos.y));
    double d13 = sqrt((p1.pos.x-p3.pos.x)*(p1.pos.x-p3.pos.x) + (p1.pos.y-p3.pos.y)*(p1.pos.y-p3.pos.y));
    double d23 = sqrt((p2.pos.x-p3.pos.x)*(p2.pos.x-p3.pos.x) + (p2.pos.y-p3.pos.y)*(p2.pos.y-p3.pos.y));
    
    
    p1.acc.x = G * p2.mass * ((p2.pos.x - p1.pos.x) / (d12 * d12 * d12)) + G * p3.mass * ((p3.pos.x - p1.pos.x)/(d13 * d13 * d13));
    p1.acc.y = G * p2.mass * ((p2.pos.y - p1.pos.y) / (d12 * d12 * d12)) + G * p3.mass * ((p3.pos.y - p1.pos.y)/(d13 * d13 * d13));
    p1.pos_prev.x = p1.pos.x - p1.vel.x * dt + 0.5 * p1.acc.x * dt * dt;
    p1.pos_prev.y = p1.pos.y - p1.vel.y * dt + 0.5 * p1.acc.y * dt * dt;
    
    p2.acc.x = G * p1.mass * ((p1.pos.x - p2.pos.x) / (d12 * d12 * d12)) + G * p3.mass * ((p3.pos.x - p2.pos.x)/(d23 * d23 * d23));
    p2.acc.y = G * p1.mass * ((p1.pos.y - p2.pos.y) / (d12 * d12 * d12)) + G * p3.mass * ((p3.pos.y - p2.pos.y)/(d23 * d23 * d23));
    p2.pos_prev.x = p2.pos.x - p2.vel.x * dt + 0.5 * p2.acc.x * dt * dt;
    p2.pos_prev.y = p2.pos.y - p2.vel.y * dt + 0.5 * p2.acc.y * dt * dt;
    
    p3.acc.x = G * p1.mass * ((p1.pos.x - p3.pos.x) / (d13 * d13 * d13)) + G * p2.mass * ((p2.pos.x - p3.pos.x) / (d23 * d23 * d23));
    p3.acc.y = G * p1.mass * ((p1.pos.y - p3.pos.y) / (d13 * d13 * d13)) + G * p2.mass * ((p2.pos.y - p3.pos.y) / (d23 * d23 * d23));
    p3.pos_prev.x = p3.pos.x - p3.vel.x * dt + 0.5 * p3.acc.x * dt * dt;
    p3.pos_prev.y = p3.pos.y - p3.vel.y * dt + 0.5 * p3.acc.y * dt * dt;
    
    p1.radius = 0.1;
    p1.colorRGB = {1.0, 0.0, 0.0};
    p1.trail.ptsTrailMax = 1000;
    p1.trail.x.resize(p1.trail.ptsTrailMax);
    p1.trail.y.resize(p1.trail.ptsTrailMax);
    p1.trail.x[0] = p1.pos_prev.x;
    p1.trail.y[0] = p1.pos_prev.y;
    p1.trail.x[1] = p1.pos.x;
    p1.trail.y[1] = p1.pos.y;
    
    p2.radius = 0.1;
    p2.colorRGB = {0.0, 1.0, 0.0};
    p2.trail.ptsTrailMax = 1000;
    p2.trail.x.resize(p2.trail.ptsTrailMax);
    p2.trail.y.resize(p2.trail.ptsTrailMax);
    p2.trail.x[0] = p2.pos_prev.x;
    p2.trail.y[0] = p2.pos_prev.y;
    p2.trail.x[1] = p2.pos.x;
    p2.trail.y[1] = p2.pos.y;
    
    p3.radius = 0.05;
    p3.colorRGB = {1.0, 1.0, 1.0};
    p3.trail.ptsTrailMax = 1000;
    p3.trail.x.resize(p3.trail.ptsTrailMax);
    p3.trail.y.resize(p3.trail.ptsTrailMax);
    p3.trail.x[0] = p3.pos_prev.x;
    p3.trail.y[0] = p3.pos_prev.y;
    p3.trail.x[1] = p3.pos.x;
    p3.trail.y[1] = p3.pos.y;
    
    double E0 = 0.5 * p1.mass * (p1.vel.x * p1.vel.x + p1.vel.y * p1.vel.y) + 0.5 * p2.mass * (p2.vel.x * p2.vel.x + p2.vel.y * p2.vel.y) + 0.5 * p3.mass * (p3.vel.x * p3.vel.x + p3.vel.y * p3.vel.y) - G * p1.mass * p2.mass / d12 - G * p1.mass * p3.mass / d13 - G * p2.mass * p3.mass / d23;
    double E;
    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(winWidth, winHeight, "3BodyProblem", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3, 3, -3, 3, -1, 1);
    
    std::cout << "OpenGL Version: "
              << glGetString(GL_VERSION) << std::endl;

    std::cout << "GLSL Version: "
              << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


    
    unsigned int cont = 2;
    
    /* Loop until the user closes the window */
    
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
            
        drawCircle(p1.pos.x,p1.pos.y,p1.radius,30,p1.colorRGB);
        drawTrail(p1.trail.x,p1.trail.y, cont, p1.trail.ptsTrailMax, p1.colorRGB);
        
        drawCircle(p2.pos.x,p2.pos.y,p2.radius,30,p2.colorRGB);
        drawTrail(p2.trail.x,p2.trail.y, cont, p2.trail.ptsTrailMax, p2.colorRGB);
        
        drawCircle(p3.pos.x,p3.pos.y,p3.radius,30,p3.colorRGB);
        drawTrail(p3.trail.x,p3.trail.y, cont, p3.trail.ptsTrailMax, p3.colorRGB);
       
        verlet(p1.pos_prev.x, p1.pos_prev.y, p1.pos.x, p1.pos.y, p1.vel.x, p1.vel.y, p1.acc.x, p1.acc.y, dt);
        verlet(p2.pos_prev.x, p2.pos_prev.y, p2.pos.x, p2.pos.y, p2.vel.x, p2.vel.y, p2.acc.x, p2.acc.y, dt);
        verlet(p3.pos_prev.x, p3.pos_prev.y, p3.pos.x, p3.pos.y, p3.vel.x, p3.vel.y, p3.acc.x, p3.acc.y, dt);
        
        d12 = sqrt((p1.pos.x-p2.pos.x)*(p1.pos.x-p2.pos.x) + (p1.pos.y-p2.pos.y)*(p1.pos.y-p2.pos.y));
        d13 = sqrt((p1.pos.x-p3.pos.x)*(p1.pos.x-p3.pos.x) + (p1.pos.y-p3.pos.y)*(p1.pos.y-p3.pos.y));
        d23 = sqrt((p2.pos.x-p3.pos.x)*(p2.pos.x-p3.pos.x) + (p2.pos.y-p3.pos.y)*(p2.pos.y-p3.pos.y));
        
        E = 0.5 * p1.mass * (p1.vel.x * p1.vel.x + p1.vel.y * p1.vel.y) + 0.5 * p2.mass * (p2.vel.x * p2.vel.x + p2.vel.y * p2.vel.y) + 0.5 * p3.mass * (p3.vel.x * p3.vel.x + p3.vel.y * p3.vel.y) - G * p1.mass * p2.mass / d12 - G * p1.mass * p3.mass / d13 - G * p2.mass * p3.mass / d23;
        
        p1.acc.x = G * p2.mass * ((p2.pos.x - p1.pos.x) / (d12 * d12 * d12)) + G * p3.mass * ((p3.pos.x - p1.pos.x)/(d13 * d13 * d13));
        p1.acc.y = G * p2.mass * ((p2.pos.y - p1.pos.y) / (d12 * d12 * d12)) + G * p3.mass * ((p3.pos.y - p1.pos.y)/(d13 * d13 * d13));
        
        p2.acc.x = G * p1.mass * ((p1.pos.x - p2.pos.x) / (d12 * d12 * d12)) + G * p3.mass * ((p3.pos.x - p2.pos.x)/(d23 * d23 * d23));
        p2.acc.y = G * p1.mass * ((p1.pos.y - p2.pos.y) / (d12 * d12 * d12)) + G * p3.mass * ((p3.pos.y - p2.pos.y)/(d23 * d23 * d23));
        
        p3.acc.x = G * p1.mass * ((p1.pos.x - p3.pos.x) / (d13 * d13 * d13)) + G * p2.mass * ((p2.pos.x - p3.pos.x) / (d23 * d23 * d23));
        p3.acc.y = G * p1.mass * ((p1.pos.y - p3.pos.y) / (d13 * d13 * d13)) + G * p2.mass * ((p2.pos.y - p3.pos.y) / (d23 * d23 * d23));
        
        p1.trail.x[cont % p1.trail.ptsTrailMax] = p1.pos.x;
        p1.trail.y[cont % p1.trail.ptsTrailMax] = p1.pos.y;
        
        p2.trail.x[cont % p2.trail.ptsTrailMax] = p2.pos.x;
        p2.trail.y[cont % p2.trail.ptsTrailMax] = p2.pos.y;
        
        p3.trail.x[cont % p3.trail.ptsTrailMax] = p3.pos.x;
        p3.trail.y[cont % p3.trail.ptsTrailMax] = p3.pos.y;
        
        cont++;
        
        
        /*Local relative error display*/
        std::cout << "E_tot = " << E0 << "\t E_verlet = " << E << "\t loc_rel_err = " << abs((E0-E)/E0)<< std::endl;
        
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    
    

    return cont;
}
