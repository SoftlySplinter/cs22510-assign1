package uk.ac.aber.users.adb9.cs22510.staff_program.io;

/**
 * Defines the exception to be thrown if there is an error with
 * handlling a file.
 *
 * @author	Alexander Brown
 * @version	1.0
 */
public class FileException extends Exception {
	
	/**
	 * Calls the super constructor.
	 *
	 * @param message	The message to display.
	 *
	 * @see Exception#Exception(String)
	 */
	public FileException(String message) {
		super(message);
	}
}
