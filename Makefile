CPPC = g++
CPPFLAGS = -c -Wall
CC = gcc
CFLAGS = -Wall -std=c99
REPO = repository
PSWD = letmein


all: repository admin_prog staff_program student_program

repository:
	@echo Checking if $(REPO) exists 
ifneq "`test -d repository`" ""
	@echo $(REPO) does not exist, creating.
	mkdir $(REPO)
	
	@echo Creating logfile.
	echo -e "`date +%F-%H-%M-%S` init : $(USER)\tInitilisation\t$(REPO)/" >> $(REPO)/logfile.log
	echo -e "`date +%F-%H-%M-%S` init : $(USER)\tInitilisation\t$(REPO)/logfile.log" >> $(REPO)/logfile.log
	
	@echo Creating user with username: $(USER) and password: $(PSWD)
	echo "#USER TYPE PASS" >> $(REPO)/.auth
	echo -e "`date +%F-%H-%M-%S` init : $(USER)\tInitilisation\t$(REPO)/.auth" >> $(REPO)/logfile.log
	echo "$(USER) admin $(PSWD)" >> $(REPO)/.auth
	echo -e "`date +%F-%H-%M-%S` init : $(USER)\tCreated user $(USER)\t$(REPO)/.auth" >> $(REPO)/logfile.log
	
	@echo Creating assignment directory
	mkdir $(REPO)/assignment
	echo -e "`date +%F-%H-%M-%S` init : $(USER)\tInitilisation\t$(REPO)/assignment/" >> $(REPO)/logfile.log
	
	@echo Creating students directory
	mkdir $(REPO)/students
	echo -e "`date +%F-%H-%M-%S` init : $(USER)\tInitilisation\t$(REPO)/students/" >> $(REPO)/logfile.log
	
	@echo Creating config file
	echo "`pwd`/$(REPO)" > config
	echo "$(REPO)" >> config
endif

admin_prog: admin_program.o admin_program_doc
	@echo Compiling Admin Program.

admin_program.o:
	$(CPPC) -Wall admin_program//src/main.cpp admin_program/src/Setup.cpp admin_program/src/Logger.cpp admin_program/src/User.cpp admin_program/src/UserCreator.cpp admin_program/src/FileHandller.cpp admin_program/src/FileLock.cpp -o admin_prog

admin_program_doc:
	- cd admin_program && doxygen Doxyfile

staff_program: staff_program.jar staff_program_javadoc
	@echo Compiling Staff Program.

staff_program.jar:
	javac staff_program/src/uk/ac/aber/users/adb9/cs22510/staff_program/*.java staff_program/src/uk/ac/aber/users/adb9/cs22510/staff_program/io/*.java -d staff_program/dist
	jar cfm staff_prog.jar staff_program/META-INF/MANIFEST.MF -C staff_program/dist/ . 
	#/uk/ac/aber/users/adb9/cs22510/staff_program/* /uk/ac/aber/users/adb9/cs22510/staff_program/io/*

student_program: student_program.o student_program_doc
	@echo Compiling Student Program

student_program.o:
	$(CC) $(CFLAGS) student_program/src/main.c student_program/src/user.c student_program/src/logger.c student_program/src/file_lock.c student_program/src/utils.c -o student_prog

student_program_doc:
	doxygen student_program/Doxyfile

staff_program_javadoc:
include staff_program/MakeJavadoc.mk
