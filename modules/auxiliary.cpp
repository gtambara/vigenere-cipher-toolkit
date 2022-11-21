#include "./headers/auxiliary.h"

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

void toLower(std::string *text)
{
  std::transform((*text).begin(), (*text).end(), (*text).begin(), [](unsigned char c)
                 { return std::tolower(c); });
}

void outputText(std::vector<char> text, std::string filename)
{
  std::string ss(text.begin(), text.end());
  std::ofstream file(FILES_FOLDER + filename + ".txt");
  file << ss;
  file.close();
}

std::string inputText(std::string filename)
{
  std::ifstream file(FILES_FOLDER + filename + ".txt");
  return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}
