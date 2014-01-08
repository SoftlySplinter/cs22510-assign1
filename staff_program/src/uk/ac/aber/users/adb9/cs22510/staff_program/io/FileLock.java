package uk.ac.aber.users.adb9.cs22510.staff_program.io;

import java.io.File;
import java.io.RandomAccessFile;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.channels.FileChannel;

/**
 * Creates a lock on a given file.
 * <p>
 * This class deals with the file locking behaviour needed for the program,
 * using the newer java.nio classes to facilitate this behaviour.
 *
 * @author	Alexander Brown
 * @version	1.0
 */
public class FileLock {
	/** The filepath to the locked file */
	private String filepath;

	/** The Java File Lock */
	private java.nio.channels.FileLock javaLock;

	/** The file channel of the file */
	private FileChannel channel;

	/**
	 * Creates the FileLock and ensures it is locked.
	 *
	 * @param filepath	The filepath to the locked file
	 */
	public FileLock(String filepath) {
		this.filepath = filepath;
		this.lock();
	}

	/**
	 * Performs to actual lock.
	 */
	private void lock() {
		try {
			File file = new File(filepath);
			channel = new RandomAccessFile(file, "rw").getChannel();
			javaLock = channel.lock();
		} catch (FileNotFoundException fnfe) {
			System.err.println(fnfe);
		} catch (IOException ioe) {
			System.err.println(ioe);
		}
	}

	/**
	 * Unlocks the file as Java has no proper deconstructor
	 */
	public void unlock() {
		try {
			javaLock.release();
			channel.close();
		} catch (IOException ioe) {
			//System.err.println(ioe);
		}
	}
}
