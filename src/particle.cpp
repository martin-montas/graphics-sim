#include "particle.hpp"
#include "global.hpp"
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>

float map(float value, float in_min, float in_max, float out_min, float out_max) {
    return out_min + (value - in_min) * (out_max - out_min) / (in_max - in_min);
}

float magnitude(const Vec2& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}
Vec2 normalize(const Vec2& v) {
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    if (len == 0.0f)
        return {0.0f, 0.0f}; // avoid division by zero
    return {v.x / len, v.y / len};
}

void Particle::update(std::vector<Particle*>& swarm) {
    Vec2 direction;
    Vec2 velocity;
    velocity.x = 0;
    velocity.y = 0;
    Vec2 total_force;
    total_force.x = 0;
    total_force.y = 0;
    Vec2 acceleration;
    acceleration.x = 0;
    acceleration.y = 0;
    float dis;
    for (auto p : swarm) {
        if (p != this) {
            direction.x = 0;
            direction.y = 0;

            direction.x = p->_x - _x;
            direction.y = p->_y - _y;
            if (direction.x > 0.5 * WIDTH) {
                direction.x -= WIDTH;
            }
            if (direction.x < -0.5 * WIDTH) {
                direction.x += WIDTH;
            }
            if (direction.y > 0.5 * HEIGHT) {
                direction.y -= HEIGHT;
            }
            if (direction.y < -0.5 * HEIGHT) {
                direction.y += HEIGHT;
            }

            dis = magnitude(direction);
            if (dis > 0.00001f) {
                Vec2 dir = normalize(direction);
                if (dis < min_distance_matrix[_kind][p->_kind]) {
                    Vec2 force = dir;
                    // force.x    = direction.x;
                    // force.y    = direction.y;

                    force.x *= std::abs(force_matrix[_kind][p->_kind]) * -3;
                    force.y *= std::abs(force_matrix[_kind][p->_kind]) * -3;

                    force.x *= map(dis, 0, min_distance_matrix[_kind][p->_kind], 1, 0);
                    force.y *= map(dis, 0, min_distance_matrix[_kind][p->_kind], 1, 0);

                    force.x *= K;
                    force.y *= K;

                    total_force += force;
                } else if (dis < radii_matrix[_kind][p->_kind]) {
                    Vec2 force = dir;
                    // force.x    = direction.x;
                    // force.y    = direction.y;

                    force.x *= force_matrix[_kind][p->_kind];
                    force.y *= force_matrix[_kind][p->_kind];

                    force.x *= map(dis, 0, radii_matrix[_kind][p->_kind], 1, 0);
                    force.y *= map(dis, 0, radii_matrix[_kind][p->_kind], 1, 0);

                    force.x *= K;
                    force.y *= K;

                    total_force += force;
                }
            }
        }
    }
    acceleration += total_force;
    velocity += acceleration;
    _x += velocity.x;
    _y += velocity.y;

    _x = (_x + WIDTH) % WIDTH;
    _y = (_y + HEIGHT) % HEIGHT;

    velocity.x *= FRICTION;
    velocity.y *= FRICTION;
}

void Particle::draw() {
    SDL_SetRenderDrawColor(_rend, _r, _g, _b, 255);
    SDL_Rect rect = {(int)_x, (int)_y, PARTICLE_WIDTH, PARTICLE_HEIGHT};
    SDL_RenderFillRect(_rend, &rect);
}
