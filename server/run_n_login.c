#include "run_n_login.h"

#define PORT 9001
#define MAX_CLIENT 10

char ID[] = "ID : ";
char pswd[] = "password : ";

int list_c[MAX_CLIENT];

pthread_t thread;
pthread_t login_thread;
pthread_mutex_t mutex;


int safe_memcpy(char *d_str, char *str, int len)
{
    printf("len: %d\n", len);
    if (len > MAX_ID) {
	printf("nonononnononono\n");
	return 0;
    }
    else {
	memcpy(d_str, str, strlen(str) - 1);
	return 1;
    }
}

int do_compare(char *id, char *pswd)
{
    FILE *f = fopen("login.txt", "r");

    char d_id[20];
    char d_pswd[20];

    
    //memcpy(d_id, id, strlen(id) - 1);   //got ID from the client
    //memcpy(d_pswd, pswd, strlen(pswd) - 1);   //got pswd from the client
    if(!safe_memcpy(d_id, id, strlen(id))) return -2;
    if(!safe_memcpy(d_pswd, pswd, strlen(pswd))) return -2;


    if (f == NULL) {
	return -1;
    }
    else {
	char compare_id[20];
	char compare_pswd[20];

	while (!feof(f)) {
	    fscanf(f, "%s %s\n", compare_id, compare_pswd);
	    //printf("test: %s %s\n", compare_id, compare_pswd);

	    if(!strcmp(compare_id, d_id))
	    {
		printf("matched\n");
		return 1;
	    }
	}

	fclose(f);
	return -2;    //login failure
    }
}

void * do_login(void *arg)
{
    int c_socket = (int) arg;
    char login_id[20];
    char login_pswd[20];

    int n, m;   // n for id, m for pswd

    memset(login_id, 0, sizeof(login_id));
    memset(login_pswd, 0, sizeof(login_pswd));
    
    
    while(1) {
	write(c_socket, ID, strlen(ID));
	if((n = read(c_socket, login_id, sizeof(login_id))) > 0) {
	    //login_id[strlen(login_id) - 1] = '\0';
	    printf("got ID from client %d, %s\n", c_socket, login_id);
	}

	write(c_socket, pswd, strlen(pswd));
	if((m = read(c_socket, login_pswd, sizeof(login_id))) > 0) {
	    //login_pswd[strlen(login_pswd) - 1] = '\0';
	    printf("got ID from client %d, %s\n", c_socket, login_pswd);
	}


	if(n > 20 || m > 20) {
	    char bye[] = "too long ID or PSWD\n";
	    write(c_socket, bye, strlen(bye));
	}

	else {
	    //printf("%d\n", do_compare(login_id, login_pswd));
	    if(do_compare(login_id, login_pswd) < 0) {
		char bye[] = "invalid ID or PSWD\n";
		write(c_socket, bye, strlen(bye));
	    }
	}
    }


}
