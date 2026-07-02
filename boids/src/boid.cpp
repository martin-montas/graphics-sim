#include "boid.hpp"
#include "global.hpp"
#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

void Boid::update(std::vector<Boid *> swarm) {
  // this fomula calculates the radius of the flock
  // Formula: (max(abs(x_1 - x_2) , abs(y_1 - y_2)) <= 2;  2 being the radius
  for (auto b : swarm) {
    if (b != this) {
      if (max(abs(x - b->x), abs(y - b->y)) <= 4) {
      }
    }
  }
}

void Boid::draw() {

  SDL_RenderDrawLine(_rend, _ver[0].x, _ver[0].y, _ver[1].x, _ver[1].y);
  SDL_RenderDrawLine(_rend, _ver[1].x, _ver[1].y, _ver[2].x, _ver[2].y);
  SDL_RenderDrawLine(_rend, _ver[2].x, _ver[2].y, _ver[0].x, _ver[0].y);
}
