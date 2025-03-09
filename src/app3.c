#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <curl/curl.h>

void print_usage() {
    printf("Utilizare: app3 [opțiuni]\n");
    printf("Opțiuni:\n");
    printf("  -h, --help           Afișează acest mesaj de ajutor\n");
    printf("  -v, --version        Afișează versiunea aplicației\n");
    printf("  -u, --url URL        Specifică URL-ul de accesat\n");
}

int main(int argc, char *argv[]) {
    int option;
    char *url = NULL;

    // Definirea opțiunilor disponibile
    struct option long_options[] = {
        {"help",    no_argument,       0, 'h'},
        {"version", no_argument,       0, 'v'},
        {"url",     required_argument, 0, 'u'},
        {0, 0, 0, 0}
    };

    // Procesarea argumentelor
    while ((option = getopt_long(argc, argv, "hv:u:", long_options, NULL)) != -1) {
        switch (option) {
            case 'h':
                print_usage();
                return 0;
            case 'v':
                printf("App3 Versiunea 1.0\n");
                return 0;
            case 'u':
                url = optarg;  // Salvează URL-ul
                break;
            default:
                print_usage();
                return 1;
        }
    }

    // Verificăm dacă URL-ul a fost furnizat
    if (url == NULL) {
        fprintf(stderr, "Eroare: Trebuie să specifici un URL.\n");
        print_usage();
        return 1;
    }

    CURL *curl;
    CURLcode res;
    long http_code = 0;

    // Inițializare curl
    if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) {
        fprintf(stderr, "Eroare: curl_global_init a eșuat\n");
        return 1;
    }

    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Eroare: curl_easy_init a eșuat\n");
        curl_global_cleanup();
        return 1;
    }

    printf("Se realizează cererea către URL: %s\n", url);  // Mesaj de debug

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);  // Nu descărcăm corpul răspunsului

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() a eșuat: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 1;
    }

    // Obținem codul de răspuns HTTP
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    printf("Cererea către %s a avut succes cu codul HTTP: %ld\n", url, http_code);

    // Curățare și finalizare
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}
