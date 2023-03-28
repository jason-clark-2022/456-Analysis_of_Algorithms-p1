RUNNING PROGRAM
if using school servers with the program folder as directory you can use the following command
to compile and run:

make run

you can also clear the executable file with the command:

make clean

The program was written in c++, so if the make commands are not working to run the file, you 
can also use c++ compiler commands, the only file that should need to be compiled is the file
"HuffmanCoding.cpp". 

USING THE PROGRAM
once the program is compiled and running, the user will be promped to enter the name of a file
without the .txt extension. Once a valid user input which yields a filename is entered
(ie LittleWomen) the program will create a huffman tree for that document. The user will then
be prompted to enter in another file which will be encoded and decoded throught the tree that was
previously created. The encoded file will be stored under "filename_ENC.txt". The decoded file will
be stored into "filename_DEC.txt". After successful compression / decompression, the program will 
then terminate.

OTHER
The report will also be stored in the same file folder as the source code.