/**
 * @file life.c
 *
 * @author Maya Savino
 *
 * @date 05/03/2023
 *
 * Assignment: Final - Conway's Game of Life
 *
 * @brief game of life main function
 *
 * @bugs none
 *
 * @todo none
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h> /* for getopt */
#include "logic.h"
#include "sdl.h"

int main(int argc, char *argv[]){
	int width = 800;
	int height = 600;
	int sprite_size = 2; // valid values = 2, 4, 8, 16
	int ws;
	int hs;

	//int m = -999; //
	//int n = -999; //

    /* Colors; valid values = [0, 250]; default green */
	unsigned char red = 50;
	unsigned char green = 255;
	unsigned char blue = 100;
	
	srand(time(NULL));
	
	struct sdl_info_t sdl_info;

	unsigned char **A, **B;
	int i, j = 30;
	int x, y;
	char buf[1000];
	int c;
	char *edge;
	FILE *fp = NULL;
	
	if(argc == 1){
		printf("include -H for help\n");
		return 0;
	}

	/* Options */
	while((c = getopt(argc, argv, ":w:h:e:r:g:b:s:x:f:o:H")) != -1){
		switch(c){
		case 'w':
			if(atoi(optarg) > 129)
				width = atoi(optarg);
			else
				printf("Invalid input for -w; too small to function. Min: 128\n\tDefaulting to width 800\n");
			break;
		case 'h':
			if(atoi(optarg) > 128)
				height = atoi(optarg);
			else
				printf("Invalid input for -h; too small to function. Min: 128\n\tDefaulting to height 600\n");
			break;
		case 'e':
			edge = optarg;
			if(strcmp(edge, "hedge") != 0 && strcmp(edge, "torus") != 0 && strcmp(edge, "klein") != 0)
				printf("Invalid input for edge type -e; defaulting to hedge.\n"); // defaults during rendering
			break;
		case 'r':
			red = atoi(optarg);
			break;
		case 'g':
			green = atoi(optarg);
			break;
		case 'b':
			blue = atoi(optarg);
			break;
		case 's':
			sprite_size = atoi(optarg);
			if((sprite_size != 2) && (sprite_size != 4) && (sprite_size != 8) && (sprite_size != 16)){
				printf("Invalid argument for size of cell; valid arguments: 2, 4, 6, 18\n\tDefaulting to size 2.\n");
				sprite_size = 2;
			}
			break;
		case 'x':
			red = randomize_colors(red);
			green = randomize_colors(green);
			blue = randomize_colors(blue);
			//printf("colors: r = %d, g = %d, b = %d\n", red, green, blue); // for debugging
			break;
		case 'f':
			ws = (width / sprite_size);
			hs = (height / sprite_size);
			A = init_matrix(ws, hs);

			B = init_matrix(ws, hs);

			fp = fopen(optarg, "r");
			fgets(buf, 1000, fp);
			while(fgets(buf, 1000, fp) != NULL){
				sscanf(buf, "%d %d", &x, &y);
				A[i+x][j+y] = 1;
			}
			break;
		case 'o':
			sscanf(optarg, "%d,%d", &i, &j);
			break;
		case 'H':
            printf("\n");
			printf("-w   Width of display window; 640, 800, 1024, etc.\n");
            printf("\n");
			printf("-h   Height of display window; 480, 600, 768, etc.\n");
			printf("\n");
            printf("-e   Edge type; valid arguments: hedge, torus, klein\n");
			printf("\n");
            printf("-r   Red color value; integer between [0, 250]\n");
			printf("\n");
            printf("-g   Green color value; integer between [0, 250]\n");
			printf("\n");
            printf("-b   Blue color value; an integer between [0, 250]\n");
			printf("\n");
            printf("-s   Size of each cell; valid arguments are 2, 4, 8, or 16.\n");
			printf("     Values in range 2-6 work best for most laptop screens.\n");
			printf("\n");
			printf("-x   Randomize color (takes no arguments); may cause a segmentation fault, simply wait and re-run if so\n");
			printf("\n");
            printf("-f   Filename; life pattern in file format ./conwaylife/[filename]_106.lif\n");
			printf("\n");
            printf("-o   Initial x,y coordinate pattern found in the file; no space between x and y.\n");
			printf("\n");
			printf("-H   Help (non-standard, but h is already taken)\n");
			printf("\n");
            printf("Usage Examples:\n");
			printf("./life -w 640 -h 480 -s 4 -r 250 -g 100 -b 50 -e klein -o 77,59 -f ./conwaylife/b52bomber_106.lif\n"); // done
			printf("./life -w 1400 -h 1400 -s 16 -r 143 -g 10 -b 170 -e klein -o 21,39 -f ./conwaylife/ak47reaction_106.lif\n"); // done
			printf("./life -s 4 -r 62 -g 68 -b 255 -e torus -o 100,100 -f ./conwaylife/gosperglidergun_106.lif\n"); // done
			printf("./life -s 2 -r 100 -g 100 -b 100 -e torus -o 90,90 -f ./conwaylife/bigun_106.lif\n"); // done
			printf("./life -w 1000 -h 800 -s 2 -e hedge -o 221,347 -f ./conwaylife/bunnies11_106.lif\n"); // done
			printf("./life -w 1200 -h 920 -s 8 -x -e hedge -o 60,60 -f ./conwaylife/spacefiller1_106.lif ; -x sometimes seg faults, try re-running until it works\n"); // -x sometimes seg faults, remove it to test w/ default color
			printf("\n");
			return 0;
		}
	}
	fclose(fp);

    /* SDL setup (uses SDL2) */
	init_sdl_info(&sdl_info, width, height, sprite_size, red, green, blue);

	while(1){	
		
		/* change the  modulus value to slow the rendering */
		//if (SDL_GetTicks() % 999 == 0)
		//	sdl_test(&sdl_info, m, n);

		/* ------------ HEDGE ------------ */
		if(strcmp(edge, "hedge") == 0){
			sdl_render_life(&sdl_info, A);
			hedge(A, B, ws, hs);
			sdl_render_life(&sdl_info, B);
			hedge(B, A, ws, hs);
		}
		/* ------------ TORUS ------------ */
		else if(strcmp(edge, "torus") == 0){
			sdl_render_life(&sdl_info, A);
			torus(A, B, ws, hs);
			sdl_render_life(&sdl_info, B);
			torus(B, A, ws, hs);
		}
		/* ------------ KLEIN ------------ */
		else if(strcmp(edge, "klein") == 0){
			sdl_render_life(&sdl_info, A);
			klein(A, B, ws, hs);
			sdl_render_life(&sdl_info, B);
			klein(B, A, ws, hs);
		}
		/* DEFAULT to HEDGE if edge input is goofy */
		else{
			sdl_render_life(&sdl_info, A);
			hedge(A, B, ws, hs);
			sdl_render_life(&sdl_info, B);
			hedge(B, A, ws, hs);
		}
		
        /* Events */
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
                /* press escape to quit */
				if(event.key.keysym.sym == SDLK_ESCAPE){
					printf("You killed them :( play again.\n");
					return 0;
				}
				break;
			case SDL_QUIT:
				printf("You killed them :( play again.\n");
				return(0);
			}
		}
	}
	free_matrix(A, ws);
	free_matrix(B, ws);

	return 0;
}

int randomize_colors(int color){
	int value;
	value = (rand()*color) % 200;
	if(value < 0)
		value *= -1;
	value += 3;
	return value;
}