#include "encript.h"

std::vector<char> encript(std::vector<char> key, std::vector<char> msg)
{
  std::vector<char> cryptogram;
  std::vector<char> keyAux;

  const int MSG_SIZE = msg.size();

  keyAux = extendKey(key, msg.size());

  for (int i = 0; i < MSG_SIZE; i++)
  {
    if (msg[i] > 'z' or msg[i] < 'a')
    {
      cryptogram.push_back(msg[i]);
      continue;
    }
    if (msg[i] + keyAux[i] - 'a' > 'z')
    {
      cryptogram.push_back(msg[i] + keyAux[i] - 'a' - TAM_ALFABETO);
    }
    else
    {
      cryptogram.push_back(msg[i] + keyAux[i] - 'a');
    }
  }

  return cryptogram;
}