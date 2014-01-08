/** User.cpp  Copyright (c) Alexander Brown, March 2011 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "Logger.h"

#include <termios.h>
#include <unistd.h>

#include "User.h"
#include "UserCreator.h"
#include "Setup.h"
#include "UserType.h"

using namespace std;

/**
 * Sets whether the stdin stream should echo to
 * the console or not.
 *
 * @param enable If stdin echo is enabled or not.
 *		defaults to true.
 * Note: Linux systems only.
 * @author Unknown (taken from Stack Overflow).
 */
void SetStdinEcho(bool enable = true) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable)
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

User *User::_INSTANCE = NULL;

User::User(Logger *logger, std::string uid): _logger(logger), _uid(uid) {
}

User::~User() {
    _logger = NULL;
    _INSTANCE = NULL;
}

User* User::login(Logger *logger) throw (std::string) {
    // TODO decide if it would be best to break this function down further.
    if (_INSTANCE == NULL) {
        std::string user;
        std::string pass;

        cout << "Enter User ID: ";
        cin >> user;

        cout << "" << user << "'s password: ";

        SetStdinEcho(false);
        cin >> pass;
        SetStdinEcho(true);
        cout << endl;
        
        ifstream authstream(Setup::AUTH_FILE.data());

        if (!authstream.is_open()) {
            std::string t = "Error opening '" + Setup::AUTH_FILE + "'";
	    throw t;
        }

        bool authenticated = false;
        string line;


        while (authstream.good()) {
            getline(authstream, line);
            if (line.data()[0] != '#') {
                if (line.find((user + " admin " + pass).data()) != string::npos) { // TODO See if this can be made more secure.
                    authenticated = true;
                }
            }
        }

        if (!authenticated) {
            std::string t = "Invalid Username/Password";
	    throw t;
        }

        _INSTANCE = new User(logger, user);

        authstream.close();
    }
    return _INSTANCE;
}

std::string User::get_uid() {
    return _uid;
}

std::string User::add_user(std::string uid, UserType type) {
    UserCreator creator(uid, type);
    return creator.create_user();
}

std::string User::add_staff(std::string uid) {
    enum UserType type = STAFF;
    std::string pass = add_user(uid, type);
    _logger->log("Created Staff User", Setup::AUTH_FILE);
    cout << "Created Staff User: " << uid << endl << "password: " << pass << endl;
    return pass;
}

std::string User::add_student(std::string uid) {
    enum UserType type = STUDENT;
    std::string pass = add_user(uid, type);
    _logger->log("Created Student User", Setup::AUTH_FILE);
    cout << "Created Student User: " << uid << endl << "password: " << pass << endl;
    return pass;
}
