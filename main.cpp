#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<iostream>
using namespace std;
const int height = 600;
const int width = 150;
int x=0;
int dirx=0;
int tcx,tcy; //random cubes position
const int maxCube = 3; // random cubes in the game
int score = 0;

//structure for random cubes position
struct randomCube{
	int tcx;
	int tcy;
};
struct randomCube arr[maxCube];

//set random cubes default position
void set(){
	for(int i=0;i<maxCube;i++){
		arr[i].tcx = (rand()*50)%150;
		arr[i].tcy = -((rand()*70)%490);
	}
}

//draw the board or outline border
void board(){
	setcolor(1);
	rectangle(0,0,width,height);
}


//draw the cube and random cubes
void drawCube(){
	board();
	//player cube
	setcolor(2);
	setfillstyle(SOLID_FILL,2);
	rectangle(x,height-70,x+50,height);
	floodfill(x+1,height-69,2);
	
	//draw top random cubes and move down side
	for(int i=0;i<maxCube;i++)
	if(arr[i].tcy>height){
		score+=5;
		cout<<"\nScore : "<<score;
		arr[i].tcx = (rand()*50)%150;
		arr[i].tcy = -((rand()*70)%350);
	}
	else{
		setcolor(3);
		setfillstyle(SOLID_FILL,3);
		rectangle(arr[i].tcx,arr[i].tcy,arr[i].tcx+50,arr[i].tcy+70);
		floodfill(arr[i].tcx+49,arr[i].tcy+69,3);
	}
}

//update function- to update the cube in x-axis
// and update the random cubes y-axis
void update(){
	if(kbhit())
	switch(getch()){
		//75-left key pressed
		case 75: dirx = -1; break;
		//77-right key pressed
		case 77: dirx = 1; break;
			
	}
	if(dirx==1){
		x += 50;
		dirx=0; 
	}
	else if(dirx==-1){
		x -= 50;
		dirx = 0;
	}
	
	for(int i=0;i<maxCube;i++)
	arr[i].tcy += 10; 
}

//gameOver function
bool gameOver(){
	//check if player cube colide to random cubes or not and check if player cube is outside the outline or not
	for(int i=0;i<maxCube;i++)
	if(x+50>width || x<0 || x==arr[i].tcx && height-70==arr[i].tcy+70 || x==arr[i].tcx && arr[i].tcy+70>=height){
		setcolor(RED);
		settextstyle(1,0,2);
		outtextxy(200,100,"GAME OVER...");
		Beep(500,500);
		cout<<"\nGame over....";
		getch();
		return true; 
	}
}

//driver code
int main(){
	initwindow(500,800,"Cube Runner",500);
	//set the random cubes position
	set();
	
	while(!gameOver()){
		cleardevice();
		update();
		drawCube();
		Sleep(20);
	}
	return 0;
}
