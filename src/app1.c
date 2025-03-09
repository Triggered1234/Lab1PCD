#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

void print_usage() {
    printf("Utilizare: ./app1 [opțiuni]\n");
    printf("Opțiuni:\n");
    printf("  -n, --name <nume>     Furnizează un nume (necesar pentru procesare)\n");
    printf("  -a, --age <vârstă>    Furnizează vârsta (opțional, dar necesită o valoare)\n");
    printf("  -v, --verbose         Activează modul detaliat\n");
    printf("  -h, --help            Afișează acest mesaj de ajutor\n");
}

int main(int argc, char *argv[]) {
    int verbose = 0;
    char *name = NULL;
    int age = -1;

    // Definirea opțiunilor lungi
    static struct option long_options[] = {
        {"name", required_argument, 0, 'n'},
        {"age", required_argument, 0, 'a'},
        {"verbose", no_argument, 0, 'v'},  // Use 'v' as value
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}  // Sfârșitul listei de opțiuni
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "n:a:vh", long_options, NULL)) != -1) {
        switch (opt) {
            case 'n':
                name = optarg;
                break;
            case 'a':
                age = atoi(optarg);
                break;
            case 'v':
                verbose = 1;
                break;
            case 'h':
                print_usage();
                return 0;
            default:
                print_usage();
                return 1;
        }
    }

    // Verificarea argumentelor obligatorii
    if (name == NULL) {
        printf("Eroare: Numele este obligatoriu.\n");
        print_usage();
        return 1;
    }

    // Afișarea rezultatelor pe baza argumentelor procesate
    printf("Bună, %s!\n", name);
    if (age != -1) {
        printf("Ai %d ani.\n", age);
    }
    
    if (verbose) {
        printf("Modul detaliat activat.\n");
    }

    return 0;
}
