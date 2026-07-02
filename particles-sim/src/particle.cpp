#include "particle.hpp"
#include "global.hpp"
#include <SDL2/SDL.h>
#include <cmath>
#include <cstdio>
#include <vector>

float map(float value, float in_min, float in_max, float out_min,
          float out_max) {
  return out_min + (value - in_min) * (out_max - out_min) / (in_max - in_min);
}

float mass = 0.01f;
float dt = 0.06f;

void normalize(float distance, Vec2 &v) {
  v.x /= distance;
  v.y /= distance;
}

void Particle::update(std::vector<Particle *> &swarm) {
  Vec2 velocity;
  velocity.x = 0;
  velocity.y = 0;

  Vec2 total_force;
  total_force.y = 0;
  total_force.x = 0;

  Vec2 acc;
  acc.x = 0;
  acc.y = 0;

  Vec2 delta;
  delta.x = 0;
  delta.y = 0;

  for (auto p : swarm) {
    if (p != this) {
      // find direction
      delta.x = p->_x - _x;
      delta.y = p->_y - _y;

      // calcualte the distance of the vector
      float distance = std::sqrt((delta.x * delta.x) + (delta.y * delta.y));

      // make the delta vector a uni vector
      normalize(distance, delta);

      if (distance < min_distance_matrix[_kind][p->_kind]) {
        float penetration = min_distance_matrix[_kind][p->_kind] - distance;
        float _force = K * penetration;

        total_force.x += -(_force * (delta.x));
        total_force.y += -(_force * (delta.y));
      } else if (distance < radii_matrix[_kind][p->_kind]) {

        total_force.x += force_matrix[_kind][p->_kind] * delta.x;
        total_force.y += force_matrix[_kind][p->_kind] * delta.y;
      }
    }
  }
  acc.x += total_force.x / mass;
  acc.y += total_force.y / mass;

  velocity.x += acc.x * dt;
  velocity.y += acc.y * dt;
  _x += velocity.x * dt;
  _y += velocity.y * dt;

  if (_x <= 0)
    _x += WIDTH;
  else if (_y < 0)
    _y += HEIGHT;

  else if (_x >= WIDTH)
    _x += 0;
  else if (_y >= HEIGHT)
    _y += 0;
}

void Particle::draw() {
  SDL_SetRenderDrawColor(_rend, _r, _g, _b, 255);
  SDL_Rect rect = {(int)_x, (int)_y, PARTICLE_WIDTH, PARTICLE_HEIGHT};
  SDL_RenderFillRect(_rend, &rect);
}
