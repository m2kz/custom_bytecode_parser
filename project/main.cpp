#include <iostream>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <errno.h>

struct Header {

};

int main(int argc, char *argv[]) {

    struct stat sb;

    if (argc < 2) {
        fprintf(stderr, "You did not provide program name.\n");
        exit(1);
    }

    std::string emv_file_path(argv[1]);


    if (stat(emv_file_path.c_str(), &sb) == 0 && S_ISREG(sb.st_mode))
    {
        printf("It's a file");
    }

    return 0;
}