#include "simulator.hpp"
#include "particle.hpp"

Simulator::init_sdl() {

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

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                                WIDTH, HEIGHT);
}

void Simulator::run_sim() {
    init_sdl();
    bool quit = false;
    /* create particle swarm here */

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

        // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        // SDL_RenderFillRect(renderer, &ball);
        // update_rect(ball, speed, width, height);
        // SDL_RenderPresent(renderer);
    }
}

Simulator::~Simulator() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
