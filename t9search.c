#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 111

char t9_char(char c) {
  c = tolower(c);

  if(c >= 'a' && c <= 'z') {
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

    // current position [i] checking match with next chars [j]
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

  //whole list when no argumentu
  if(argc == 1){
		char jmeno[MAX_LEN];
		char cislo[MAX_LEN];
		// checking if name and number exists
		while(fgets(jmeno, sizeof(jmeno), stdin) != NULL) {

      for(int i = 0;jmeno[i] != '\0'; i++){
        if (jmeno[i] < 32 || jmeno[i] > 126) {
          fprintf(stderr, "V souboru je kontakt s nevalidnim znakem ASCII.\n");
          return 1;
        }
      }

			if(fgets(cislo, sizeof(cislo), stdin) == NULL) {
        fprintf(stderr, "V souboru je neuplny kontakt.\n");
        return 1;
      }
			jmeno[strcspn(jmeno, "\n")] = '\0';
			cislo[strcspn(cislo, "\n")] = '\0';

        
      if(strlen(jmeno) > 100 || strlen(cislo) > 100) {
			  fprintf(stderr, "Radek prekrocil 100 znaku.\n");
        return 1;
      }
			printf("%s, %s\n", jmeno, cislo);
		}
		return 0;
	}

  //exact contacts from the list
  else if(argc == 2) {
		char jmeno[MAX_LEN];
    char cislo[MAX_LEN];
    int nalezeno = 0;
    
    if (argv[1][0] == '\0') {
      fprintf(stderr, "Argument nesmi byt prazdny\n");
      return 1;
    }

    for(int j = 0; argv[1][j] != '\0'; j++) {
      if (!isdigit(argv[1][j])) {
        fprintf(stderr, "Argument obshauje neciselne znaky\n");
        return 1;
      }
    }

	  while(fgets(jmeno, sizeof(jmeno), stdin) != NULL) {
			if(fgets(cislo, sizeof(cislo), stdin) == NULL) {
        fprintf(stderr, "V souboru je neuplny kontakt.\n");
        return 1;
      } 
    
      
			  jmeno[strcspn(jmeno, "\n")] = '\0';
		    cislo[strcspn(cislo, "\n")] = '\0';
			    		    
        if(strlen(jmeno) > 100 || strlen(cislo) > 100) {
			    fprintf(stderr, "Radek prekrocil 100 znaku.\n");
          return 1;
			  }

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
  
    if (nalezeno == 0) {
      printf("Not found\n");
    }
  }


  else {
      fprintf(stderr, "Prilis mnoho argumentu\n");
      return 1;
    }

	return 0;
}
