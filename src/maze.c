#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX 100

int onesol(char **,int,int,int,int);

int main(int argc,char *argv[]){
	FILE *fp;
	int r,c,i,j,row=-1,col=-1;
	int sol;
	char line[MAX],**mazemat;



	if(argc != 2){
		printf("Error on command \n");
		return 1;
	}

	fp=fopen(argv[1],"r");
	if(fp==NULL){
		printf("error file opening ! \n");
		return 1;
	}
	fgets(line,MAX,fp);
	sscanf(line,"%d %d",&r,&c);
	mazemat=(char **)malloc(r*sizeof(char *));
	if(mazemat==NULL){
		printf("allocation ERROR !");
	}
	for(i=0;i<r;i++){
		fgets(line,MAX,fp);
		mazemat[i]=strdup(line);
		if(mazemat==NULL){
			printf("allocation ERROR !");
			return 1;
		}
		for(j=0;j<c;j++){
			if(mazemat[i][j]=='@'){
				row=i;
				col=j;
			}
		}
	}
	if(row<0 || col<0){
		printf("No start point!");
		return 1;
	}
	printf("one solution:\n");
	mazemat[row][col]=' ';
	sol=onesol(mazemat,r,c,row,col);
	if(sol==1){
		mazemat[row][col]='@';
		for(i=0;i<r;i++){
			printf("%s",mazemat[i]);
		}
	}else{
		printf("no solution found!\n");
	}
for(row=0;row<r;row++){
	free(mazemat[row]);
}
free(mazemat);
fclose(fp);
return 0;
}
int onesol(char **mazemat,int r,int c,int row,int col){

	int i,rpath,cpath;
	int xoff[4]={0,1,0,-1};
	int yoff[4]={-1,0,1,0};
	//termination
	if(mazemat[row][col]=='#'){
		return 1;
	}
	if(mazemat[row][col] != ' '){
		return 0;
	}
	mazemat[row][col]=-1;
	for(i=0;i<4;i++){
		rpath=row+xoff[i];
		cpath=col+yoff[i];
		if(rpath>=0 && rpath<r && cpath>=0 && cpath<c){
			if(onesol(mazemat,r,c,row,col)==1)
				return 1;
		}
	}
	mazemat[row][col]='.';
	return 0;


}


