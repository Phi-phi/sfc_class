#include <io.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	char buf[1024];
	int fd;
	int rc;
	int kc;
	char keydata[1];
	char dispdata[1024];
	char* disp;
	int count=0;

	if(argc==1)
	{
		while(1){
			if((kc = read(0,keydata,1)) != -1){
				dispdata[count] = keydata[0];
				count++;
				if(keydata[0] == '\n'){
					disp = dispdata;
					write(1,disp,count);
					count=0;
				}
			}
			
		}
	}//*/
		int i;
		for(i=1;i<argc;i++)
		{
			if ((fd = open(argv[i],O_RDONLY)) == -1)
			{
				write(1,"Error. No such File or directory.\n",32);
				exit(1);
			}
			else
			{
				if((rc = read(fd,buf,1024)) != -1)
				{
				write(1,buf,rc);
				}else
				{
					write(1,"Error. File can not be read.\n",32);
					exit(1);
				}
			}
			close(fd);
		}
}
