/**
 * @file break.cpp
 * @brief Cipher breaking related code.
 *
 */
#include "./headers/break.h"

/**
 * @brief Find all instances of a specific substring in a string txt.
 *
 * @param txt Text to be looked upon.
 * @param st  String to be compared inside the text.
 * @return particles The object that containts the string and the ocurrences.
 */
particles findInstances(std::string txt, std::string st)
{
  particles particle;
  particle.text = st;
  int i = 0;
  while ((i = txt.find(st, i)) != std::string::npos)
  {
    particle.ocurrencies.push_back(i);
    i++;
  }
  return particle;
}

/**
 * @brief Verify if a substring is already saved in a vector of particles
 *
 * @param st Substring to be verified.
 * @param vec Vector of particles to be looked upon.
 * @return true Return true if found.
 * @return false Return false if not found.
 */
bool alreadyStored(std::string st, std::vector<particles> vec)
{
  for (int i = 0; i < vec.size(); i++)
  {
    if (vec[i].text == st)
    {
      return true;
    }
  }
  return false;
}

/**
 * @brief Searches for multiple substrings that repeat inside a text.
 *
 * @param text Text to be searched upon repetitions.
 * @return std::vector<particles> List of instances of repetitive substrings.
 */
std::vector<particles> findParticles(std::vector<char> text)
{
  const std::string txt(text.begin(), text.end());
  std::vector<particles> output;
  particles auxParticle;

  const int TEXT_SIZE = text.size();
  std::string st;

  for (int i = 0; i < TEXT_SIZE - 1; i++)
  {
    for (int j = MIN_PARTICLE_SIZE; j < TEXT_SIZE; j++)
    {
      st = txt.substr(i, j);
      if (alreadyStored(st, output) == true)
      {
        continue;
      }
      auxParticle = findInstances(txt, st);

      if (auxParticle.ocurrencies.size() > 1)
      {
        output.push_back(auxParticle);
      }
    }
  }

  return output;
}

#if ADVANCED_STRING_CUT == 1

/**
 * @brief Creates new list of particles with removed substrings that can be contained by other substrings to deal with redundancy.
 *
 * @param input Input vector of particles to be filtered.
 * @return std::vector<particles> Filtered vector of particles.
 */
std::vector<particles> filterRepetitive(std::vector<particles> input)
{
  std::vector<particles> output;
  int flag;
  int pos;
  for (int i = 0; i < input.size(); i++)
  {
    flag = 0;
    for (int j = 0; j < input.size(); j++)
    {
      if (i == j)
      {
        continue;
      }
      pos = input[j].text.find(input[i].text);
      if (pos != std::string::npos)
      {
        // This increses the ammount of substrings it finds but decreases the accuracy of how reliable is the data

        bool flagSame = false; // flag to verify if a substring is the same as other by comparing ocurrency index
        for (int k = 0; k < input[i].ocurrencies.size(); k++)
        {
          if ((std::find(input[j].ocurrencies.begin(), input[j].ocurrencies.end(), input[i].ocurrencies[k] - pos) != input[j].ocurrencies.end()) && (input[j].ocurrencies.size() == input[i].ocurrencies.size()))
          {
            flagSame = true;
            break;
          }
        }
        if (flagSame == true)
        {
          flag = 1;
          break;
        }
      }
    }
    if (flag == 0)
    {
      output.push_back(input[i]);
    }
  }
  std::sort(output.begin(), output.end());
  std::reverse(output.begin(), output.end());
  return output;
}

#endif
#if ADVANCED_STRING_CUT == 0

std::vector<particles> filterRepetitive(std::vector<particles> input)
{
  std::vector<particles> output;
  int flag;
  int pos;
  for (int i = 0; i < input.size(); i++)
  {
    flag = 0;
    for (int j = 0; j < input.size(); j++)
    {
      if (i == j)
      {
        continue;
      }
      pos = input[j].text.find(input[i].text);
      if (pos != std::string::npos)
      {
        flag = 1;
        break;
      }
    }
    if (flag == 0)
    {
      output.push_back(input[i]);
    }
  }
  std::sort(output.begin(), output.end());
  std::reverse(output.begin(), output.end());
  return output;
}

#endif

/**
 * @brief Calculates the distances between the positions of the particles and stores them in the respective particle vector<int>.
 *
 * @param particleList List of partices to iterate.
 */
void calcDistances(std::vector<particles> *particleList)
{
  int distance;
  for (int i = 0; i < (*particleList).size(); i++)
  {
    for (int j = 0; j < (*particleList)[i].ocurrencies.size(); j++)
    {
      for (int k = j + 1; k < (*particleList)[i].ocurrencies.size(); k++)
      {
        distance = (*particleList)[i].ocurrencies[j] - (*particleList)[i].ocurrencies[k];
        distance = (distance > 0) ? distance : -distance;
        (*particleList)[i].distances.push_back(distance);
      }
    }
  }
}

/**
 * @brief Find if a factor is already present in a list of factors
 *
 * @param factorList List of factors that are composed by a vector of its value on index 0 and the frequency on index 1.
 * @param number Number to find.
 * @return int If negative, there was no match. Else, the index is returned.
 */
int repeatedFactor(std::vector<std::vector<int>> factorList, int number)
{
  int answer = -1;

  for (int i = 0; i < factorList.size(); i++)
  {
    if (factorList[i][0] == number)
    {
      answer = i;
    }
  }

  return answer;
}

/**
 * @brief Find all the factors and their frequency in the distances of a list of particles.
 *
 * @param particleList List of substrings/particles to be analyzed.
 * @return std::vector<std::vector<int>> vector of factors containing its value on index 0 and the frequency on index 1.
 */
std::vector<std::vector<int>> findFactors(std::vector<particles> particleList)
{
  std::vector<std::vector<int>> factorList;
  std::vector<int> factors; // first index is number, second is frequency

  for (int i = 0; i < particleList.size(); i++)
  {
    for (int j = 0; j < particleList[i].distances.size(); j++)
    {
      for (int k = MIN_KEY_SIZE; k <= particleList[i].distances[j]; k++) // finding the factors by iterating over all the lower numbers
      {
        if (particleList[i].distances[j] % k == 0)
        {
          int indexOfFactor = repeatedFactor(factorList, k);
          if (indexOfFactor == -1)
          {
            factors.push_back(k);
            factors.push_back(1);
            factorList.push_back(factors);
            factors.resize(0);
          }
          else
          {
            factorList[indexOfFactor][1]++;
          }
        }
      }
    }
  }

#if DEBUG_MODE == 1
  /**
    printf("factors:\n");
    for (int i = 0; i < factorList.size(); i++)
    {
      printf("%d: %d\n", factorList[i][0], factorList[i][1]);
    }
    **/
#endif
  return factorList;
}

/**
 * @brief Compare two 2D vectors by the index 1 item's size to sort purposes.
 *
 * @param vectorOne First vector.
 * @param vectorTwo Second vector.
 * @return true True if vectorOne[1] > vectorTwo[1].
 * @return false False if vectorOne[1] <= vectorTwo[1]
 */
bool sortByColumn(std::vector<int> &vectorOne, std::vector<int> &vectorTwo)
{
  return vectorOne[1] > vectorTwo[1];
}

/**
 * @brief Sort a list of factors of type std::vector<std::vector<int>>, with first index being the number and second being the frequency, by the frequency.
 *
 * @param listOfFactors List of factors to sort.
 */
void sortFactors(std::vector<std::vector<int>> *listOfFactors)
{
  std::sort((*listOfFactors).begin(), (*listOfFactors).end(), sortByColumn);
}

/**
 * @brief Print all particles saved in a vector of particles.
 *
 * @param particleList Vector of particles to be printed.
 */
void printParticles(std::vector<particles> particleList)
{
  printf("PARTICLES FREQUENCY:\n");

  for (int i = 0; i < particleList.size(); i++)
  {
    printf("txt: '%s'\n", particleList[i].text.c_str());
    printf("occr: ");
    for (int j = 0; j < particleList[i].ocurrencies.size(); j++)
    {
      printf("%d,", particleList[i].ocurrencies[j]);
    }
    printf("\n");
    printf("dist: ");
    for (int j = 0; j < particleList[i].distances.size(); j++)
    {
      printf("%d,", particleList[i].distances[j]);
    }
    printf("\n");
  }
}

/**
 * @brief Print all factors and their frequency from a list.
 *
 * @param factorList List to print.
 */
void printFactors(std::vector<std::vector<int>> factorList)
{
  printf("factors:\n");
  printf("num,\tfreq\n");
  for (int i = 0; i < factorList.size(); i++)
  {
    printf("[%d,\t%d]\n", factorList[i][0], factorList[i][1]);
  }
  printf("\n");
}

/**
 * @brief Finds the index of coincidence of a text.
 *
 * @param text Text to be analyzed.
 * @return float The index of coincidence.
 */
float findIndexOfCoincidence(std::vector<char> text)
{
  int frequency = 0;
  float index = 0;
  float textSize = text.size();

  for (int i = 0; i < TAM_ALFABETO; i++)
  {
    frequency = count(text.begin(), text.end(), 'a' + i);
    index += (frequency * (frequency - 1));
  }

  index = (index / (textSize * (textSize - 1)));

#if DEBUG_MODE == 1
  std::cout << "CI :" << index << std::endl;
#endif

  return index;
}

/**
 * @brief Transforms a text to a matrix text which the number of columns is an estimated key size.
 *
 * @param text Text to be transformed.
 * @param keySize Size of the key.
 * @return std::vector<std::vector<char>> The transformed text.
 */
std::vector<std::vector<char>> textToMatrix(std::vector<char> text, int keySize)
{
  std::vector<char> auxText;
  int textSize = text.size();

  std::vector<std::vector<char>> matrix;

  for (int chars = 0; chars < textSize; chars++)
  {
    if (chars % keySize == 0 && chars != 0)
    {
      matrix.push_back(auxText);
      auxText.clear();
      auxText.push_back(text[chars]);
    }
    else
    {
      auxText.push_back(text[chars]);
    }
  }
  if (auxText.size() > 0)
  {
    matrix.push_back(auxText);
  }

#if DEBUG_MODE == 1
  printf("vei: %d %d\n", matrix.size(), matrix[1].size());
  for (int i = 0; i < matrix.size(); i++)
  {
    printf("*");
    for (int j = 0; j < matrix[i].size(); j++)
    {
      printf("%c", matrix[i][j]);
    }
  }
#endif
  return matrix;
}

/**
 * @brief Transforms a column of a matrix text to a vector form.
 *
 * @param matrixText Matrix that contains the column be transformed.
 * @param index The index of the matrix to transform.
 * @return std::vector<char> The text output.
 */
std::vector<char> matrixToText(std::vector<std::vector<char>> matrixText, int index)
{
  std::vector<char> text;

  for (int i = 0; i < matrixText.size(); i++)
  {
    try
    {
      char aux = matrixText[i].at(index);
    }
    catch (std::out_of_range const &exc)
    {
      return text;
    }
    text.push_back(matrixText[i][index]);
  }

  return text;
}

/**
 * @brief Finds a list of possible key lenghts, with their respective IC (Index of Coincidence) based on the Friedman test.
 *
 * @param text Criptogram to be analyzed.
 * @return std::vector<keyEstimateSize> List of keyLenghts and their IC.
 */
std::vector<keyEstimateSize> findKeySizeList(std::vector<char> text)
{
  float indexOfCoincidence;
  std::vector<std::vector<char>> matrix;
  std::vector<char> auxText;
  keyEstimateSize auxKey;
  std::vector<keyEstimateSize> keyList;

  for (int i = MIN_KEY_SIZE; i <= MAX_KEY_SIZE; i++)
  {
#if DEBUG_MODE == 1
    printf("\ni: %d", i);
#endif
    matrix = textToMatrix(text, i);
    indexOfCoincidence = 0;

    for (int j = 0; j < i; j++)
    {
#if DEBUG_MODE == 1
// printf("\n\tj: %d ", j);
#endif
      auxText = matrixToText(matrix, j);
#if DEBUG_MODE == 1
// printf("---");
#endif
      indexOfCoincidence += findIndexOfCoincidence(auxText);
    }

    matrix.clear();
    auxKey.indexOfCoincidence = indexOfCoincidence / (float)i;
    auxKey.size = i;
    keyList.push_back(auxKey);
  }

  return keyList;
}

/**
 * @brief Print all possible key sizes followed by their Index of Coincidence, by the Friedman test.
 *
 * @param keyList List of key sizes.
 */
void printIndexAndKeys(std::vector<keyEstimateSize> keyList)
{
  printf("\nKey sizes and IC's:\n");
  for (int i = 0; i < keyList.size(); i++)
  {
    printf("[%d:\t%f]\n", keyList[i].size, keyList[i].indexOfCoincidence);
  }
}

/**
 * @brief Sort a list of possible key sizes by their Index of Coincidence.
 *
 * @param listOfKeySizes list of possible key sizes to be sorted.
 */
void sortKeySizes(std::vector<keyEstimateSize> *listOfKeySizes)
{
  std::sort((*listOfKeySizes).begin(), (*listOfKeySizes).end());
}

/**
 * @brief Find the final key list by summing the results of the kasiski method and friedman method.
 *
 * @param keyList List of possible key sizes based on Friedman.
 * @param factorList List of possible key sizes based on Kasiski.
 * @return std::vector<keyEstimateSize> Vector that containts a list of possible key sizes.
 */
std::vector<keyEstimateSize> uniteEstimationMethods(std::vector<keyEstimateSize> keyList, std::vector<std::vector<int>> factorList)
{
  std::vector<keyEstimateSize> finalKeys;
  keyEstimateSize aux;
  std::vector<float> addedList;

  for (int i = 0; i < factorList.size(); i++)
  {
    aux.size = factorList[i][0];
    aux.indexOfCoincidence = factorList[i][1];
    finalKeys.push_back(aux);
    addedList.push_back(aux.size);
  }

  for (int i = 0; i < keyList.size(); i++)
  {
    auto indexIterator = std::find(addedList.begin(), addedList.end(), keyList[i].size);
    if (indexIterator != addedList.end())
    {
      int index = std::distance(addedList.begin(), indexIterator);
      finalKeys[index].indexOfCoincidence += (keyList[i].indexOfCoincidence * 100);
    }
    else
    {
      aux.size = keyList[i].size;
      aux.indexOfCoincidence = (keyList[i].indexOfCoincidence * 100);
      finalKeys.push_back(aux);
    }
  }

  return finalKeys;
}

/**
 * @brief Print all possible final key sizes followed by their weight.
 *
 * @param keyList List of key sizes.
 */
void printFinalKeySizes(std::vector<keyEstimateSize> keyList)
{
  printf("\nKey sizes and weight:\n");
  for (int i = 0; i < keyList.size(); i++)
  {
    printf("[%d:\t%f]\n", keyList[i].size, keyList[i].indexOfCoincidence);
  }
}

/**
 * @brief Transforms a text to a matrix by dividing in cosets (text viewed by columns) and putting them in a vector of cosets.
 *
 * @param text  Text to be analyzed.
 * @param keySize Key size to divide the text.
 * @return std::vector<std::vector<char>> Vector of cosets.
 */
std::vector<std::vector<char>> changeTextFormat(std::vector<char> text, int keySize)
{
  std::vector<std::vector<char>> matrixText = textToMatrix(text, keySize);
  std::vector<std::vector<char>> stringLists(keySize);

  int k = 0;
  for (int i = 0; i < matrixText.size(); i++)
  {
    for (int j = 0; j < matrixText[i].size(); j++)
    {
      if (k == keySize)
      {
        k = 0;
      }
      stringLists[k].push_back(matrixText[i][j]);
      k++;
    }
  }

#if DEBUG_MODE == 1
  printf("vei:\n");
  for (int i = 0; i < stringLists.size(); i++)
  {
    printf("*");
    for (int j = 0; j < stringLists[i].size(); j++)
    {
      printf("%c", stringLists[i][j]);
    }
    printf("\n");
  }
#endif

  return stringLists;
}

/**
 * @brief Obtain a vector of frequencies, from a to z, of a coset.
 *
 * @param coset Coset to be analyzed.
 * @return std::vector<double>  Vector of frequencies.
 */
std::vector<double> getLettersFrequency(std::vector<char> coset)
{
  std::vector<double> frequency(TAM_ALFABETO, 0);
  for (int i = 0; i < coset.size(); i++)
  {
    frequency[(int)(coset[i] - 'a')]++;
  }
  for (int i = 0; i < coset.size(); i++)
  {
    frequency[i] /= (double)coset.size();
  }

#if DEBUG_MODE == 1
  printf("\nfreq: ");
  for (int i = 0; i < frequency.size(); i++)
  {
    std::cout << frequency[i] << ",";
  }
  printf("\n");
#endif

  return frequency;
}

/**
 * @brief Obtain the Xi Squared of a coset frequency list by comparing with baseFrequency list.
 *
 * @param frequency List of letter frequency of coset.
 * @param baseFrequency Language base letter frequency.
 * @return double Xi Squared of coset form determined language.
 */
double getXiSquared(std::vector<double> frequency, std::vector<float> baseFrequency)
{
  double xiSquared = 0;
  float aux;

#if DEBUG_MODE == 1
  printf("\nxiFrac: ");
#endif

  for (int i = 0; i < TAM_ALFABETO; i++)
  {
    aux = ((frequency[i] - baseFrequency[i]) * (frequency[i] - baseFrequency[i]) / (baseFrequency[i]));

#if DEBUG_MODE == 1
    printf("%f = ( %f - %f )^2 / %f \n", aux, frequency[i], baseFrequency[i], baseFrequency[i]);
#endif

    xiSquared += aux;
  }

#if DEBUG_MODE == 1
  printf("\nXi2 = %f\n", xiSquared);
#endif

  return xiSquared;
}

/**
 * @brief Find the letter wich corresponds to a lower Xi of a list of Xi's for different offsets.
 *
 * @param xiSquared Xi Squared of a coset.
 * @return char Result letter.
 */
char findLetterWithLowerXi(std::vector<double> xiSquared)
{
  int letterIndex = 0;
  double xiAux = 999;
  for (int i = 0; i < TAM_ALFABETO; i++)
  {
    if (xiSquared[i] < xiAux)
    {
      xiAux = xiSquared[i];
      letterIndex = i;
    }
  }

#if DEBUG_MODE == 1
  std::cout << "won Letter: " << (char)('a' + letterIndex) << "\n";
#endif

  return ('a' + letterIndex);
}

/**
 * @brief Finds the most probable key characters based on a list of cosets and the language defined.
 *
 * @param cosets
 * @param language  Integet to define the language. 0 for portuguese, any other number for english.
 * @return std::vector<char> Result key.
 */
std::vector<char> findKey(std::vector<std::vector<char>> cosets, int language)
{
  std::vector<float> PortugueseFrequency = {0.14630, 0.01040, 0.03880, 0.04990, 0.12570, 0.01020,
                                            0.01300, 0.01280, 0.06180, 0.00400, 0.00020, 0.02780,
                                            0.04740, 0.05050, 0.10730, 0.02520, 0.01200, 0.06530,
                                            0.07810, 0.04340, 0.04630, 0.01670, 0.00100, 0.02100,
                                            0.00100, 0.04700};

  std::vector<float> EnglishFrequency = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
                                         0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
                                         0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
                                         0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
                                         0.01974, 0.00074};

  std::vector<float> baseFrequency;
  if (language == 0)
  {
    baseFrequency = PortugueseFrequency;
  }
  else
  {
    baseFrequency = EnglishFrequency;
  }

  std::vector<char> key;

  for (int i = 0; i < cosets.size(); i++) // iterate over all cosets
  {
    std::vector<double> xiSquared;
    for (int chars = 0; chars < TAM_ALFABETO; chars++) // iterate the offsets applied to the specific coset
    {

#if DEBUG_MODE == 1
      printf("\nletter: %c", chars + 'a');
#endif

      std::vector<char> offsetText;
      std::vector<double> frequency;

      for (int j = 0; j < cosets[i].size(); j++) // iterate inside the coset to create offset
      {
        offsetText.push_back(((cosets[i][j] - 'a' - chars + TAM_ALFABETO) % TAM_ALFABETO) + 'a');
      }

#if DEBUG_MODE == 1
      printf("\noffsetTxT: ");
      for (int l = 0; l < offsetText.size(); l++)
      {
        printf("%c", offsetText[l]);
      }
#endif

      frequency = getLettersFrequency(offsetText);
      xiSquared.push_back(getXiSquared(frequency, baseFrequency));
    }
    key.push_back(findLetterWithLowerXi(xiSquared));
  }

  printf("\nEstimated key: ");
  for (char i : key)
    std::cout << i;
  std::cout << std::endl;
  return key;
}