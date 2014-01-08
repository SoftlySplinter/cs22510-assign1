/**
 * @brief Creates a lock on a file.
 *
 * @author Alexander Brown
 * @version 1.0
 */

/**
 * @brief Locks a file.
 *
 * @param filepath The path to the file.
 * @return The file descriptor of the file to lock, -1 if anything fails.
 */
int lock(char * filepath);

/**
 * @brief Unlocks a file.
 *
 * @param file_descriptor
 * @return
 * 	1 - If the file unlocked sucessfully.
 * 	0 - If not.
 */
int unlock(int file_descriptor);
