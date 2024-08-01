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
        sscanf(buff, "%c", &mark);
        printf("[%c] ", mark);
        for (int i = 2; buff[i] != '\0'; i++)
            printf("%c", buff[i]);
        printf("\n");
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

void editTask(FILE* file, int targetLine, char *newLine)
{
    FILE* temp = fopen(TMPFILE, "w");

    char line[1024];
    char tmpNewLine[1024];
    int currentLine = 1;
    while(fgets(line, sizeof(line), file) != NULL)
    {
       if (currentLine == targetLine)
        {        
            strncpy(tmpNewLine, line, 2);
            strcat(tmpNewLine, newLine);
            strcat(tmpNewLine, "\n");
            fputs(tmpNewLine, temp);
            currentLine++;
            continue;
        }
        fputs(line, temp);
        currentLine++;
    }
    fclose(file);
    fclose(temp);
    remove(FILENAME);
    rename(TMPFILE, FILENAME);
}
