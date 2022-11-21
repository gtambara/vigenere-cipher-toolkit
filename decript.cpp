#include "decript.h"

std::vector<char> decript(std::vector<char> key, std::vector<char> cript)
{
  std::vector<char> message;
  std::vector<char> keyAux;

  const int MSG_SIZE = cript.size();

  keyAux = extendKey(key, cript.size());

  for (int i = 0; i < MSG_SIZE; i++)
  {
    if (cript[i] > 'z' || cript[i] < 'a')
    {
      message.push_back(cript[i]);
      continue;
    }
    if (cript[i] - keyAux[i] < 0)
    {
      message.push_back(cript[i] - keyAux[i] + TAM_ALFABETO + 'a');
    }
    else
    {
      message.push_back(cript[i] - keyAux[i] + 'a');
    }
  }
  return message;
}