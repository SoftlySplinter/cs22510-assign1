/* FileLock.cpp  Copyright (c) Alexander Brown, March 2011 */

#include <cstdlib>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string>

#include "FileLock.h"

/**
 * Structure contaning details on the lock.
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

FileLock::FileLock(std::string filename) throw (std::string) {
    _file_des = open(filename.data(), O_RDWR);

    if (_file_des == -1) {
        throw std::string("File Descriptor Error");
    }
    lock();
}

FileLock::~FileLock() {
    unlock();
    close(_file_des);
}

void FileLock::lock() throw (std::string) {
    _file_lock = file_lock(F_WRLCK, SEEK_SET);

    if (fcntl(_file_des, F_SETLK, _file_lock) == -1) {
        if (errno == EACCES || errno == EAGAIN) {
            throw std::string("Already locked by another process");
        } else {
            throw std::string("Unkown Error");
        }
    }
}

void FileLock::unlock() {
    fcntl(_file_des, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
}

int FileLock::get_locked_file() {
    return _file_des;
}
