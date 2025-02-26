#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 3
#define COLS 4
#define TILE_COUNT 6

/*
Input these as CLAs : {1,2},{1,2},{2,1},{1,2},{2,1},{1,2}
*/

/*

This code generates the solution for Level 4.
It could theoretically be modified for any level,
though it doesn't have rotational functionality yet.

The solution :
{0,0,1,1}
{4,5,5,2}
{4,3,3,2}

*/

typedef struct Tile
{

    int n;
    int m;

} Tile;

bool validate_adjacency(int grid[ROWS][COLS], int adjacencyMatrix[TILE_COUNT][TILE_COUNT]);

bool can_place(int grid[ROWS][COLS], int r, int c, Tile tile);

void remove_tile(int grid[ROWS][COLS], int r, int c, Tile tile);

void place_tile(int grid[ROWS][COLS], int r, int c, Tile tile, int tileNum);

bool solve(int grid[ROWS][COLS], Tile tiles[], int tileIndex, int adjacencyMatrix[TILE_COUNT][TILE_COUNT]);

void print_grid(int grid[ROWS][COLS]);

int main(int argc, char **argv)
{

    int grid[ROWS][COLS] = {
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1}};

    Tile *tiles = (Tile *)malloc(sizeof(Tile) * TILE_COUNT);

    // Tile Array : {1,2},{1,2},{2,1},{1,2},{2,1},{1,2}

    for (int i = 0; i < 6; i++)
    {

        tiles[i].m = (argv[i + 1][0] - '0');
        tiles[i].n = (argv[i + 1][1] - '0');
    }

    int adjacencyMatrix[TILE_COUNT][TILE_COUNT] = {
        {0, 1, 0, 0, 1, 1},
        {1, 0, 1, 0, 0, 1},
        {0, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 1},
        {1, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1},
    };

    // Validation function test.

    // int solution[3][4] = {
    //     {0,0,1,1},
    //     {4,5,5,2},
    //     {4,3,3,2}
    // };

    // if(validate_adjacency(solution, adjacencyMatrix)) {printf("Adjacency preserved.");} else {printf("Not valid.");}

    time_t start, end;

    start = clock();

    if (!solve(grid, tiles, 0, adjacencyMatrix))
    {
        printf("No valid solution found.\n");
    }

    end = clock();

    printf("Time taken : %lf", (double)(end-start)*(1000)/CLOCKS_PER_SEC);
    return 0;
}

bool validate_adjacency(int grid[ROWS][COLS], int adjacencyMatrix[TILE_COUNT][TILE_COUNT])
{

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < ROWS; i++)
    {

        for (int j = 0; j < COLS; j++)
        {

            int node = grid[i][j];

            for (int d = 0; d < 4; d++)
            {

                int ni = i + directions[d][0];
                int nj = j + directions[d][1];

                if ((ni >= 0) && (nj >= 0) && (ni < 3) && (nj < 4))
                {

                    int neighbour = grid[ni][nj];

                    if (adjacencyMatrix[node][neighbour] == 0 && neighbour != node)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool can_place(int grid[ROWS][COLS], int r, int c, Tile tile)
{
    if (r + tile.m > ROWS || c + tile.n > COLS)
        return false;

    for (int i = 0; i < tile.m; i++)
    {
        for (int j = 0; j < tile.n; j++)
        {
            if (grid[r + i][c + j] != -1)
                return false;
        }
    }
    return true;
}

void place_tile(int grid[ROWS][COLS], int r, int c, Tile tile, int tileNum)
{

    for (int i = 0; i < tile.m; i++)
    {

        for (int j = 0; j < tile.n; j++)
        {

            grid[r + i][j + c] = tileNum;
        }
    }
}

void remove_tile(int grid[ROWS][COLS], int r, int c, Tile tile)
{

    for (int i = 0; i < tile.m; i++)
    {

        for (int j = 0; j < tile.n; j++)
        {

            grid[r + i][j + c] = -1;
        }
    }
}

bool solve(int grid[ROWS][COLS], Tile tiles[], int tileIndex, int adjacencyMatrix[TILE_COUNT][TILE_COUNT])
{
    if (tileIndex == TILE_COUNT)
    {
        if (validate_adjacency(grid, adjacencyMatrix))
        {
            print_grid(grid);
            return true;
        }
        return false;
    }

    Tile tile = tiles[tileIndex];
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (can_place(grid, r, c, tile))
            {
                place_tile(grid, r, c, tile, tileIndex);

                // print_grid(grid); Debugging k liye

                if (solve(grid, tiles, tileIndex + 1, adjacencyMatrix))
                {
                    return true;
                }
                remove_tile(grid, r, c, tile);
            }
        }
    }
    return false;
}

void print_grid(int grid[ROWS][COLS])
{

    for (int i = 0; i < ROWS; i++)
    {

        for (int j = 0; j < COLS; j++)
        {

            printf("%d ", grid[i][j]);
        }

        printf("\n");
    }
}
