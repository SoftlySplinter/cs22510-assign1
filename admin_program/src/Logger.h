/* Logger.h  Copyright (c) Alexander Brown, March 2011 */

#ifndef _LOGGER_H
#define _LOGGER_H

#include <string>

class User;
class FileHandller;

/**
 * @brief A class which handles all log file actions.
 *
 * This class deals with all operations that will be performed on
 * the logfile, ensuring the file is locked whilst these actions
 * are performed, etc.
 *
 * It also ensures that the same format is used, so that the
 * logfile can be read and formatted back.
 *
 * @author Alexander Brown
 * @version 1.0
 */
class Logger {
public:
    Logger();
    ~Logger();

    /**
     * Sets user to be the current User.
     *
     * @param user The current User.
     */
    void set_user(User *user);

    /**
     * Makes an entry to the logfile.
     *
     * @param activity  The activity that was performed.
     * @param filepath  The path to the file the activity was performed on.
     *
     * @see Logger::generateLogEntry(std::string, std::string)
     */
    void log(std::string activity, std::string filepath);

    /**
     * Prints the logfile in a human readable format.
     *
     * @see Logger::decodeDateTime(std::string)
     */
    void read_log(void);
private:
    /** Aggregation to the User */
    User * _user;

    FileHandller * _file_handller;

    /**
     * Generates the text for the log entry.
     *
     * @param activity  The activity that was performed.
     * @param filepath  The path to the file the activity was performed on.
     *
     * @return The textual form of a log entry.
     *
     * @see Logger::encodeDateTime()
     */
    std::string generate_log_entry(std::string activity, std::string filepath);

    /**
     * Encodes the current Date and Time into the string format used by the log
     * file.
     *
     * @return The current Date and Time into the string format used by the log
     * file.
     */
    std::string encode_date_time(void);

    /**
     * Decodes the Date and Time from a log entry into a human-readable format.
     *
     * @param date_time  The date and time to decode into a human readable
     * format
     * 
     * @return The Date and Time from a log entry into a human-readable format.
     */
    std::string decode_date_time(std::string date_time);
};

#endif  /* _LOGGER_H */
