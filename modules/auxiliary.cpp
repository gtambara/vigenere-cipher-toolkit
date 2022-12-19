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
 * @brief Format text by removing/adapting spaces and special characters.
 *
 * @param text Text to be formatted.
 */
std::vector<char> formatText(std::vector<char> text)
{
  std::vector<char> aux;
  for (int i = 0; i < text.size(); i++)
  {
    if (text[i] >= 'a' && text[i] <= 'z')
    {
      aux.push_back(text[i]);
    }
  }
  return aux;
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

/**
 * @brief Find useful size of vector, disregarding non characters.
 *
 * @param msg Message to be analyzed.
 * @return int Size of message.
 */
int trueSize(std::vector<char> msg)
{
  int size = 0;
  for (int i = 0; i < msg.size(); i++)
  {
    if (msg[i] >= 'a' && msg[i] <= 'z')
    {
      size++;
    }
  }
  return size;
}

/**
 * @brief Holds the information about where to put special characters in the text after removing them.
 *
 * @param text  Text with special chars to be later removed.
 * @return std::vector<int> Vector with the proper index where special chars need to be placed again later.
 */
std::vector<specialChars> receiveSpecials(std::string text)
{
  std::vector<specialChars> replacementList;
  specialChars itemAux;

  for (int i = 0; i < text.size(); i++)
  {
    if (text[i] > 'z' || text[i] < 'a')
    {
      if ((unsigned char)text[i] > 127) // Verify if it's a non ascii character
      {
        itemAux.index = -1;
        replacementList.push_back(itemAux);
      }
      else
      {
        itemAux.character = text[i];
        itemAux.index = i;
        replacementList.push_back(itemAux);
      }
#if DEBUG_MODE == 0
      printf("[%d,%c]", itemAux.index, itemAux.character);
#endif
    }
  }

  return replacementList;
}

/**
 * @brief Add spaces in the indexes saved  before removing them in the text.
 *
 * @param text Text to add spaces.
 * @param spaces Vector of index of spaces positions.
 */
void addSpecials(std::vector<char> *text, std::vector<specialChars> replacementList)
{
  if (replacementList.size() <= 0)
  {
    return;
  }

  int errorCounter = 0;
  (*text).push_back(' ');
  for (int i = 0; i <= (*text).size() + errorCounter; i++)
  {
    if (replacementList[0].index == -1)
    {
      replacementList.erase(replacementList.begin());
      errorCounter++;
    }
    if (i == replacementList[0].index)
    {
#if DEBUG_MODE == 0
      printf("\n[%d,%c]\n", i, replacementList.back().character);
#endif
      (*text).insert((*text).begin() + i - errorCounter, replacementList[0].character);
      replacementList.erase(replacementList.begin());
    }
    if (replacementList.size() == 0)
    {
      break;
    }
  }
  (*text).pop_back();
}
