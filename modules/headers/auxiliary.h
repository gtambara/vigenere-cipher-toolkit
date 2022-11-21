#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <iostream>
#include <fstream>
#include <iterator>
#include <stdio.h>
#include <vector>
#include <algorithm> // for transform function
#include <string>

#define TAM_ALFABETO 26
#define FILES_FOLDER "workspace/"

std::vector<char> extendKey(std::vector<char> key, const int newSize);
void toLower(std::string *text);
void outputText(std::vector<char> text, std::string filename);
std::string inputText(std::string filename);

#endif