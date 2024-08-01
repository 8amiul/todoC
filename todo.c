#include <stdio.h>
#include "todoc.h"
#include <string.h>
#include <stdlib.h>
#define FILENAME "todoc.Task"


int main(int argc, char *argv[])
{
    FILE* fp = fopen(FILENAME, "a+");
    
    //******ADD_TASK*******//
    if (argc > 2 && strcmp(argv[1], "add") == 0 && strlen(argv[2]) > 0)
    {
        char task[1024];
        strcpy(task, argv[2]);
        addTask(fp, task);
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
    if (argc == 4 && strcmp(argv[1], "edit") == 0)
    {
        char newLine[1024];
        strcpy(newLine, argv[3]);
        long targetLine = strtol(argv[2], NULL, 10);
        editTask(fp, targetLine, newLine);
        fp = fopen(FILENAME, "a+");
        printTask(fp);
    }
    fclose(fp);
    return 0;
}
