#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 8
#define n 3
#define m 3

void init();
void solver();

int tile[n][m];

//Initialsation of the tileay to keep track and all the values are assigned -1
//===========================================================================//

typedef struct{
	bool arr[4];//0->arr[0]
		    //1->arr[1]
		    //2->arr[2]
		    //3->arr[3]
}dir;

typedef struct{
	bool solved;
	int count;
}solve;

typedef struct{
	int x;
	int y;
}cord;

void init(){
	int x=rand()%n, y=rand()%m;
	printf("%d, %d\n", x, y);
	tile[x][y]=0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(i==x&&j==y){
				continue;
			}
			else{
				tile[i][j]=-1;
			}
		}
	}
}

cord  search(int key){
	cord c;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(tile[i][j]==key){
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
			if(tile[i][j]==0){
				continue;
			}
			cord c=search(temp);
			if(c.x==-1){
				j--;
			}
			else if(c.x==-2&&c.y==-2){
				tile[i][j]=temp;
			}
		}
	}
}

void display(){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			printf("%d", tile[i][j]);
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

int max_point(int arr[]){
	int max=0;
	int n=sizeof(arr)/4;
	for(int i=0; i<n; i++){
		if(arr[i]>arr[max]){
			max=arr[i];
		}
	}
	return max;
}
//====================================================================//
//The real game logic bellow
//====================================================================//

int count(){
	int ct;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(i==0&&(tile[i][j]==j+1)){
				ct++;
			}
			else if(i==2&&(tile[i][j]==7-j)){
				ct++;	
			}
			else if(i==1){
				if((j==2&&tile[i][j]==4)||(j==0&&tile[i][j]==8)){
					ct++;
				}
			}
		}
	}
	return ct;
}

bool is_solved(){
	int ct=0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(i==0){
				if(tile[i][j]!=j+1){
					return false;
				}
			}
			else if(i==2){
				if(tile[i][j]!=7-j){
					return false;
				}
			}
			else if(i==1){
				if((j==2&&tile[i][j]!=4)||(j==0&&tile[i][j]!=8)){
					return false;
				}	
			}
		}
	}
	return true;
}

//The direction determiner

dir direction(cord c){
	dir d;
	d.arr[1]=true;
	d.arr[0]=true;
	d.arr[2]=true;
	d.arr[3]=true;

	if(c.x-1<0){
		d.arr[2]=false;
	}
	if(c.x+1>2){
		d.arr[3]=false;
	}
	if(c.y-1<0){
		d.arr[1]=false;
	}
	if(c.y+1>2){
		d.arr[0]=false;
	}
	return d;
}

//The test for finding the max point

int point(int cor[]){
	int arr[n][m];

	cord c=search(0);
	dir d=direction(c);
	//Copy the arry for experiment
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			arr[i][j]=tile[i][j];
		}
	}

	for(int i=0; i<4; i++){
		if(d.arr[0]!=false){
			swap(arr[c.y], arr[c.y+1]);
			cor[i]=count();
		}
		else{
			cor[i]=-1;
		}
	}

}

//The solver//

void solver(){
	int corr[4], arr[n][m];
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			arr[i][j]=tile[i][j];
		}
	}
	point(corr);
}

//The main function//

int main(){
	srand(time(NULL));
	init();
	filler();
	display();
	return 0;
}
