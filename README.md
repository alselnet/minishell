# TEST BUILT-IN COMMANDS

cd srcs/built_in_commands  
gcc -Wall -Werror -Wextra main.c -I../../include/  

## To test the built-in commands, do this:

**FOR CD**  
./a.out "cd"  
./a.out "cd" "<path>"  
./a.out "cd" "-/" _(will try to move to a folder that does not exist)_  

**FOR PWD**  
./a.out pwd  

**FOR UNSET**  
To test "unset", export a variable first in your environment:  
export TEST=océ  
Check that it has been added in your terminal: env | grep TEST  
rerun gcc -Wall -Werror -Wextra main.c -I../../include/  
./a.out unset TEST _(will remove TEST inside envp)_  
./a.out unset océ _(will try remove a variable that does not exist)_  
./a.out unset _(will remove all variables inside envp)_  

**FOR ENV**  
./a.out env  
