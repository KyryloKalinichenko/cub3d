#include "cub_head.h"

static void check_first(char *line)
{
    int i;

    i = -1; 
    while(line[++i])
    {
        if (line[i] != '1' || line[i] != ' ')
            map_err();
    }
}

static void check_mid(char *line)
{
    int i;

    i = -1; 
    while(line[++i])
    {
        if (line[i] == ' ')
            continue;
        
                 map_err();
    }
}

void        check_map(char **map, int last)
{
    int i;

    i = -1;
    while(map[++i])
    {
        if (!i)
            check_first(map[i]);
        if (i != last)
            check_mid(map[i]);
        if (i == last)
            check_last(map[i]);
    }
}