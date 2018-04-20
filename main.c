/**
 * Name: main.c
 * Description: Initialize SDL modules and connect game mechanics
 * Author: Lucas B. Black
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "player.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480
#define FPS           60

void initialize_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
}

SDL_Window* get_window(const char *title)
{
    SDL_Window* win = SDL_CreateWindow(title,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,
                                       SDL_WINDOW_OPENGL);

    if (!win) {
        printf("Unable to create window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    return win;
}

SDL_Renderer* get_renderer(SDL_Window* win)
{
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend) {
        printf("Unable to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(1);
    }
    return rend;
}

void handle_keys(SDL_Event e, struct Player* player_ptr, int *is_running)
{
    if (e.type == SDL_KEYDOWN) {
        update_keys(player_ptr, e.key.keysym.scancode, 1);
        switch (e.key.keysym.scancode)
        {
        case SDL_SCANCODE_ESCAPE:
            *is_running = 0;
            break;
        default:
            break;
        }
    } else if (e.type == SDL_KEYUP) {
        update_keys(player_ptr, e.key.keysym.scancode, 0);
    }
}

void load_sprite(struct Sprite* sprite, SDL_Renderer* rend, SDL_Window* win)
{
    load_surface(rend, sprite, win);
    load_texture(rend, sprite, win);

    free_surface(sprite);
}

void set_rect_dimensions(SDL_Rect* rect, SDL_Texture* texture)
{
    SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
    rect->w /= 4;
    rect->h /= 4;
}

int main(void)
{
    srand(time(NULL));

    initialize_sdl();
    SDL_Window* win = get_window("Ambitious");
    SDL_Renderer* rend = get_renderer(win);

    printf("Successfully initialized SDL\n");

    // Player initialization
    SDL_Rect rect = {};
    struct Sprite player_sprite = {"FF0000.png", NULL, NULL};
    struct Player player = { {0, 0, 0, 0}, 350, rect, &player_sprite, 0, 0, 0, 0 };

    load_sprite(player.sprite, rend, win);
    set_rect_dimensions(&player.rect, player_sprite.texture);

    // Game loop variables
    int is_running = 1;
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    // Begin game loop
    while (is_running) {
        // Handle events
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = 0;
            } else {
                handle_keys(event, &player, &is_running);
            }
        }

        // Draw entities
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, player_sprite.texture, NULL, &player.rect);
        SDL_RenderPresent(rend);

        // Update entities
        update_movement(&player, FPS);
        update_boundry(&player, WINDOW_WIDTH, WINDOW_HEIGHT);

        // Move to next frame and update events
        SDL_PumpEvents();
        SDL_Delay(1000 / FPS);
    }

    destroy_texture(&player_sprite);

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
}
