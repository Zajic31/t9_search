#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 102

char t9_char(char c) {
  c = tolower(c);

  if(c >= 'a' && c <= "z") {
    
    return "22233344455566677778889999"
  }
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
