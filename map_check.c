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
            continue;
        }
    }
}
*/

static void point_check(char **map, int i, int j)
{
    if (map[i][j] == '0' && map[i][j] == '2')
    {
        if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
            map_err();
        if (map[i + 1][j + 1] == ' ' || map[i - 1][j - 1] == ' ')
            map_err();
        if (map[i - 1][j + 1] == ' ' || map[i + 1][j - 1] == ' ')
            map_err();
        if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
            map_err();
    }
}

void        check_col(char **map, int last)
{
    int i;
    int j;

    i = 0;
    j = 0;
    check_first_last(map[i++]);
    while(map[i] && map[i][j] && i < (last - 2))
    {
        //printf("//////%i///////////%i\n", i, last);
        while(map[i][j])
        {
            //printf("j = %i\n", j);
            point_check(map, i, j);
            j++;
        }
        j = 0;
        i++;
    }
    check_first_last(map[i]);
}

void        check_map(char **map, int last)
{
    //check_row(map, last);
   // printf("----------\n");
    check_col(map, last);
}