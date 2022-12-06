/**
 * @file main.cpp
 * @author Gabriel Tambara Rabelo (180017021@aluno.unb.br)
 * @brief Main routine file for Vigenere's cipher toolbox.
 * @version 1.0
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include "./modules/headers/encript.h"
#include "./modules/headers/decript.h"
#include "./modules/headers/auxiliary.h"
#include "./modules/headers/break.h"

/**
 * @brief Main routine for encription and decription of Vigenere's cipher.
 *
 * @return int Exit code.
 */
int main()
{
	std::string s = inputText("input");
	std::string k = inputText("key");

	toLower(&s);
	toLower(&k);

	std::vector<char> cript;
	std::vector<char> msg(s.begin(), s.end());
	std::vector<char> key(k.begin(), k.end());

	msg = formatText(msg);

	cript = encript(key, msg);
	outputText(cript, "criptogram");
	outputText(decript(key, cript), "output");

	// Kasiski examination for key size
	std::vector<particles> listRepeated;
	std::vector<std::vector<int>> listOfFactors;

	listRepeated = findParticles(cript);
	listRepeated = filterRepetitive(listRepeated);
	calcDistances(&listRepeated);
	listOfFactors = findFactors(listRepeated);
	sortFactors(&listOfFactors);
	printFactors(listOfFactors);

	// Friedman test for key size
	std::vector<keyEstimateSize> keyList = findKeySizeList(cript);
	sortKeySizes(&keyList);
	printIndexAndKeys(keyList);

	// Uniting both methods
	std::vector<keyEstimateSize> finalKeys = uniteEstimationMethods(keyList, listOfFactors);
	sortKeySizes(&finalKeys);
	printFinalKeySizes(finalKeys);

	// Finding the key
	std::vector<char> EstimatedKey;
	printf("\nKey size: %d\n", finalKeys[0].size);
	std::vector<std::vector<char>> matrixText = changeTextFormat(cript, finalKeys[0].size);
	EstimatedKey = findKey(matrixText, 1);

	return 0;
}