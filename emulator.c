#include "shell.h"

/**
 * custom_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status (0) if info.argv[0] != "exit"
 */
int custom_exit(info_t *info)
{
    int exitcheck;

    if (info->argv[1])  /* If there is an exit argument */
    {
        exitcheck = custom_erratoi(info->argv[1]);
        if (exitcheck == -1)
        {
            info->status = 2;
            custom_print_error(info, "Illegal number: ");
            custom_eputs(info->argv[1]);
            custom_eputchar('\n');
            return (1);
        }
        info->err_num = custom_erratoi(info->argv[1]);
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * custom_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int custom_cd(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        custom_puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        dir = custom_getenv(info, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = custom_getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (custom_strcmp(info->argv[1], "-") == 0)
    {
        if (!custom_getenv(info, "OLDPWD="))
        {
            custom_puts(s);
            custom_putchar('\n');
            return (1);
        }
        custom_puts(custom_getenv(info, "OLDPWD=")), custom_putchar('\n');
        chdir_ret = chdir((dir = custom_getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        custom_print_error(info, "can't cd to ");
        custom_eputs(info->argv[1]), custom_eputchar('\n');
    }
    else
    {
        custom_setenv(info, "OLDPWD", custom_getenv(info, "PWD="));
        custom_setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * custom_help - displays help information
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int custom_help(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    custom_puts("help call works. Function not yet implemented \n");
    if (0)
        custom_puts(*arg_array); /* temp att_unused workaround */
    return (0);
}

/**
 * custom_history - displays the history list, one command by line, preceded
 *                 with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int custom_history(info_t *info)
{
    custom_print_list(info->history);
    return (0);
}

/**
 * custom_unset_alias - unsets an alias
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int custom_unset_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = custom_strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = custom_delete_node_at_index(&(info->alias),
                                      custom_get_node_index(info->alias, custom_node_starts_with(info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * custom_set_alias - sets an alias
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int custom_set_alias(info_t *info, char *str)
{
    char *p;

    p = custom_strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (custom_unset_alias(info, str));

    custom_unset_alias(info, str);
    return (custom_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * custom_print_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int custom_print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = custom_strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            custom_putchar(*a);
        custom_putchar('\'');
        custom_puts(p + 1);
        custom_puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * custom_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int custom_alias(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            custom_print_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        p = custom_strchr(info->argv[i], '=');
        if (p)
            custom_set_alias(info, info->argv[i]);
        else
            custom_print_alias(custom_node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}

