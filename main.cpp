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
	std::string c = inputText("criptogram");
	std::vector<char> cript;
	std::vector<char> msg;
	std::vector<char> key;

	std::vector<particles> listRepeated;
	std::vector<std::vector<int>> listOfFactors;

	std::vector<keyEstimateSize> keyList;
	std::vector<keyEstimateSize> finalKeys;
	std::vector<char> EstimatedKey;
	std::vector<std::vector<char>> matrixText;

	int selectedSize;
	int selectedLang = 1;

	char operation;
	do
	{
		std::cout << "Vigenere cipher toolbox" << std::endl;
		std::cout << "1 - Full test routine" << std::endl;
		std::cout << "2 - Import text" << std::endl;
		std::cout << "3 - Import key" << std::endl;
		std::cout << "4 - Import criptogram" << std::endl;
		std::cout << "5 - Cipher text" << std::endl;
		std::cout << "6 - Decipher text with known key" << std::endl;
		std::cout << "7 - Estimate key size" << std::endl;
		std::cout << "8 - Find key with chosen size" << std::endl;
		std::cout << "9 - Choose text for decription language" << std::endl;
		std::cout << "0 - Exit" << std::endl;
		std::cin >> operation;

		switch (operation)
		{
		case '1':

			s = inputText("input");
			k = inputText("key");

			toLower(&s);
			toLower(&k);

			std::copy(s.begin(), s.end(), std::back_inserter(msg));
			std::copy(k.begin(), k.end(), std::back_inserter(key));

			msg = formatText(msg);
			key = formatText(key);

			cript = encript(key, msg);
			outputText(cript, "criptogram");
			outputText(decript(key, cript), "output");

			// Kasiski examination for key size

			listRepeated = findParticles(cript);
			listRepeated = filterRepetitive(listRepeated);
			calcDistances(&listRepeated);
			listOfFactors = findFactors(listRepeated);
			sortFactors(&listOfFactors);
			printFactors(listOfFactors);

			// Friedman test for key size
			keyList = findKeySizeList(cript);
			sortKeySizes(&keyList);
			printIndexAndKeys(keyList);

			// Uniting both methods
			finalKeys = uniteEstimationMethods(keyList, listOfFactors);
			sortKeySizes(&finalKeys);
			printFinalKeySizes(finalKeys);

			// Finding the key
			printf("\nKey size: %d\n", finalKeys[0].size);
			matrixText = changeTextFormat(cript, finalKeys[0].size);
			EstimatedKey = findKey(matrixText, selectedLang);

			break;

		case '2':
			s = inputText("input");
			toLower(&s);
			msg.clear();
			std::copy(s.begin(), s.end(), std::back_inserter(msg));
			msg = formatText(msg);
			std::cout << "\nText imported:\n"
								<< std::endl;

			for (char i : msg)
				std::cout << i;
			std::cout << std::endl
								<< std::endl;
			break;

		case '3':
			k = inputText("key");
			toLower(&k);
			key.clear();
			std::copy(k.begin(), k.end(), std::back_inserter(key));
			key = formatText(key);
			std::cout << "\nKey imported:\n"
								<< std::endl;

			for (char i : key)
				std::cout << i;
			std::cout << std::endl
								<< std::endl;
			break;

		case '4':
			c = inputText("criptogram");
			toLower(&c);
			cript.clear();
			std::copy(c.begin(), c.end(), std::back_inserter(cript));
			cript = formatText(cript);
			std::cout << "\nCriptogram imported:\n"
								<< std::endl;
			for (char i : cript)
				std::cout << i;
			std::cout << std::endl
								<< std::endl;
			break;

		case '5':
			cript = encript(key, msg);
			outputText(cript, "criptogram");
			std::cout << "\nCriptogram generated\n"
								<< std::endl;
			break;

		case '6':
			outputText(decript(key, cript), "output");
			std::cout << "\nDecripted output generated\n"
								<< std::endl;
			break;

		case '7':
			// Kasiski examination for key size
			listRepeated = findParticles(cript);
			listRepeated = filterRepetitive(listRepeated);
			calcDistances(&listRepeated);
			listOfFactors = findFactors(listRepeated);
			sortFactors(&listOfFactors);
			printFactors(listOfFactors);

			std::cout << "\nKasiski method finished. Beggining Friedman test.\n"
								<< std::endl;

			// Friedman test for key size
			keyList = findKeySizeList(cript);
			sortKeySizes(&keyList);
			printIndexAndKeys(keyList);

			std::cout << "\nFriedman method finished. Merging results.\n"
								<< std::endl;

			// Uniting both methods
			finalKeys = uniteEstimationMethods(keyList, listOfFactors);
			sortKeySizes(&finalKeys);
			printFinalKeySizes(finalKeys);
			std::cout << std::endl;
			break;

		case '8':
			std::cout << "\nPress the selected key size number\n"
								<< std::endl;
			std::cin >> selectedSize;
			std::cout << "\nSelected key size of " << selectedSize << std::endl
								<< std::endl;
			// Finding the key
			matrixText = changeTextFormat(cript, selectedSize);
			EstimatedKey = findKey(matrixText, selectedLang);
			std::cout << std::endl;
			break;

		case '9':
			std::cout << "\nPress 0 for portuguese and 1 for english\n"
								<< std::endl;
			std::cin >> selectedLang;
			if (selectedLang != 0 && selectedLang != 1)
			{
				std::cout << "\nInvalid input, exiting operation\n"
									<< std::endl;
			}
			break;

		case '0':
			return 0;

		default:
			std::cout << "Invalid command, please try again" << std::endl;
			break;
		}

	} while (operation != '0');

	return 0;
}