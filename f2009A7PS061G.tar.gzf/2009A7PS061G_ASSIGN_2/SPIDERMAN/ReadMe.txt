

---This assignment is submitted by Praveen Prakash Oak(2009A7PS061G)
I have Interacted with the following people while completing this assignment
1.Aniket Panse
2.Rachit Maheshwari
3.Chaitanya Datye

---The program can be compiled by typing make after going into the assignment folder and run by typing ./exec
---The input should be given in a file called input.txt(a file by that name is already provided in that folder, if a new file is to be given replace the given file)


--program is complete

---The general structure that I have followed in implementing this assignment is:
1.I have taken input from file named input.txt

2.Once input is read I am creating a new process and inside this process I am called a recursive function

3.This recursive function keeps creating 2 new processes as long as it is inside bounds ot 2D array

4.If MJ is found then I am printing the information inside the child itself and exiting all processes

5.Else I am passing status of processes all the way up to tell that MJ ws not found

------------DESCRIPTION OF FILES-----------------

1.spiderman.c----this is the execution file

2.headerfile.h---contains one method to take input and one recursive method to find MJ
