#include "pgm.h"

int main(int argc, char *argv[]) {
//...Variable 
	FILE *fpi;
	int w=0, h=0, g=0, x, i, j, p;
//...Arguments
	if(argc < 2){
		perror("File not given\n");
		exit(1);
	}
	if((fpi = fopen(argv[1],"rb")) == NULL){
		perror("Input File opening Error!\n");
		exit(1);
	}
//...Read File
	img = fpi;
	pgm_to_mtx();


/* ..... DO WHATEVER YOU WANNA DO WITH THE MATRIX ..... */


//...Write File
	printf("Creating output file\n");
	FILE *fpo;
	if((fpo = fopen("./op.pgm","wb")) == NULL) {
		perror("Output File opening Error!\n");
		exit(1);
	}
	img = fpo;
	mtx_to_pgm();

	fclose(fpo);
lE:	fclose(fpi);

	return 0;
}
