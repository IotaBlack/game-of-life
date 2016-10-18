#pragma once
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
class Grid
{

public:
	//Basic struc to track coords
	struct coord {
		int x;
		int y;
		int z;

		// Constructors
		coord() {
			x = 0;
			y = 0;
			z = 0;
		}
		coord(int nx,int ny) {
			x = nx;
			y = ny;
			z = 0;
		}
		coord(int nx, int ny, int nz) {
			x = nx;
			y = ny;
			z = nz;
		}

	};
	int** Cells;
	int x;
	int y;
	int* palette_r;
	int* palette_g;
	int* palette_b;
	int* palette_a;
	Grid(int,int,int);
	~Grid();
	void DrawGrid(SDL_Renderer*,int scale);
	void DrawCell(SDL_Renderer*, int i, int o, int scale);
	void SetPalette(int c, int r, int g, int b, int a);
};

