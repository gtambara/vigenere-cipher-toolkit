/**
 * @file auxiliary.cpp
 * @brief Auxiliary functions for encription/decription related code.
 *
 */
#include "./headers/auxiliary.h"

/**
 * @brief Extend the key string to a keystream of the message's size.
 *
 * @param key Cryptographic key used for encription.
 * @param newSize Size of the message.
 * @return std::vector<char> Extended keystream.
 */
std::vector<char> extendKey(std::vector<char> key, const int newSize)
{
  std::vector<char> keyAux;

  const int KEY_SIZE = key.size();

  // extend and loop key to size of msg
  int index = 0;
  for (int i = 0; i < newSize; i++)
  {
    if (index == KEY_SIZE)
    {
      index = 0;
    }
    keyAux.push_back(key[index]);
    index++;
  }

  return keyAux;
}

/**
 * @brief Transform a text to remove casp lock.
 *
 * @param text Text to be transformed.
 */
void toLower(std::string *text)
{
  std::transform((*text).begin(), (*text).end(), (*text).begin(), [](unsigned char c)
                 { return std::tolower(c); });
}

/**
 * @brief Output text to filename.txt file.
 *
 * @param text Text to be outputted.
 * @param filename Name of the file for the text to be outstreamed to.
 */
void outputText(std::vector<char> text, std::string filename)
{
  std::string ss(text.begin(), text.end());
  std::ofstream file(FILES_FOLDER + filename + ".txt");
  file << ss;
  file.close();
}

/**
 * @brief Input text from filename.txt file.
 *
 * @param filename Name of the file for the text to be read.
 * @return std::string String from which the input text is saved.
 */
std::string inputText(std::string filename)
{
  std::ifstream file(FILES_FOLDER + filename + ".txt");
  return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}
