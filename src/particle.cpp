#include "particle.hpp"
#include "global.hpp"
#include <SDL2/SDL.h>

float map(float value, float in_min, float in_max, float out_min, float out_max) {
    return out_min + (value - in_min) * (out_max - out_min) / (in_max - in_min);
}

void Particle::update(std::vector<Particle*>& swarm) {
    Vec direction, direction.x = 0, direction.y = 0;
    Vec velocity, velocity.x = 0, velocity.y = 0;
    Vec total_force, total_force.x = 0, total_force.y = 0;
    Vec acceleration, acceleration.x = 0, acceleration.y = 0;

    float dis;
    for (auto p : swarm) {
        if (p != this) {
            direction.x *= 0;
            _x -= dir_x, _y -= dir_y;
            float dx = p->_x, float dy = p->_y;

            dis = std::sqrt(dx);
            if (distance > 0.0f) {
                dx /= distance;
                dy /= distance;
            }
            if (dis < min_distance[_kind][p->_kind]) {
                Vec2 force, force.x = direction.x, force.y = direction.y;
                force.x *= foce_matrix[_kind][p->_kind] * -3;
                force.y *= foce_matrix[_kind][p->_kind] * -3;

                force.x = map(dis, 0, min_distance[_kind][p->_kind], 1, 0);
                force.y = map(dis, 0, min_distance[_kind][p->_kind], 1, 0);
                if (dis > max_distance) {
                    dis = max_distance;
                }
                if (dis < 0) {
                    dis = 0;
                }
                force.x *= K;
                force.y *= K;

                total_force += force;
            }
        }
    }
    acceleration += total_force;
    velocity += acceleration;
    _x += velocity.x, _y += velocity.y;

    _x = (_x * 800) % 800;
    _y = (_y * 600) % 600;
    total_force.x += FRICTION;
    total_force.y += FRICTION;
}
void Particle::draw() {
    SDL_SetRenderDrawColor(_rend, _r, _g, _b, 255);
    SDL_Rect rect = {(int)_x, (int)_y, PARTICLE_WIDTH, PARTICLE_HEIGHT};
    SDL_RenderFillRect(_rend, &rect);
}

// void Particle::particle_distance(Particle p1, Particle p2) {
//     float dx              = p1._x - p2._x;
//     float dy              = p1._y - p2._y;
//     float distance_square = dx * dx + dy * dy;
//
//     if (distance_square < 1.0f * 1.0f) {
//         // particles are closer than 1 unit
//         // maybe use force function here
//     }
// }

// float Particle::particle_force_handler(float d, int p1_kind, int p2_kind) {
//     float a = attraction_matrix[p1_kind][p2_kind];
//
//     if (d < BETA) {
//         return d / BETA - 1;
//     } else if (BETA < d && d < 1) {
//         return a * (1 - std::abs(2 * d - 1 - BETA) / (1 - BETA));
//     } else {
//         return 0;
//     }
// }

// float Particle::particle_direction() {}
