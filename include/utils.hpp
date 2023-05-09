#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <tuple>
#include <string>

std::tuple<int, std::tuple<int, int>, std::vector<std::tuple<int, int, bool>>> next_generation(const std::vector<std::tuple<int, int, bool>> &current_status, tuple<int, int> ant_pos, int ant_angle, int rows, int columns);
std::vector<std::tuple<int, int, bool>> start(int rows, int columns);
#endif
