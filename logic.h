/**
 * @file logic.c
 *
 * @author Maya Savino
 *
 * @date 05/03/2023
 *
 * Assignment: Final - Conway's Game of Life
 *
 * @brief header file for logic.c; initializes functions
 *
 * @bugs none
 *
 * @todo none
 * 
 * @param init_matrix initializes the matrix
 * @param free_matrix frees the matrix
 * @param hedge hedge implementation
 * @param torus torus implementation
 * @param klein klein implementation
 * @param randomize_colors randomizes colors
 */

#ifndef GOLFUNC
#define GOLFUNC

unsigned char **init_matrix(int rows, int cols);
void free_matrix(unsigned char **A, int rows);
void hedge(unsigned char **A, unsigned char **B, int rows, int cols);
void torus(unsigned char **A, unsigned char **B, int rows, int cols);
void klein(unsigned char **A, unsigned char **B, int rows, int cols);
int randomize_colors(int color);

#endif