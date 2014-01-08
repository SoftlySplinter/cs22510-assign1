package uk.ac.aber.users.adb9.cs22510.staff_program;

/**
 * An Exception for throwing when a Username or Password is incorrect.
 * <p>
 * Thrown from {@link User#login(Logger)} so that the program doesn't have
 * to compare ugly things like {@code null}s to check if a User logged in.
 * 
 * @author Alexander Brown
 * @version 1.0
 */
public class InvalidUserException extends Exception {
	/** The Serial Version UID for serialisation potential. */
	private static final long serialVersionUID = -239788711036612392L;
	
	/** The default error message. */
	private static final String DEFAULT_MESSAGE = "Invalid User/Password";
	
	/** Displays the default error message */
	public InvalidUserException() {
		super(DEFAULT_MESSAGE);
	}
}
