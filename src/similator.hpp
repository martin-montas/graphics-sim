#ifndef SRC_SIMULATOR_HPP_
#define SRC_SIMULATOR_HPP_

#include <vector>
#include "particle.hpp"

class Simulator {
    std::vector<Particle> particle; /* array of particles */

  public:
    void simulate();
};

#endif // !SRC_SIMULATOR_HPP_
