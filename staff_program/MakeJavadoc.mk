WINDOWTITLE = 'Alexander Brown - CS22510: Staff Program'
DOCTITLE = 'Staff Program API'
HEADER = '<b>Staff Program</b> v1.0'
FOOTER = 'All material &copy; Alexander Brown, March 2011.'
PACKAGE = 'uk.ac.aber.users.adb9.cs22510.staff_program'

all:
	javadoc -quiet -sourcepath staff_program/src/ -d staff_program/javadoc/ -use -splitIndex -windowtitle $(WINDOWTITLE) -doctitle $(DOCTITLE) -header $(HEADER) -bottom $(FOOTER) -subpackages $(PACKAGE)
