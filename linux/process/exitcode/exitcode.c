#include <stdlib.h>

int main(int argc, char **argv)
{
        if (argc < 2)
                exit(EXIT_FAILURE);
        exit(atoi(argv[1]));
        return 0;
}
