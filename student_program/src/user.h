/* user.h Copyright (c) Alexander Brown, March 2011 */

/**
 * @brief	Defines operations for a user.
 * @author	Alexander Brown.
 * @version	1.0
 */

#ifndef _USER_H
#define _USER_H

/**
 * Logs in a user.
 * @param uid 	The user id of the user.
 * @return 	<code>1</code> - If the operation was sucessful.
 */
int login(char * uid);

/**
 * Downloads the assignment.
 * @param dest_path	The path of the file to download to.
 * @return		<code>1</code> - If the operation was sucessful.
 */
int download_assignment(char * dest_path);


int submit_assignment(char * src_path, char * uid);

/**
 * Views the marks and comments for this assignment.
 * @param uid	The User ID of the user.
 */
void view_marks(char * uid);

/**
 * Copies the source file to the destination file.
 * @param src_path	The path to the source file.
 * @param dest_path	The path to the destination file.
 * @return 		<code>1</code> - If the operation was sucessful.
 */
int copy(char * src_path, char * dest_path);

#endif /* _USER_H */
