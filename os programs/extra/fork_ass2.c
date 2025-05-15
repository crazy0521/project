// Program 2: Count Number of Vowels using vfork()

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char sentence[100];
    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    int vowels = 0;

    pid_t pid = vfork(); // Use vfork instead of fork

    if (pid < 0)
    {
        printf("vfork failed.\n");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process: Count vowels
        for (int i = 0; sentence[i] != '\0'; i++)
        {
            char c = tolower(sentence[i]);
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                vowels++;
        }
        printf("Child: Number of vowels = %d\n", vowels);
        _exit(0); // Use _exit() with vfork
    }
    else
    {
        // Parent process continues after child exits
        printf("Parent: Sentence entered: %s", sentence);
    }

    return 0;
}
