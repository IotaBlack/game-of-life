#include "Grid.h"
#include <stdlib.h>
#include <iostream>


Grid::Grid(int a,int b,int s)
{
	x = a;
	y = b;
	Cells = (int**) malloc(x*s);
	for (int i = 0;i < x;i++)
	{
		Cells[i] = (int*)malloc(y*s);
	}
	for (int i = 0;i < x;i++)
	{
		for (int o = 0;o < y;o++)
		{
			Cells[i][o] = 0;
		}
	}
	palette_r = (int*)malloc(256*s);
	palette_g = (int*)malloc(256*s);
	palette_b = (int*)malloc(256*s);
	palette_a = (int*)malloc(256*s);
	for (int i = 0;i < 256;i++)
	{
		SetPalette(i, 255, 255, 255, 0);
	}
}


Grid::~Grid()
{
	free(Grid::Cells);
	free(Grid::palette_r);
	free(Grid::palette_g);
	free(Grid::palette_b);
	free(Grid::palette_a);
}


void Grid::DrawGrid(SDL_Renderer* renderer,int scale)
{
	for (int i = 0;i < x;i++)
	{
		for (int o = 0;o < x;o++)
		{
			int val = floor(Cells[i][o]);

			SDL_SetRenderDrawColor(renderer, palette_r[val], palette_g[val], palette_b[val], palette_a[val]);
			for (int ioff = 0;ioff < scale;ioff++) {
				for (int ooff = 0;ooff < scale;ooff++) {
					SDL_RenderDrawPoint(renderer, i*scale+ioff, o*scale+ooff);
				}
			}
			
		}
	}
}

void Grid::DrawCell(SDL_Renderer* renderer, int x, int y, int scale)
{
	int val = floor(Cells[x][y]);
	SDL_SetRenderDrawColor(renderer, palette_r[val], palette_g[val], palette_b[val], palette_a[val]);
	for (int xoff = 0;xoff < scale;xoff++) {
		for (int yoff = 0;yoff < scale;yoff++) {
			SDL_RenderDrawPoint(renderer, x*scale + xoff, y*scale + yoff);
		}
	}
}

void Grid::SetPalette(int c, int r, int g, int b, int a)
{	
	palette_r[c] = r;
	palette_g[c] = g;
	palette_b[c] = b;
	palette_a[c] = a;
}
