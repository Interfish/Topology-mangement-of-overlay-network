
# Description

This is a implemeentaion of T-MAN protocal. It's also the solution for assignment 1 of EEL6935 Distributed Computing, University of Florida, spring 2017.

"Overlay topology plays an important role in P2P systems. Topology serves as a basis for achieving functions such as routing, searching and information dissemination, and it has a major impact on their efﬁciency, cost and robustness. Furthermore, the solution to problems such as sorting and clustering of nodes can also be interpreted as a topology. In this paper we propose a generic protocol, T-Man, for constructing and maintaining a large class of topologies. In the proposed framework, a topology is deﬁned with the help of a ranking function. The nodes participating in the protocol can use this ranking function to order any set of other nodes according to preference for choosing them as a neighbor. This simple abstraction makes it possible to control the self-organization process of topologies in a straightforward, intuitive and ﬂexible manner. At the same time, the T-Man protocol involves only local communication to increase the quality of the current set of neighbors of each node. We show that this bottom-up approach results in fast convergence and high robustness in dynamic environments. The protocol can be applied as a standalone solution as well as a component for recovery or bootstrapping of other protocols."

You can find the paper here: [T-Man: Gossip-based Overlay Topology Management](http://www.cs.unibo.it/babaoglu/papers/pdf/tman)

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
