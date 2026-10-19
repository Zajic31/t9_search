#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 111
#define MAX_ASCII 126
#define MIN_ASCII 32

const char T9_KLAVESNICE[] = "22233344455566677778889999";


//prevadi jmena v kontaktu na jejich ciselnou t9 hodnotu
char t9_znak(char znak)
{
  znak = tolower(znak);

  if (znak >= 'a' && znak <= 'z') {
    return T9_KLAVESNICE[znak - 'a'];
  }
  if (znak == '+') {
    return '0';
  }
  return znak;
}

//porovnava jmena a cisla v kontaktu se zadanym cislem v argumentu
int je_shoda(char text[], char najdi[])
{
  for (int i = 0; text[i] != '\0'; i++) {
    int j = 0;
    while (text[i + j] == najdi[j] && najdi[j] != '\0') {
      j++;
    }
    if (najdi[j] == '\0') {
      return 1;
    }
  }
  return 0;
}

// kontrola zda zadany argument neni prazdny nebo zda neobsahuje neciselne znaky
int validuj_argument(char *arg)
{
  if (arg[0] == '\0') {
    fprintf(stderr, "Argument nesmi byt prazdny\n");
    return 0;
  }

  if (strlen(arg) > 100) {
    fprintf(stderr, "Argument je delsi nez 100 znaku.\n");
    return 0;
  }

  for (int j = 0; arg[j] != '\0'; j++) {
    if (!isdigit(arg[j])) {
      fprintf(stderr, "Argument obsahuje neciselne znaky\n");
      return 0;
    }
  }
  return 1;
}

//kontrola zda jmeno je slozeno pouze z tisknutelnych
//ASCII znaku a zda delka radku neni vetsi nez 100
int validuj_kontakt(char jmeno[], char cislo[])
{
  for (int i = 0; jmeno[i] != '\0'; i++) {
    if (jmeno[i] < MIN_ASCII || jmeno[i] > MAX_ASCII) {
      fprintf(stderr,
              "Kontakt neni validni - obsahuje netisknutelny znak nebo znak neni v ASCII.\n");
      return 0;
    }
  }

  for (int i = 0; cislo[i] != '\0'; i++) {
    if (cislo[i] < MIN_ASCII || cislo[i] > MAX_ASCII) {
      fprintf(stderr,
              "Kontakt neni validni - obsahuje netisknutelny znak nebo znak neni v ASCII.\n");
      return 0;
    }
  }

  if (strlen(jmeno) > 100 || strlen(cislo) > 100) {
    fprintf(stderr, "Radek prekrocil 100 znaku.\n");
    return 0;
  }

  if (strlen(jmeno) == 0 || strlen(cislo) == 0) {
    fprintf(stderr, "Radek nemuze byt prazdny.\n");
    return 0;
  }

  for (int i = 0; cislo[i] != '\0'; i++) {
    if (i == 0 && cislo[i] == '+') {
      if (cislo[1] == '\0') {
        fprintf(stderr, "Cislo nemuze obsahovat pouze '+'\n");
        return 0;
      }
      continue;
    }

    if (!isdigit(cislo[i])) {
      fprintf(stderr, "Cislo obsahuje neplatny znak\n");
      return 0;
    }
  }

  return 1;
}

//overuje zda vyhledavame bez nebo s argumentem 
//zaroven kontroluje spravnost argumentu
int validuj_parametry(int argc, char *argv[], char **hledany_text)
{
  if (argc == 1) {
    *hledany_text = NULL;
    return 1;
  }

  else if (argc == 2) {
    if (!validuj_argument(argv[1])) {
      return 0;
    }
    *hledany_text = argv[1];
    return 1;
  }

  else {
    fprintf(stderr, "Prilis mnoho argumentu.\n");
    return 0;
  }
}

int main(int argc, char *argv[])
{
  char *hledany_text = NULL;

  if (!validuj_parametry(argc, argv, &hledany_text)) {
    return 1;
  }

  char jmeno[MAX_LEN];
  char cislo[MAX_LEN];
  int nalezeno = 0;

  while (fgets(jmeno, sizeof(jmeno), stdin) != NULL) {
    if (fgets(cislo, sizeof(cislo), stdin) == NULL) {
      fprintf(stderr, "V souboru je neuplny kontakt.\n");
      return 1;
    }

    jmeno[strcspn(jmeno, "\n")] = '\0';
    cislo[strcspn(cislo, "\n")] = '\0';

    if (!validuj_kontakt(jmeno, cislo)) {
      return 1;
    }

    if (hledany_text == NULL) {
      printf("%s, %s\n", jmeno, cislo);
    }
    
    else {
      //preklad jmena a cisla v kontaktu na 
      //sekvenci cisel odpovidajici na t9 klavesnici
      char t9_jmeno[MAX_LEN];
      char t9_cislo[MAX_LEN];
      int i;
      for (i = 0; jmeno[i] != '\0'; i++) {
        t9_jmeno[i] = t9_znak(jmeno[i]);
      }
      t9_jmeno[i] = '\0';

      for (i = 0; cislo[i] != '\0'; i++) {
        t9_cislo[i] = t9_znak(cislo[i]);
      }
      t9_cislo[i] = '\0';

      if (je_shoda(t9_jmeno, hledany_text) || je_shoda(t9_cislo, hledany_text)) {
        printf("%s, %s\n", jmeno, cislo);
        nalezeno = 1;
      }
    }
  }
    if (nalezeno == 0 && hledany_text != NULL) {
      printf("Not found\n");
    }

  return 0;
}
