/**
 * Name: player.c
 * Description: Player sprite initialization and movement handling
 * Author: Lucas B. Black
 */

#include "player.h"

void update_keys(struct Player* p, SDL_Scancode s, int n)
{
    switch (s)
    {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
            p->keys[0] = n;
            break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
            p->keys[1] = n;
            break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
            p->keys[2] = n;
            break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
            p->keys[3] = n;
            break;
        default:
            break;
    }
}

void update_movement(struct Player* p, int dt)
{
    p->rect.y = (int) p->y_pos;
    p->rect.x = (int) p->x_pos;

    if (p->keys[0])
        p->y_vel = (float) p->move_speed / dt;
    else if (p->keys[2])
        p->y_vel = (float) -p->move_speed / dt;
    else
        p->y_vel = 0;

    if (p->keys[1])
        p->x_vel = (float) p->move_speed / dt;
    else if (p->keys[3])
        p->x_vel = (float) -p->move_speed / dt;
    else
        p->x_vel = 0;

    p->x_pos -= p->x_vel;
    p->y_pos -= p->y_vel;
}

void update_boundry(struct Player* p, int window_width, int window_height)
{
    if (p->x_pos < 0) {
        p->x_pos = 0;
        p->x_vel = 0;
    } else if (p->x_pos + p->rect.w > window_width) {
        p->x_pos = window_width - p->rect.w;
    }
    if (p->y_pos < 0) {
        p->y_pos = 0;
        p->y_vel = 0;
    } else if (p->y_pos + p->rect.h > window_height) {
        p->y_pos = window_height - p->rect.h;
    }
}
