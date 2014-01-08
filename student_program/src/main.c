/**
 * @author Alexander Brown
 */

#ifndef LOGIN_FAILURE
#define LOGIN_FAILURE 12
#endif

#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "logger.h"

#ifndef MENU_OPTIONS
#define MENU_OPTIONS
#define QUIT	'q'
#define HELP	'h'
#define GET	'g'
#define SUBMIT	's'
#define MARK	'm'
#define NONE	' '
#endif

static char uid[7];

int main(int argc, char ** argv) {
	get_logfile();
	printf("Enter User ID: ");
	scanf("%6s", uid);
	
	if(!(login(uid) == 1)) {
		printf("Invalid Username/Password\n");
		return 12;
	}

	if(argc < 2) {
		char option = NONE;
		char path[100];
		while(option == NONE) {
			printf("Enter option code (h for help): ");
			fflush(stdin);
			scanf("%1s", &option);
			getchar(); // getchar() apparently stops this looping infinitely on my machine.
			switch(option) {
				case GET :
					printf("Location to download the assignment to: ");
					scanf("%98s", path);
					if(download_assignment(path) == 1) {
						log("Downloaded assignment", uid, "repository/assignment/");
					}
					break;
				case SUBMIT:
					printf("Location of file to submit: ");
					scanf("%98s", path);
					if(submit_assignment(path, uid) == 1) {
						strcpy(path, "repository/students/");
						strcat(path, uid);
						strcat(path, "/");
						log("Uploaded assignment", uid, path);						
					}
					break;
				case MARK:
					view_marks(uid);
					break;
				case HELP:
					printf("\t%c - Get Assignment.\n\t%c - Submit Assignment.\n\t%c - View Marks.\n\t%c - Quit.\n", 
						GET, 
						SUBMIT, 
						MARK, 
						QUIT);
					option = NONE; // To allow looping
					break;
				case QUIT:
					break;
				default:
					printf("Unrecognised option '%s'\n", &option);
					option = NONE;
			}
		}
	}
	free_logger();
	return EXIT_SUCCESS;
}
