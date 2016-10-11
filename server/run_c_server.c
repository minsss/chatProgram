//
//  run_c_server.c
//  communucation
//
//  Created by Minsu Lee on 2016. 5. 24..
//  Copyright © 2016년 mins. All rights reserved.
//


#include "run_c_server.h"

char quit_c[] = ":quit";
char nomore_c[] = "No more connection // MAX 10\n";
char greet0_c[] = "------------------------------------------------------------------\n";
char greet1_c[] = "------------------- Welcome to CSRC chat server ------------------\n";
char greet2_c[] = "------------------------------------------------------------------\n";

int list_c[MAX_CLIENT];

pthread_t thread;
pthread_t login_thread;
pthread_mutex_t mutex;


//more functions
void * do_c_chat(void *arg);

int run_c_server()
{
    
    int c_socket, s_socket;   // client_socket, server_socket
    struct sockaddr_in s_addr, c_addr;   // server_addr., client_addr.
    unsigned int len;
    unsigned int res;
    int n;
    
    int pid;   // process id;
    
    char rcvBuffer[1000];
    
    if(pthread_mutex_init(&mutex, NULL) != 0) {
	printf("Cannot create mutex\n");
	return -1;
    }

    // Create socket
    if ((s_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Could not create socket");
    }
    puts("Socket Created!");
    
    bzero((char*) &s_addr, sizeof(s_addr));
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    
    // Bind
    if(bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) < 0) {
        printf("Can't Bind\n");
        return -1;
    }
    puts("Bind Done!!");
    
    // Listen
    if(listen(s_socket, 1) < 0) {
        printf("Listen Fail\n");
        return -1;
    }

    // init client
    for(int i = 0; i < MAX_CLIENT; i++)
    {
	list_c[i] = -1;
    }
    // Accept and incoming connection
    puts("Waiting for incoming connections...");


    while(1) {
    	len = sizeof(c_addr);
	c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);

	write(c_socket, greet0_c, strlen(greet0_c));
	write(c_socket, greet1_c, strlen(greet1_c));
	write(c_socket, greet2_c, strlen(greet2_c));

	res = pushClient(c_socket);

	if(res < 0)   //if the num of client is MAX
	{
	    write(c_socket, nomore_c, strlen(nomore_c));
	    close(c_socket);
	}

	else
	{
	    if(pthread_create(&thread, NULL, do_c_chat, (void *) c_socket) < 0) {
		perror("pthread create error!!!!!\n");
		exit(1);
	    }
	}
    }
}

void * do_c_chat(void *arg)
{
    int c_socket = (int) arg;
    char chatData[1024];
    int n;   //the max char can be got

    while(1) {
	memset(chatData, 0, sizeof(chatData));
	if((n = read(c_socket, chatData, sizeof(chatData))) > 0) {
	    for(int i = 0; i < MAX_CLIENT; i++) {

		if(strstr(chatData, quit_c) != NULL) {
		    popClient(c_socket);
		    break;
		}

		if(list_c[i] != -1 && list_c[i] != c_socket) {   // client on && don't return messages to myself
		    write(list_c[i], chatData, n);
		}
	    }


	}
    }

}
