package uk.ac.aber.users.adb9.cs22510.staff_program;

import java.text.SimpleDateFormat;
import java.util.Date;

import uk.ac.aber.users.adb9.cs22510.staff_program.io.FileHandller;

/**
 * Defines the logging class.
 * <p>
 * This class handles all entries that have to be made to the
 * {@linkplain StaffProgram#LOG_FILE logfile}, controlling how the entries
 * are made and the format in which they are made.
 *
 * @author	Alexander Brown
 * @version	1.0
 *
 * @see FileHandller
 */
public class Logger {
	/** Link back to the User */
	private User user;
	
	/**
	 * Sets the link to the User.
	 * @param user	The User to set the link back to.
	 */
	public void setUser(User user) {
		this.user = user;
	}
	
	/**
	 * Makes an entry to the logfile.
	 * 
	 * @param activity	The activity to be logged.
	 * @param filepath	The path to the file that the activity was
	 * performed on.
	 *
	 * @see generateLogEntry()
	 */
	public void log(String activity, String filepath) {
		FileHandller handller = new FileHandller(StaffProgram.LOG_FILE);
		handller.appendFile(generateLogEntry(activity, filepath));
		handller.close();
	}

	/**
	 * Generates the text for a log entry
	 *
	 * @param activity	The activity to be logged.
	 * @param filepath	The path to the file that the activity was
	 * performed on.
	 *
	 * @see encodeDateTime()
	 */
	private String generateLogEntry(String activity, String filepath) {
		String file = filepath.replace(StaffProgram.BASE_DIR, "");

		String[] path = StaffProgram.BASE_DIR.split("/");
		String base = path[path.length-1];

		String entry = String.format("%s staff: %s\t%s\t%s/%s\n", 
			encodeDateTime(), 
			user.getUID(), 
			activity, 
			base,
			file);
		return entry;
	}
	
	/**
	 * Takes the date and time and encodes them into the string format
	 * used by the log.
	 *
	 * @return An encoded date time.
	 */
	private String encodeDateTime() {
		Date d = new Date();
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd-kk-mm-ss");
		return df.format(d);
	}
}
