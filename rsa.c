#include <stdio.h>
#include <stdlib.h>

unsigned long gcd(unsigned long a, unsigned long b)
{
    while (b != 0)
    {
        unsigned long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long pollards_rho(unsigned long n)
{
    unsigned long x = 2, y = 2, d = 1;

    while (d == 1)
    {
        x = (x * x + 1) % n;
        y = ((y * y + 1) % n * (y * y + 1) % n + 1) % n;
        d = gcd((x > y) ? (x - y) : (y - x), n);
    }

    return d;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char line[256];

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

    while (fgets(line, sizeof(line), file) != NULL)
    {
        unsigned long n = strtoul(line, NULL, 10);

        if (n == 0 && line[0] != '0')
        {
            fprintf(stderr, "Error: Invalid number in the file\n");
            exit(EXIT_FAILURE);
        }

        printf("%lu=", n);

        while (n > 1)
        {
            unsigned long factor = pollards_rho(n);
            printf("%lu", factor);

            n /= factor;

            if (n > 1)
                printf("*");
        }

        printf("\n");
    }

    fclose(file);
    return EXIT_SUCCESS;
}

