#include "boid.hpp"
#include "global.hpp"
#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

void Boid::rotate(float angle) {
    int   i = 0;
    float x;
    float y;
    float cx = (_ver[0].x + _ver[1].x + _ver[2].x) / 3.0f;
    float cy = (_ver[0].y + _ver[1].y + _ver[2].y) / 3.0f;
    while (i < 3) {
        x         = _ver[i].x - cx;
        y         = _ver[i].y - cy;
        float c   = cos(angle);
        float s   = sin(angle);
        _ver[i].x = x * c - y * s + cx;
        _ver[i].y = x * s + y * c + cy;
        i += 1;
    }
}

void Boid::update(std::vector<Boid*> swarm) {
    // this fomula calculates the radius of the flock
    // Formula: (max(abs(x_1 - x_2) , abs(y_1 - y_2)) <= 2;  2 being the radius

    // Vec2 direction = {_ver[0].y - _ver[1].y};

    // check_doundries();

    // for (auto b : swarm) {
    //     if (b != this) {
    //         // takes the
    //         if (max(abs(x - b->x), abs(y - b->y)) <= FLOCK_RADIUS) {
    //         }
    //     }
    // }
}

void Boid::check_doundries() {

    if (_ver[0].x <= 0) {
        _ver[0].x = WIDTH;
    } else if (_ver[1].x <= 0) {
        _ver[1].x = WIDTH;
    } else if (_ver[2].x <= 0) {
        _ver[2].x = WIDTH;

    } else if (_ver[0].y >= HEIGHT) {
        _ver[0].y = 0;
    } else if (_ver[1].y >= HEIGHT) {
        _ver[1].y = 0;
    } else if (_ver[2].y >= HEIGHT) {
        _ver[2].y = 0;

    } else if (_ver[0].x >= WIDTH) {
        _ver[0].y = 0;
    } else if (_ver[1].x >= WIDTH) {
        _ver[1].y = 0;
    } else if (_ver[2].x >= WIDTH) {
        _ver[2].y = 0;
    }
}

void Boid::draw() {
    SDL_RenderDrawLine(_rend, _ver[0].x, _ver[0].y, _ver[1].x, _ver[1].y);
    SDL_RenderDrawLine(_rend, _ver[1].x, _ver[1].y, _ver[2].x, _ver[2].y);
    SDL_RenderDrawLine(_rend, _ver[2].x, _ver[2].y, _ver[0].x, _ver[0].y);
}
