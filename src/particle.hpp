#ifndef SRC_PARTICLE_HPP_
#define SRC_PARTICLE_HPP_

#include <SDL2/SDL.h>

#define BETA                 0.3;
#define RADIUS               10
#define PARTICLE_KIND_AMOUNT 2;

int attraction_matrix[PARTICLE_KIND_AMOUNT][PARTICLE_KIND_AMOUNT];
enum ParticleType { NORMAL, ATTRACTED, REPULSED };

class Particle {
    SDL_Renderer* _renderer;  /* pointer the renderer */
    Uint8         _r, _g, _b; /* color for the given particle */
    ParticleType  _type;      /* type particle */
    float         _ax;        /* atractor point x */
    float         _ay;        /* atractor point y */
    int           _width;     /*  how wide the particle */
    int           _height;    /* how tall the particle */
    float         _dx;        /* direction point x */
    float         _dy;        /* direction point y */

  public:
    int _x;    /* horizontal coordinate */
    int _y;    /* vertical coordinate */
    int _kind; /* to identify each type of particle */

    inline explicit Particle(int kind, int x, int y, int w, int h, Uint8 r, int g, int b,
                             ParticleType t, float ax, float ay, float dx, float dy) {
        x       = x;
        y       = y;
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
        _kind   = kind;
    }
    void  particle_update(SDL_Renderer* renderer, int cx, int cy);
    float particle_force_handler(float d, int p1_kind, int p2_kind);
    float particle_direction();
};

#endif // SRC_PARTICLE_HPP_
