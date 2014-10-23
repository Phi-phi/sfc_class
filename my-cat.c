#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	char buf[1024];
	int fd;
	int rc;

	if(argc==1)
	{
		perror("ファイル名を一つ以上入力してください\n");
		exit(1);
	}//*/
		int i;
		for(i=1;i<argc;i++)
		{
			if ((fd = open(argv[i],O_RDONLY)) == -1)
			{
				perror("ファイルが開けませんでした。\n");
				exit(1);
			}
			else
			{
				if((rc = read(fd,buf,1024)) != -1)
				{
				write(1,buf,rc);
				}else
				{
					perror("ファイルが読み込めませんでした。\n");
				}
			}
			close(fd);
		}
}
