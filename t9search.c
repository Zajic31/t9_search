#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 102

char t9_char(char c) {
  c = tolower(c);

  if(c >= 'a' && c <= "z") {
    // retezec cisel odpovidajic pismenum
    // znak odecte hodnotu 'a'(97) a dostaneme pozici znaku v retezec
    return "22233344455566677778889999"[c - 'a'];
  }

  if(c == '+') {
    return '0';
  }

  return c;
}


int main(int argc, char *argv[]) {
	if(argc < 2){
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


	return 0;
}
