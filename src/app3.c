/*
 * Nume: Adrian-Petru Enache
 * Subgrupa: IR3 Subgrupa 4
 * Descriere: Acest program face o cerere HTTP simpla folosind cURL la un URL specificat de utilizator.
 * De asemenea, poate sa afiseze versiunea aplicatiei sau ajutorul.
 * Optiunea "-h" afiseaza ajutorul, iar optiunea "-v" afiseaza versiunea aplicatiei.
 * Optiunea "-u" este folosita pentru a specifica URL-ul care va fi accesat.
 */

 #include <stdio.h>  // pentru printf
 #include <stdlib.h> // pentru functii standard
 #include <getopt.h> // pentru getopt_long
 #include <curl/curl.h> // pentru operatiuni HTTP cu cURL
 
  // Functia care afiseaza mesajul de utilizare.
 void print_usage() {
     printf("Utilizare: app3 [optimi]\n");
     printf("Optiuni:\n");
     printf("  -h, --help           Afiseaza acest mesaj de ajutor\n");
     printf("  -v, --version        Afiseaza versiunea aplicatiei\n");
     printf("  -u, --url URL        Specifica URL-ul de accesat\n");
 }
 
 int main(int argc, char *argv[]) {
     int option;
     char *url = NULL;
 
     struct option long_options[] = {
         {"help",    no_argument,       0, 'h'},
         {"version", no_argument,       0, 'v'},
         {"url",     required_argument, 0, 'u'},
         {0, 0, 0, 0}
     };
 
     // Procesarea argumentelor de linie de comanda
     while ((option = getopt_long(argc, argv, "hv:u:", long_options, NULL)) != -1) {
         switch (option) {
             case 'h':
                 print_usage();
                 return 0;
             case 'v':
                 printf("App3 Versiunea 1.0\n");
                 return 0;
             case 'u':
                 url = optarg;
                 break;
             default:
                 print_usage();
                 return 1;
         }
     }
 
     // Verificam daca URL-ul a fost furnizat
     if (url == NULL) {
         fprintf(stderr, "Eroare: Trebuie sa specifici un URL.\n");
         print_usage();
         return 1;
     }
 
     CURL *curl;
     CURLcode res;
     long http_code = 0;
 
     // Initializare cURL
     if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) {
         fprintf(stderr, "Eroare: curl_global_init a esuat\n");
         return 1;
     }
 
     curl = curl_easy_init();
     if (!curl) {
         fprintf(stderr, "Eroare: curl_easy_init a esuat\n");
         curl_global_cleanup();
         return 1;
     }
 
     printf("Se realizeaza cererea catre URL: %s\n", url);  // Mesaj de debug
 
     curl_easy_setopt(curl, CURLOPT_URL, url);
     curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);  // Nu descarcam body-ul raspunsului
 
     res = curl_easy_perform(curl);
 
     if (res != CURLE_OK) {
         fprintf(stderr, "curl_easy_perform() a esuat: %s\n", curl_easy_strerror(res));
         curl_easy_cleanup(curl);
         curl_global_cleanup();
         return 1;
     }
 
     // Obținem codul de raspuns HTTP
     curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
     printf("Cererea catre %s a avut succes cu codul HTTP: %ld\n", url, http_code);
 
     // Curatare si finalizare
     curl_easy_cleanup(curl);
     curl_global_cleanup();
 
     return 0;
 }
 
 /*
  * Rulari care produc erori:
  * 1. ./app3 -u "" (URL invalid) -> Eroare: curl_easy_perform() a esuat.
  * 2. ./app3 (fara nici o optiune) -> Eroare: Trebuie sa specifici un URL.
  *
  * Rulari care produc stare de succes:
  * 1. ./app3 -u "http://exemplu.com" -> Cererea catre URL-ul specificat se realizeaza cu succes.
  * 2. ./app3 -v -> Afiseaza versiunea aplicatiei (App3 Versiunea 1.0).
  * 3. ./app3 -h -> Afiseaza ajutorul pentru utilizare.
  */
 