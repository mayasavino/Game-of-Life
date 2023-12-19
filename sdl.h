/**
 * @file sdl.h
 *
 * @author Maya Savino
 *
 * @date 05/03/2023
 *
 * Assignment: Final - Conway's Game of Life
 *
 * @brief logic for game of life
 *
 * @bugs none
 *
 * @todo none
 * 
 * @param init_sdl_info initialize with given info
 * @param sdl_render_life render game of life
 * @param sdl_test for testing
 */

#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>

struct color_t {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned int value;
};

struct sdl_info_t {
 	SDL_Surface *screen;
	SDL_Window *window;
        SDL_Renderer *renderer; 
	SDL_Texture *texture;
        struct color_t color; 
        int width;
        int height;
        int sprite_size; 
};

void init_sdl_info(struct sdl_info_t *sdl_info, int width, int height, int sprite_size, unsigned int red, unsigned int green, unsigned int blue);
void sdl_render_life(struct sdl_info_t *sdl_info, unsigned char **life);
void sdl_test(struct sdl_info_t *sdl_info, int m, int n);

#endif