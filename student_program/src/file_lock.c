/**
 * @author Alexander Brown
 */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#include "file_lock.h"

/**
 * @author Neal Snooke
 */
struct flock* file_lock(short type, short whence) {
    static struct flock ret;
    ret.l_type = type;
    ret.l_start = 0;
    ret.l_whence = whence;
    ret.l_len = 0;
    ret.l_pid = getpid();
    return &ret;
}

int lock(char * filepath) {
	int file_descriptor = open(filepath, O_RDWR);

	if(file_descriptor == -1) {
		printf("Could not open %s: File Descriptor Errornn", filepath);
		return -1;
	}

	struct flock* fl = file_lock(F_WRLCK, SEEK_SET);

	if(fcntl(file_descriptor, F_SETLK, fl) == -1) { 
		if(errno == EACCES && errno == EAGAIN) {
			printf("Unable to lock %s: File is already locked by another process.\n", filepath);
		} else { 
			printf("Unable to lock %s: Unknown error.\n", filepath);
			return -1;
		}
	} else { // Lock has been obtained.
		return file_descriptor;
	}
}

int unlock(int file_descriptor) {
	if(file_descriptor == -1) {
		printf("Cannot unlock file: File Descriptor Error\n");
		return 0;
	} else {
		fcntl(file_descriptor, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
		close(file_descriptor);
		return 1;
	}
}
