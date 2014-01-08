/* Setup.cpp  Copyright (c) Alexander Brown, March 2011 */

#include <string>
#include <iostream>
#include <fstream>

#include "Setup.h"
#include "FileHandller.h"
#include "Logger.h"

using namespace std;

std::string get_base_dir() {
    string line = "";
    ifstream config_file("config");
    if(config_file.is_open()) {
        getline(config_file, line);
    }
    line = line + "/";
    return line;
}

std::string get_repo_dir() {
    string line = "";
    ifstream config_file("config");
    if(config_file.is_open()) {
        getline(config_file, line);
        getline(config_file, line);
    }
    line = line + "/";
    return line;
}


// Change this to change the base directory.
const std::string Setup::BASE_DIR = get_base_dir();
const std::string Setup::REPO_DIR = get_repo_dir();

// Constant definitions.
const std::string Setup::AUTH_FILE = BASE_DIR+".auth";
const std::string Setup::LOG_FILE = BASE_DIR+"logfile.log";
const std::string Setup::ASSIGNMENT_DIR = BASE_DIR+"assignment/";
const std::string Setup::STUDENT_DIR = BASE_DIR+"students/";

Setup::Setup(Logger* logger): _logger(logger) {

}

Setup::~Setup() {
    _logger = NULL;
}

void Setup::upload_assignment(std::string src) throw (std::string) {
    int pos = src.find_last_of('/');
    std::string filename = src.substr(pos+1, src.length());

    FileHandller::upload_file(src, ASSIGNMENT_DIR+filename);
    
    _logger->log("Uploaded Assignment", ASSIGNMENT_DIR+filename);
}
