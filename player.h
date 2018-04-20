#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include <SDL2/SDL.h>

struct Player {
    int              keys[4];
    int              move_speed;
    SDL_Rect         rect;
    struct Sprite*   sprite;
    float            x_pos, x_vel, y_pos, y_vel;
};

void update_keys(struct Player* p, SDL_Scancode s, int n);
void update_movement(struct Player* p, int dt);
void update_boundry(struct Player* p, int window_width, int window_height);

#endif
