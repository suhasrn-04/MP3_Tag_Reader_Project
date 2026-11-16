#include <stdio.h>
#include "types.h"
#include "header.h"
#include <string.h>
#include <stdlib.h>



Status read_and_validate_edit_args(int argc, char *argv[], MP3 *mp3)
{
    printf("Validating editing arguments!!!\n");

    if(argv[2][1] == 't')
    {

    }
    else if(argv[2][1] == 'a')
    {

    }
    else if(argv[2][1] == 'A')
    {

    }
    else if(argv[2][1] == 'm')
    {

    }
    else if(argv[2][1] == 'y')
    {

    }
    else if(argv[2][1] == 'c')
    {

    }
    else 
    {
        printf("Invalid editing arguments!!!\n");
            printf("Use: \n./a.out -v -t/-a/-A/-m/-y/-c mp3filename( 'filename.mp3' )\n");
        return failure;
    }

    return success;
}

Status edit_metadata(MP3 *mp3)
{

    
    return success;
}