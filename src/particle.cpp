#include "particle.hpp"

void Particle::particle_update(SDL_Renderer* renderer, int cx, int cy) {
    for (int y = -RADIUS; y <= RADIUS; y++) {
        for (int x = -RADIUS; x <= RADIUS; x++) {

            if (x * x + y * y <= RADIUS * RADIUS) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

void Particle::particle_distance(Particle p1, Particle p2) {
    float dx              = p1._x - p2._x;
    float dy              = p1._y - p2._y;
    float distance_square = dx * dx + dy * dy;

    if (distance_square < 1.0f * 1.0f) {
        // particles are closer than 1 unit
        // maybe use force function here
    }
}

float Particle::particle_force_handler(float d, int p1_kind, int p2_kind) {
    float a = attraction_matrix[p1_kind][p2_kind];

    if (d < BETA) {
        return d / BETA - 1;
    } else if (BETA < d && d < 1) {
        return a * (1 - std::abs(2 * d - 1 - BETA) / (1 - BETA));
    } else {
        return 0;
    }
}

float Particle::particle_direction() {}
