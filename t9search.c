#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 102

char t9_char(char c) {
  c = tolower(c);

  if(c >= 'a' && c <= 'z') {
    // retezec cisel odpovidajic pismenum
    // znak odecte hodnotu 'a'(97)
    // dostaneme pozici znaku v retezec
    return "22233344455566677778889999"[c - 'a'];
  }

  if(c == '+') {
    return '0';
  }

  return c;
}

int shoda(char text[], char hledam[]) {
  for(int i = 0; text[i] != '\0'; i++) {
    int j = 0;

    // od aktualni pozice [i] zkousim jestli se shoduji
    // dalsi znaky [j]
    while(text[i + j] == hledam[j] && hledam[j] != '\0') {
      j++; 
    }

    if(hledam[j] == '\0') {
      return 1;
    }
  }
  return 0;
}


int main(int argc, char *argv[]) {
	if(argc == 1){
		char jmeno[MAX_LEN];
		char cislo[MAX_LEN];
		// zjisteni existence jmena a cisla
		while(fgets(jmeno, sizeof(jmeno), stdin) != NULL) {
			if(fgets(cislo, sizeof(cislo), stdin) != NULL) {
				jmeno[strcspn(jmeno, "\n")] = '\0';
				cislo[strcspn(cislo, "\n")] = '\0';

				printf("%s, %s\n", jmeno, cislo);
			}
		}
		return 0;
	}

  else if(argc == 2) {
		char jmeno[MAX_LEN];
    char cislo[MAX_LEN];
    int nalezeno = 0;

		while(fgets(jmeno, sizeof(jmeno), stdin) != NULL) {
			if(fgets(cislo, sizeof(cislo), stdin) != NULL) {
				jmeno[strcspn(jmeno, "\n")] = '\0';
				cislo[strcspn(cislo, "\n")] = '\0';


        // jmeno ze seznamu na t9 format
        char t9_jmeno[MAX_LEN];
        int i;
        for(i = 0; jmeno[i] != '\0'; i++) {
          t9_jmeno[i] = t9_char(jmeno[i]);
        }
        t9_jmeno[i] = '\0';

        char t9_cislo[MAX_LEN];
        for (i = 0; cislo[i] != '\0'; i++) {
          t9_cislo[i] = t9_char(cislo[i]);
        }
        t9_cislo[i] = '\0';

        if(shoda(t9_jmeno, argv[1]) || shoda(t9_cislo, argv[1])) {
          printf("%s, %s\n", jmeno, cislo);
          nalezeno = 1;
        }
      }  
    }
    if (nalezeno == 0) {
      printf("Not found\n");
    }
  }
	return 0;
}
