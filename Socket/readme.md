# What is socket

 Socket is communication channel in C. It's like a pipe, but with difference that it can be used to communicate between two different machines.

## How to use it

1.You can try to use it on your own, simply by opening two terminals and compiling client file on one, and server file on the seconod one. 
2.Then you need to get your current IP adress. Below i'm explaining how to do it. 
3.When you'll get your IP adress, then you have to paste it in the both server and client inet address (it's commenter line, i'm sure you'll find it)
4.The last step is to compile these files and run them seperately on two terminals.

## How to get your current IP adress
 
 -If you're using windows OS you have to:
   1.Open command line (Win + R) and then write cmd and click enter
   2.In command line write command: 
   ```bash
   ipconfig /all
   ```
   3.Then find the line with the beginning of: Adress IPv4

 -If you're using Linux OS you have to:
   1.Open terminal
   2.write command: 
   ```bash
   ifconfig
   ```
   3.Then find the line with inet addr: 

 
