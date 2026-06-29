#include "particle.hpp"
#include <SDL2/SDL.h>

void Particle::update() {
    SDL_SetRenderDrawColor(_rend, _r, _g, _b, 255);
    SDL_RenderFillRect(_rend, &_rect);
}
void Particle::draw() {
    SDL_SetRenderDrawColor(_rend, _r, _g, _b, 255);
    SDL_Rect rect = {(int)_x, (int)_y, 5, 5};
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
