#include<stdio.h>
#include "compress.h"
#include "decompress.h"

int main(int argc,char* argv[]){

//usage error	
if(argc !=4)
{
	printf("Incorrect Usage: \n");
	printf("For Compression: %s c inputFile outputFile",argv[0]);
	printf("For Decompression: %s d inputFile outputFile",argv[0]);
	return 1;
}

int result=0;
if(argv[1][0]== 'c')
result=rle_compress(argv[2],argv[3]);
else if(argv[1][0]=='d')
result=rle_decompress(argv[2],argv[3]);
else
{
	printf("::::usage error::::");
	return 1;
}
printf("program exited");
return result;
}
