package uk.ac.aber.users.adb9.cs22510.staff_program.io;

import java.io.File;
import java.io.IOException;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;

/**
 * A class to handle all file operations.
 * <p>
 * This class handles file operations the program needs to perform, which
 * ensures that file locking is performed when these operations are.
 *
 * @author	Alexander Brown
 * @version	1.0
 */
public class FileHandller {

	/**
	 * Uploads a file from the source location to the destination 
	 * location.
	 *
	 * @param dest			The destination filepath.
	 * @param src			The source filepath.
	 *
	 * @throws FileException	If the opertaion does not
	 * 				complete sucessfully.
	 *
	 * @see copy(String, String)
	 */
	public static void uploadFile(String dest, String src) throws FileException {
		FileLock l = new FileLock(dest);
		FileHandller.copy(dest, src);
		l.unlock();
	}

	/**
	 * Copies the source file to the destination file.
	 *
         * @param dest                  The destination filepath.
	 * @param src                   The source filepath.
	 *
	 * @throws FileException        If the opertaion does not
	 *                              complete sucessfully.
	 */
	private static void copy(String dest, String src) throws FileException {
		File srcFile = new File(src);
		File destFile = new File(dest);

		if (!srcFile.exists()) {
			throw new FileException("Source file does not exist");
		}
		if (!srcFile.canRead()) {
			throw new FileException("Source file is unreadable");
		}
		if (srcFile.isFile()) {
			if (!destFile.exists()) {
				try {
					//System.out.println("Creating file "+destFile.getAbsolutePath());
					destFile.createNewFile();
					
					FileInputStream in = new FileInputStream(srcFile);
					FileOutputStream out = new FileOutputStream(destFile);
					byte[] buffer = new byte[1024];
					int bytesRead = 0;
					
					//System.out.print("Copying "+srcFile.getAbsolutePath()+" to "+destFile.getAbsolutePath());
					while((bytesRead = in.read(buffer)) != -1) {
						out.write(buffer, 0, bytesRead);
						//System.out.println(".");
					}

					//System.out.println();
	
					in.close();
					out.close();
				} catch (IOException e) {
					throw new FileException("Error handlling file");
				}
			} else {
				throw new FileException("Cannot copy to an existing file");
			}
		} else {
			throw new FileException("Cannot copy dir");
		}
	}

	/** The filepath of the file to handle. */
	private String filepath;
	
	/** The file lock */
	private FileLock lock;

	/**
	 * Creates a file handller for the specified filepath.
	 *
	 * @param filepath	The file to handle.
	 */
	public FileHandller(String filepath) {
		this.filepath = filepath;
	}

	/**
	 * Downloads to current file to the destination file.
	 *
	 * @param destFilepath	The path of the destination file.
	 */
	public void downloadFile(String destFilepath) {
		lock = new FileLock(filepath);
		try {
			FileHandller.copy(destFilepath, filepath);
		} catch (FileException e) {
			System.err.println(e);
		}
		lock.unlock();
	}

	/**
	 * Appends the given string to the current file.
	 *
	 * @param appendText	The String to append to the file.
	 */
	public void appendFile(String appendText) {
		lock = new FileLock(filepath);
		try {
			BufferedWriter append = new BufferedWriter(new FileWriter(filepath, true));
			append.write(appendText);
			append.close();
		} catch (IOException ioe) {
			//TODO Something here.
		}
		lock.unlock();
	}

	/** Closes the file handller in the absense of a destructor */
	public void close() {
		lock.unlock();
	}

	/**
	 * Gets the current file.
	 * @return The current file.
	 */
	public File getFile() {
		lock = new FileLock(filepath);
		File ret = new File(filepath);
		return ret;
	}
}
