#include "shell.h"

/**
 * printString - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void printStringToStderr(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        printCharToStderr(str[i]);
        i++;
    }
}

/**
 * printCharToStderr - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int printCharToStderr(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return 1;
}

/**
 * printCharToFD - writes the character c to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int printCharToFD(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return 1;
}

/**
 * printStringToFD - prints an input string to a given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int printStringToFD(char *str, int fd)
{
    int i = 0;

    if (!str)
        return 0;

    while (*str)
    {
        i += printCharToFD(*str++, fd);
    }

    return i;
}
