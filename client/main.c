//
//  main.c
//  communication
//
//  Created by Minsu Lee on 2016. 5. 24..
//  Copyright © 2016년 mins. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

#include "run_n_client.h"
#include "run_c_client.h"



int main(int argc, char * const * argv) {
    int n;   //option
    //extern char *optarg;
    //extern int optind;
    
    
    
    if (argc != 2) {
        puts("./main [option]\n");
	return -1;
    }
    
    
    while ((n = getopt(argc, argv, "cnh")) != -1){
        switch (n)
        {
            case 'c' : //puts("-c option selected\n");

		run_c_client();
                
                break;
                
            case 'n' : //puts("-n option selected\n");
                
                run_n_client();
                
                break;

	    case 'h' :

		puts("-----------------------------\n");
		puts("-c option for normal chatting\n");
		puts("-n option for crypto chatting\n");
		puts("-----------------------------\n");

		break;

            default:
                puts("either -c or -n options please,\n");
		puts("any helps? -h option please,\n");
		puts("many thanks :)\n");
        }
        
    }
    
    return 0;
}
