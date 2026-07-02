#include "simulator.hpp"
#include "boid.hpp"
#include "global.hpp"
#include <cstdlib>
#include <ctime>
#include <random>

// Triangle size configuration (identical for all)
const int TRIANGLE_WIDTH = 10;
const int TRIANGLE_HEIGHT = 10;

void Simulator::generate_boids() {

  for (int i = 0; i < 5; i++) {
    int x =
        static_cast<int>(rand() % (WIDTH - static_cast<int>(TRIANGLE_WIDTH)));
    int y =
        static_cast<int>(rand() % (HEIGHT - static_cast<int>(TRIANGLE_HEIGHT)));

    SDL_Point vertices[3];

    // Top vertex
    vertices[0] = {x + (TRIANGLE_WIDTH / 2), y};

    // Bottom Right vertex
    vertices[1] = {x + TRIANGLE_WIDTH, y + TRIANGLE_HEIGHT};

    // Bottom Left vertex
    vertices[2] = {x, y + TRIANGLE_HEIGHT};

    Boid *b = nullptr;
    // inline Boid(SDL_Renderer *rend, SDL_Point vertex[3]);

    b = new Boid(renderer, vertices[0], vertices[1], vertices[2]);

    swarm.push_back(b);
  }
}

void Simulator::run_sim() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL Error: %s\n", SDL_GetError());
    exit(1);
  }
  window = SDL_CreateWindow("Bouncing Rect", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  SDL_StopTextInput();
  if (!window) {
    printf("Window Error: %s\n", SDL_GetError());
    exit(1);
  }
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    printf("Renderer Error: %s\n", SDL_GetError());
    exit(1);
  }
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
  bool quit = false;
  /* create boid swarm here */
  generate_boids();
  set_tables();
  int width, height;
  SDL_GetRendererOutputSize(renderer, &width, &height);
  SDL_Event event;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = false;
        break;

      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          quit = true;
        }
        break;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    /* update here */
    for (auto p : swarm) {
      // p->update(swarm);
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
      p->draw();
    }
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Simulator::set_tables() {
  std::uniform_real_distribution<float> forces(0.3f, 1.0f);
  std::uniform_real_distribution<float> min_distance(60.0f, 85.0f);
  std::uniform_real_distribution<float> radius(70.0f, 250.0f);
  std::uniform_real_distribution<float> rrandom(100);

  for (int i = 0; i < _NUM_TYPE; i++) {
    for (int j = 0; j < _NUM_TYPE; j++) {
      force_matrix[i][j] = forces(gen);

      if (rrandom(gen) < 50) {
        force_matrix[i][j] *= -1;
      }
      min_distance_matrix[i][j] = min_distance(gen);
      radii_matrix[i][j] = radius(gen);
    }
  }
}
