/**
 * @file decript.cpp
 * @brief Decription related code.
 *
 */
#include "./headers/decript.h"

/**
 * @brief Decripts a Vigenere's criptogram.
 *
 * @param key Key used to decriptograph the text.
 * @param cript The criptogram to be decriptographed.
 * @return std::vector<char> Text decriptographed from the criptogram.
 */
std::vector<char> decript(std::vector<char> key, std::vector<char> cript)
{
  std::vector<char> message;
  std::vector<char> keyAux;

  const int MSG_SIZE = trueSize(cript);

  keyAux = extendKey(key, cript.size());

  int j = 0;
  for (int i = 0; i < MSG_SIZE; i++)
  {
    message.push_back(((cript[i] - keyAux[j] + TAM_ALFABETO) % TAM_ALFABETO) + 'a');
    j++;
  }

  return message;
}