#ifndef SRC_PARTICLE_HPP_
#define SRC_PARTICLE_HPP_

#include <SDL2/SDL.h>

#define BETA                 0.3
#define RADIUS               10
#define PARTICLE_KIND_AMOUNT 2
#define PARTICLE_WIDTH       5
#define PARTICLE_HEIGHT      5
#define K                    0.05
#define FRICTION             0.85

struct Vec2 {
    int   x, y;
    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator*=(const Vec2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }
};

class Particle {
    SDL_Renderer* _rend;      /* pointer the renderer */
    SDL_Rect      _rect;      /* pointer the rect */
    Uint8         _r, _g, _b; /* color for the given particle */
    ParticleType  _type;      /* type particle */
    int           _width;     /*  how wide the particle */
    int           _height;    /* how tall the particle */
    int           _min_dist;  /* min distance of single particle */
    int           _max_dist;  /* max distance of single particle */
    int           _vx;        /* velocity of particle */
    int           _vy;        /* velocity of particle */

  public:
    int _x;    /* horizontal coordinate */
    int _y;    /* vertical coordinate */
    int _kind; /* to identify each type of particle */

    void  update(std::vector<Particle*>& swarm);
    void  draw();
    float force_handler(float d, int p1_kind, int p2_kind);
    float direction();

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
};

#endif // SRC_PARTICLE_HPP_
