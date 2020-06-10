#include <stdio.h>
#include <string.h>
#include <unistd.h>
 
int main(int argc, char *args[])
{
	// 定义读取文件的缓冲区
	char buf_read[1024];
	// 定义写入文件的缓冲区
	char buf_write[1024];
	
	// 循环读取用户从键盘输入的信息
	while (1)
	{
		// 清空读取文件缓冲区中的内存
		memset(buf_read, 0, sizeof(buf_read));
		// 清空写入文件缓冲区中的内存
		memset(buf_write, 0, sizeof(buf_write));
		
		// 打印提示信息
		char input_message[100] = "input some words : ";
		write(STDOUT_FILENO, input_message, sizeof(input_message));
		// 读取用户的键盘输入信息
		read(STDIN_FILENO, buf_read, sizeof(buf_read));
		// 判断用户输入的内容是否为quit
		if (strncmp(buf_read, "quit", 4) == 0)
		{
			// 如果用户输入的是quit，程序退出循环
			break;
		}
		// 如果用户输入的不是quit
		// 把内容拷贝到写入文件缓冲区中
		strcpy(buf_write, buf_read);
		// 打印提示信息
		char output_message[100] = "output some words : ";
		write(STDOUT_FILENO, output_message, sizeof(output_message));
		// 将信息显示在屏幕上
		write(STDOUT_FILENO, buf_write, strlen(buf_write));
	}	
	
	return 0;
}
