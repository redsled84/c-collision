/**
 * Name: sprite.c
 * Description: Sprite helper functions
 * Author: Lucas B. Black
 */

#include "sprite.h"

void load_surface(SDL_Renderer* rend, struct Sprite* s, SDL_Window* win)
{
    s->surface = IMG_Load(s->sprite_path);
    if (!s->surface) {
        printf("Unable to create surface from path: %s\n", s->sprite_path);
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(1);
    }
}

void load_texture(SDL_Renderer* rend, struct Sprite* s, SDL_Window* win)
{
    s->texture = SDL_CreateTextureFromSurface(rend, s->surface);
    if(!s->texture) {
        printf("Unable to create texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(1);
    }
}

void free_surface(struct Sprite* s)
{
    SDL_FreeSurface(s->surface);
}

void destroy_texture(struct Sprite* s)
{
    SDL_DestroyTexture(s->texture);
}
