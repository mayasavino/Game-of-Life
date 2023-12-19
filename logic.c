#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"

/**
 * @file life.c
 *
 * @author Maya Savino
 *
 * @date 05/03/2023
 *
 * Assignment: Final - Conway's Game of Life
 *
 * @brief logic for game of life
 *
 * @bugs -x option sometimes induces a seg fault, typecasing issue
 *
 * @todo fix -x option (for randomizing colors)
 * 
 * @param init_matrix initializes the matrix
 * @param free_matrix frees the matrix
 * @param hedge hedge implementation
 * @param torus torus implementation
 * @param klein klein implementation
 * @param randomize_colors randomizes colors
 */

unsigned char **init_matrix(int rows, int cols)
{
	int i, j;
	unsigned char **a;

	a = malloc(rows * sizeof(int *));
	if(!a)
		return NULL;
	for(i = 0; i < rows; i++){
		a[i] = malloc(cols * sizeof(int));
		if(!a[i]){
			for (j = 0; j < i; j++)
				free(a[j]);
			free(a);
			return NULL;
		}
	}

	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			a[i][j] = 0;
		}
	}

	return a;
}

void free_matrix(unsigned char **A, int rows){
	int i;
	for(i = 0; i < rows; i++)
		free(A[i]);
	free(A);
}

void hedge(unsigned char **A, unsigned char **B, int rows, int cols){
	int i, j, x, y, chk;
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			chk = 0;
			for(x = -1; x <= 1; x++){
				for(y = -1; y <= 1; y++){
					if((x+i) < rows && (y+j) < cols) 
						if((x+i) >= 0 && (y+j) >= 0)
							if(A[x+i][y+j] == 1)
								chk += 1;
				}
			}
			if(A[i][j] == 1){
				chk -= 1;
				if(chk < 2)
					B[i][j] = 0;
				else if(chk > 3)
					B[i][j] = 0;
				else
					B[i][j] = 1;
			} 
			else{
				B[i][j] = 0;
				if(chk == 3)
					B[i][j] = 1;
			}
		}
	}
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++)
			A[i][j] = 0;
	}
	
}

void torus(unsigned char **A, unsigned char **B, int rows, int cols){
	int i, j, x, y, chk, tmp1, tmp2;
	// Check all cells
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			chk = 0;
			// Check in on the cell's neighbors
			for(x = -1; x <= 1; x++){
				for(y = -1; y <= 1; y++){
					tmp1 = ((x+i) % rows);
					tmp2 = ((y+j) % cols);
					if (tmp1 < 0)
						tmp1 = rows - 1;
					if (tmp2 < 0)
						tmp2 = cols - 1;
					if(A[tmp1][tmp2] == 1)
						chk += 1;
				}
			}
			if(A[i][j] == 1){
				chk -= 1;
				if(chk < 2)
					B[i][j] = 0;
				else if(chk > 3)
					B[i][j] = 0;
				else
					B[i][j] = 1;
			} 
			else{
				B[i][j] = 0;
				if(chk == 3)
					B[i][j] = 1;
			}
		}
	}
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++)
			A[i][j] = 0;
	}
}

void klein(unsigned char **A, unsigned char **B, int rows, int cols){
	int i, j, x, y, chk, tmp1, tmp2;
	// Check all cells
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			chk = 0;
			// Check in on the cell's neighbors
			for(x = -1; x <= 1; x++){
				for(y = -1; y <= 1; y++){
					tmp2 = ((y+j) % cols);
					tmp1 = x + i;
					if(tmp2 < 0)
						tmp2 = cols - 1;
					if(tmp1 < 0){
						tmp2 = cols - tmp2 - 1;
						tmp1 = rows - 1;
					} 
					else if(tmp1 >= rows){
						tmp2 = cols - tmp2 - 1;
						tmp1 = ((x+i) % rows);						
					}
					if(A[tmp1][tmp2] == 1)
						chk += 1;
				}
			}
			if(A[i][j] == 1){
				chk -= 1;
				if(chk < 2){
					B[i][j] = 0;
				} 
				else if(chk > 3){
					B[i][j] = 0;
				} 
				else{
					B[i][j] = 1;
				}
			} 
			else{
				B[i][j] = 0;
				if (chk == 3) {
					B[i][j] = 1;
				}
			}
		}
	}
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++)
			A[i][j] = 0;
	}
}
