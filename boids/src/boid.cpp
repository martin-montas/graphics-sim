#include "boid.hpp"
#include "global.hpp"
#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

void Boid::update(std::vector<Boid*> swarm) {
    // this fomula calculates the radius of the flock
    // Formula: (max(abs(x_1 - x_2) , abs(y_1 - y_2)) <= 2;  2 being the radius

    Vec2  direction = {(float)_ver[0].x - _ver[1].x, (float)_ver[0].y - _ver[1].y};
    float distance  = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
    Vec2  norm      = {direction.x / distance, direction.y / distance};

    int i = 0;
    int x;
    int y;
    while (i <= 2) {
        x = _ver[i].x * cos(1) - _ver[i].y * sin(1);
        y = _ver[i].x * sin(1) + _ver[i].y * cos(1);

        _ver[i].x += x;
        _ver[i].y += y;

        i += 1;
    }

    check_doundries();

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
