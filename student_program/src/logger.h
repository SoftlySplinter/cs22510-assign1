
#ifndef _LOGGER_H
#define _LOGGER_H

/**
 * Logs an activity.
 *
 * @param activity	The activity performed.
 * @param uid		The user ID of the user.
 * @param filepath	The path to the file that the activity was performed upon.
 */
void log(char * activity, char * uid, char * filepath);

void generate_log_entry(char * entry, char * activity, char * uid, char * filepath);

void encode_date_time(char * entry);

void free_logger(void);

#endif /* _LOGGER_H */
