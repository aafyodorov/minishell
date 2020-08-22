#include <unistd.h>

int main(int ac, char **av) {
    char *adr = "bin/";
    execve("echo", &av[1], &adr);
}