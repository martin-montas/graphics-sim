#ifndef SRC_SIMULATOR_HPP_
#define SRC_SIMULATOR_HPP_

#include <vector>
#include "particle.hpp"

#define WIDTH  800
#define HEIGHT 600

class Simulator {
    std::vector<Particle> swarm; /* array of particles */

    SDL_Window*   window;
    SDL_Renderer* renderer;
    SDL_Texture*  texture;

  public:
    void run_sim();
    void init_sdl();
};
#endif // !SRC_SIMULATOR_HPP_
