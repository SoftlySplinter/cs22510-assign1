/* UserCreator.h Copyright (c) Alexander Brown, March 2011 */

#ifndef _USERCREATOR_H
#define _USERCREATOR_H

#include <string>

#include "UserType.h"

class User;
class Logger;
class FileHandller;

/**
 * @brief Handles the creation of users.
 * 
 * This classes defines the behaviour to use when creating
 * new users, ensuring this behaviour is standardised.
 *
 * @author Alexander Brown
 * @version 1.0
 */
class UserCreator {
public:
	/** Constructs a UserCreator with the given uid and type. */
	UserCreator(std::string uid, enum UserType type);

	/** Destructs the UserCreator. */
	~UserCreator();

	/** Writes the user to the .auth file */
	std::string create_user();
private:
	/** The file handller */
	FileHandller * _file_handller;

	/** The User ID of the user to create */
	std::string _uid;

	/** The generated password for the User */
	std::string _password;

	/** The type of the User */
	enum UserType _type;

	/** Generates a random password */
	std::string generate_password();
};

#endif  /* _USERCREATOR_H */
