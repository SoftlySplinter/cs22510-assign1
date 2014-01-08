/* FileLock.h  Copyright (c) Alexander Brown, March 2011 */

#ifndef _FILELOCK_H
#define	_FILELOCK_H

#include <string>

/**
 * @brief Locks a File so that only this process can use it.
 *
 * @author Alexander Brown
 * @author Neil Snooke (Locking Code).
 */
class FileLock {
public:
    /**
     * Creates a Lock on the given file.
     * @param filename  The file to lock.
     * @throws std::string If the lock fails.
     */
    FileLock(std::string filename) throw (std::string);

    /**
     * Destructs, freeing the lock in the process.
     */
    virtual ~FileLock();

    /**
     * Returns the file descriptor of the locked file.
     * @return The file descriptor of the locked file.
     * @deprecated Use of std::fstream makes this unecessary.
     */
    int get_locked_file();

private:
    /** A structure containing the details of the file lock. */
    struct flock* _file_lock;

    /** The file descriptor of the locked file. */
    int _file_des;

    /**
     * Performs the lock operation.
     * @throws std::string If the operation was not sucessful.
     */
    void lock() throw (std::string);

    /** Performs the unlock operation. */
    void unlock();
};

#endif	/* _FILELOCK_H */

