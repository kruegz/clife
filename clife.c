#include <stdio.h>		// printf, sizeof
#include <stdlib.h>		// atoi, free, malloc, system, rand, srand
#include <time.h>		// time, clock

/*
	Function: create
	Creates a two dimenstional array and populates it with a random amount of 1's and 0's.
	Takes parameters width and height of the 2d array and a randomness value.
	Returns a double pointer to the created array.
*/

int ** create(int width, int height, int randomness)
{
	// Create and allocate the heap memory required for each row of the array.
	int **world;
	world = (int **)malloc(height * sizeof(int *));

	// Set minimum and maximum values for the random number generator.
	int min = -1;
	int max = 100;

	srand(time(NULL));

	// Allocate memory for each column in the 2d array.
	for (int i = 0; i < height; ++i)
	{
		world[i] = (int *)malloc(width * sizeof(int));
	}

	// Step through each position in the 2d array and generate a random number.
	for(int x = 1; x < (width - 1); x++) 
	{
	    for(int y = 1; y < (height - 1); y++)
	    {
	    	int r = max + rand() / (RAND_MAX / (min - max + 1) + 1);
	    	printf("%d ", r);

	    	// Assign either a 1 or a 0 to that position depending on the random number and the desired randomness.
	    	if (r <= randomness)
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

/*
	Function: render
	Displays a 2d array as a world with living and dead cells.
	Takes a double pointer to the world, the width, and the height of the world as parameters.
	Returns nothing.
*/

void render(int **world, int width, int height)
{
	// Clears the screen.
	system("clear");

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			// If the cell is alive (1), print an "X", else print a space.
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

/*
	Function: freeWorld
	Free the heap memory associated with the world.
	Takes parameters double pointer to the world and the height (number of rows).
	Returns nothing.
*/

void freeWorld(int **world, int height)
{
	// First free the memory associated with each array within the large array.
	for (int i = 0; i < height; i++)
	{
		free(world[i]);
	}

	// Then free the memory from the mother array.
	free(world);
}

/*
	Function: evolve
	Constructs the next generation based on the position of living and dead cells.
	Takes parameters double pointer to the current world, double pointer to the next gen world, the width, and the height.
	Returns nothing.
*/

void evolve(int **world, int **newworld, int width, int height)
{
	// Step through each cell of the current gen world.
	for (int y = 1; y < (height - 1); ++y)
	{
		for (int x = 0; x < (width - 1); ++x)
		{
			// Deterimine if the current cell is alive (1).
			int is_alive = world[y][x];

			// Find the number of neighbors in direct contact with the cell.
			int neighbours = 0;
			neighbours = world[y-1][x-1] + world[y-1][x] + world[y-1][x+1] + world[y][x-1] + world[y][x+1] + world[y+1][x-1] + world[y+1][x] + world[y+1][x+1];

			// Deterimine the future for the cell based on it's state and its number of living neighbors,
			// and apply that state to the same position in the next generation.
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

/*
	Function: delay
	A simple function to delay time.
	Takes an amount of milliseconds as a parameter.
	Returns nothing.
*/

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    // Determines how long the pause should be as an amount of processor ticks.
    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();

    // Loops until the correct amout of processor ticks has been achieved.
    while( (now-then) < pause )
        now = clock();
}

/*
	Function: main
	Runs the game for a certain number of generations then frees all memory.
	Takes standard parameters argc and argv.
	Returns a 0.
*/

int main(int argc, char *argv[])
{
	// Converts the console arguments into intergers for width and height of the world
	// as well as the desired number of generations, randomness percentage, and desired 
	// delay between genenerations in milliseconds.
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int generations = atoi(argv[3]);
	int randomness = atoi(argv[4]);
	int dlay = atoi(argv[5]);

	// Creates the world and the next gen world using function create().
	int **world = create(width, height, randomness);
	int **newworld = create(width, height, randomness);

	// Runs through the desired number of generations.
	for (int i = 0; i < generations; ++i)
	{	
		// Evolves and renders the generation.
		evolve(world, newworld, width, height);
		render(newworld, width, height);

		// Sets the current gen equal to the next gen to prepare for the next evolution.
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				world[y][x] = newworld[y][x];
			}
		}

		// Delays a desired period of time.
		delay(dlay);
	}

	// Frees the heap memory associated with each of the 2d array worlds.
	freeWorld(world, height);
	freeWorld(newworld, height);

	return 0;
}