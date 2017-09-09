#include <iostream>
#include <sys/stat.h>

struct Header {

};

int main(int argc, char *argv[]) {

    struct stat sb;

    if (argc < 2) {
        fprintf(stderr, "You did not provide program name.\n");
        exit(1);
    }

    if (stat(argv[2], &sb) == 0 && S_ISREG(sb.st_mode))
    {
        printf("It's a file");
    }

    return 0;
}