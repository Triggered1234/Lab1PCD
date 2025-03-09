/*
 * Nume: Adrian-Petru Enache
 * Subgrupa: IR3 Subgrupa 4
 * Descriere: Acest program este o aplicatie simpla ce acceptă argumente pe linia de comandă
 * si le proceseaza. Utilizatorul trebuie să furnizeze un nume, iar varsta este optionala.
 * Optiunea "-h" afisează ajutorul.
 */

#include <stdio.h> // pentru printf
#include <stdlib.h> // pentru functiile standard, in special pentru conversia argumentului la int (atoi)
#include <getopt.h> // pentru functia getopt_long care ajută la procesarea argumentelor pe linia de comandă

void print_usage() {
    printf("Utilizare: ./app1 [opțiuni]\n");
    printf("Opțiuni:\n");
    printf("  -n, --name <nume>     Furnizează un nume (necesar pentru procesare)\n");
    printf("  -a, --age <vârstă>    Furnizează vârsta (opțional)\n");
    printf("  -v, --verbose         Se va printa un mesaj\n");
    printf("  -h, --help            Afișează indicatiile pentru utilizarea aplicatiei\n");
}

int main(int argc, char *argv[]) {
    int verbose = 0;
    char *name = NULL;
    int age = -1;

    static struct option long_options[] = {
        {"name", required_argument, 0, 'n'},
        {"age", required_argument, 0, 'a'},
        {"verbose", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    // getopt_long(): folosita pentru a analiza argumentele de linie de comanda.
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

    if (name == NULL) { // Dacă nu se furnizează un nume (optiunea -n), programul va afisa un mesaj de eroare deoarece acesta este obligatoriu.
        printf("Eroare: Numele este obligatoriu.\n");
        print_usage();
        return 1;
    }

    printf("Bună, %s!\n", name);
    if (age != -1) {
        printf("Ai %d ani.\n", age);
    }
    
    if (verbose) {
        printf("Verbose activat\n");
    }

    return 0;
}


// Rulare care produce erori: ./app1 -a "21"
// Rularri care produc stare de succes: ./app1 -n "Adrian Enache" -a "21"