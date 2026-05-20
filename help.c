#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "MP3_header.h"

void mp3_help(char* argv[])  //function defintion for help menu.
{
    printf("\n\t\t>>>>>Help menu<<<<<\n");
    printf("+--------+------------------------------------------------------+\n");
    printf("|Options |\tSyntax\t\t\t\t\t\t|\n");
    printf("+--------+------------------------------------------------------+\n");
    printf("|1. View |\t./a.out -v <filename.mp3>\t\t\t|\n");
    printf("|2. Edit |\t./a.out -e -edit_tag new_one <filename.mp3>\t|\n");
    printf("|3. Help |\t./a.out --help\t\t\t\t\t|\n");
    printf("+--------+------------------------------------------------------+\n");
    printf("+-------------------------------+\n");
    printf("|   >>>>>Tags for edit<<<<<\t|\n");
    printf("+-------------------------------+\n");
    printf("|-t : Modifies a title tag\t|\n|-a : Modifies a Artist tag\t|\n|-A : Modifies a Album tag\t|\n|-y : Modifies a Year tag\t|\n|-C : Modifies a Content tag\t|\n|-c : Modifies a Comment tag\t|\n");
    printf("+-------------------------------+\n");
}

void validate_args(int argc, char* argv[])  //Function definition for validation.
{
    if((!(argc == 3 || argc == 5 || argc == 2) ) || ((strcmp(argv[1], "-v") && strcmp(argv[1], "-e") && strcmp(argv[1], "--help"))) ) //verifies argc and 2nd arg
    {
        display_error(argv);
        exit(0);
    }
    if((!strcmp(argv[1], "-e")) && argc == 5) //to check if 2nd arg is -e and argc is 5
    {
        char TAGID[6][3] = {"-t", "-a", "-A", "-y", "-C", "-c"};
        int flag = 0;
        for(int i = 0; i < 6; i++)
        {
            if(!(strcmp(argv[2], TAGID[i])))
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            display_error(argv);  //to display error
            exit(0);
        }
    }
    
    //(to display error if 2nd argument is neither -v or --help) ||
    // (to check even if 2nd arument is --help but not contains 2 argument, if so display error) || 
    //(to check even if 2nd arument is -v but not contains 3 argument, if so display error)
    else if((strcmp(argv[1], "-v") && strcmp(argv[1], "--help")) || (!strcmp(argv[1], "--help") && argc != 2) || (!strcmp(argv[1], "-v") && argc != 3)) 
    {
        display_error(argv);
        exit(0);
    }
}

void display_error(char* argv[])
{
    //to store CL arg as a string
    char str[200] = "";
    int i = 0;
    while(argv[i] != NULL)
    {
        strcat(str, argv[i]);
        strcat(str, " ");
        i++;
    }

    //Error message
    printf("-------------------------------------------------------------------\n");
    printf("ERROR: %s: INVALID ARGUMENTS\n", str);
    printf("USAGE :\n");
    printf("To view pass like: ./a.out -v mp3filename\n");
    printf("To edit pass like: ./a.out -e -t/-a/-A/-m/-y/-c new_one mp3filename\n");
    printf("-------------------------------------------------------------------\n");

}
