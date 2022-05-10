# Online-Banking-Management-System
This is a mini Project of course Operating System where I build a banking management system using low level C programming using system calls.


## To run the system

Firstly run the the program Sign_In.c to fill new data of accounts. 

-> gcc Sign_In.c -o Sign_In

-> ./Sign_In

Then Run the Server 

-> gcc -pthread Server.c -o Server

-> ./Server

Then Run the client 

-> gcc Client.c -o Client 

-> ./Client
