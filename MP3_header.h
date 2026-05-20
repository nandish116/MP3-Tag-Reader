#ifndef MP3_H
#define MP3_H

#include<stdio.h>

void mp3_view(char* argv[]);    //function prototype for view
void mp3_edit(int argc, char* argv[]);   //function prototype for edit
void convert_be_to_le(char* ptr);        //function prototype for endiness conversion
void tag_name(char* tag, char* tagname );  //function prototype for tag_name
void edittag_name(char* tag, char* edittag, char* tagname );   //function prototype for editing tag name
void mp3_help(char* argv[]);  //function prototype for help
void validate_args(int argc, char* argv[]);  //function prototype for validation
void display_error(char* argv[]);  //function prototype for displaying error


#endif
