void handle_redirections(t_redir *redir_list)
{
    t_redir *curr = redir_list;

    while (curr)
    {
        if (curr->type == TOKEN_OUTPUT)
        {
            int fd = open(curr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                perror("Error opening file");
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (curr->type == TOKEN_APPEND)
        {
            int fd = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                perror("Error opening file");
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (curr->type == TOKEN_INPUT)
        {
            int fd = open(curr->file, O_RDONLY);
            if (fd == -1)
                perror("Error opening file");
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        curr = curr->next;
    }
}


void handle_heredoc(char *delimiter)
{
    char *line;
    int pipe_fd[2];

    pipe(pipe_fd);
    while (1)
    {
        line = readline("> ");
        if (!line || strcmp(line, delimiter) == 0)
            break;
        write(pipe_fd[1], line, strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
}


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;

    // Open the file "output.txt" for writing (create if not exist, truncate if exist)
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    // Redirect stdout (file descriptor 1) to the file descriptor fd
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("Error with dup2");
        close(fd);
        return (1);
    }

    // Close the file descriptor as it's no longer needed
    close(fd);

    // Now, all printf statements will go to "output.txt" instead of the terminal
    printf("Hello, this is written to output.txt\n");
    printf("Another line redirected to the file\n");

    return 0;
}

