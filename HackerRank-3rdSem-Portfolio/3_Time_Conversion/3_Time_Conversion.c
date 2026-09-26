#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline();

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */
char *timeConversion(char *s)
{
    // Allocate exactly 9 bytes for the 8-character time string plus the null terminator
    char *result = (char *)malloc(9 * sizeof(char));

    // Copy the hh:mm:ss portion into our result string
    strncpy(result, s, 8);
    result[8] = '\0';

    // Convert the first two characters to an integer for the hour
    int hh = (s[0] - '0') * 10 + (s[1] - '0');

    // Check if it's PM and not 12, or AM and 12
    if (s[8] == 'P' && hh != 12)
    {
        hh += 12;
    }
    else if (s[8] == 'A' && hh == 12)
    {
        hh = 0;
    }

    // Convert the calculated hour back into characters
    result[0] = (hh / 10) + '0';
    result[1] = (hh % 10) + '0';

    return result;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char *s = readline();

    char *result = timeConversion(s);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}

char *readline()
{
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char *data = malloc(alloc_length);

    while (true)
    {
        char *cursor = data + data_length;
        char *line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line)
        {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n')
        {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data)
        {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n')
    {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data)
        {
            data = '\0';
        }
    }
    else
    {
        data = realloc(data, data_length + 1);

        if (!data)
        {
            data = '\0';
        }
        else
        {
            data[data_length] = '\0';
        }
    }

    return data;
}