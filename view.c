#include <stdio.h>
#include "types.h"
#include "header.h"
#include <string.h>
#include <stdlib.h>

Status read_and_validate_view_args(int argc, char *argv[], MP3 *mp3)
{
    printf("Validating viewing arguments!!!\n");
    if(argv[2] == NULL)
    {
        printf("Error -> Soure file name not found.\n");
        return failure;
    }
    else if (strstr(argv[2], ".mp3") == NULL)
    {
        printf("Error -> Source file must have a .mp3 extension.\n");
        return failure;
    }
    else if(strlen(argv[2]) < 4 || strcmp(argv[2] + strlen(argv[2]) - 4, ".mp3") != 0)
    {
        printf("Error -> Invalid source file name.\n");
        return failure;
    }
    else
    {
        mp3->mp3_fname = argv[2];
    }

    mp3->fptr_mp3 = fopen(argv[2],"rb");
    if(mp3->fptr_mp3 == NULL)
    {
        printf("Error -> Unable to open Source file.\n");
        return failure;
    }

    return success;
}

Status check_mp3_header(FILE *fptr)
{
    char buff[4];

    // read 3 bytes of mp3 header
    fread(buff, 1, 3, fptr);
    buff[3]='\0';

    if(strcmp(buff, "ID3") == 0)
    {
        printf("ID3 tag found!\n");
    }
    else
    {
        printf("ID3 tag not found!\n");
        return failure;
    }

    //skip 7 bytes of mp3 header
    fseek(fptr, 7, SEEK_CUR);

    return success;
}

Status view_metadata(MP3 *mp3) //display content of mp3 file
{
    //skip 10 bytes of mp3 header
    if(check_mp3_header(mp3->fptr_mp3) == failure)
    {
        printf("Error -> Failed to skip 10 bytes of mp3 header\n");
        return failure;
    }


    int i,size;
    char buff[5];
    char *data;
    printf("\n===========================================================\n");
    printf("                        MP3 TAG READER                     \n");
    printf("===========================================================\n");
    printf("                        SONG DETAILS                       \n");
    printf("-----------------------------------------------------------\n");
    for(i=0;i<6;i++)
    {
        // read 4 bytes from file
        fread(buff, 1, 4, mp3->fptr_mp3);
        buff[4] ='\0';

        // convert size into little endianess
        if(endianess(mp3, &size) == failure)
        {
            printf("Error -> Unable to convert size into little endianess!!\n");
            return failure;
        }

        if(size<=0)
        {
            printf("Error -> Invalid frame size!!\n");
            return failure;
        }

        //skip 2 bytes of flag and 1 byte of null char in data
        fseek(mp3->fptr_mp3, 3, SEEK_CUR);

        data= malloc(size);
        if(data == NULL)
        {
            printf("Error -> Couldn't allocate memory for data!!\n");
            return failure;
        }


        // read size-1 bytes of metedata
        fread(data,1,size-1,mp3->fptr_mp3);
        data[size-1]='\0';

        // display meta data
        if(strcmp(buff, "TPE1") == 0)
        {
            printf("%-15s : %s\n","Artist Name",data);
        }
        else if(strcmp(buff, "TIT2") == 0)
        {
            printf("%-15s : %s\n","Title Name",data);
        }
        else if(strcmp(buff, "TALB") == 0)
        {
            printf("%-15s : %s\n","Album",data);
        }
        else if(strcmp(buff, "TYER") == 0)
        {
            printf("%-15s : %s\n","Year",data);
        }
        else if(strcmp(buff, "TCON") == 0)
        {
            printf("%-15s : %s\n","Content Type",data);
        }
        else if(strcmp(buff, "COMM") == 0)
        {
            printf("%-15s : %s\n","Comments",data);
        }
        else if(strcmp(buff, "TCOM") == 0)
        {
            printf("%-15s : %s\n","Composer Name",data);
        }
        else 
        {
            printf("%-15s : %.4s\n","Unknown frame",data);
        }
        free(data);
    }

    printf("-----------------------------------------------------------\n");
    printf("                        END VIEW                           \n");
    printf("===========================================================\n");

    return success;
}

Status endianess(MP3 *mp3, int *size)
{
    unsigned char buff[4];
    unsigned char temp;

    // read 4 bytes of size
    fread(buff,1,4,mp3->fptr_mp3);
    
    //converting from big endian to little endian by swapping  
    temp = buff[0];
    buff[0] = buff[3];
    buff[3] = temp;

    temp=buff[1];
    buff[1] = buff[2];
    buff[2] = temp;

    //convert reversed byte into integer
    *size= *(int  *)buff;

    return success;
}