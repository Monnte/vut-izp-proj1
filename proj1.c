//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//         Projekt C.1 - Telfonny zoznam                                    //
//         Vypracoval - Peter Zdravekcy                                     //
//         10.11.2019                                                       //
//                                                                          //
//                                                                          //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_LENGTH 103

int read_a_print(char *Key);
bool isvalid(char *Line);
bool isNumber(char number[]);
void convert(char *buffer);
bool compare(char *Line, char *Key);

int main(int argc, char **argv)
{
    char *Key = NULL;
    //Overenie argumentu a priradenie hodnoty hladanej sekvencei na kontrolu
    if (argc >= 2)
    {
        if (isNumber(argv[1]))
            Key = argv[1];
        else
        {
            fprintf(stderr, "> Invalid number sequence.\n");
            return 1;
        }
    }
    //Volanie funkcii read and print a zapisanie vysledku
    int result = read_a_print(Key);
    //Ak sa nič nenájde tak vypíš Not Found
    if (!result && (Key != NULL))
        printf("Not Found\n");

    return 0;
}

int read_a_print(char *Key)
{
    char name[LINE_LENGTH];
    char number[LINE_LENGTH];
    int num_founded = 0;
    //čitaj mená
    while (fgets(name, LINE_LENGTH, stdin) != NULL)
    {
        //Osetrenie neplatnych dát // Meno
        name[strcspn(name, "\n")] = '\0';
        bool validname = isvalid(name);
        //Osetrenie neplatnych dát // Cislo
        fgets(number, LINE_LENGTH, stdin);
        number[strcspn(number, "\n")] = '\0';
        bool validnumber = isvalid(number);
        if (!validname || !validnumber)
        {
            fprintf(stderr, "> Invalid Data.\n");
            continue;
        }
        //Vypis Kontaktu ak obsahuje hladanú postupnosť
        if (compare(name, Key) || compare(number, Key))
        {
            printf("%s, %s\n", name, number);
            num_founded++;
        }
    }
    return num_founded;
}
bool isvalid(char *Line)
{
    if (strlen(Line) > (101 - 1))
    { //101 - 1 lebo odstranujem /n
        while (fgets(Line, LINE_LENGTH, stdin) != NULL && strstr(Line, "\n") == NULL)
            ;
        return false;
    }
    return true;
}
bool isNumber(char number[])
{
    for (int i = 0; number[i] != '\0'; i++)
        if (!isdigit(number[i]))
            return false;

    return true;
}
void convert(char *buffer)
{
    //Konvertovanie retazca na základe podmienok / Výsledok je postupnost čisiel
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        buffer[i] = tolower(buffer[i]);
        //Convertuj pismena na čisla
        if ((buffer[i] >= 'a') && (buffer[i] <= 'c'))
            buffer[i] = '2';
        else if ((buffer[i] >= 'd') && (buffer[i] <= 'f'))
            buffer[i] = '3';
        else if ((buffer[i] >= 'g') && (buffer[i] <= 'i'))
            buffer[i] = '4';
        else if ((buffer[i] >= 'j') && (buffer[i] <= 'l'))
            buffer[i] = '5';
        else if ((buffer[i] >= 'm') && (buffer[i] <= 'o'))
            buffer[i] = '6';
        else if ((buffer[i] >= 'p') && (buffer[i] <= 's'))
            buffer[i] = '7';
        else if ((buffer[i] >= 't') && (buffer[i] <= 'v'))
            buffer[i] = '8';
        else if ((buffer[i] >= 'w') && (buffer[i] <= 'z'))
            buffer[i] = '9';
        else if (buffer[i] == '+')
            buffer[i] = '0';
    }
}
bool compare(char *Line, char *Key)
{
    if (Key == NULL)
        return true; //Ak je hladana sekvencia prazdna tak vyhovuje kazdy kontakt / vrať true.
    char Word[LINE_LENGTH];
    strcpy(Word, Line);
    convert(Word);
    int KeyLenght = strlen(Key);
    //Hladanie postupnosti prerusene / neprerusene
    int z = 0;
    for (int k = 0; Word[k] != '\0'; k++)
    {
        if (Word[k] == Key[z])
        {
            z++;
            if (z == KeyLenght)
                return true;
        }
    }
    return false;
}