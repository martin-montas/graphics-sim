#include <SDL2/SDL.h>
#include <complex>
#include <stdint.h>
#include <stdio.h>

// (0,0) ---------------------> x
// |
// |
// |
// |
// y

int WIDTH  = 800;
int HEIGHT = 600;
int size   = 25;

typedef struct {
    int x;
    int y;

} Speed;

void drawCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {

            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

void update_rect(SDL_Rect& ball, Speed& speed, int width, int height) {
    ball.x += speed.x;
    ball.y += speed.y;

    if ((ball.x + ball.w) >= width || (ball.x <= 0)) {
        speed.x *= -1;
    }
    if ((ball.y + ball.h) >= height || (ball.y <= 0)) {
        speed.y *= -1;
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window* window =
        SDL_CreateWindow("Bouncing Rect", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,
                         HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    SDL_StopTextInput();
    if (!window) {
        printf("Window Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        printf("Renderer Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    bool  quit = false;
    Speed speed;
    speed.x = 15;
    speed.y = 15;

    /* main render logic */
    SDL_Rect ball;
    ball.x = WIDTH / 2;
    ball.y = HEIGHT / 2;
    ball.h = size * 2;
    ball.w = size * 2;

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
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &ball);
        update_rect(ball, speed, width, height);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
