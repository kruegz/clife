#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ** create(int width, int height)
{
	int **world;
	world = malloc(height * sizeof(int *));
	int min = 1;
	int max = 10;

	srand(time(NULL));

	for (int i = 0; i < height; ++i)
	{
		world[i] = malloc(width * sizeof(int));
	}

	for(int x = 1; x < (width - 1); x++) 
	{
	    for(int y = 1; y < (height - 1); y++)
	    {
	    	int r = max + rand() / (RAND_MAX / (min - max + 1) + 1);

	    	if (r <= 5)
	    	{
	    		world[y][x] = 1;
	    	}
	    	else
	    	{
	    		world[y][x] = 0;
	    	}
	    }
	}

	return world;
}

void render(int **world, int width, int height)
{
	system("clear");

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (world[i][j] == 1)
			{
				printf("%s", "X");
			}
			else
			{
				printf("%s", " ");
			}
		}
		printf("\n");
	}
}

void freeWorld(int **world, int height)
{
	for (int i = 0; i < height; i++)
	{
		free(world[i]);
	}
	free(world);
}

void evolve(int **world, int **newworld, int width, int height)
{
	for (int y = 1; y < (height - 1); ++y)
	{
		for (int x = 0; x < (width - 1); ++x)
		{
			int is_alive = world[y][x];
			int neighbours = 0;
			neighbours = world[y-1][x-1] + world[y-1][x] + world[y-1][x+1] + world[y][x-1] + world[y][x+1] + world[y+1][x-1] + world[y+1][x] + world[y+1][x+1];

			if (is_alive == 1)
			{
				if (neighbours < 2)
				{
					newworld[y][x] = 0;
				}
				else if (neighbours == 2 | neighbours == 3)
				{
					newworld[y][x] = 1;
				}
				else if (neighbours > 3)
				{
					newworld[y][x] = 0;
				}
			}
			else
			{
				if (neighbours == 3)
				{
					newworld[y][x] = 1;
				}
				else
				{
					newworld[y][x] = 0;
				}
			}
		}
	}
}

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

int main(int argc, char *argv[])
{
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int generations = atoi(argv[3]);

	int **world = create(width, height);
	int **newworld = create(width, height);

	for (int i = 0; i < generations; ++i)
	{
		evolve(world, newworld, width, height);
		render(newworld, width, height);

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				world[y][x] = newworld[y][x];
			}
		}

		delay(100);
	}

	freeWorld(world, height);
	freeWorld(newworld, height);

	return 0;
}