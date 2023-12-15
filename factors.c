#include <stdio.h>
#include <stdlib.h>

void factorize(FILE *file);

int main(int argc, char *argv[])
{
    FILE *file;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    factorize(file);

    fclose(file);
    return EXIT_SUCCESS;
}

void factorize(FILE *file)
{
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        /* Convert the string to an integer */
        unsigned long num = strtoul(line, NULL, 10);
	unsigned long i = 0;

        if (num == 0 && line[0] != '0')
        {
            fprintf(stderr, "Error: Invalid number in the file\n");
            exit(EXIT_FAILURE);
        }

        printf("%lu=", num);

        /* Find the factors */
        for (i = 2; i <= num / 2; ++i)
        {
            if (num % i == 0)
            {
                printf("%lu*%lu\n", i, num / i);
                break;
            }
        }
    }
}

