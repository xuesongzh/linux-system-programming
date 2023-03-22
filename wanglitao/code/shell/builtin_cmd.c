/************************************************
* Copyright(C) zhaixue.cc All rights reserved
*
*      Filename: builtin_cmd.c
*        Author: litao.wang
*        E-mail: 3284757626@qq.com
*   Description: 
*        Create: 2019-08-21 10:53:54
* Last Modified: 2019-08-22 17:26:18
************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>


static int builtin_cmd_exit (void)
{
    void shell_env_cleanup (void);
    shell_env_cleanup ();
    pid_t pid;
    pid = getpid ();
    kill (pid, SIGHUP);
    return 0;
}

static int builtin_cmd_cd (char path[])
{
    int ret;
    ret = chdir (path);
    if (ret == -1)
    {
        printf ("cd %s failed\n", path);
        return -1;
    }
    return 0;
}

int is_builtin_cmd (char *arglist[])
{
    if (strcmp (arglist[0], "cd") == 0)
        return 1;
    if (strcmp (arglist[0], "exit") == 0)
        return 1;
    return 0;
}

int exec_builtin_cmd (char *arglist[])
{
    if (strcmp (arglist[0], "cd") == 0)
    {
        if (arglist[1] == 0) 
            return 0;
        else
            builtin_cmd_cd (arglist[1]);
    }
    if (strcmp (arglist[0], "exit") == 0)
    {
        builtin_cmd_exit ();
    }
    return 0;
}
