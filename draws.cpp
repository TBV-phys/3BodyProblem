// Draws

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include "draws.h"

void drawCircle(float cx, float cy, float r, int segments, const std::array<float,3>& colorRGB){
    glBegin(GL_TRIANGLE_FAN);
    
    glColor3f(colorRGB[0], colorRGB[1], colorRGB[2]); // color del círculo
    glVertex2f(cx, cy); // centro
    
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * M_PI * i / segments;
        float x = cx + cos(angle) * r;
        float y = cy + sin(angle) * r;
        glVertex2f(x, y);
    }
    
    glEnd();
}

void drawTrail(const std::vector<double>& x1, const std::vector<double>& y1, const int& cont, const int& ptsColaMax, const std::array<float,3>& colorRGB){
    glLineWidth(3.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBegin(GL_LINE_STRIP);
    
    glColor4f(colorRGB[0], colorRGB[1], colorRGB[2], 1);
    
    size_t N = std::min((size_t)cont, x1.size());
    
    for(size_t k=0; k < N; k++){
        
        // circular buffer index
        size_t idx = (cont < ptsColaMax) ? k : (cont + k) % ptsColaMax;
        
        //dynamical alpha
        float t = (N > 1) ? float(k) / float(N - 1) : 1.0f;
        float alpha = pow(t, 2.5f);   // o pow(t,2.0f) si quieres más suave
        
        glColor4f(colorRGB[0], colorRGB[1], colorRGB[2], alpha);
        glVertex2f(x1[idx], y1[idx]);
    }
        
    glEnd();
}
