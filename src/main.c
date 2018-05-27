#include "lex.h"
#include "func.h"

int main(int argc, const char *argv[]) 
{
	if(argc != 2) {
		printf("Wrong number of arguments\n");
		return 0;
	}
	strcpy(script_file, argv[1]);
	f = fopen(script_file, "r");
	if(f != NULL) {
		for (int i = 0; i < MAX_VAR_COUNT; i++) 
			vars[i].name[0] = '\0';
		while(fgets(str, 100, f) != NULL)
			lex();
	} else
		printf("Could't open file!\n");
	fclose(f);
	return 0;
}
