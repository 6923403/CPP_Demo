
bool daemonize()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        return false;
    }
    else if(pid > 0)
    {
        exit(0);
    }

    umask(0);
    pid_t sid = setsid();
    if(sid < 0)
    {
        return false;
    }

    if((chdir("/")) < 0)
    {
        return false;
    }

    /*
     * 关闭标准输入、输出、错误输出设备
     */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /*
     * 关闭其他已经打开的文件描述符
     * 将标准输入、输出、错误输出定向到/dev/null
     */
    open("/dev/null", O_RDONLY);
    open("dev/null", O_RDWR);
    pen("/dev/null", O_RDWR);

    return true;
    return 0;
}
