package uk.ac.aber.users.adb9.cs22510.staff_program;

import java.util.Scanner;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class StaffProgram {
	private static final File CONFIG_FILE = new File("config");

	public static final String BASE_DIR = getBaseDir();
	public static final String LOG_FILE = BASE_DIR + "logfile.log";
	public static final String AUTH_FILE = BASE_DIR + ".auth";
	public static final String STUDENT_DIR = BASE_DIR + "students/";

	/**
	 * Defins the list option
	 * @see User#list()
	 */
	private static final char LIST = 'l';
	
	/**
	 * Defines the get option
	 * @see User#get(String uid, String destPath);
	 */
	private static final char GET  = 'g';
	
	/**
	 * Defines the mark option
	 * @see User#mark(String uid);
	 */
	private static final char MARK = 'm';
	
	/** Defines the quit option */
	private static final char QUIT = 'q';
	
	/** 
	 * Defines the help option
	 * @see help()
	 */
	private static final char HELP = 'h';
	
	/** Defines the Unrecognised option, used to continue looping the menu. */
	private static final char NONE = ' ';

	public static void main(String args[]) {
		Logger logger = new Logger();
		User user = null;
		try {
			user = User.login(logger);
		} catch (InvalidUserException e) {
			System.err.println(e.getMessage());
			System.exit(1);
		}
		
		logger.setUser(user);

		char option = NONE;
		Scanner in = new Scanner(System.in);

		while (option == NONE) {
			System.out.print("Enter option code (h for help): ");
			option = in.next().charAt(0);
			String uid = "";
			switch (option) {
				case LIST:
					user.list();
					break;
				case  GET:
					System.out.print("Enter the uid of the student to get the submission of: ");
					uid = in.next();
					System.out.print("Enter the location you wish to download this submission to: ");
					String file = in.next();
					user.download(uid, file);
					break;
				case MARK:
					System.out.print("Enter the uid of the student to submit a mark for: ");
					uid = in.next();
					user.mark(uid);
					break;
				case QUIT:
					break;
				case HELP:
					StaffProgram.help();
					option = NONE;
					break;
				default:
					System.out.println("Unrecognised option '"+option+"'");
					option = NONE;
			}
		}
	}
	
	/** Prints out the help options */
	private static void help() {
		System.out.printf("\t%s - List all students with submitted work.\n"
		+"\t%s - Download a specified student's work.\n"
		+"\t%s - Submit a mark for a specified student's work.\n"
		+"\t%s - Quit the program.\n", 
		LIST, 
		GET, 
		MARK, 
		QUIT);
	}

	/**
	 * Gets the Base Directory from the config file
	 * @return The path of the Base Directory
	 */
	private static String getBaseDir() {
		try {
			String line = "";
			if(CONFIG_FILE.exists()) {
				Scanner s = new Scanner(new InputStreamReader(
						new FileInputStream(CONFIG_FILE)));
				line = s.nextLine();
			}
	
			return line+"/";
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
			return "";
		}
	}
}
