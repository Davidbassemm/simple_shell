#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @str: The input string.
 * Return: The length of the string.
 */
size_t _strlen(const char *str)
{
    size_t len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: 0 if strings are equal, positive if s1 > s2, negative if s1 < s2.
 */
int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 * Return: A pointer to the concatenated string (dest).
 */
char *_strcat(char *dest, const char *src)
{
    size_t dest_len = _strlen(dest);
    size_t i;

    for (i = 0; src[i] != '\0'; i++)
        dest[dest_len + i] = src[i];

    dest[dest_len + i] = '\0';
    return dest;
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 * Return: A pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
    size_t len = _strlen(str) + 1;
    char *dup_str = malloc(len);

    if (dup_str != NULL)
        _strcpy(dup_str, str);

    return dup_str;
}

/**
 * _strcpy - Copies a string.
 * @dest: The destination string.
 * @src: The source string.
 * Return: A pointer to the copied string (dest).
 */
char *_strcpy(char *dest, const char *src)
{
    size_t i;

    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];

    dest[i] = '\0';
    return dest;
}
