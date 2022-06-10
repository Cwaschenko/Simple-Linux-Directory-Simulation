## Problem Description:

This project implements a simulator for a Linux file system.
A file system consists of files and directories.
The top directory is the root.
A directory in the file system may contain other files and directories.

Since a single directory may contain a variable number of files and directories, there are multiple options for representing a file system.
One option is to build a tree where each node of the tree is a file or directory, where each directory could have links to children (other files and directories).
Using a vector for children then allows for an arbitrary number of children.
You can see this type of structure in 17.2 of your Zybook.

For simplicity, we will use the same node structure for files and directories.
Nodes will contain an indicator (a character) to indicate whether the node is a file (f) or a directory (d).
Additionally, a node will maintain a pointer to its parent for easy reference to the parent from the child.

Using this structure, we will simulate a number of Linux commands that interact with this (simulated) file system.
The commands that are supported are the following:
```bash
ls                    # lists all files and directories in the current directory.
mkdir <dirname>       # creates a new directory within the current directory if it does not already exist
cd <dirname>          # changes the current working directory to the given dirname.
                      # We will assume that dirname, if exists, should be located in the current working directory.
                      # Also "cd .." changes to the parent directory.
pwd                   # prints the current working directory. ex;  /root/nextdir/etc
touch <filename>      # adds a file to the current directory
mv <fname1> <fname2>  # change the name of the file or directory to the specified file/directory name
                      # unlike in linux, this command is a simple rename and should not actually move anything
rm <filename/dirname> # locate and remove the file or directory.
                      # If the directory has files/directories inside, they also need to be removed (similar to the `-r` flag in linux.
                      # note that we will assume that the file or directory to remove is within the current directory
exit                  # ends the session
```

Error checking is required for this assignment.
For example, you should not create a file or a directory with a name that already exists in the current directory.
You should not switch to a directory that does not exist.
The root has no parent, and therefore, you should not switch to the parent directory if you are currently in the root.

The data structure will be available in the background and will grow as we add subdirectories and files, or shrink as we remove them.
However, real files and directories are not going to be created on your computer (hence, why we say this is simulated).

## Overview of the Interface:

Once the program is started, a root node is automatically created with the name /root.
The user is given a "$" prompt just like a Linux Terminal.
The user can then type the commands.
Your terminal should provide error messages when incorrect commands are entered (refer to the test suite files in [test/](test/) to see what these error messages should be).
The following sample run will demonstrate these commands.

### Sample run of program

Takes a second or so to start.
You can ignore the cd command.

![Sample execution of program](https://res.cloudinary.com/dm3fdmzec/image/upload/v1649473441/filesystem-demo_rkldq9.gif)

## Code Organization:

You will need to make sure that your code meets the following specifications.
Note that there is some room for interpretation, but a general code outline is given below.

### The Main File
The main file will create an instance of the terminal and start up the program.

### The Node class
![UML of Node class](http://www.plantuml.com/plantuml/png/VP7DJiKW48NtVGgMnPyNw3Nc6XUwySQeBy0j4sr2WS3Gn1ZVtM4apAQwwypvEESKZXbDmhAwONOcP_K4lgYluLhXPmGrgVd3f0EDtgnrp6YdZ6dnxxGaSN4sWM_2jC6C8TsSWeMBsmf4GogIpAkwUO4rRF08Ba8QUQjoEMC2q8HjOR67uPBnaIr_mpZ-YijmCTqX_hgpzhvMQOPSI-n4_zTI-5PozmXpvn1SvLu1d_aFMt3aGOiH0M_aFKgAQ0-0VoJqwnA8V4UzVyrCjHxCoE6Mhlixykv46Tsil-RtS0Hlo-f-0000)

This class class represents a file or directory within the file system.
Each node contains information for the name of the file or directory, the type ('**f**' for file and '**d**' for directory), and information on a node's children and parent.
The methods provided allow you to modify each of these values or to retrieve values based on the name of a file or directory.
Note, that `GetChildren` allows you to retrieve all the children that a node has.

Special attention should be paid to `RemoveChild` and `RemoveHelper`.
`RemoveChild` finds a child based on the name and removes it from the vector of children, however, before it can be erased, you need to take care of any children that it has.
Notice that we are talking about removing the children of a child node, and that those can in turn also have children.
This means that the removal must be done recursively.
`RemoveHelper` is a recursive method that you will use to recursively remove children during a delete.

### The FileSystem Class
![UML of FileSystem class](http://www.plantuml.com/plantuml/png/ZOuzJiOm343tdi9Zoyy5ol8XeOuidA2A3KJ4CNASLXM2izF0G8eoTBDVdfzoIJQhPGwT2tDACFb0JrioOlZeRa5534Pu5AIhktrtMPMYFNWbPw9R_NQFMER-1q2ajGp3RYpYiGYJZxz6CXp7PEhZ2yIPQVZBN5S_w8UoV_q7_8PUcusA5T4akzSpulkAVGE7rABAPvAy7And5Rw1cfWqhXmUhj1hC__PNIXYvl0D)

This class is responsible for storing the filesystem and carrying out the commands that manipulate it from the terminal.
The majority of the methods shown in this UML are described in the table above.
The string return values are what should be printed to the screen as a result of carrying out the operation.
For the two helper methods:

* `AddNode()`
  * Adds a new file or directory within the current directory (can be used by `mkdir` and `touch`).

* `FindNode()`
  * Looks for the file or directory within the current directory and returns it if it exists.

### The Terminal Class
![UML of Terminal class](http://www.plantuml.com/plantuml/png/SoWkIImgAStDuKhEIImkLWX9BShDp4lCKQZcqbL8ArQmKd3Bp4aDhYmkIStLikRIXYlGq0JnWahpD3I1YihoCrEikMgv75BpKe260G00)

The responsibility of this class is to interact with the user.
It takes in commands and user input and calls the corresponding methods on the **FileSystem** to get the results.


