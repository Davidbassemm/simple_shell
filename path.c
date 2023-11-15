#include "shell.h"

/**
 * isExecutable - checks if a file is an executable command
 * @info: information structure
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isExecutable(info_t *info, char *path)
{
    struct stat fileStat;

    (void)info;
    if (!path || stat(path, &fileStat))
        return 0;

    return S_ISREG(fileStat.st_mode);
}

/**
 * copySubstring - copies a substring from a string
 * @source: source string
 * @start: starting index
 * @end: ending index
 *
 * Return: pointer to the new buffer
 */
char *copySubstring(char *source, int start, int end)
{
    static char buffer[1024];
    int bufferIndex = 0;

    for (int i = start; i < end; i++)
    {
        if (source[i] != ':')
            buffer[bufferIndex++] = source[i];
    }

    buffer[bufferIndex] = '\0';
    return buffer;
}

/**
 * findCommandInPath - finds the command in the PATH string
 * @info: information structure
 * @pathStr: the PATH string
 * @command: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *findCommandInPath(info_t *info, char *pathStr, char *command)
{
    int currentIndex = 0;
    char *path;

    if (!pathStr)
        return NULL;

    if ((_strlen(command) > 2) && starts_with(command, "./"))
    {
        if (isExecutable(info, command))
            return command;
    }

    for (int i = 0; ; i++)
    {
        if (!pathStr[i] || pathStr[i] == ':')
        {
            path = copySubstring(pathStr, currentIndex, i);
            if (!*path)
                _strcat(path, command);
            else
            {
                _strcat(path, "/");
                _strcat(path, command);
            }

            if (isExecutable(info, path))
                return path;

            if (!pathStr[i])
                break;

            currentIndex = i;
        }
    }

    return NULL;
}
