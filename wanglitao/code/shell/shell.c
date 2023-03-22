/************************************************
* Copyright(C) zhaixue.cc All rights reserved
*      Filename: shell.c
*        Author: litao.wang
*        E-mail: 3284757626@qq.com
*   Description: 
*        Create: 2019-08-20 14:03:55
* Last Modified: 2019-08-22 17:33:16
************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <pwd.h>

#include "syntax.h"
#include "builtin_cmd.h"
#include "env.h"

int read_cmdline  (char buffer[]);
int parse_cmdline (char buffer[], char *arglist[]);
int exec_cmdline  (char *arglist[], char buffer[]);
int free_cmdline  (char *arglist[], int args_num);
int exec_script   (char pathname[], char buffer[], char *arglist[]);
void print_cmd_prompt (void);

int background_exec = 0;
/*
    1: background exec mode
    0: normal exec mode
*/

int pipe_mode = 0;
/*
    1: pipe mode
    0: normal mode
*/


int main (int argc, char *argv[])
{
    char buffer[512] = {0};
    char *arglist[20] = {0};
    shell_env_setup ();
    if (argc == 1)
    {
        while (1)
        {
            print_cmd_prompt ();
            read_cmdline (buffer);
            exec_cmdline (arglist, buffer);
            memset (buffer, '\0', 512);
            memset (arglist, 0, 80);
        }
    }
    else
    {
        exec_script (argv[1], buffer, arglist);
        shell_env_cleanup ();
    }
    printf ("main shell exit\n");
    return 0;
}

void print_cmd_prompt (void)
{
    struct passwd *pwd;
    pwd = getpwuid (getuid());
    char path[256];
    getcwd (path, sizeof(path));
    printf ("\033[33;1m%s@wsh:\033[34;1m%s\033[0m >>>", pwd->pw_name, path);
}

int read_cmdline (char buffer[])
{
    char c;
    int pos = 0;
    while (1)
    {
        c = getchar ();
        if (c != '\n' && c != EOF)
            buffer[pos++] = c;
        else
        {
            buffer[pos++] = '\0';
            break;
        }
    }
    return pos;
}

int parse_cmdline (char buffer[], char *arglist[])
{
    int  args_num = 0;
    char *cp = buffer;
    int  len;
    char *start;
    char c;
    while (*cp != '\0' && *cp != '\n')
    {
        if (*cp == '&')
        {
            background_exec = 1;
            *cp = '\0';
            break;
        }
        cp++;
    }

    cp = buffer;
    while (*cp != '\0')
    {
        while (*cp == ' ' || *cp == '\t')
            cp++;
        if (*cp == 0)
            break;
        start = cp;
        len = 1;
        c = *++cp;
        while (c != '\0' && c != ' ' && c != '\t')
        {
            len++;
            c = *++cp;
        }
        arglist[args_num] = (char *) malloc (len + 1);
        strncpy (arglist[args_num], start, len);
        arglist[args_num][len] = '\0';
        args_num++;
    }
    return args_num;
}

int exec_cmd (char *arglist[], int fd_in, int fd_out)
{
    int ret_from_fork;
    int child_ret_status = 0;
    ret_from_fork = fork ();
    if (ret_from_fork == 0)
    {
        signal (SIGINT, SIG_DFL);
        signal (SIGQUIT, SIG_DFL);

        dup2 (fd_in, 0);
        dup2 (fd_out, 1);
        if (fd_in != 0)
            close (fd_in);
        if (fd_out != 1)
            close (fd_out);

        execvp (arglist[0], arglist);
        perror ("execvp");
        exit (EXIT_FAILURE);
    }
    else if (ret_from_fork > 0)
    {
        signal (SIGINT, SIG_IGN);
        signal (SIGQUIT, SIG_IGN);
        if (background_exec == 1)
        {
            background_exec = 0;
            signal (SIGCHLD, SIG_IGN);
        }
        else
        {
            signal (SIGCHLD, SIG_DFL);
            if(wait (&child_ret_status) == -1)
                perror ("wait");
        }

        if (fd_in != 0)
            close (fd_in);
        if (fd_out != 1)
            close (fd_out);
    }
    else
    {
        perror ("fork");
        exit (EXIT_FAILURE);
    }
    
    return child_ret_status;
}

int is_pipe_command (char buffer[])
{
    char *cp = buffer;
    while (*cp != '\n' && *cp != '\0')
    {
        if (strncmp (cp, "|", 1) == 0)
            return 1;
        cp++;
    }
    return 0;
}


int exec_cmdline (char *arglist[], char buffer[])
{
    char *temp = buffer;
    char *args;
    int  args_num = 0;
    int fd_tmp = 0;

    pipe_mode = is_pipe_command (buffer);

    while ((args = strtok(temp, "|")) != NULL)
    {
        temp = NULL;
        args_num = parse_cmdline (args, arglist);
        if (arglist[0] == 0)
            return 0;
        if (is_builtin_cmd(arglist))
        {
            exec_builtin_cmd (arglist);
            continue;
            // return 0;
        }
        if (is_env_command (arglist))
        {
            exec_env_cmdline (arglist);
            continue;
        }
        if (pipe_mode == 1)
        {
            int fd[2];
            if (pipe(fd) == -1)
            {
                perror ("pipe");
                exit (EXIT_FAILURE);
            }
            exec_cmd (arglist, fd_tmp, fd[1]);
            fd_tmp = fd[0];
            pipe_mode = 0;
        }
        else
        {
            exec_cmd (arglist, fd_tmp, 1);
        }
        free_cmdline (arglist, args_num);
        memset (arglist, 0, 80);
    }
    fd_tmp = 0;
    pipe_mode = 0;
    return 0;
}


int exec_script (char pathname[], char buffer[], char *arglist[])
{
    FILE *fp;
    fp = fopen (pathname, "r");
    if (fp == NULL)
    {
        perror ("fopen");
        exit (EXIT_FAILURE);
    }
    char c;
    int pos = 0;
    struct ctl_cmd_info cmd_info = {0,0,0};
    while (1)
    {
        c = getc (fp);
        if (c == '\n' || c == EOF)
        {
            buffer[pos++] = '\0';
            if (strlen (buffer) == 1 && c == '\n')
                continue;
            if (is_control_cmdline (buffer))
            {
                process_control_cmdline (buffer, &cmd_info);
                memset (buffer, '\0', 512);
                pos = 0;
                continue;
            }
            if (is_exec_cmdline (cmd_info))
                exec_cmdline (arglist, buffer);
            memset (buffer, '\0', 512);
            memset (arglist, 0, 80);
            pos = 0;
            if (c == EOF) //check end of file
                break;
        }
        else
            buffer[pos++] = c;
    }
    fclose (fp);
    return 0;
}

int free_cmdline (char *arglist[], int args_num)
{
    int i;
    for (i = 0; i < args_num; i++)
        free (arglist[i]);
    return 0;
}

