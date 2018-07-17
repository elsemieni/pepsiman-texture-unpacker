#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {
	
	FILE *source, *dest, *fileTable, *timFile;
	char filenameBuffer[256], *fileBuffer, buffer;
	uint32_t address, currPos, totalSize, timSize; 
	
	int bytes, i;
	
	if (argc != 2) {
		printf("Usage: packer.exe filename\nExample: packer.exe 0001");
		return -1;
	}
	
	source = fopen(argv[1], "rb");
	if (!source) {
		printf("Error opening file %s", argv[1]);
		return -1;
	}
	
	//get file total size
	fseek(source, 0L, SEEK_END);
	totalSize = ftell(source);
	fileBuffer = (char*) malloc(sizeof(char)* totalSize);
	fseek(source, 0, SEEK_SET);
	
	sprintf(filenameBuffer, "%s_filetable.txt", argv[1]);
	fileTable = fopen(filenameBuffer, "r");
	if (!fileTable) {
		printf("Error opening file %s. There's a file table created with the extractor?\n", filenameBuffer);
		return -1;
	}
	
	//making backup file
	sprintf(filenameBuffer, "%s.bak", argv[1]);
	dest = fopen(filenameBuffer, "wb");
	if (!dest) {
		printf("Error writing file %s. Did you have write permission here?\n", filenameBuffer);
		fclose(source);
		return -1;
	}
	while (0 < (bytes = fread(&buffer, 1, sizeof(buffer), source))) fwrite(&buffer, 1, bytes, dest);
    fclose(dest);
	fclose(source);
	
	//write at original file as output, using backup as original file
	source = fopen(filenameBuffer, "rb");
	dest = fopen(argv[1], "wb");
	
	currPos = 0;
	i = 0;
	while (fscanf(fileTable, "%d\n", &address)!= EOF) {
		
		//write from currPos until address from original file
		fseek(source, currPos, SEEK_SET);
		fread(fileBuffer, address - currPos, 1, source);
		fwrite(fileBuffer, address - currPos, 1, dest);
		currPos += address - currPos;
		
		sprintf(filenameBuffer, "%s_extract_%d.tim", argv[1], i);
		i++;
		printf("Patching %s into 0x%.4x ... \n", filenameBuffer, address);
		
		timFile = fopen(filenameBuffer, "rb");
		if (!source) {
			printf("Error opening file %s", filenameBuffer);
			fclose(source);
			fclose(dest);
			return -1;
		}
		
		//write file content into the packed file
		fseek(timFile, 0L, SEEK_END);
		timSize = ftell(timFile);
		fseek(timFile, 0, SEEK_SET);
		
		fread(fileBuffer, timSize, 1, timFile);
		fwrite(fileBuffer, timSize, 1, dest);
		currPos += timSize;
		
		fclose(timFile);
		
	}
	
	//remains? write here!
	fseek(source, currPos, SEEK_SET);
	fread(fileBuffer, totalSize - currPos, 1, source);
	fwrite(fileBuffer, totalSize - currPos, 1, dest);
	
	fclose(source);
	fclose(dest);
	
	return 0;
	
}