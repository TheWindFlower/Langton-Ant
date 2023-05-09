#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <ctime>
#include <unordered_map>
#include "../include/utils.hpp"

using std::tuple;
using std::vector;

// return the next board of the game given the current one
tuple<int, tuple<int, int>, vector<tuple<int, int, bool>>> next_generation(const vector<tuple<int, int, bool>> &current_status, tuple<int, int> ant_pos, int ant_angle, int rows, int columns)
{
    vector<tuple<int, int, bool>> next_status = current_status;
    int x_pos, y_pos;
    int angle = ant_angle;
    tuple<int, int> next_ant_pos;
    std::tie(x_pos, y_pos) = ant_pos;
    bool case_color = std::get<2>(current_status[x_pos * columns + y_pos]);

    if (case_color)
    {
        // if the case is black
        // change the color of the case
        next_status.emplace_back(x_pos, y_pos, false);
        // set the next angle
        if (angle >= 90)
        {
            angle -= 90;
        }
        else
        {
            angle = 270;
        }
        // move the ant in the given angle
        if (angle == 0)
        {
            next_ant_pos = std::make_tuple(x_pos, y_pos - 1);
        }
        else if (angle == 90)
        {
            next_ant_pos = std::make_tuple(x_pos + 1, y_pos);
        }
        else if (angle == 180)
        {
            next_ant_pos = std::make_tuple(x_pos, y_pos - 1);
        }
        else if (angle == 270)
        {
            next_ant_pos = std::make_tuple(x_pos - 1, y_pos);
        }
    }
    return std::make_tuple(angle, next_ant_pos, next_status);
}

vector<tuple<int, int, bool>> start(int rows, int columns)
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
    return coordinates;
}