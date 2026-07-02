#ifndef SRC_SIMULATOR_HPP_
#define SRC_SIMULATOR_HPP_

#include "boid.hpp"
#include <algorithm>
#include <random>
#include <vector>

class Simulator {
  SDL_Window *window;     /* pointer to sdl window */
  SDL_Renderer *renderer; /*pointer to sdl renderer */
  SDL_Texture *texture;   /* pointer to sdl texture */
  std::mt19937 gen;       /* used for randomness */

  std::vector<Boid *> swarm; /* array of boid */
public:
  void run_sim();
  void generate_boids();
  void set_tables();
};
#endif // !SRC_SIMULATOR_HPP_
