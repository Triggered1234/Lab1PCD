/*
 * Nume: Adrian-Petru Enache
 * Subgrupa: IR3 Subgrupa 4
 * Descriere: Acest program proceseaza un fisier text: citeste continutul dintr-un fisier de intrare, 
 * poate inversa textul si il scrie intr-un fisier de iesire.
 * Optiunea "-h" afiseaza ajutorul.
 */

 #include <stdio.h>  // pentru printf
 #include <stdlib.h> // pentru functiile standard, inclusiv malloc pentru alocarea memoriei
 #include <getopt.h> // pentru functia getopt_long care ajuta la procesarea argumentelor de linie de comanda
 #include <string.h> // pentru functiile de manipulare a sirurilor de caractere
 
  // Functia care inverseaza un sir de caractere.
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
 
 /*
  * Functia care citeste un fisier si returneaza continutul acestuia sub forma de sir de caractere.
  * Daca fisierul nu poate fi deschis, va afisa un mesaj de eroare.
  */
 char* read_file(const char* filename) {
     FILE *file = fopen(filename, "r");
     if (!file) {
         perror("Eroare la deschiderea fisierului");
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
     content[file_size] = '\0';  // Asigura ca sirul este terminat corect
     fclose(file);
     return content;
 }
 
 /*
  * Functia pentru a scrie rezultatele intr-un fisier.
  * Daca fisierul nu poate fi deschis pentru scriere, va afisa un mesaj de eroare.
  */
 void write_file(const char* filename, const char* content) {
     FILE *file = fopen(filename, "w");
     if (!file) {
         perror("Eroare la deschiderea fisierului pentru scriere");
         return;
     }
     
     fprintf(file, "%s", content);
     fclose(file);
 }
 
 /*
  * Functia care afiseaza informatiile de utilizare a programului.
  */
 void print_usage() {
     printf("Utilizare: ./app2 [optimi]\n");
     printf("Optiuni:\n");
     printf("  -i, --input <fisier>   Specifica fisierul de intrare\n");
     printf("  -o, --output <fisier>  Specifica fisierul de iesire\n");
     printf("  -p, --process           Activeaza procesarea (inversarea textului)\n");
     printf("  -v, --verbose           Activeaza modul detaliat\n");
     printf("  -h, --help              Afiseaza acest mesaj de ajutor\n");
 }
 
 int main(int argc, char *argv[]) {
     int verbose = 0;  // initializare pentru verbose
     char *input_file = NULL;
     char *output_file = NULL;
     int process = 0;  // initializare pentru procesare (inversare text)
 
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
 
     // Verificam daca fisierele de intrare si iesire sunt specificate
     if (input_file == NULL || output_file == NULL) {
         printf("Eroare: Fisierele de intrare si iesire sunt obligatorii.\n");
         print_usage();
         return 1;
     }
 
     // Citirea fisierului de intrare
     char *content = read_file(input_file);
     if (content == NULL) {
         return 1;
     }
 
     // Procesarea textului (inversarea continutului)
     if (process) {
         if (verbose) {
             printf("Procesam textul... Inversam continutul.\n");
         }
         reverse_string(content);
     }
 
     // Scrierea rezultatelor in fisierul de iesire
     write_file(output_file, content);
 
     if (verbose) {
         printf("Rezultatele au fost salvate in fisierul: %s\n", output_file);
     }
 
     // Curatarea memoriei alocate
     free(content);
 
     return 0;
 }
 
 // Rulari care produc erori:
 // 1. ./app2 -i "input.txt" (fara a specifica fisierul de iesire) -> Eroare: Fisierele de intrare si iesire sunt obligatorii.
 // 2. ./app2 -i "input.txt" -o "output.txt" (consideram ca input.txt si/sau output.txt nu exista, astfel va afisa eroare de file not found)
 
 // Rulare care produce stare de succes:
 // ./app2 -i "input.txt" -o "output.txt" -p -> Se citeste fisierul de intrare, se proceseaza textul (inversare) si se scrie in fisierul de iesire.
 