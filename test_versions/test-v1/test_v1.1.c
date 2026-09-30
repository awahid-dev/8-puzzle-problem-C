#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 8

void init();
void solver();


int arr[3][3];
int n=3, m=3;

//Initialsation of the array to keep track and all the values are assigned -1
//===========================================================================//

typedef struct{
	bool left;
	bool right;
	bool up;
	bool down;
}dir;

typedef struct{
	bool solved;
	int count;
}cntXsld;

typedef struct{
	int x;
	int y;
}cord;

void init(){
	int x=rand()%n, y=rand()%m;
	printf("%d, %d\n", x, y);
	arr[x][y]=0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(i==x&&j==y){
				continue;
			}
			else{
				arr[i][j]=-1;
			}
		}
	}
}

cord  search(int key){
	cord c;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(arr[i][j]==key){
				if(key!=0){
					c.x=-1;
					return c;
				}
				else{
					c.x=i;
					c.y=j;
					return c;
				}
			}
		}
	}
	c.x=-2;
	c.y=-2;
	return c;
}


void filler(){
	for(int i=0; i<n;i++){
		for(int j=0; j<m; j++){
			int temp=(rand()%MAX)+1;	
			if(arr[i][j]==0){
				continue;
			}
			cord c=search(temp);
			if(c.x==-1){
				j--;
			}
			else if(c.x==-2&&c.y==-2){
				arr[i][j]=temp;
			}
		}
	}
}

void display(){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			printf("%d", arr[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

void swap(int*a, int*b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

//====================================================================//
//The real game logic bellow
//====================================================================//

cntXsld is_solved(){
	cntXsld sc;
	int ct=0;

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(i==0){
				if(arr[i][j]==j+1){
					ct++;
				}
				else{
					sc.solved=false;
				}
			}
			else if(i==2){
				if(arr[i][j]==7-j){
					ct++;
				}
				else{
					sc.solved=false;
				}
			}
			else if(i==1){
				if((j==2&&arr[i][j]==4)||(j==0&&arr[i][j]==8)){
					ct++;
				}
				else{
					sc.solved=false;
				}
			}
		}
	}
	sc.count=ct;
	return sc;
}

//The direction determiner

dir direction(cord c){
	dir d;
	d.left=true;
	d.right=true;
	d.up=true;
	d.down=true;

	if(c.x-1<0){
		d.up=false;
	}
	if(c.x+1>2){
		d.down=false;
	}
	if(c.y-1<0){
		d.left=false;
	}
	if(c.y+1>2){
		d.right=false;
	}
	return d;
}

//The solver//

void solver(){
	int corr[4];
	while (!is_solved()){
		solver();
	}
}

//The main function//

int main(){
	srand(time(NULL));
	init();
	filler();
	cntXsld sc=is_solved();
	dir d=direction(search(0));
	printf("Left: %d\nRight: %d\nUp:%d\nDown: %d\n", d.left, d.right, d.up, d.down);
	display();
	return 0;
}
