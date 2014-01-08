/* user.c  Copyright (c) Alexander Brown, March 2011 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#include <termios.h>
#include <unistd.h>

#include "user.h"
#include "utils.h"
#include "file_lock.h"

void set_stdin_echo(int enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable)
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

int login(char * uid) {
	set_stdin_echo(0);
	char passwd[13];
	printf("%s's password: ", uid);
	scanf("%12s", passwd);
	set_stdin_echo(1);
	printf("\n");

	char * base_dir = malloc(115 * sizeof(char));
	get_base_dir(base_dir);
	strcat(base_dir, "/.auth");

	int auth_fd = lock(base_dir);
	
	if(auth_fd == -1) {
		printf("Error: .auth file not found");
		free(base_dir);
		return 0;
	}

	FILE * auth = fdopen(auth_fd, "r");
	char line[100];
	char user_line[100];
	int autherised = 0;

	strcpy(user_line, uid);
	strcat(user_line, " stdnt ");
	strcat(user_line, passwd);
	strcat(user_line, "\n");
	while(fgets(line, 100, auth) != NULL) {
		if(strcmp(user_line, line) == 0) {
			autherised = 1;
		}
	}

	fclose(auth);
	unlock(auth_fd);
	free(base_dir);
	return autherised;	
}

int download_assignment(char * dest_path) {
	char * src_path = malloc(115 * sizeof(char));	
	DIR * assignment_dir;
	struct dirent * dir_entry;
	struct stat entry_stat; 
	int has_file = 0;

	get_base_dir(src_path);
	strcat(src_path, "/assignment/");
	assignment_dir = opendir(src_path);
	
	while((dir_entry = readdir(assignment_dir)) != NULL) {
		if(stat(dir_entry->d_name, &entry_stat) == -1) {
		} 
		
		if(S_ISREG(entry_stat.st_mode)) {
			strcat(src_path, dir_entry->d_name);
			has_file = 1;
			break;
		}
	}

	closedir(assignment_dir);

	if(has_file == 0) {
		printf("No assignment file found\n");
		return 0;
	}
	
	int ret = copy(src_path, dest_path);
	free(src_path);
	return ret;
}

int submit_assignment(char * src_path, char * uid) {
	char * dest_path = malloc(115 * sizeof(char));
	get_base_dir(dest_path);
	strcat(dest_path, "/students/");
	strcat(dest_path, uid);
	strcat(dest_path, "/");

	char * tokens = strtok(src_path, "/");
	char * filename;

	while(tokens != NULL) {
		filename = tokens;
		tokens = strtok(NULL, "/");
	}
	strcat(dest_path, filename);
	int ret = copy(src_path, dest_path);
	free(dest_path);
	return ret;
}

void view_marks(char * uid) {
	char * dest_path = malloc(115 * sizeof(char));
	get_base_dir(dest_path);
	strcat(dest_path, "/students/");
	strcat(dest_path, uid);
	strcat(dest_path, "/results/result.txt");

	int dest_fd = lock(dest_path);
	FILE * dest = fdopen(dest_fd, "r");
	
	if(dest == NULL) {
		printf("No results found for user '%s'\n", uid);
		free(dest_path);
		return;
	}	

	int mark;
	char comments[200];
	fscanf(dest, "%d%%\n", &mark);
	fgets(comments, 200, dest);

	char * grade;

	if (mark <= 15)
		grade = "F-";
	else if (mark <= 30)
		grade = "F";
	else if (mark <= 34)
		grade = "F+";
	else if (mark <= 39)
		grade = "E";
	else if (mark <= 43)
		grade = "D-";
	else if (mark <= 46)
		grade = "D";
	else if (mark <= 59)
		grade = "D+";
	else if (mark <= 53)
		grade = "C-";
	else if (mark <= 56)
		grade = "C";
	else if (mark <= 59)
		grade = "C+";
	else if (mark <= 63)
		grade = "B-";
	else if (mark <= 66)
		grade = "B";
	else if (mark <= 69)
		grade = "B+";
	else if (mark <= 79)
		grade = "A-";
	else if (mark <= 89)
		grade = "A";
	else if (mark <= 95)
		grade = "A+";
	else
		grade = "A++";

	printf("Results for user '%s':\n\tMark: %d%% (%s)\n\tComments: %s\n", uid, mark, grade, comments);
	
	fclose(dest);
	unlock(dest_fd);
	free(dest_path);
}

int copy(char * src_path, char * dest_path) {
	FILE * dest;
        FILE * src;
	int src_fd;
	int reader;

	src_fd = lock(src_path);
	if(src_fd == -1) {
		return 0;
	}
	src = fdopen(src_fd, "rb");
	dest = fopen(dest_path, "wb");
	
	while(1) {
		reader = fgetc(src);
		if(reader == EOF) break;
		fputc((int) reader, dest);
	}

	fclose(src);
	fclose(dest);
	unlock(src_fd);
//	free(src_path);
	return 1;
}
