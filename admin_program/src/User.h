/* User.h  Copyright (c) Alexander Brown, March 2011 */

#ifndef _USER_H
#define _USER_H

#include <string>
#include "UserType.h"

// Define the Logger class to stop strange dependancy errors.
class Logger;

/**
 * @brief Defines the User for the Administator Programs and associated methods.
 *
 * This class is mostly used to control the logging in and out of the User, as
 * well as a few base actions (adding Users) so most items can be set up without
 * too much hastle.
 *
 * This class is a singleton, hence the private constructor, and can only be
 * instantiated through the login method.
 */
class User {
public:
    /**
     * Logs in a user.
     *
     * @param logger    The aggregation to the logger.
     *
     * @return The single instance of the User. Note that if the User is already
     * logged in then this will still return the instance, just without any
     * ability to re-login.
     */
    static User* login(Logger *logger) throw (std::string);

    /**
     * Destructor. As ISTANCE is the only pointer that needs to be freed in this
     * class and is the one this destructor will be called upon, this doesn't
     * acutally do much, other than setting a few nulls.
     */
    ~User(void);

    /**
     * Adds a member of staff to the program.
     *
     * @param uid   The User ID of the Staff to add.
     *
     * @param The auto-generated password.
     *
     * @see User::addUser(std::string, enum UserType)
     */
    std::string add_staff(std::string uid);


    /**
     * Adds a student to the program.
     *
     * @param uid   The User ID of the Student to add.
     *
     * @param The auto-generated password.
     *
     * @see User::addUser(std::string, enum UserType)
     */
    std::string add_student(std::string uid);

    /**
     * Returns the User ID of the current User.
     *
     * @return The User ID of the current User.
     */
    std::string get_uid(void);

private:
    /** The single instance of this class */
    static User * _INSTANCE;

    /** Aggregation to the logger. */
    Logger * _logger;

    /** The User ID of the User, used for logging purposes. */
    std::string _uid;

    /**
     * Private Constructor to ensure this remains a singleton.
     *
     * @param logger    The aggregation to the Logger.
     * @param uid       The User ID of this User.
     */
    User(Logger *logger, std::string uid);

    /**
     * Adds a user to the program, returning the auto-generated password.
     *
     * @param uid   The User ID of the user to create.
     * @param type  The type of the User.
     *
     * @param The auto-generated password.
     */
    std::string add_user(std::string uid, enum UserType type);
};

#endif  /* _USER_H */
