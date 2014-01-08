/* Logger.cpp  Copyright (c) Alexander Brown, March 2011 */

#include <string>
#include <bits/basic_string.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "Logger.h"
#include "FileHandller.h"
#include "Setup.h"
#include "User.h"

using namespace std;

Logger::Logger() {
    _file_handller = new FileHandller(Setup::LOG_FILE);
}

Logger::~Logger() {
    delete _file_handller;
    _user = NULL;
}

void Logger::set_user(User* user) {
    _user = user;
}

void Logger::log(std::string activity, std::string filepath) {
	bool complete = _file_handller->append_file(generate_log_entry(activity, filepath));
	if(!complete) {
		log(activity, filepath);
	}
}

std::string Logger::generate_log_entry(std::string activity,
        std::string filepath) {
    std::string entry = encode_date_time();
    entry += " admin: ";
    entry += _user->get_uid() + "\t";
    entry += activity + "\t";
    int base_dir_pos = filepath.rfind(Setup::BASE_DIR);
    filepath = filepath.replace(base_dir_pos, base_dir_pos + Setup::BASE_DIR.length(), "");
    filepath = Setup::REPO_DIR + filepath;
    entry += filepath;


    return entry;
}

std::string Logger::encode_date_time() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [20];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 20, "%Y-%m-%d-%H-%M-%S", timeinfo);

    return std::string(buffer);
}

void Logger::read_log() {
    ifstream authstream(Setup::LOG_FILE.data());

    if (!authstream.is_open()) {
        throw string("Error opening '" + Setup::LOG_FILE + "'");
    }
    string line;
    getline(authstream, line);


    while (authstream.good()) {
        if (line.data()[0] != '#') {
            cout << "========================================" << endl;
            std::string date_time = line.substr(0, 20);
            line = line.substr(20, line.length());
            date_time = decode_date_time(date_time);

            std::string user_type = line.substr(0,5);
            line = line.substr(7, line.length());

            std::string user = line.substr(0, line.find("\t"));
            line = line.substr(line.find("\t")+1, line.length());

            std::string action = line.substr(0, line.find("\t"));
            line = line.substr(line.find("\t")+1, line.length());
            
            cout << date_time;
            cout << "User:\t\t" << user << endl;
            cout << "Program:\t" << user_type << endl;
            cout << "Action:\t\t" << action << endl;
            cout << "File:\t\t" << line << endl;
        }
        getline(authstream, line);
    }
    cout << "========================================" << endl;

    authstream.close();
}

std::string Logger::decode_date_time(std::string date_time) {
    struct tm tm;
    strptime(date_time.data(), "%Y-%m-%d-%H-%M-%S ", &tm);
    
    char buffer[80];
    strftime(buffer, 80, "Date:\t\t%d/%m/%Y\nTime:\t\t%H:%M:%S\n", &tm);

    return std::string(buffer);
}
