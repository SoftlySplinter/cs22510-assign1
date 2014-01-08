/*
 * logger.c copyright (c) Alexander Brown, March 2011
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "utils.h"
#include "logger.h"
#include "file_lock.h"

#ifndef MAX_ENTRY_SIZE
#define MAX_ENTRY_SIZE 100
#endif

char * logfile;

void get_logfile(void) {
	if(logfile != NULL) {
		return;
	}
	logfile = malloc(115 * sizeof(char));
	char * base_dir = malloc(85 * sizeof(char));
	get_base_dir(base_dir);
	strcat(logfile, base_dir);
	strcat(logfile, "/logfile.log");
	free(base_dir);
}

void log(char * activity, char * uid, char * filepath) {
	get_logfile();
	int fd = lock(logfile);
	
	FILE * logfile = fdopen(fd, "a");

	char * entry = malloc(MAX_ENTRY_SIZE * sizeof(char));
	generate_log_entry(entry, activity, uid, filepath);	
	fprintf(logfile, "%s", entry);
	fclose(logfile);

	unlock(fd);
//	free(entry);
}

void generate_log_entry(char * entry, char * activity, char * uid, char * filepath) {
	//yyyy-mm-dd-hh-mm-ss stdnt: %uid	%activity	%filepath
	encode_date_time(entry);
	strcat(entry, " stdnt: ");
	strcat(entry, uid);
	strcat(entry, "\t");
	strcat(entry, activity);
	strcat(entry, "\t");
	strcat(entry, filepath);
	strcat(entry, "\n");
}

void encode_date_time(char * entry) {
	time_t rawtime;
	struct tm * timeinfo;
	char time_str[21];
	
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(time_str, 21, "%Y-%m-%d-%H-%M-%S", timeinfo);
	strcat(entry, time_str);
}

void free_logger() {
	free(logfile);
}
