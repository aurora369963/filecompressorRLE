#include "compress.h"

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#define BUF_SIZE 4096
#define MAX_RUN 255

int rle_compress(char *input_file,char* output_file)
{

	//open files
	int fd_in=open(input_file,O_RDONLY);
	
	if(fd_in<0)
	{
		printf("error opening input file");
		exit(1);

	}

	int fd_out=open(output_file,O_WRONLY | O_TRUNC | O_CREAT);
	
	if(fd_out<0)
	{
		printf("error opening or creating output file");
		exit(1);
	}

	ssize_t bytes;
	unsigned char buf[BUF_SIZE];
	unsigned char count=0;
	unsigned char prev;
	int  first=1;
	while((bytes=read(fd_in,buf,BUF_SIZE))>0)
	{
	   for (ssize_t i =0;i<bytes;i++)
	    {
	  	unsigned char curr=buf[i];
		//for first character
	
		if(first==1){
		prev=curr;
		count=1;
		first=0;
		continue;
		}

		//remaining characters
		if(curr==prev && count<MAX_RUN)
	 	{
			count++;
		
		}
		else{
			unsigned char out[2]={count,prev};

			if(write(fd_out,out,2)!=2)
			{
				printf("error while writing to output file");

			}
			prev=curr;
			count=1;
		}
	    }
	}  
	
	   //if bytes read less than zero
	   if(bytes<0)
	   {
	   perror("error while reading input file");

	   }
	//last character
	if(!first)
         
	{	
		unsigned char out[2]={count,prev};
		if(write(fd_out,out,2)!=2)
		{

			perror("error writing to output file");

			exit(1);
		}

	}

	close(fd_in);
	close(fd_out);

     
}
