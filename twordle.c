//Author: Ian Sutherland
//Purpose: Project 10

#include <stdio.h>
#include <stdbool.h>

#define SIZE 5
#define TRIES 6

void readWord(char word[]);
void makeLower(char str[]);
bool goodGuess(char guess[]);
bool same(char guess[], char word[]);
bool hasLetter(char word[], char c);
void show(char guesses[][SIZE + 1], int count, char word[]);

int main(){
    
    char word[SIZE + 1];
    char guess[SIZE + 1];
    char guesses[TRIES][SIZE + 1];

    int count = 0;
    bool won = false;

    readWord(word);

    while (count < TRIES && !won){
        
        printf("Guess: ");
        scanf("%s", guess);

        makeLower(guess);

        if (!goodGuess(guess))
        {
            printf("Invalid guess. Try again.\n");
        }
        else
        {
            for (int i = 0; i < SIZE; i++)
                guesses[count][i] = guess[i];

            guesses[count][SIZE] = '\0';
            count++;

            show(guesses, count, word);

            if (same(guess, word))
                won = true;
        }
    }

    if (won)
        printf("You won!\n");
    else
        printf("You lost. The word was %s\n", word);

    return 0;
}

void readWord(char word[])
{
    FILE *fin = fopen("mystery.txt", "r");
    fscanf(fin, "%s", word);
    fclose(fin);
    makeLower(word);
}

void makeLower(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    }
}

bool goodGuess(char guess[])
{
    int length = 0;

    while (guess[length] != '\0')
        length++;

    if (length != SIZE)
        return false;

    for (int i = 0; i < SIZE; i++)
    {
        if (guess[i] < 'a' || guess[i] > 'z')
            return false;
    }

    return true;
}

bool same(char guess[], char word[])
{
    for (int i = 0; i < SIZE; i++)
    {
        if (guess[i] != word[i])
            return false;
    }

    return true;
}

bool hasLetter(char word[], char c)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (word[i] == c)
            return true;
    }

    return false;
}

void show(char guesses[][SIZE + 1], int count, char word[])
{
    printf("\n");

    for (int row = 0; row < count; row++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (guesses[row][i] == word[i])
                printf("%c", guesses[row][i] - 32);
            else
                printf("%c", guesses[row][i]);
        }

        printf("\n");

        for (int i = 0; i < SIZE; i++)
        {
            if (guesses[row][i] != word[i] && hasLetter(word, guesses[row][i]))
                printf("^");
            else
                printf(" ");
        }

        printf("\n");
    }

    printf("\n");
}

