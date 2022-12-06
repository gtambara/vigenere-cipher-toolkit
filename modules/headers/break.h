/**
 * @file break.h
 * @brief Cipher breaking related code.
 *
 */
#ifndef BREAK_H
#define BREAK_H

#define MIN_PARTICLE_SIZE 3   // minimum size for substrings to be analyzed
#define ADVANCED_STRING_CUT 1 // 1 for more adquate substring repetition cuts but with more bias on result, 0 for off
#define MAX_KEY_SIZE 20
#define MIN_KEY_SIZE 4
#define DEBUG_MODE 1 // 1 for on, 0 for off

#include <vector>
#include <algorithm> // for transform and find functions
#include <string>
#include "auxiliary.h"

/**
 * @brief Class to save a text and which indexes of a text it appeared.
 *
 *  It contains a vector<int> of occurencies and a string text.
 */

class particles
{
public:
  std::vector<int> ocurrencies;
  std::vector<int> distances;
  std::string text;

  // redefining operator < for sorting purposes
  bool operator<(const particles &p)
  {
    return this->text.size() < p.text.size();
  }
};

class keyEstimateSize
{
public:
  int size;
  float indexOfCoincidence;

  // redefining operator < for sorting purposes
  bool operator<(const keyEstimateSize &p)
  {
    return this->indexOfCoincidence > p.indexOfCoincidence;
  }
};

// Kasiski examination for key size
particles findInstances(std::string txt, std::string st);
bool alreadyStored(std::string st, std::vector<particles> vec);
std::vector<particles> findParticles(std::vector<char> text);
std::vector<particles> filterRepetitive(std::vector<particles> input);
void calcDistances(std::vector<particles> *particleList);
int repeatedFactor(std::vector<std::vector<int>> factorList, int number);
std::vector<std::vector<int>> findFactors(std::vector<particles> particleList);
bool sortByColumn(std::vector<int> &vectorOne, std::vector<int> &vectorTwo);
void sortFactors(std::vector<std::vector<int>> *listOfFactors);
void printParticles(std::vector<particles> input);
void printFactors(std::vector<std::vector<int>> listOfFactors);

// Friedman test for key size
float findIndexOfCoincidence(std::vector<char> text);
std::vector<std::vector<char>> textToMatrix(std::vector<char> text, int keySize);
std::vector<char> matrixToText(std::vector<std::vector<char>> matrixText, int index);
std::vector<keyEstimateSize> findKeySizeList(std::vector<char> text);
void printIndexAndKeys(std::vector<keyEstimateSize> keyList);
void sortKeySizes(std::vector<keyEstimateSize> *listOfKeySizes);

// Uniting both methods
std::vector<keyEstimateSize> uniteEstimationMethods(std::vector<keyEstimateSize> keyList, std::vector<std::vector<int>> factorList);
void printFinalKeySizes(std::vector<keyEstimateSize> keyList);

// Finding the key
std::vector<std::vector<char>> changeTextFormat(std::vector<char> text, int keySize);
std::vector<double> getLettersFrequency(std::vector<char> coset);
double getXiSquared(std::vector<double> frequency, std::vector<float> baseFrequency);
char findLetterWithLowerXi(std::vector<double> xiSquared);
std::vector<char> findKey(std::vector<std::vector<char>> cosets, int language);

#endif