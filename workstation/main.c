#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<math.h>

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
}direc_t;

typedef struct{
	int x;
	int y;
}cord_t;

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

cord_t search(int key){
	cord_t c;
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
			cord_t c=search(temp);
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

int min(int arr[]){
	int mn=0;
	for(int i=0; i<4; i++){
		if(arr[i]<arr[mn]&&(arr[i]!=-1)){
			mn=i;
		}
	}
	return mn;
}
//====================================================================//
//The real game logic bellow
//====================================================================//

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

//The direc_ttion determiner

direc_t direction(cord_t c){
	direc_t d;
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

//correct coordination

cord_t correct_position(int key){
	cord_t correct_cord;
	if(key<=3&&key>=1){
		correct_cord.y=key-1;
		correct_cord.x=0;
		return correct_cord;
	}
	if(key<=7&&key>=5){
		correct_cord.y=7-key;
		correct_cord.x=2;
		return correct_cord;
	}
	if(key==4){
		correct_cord.y=2;
		correct_cord.x=1;
		return correct_cord;
	}
	if(key==8){
		correct_cord.y=0;
		correct_cord.x=1;
		return correct_cord;
	}
}

//The distance finds the distance from the correct possition

int distance(){
	int dist=0;
	cord_t correct_cord, current_cord;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(tile[i][j]==0)break;
			current_cord.x=i;
			current_cord.y=j;
			correct_cord=correct_position(tile[i][j]);
	
			dist+=abs(current_cord.x-correct_cord.x)
			     +abs(current_cord.y-correct_cord.y);
		}
	}
	return dist;
}

void best_move(){
	int dist[4];
	cord_t c=search(0);
	direc_t d=direction(c);
	int prev_dist=distance();
	if(d.dir[0]==true){
                swap(&tile[c.x][c.y], &tile[c.x][c.y+1]);
                dist[0]=distance();
                swap(&tile[c.x][c.y], &tile[c.x][c.y+1]);
        }
        else{
               dist[0]=-1;
        }
        if(d.dir[1]==true){
                swap(&tile[c.x][c.y], &tile[c.x][c.y-1]);
                dist[1]=distance();
                swap(&tile[c.x][c.y], &tile[c.x][c.y-1]);
        }
        else{
                dist[1]=-1;
        }
        if(d.dir[2]==true){
                swap(&tile[c.x][c.y], &tile[c.x-1][c.y]);
                dist[2]=distance();
                swap(&tile[c.x][c.y], &tile[c.x-1][c.y]);
        }
        else{
                dist[2]=-1;
        }
        if(d.dir[3]==true){
                swap(&tile[c.x][c.y], &tile[c.x+1][c.y]);
                dist[3]=distance();
                swap(&tile[c.x][c.y], &tile[c.x+1][c.y]);
        }
        else{
                dist[3]=-1;
        }
	int mn=min(dist);
	if(mn==0&&dist[0]!=-1&&prev_dist>dist[0]){
		swap(&tile[c.x][c.y], &tile[c.x][c.y+1]);
	}
	else if(mn==1&&dist[1]!=-1&&prev_dist>dist[1]){
              	swap(&tile[c.x][c.y], &tile[c.x][c.y-1]);
       	}
       	else if(mn==2&&dist[2]!=-1&&prev_dist>dist[2]){
              	swap(&tile[c.x][c.y], &tile[c.x-1][c.y]);
       	}
       	else if(mn==3&&dist[3]!=-1&&prev_dist>dist[3]){
            	swap(&tile[c.x][c.y], &tile[c.x+1][c.y]);
        }
}

       //The solver//

void solver(){
	while(!is_solved()){
		best_move();
		display();
		printf("\n\n");
		sleep(1);
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
