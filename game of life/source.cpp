#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Grid.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;
const int scl = 1;
const int gridsize = 800;
void DoGen(Grid*, Grid*);
int ruleset[18]= { 0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0 };
int main(int argc, char* args[])
{
	for (int i = 0;i < 19;i++) { std::cout << "   " << i << ": " << ruleset[i]; }


	bool QUIT = false;
	bool Draw = true;
	int cursor_x = gridsize / 2;
	int cursor_y = gridsize / 2;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		QUIT = true;
	}

	window = SDL_CreateWindow("Game Of Life!", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		QUIT = true;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "renderer error: " << SDL_GetError();
		QUIT = true;
	}
	SDL_Event e;

	//Main loop
	Grid Life_grid(gridsize, gridsize, 8);
	Grid NLife_grid(gridsize, gridsize, 8);
	Life_grid.SetPalette(0, 0, 0, 0, 255);
	Life_grid.SetPalette(1, 255, 255, 255, 255);
	bool gen = false;


	if (false)
	{
		std::cout << "do";
		for (int i = 0;i < Life_grid.x;i++)
		{
			for (int o = 0;o < Life_grid.x;o++)
			{
				Life_grid.Cells[i][o] = rand() % 2;
			}
		}

	}

	Life_grid.DrawGrid(renderer, scl);

	while (!QUIT)
	{
		// Event check
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				QUIT = true;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					QUIT = true;
					break;
				case SDLK_w:
					if (cursor_y>0)
					cursor_y -= 1;
					break;
				case SDLK_a:
					if (cursor_x>0)
					cursor_x -= 1;
					break;
				case SDLK_s:
					if (cursor_y<Life_grid.y-1)
					cursor_y += 1;
					break;
				case SDLK_d:
					if (cursor_x<Life_grid.x-1)
					cursor_x += 1;
					break;
				case SDLK_f:
					Life_grid.Cells[cursor_x][cursor_y] = !Life_grid.Cells[cursor_x][cursor_y];
					break;

				case SDLK_g:
					gen = !gen;
					break;

				case SDLK_h:
					Draw = !Draw;
					break;
				case SDLK_r:
					for (int i = 1;i < Life_grid.x - 1;i++) {
						for (int o = 1;o < Life_grid.y - 1;o++) {
							Life_grid.Cells[i][o] = rand() % 2;
						}
					}
				}

			}
		}
		// End of events
		if (gen) {
			DoGen(&Life_grid, &NLife_grid);
		}
		if (Draw == true)
		{

			Life_grid.DrawGrid(renderer, scl);

		}
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 10);
		for (int i = 0;i < scl;i++) {
			for (int o = 0;o < scl;o++) {
				SDL_RenderDrawPoint(renderer, cursor_x*scl + i, cursor_y*scl + o);
			}
		}
		SDL_RenderPresent(renderer);


	}
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}

void DoGen(Grid* cgrid, Grid* ngrid)
{
	for (int i = 1;i < cgrid->x - 1;i++) {
		for (int o = 1;o < cgrid->y - 1;o++) {
			int	neighborcount = (cgrid->Cells[i][o]*10 )+ cgrid->Cells[i - 1][o - 1] + cgrid->Cells[i][o - 1] + cgrid->Cells[i + 1][o - 1] + cgrid->Cells[i - 1][o] + cgrid->Cells[i + 1][o] + cgrid->Cells[i - 1][o + 1] + cgrid->Cells[i][o + 1] + cgrid->Cells[i + 1][o + 1];
			ngrid->Cells[i][o] = ruleset[neighborcount];
		}
	}

	for (int i = 0;i < cgrid->x;i++) {
		for (int o = 0;o < cgrid->y;o++) {
			if (cgrid->Cells[i][o] != ngrid->Cells[i][o]) { cgrid->Cells[i][o] = ngrid->Cells[i][o]; cgrid->DrawCell(renderer, i, o, scl); }
		}
	}
}

