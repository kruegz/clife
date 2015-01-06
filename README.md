clife
=====

Conway's Game of Life written in C.

Usage:
-----------

In it's current state, the simulation creates a randomly populated world of a desired size
and evolves the world over a certain number of generations.

To run the simulation, compile and run the program with the following arguments:
- Width of the world in characters.
- Height of the world in characters.
- Number of generations.
- Percentage of random live cells.
- Delay period in milliseconds.

For example, the following command:

<code>./clife 100 50 100 15 100</code>

will produce a simulation that is 100 characters wide, 50 characters tall, run it over 100
generations, will initially populate the world with approximately 15% living cells, and
will delay 100 milliseconds between rendering each generation.
