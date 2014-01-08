/* main.cpp  Copyright (c) Alexander Brown, March 2011 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Setup.h"
#include "User.h"
#include "Logger.h"

#include "UserCreator.h"
#include "UserType.h"

using namespace std;

#define FLAG_CREATE_ASSIGN  'c'
#define FLAG_CREATE_STAFF   's'
#define FLAG_CREATE_STDNT   'd'
#define FLAG_PRINT_LOG      'l'
#define FLAG_HELP           'h'
#define FLAG_NO_OPTION      'n'

void print_help() {
    cout << "\t" << FLAG_CREATE_ASSIGN << " [file]: Upload Assignment\n";
    cout << "\t" << FLAG_CREATE_STAFF << " [uid]: Create a new Staff User\n";
    cout << "\t" << FLAG_CREATE_STDNT << " [uid]: Create a new Student User\n";
    cout << "\t" << FLAG_PRINT_LOG << ": Read the log file\n";
}

int main(int argc, char** argv) {
    try {
        char flag = FLAG_NO_OPTION;

        Logger *logger = new Logger();
        User * user = User::login(logger);
        logger->set_user(user);
        Setup * setup = new Setup(logger);

        if (argc < 2) {
            //Allow the user to input their own choice rather than forcing them to use command line arguments.
            do {
                cout << "Enter option code (h for help): ";
                cin >> flag;
                switch (flag) {
                    case FLAG_CREATE_ASSIGN:
                        break;
                    case FLAG_CREATE_STAFF:
                        break;
                    case FLAG_CREATE_STDNT:
                        break;
                    case FLAG_PRINT_LOG:
                        break;
                    case FLAG_HELP:
                        print_help();
                        //Intended fallthrough so that the program doesn't continue and exit.
                    default:
                        flag = FLAG_NO_OPTION;
                }
            } while (flag == FLAG_NO_OPTION);
        } else {
            flag = argv[1][1];
        }

        std::string option;
        switch (flag) {
            case FLAG_CREATE_ASSIGN:
                if (argc < 3) {
                    cout << "Enter the file (including path) of the assignment: ";
                    cin >> option;
                } else {
                    option = argv[2];
                }
                setup->upload_assignment(option);
                break;
            case FLAG_CREATE_STAFF:
                if (argc < 3) {
                    cout << "Enter the UID for the new staff user: ";
                    cin >> option;
                } else {
                    option = argv[2];
                }
                user->add_staff(option);
                break;
            case FLAG_CREATE_STDNT:
                if (argc < 3) {
                    cout << "Enter the UID for the new student user: ";
                    cin >> option;
                } else {
                    option = argv[2];
                }
                user->add_student(option);
                //TODO add something to create dir for the student.

                break;
            case FLAG_PRINT_LOG:
                logger->read_log();
                break;
            case FLAG_HELP:
                print_help();
                break;
            default:
                throw std::string("Unrecognised Option");
        }

        delete logger;
        delete user;
        delete setup;

        return (EXIT_SUCCESS);
    } catch (std::string e) {
        cout << argv[0] << ": " << e << endl;
        cout << "Useage: " << argv[0] << " [OPTION] [INPUT]" << endl;
        cout << "Try `" << argv[0] << " -h' for more information" << endl;
        return (EXIT_FAILURE);
    } catch (char const* c) {
	cout << c << endl;
    }
}
