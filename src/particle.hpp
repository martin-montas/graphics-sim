#ifndef SRC_PARTICLE_HPP_
#define SRC_PARTICLE_HPP_

#include <SDL2/SDL.h>

#define RADIUS 10

enum ParticleType { NORMAL, ATTRACTED, REPULSED };

class Particle {
    int           _x;         /* horizontal coordinate */
    int           _y;         /* vertical coordinate */
    int           _width;     /*  how wide the particle */
    int           _height;    /* how tall the particle */
    SDL_Renderer* _renderer;  /* pointer the renderer */
    Uint8         _r, _g, _b; /* color for the given particle */
    ParticleType  _type;      /* type particle */
    float         _ax;        /* atractor point x */
    float         _ay;        /* atractor point y */
    float         _dx;        /* direction point x */
    float         _dy;        /* direction point y */

  public:
    inline explicit Particle(int x, int y, int w, int h, Uint8 r, int g, int b, ParticleType t,
                             float ax, float ay, float dx, float dy) {
        _x      = x;
        _y      = y;
        _width  = w;
        _height = h;
        _r      = r;
        _g      = g;
        _b      = b;
        _type   = t;
        _ax     = ax;
        _ay     = ay;
        _dx     = dx;
        _dy     = dy;
    }
    void draw_particle(SDL_Renderer* renderer, int cx, int cy);
};

#endif // SRC_PARTICLE_HPP_
