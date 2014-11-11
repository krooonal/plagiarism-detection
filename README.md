plagiarism-detection
====================

Detect plagiarism in single and multi-file assignments (only C language as of now).

Uses flex, bash, wxPython, gcc 

**File Info**

FindSim.sh -> To find similarities between two single file assignments<br />
README.md -> This File<br />
compare.cpp -> To compare the tokens generated using KMP algo<br />
directory.sh -> To find similarities between mutiple single file assignments<br />
directoryas.sh -> To find similarities between multiple multi-file assignments<br />
pld.py -> GUI for this system<br />
recompile.sh -> To recompile the entire code whenever there is any change in tokenizerC.l or compare.cpp<br />
removeComments1.sh -> To remove comments and pre process a file<br />
tokenizerC.l -> Tokenizer for C files<br />
singleFileTestDir -> test codes<br />
other directories -> multiple file assignments

**Usage**

The plagiarism detection system is very easy to use and modify according to the changes needed. Here are the necessary commands to use the system.

After every modification of the system source code or before the first usage <br />
sh recompile.sh

For comparing two programs say testcode1.c and testcode2.c <br />
sh FindSim.sh /path/to/testcode1.c /path/to/testcode2.c

For comparing all single source file submission in a directory say submission <br />
bash directory.sh /path/to/submission

For comparing all multiple source files assignment submission in a directory say submissions <br />
bash directoryas.sh /path/to/submission

To use GUI <br />
./pld.py

Known BUG: All filenames and directory names must not have spaces in them
