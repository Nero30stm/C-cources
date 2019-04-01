#include <iostream>
#include <string.h>
#include <vector>
#include <cassert>

using namespace std;

int _min(int a, int b, int c)
{
    return min(min(a, b), c);
}

int **createMatrix(int row_count, int column_count)
{
    int **array = new int*[row_count];
    for(int i = 0; i < row_count; ++i)
    {
        array[i] = new int[column_count];
    }
    return array;
}

int LD(const char *firstWord, const char *secondWord)
{
    size_t firstWordLength = strlen(firstWord);
    size_t secondWordLength = strlen(secondWord);
    if (firstWordLength == 0)
    {
        return secondWordLength;
    }
    if (secondWordLength == 0)
    {
        return firstWordLength;
    }

    int **matrix = createMatrix(secondWordLength + 1, firstWordLength + 1);
    for(unsigned int i = 0; i <= firstWordLength; ++i)
    {
        matrix[0][i] = i;
    }

    for(unsigned int i = 0; i <= secondWordLength; ++i)
    {
        matrix[i][0] = i;
    }

    unsigned int aboveCell, leftCell, diagonalCell, cost;

    for(unsigned i = 1; i <= secondWordLength; ++i)
    {
        for(unsigned int j = 1; j <= firstWordLength; ++j)
        {
            if (firstWord[i-1] == secondWord[j-1])
            {
                cost = 0;
            }
            else
            {
                cost = 1;
            }
            aboveCell = matrix[i-1][j];
            leftCell = matrix[i][j-1];
            diagonalCell = matrix[i-1][j-1];
            matrix[i][j] = _min(aboveCell + 1, leftCell + 1, diagonalCell + cost);
        }
    }
    unsigned int result = matrix[secondWordLength][firstWordLength];
    delete [] matrix;
    return result;
}

char* findWordInDictionary(char* inputWord, char** dictionary, const unsigned int dictionaryLength)
{
    char* resultWord = inputWord;
    int minDifferent = strlen(inputWord);
    for(unsigned int i = 0; i < dictionaryLength; ++i)
    {
        if(LD(inputWord, dictionary[i]) < minDifferent)
        {
            minDifferent = LD(inputWord, dictionary[i]);
            resultWord = dictionary[i];
        }
    }
    return resultWord;
}

int main()
{
    char* dictionary[4] {"apple", "orange", "black", "white"};
    {
        assert(LD("aby", "abcd") == 2);
    }

    {
        assert(LD("", "poiuy") == 5);
    }

    {
        assert(LD("bak", "black") == 4);
    }
    {
        assert(findWordInDictionary("opplia",dictionary, 4) == dictionary[0]);
    }
    {
        assert(findWordInDictionary("bac",dictionary, 4) == "bac");
    }
    {
        assert(findWordInDictionary("",dictionary, 4) == "");
    }
}

