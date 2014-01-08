/* Setup.h  Copyright (c) Alexander Brown, March 2011 */

#ifndef _SETUP_H
#define	_SETUP_H

#include <string>

class User;
class Logger;


/**
 * @brief A class to hadnle the setup of the repository.
 *
 * This class was orignally meant to handle the setup of the
 * retpository. However, due to a lack of time, I put the
 * majority of the code for this in the makefile as BASH
 * commands.
 *
 * Instead, this contains constants to locations in the
 * repository and allows for uploading of an assignment
 * file.
 *
 * @author Alexander Brown
 * @version 1.0
 */
class Setup {
public:
    /** The Base Directory of the repository. */
    static const std::string BASE_DIR;

    /** The Repository directory */
    static const std::string REPO_DIR;

    /** The location of the authentication file */
    static const std::string AUTH_FILE;

    /** The location of the log file */
    static const std::string LOG_FILE;

    /** The location of the assignment directory */
    static const std::string ASSIGNMENT_DIR;

    /** The location of the assignment directory */
    static const std::string STUDENT_DIR;

    /**
     * Aggregate the User and the Logger.
     * @param user      The User to aggregate to.
     * @param logger    The Logger to aggregate to.
     * @deprecated  Unneeded.
     */
    Setup(User *user, Logger *logger);

    /**
     * Aggregate the User and the Logger.
     * @param user      The User to aggregate to.
     * @param logger    The Logger to aggregate to.
     */
    Setup(Logger *logger);

    /** Removes the aggregation */
    virtual ~Setup(void);

    /** Sets up the entire repository. */
    void run_setup(void);

    /**
     * Allows an assignment to be uploaded.
     * @param src   The location of the local assignment file to upload.
     */
    void upload_assignment(std::string src) throw (std::string);

private:
    /**
     * Aggregation to the user
     * @deprecated  Unneeded.
     */
    User* _user;

    /** Aggregation to the logger */
    Logger* _logger;

    void create_dir_structure(void);
};

#endif	/* _SETUP_H */

