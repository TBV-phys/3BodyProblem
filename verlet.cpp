#include "verlet.h"

void verlet(double& x_prev, double& y_prev, double& x, double& y, double& vx, double& vy, double& ax, double& ay, float dt){
    
    double x_new = 2*x - x_prev + dt*dt*ax;
    double y_new = 2*y - y_prev + dt*dt*ay;

    vx = (x_new - x_prev) / (2*dt);
    vy = (y_new - y_prev) / (2*dt);

    x_prev = x;
    y_prev = y;
    x = x_new;
    y = y_new;
};
