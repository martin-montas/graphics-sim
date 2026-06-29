#include "simulator.hpp"
#include "global.hpp"
#include "particle.hpp"
#include <random>

void Simulator::generate_particles() {
    std::random_device rd;
    gen = std::mt19937(rd());

    std::uniform_int_distribution<int> x_val(0, WIDTH);
    std::uniform_int_distribution<int> y_val(0, HEIGHT);
    std::uniform_int_distribution<int> color(0, 2);

    for (int i = 0; i < 1200; i++) {
        int x = x_val(gen);
        int y = y_val(gen);
        int r = color(gen);

        Particle* p = nullptr;

        if (r == 0) {
            p = new Particle(r, x, y, 255, 0, 0, renderer);
        } else if (r == 1) {
            p = new Particle(r, x, y, 0, 255, 0, renderer);
        } else if (r == 2) {
            p = new Particle(r, x, y, 0, 0, 255, renderer);
        }
        swarm.push_back(p);
    }
}

void Simulator::run_sim() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("Bouncing Rect", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_StopTextInput();
    if (!window) {
        printf("Window Error: %s\n", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("Renderer Error: %s\n", SDL_GetError());
        exit(1);
    }
    texture   = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                                  WIDTH, HEIGHT);
    bool quit = false;
    /* create particle swarm here */
    generate_particles();
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
            p->update(swarm);
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
            radii_matrix[i][j]        = radius(gen);
        }
    }
}
