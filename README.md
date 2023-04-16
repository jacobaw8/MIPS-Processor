This MIPS processor was made by Jacob Webb. I struggled to complete this by myself, but I did an alright job by the end.
I thought about how I could make this object oriented, and I decided that one object made a lot more sense to me than multiple.
For that reason, I just have one object, called Program, that acts as a processor and counts all of the important stats.
I struggled to control data memory, and that function might not work as a result. It confused me how it could possibly overwrite
the instruction memory when they were combined into one array. However, I guess the input is what will determine if it gets 
overwritten. Safe input will work. 

To use you can run the following commands

make all
make run FILE=<FILE_NAME> FLAG=<OPTIONAL_FLAG>

the file input will default to "in.bin" if not specified

The only allowed flag is -s, which enables single step mode

In single step mode, you must press enter between each instruction.


You can also just compile it normally and run it like so:

./a.out <FILE_NAME> <OPTIONAL_FLAG>