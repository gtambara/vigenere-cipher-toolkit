#ifndef ENCRIPT_H
#define ENCRIPT_H

#include <vector>
#include <algorithm> // for transform function
#include <string>
#include "auxiliary.h"

std::vector<char> encript(std::vector<char> key, std::vector<char> msg);

#endif