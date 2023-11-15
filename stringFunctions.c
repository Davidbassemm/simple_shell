#include "shell.h"

#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\0'

/**
 * strLength - returns the length of a string
 * @str: the string to check
 *
 * Return: integer length of the string
 */
int strLength(char *str)
{
    int length = 0;

    if (!str)
        return 0;

    while (*str++)
        length++;

    return length;
}

/**
 * strCompare - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int strCompare(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }

    return 0;
}

/**
 * isDelimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delimiters: the string containing delimiters
 *
 * Return: 1 if c is a delimiter, 0 otherwise
 */
int isDelimiter(char c, char *delimiters)
{
    while (*delimiters)
    {
        if (*delimiters == c)
            return 1;
        delimiters++;
    }
    return 0;
}

/**
 * startsWith - checks if a string starts with another string
 * @haystack: the string to search
 * @needle: the substring to find
 *
 * Return: pointer to the next character of haystack or NULL
 */
char *startsWith(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return NULL;
    return (char *)haystack;
}

/**
 * stringCat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *stringCat(char *dest, char *src)
{
    char *result = dest;

    while (*dest)
        dest++;

    while (*src)
        *dest++ = *src++;

    *dest = *src;
    return result;
}

/**
 * stringCopy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *stringCopy(char *dest, char *src)
{
    int i = 0;

    if (dest == src || src == 0)
        return dest;

    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return dest;
}

/**
 * stringDuplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *stringDuplicate(const char *str)
{
    int length = 0;
    char *duplicate;

    if (str == NULL)
        return NULL;

    while (*str++)
        length++;

    duplicate = malloc((length + 1) * sizeof(char));

    if (!duplicate)
        return NULL;

    for (length++; length--;)
        duplicate[length] = *--str;

    return duplicate;
}

/**
 * stringPut - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void stringPut(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        putChar(str[i]);
        i++;
    }
}

/**
 * putChar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int putChar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return 1;
}

/**
 * stringNCopy - copies n characters from source to destination
 * @dest: destination string
 * @src: source string
 * @n: number of characters to copy
 *
 * Return: pointer to the destination buffer
 */
char *stringNCopy(char *dest, char *src, int n)
{
    int i, j;
    char *result = dest;

    i = 0;

    while (src[i] != '\0' && i < n - 1)
    {
        dest[i] = src[i];
        i++;
    }

    if (i < n)
    {
        j = i;

        while (j < n)
        {
            dest[j] = '\0';
            j++;
        }
    }

    return result;
}

/**
 * stringNCat - concatenates n characters from source to destination
 * @dest: the first string
 * @src: the second string
 * @n: the maximum number of bytes to use
 *
 * Return: pointer to the concatenated string
 */
char *stringNCat(char *dest, char *src, int n)
{
    int i, j;
    char *result = dest;

    i = 0;
    j = 0;

    while (dest[i] != '\0')
        i++;

    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    if (j < n)
        dest[i] = '\0';

    return result;
}

/**
 * stringChr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 *
 * Return: pointer to the memory area s
 */
char *stringChr(char *s, char c)
{
    do
    {
        if (*s == c)
            return s;
    } while (*s++ != '\0');

    return NULL;
}

/**
 * stringSplit - splits a string into words
 * @str: the input string
 * @delimiters: the delimiter string
 *
 * Return: pointer to an array of strings, or NULL on failure
 */
char **stringSplit(char *str, char *delimiters)
{
    int i, j, k, m, numWords = 0;
    char **result;

    if (str == NULL || str[0] == '\0')
        return NULL;

    if (!delimiters)
        delimiters = " ";

    for (i = 0; str[i] != '\0'; i++)
        if (!isDelimiter(str[i], delimiters) && (isDelimiter(str[i + 1], delimiters) || !str[i + 1]))
            numWords++;

    if (numWords == 0)
        return NULL;

    result = malloc((1 + numWords) * sizeof(char *));
    if (!result)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++)
    {
        while (isDelimiter(str[i], delimiters))
            i++;

        k = 0;

        while (!isDelimiter(str[i + k], delimiters) && str[i + k])
            k++;

        result[j] = malloc((k + 1) * sizeof(char));

        if (!result[j])
        {
            for (k = 0; k < j; k++)
                free(result[k]);
            free(result);
            return NULL;
        }

        for (m = 0; m < k; m++)
            result[j][m] = str[i++];

        result[j][m] = '\0';
    }

    result[j] = NULL;
    return result;
}

/**
 * stringSplit2 - splits a string into words
 * @str: the input string
 * @delimiter: the delimiter
 *
 * Return: pointer to an array of strings, or NULL on failure
 */
char **stringSplit2(char *str, char delimiter)
{
    int i, j, k, m, numWords = 0;
    char **result;

    if (str == NULL || str[0] == '\0')
        return NULL;

    for (i = 0; str[i] != '\0'; i++)
        if ((str[i] != delimiter && str[i + 1] == delimiter) ||
            (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
            numWords++;

    if (numWords == 0)
        return NULL;

    result = malloc((1 + numWords) * sizeof(char *));
    if (!result)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++)
    {
        while (str[i] == delimiter && str[i] != delimiter)
            i++;

        k = 0;

        while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
            k++;

        result[j] = malloc((k + 1) * sizeof(char));

        if (!result[j])
        {
            for (k = 0; k < j; k++)
                free(result[k]);
            free(result);
            return NULL;
        }

        for (m = 0; m < k; m++)
            result[j][m] = str[i++];

        result[j][m] = '\0';
    }

    result[j] = NULL;
    return result;
}
