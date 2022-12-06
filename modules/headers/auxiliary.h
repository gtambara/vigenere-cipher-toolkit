/**
 * @file auxiliary.h
 * @brief Auxiliary functions for encription/decription related code header.
 *
 */
#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <iostream>
#include <fstream>
#include <iterator>
#include <stdio.h>
#include <vector>
#include <algorithm> // for transform function
#include <string>

#define TAM_ALFABETO 26           ///< Size of the Alphabet
#define FILES_FOLDER "workspace/" ///< Name of the folder for file handling

std::vector<char> extendKey(std::vector<char> key, const int newSize);
void toLower(std::string *text);
std::vector<char> formatText(std::vector<char> text);
void outputText(std::vector<char> text, std::string filename);
std::string inputText(std::string filename);
int trueSize(std::vector<char> msg);

#endif