#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <unordered_map>
#include "../include/utils.hpp"

using std::tuple;
using std::vector;

// return the next board of the game given the current one
vector<tuple<int, int, bool>> next_generation(const vector<tuple<int, int, bool>> &current_status, int rows, int columns)
{
    vector<tuple<int, int, bool>> next_status;
    // for each cell count the friendly || enemy neighbors
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int alive_neighbors = 0;
            int friendly_neighbors = 0;
            int enemy_neighbors = 0;
            int cells_type = 0;                                                      // default = dead
            bool current_cell_status = std::get<2>(current_status[i * columns + j]); // dead or alive
            if (std::get<2>(current_status[i * columns + j]) == true)                // if the cell is alive then get the species
            {
                cells_type = std::get<3>(current_status[i * columns + j]); // get the species
            }
            else
            {
                cells_type = 0; // dead cell
            }

            // Check neighbors (for each cell check the neighbors cells)
            vector<int> enemy_neighbors_vect; // vector of enemy species
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {

                    int neighbor_row = i + x;
                    int neighbor_column = j + y;
                    // Check if neighbor is within bounds
                    if (neighbor_row >= 0 && neighbor_row < rows && neighbor_column >= 0 && neighbor_column < columns)
                    {
                        // Ignore current cell
                        if (x == 0 && y == 0)
                        {
                            continue;
                        }
                        // Count alive neighbors
                        if (std::get<2>(current_status[neighbor_row * columns + neighbor_column]))
                        {
                            alive_neighbors++;
                            if (std::get<3>(current_status[neighbor_row * columns + neighbor_column]) == cells_type) // if the cells is dead(species=0) then their is no friendly
                            {
                                friendly_neighbors++;
                            }
                            else
                            {
                                enemy_neighbors_vect.push_back(std::get<3>(current_status[neighbor_row * columns + neighbor_column]));
                                enemy_neighbors++;
                            }
                        }
                    }
                }
            }

            // Apply Game of Life rules
            if (current_cell_status && alive_neighbors < UNDER_POPULATION_CAP)
            {
                // underpopulation
                next_status.emplace_back(i, j, false, cells_type); // die
            }
            else if (current_cell_status && (alive_neighbors == UNDER_POPULATION_CAP || alive_neighbors == OVER_POPULATION_CAP))
            {
                // Survival
                next_status.emplace_back(i, j, true, cells_type); // stay alive
            }
            else if (current_cell_status && alive_neighbors > OVER_POPULATION_CAP)
            {
                // Overpopulation
                next_status.emplace_back(i, j, false, cells_type); // die
            }
            else if (!current_cell_status && alive_neighbors == REPRODUCTION_POPULATION_CAP)
            {
                // Reproduction
                // need to check witch neighbors is the more present
                next_status.emplace_back(i, j, true, mostFrequent(enemy_neighbors_vect));
            }
            else
            {
                // Stasis
                next_status.emplace_back(i, j, current_cell_status, cells_type);
            }
        }
    }
    return (next_status);
}

vector<tuple<int, int, bool>> start(std::string filename, int rows, int columns)
{
    vector<tuple<int, int, bool>> coordinates;

    // Initialize all coordinates to false (dead cells so no species)
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            coordinates.push_back(std::make_tuple(i, j, false));
        }
    }

    // Open file and set bool to true (1) for specified coordinates and set
    std::ifstream inputFile(filename);
    int x, y, kind;
    while (inputFile >> x >> y >> kind)
    {
        std::cout << kind << std::endl;
        int index = x * columns + y;
        coordinates[index] = std::make_tuple(x, y, true, kind);
    }
    inputFile.close();

    return coordinates;
}