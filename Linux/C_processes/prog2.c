#include <stdio.h>
#include <stdlib.h> // atoi(); atof();
#include <unistd.h>

int main(int argc, char *argv[], int x)  //(number of arguments, array of strings)
{
    printf("Inside prog2.c program PID = %d Child of %d\n", getpid(), getppid());
    printf("Arguments received:\n");

    int i;
    for(i = 0; i < (argc-2); i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    printf("int  : %d\n", atoi(argv[i++]));     // strtoi(argv[i++])
    printf("float: %.3f\n", atof(argv[i]));   // strtoi(argv[i++])

    return 0;
}

/* Timeline:

Shell (PID 001)
       |
       |
    prog1 (002)
       |
       +------ Child (003)

After fork():
Shell (001)
       |
    prog1 (002)
       |
       +------ Child (003)

Then the child executes:
execvp("./prog2", args);
exec() does not create a new process. It only replaces the current program.

So now:
Shell (001)
       |
    prog1 (002)
       |
       +------ prog2 (003)

Notice the PID is still 003. 
Why did the parent become 001?
Because prog1 exited before prog2 printed its parent PID.
When process 002 dies, process 003 becomes an orphan.

Orphan processes are automatically adopted by the special system process—traditionally PID 1 (init/systemd), 
the first user-space process started when Linux boots, or by an init/subreaper process (such as in WSL).
      |
      +---- Shell (001)
              |
              +---- prog1 (002)
                      |
                      +---- prog2 (003)

In your environment, that parent has PID 001.
So the process tree becomes:
001
 |
 +---- prog2 (003)

Therefore:
getppid() returns 001 instead of 002.

*/