#ifndef SRC_BOID_HPP_
#define SRC_BOID_HPP_

#include <SDL2/SDL.h>
#include <random>
#include <vector>

#define RADIUS       10
#define FLOCK_RADIUS 4
#define K            0.05
#define FRICTION     0.85;

using namespace std;

struct Vec2 {
    float x, y;
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

class Boid {
    SDL_Renderer* _rend; /* pointer to renderer object */
    float         angle = 0.0f;

  public:
    int       x;       /* coodinate x */
    int       y;       /* coodinate y */
    SDL_Point _ver[3]; /* pointer to vertexs */

    inline Boid(SDL_Renderer* rend, SDL_Point p1, SDL_Point p2, SDL_Point p3) {
        _rend   = rend;
        _ver[0] = p1;
        _ver[1] = p2;
        _ver[2] = p3;
    }

    void draw();
    void rotate(float rotate);
    void update(std::vector<Boid*> swarm);
    void check_doundries();
};

#endif // SRC_BOID_HPP_
