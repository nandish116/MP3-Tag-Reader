#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "MP3_header.h"

void mp3_edit(int argc, char* argv[])
{
    
    //to open sample.mp3
    FILE* fp1 = NULL;
    fp1 = fopen(argv[4], "r");
    if(fp1 == NULL)
    {
        printf("file not found\n");
        display_error(argv);
        exit(0);
    }

    //to find which tag to edit
    char edittag[5], tagname[8];
    edittag_name(argv[2], edittag, tagname);





    char buffer[4];  //buffer string for storing the data
    fread(buffer, 3, 1, fp1);
    buffer[3] = '\0';
    if(!(strcmp(buffer, "ID3")))  //to check if it is mp3 file
    {
        printf("%s is an MP3 file\n", argv[4]);
    }
    else
    {
        printf("%s is not an MP3 file\n", argv[4]);
        display_error(argv);
        return;
    }

    printf("---------------------------Selected Edit Option---------------------------\n");
    printf("-----------------------Selected %s Change Option-----------------------\n", tagname);
    printf("\t\t%s : %s\n", tagname,argv[3] );

    //to open temp.mp3
    FILE* fp2 = NULL;
    fp2 = fopen("temp.mp3", "w");
    if(fp2 == NULL)
    {
        printf("Error opening file\n");
        exit(0);
    }
    fwrite(buffer, 3, 1, fp2);  //to write ID3 to temp.mp3

    //to read 10 bytes of header
    char header[8];
    fread(header, 7, 1, fp1);
    header[7] = '\0';
    //to write 10 bytes of header
    fwrite(header, 7, 1, fp2);

    for(int i = 0; i < 6; i++)
    {
        //to read 4 bytes of tag
        char tag[5];
        fread(tag, 4, 1, fp1);
        tag[4] = '\0';
        //to write tag
        fwrite(tag, 4, 1, fp2);

        //to check if it is the same tag we should edit
        if(!(strcmp(edittag, tag)))
        {
            int len = strlen(argv[3]);
            len++; //to include null character
            int oglen = len;

            //to convert  to len to little endian.
            char* ptr = (char*)&len;  // since len is integer we shoud type cast address to character address
            convert_be_to_le(ptr);   //function call for conversion.

            fwrite(&len, 4, 1, fp2);  //to write size
            
            int size;
            fread(&size, 4, 1, fp1); //to get size of content
            char* ptr1 = (char*)&size;  // since size is integer we shoud type cast address to character address
            convert_be_to_le(ptr1);   //function call for conversion.

            //to read 3 bytes of flag and '\0' and write it
            char flag[4];
            fread(flag, 3, 1, fp1);
            flag[3] = '\0';
            fwrite(flag, 3, 1, fp2);
            
            //to write new content         
            fwrite(argv[3], oglen - 1, 1, fp2);

            //to skip content size in sample.mp3
            fseek(fp1, size - 1, SEEK_CUR);

            //to copy rest of the file
            char ch;
            while (fread(&ch, 1, 1, fp1) == 1) 
            {
                fwrite(&ch, 1, 1, fp2);
            }

            fclose(fp1); //close sample.mp3
            fclose(fp2); //close temp.mp3

            remove(argv[4]);
            rename("temp.mp3", argv[4]);  // reaname the file..
            printf("------------------------%s Changed Successfully------------------------\n", tagname);
            exit(0);  //exits the program
        }
        else
        {
            //to read size
            int size;
            fread(&size, 4, 1, fp1);
            //to write size
            fwrite(&size, 4, 1, fp2);

            //to convert size to big endian.
            char* ptr = (char*)&size;  // since size is integer we shoud type cast address to character address
            convert_be_to_le(ptr);   //function call for conversion.

            //to read 3 bytes of flag and '\0'
            char flag[4];
            fread(flag, 3, 1, fp1);
            flag[3] = '\0';
            //to write flag
            fwrite(flag, 3, 1, fp2);

            //to read  size-1 bytes of content
            char content[size];
            fread(content, size - 1, 1, fp1);
            content[size - 1] = '\0';
            //to write tag
            fwrite(content, size - 1, 1, fp2);
        }
    }
}

void edittag_name(char* tag, char* edittag, char* tagname )   //function definition for edittag_name
{
    char TAGID[6][3] = {"-t", "-a", "-A", "-y", "-C", "-c"}; //tag modifiers
    char TAGS[6][5] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};  //tags
    char TAGSNAME[6][20] = {"Title", "Artist", "Album", "Year", "Music", "Comment"};  //tagname
    for(int i = 0; i < 6; i++)
    {
        if(!(strcmp(tag, TAGID[i])))  //to identify which tag to modify
        {
            strcpy(edittag, TAGS[i]);
            strcpy(tagname, TAGSNAME[i]);
            break;
        }
    }
}
