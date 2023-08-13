#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define LISTSIZE 1000
#define EXACT 2
#define CLOSE 1
#define WRONG 0

#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define MAG     "\e[0;35m"
#define RESET   "\e[0;39m"

bool check_guess(char *guess, int wordsize);
char *get_guess(int wordsize);
int check_word(char *guess, int wordsize, int status[], char *choice);
void print_word(char *guess, int wordsize, int status[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    int wordsize = atoi(argv[1]);

    if (!(wordsize >= 5 && wordsize <= 8))
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    char wl_filename[10];
    sprintf(wl_filename, "%d.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    srand(time(NULL));
    char *choice = options[rand() % LISTSIZE];
    int guesses = wordsize + 1;
    int won = 0;

    printf(MAG"This is WORDLE09"RESET"\n");
    printf("You have %d tries to guess the %d-letter word I'm thinking of\n", guesses, wordsize);

    for (int i = 0; i < guesses; i++)
    {
        char *guess = get_guess(wordsize);

        int status[wordsize];

        for (int k = 0; k < wordsize; k++)
        {
            status[k] = WRONG;
        }

        printf("Guess %d: ", i + 1);
        int score = check_word(guess, wordsize, status, choice);
        print_word(guess, wordsize, status);

        if (score == EXACT * wordsize)
        {
            won = 1;
            break;
        }
    }

    if (won)
    {
        printf("You won!\n");
    }
    else
    {
        printf("You lose!\nThe correct word was '%s'\n", choice);
    }

    return 0;
}

bool check_guess(char *guess, int wordsize)
{
    if (strlen(guess) != wordsize)
    {
        return false;
    }
    for (int i = 0; i < strlen(guess); i++)
    {
        if (!islower(guess[i]))
        {
            return false;
        }
    }
    return true;
}

char *get_guess(int wordsize)
{
    char *guess = malloc((wordsize + 1) * sizeof(char));
    do
    {
        printf("Input a %d-letter word: ", wordsize);
        scanf("%s", guess);
    }
    while (!check_guess(guess, wordsize));

    return guess;
}

int check_word(char *guess, int wordsize, int status[], char *choice)
{
    int score = 0;

    for (int i = 0; i < wordsize; i++)
    {
        for (int j = 0; j < wordsize; j++)
        {
            if (guess[i] == choice[j])
            {
                if (i == j)
                {
                    score += EXACT;
                    status[i] = EXACT;
                    break;
                }
                else
                {
                    score += CLOSE;
                    status[i] = CLOSE;
                }
            }
        }
    }
    return score;
}

void print_word(char *guess, int wordsize, int status[])
{
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == EXACT)
        {
            printf(GREEN " %c " RESET, guess[i]);
        }
        else if (status[i] == CLOSE)
        {
            printf(YELLOW " %c " RESET, guess[i]);
        }
        else
        {
            printf(RED " %c " RESET, guess[i]);
        }
    }
    printf("\n");
}
