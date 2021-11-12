IGNORE_LINE_STR = "IGNORE_TAG"


# Order matters, so can't really do a dir listing
TARGET_H_FILE = "mrtest.h"
HEADER_DIR = "./includes"
HEADER_FILES = [
	"mrtest_internal.h",
	"mr_function_vector.h",
	"mr_testcase.h",
	"mrtest.h"
]

TARGET_C_FILE = "mrtest.c"
SRC_DIR = "./src/mrtest_files"
C_FILES = [
	"function_vector.c",
	"mrtest.c"
]

def createHeader():
	target_file = open(TARGET_H_FILE, 'w')
	for h in HEADER_FILES:
		with open(HEADER_DIR + "/" + h, 'r') as f:
			for l in f.readlines():
				if l.find(IGNORE_LINE_STR) == -1:
					target_file.write(l)
	target_file.close()
	return

def createCFiles():
	include_content = set()
	content = str()
	for c in C_FILES:
		with open(SRC_DIR + "/" + c, 'r') as f:
			for line in f.readlines():
				if line.find("#include") == 0:
					include_content.add(line)
				else:
					content += line
	
	f = open(TARGET_C_FILE, 'w')
	for x in include_content:
		f.write(x)
	f.write(content)
	return

if __name__ == '__main__':

	createHeader()
	createCFiles()