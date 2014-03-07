# CS22510 Assignment One 2010–2011

*This was an assignment which I completed in 2011.*

> Fred Long
> 
> 4 March 2011

## Introduction

This is the first of two CS22510 assignments. It will count for 30% of the total
marks for the module. You should spend roughly 20 hours of effort on this
assignment.

**Deadline:** This assignment should be posted in the Departmental Coursework
Postbox **between 11:00am. and 2:00pm. on Friday, 25th March 2011**.

Notes:

1. If there is good reason why you cannot hand in the assignment via the
Departmental Coursework Postbox, you must make alternative arrangements with me
(or, exceptionally, with another member of staff) to hand in the assignment
before the deadline.
2. If you hand in work at a time other than that specified you must ensure that
the work is dated and a receipt obtained.
3. Work which is handed in after the deadline, without prior permission (which
is rarely given), will usually receive no marks. If you do hand in your work
after the deadline, please also submit a “Late Assignment” form explaining why
the work was handed in late.
4. If you feel that you have a very good reason for handing in your work late,
you must seek the permission of the year co-ordinator (Rhys Parry
<rrp@aber.ac.uk>) before the deadline for handing in the work. In almost all
cases you will be told to hand in the work, in an incomplete state, by the
deadline, and complete a Special Circumstances Form explaining the circumstances
that made it impossible for you to complete the work, which must be accompanied
by supporting evidence.
5. The assignment will not be returned to you. Therefore, if you want to keep a
copy of it, you should make your own copy before submitting your assignment.
6. Because this is a coding assignment it cannot be submitted anonymously. Every
piece of code submitted should show, in a header comment, the author of the
piece of code.

## The Main Task

You are required to write the code for a distributed system that simulates a
student assignment submission system (details below).

The system consists of three programs:

### Administrative Program

This program allows an administrator to set up the system for an assignment.

### Student Program

This program has two functions. It allows students to copy a file containing
their assignment from their own filestore into the central filestore. It also
allows them to retrieve their result for the assignment and any comments from
the marker after their assignment has been marked.

### Staff Program

This program also has two functions. It allows a member of staff to copy a file
from the central filestore into their own filestore for marking. It also allows
the member of staff to upload their result and comments about the assignment.

You must write one of the programs in Java, one in the C Programming Language,
and one in C++. Which program you write in which language is up to you.

## The general requirements are:

* The system will simulate the operation of a student assignment submission
  system. For simplicity in this prototype, the system need deal with the
  submissions from one class of students for only one assignment.
* There is one “log file” available to the system. Every time any of the three
  programs carries out an activity, a line is appended to this “log file”
  recording the date and time of the activity, which program caused the
  activity, and what the activity was.
* The administrator enters the userids of the students registered for the
  assignment and of the members of staff who will be involved in assessing the
  assignment.
* A staff or student userid is a string of at at least three and at most six
  lower-case letters or digits, beginning with a lower-case letter.
* Your system should allow for about twelve students and three members of staff,
  although your system should allow for a reasonable amount of expansion.
* When the administrator enters the userid of a student or member of staff, the
  system returns a randomly generated password of between eight and twelve
  characters. (The password is communicated to the student or member of staff by
  a mechanism that is outside of the system and this need not concern you. Also,
  you do not need to worry about encrypting the password.) The list of students
  and members of staff able to access the assignment system, with their
  passwords, is maintained in an ordinary file. It must be possible for the
  administrator to add new students and members of staff at any time.a
* The administrator's program maintains a directory structure with one directory
  for each student registered with the system.
* Also, the administrator's program can display the contents of the “log file”
  to the screen when requested by the administrator. (Of course, this is itself
  an activity and should be logged.)
* Once a student has been registered with the system and received their password
  from the administrator, they can use the Student Program to log in to the
  system (entering their userid and password) and, provided their credentials
  match an entry in the administrator's list of students and members of staff,
  they are prompted for a filename. The file is copied into the appropriate
  directory of the central system directory structure.
* Once a member of staff has been registered with the system and received their
  password from the administrator, they can use the Staff Program to log in to
  the system (entering their userid and password) and, provided their
  credentials match an entry in the administrator's list of students and members
  of staff, they are presented with a list of the students who have uploaded
  their assignments. The member of staff may then select one of these and
  specify a filename (not necessarily already in existence) in their own
  filestore to which the student's assignment file is copied.
* After a student's assignment file has been copied into a member of staff's
  filestore, the Staff Program should allow that member of staff to enter a mark
  and some textual comments into the central system. The mark and comments are
  read from the keyboard and written to a file in the same directory as the
  student's assignment is stored in the central system.
* After a member of staff has entered the mark and comments for a student into
  the central system, the Student Program should allow that student to access
  their result. The mark and comments are simply written to the screen.

I do not require sophisticated user interfaces for any of the programs. Simple
character-based I/O is sufficient.

Also, you do not need to worry about the confidentiality of the information in
your implementation of this prototype (but you will be asked to consider this in
Assignment Two.)

## Hints

This section contains some hints on how you might design and implement your
system. You do not have to follow any of these hints, as long as your system
satisfies the requirements set out above.

### File Locking

File locking is required to avoid the potential problem of file corruption due
to concurrent changes being made to the “log file”, and to avoid contention over
the administrator's list of students and members of staff.

File locking is platform dependent. Microsoft Windows supports mandatory file
locking and Unix-based platforms generally support cooperative file locking,
however this is sufficient for the application.

Java supports file locking in its `java.nio.channels.FileLock` Class which is
mapped to (and therefore is dependent on) the underlying operating system file
locking capabilities. Hence cooperative locking is provided by Java on most
\*nix based platforms.

When using C or C++, most Unix, Linux and MacOSX based systems support
Posix-based cooperative file locking using the fcntl() function specified in
fcntl.h.

The Microsoft Windows operating system supports mandatory locking using the
WinAPI LockFile functions on file handles. This requires use of the Microsoft
specific WinAPI libraries and therefore such code will only work on windows
platforms. Alternatively the Posix-based fcntl() functions could be used if the
Cygwyn DLL is installed on an MS Windows machine (this also provides the Gnu g++
series of compilers which may be used with NetBeans for example).

Example code illustrating simple use of the Java and Posix-based file locking
mechanisms are provided on Blackboard together with the URL for Cygwyn and the
Microsoft WinAPI documentation.

### System Construction

I suggest that you write the Administrative Program first and test it as a
stand-alone program, generating the data that would be produced by the other two
programs by hand.

The “log file” maintained by the system should help you in debugging your
program. Then you can write one of the other two programs, get that working, and
ensure that it interacts correctly with the data maintained by the
Administrative Program, again generating the data of the third program by hand.

Finally, complete the system by writing the third program.

## Assessment Criteria

This assignment will be assessed using the “Assessment Criteria for
Development”. See the Student Handbook, Appendix AA, via the URL:
http://www.aber.ac.uk/compsci/Dept/Teaching/Handbook/AppendixAA.pdf

The usual requirements for coding projects apply, namely that programs should be
well commented with comments that add real value and do not just, in essence,
duplicate code. Programs should have good layout and must use meaningful names
for variables, classes and other identifiers.

This assignment is worth 30% of the total marks available for this module.

## The Material You Must Submit

You must hand in:

* A printed version of all sections of the code of your system.
* Printout showing the results of attempting to compile your programs and any
  errors or warnings that are produced. If you use an IDE such as NetBeans to
  develop your code, screen images of the compiler output is acceptable.
* The printout of the output generated when running your system. You should run
  a simulation of the system and show a number of assignment submissions,
  assignment downloads by members of staff, result uploads, and result
  collection by students. Again, screen images is acceptable. Also, submit a
  printout of the “log file” produced by the system.
* A short written document describing your three programs. This document must be
  brief and should be at most two sides of A4 in length. Include diagrams if you
  wish to help explain your programs.
* A machine readable version of your system on either a floppy disk, CD, DVD, or
  pen drive. Note. The digital media that you submit will not be returned to
  you.

You must put all the material you hand in in a single folder and it must be
possible to read and write on all sheets that you hand in without having to
remove them from the folder. In particular, you must not hand in loose sheets in
a bag, or put everything in a single plastic pocket of a folder.

The “folder” does not need to be a commercially made folder, indeed, I'm happy
to accept sheets neatly stapled together as a “leaflet”.

The floppy disk, CD, DVD, or pen drive must be attached to your written material
in a sensible manner so that on the one hand it will not get lost, but on the
other hand, it is easy for me to remove and use. Also, the floppy disk, CD, DVD,
or pen drive must be labelled with your name, in case it becomes separate from
the main body of work.

NOTE: This is an “individual” assignment and must be completed as a one person
effort by the student submitting the work. Please take note of the statement on
Plagiarism and Unfair Practice which can be found in Section 5 of the Department
Handbook. See:
http://www.aber.ac.uk/compsci/Dept/Teaching/Handbook/handbook.htm

You must attach, to the front of your submission, a completed and signed copy of
the departmental standard assignment cover sheet which includes a Declaration of
Originality.

## Submission Date

Your solution to this assignment must be handed in to the Computer Science
Coursework Postbox between 11:00am. and 2:00pm. on Friday 25th March 2011.

It is not acceptable to miss any lecture for the purposes of completing
assignment work, in terms of the department's monitoring of student attendance
and any actions that might be taken in respect of poor attendance.

> F.W. Long,
> 
> 4th March 2011.
