/**
 * @file main.cpp
 * @author Gabriel Tambara Rabelo (180017021@aluno.unb.br)
 * @brief Main routine file for Vigenere's cipher.
 * @version 1.0
 * @date 2022-11-21
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
	const std::vector<char> msg(s.begin(), s.end());
	const std::vector<char> key(k.begin(), k.end());

	cript = encript(key, msg);
	outputText(cript, "criptogram");
	outputText(decript(key, cript), "output");

	return 0;
}