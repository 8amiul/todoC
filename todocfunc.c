#include <stdio.h>
#include "todoc.h"
#include <string.h>
#define FILENAME "todoc.Task"
#define TMPFILE "todoc.TMP"

void printTask(FILE *file)
{
    printf("[TodoC]\n");
    char buff[1024];
    while (fgets(buff, sizeof(buff), file) != NULL)
    {
        char mark;
        char task[1024];
        sscanf(buff, "%c,%s", &mark, task);
        printf("[%c] %s\n", mark, task);
    }
}

void addTask(FILE *file, char *task)
{
    fprintf(file, "%c,%s\n", ' ', task);
    fclose(file);
}

void markTask(FILE *file, int targetLine)
{
    FILE* temp = fopen(TMPFILE, "w");

    char line[1024];
    int currentLine = 1;
    while(fgets(line, sizeof(line), file) != NULL)
    {
        if (currentLine == targetLine)
        {
            if (line[0] != '\0' && line[0] != '*')
                line[0] = '*';
            else
                line[0] = ' ';
        }
        currentLine++;
        fputs(line, temp);
    }
    fclose(file);
    fclose(temp);

    int rF = remove(FILENAME);
    int renameF = rename(TMPFILE, FILENAME);
}

void delTask(FILE* file, int targetLine)
{
    FILE* temp = fopen(TMPFILE, "w");

    char line[1024];
    int currentLine = 1;
    while(fgets(line, sizeof(line), file) != NULL)
    {
        if (currentLine != targetLine)
        {
            fputs(line, temp);
        }
        currentLine++;
    }
    fclose(file);
    fclose(temp);

    int rF = remove(FILENAME);
    int renameF = rename(TMPFILE, FILENAME);


}
