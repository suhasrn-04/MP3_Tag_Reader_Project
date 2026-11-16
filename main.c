#include <stdio.h>
#include "header.h"
#include "types.h"

int main(int argc ,char *argv[])
{
    MP3 mp3;

    if(check_operation_type(argv[1][1])==view) //1st 1=-v 2nd 1= v this check v
    {
        if(argc<2 && argc>3)
        {
            printf("Invalid input!!!\n");
            printf("Use: \n./a.out -v mp3filename( 'filename.mp3' )\n");
            return 0;
        }
        if(read_and_validate_view_args(argc,argv,&mp3) == success)
        {
            if(view_metadata(&mp3) == success)
            {
                printf("---------------------- END VIEW ----------------------\n");
            }
            else
            {
                printf("Invalid!!! \nCouldn't view the file!!!\n");
            }
        }
        else
        {
            printf("Invalid viewing arguments!!!\n");
        }
    }
    else if(check_operation_type(argv[1][1])==edit) //1st 1=-e 2nd 1= e this check e
    {
        if(argc<3 && argc>4)
        {
            printf("Invalid input!!!\n");
            printf("Use: \n./a.out -e -t/-a/-A/-m/-y/-c mp3filename( 'filename.mp3' )\n");
            return 0;
        }
        if(read_and_validate_edit_args(argc,argv,&mp3) == success)
        {
            if(edit_metadata(&mp3) == success)
            {
                printf("---------------------- DONE EDITING ----------------------\n");
            }
            else
            {
                printf("Invalid!!! \nCouldn't edit the file!!!\n");
            }
        }
        else
        {
            printf("Invalid editing arguments!!!\n");
        }
    }
    else
    {
        printf("Invalid input!!!... \nEntered arguments are invalid!\n");
    }

    return 0;
}

OperationType check_operation_type(char opt)
{
    if(opt == 'v')
    {
        printf("---------------------- VIEWING STARTED ----------------------\n");
        return view;

    }
    else if(opt == 'e')
    {
        printf("----------------------EDITING STARTED-------------------------\n");
        return edit;
    }
    else 
    {
        printf("Invalid input!!!\n");
        return unsupported;
    }
}