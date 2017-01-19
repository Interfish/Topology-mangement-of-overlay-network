operating system:
	Linux wrtUbuntu 4.4.0-59-generic #80-Ubuntu SMP Fri Jan 6 17:47:47 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux
	Ubuntu 16.04.1 LTS \n \l

language written:
	C++

compiler version:
	g++
	gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.4) 

I use g++ command to complie. But I also write a makefile so you can just type 'make' to compile and 'make clean' to delete the object files and executable files.

There are mainly 3 parts inthis program.
TMAN.cpp:
	main fuctions for this program. It reads arguments and constructs Topology class instance. It will conduct different operations accroding to differentinput arguments.

Topology.cpp & TOpology.hpp:
	Defination and declarition of Topology class.

EasyBMP:
	It's a portable bmp image processing library. I use it in Topology.cpp to generate bmp file.
