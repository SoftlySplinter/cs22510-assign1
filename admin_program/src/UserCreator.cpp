/* UserCreator.cpp  Copyright (c) Alexander Brown, March 2011 */

#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "UserCreator.h"
#include "Setup.h"
#include "FileHandller.h"

UserCreator::UserCreator(std::string uid, enum UserType type) : _uid(uid), _type(type) {
    _file_handller = new FileHandller(Setup::AUTH_FILE);
}

UserCreator::~UserCreator() {
    delete _file_handller;
}

std::string UserCreator::create_user() {
    std::string passwd = generate_password();
    std::string entry = _uid + " ";
    switch (_type) {
        case STAFF:
            entry += "staff ";
            break;
        case STUDENT:
            entry += "stdnt ";
	    mkdir((Setup::STUDENT_DIR+_uid+"/").data(), 0744);
	    mkdir((Setup::STUDENT_DIR+_uid+"/results/").data(), 0744);
	    break;
        default:
            entry = "#" + entry; //Something went wrong so comment it out.
    }
    entry += passwd;
    _file_handller->append_file(entry);
    return passwd;

}

std::string UserCreator::generate_password() {
    srand(time(NULL));
    int passwd_length = 8 + (rand() % 5);
    std::string passwd = "";

    for (int i = 0; i < passwd_length; i++) {
        /* Modulo of the last character of the characters we want (z, as
         * lowercase is after uppercase and numbers) minus the first character,
         * plus one to make it encompass them all. Plus the starting character).
         */
        char c = rand() % ('z' - '0' + 1) + '0';
        passwd += c;
    }

    return passwd;
}
