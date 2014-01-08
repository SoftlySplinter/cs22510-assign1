/* FileHandller.cpp Copyright (c) Alexander Brown, March 2011 */

#include <string>
#include <fstream>
#include <ios>
#include <iostream>

#include "FileHandller.h"
#include "FileLock.h"

using namespace std;

FileHandller::FileHandller(std::string file) : _filename(file) {
}

FileHandller::~FileHandller() {

}

bool FileHandller::append_file(std::string append_text) {
	try {
		FileLock lock(_filename);

		std::ofstream dest;
		dest.open(_filename.data(), ofstream::app);
		dest << append_text << endl;
		dest.close();
		// lock automatically freed and unlocked here.
		return true;
	} catch (std::string e) {
		//cout << "Append Failed: " << e << endl;
		return false;
	}
}

bool FileHandller::download_file(std::string dest_filename) throw (std::string) {
	try {
		FileLock lock(_filename);
		return FileHandller::copy(_filename, dest_filename);
		// lock automatically freed and unlocked here.
	} catch (std::string e) {
		cout << "Download Failed: " << e << endl;
	}
}

bool FileHandller::upload_file(std::string src_filename ,
		std::string dest_filename) throw (std::string){
	try {
		FileLock lock(dest_filename); //Lock the file if it exists.
	} catch (std::string e) {
		if(e == "File Descriptor Error") {
			// Do nothing - the file needs to be created instead, defying the point of locking it.
		} else {
			throw e; //Otherwise the file is locked.
		}
	}
	return copy(src_filename, dest_filename);
	// Lock automatically freed and unlocked here.
}

bool FileHandller::copy(std::string src_filename, std::string dest_filename) {
        std::ifstream src;
        std::ofstream dest;

        src.open(src_filename.data(), std::ios::binary);
        dest.open(dest_filename.data(), std::ios::binary);

        if (!src.is_open() || !dest.is_open()) {
            return false;
        }
        dest << src.rdbuf();

        dest.close();
        src.close();
	return true;
}
