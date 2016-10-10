#include "run_n_login.h"

int do_compare(char *id, char *pswd)
{
    char d_id[20];
    char d_pswd[20];

    FILE *f = fopen("login.txt", "r");

    memcpy(d_id, id, sizeof(id));   //got ID from the client
    memcpy(d_pswd, pswd, sizeof(pswd));   //got pswd from the client
    //printf("%s\n", d_id);
    //printf("%s\n", d_pswd);

    if (f == NULL) {
	return -1;
    }
    else {
	char compare_id[20];
	char compare_pswd[20];

	while (!feof(f)) {
	    fscanf(f, "%s %s\n", compare_id, compare_pswd);
	    //printf("test: %s %s\n", compare_id, compare_pswd);
	}
    }



    return 1;
}
