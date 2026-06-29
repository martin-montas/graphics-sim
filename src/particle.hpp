#ifndef SRC_PARTICLE_HPP_
#define SRC_PARTICLE_HPP_

#include <SDL2/SDL.h>

#define BETA                 0.3
#define RADIUS               10
#define PARTICLE_KIND_AMOUNT 2
#define PARTICLE_WIDTH       10
#define PARTICLE_HEIGHT      10

// int attraction_matrix[PARTICLE_KIND_AMOUNT][PARTICLE_KIND_AMOUNT];
enum ParticleType { NORMAL, ATTRACTED, REPULSED };

class Particle {
    SDL_Renderer* _rend;      /* pointer the renderer */
    SDL_Rect      _rect;      /* pointer the rect */
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

    inline Particle(int kind, int x, int y, int r, int g, int b, ParticleType t,
                    SDL_Renderer* rend) {
        _x    = x;
        _y    = y;
        _r    = r;
        _g    = g;
        _b    = b;
        _type = t;
        _kind = kind;
        _rend = rend;

        _rect = {x, y, PARTICLE_WIDTH, PARTICLE_HEIGHT};
    }
    void  update();
    void  draw();
    float force_handler(float d, int p1_kind, int p2_kind);
    float direction();
};

#endif // SRC_PARTICLE_HPP_
