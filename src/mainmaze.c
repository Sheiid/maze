#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<limits.h> MAX_INT worst case for finding min

#define MAX 50

#define START '@'

char **malloc2d(int, int, FILE *);
char **free2d(char **, int);
int find_path(char **, int, int, int, int);
int find_all(char **, int, int, int, int);
int find_best(char **, char **, int, int, int, int, int);
void display(char **, int);

const int xoff[4] = { 1, 0, -1, 0 };
const int yoff[4] = { 0, 1, 0, -1 };

int main(int argc, char *argv[]) {
	FILE *fp;
	int i, j;
	int numrow, numcol;
	int command, rstart = 0, cstart = 0;
	char **mazemat, **mazeBest;
	int res;

	if (argc != 2) {
		printf("Error number of parameters.\n");
		return 1;
	}
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("File can not open !\n");
		return 1;
	}
	if (fscanf(fp, "%d %d ", &numrow, &numcol) == EOF) {
		printf("Read File Error.!\n");
		return 1;
	}

	mazemat = malloc2d(numrow, numcol, fp);
	mazeBest = malloc2d(numrow, numcol, fp);
	//reading the file in to our allocated matrix

	for (i = 0; i < numrow; i++) {
		for (j = 0; j < numcol; j++) {

			if (mazemat[i][j] == START) {
				rstart = i;
				cstart = j;
			}
		}
	}
	printf("start point is : ");
	printf("%d %d", rstart, cstart);
	printf("\n");
	setbuf(stdout, NULL);
	do {
		printf(
				"find path :one solution(1), all solution(2), best solution(3):\n");
		scanf("%d", &command);
		switch (command) {
		case 1:

			mazemat[rstart][cstart] = ' ';
			//display(mazemat,numrow);
			res = find_path(mazemat, numrow, numcol, rstart, cstart);
			if (res) {

				mazemat[rstart][cstart] = START;
				display(mazemat, numrow);
			} else
				printf("No solution\n");
			break;

		case 2:
			//find_all();
			mazemat[rstart][cstart] = ' ';
			res = find_all(mazemat, numrow, numcol, rstart, cstart);
			if (res) {
				mazemat[rstart][cstart] = START;
				printf("number of solutions : %d", res);
			} else
				printf("No solution!");
			break;

		case 3:
			mazemat[rstart][cstart] = ' ';
			res = find_best(mazemat, mazeBest, numrow, numcol, rstart, cstart,
					0);
			if (res) {
				printf("Best solution:\n");
				mazeBest[rstart][cstart] = START;
				display(mazeBest, numrow);

			} else
				printf("No solution!");
			break;

		}
	} while (command < 1 || command > 3);

	fclose(fp);

	mazemat = free2d(mazemat, numrow);
	return 0;
}

char **malloc2d(int R, int C, FILE *fin) {

	int i;
	char line[MAX];
	char **mat;
	mat = (char **) malloc(R * sizeof(char *));
	if (mat == NULL) {
		printf("Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < R; i++) {
		fgets(line, MAX, fin);

		mat[i] = strdup(line);

//		mat[i]=(char *)malloc(C *sizeof(char));
//		if(mat[i]==NULL){
//			printf("ERROR\n");
//			exit (EXIT_FAILURE);
//
//		}

	}
// test input file 	display(mat,R);

	return mat;
}

int find_path(char **mazemat, int nr, int nc, int new_r, int new_c) {

	int i, r, c;

	//termination
	if (mazemat[new_r][new_c] == '#') {
		return 1;
	}
	//moving in to our matrix through the condition checking and space
	for (i = 0; i < 4; i++) {
		r = new_r + xoff[i];
		c = new_c + yoff[i];
		//check it is inside the Matrix and it is space
		if (r >= 0 && c >= 0 && r < nr && c < nc
				&& mazemat[new_r][new_c] == ' ') {
			mazemat[new_r][new_c] = '$';
			//call the function again till termination
			if (find_path(mazemat, nr, nc, r, c))
				return 1;
			//chon @ hichvaght too loope bala nemire un bala aval mosavi space mizaramesh !
			mazemat[new_r][new_c] = ' ';
		}

	}

	return 0;
}

int find_all(char **mazemat, int nr, int nc, int new_r, int new_c) {

	int i, r, c, sol = 0;

	//termination
	if (mazemat[new_r][new_c] == '#') {

		display(mazemat, nr);
		return 1;
	}
	//moving in to our matrix through the condition checking and space
	for (i = 0; i < 4; i++) {
		r = new_r + xoff[i];
		c = new_c + yoff[i];
		//check it is inside the Matrix and it is space
		if (r >= 0 && c >= 0 && r < nr && c < nc
				&& mazemat[new_r][new_c] == ' ') {
			mazemat[new_r][new_c] = '$';
			//call the function again till termination
			sol += find_all(mazemat, nr, nc, r, c);

			//chon @ hichvaght too loope bala nemire un bala aval mosavi space mizaramesh !
			mazemat[new_r][new_c] = ' ';
		}

	}
	//printf("test");
	return sol;

}
int find_best(char **mazemat, char **tmp, int nr, int nc, int new_r, int new_c, int level) {

	int i, r, sol = 0, c, best = nr * nc;

	//termination
	if (mazemat[new_r][new_c] == '#') {

		if (level < best) {
			for (i = 0; i < nr; i++) {
				strcpy(tmp[i], mazemat[i]);
			}
		}
		best = level;

		return 1;
	}
//moving in to our matrix through the condition checking and space
	for (i = 0; i < 4; i++) {
		r = new_r + xoff[i];
		c = new_c + yoff[i];
		//check it is inside the Matrix and it is space
		if (r >= 0 && c >= 0 && r < nr && c < nc
				&& mazemat[new_r][new_c] == ' ') {
			mazemat[new_r][new_c] = '$';

			//call the function again till termination
			sol += find_best(mazemat, tmp, nr, nc, r, c, level + 1);

			//chon @ hichvaght too loope bala nemire un bala aval mosavi space mizaramesh !
			mazemat[new_r][new_c] = ' ';


		}
	}
	return sol;

}

void display(char **mazemat, int nr) {
	int i;
	for (i = 0; i < nr; i++) {
		printf("%s", mazemat[i]);
	}
}

char **free2d(char **mat, int R) {
	int i;
	for (i = 0; i < R; i++) {
		free(mat[i]);
	}
	free(mat);
	return mat;
}

