Name : Phaneendra Hari
ID : 2007A7PS069G
Question 1 of Assignment 2

-------------------------------------------------------------------------------------------------------------------
List of Files:
-------------
headerFile.h		:	File Containing the required header files for the assignment
implimentation.c	:	File containing the functions and variables used in the problem
implimentation.o	:	Object file of the implimentationFile.c
driverFile		:	File containing the main()
makeFile		:	executable File of the complete problem

All the files belong to Question Number 1 of assignment 2.
--------------------------------------------------------------------------------------------------------------------

How to Compile:
--------------

After extracting the individual files, 

gcc -o exe driverFile.c implimentation.o

How to Execute:
--------------
After extracting the individual files from the compressed .tar.gz file, type the following command to execute the program

./makeFile

--------------------------------------------------------------------------------------------------------------------
Structure of Program
--------------------
Implimentation file consists of
1)A function to read from the kepboard the size of the Square Matrix
2)A function to perform the rest of the problem. That is,
	a)A matrix values are read from the keyboard and are entered into a N*N matrix.
	b)Input values of the matrix are screened for illogical numbers i.e only 1 and 0 are allowed to enter into the matrix
	c)The problem of Spiderman and MJ is solved using, "Recursive Backtracking Algorithm". Details about which were found from 		wikipedia.com and other Computer Science help sites
		(i) In the Input Matrix, lets assume that all the 0 values are potential nodes.
		(ii)The program starts from (0,0), where a child process is created and it proceeds into horizontal/vertical 			direction. At each node encountered new child processes are created.
		(iii)If a child process encounters '1', then it backtracks a node and will proceed in vertical/horizontal direction 			depending on its previous movement
		(iv)The whole set of program statements are placed in an infinite loop, which can be broken only when a successful 			path is	established or a path cannot be extablished.
	d) Another Matrix is used to keep track of the path that is being followed and later printed out.

----------------------------------------------------------------------------------------------------------------------------
What I have/haven't done:
------------------------
1)I have finished Question 1 with a logical and runtime error
	The logical and runtime error are the same in this case. Due to usage of Recursive algorithm, multiple child and parents are created. They inturn lead to creating large number of children. I couldnt properly control the life span of the processes. This lead to the program repeating itself a very large numeber of times, sufficient enough to hang the computer.

This could have been avoided with proper usage of wait() and exit() functions.

2)I havent done Question 2

Problems I have faced:
---------------------
1)I am facing problem with solving questions which have Multiple looping & conditional fork() functions. I have understood the theory behind fork() function but when it came to application of it, I am confused.

2)Multiple child creation from the same parent, each child having a different task. writing a program from the process tree.







