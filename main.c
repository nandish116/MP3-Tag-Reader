#include<stdio.h>
#include<string.h>
#include "MP3_header.h"

int main(int argc, char* argv[])
{
    //Validate cmd line arguments
    validate_args(argc, argv);   //function call for validation

    if(!(strcmp(argv[1], "-v")))
    {
        mp3_view(argv);  //function call for view
    }
    if(!(strcmp(argv[1], "-e")))
    {
       mp3_edit(argc, argv); //function call for edit
    }
    if(!(strcmp(argv[1], "--help")))
    {
       mp3_help(argv);  //function call for displaying help menu
    }

}
