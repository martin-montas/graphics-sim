#include "particle.hpp"
#include <SDL2/SDL.h>

void Particle::drawCircle(SDL_Renderer* renderer, int cx, int cy, int RADIUS) {
    for (int y = -RADIUS; y <= RADIUS; y++) {
        for (int x = -RADIUS; x <= RADIUS; x++) {

            if (x * x + y * y <= RADIUS * RADIUS) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}
