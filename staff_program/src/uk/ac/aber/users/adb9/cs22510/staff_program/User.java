package uk.ac.aber.users.adb9.cs22510.staff_program;

import java.io.Console;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Scanner;

import uk.ac.aber.users.adb9.cs22510.staff_program.io.FileHandller;

public class User {
	/** The Singleton Instance. */
	static private User INSTANCE = null;
	
	/**
	 * Logs in a User.
	 * <p>
	 * This is the only way of creating a User, and ensures that the singleton
	 * design patter this class uses is kept strict.
	 * <p>
	 * As expected from a login method, the system asks for a User ID and password
	 * (the latter of which is concealed by the Console), then checks them against
	 * the {@linkplain StaffProgram#AUTH_FILE authentication file} and acts 
	 * accordingly.
	 *
	 * @param logger	The link back to the Logger.
	 *
	 * @throws InvalidUserException	If the User ID or connected password is 
	 * incorrect.
	 *
	 * @see Console
	 */
	public static User login(Logger logger) throws InvalidUserException {
		Console c = System.console();
		if(c == null) {
			System.err.println("No Console.");
			System.exit(2);
		}
		
		Scanner s = new Scanner(System.in);
		System.out.print("Enter User ID: ");
		String uid = s.next();
		
		System.out.printf("Password for %s: ", uid);
		char[] charPass = c.readPassword("");
		String passwd = String.valueOf(charPass);

		FileHandller f = new FileHandller(StaffProgram.AUTH_FILE);
		File auth = f.getFile();
		String line;
		Scanner reader = null;

		try {
			reader = new Scanner(new InputStreamReader(
					new FileInputStream(auth)));
			while (reader.hasNext()) {
				line = reader.nextLine();
				if (line.equals(String.format("%s staff %s", uid, passwd))) {
					INSTANCE = new User(uid, logger);
				}
			}
			reader.close();
		} catch (IOException eio) {
			
		}
		
		f.close();

		if (INSTANCE == null) {
			throw new InvalidUserException();
		}

		return INSTANCE;
	}

	/** The User ID of the current User */
	private String uid;

	/** The link to the Logger */
	private Logger logger;

	/** The File Handller this class makes use of */
	private FileHandller fileHandller;

	/**
	 * Creates a new User, with the given User ID and a link to a Logger.
	 * <p>
	 * Note that this is private to facilitate the singleton design pattern this class uses.
	 *
	 * @param uid 		The User ID of this User.
	 * @param logger 	The link to the Logger.
	 */
	private User(String uid, Logger logger) {
		this.uid = uid;
		this.logger = logger;
	}

	/**
	 * Returns the User ID of the current User.
	 * @return The User ID of the current User.
	 */
	public String getUID() {
		return uid;
	}

	/**
	 * Lists all Students that have made submissions.
	 * <p>
	 * Works by looping through all directories in the {@linkplain StaffProgram#STUDENT_DIR student directory}
	 * looking for those with more than 1 file contained within them (bearing in mind a directory for results
	 * is created in the student's directory when it's created). And writing their username (which is handily
	 * the name of the directory too) to a String.
	 * <p>
	 * Assuming any Students have made a submission, this String is then printed, otherwise a message to tell
	 * the user than no Students have made submissions yet is displayed.
	 *
	 * @see FileHandller#getFile()
	 * @see File#listFiles()
	 */
	public void list() {
		//fileHandller = new FileHandller(StaffProgram.STUDENT_DIR);
		//TODO - Cannot currently lock directories.
		File studentDir = new File(StaffProgram.STUDENT_DIR); //fileHandller.getFile();
		File[] students = studentDir.listFiles();
		boolean submission = false;
		String submissions = "The following students have made submissions:\n";
		for(File student:students) {
			if(student.listFiles().length > 1) {
				submission = true;
				submissions += "\t" + student.getName() + "\n";
			}
		}
		if(submission) {
			System.out.print(submissions);
		} else {
			System.out.println("No Students have made submissions");
		}

		logger.log("Listed Submissions",StaffProgram.STUDENT_DIR);

		//fileHandller.close();
	}

	public void download(String uid, String destination) {
		File studentDir = new File(StaffProgram.STUDENT_DIR);
		File[] studentDirs = studentDir.listFiles();

		for(File student:studentDirs) {
			if(student.getName().equals(uid)) {
				File[] studentFiles = student.listFiles();
				if(studentFiles.length > 1) {
					for(File assignFile:studentFiles) {
						if(!(assignFile.getName().equals("results"))) {
							fileHandller = new FileHandller(assignFile.getAbsolutePath());
							fileHandller.downloadFile(destination);
							fileHandller.close();
							logger.log("Downloaded assignment", assignFile.getAbsolutePath());
							return;
						}
					}
				}
			}
		}
		System.out.println("Could not find assigment of student with uid: "+uid);
	}

	public void mark(String uid) {
		File studentDir = new File(StaffProgram.STUDENT_DIR);
		File[] studentDirs = studentDir.listFiles();
		for(File student:studentDirs) {
			if(student.getName().equals(uid)) {
				File[] studentFiles = student.listFiles();
				if(studentFiles.length > 1) {
					File markFile = new File(student.getAbsolutePath()+"/results/result.txt");
					if(!markFile.exists()) {
						try {
							System.out.println(markFile.getAbsolutePath());
							markFile.createNewFile();
							fileHandller = new FileHandller(markFile.getAbsolutePath());
							Scanner in = new Scanner(System.in);
							System.out.print("Enter the mark (%): ");
							int mark = in.nextInt();
							in.nextLine();
							System.out.println("Enter any comments: ");
							String comment = in.nextLine();
						
							fileHandller.appendFile(String.format("%d%%\n%s\n", mark, comment));
							fileHandller.close();

							logger.log("Submitted mark for "+uid, markFile.getAbsolutePath());
							return;
						} catch (IOException e) {
							System.err.println(e);
						}
					}
				}
			}
		}

		System.err.println("Cannot submit mark: Student does not exist or has not yet submitted");
	}
}
