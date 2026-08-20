#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    int file = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    write(file, "This is a test text", sizeof("This is a test text") - 1);
    close(file);

    int p_pid = fork();

    char c1,c2;
	
	 
	 
    if (p_pid > 0) {
	int file2 = open("test.txt", O_RDONLY);
       

        printf("Parent:\n");

        while (read(file2, &c1, 1) > 0) {
            printf("%c", c1);
        }

        printf("\n");
	
	 close(file2);
        
    }
    else {

       int file2 = open("test.txt", O_RDONLY);

        printf("Child:\n");

        while (read(file2, &c2, 1) > 0) {
            printf("%c", c2);
        }

        printf("\n");

         close(file2);
    }
    
   

    return 0;
}
