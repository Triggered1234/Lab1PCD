#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

// Funcție care inversează un șir de caractere
void reverse_string(char *str) {
    int start = 0;
    int end = strlen(str) - 1;
    char temp;
    
    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Funcție pentru a citi fișierul de intrare
char* read_file(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Eroare la deschiderea fișierului");
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(file_size + 1);
    if (!content) {
        perror("Eroare la alocarea memoriei");
        fclose(file);
        return NULL;
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';  // Asigură că șirul este terminat corect
    fclose(file);
    return content;
}

// Funcție pentru a scrie rezultatele într-un fișier
void write_file(const char* filename, const char* content) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Eroare la deschiderea fișierului pentru scriere");
        return;
    }
    
    fprintf(file, "%s", content);
    fclose(file);
}

void print_usage() {
    printf("Utilizare: ./app2 [opțiuni]\n");
    printf("Opțiuni:\n");
    printf("  -i, --input <fișier>   Specifică fișierul de intrare\n");
    printf("  -o, --output <fișier>  Specifică fișierul de ieșire\n");
    printf("  -p, --process           Activează procesarea (inversarea textului)\n");
    printf("  -v, --verbose           Activează modul detaliat\n");
    printf("  -h, --help              Afișează acest mesaj de ajutor\n");
}

int main(int argc, char *argv[]) {
    int verbose = 0;  // initializare pentru verbose
    char *input_file = NULL;
    char *output_file = NULL;
    int process = 0;

    static struct option long_options[] = {
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {"process", no_argument, 0, 'p'},
        {"verbose", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long_only(argc, argv, "i:o:pvh", long_options, NULL)) != -1) {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'p':
                process = 1;
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

    if (input_file == NULL || output_file == NULL) {
        printf("Eroare: Fișierele de intrare și ieșire sunt obligatorii.\n");
        print_usage();
        return 1;
    }

    // Citirea fișierului de intrare
    char *content = read_file(input_file);
    if (content == NULL) {
        return 1;
    }

    // Procesarea textului (dacă opțiunea -p este activată)
    if (process) {
        if (verbose) {
            printf("Procesăm textul... Inversăm conținutul.\n");
        }
        reverse_string(content);
    }

    // Scrierea rezultatelor în fișierul de ieșire
    write_file(output_file, content);

    if (verbose) {
        printf("Rezultatele au fost salvate în fișierul: %s\n", output_file);
    }

    // Curățarea memoriei
    free(content);

    return 0;
}
