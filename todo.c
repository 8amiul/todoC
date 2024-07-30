#include <stdio.h>
#include "todoc.h"
#include <string.h>
#include <stdlib.h>
#define FILENAME "todoc.Task"


int main(int argc, char *argv[])
{
    FILE* fp = fopen(FILENAME, "a+");
    
    //******ADD_TASK*******//
    if (argc == 3 && strcmp(argv[1], "add") == 0 && strlen(argv[2]) > 0)
    {
        addTask(fp, argv[2]);
        fp = fopen(FILENAME, "a+");
        printTask(fp);
    }
    //******MARK_TASK*****//
    if (argc == 3 && strcmp(argv[1], "x") == 0)
    {
        long targetLine = strtol(argv[2], NULL, 10);
        markTask(fp, targetLine);
        fp = fopen(FILENAME, "a+");
        printTask(fp);
    }

    //*****PRINT_TASK*****//
    if (argc == 1)
        printTask(fp);
    
    //*****DEL_TASK******//
    if (argc == 3 && strcmp(argv[1], "del") == 0)
    {
        long targetLine = strtol(argv[2], NULL, 10);
        delTask(fp, targetLine);
        fp = fopen(FILENAME, "a+");
        printTask(fp);
    }
    fclose(fp);
    return 0;
}
