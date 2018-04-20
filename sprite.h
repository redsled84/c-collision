#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Sprite {
    char            sprite_path[50];
    SDL_Surface*    surface;
    SDL_Texture*    texture;
};

void load_surface(SDL_Renderer* rend, struct Sprite* s, SDL_Window* win);
void load_texture(SDL_Renderer* rend, struct Sprite* s, SDL_Window* win);
void free_surface(struct Sprite* s);
void destroy_texture(struct Sprite* s);

#endif
