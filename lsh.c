#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define LSH_RL_BUFSIZE 1024

char* lsh_read_line()
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char* buffer = malloc(sizeof(char) * bufsize);
    int c;

    if(!buffer)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        // read a characted
        c = getchar();

        // EOF case : replace it with a null character then return
        if(c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position ++;

        // Reallocate memory case : the buffer mem is exceded
        if(position >= bufsize)
        {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if(!buffer)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);     
            }
        }
    }
}

// This function take a string and convert it to many tokens (tokenisation process) by delimiting the original
// string with whitespaces

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char** lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if(!tokens)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while(token != NULL)
    {
        // Assign token into tokenS array
        tokens[position] = token;
        position++;
        
        // Reallocate memory case...
        if(position >= bufsize)
        {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if(!tokens)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}


// This Function start shell process

int lsh_launch(char** args)
{
    pid_t pid, wpid;
    
}

void lsh_loop()
{
    char* line;
    char** args;
    int status;
    
    do
    {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);

        for(int i = 0; args[i] != NULL; i++)
        {
            printf("%s ", args[i]);
        }

        //status = lsh_execute(args);

        free(line);
        free(args);
    }while(status);
    
}


int main(int argc, char** argv)
{
    // Load Config files

    // Run Commands Loop
    lsh_loop();
    // Perform shutdown/cleanup


    return EXIT_SUCCESS;
}
