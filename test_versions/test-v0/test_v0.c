#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 8
void dash(int n){
	for(int i=0; i<n; i++){
		printf("-");
	}
}

void undscr(int n){
	for(int i=0; i<n; i++){
		printf("_");
	}
}
void pipe(int n){
	for(int i=0; i<n; i++){
		if(i%2==0){
			printf("|");
		}
		else{
			printf("%d", rand()%MAX);
		}
	}
}

int main(){
	undscr(7);
	printf("\n");
	pipe(7);
	printf("\n");
	dash(7);
	printf("\n");

	pipe(7);
	printf("\n");
	dash(7);
	printf("\n");

	pipe(7);
	printf("\n");
	dash(7);
	printf("\n");
}
