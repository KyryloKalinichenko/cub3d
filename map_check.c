#include "cub_head.h"

static void check_first_last(char *line)
{
    int i;

    i = -1; 
    while(line[++i] && (line[i] != '1' || line[i] != ' '))
        ;
    if (line[i]) 
        map_err();
    
}
/*
static int base_check(char *line, int i)
{
    while(line[i++])
    {
        if (line[i] == '1')
            continue;
        if (line[i] == '0' || line[i] == '2')
            continue;
        
    }
    return (i);
}
*/
static int skip_(char *line, int i, char to_skip)
{
    while(line[i])
    {
        if (line[i] == to_skip)
            i++;
        else
            break;
    }
    return (i);
}

static void check_mid(char *line)
{
    int i;
    int tmp;

    i = -1;
    while(line[++i])
    {
        if (line[i] == ' ')
            continue;
        else if (line[i] == '1')
        {
            i = skip_(line, i, '1');
            while(line[i] == '0' || line[i] == '2')
            {
                i = skip_(line, i, '0');
                i = skip_(line, i, '2');
                if (line[i] == '1')
                {
                    tmp = skip_(line, i, '1');
                    if (line[tmp] == '0' || line[tmp] == '2')
                    {
                        i = tmp;
                        continue;
                    }
                }
                else
                    map_err();
            }
           // while(line[i] == '1')
            //    i++;
            continue;
        }
        /*else
        {
            printf("%i\n", i);
            printf("%c\n", line[i]);
            map_err();
        }*/
    }
}

void        check_map(char **map, int last)
{
    int i;
    (void)last;

    i = -1;
    while(map[++i])
    {
        printf("%s\n", map[i]);
        if (!i)
        {
            check_first_last(map[i]);
            continue;
        }
        check_mid(map[i]);
        //if (i == last)
          //  check_first_last(map[i]);
    }
}