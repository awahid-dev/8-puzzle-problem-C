#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define MAX 8
#define n 3
#define m 3

int tile[n][m];

//Initialsation of the tileay to keep track and all the values are assigned -1
//===========================================================================//

typedef struct{
	bool dir[4];//0->arr[0]->right
		    //1->arr[1]->left
		    //2->arr[2]->up
		    //3->arr[3]->down
}direc;

typedef struct{
	int x;
	int y;
}cord;

void init(){
	int x=rand()%n, y=rand()%m;
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

int max(int arr[]){
	int mx=0;
	for(int i=0; i<4; i++){
		if(arr[i]>arr[mx]&&(arr[i]!=-1)){
			mx=i;
		}
	}
	return mx;
}
//====================================================================//
//The real game logic bellow
//====================================================================//

int count(){
	int ct=0;
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

direc direction(cord c){
	direc d;
	d.dir[1]=true;
	d.dir[0]=true;
	d.dir[2]=true;
	d.dir[3]=true;

	if(c.x-1<0){
		d.dir[2]=false;
	}
	if(c.x+1>2){
		d.dir[3]=false;
	}
	if(c.y-1<0){
		d.dir[1]=false;
	}
	if(c.y+1>2){
		d.dir[0]=false;
	}
	return d;
}

//The test for finding the max point

int best_move(){
	int corr[4];
	cord c=search(0);
	direc d=direction(c);
	
	if(d.dir[0]==true){
		swap(&tile[c.x][c.y], &tile[c.x][c.y+1]);
		corr[0]=count();
		swap(&tile[c.x][c.y], &tile[c.x][c.y+1]);
	}
	else{
                corr[0]=-1;
        }
	if(d.dir[1]==true){
		swap(&tile[c.x][c.y], &tile[c.x][c.y-1]);
		corr[1]=count();
		swap(&tile[c.x][c.y], &tile[c.x][c.y-1]);
	}
	else{
                corr[1]=-1;
        }
	if(d.dir[2]==true){
		swap(&tile[c.x][c.y], &tile[c.x-1][c.y]);
		corr[2]=count();
		swap(&tile[c.x][c.y], &tile[c.x-1][c.y]);
	}
	else{
                corr[2]=-1;
        }
	if(d.dir[3]==true){
		swap(&tile[c.x][c.y], &tile[c.x+1][c.y]);
		corr[3]=count();
		swap(&tile[c.x][c.y], &tile[c.x+1][c.y]);
	}
	else{
		corr[3]=-1;
	}

	int mx=max(corr);

	if(mx==8){
		return 0;
	}

	if(mx==0&&corr[0]!=-1){
		swap(&tile[c.x][c.y], &tile[c.x][c.y+1]);
	}
	else if(mx==1&&corr[1]!=-1){
		swap(&tile[c.x][c.y], &tile[c.x][c.y-1]);
	}
	else if(mx==2&&corr[2]!=-1){
		swap(&tile[c.x][c.y], &tile[c.x-1][c.y]);
	}
	else if(mx==3&&corr[3]!=-1){
		swap(&tile[c.x][c.y], &tile[c.x+1][c.y]);
	}
	return 0;
}

//The solver//

void solver(){
	while(!is_solved()){
		display();
		printf("\n\n");
		sleep(1);
		best_move();
	}
}

//The main function//

int main(){
	srand(time(NULL));
	init();
	filler();
	solver();
	return 0;
}
