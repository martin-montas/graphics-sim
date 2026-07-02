#ifndef SRC_SIMULATOR_HPP_
#define SRC_SIMULATOR_HPP_

#include <vector>
#include <algorithm>
#include <random>
#include "particle.hpp"

class Simulator {
    SDL_Window*   window;   /* pointer to sdl window */
    SDL_Renderer* renderer; /*pointer to sdl renderer */
    SDL_Texture*  texture;  /* pointer to sdl texture */
    std::mt19937  gen;      /* used for randomness */

    std::vector<Particle*> swarm; /* array of particles */
  public:
    void run_sim();
    void generate_particles();
    void set_tables();
};
#endif // !SRC_SIMULATOR_HPP_
