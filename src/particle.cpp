#include "particle.hpp"

void Particle::draw_particle(SDL_Renderer* renderer, int cx, int cy) {
    for (int y = -RADIUS; y <= RADIUS; y++) {
        for (int x = -RADIUS; x <= RADIUS; x++) {

            if (x * x + y * y <= RADIUS * RADIUS) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}
