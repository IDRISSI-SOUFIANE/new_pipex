#include "../include/pipex.h"

static size_t    word_count(char const *s, char sep)
{
    size_t    i;
    size_t    wc;

    i = 0;
    wc = 0;
    while (s[i])
    {
        while (s[i] && s[i] == sep)
            i++;
        if (s[i] && s[i] != sep)
        {
            wc++;
            if (s[i] == '\'')
            {
                i++;
                while(s[i] && s[i] != '\'')
                    i++;
            }
            while (s[i] && s[i] != sep)
                i++;
        }
    }
    return (wc);
}

char    **ft_free(char **arr, size_t n)
{
    size_t    i;

    i = 0;
    while (i < n)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
    return (NULL);
}

static char    *ft_allocate(const char *s, char end)
{
    size_t    len;
    char    *str;
    size_t    i;

    len = 0;
    while (s[len] && s[len] != end)
        len++;
    str = malloc(len + 1);
    if (str == NULL)
        return (NULL);
    i = 0;
    while (i < len)
    {
        str[i] = s[i];
        i++;
    }
    str[len] = '\0';
    return (str);
}



static int    handle_word(const char **s_ptr, char **arr, size_t *i, char sep)
{
    const char    *s;
    char        end_char;

    s = *s_ptr;
    if (*s == '\'')
    {
        s++;
        end_char = '\'';
    }
    else
        end_char = sep;
    arr[*i] = ft_allocate(s, end_char);
    if (arr[*i] == NULL)
        return (-1);
    while (*s && *s != end_char)
        s++;
    *s_ptr = s;
    if (*s == '\'')
        (*s_ptr)++;
    (*i)++;
    return (0);
}

char    **ft_split(char const *s, char sep)
{
    char    **arr;
    size_t    i;

    if (s == NULL)
        return (NULL);
    arr = malloc(sizeof(char *) * (word_count(s, sep) + 1));
    if (arr == NULL)
        return (NULL);
    i = 0;
    while (*s)
    {
        while (*s && *s == sep)
            s++;
        if (*s && *s != sep)
        {
            if (handle_word(&s, arr, &i, sep) != 0)
                return (ft_free(arr, i));
        }
    }
    arr[i] = NULL;
    return (arr);
}

