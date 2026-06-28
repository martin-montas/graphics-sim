#ifndef SRC_PARTICLE_HPP_
#define SRC_PARTICLE_HPP_

#define RADIUS 10

class Particle {
    int           _x;        /* horizontal coordinate */
    int           _y;        /* vertical coordinate */
    int           _width;    /*  how wide the particle */
    int           _height;   /* how tall the particle */
    SDL_Renderer* _renderer; /* pointer the renderer */

  public:
    void drawCircle(SDL_Renderer* renderer, int cx, int cy, int radius);
};

#endif // SRC_PARTICLE_HPP_
