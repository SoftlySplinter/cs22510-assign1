
#include <iostream>
#include "FileLock.h"

using namespace std;

int main(int argc, char ** argv) {
	try {
		FileLock l(argv[1]);
		while(true) {
			;
		}
	} catch (std::string e) {
		cout << e << endl;
	}
}
