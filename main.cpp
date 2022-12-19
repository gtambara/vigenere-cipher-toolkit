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
	bool insertedText = false;
	bool insertedKey = false;
	bool insertedCriptogram = false;

	std::string s = inputText("input");
	std::string k = inputText("key");
	std::string c = inputText("criptogram");

	std::vector<specialChars> replacementList;

	std::vector<char> cript;
	std::vector<char> msg;
	std::vector<char> key;

	std::vector<char> outputAux;
	std::vector<int> spaces;

	std::vector<particles> listRepeated;
	std::vector<std::vector<int>> listOfFactors;

	std::vector<keyEstimateSize> keyList;
	std::vector<keyEstimateSize> finalKeys;
	std::vector<char> EstimatedKey;
	std::vector<std::vector<char>> matrixText;

	int selectedSize;
	int selectedLang = 1;

	char operation;
	char operationTwo;
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

			replacementList = receiveSpecials(s);

			std::copy(s.begin(), s.end(), std::back_inserter(msg));
			std::copy(k.begin(), k.end(), std::back_inserter(key));

			msg = formatText(msg);
			key = formatText(key);

			cript = encript(key, msg);
			outputText(cript, "criptogram");

			outputAux = decript(key, cript);
			addSpecials(&outputAux, replacementList);
			outputText(outputAux, "output");

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
			replacementList = receiveSpecials(s);
			msg.clear();
			std::copy(s.begin(), s.end(), std::back_inserter(msg));
			msg = formatText(msg);
			std::cout << "\nText imported:\n"
								<< std::endl;

			for (char i : msg)
				std::cout << i;
			std::cout << std::endl
								<< std::endl;

			insertedText = true;
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

			insertedKey = true;
			break;

		case '4':
			c = inputText("criptogram");
			replacementList = receiveSpecials(c);
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

			insertedCriptogram = true;
			break;

		case '5':
			if (insertedKey == false || insertedText == false)
			{
				std::cout << "You have to import a key and a message for this process." << std::endl;
				break;
			}
			cript = encript(key, msg);
			outputText(cript, "criptogram");
			std::cout << "\nCriptogram generated\n"
								<< std::endl;

			insertedCriptogram = true;
			break;

		case '6':
			if (insertedKey == false || insertedCriptogram == false)
			{
				std::cout << "You have to import a key and a criptogram for this process." << std::endl;
				break;
			}
			outputAux = decript(key, cript);
			addSpecials(&outputAux, replacementList);
			outputText(outputAux, "output");
			std::cout << "\nDecripted output generated\n"
								<< std::endl;

			break;

		case '7':
			if (insertedCriptogram == false)
			{
				std::cout << "You have to import a criptogram for this process." << std::endl;
				break;
			}
			do
			{
				std::cout << "\nSelect the method of estimation\n"
									<< std::endl;
				std::cout << "\n1 - Kasiski method (slow for big texts)\n"
									<< std::endl;
				std::cout << "\n2 - Fridman method (fast)\n"
									<< std::endl;
				std::cout << "\n3 - Mix methods\n"
									<< std::endl;
				std::cin >> operationTwo;

			} while (operationTwo != '1' && operationTwo != '2' && operationTwo != '3');

			switch (operationTwo)
			{
			case '1':
				listRepeated = findParticles(cript);
				listRepeated = filterRepetitive(listRepeated);
				calcDistances(&listRepeated);
				listOfFactors = findFactors(listRepeated);
				sortFactors(&listOfFactors);
				printFactors(listOfFactors);
				break;

			case '2':
				keyList = findKeySizeList(cript);
				sortKeySizes(&keyList);
				printIndexAndKeys(keyList);
				break;

			case '3':
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

			default:
				std::cout << "Invalid command, please try again" << std::endl;
				break;
			}

			break;

		case '8':
			if (insertedCriptogram == false)
			{
				std::cout << "You have to import a criptogram for this process." << std::endl;
				break;
			}
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