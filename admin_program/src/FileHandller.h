/* FileHandeller.h  Copyright (c) Alexander Brown, March 2011 */

#ifndef _FILEHANDLLER_H
#define	_FILEHANDLLER_H

/**
 * @brief A file handller for a single file.
 *
 * Due to the nature of the repository and the need for locking, it is best that
 * all file operations are handlled properly. This class enforces the locking
 * mechanism (calling the File Lock class) and performs basic operations with
 * files found in the repository.
 *
 * @author Alexander Brown
 * @version 1.0
 * @see FileLock
 */
class FileHandller {
public:
	/**
	 * Creates a file handller for a given file.
	 * @param filename      The file to work with.
	 */
	FileHandller(std::string filename);

	/**
	 * Destructor.
	 */
	virtual ~FileHandller();

	/**
	 * Uploads the local sorce file to the destination file in the repository.
	 * @param src_filename  The location of the local file to upload.
	 * @param dest_filename The destination of the source file.
	 * @see copy()
         * @return               <code>true</code> - If the operation completed sucessfully
	 */
	static bool upload_file(std::string src_filename,
		std::string dest_filename) throw (std::string);

	/**
	 * Downloads the current file from the repository.
	 * @param dest_filename The location of the file to download to.
	 * @see copy()
         * @return               <code>true</code> - If the operation completed sucessfully
	 */
	bool download_file(std::string dest_filename) throw (std::string);

	/**
	 * Appends a given string to the current file.
	 * @param append_text   The string to append.
	 * @return		<code>true</code> - If the operation completed sucessfully
	 */
	bool append_file(std::string append_text);
private:
	/** The current file in the repository. */
	std::string _filename;

	/**
	 * Copies the src file to the destination file.
	 * @param src_filename  The location of the file to copy.
	 * @param dest_filename The destination of the source file.
	 * @return               <code>true</code> - If the operation completed sucessfully
	 */
	static bool copy(std::string src_filename, std::string dest_filename);
};

#endif	/* _FILEHANDLLER_H */

