#include <iostream>
#include <string>
#include <random>
#include <conio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "texturemanager.cpp"
using namespace std;

//Global Variables
//Font
TTF_Font *font;
SDL_Color colorw = {255, 255, 255};

//Background Image and Rectangle
SDL_Texture* backgroundTxt;
SDL_Rect backgroundrect;
SDL_Rect backgroundrect2;

//Bird Image and Rectangle
SDL_Texture* birdTxt;
SDL_Rect birdrect;
float birdVY=1;

//Pipe Image and Rectangle
SDL_Texture* pipeTxt;
SDL_Rect piperect;
SDL_Rect piperect2;
SDL_Rect piperect3;
SDL_Rect piperect4;
int random1;
int random2;

//Event and bools
SDL_Event event;
bool isTouching=false;
bool isTouchingflag=false;
bool collision;
bool isRunning=true;
bool startGame=false;

//Score
int gameScore = 0;
SDL_Surface* gameScoreSur;
SDL_Texture* gameScoreTxt;
SDL_Rect gameScorerect;
string gameScoreS;


void init(SDL_Renderer* renderer){
//Initialize background 
backgroundTxt = loadImage(renderer,"background.png");
backgroundrect = {0,0,720,1544};
backgroundrect2 = {720,0,720,1544};
//Initialize bird
birdTxt = loadImage(renderer,"bird.png");
birdrect = {0,200,150,107};

//Initialize pipe
pipeTxt = loadImage(renderer,"pipe.png");
int pH=500;
int pW=200;
//top
piperect = {720-pW,0,pW,pH};
//bottom 
piperect2 = {720-pW,360+(1544-pH*2),pW,pH};
}


void writeText(SDL_Renderer *renderer, std::string message, int x, int y,int scale=1) {
    // Initialize font
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("/system/fonts/Roboto-Regular.ttf", 256);

    // Create a SDL_Surface to hold the text
    SDL_Color color = {255, 0, 0};
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, message.c_str(), color);

    // Create a SDL_Texture from the surface
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Get the width and height of the texscale
    float precScale = scale*0.1;
    int text_width = (textSurface->w)*precScale;
    int text_height = (textSurface->h)*precScale;
    

    // Create a SDL_Rect for the text's position
    SDL_Rect textRect = { x, y, text_width, text_height };

    // Render the text
    SDL_RenderCopy(renderer, text, NULL, &textRect);

    // Clean up
    TTF_CloseFont(font);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(text);
}


void eventHandler(){
	isTouching=false;
	while(SDL_PollEvent(&event)){
		if (event.type == SDL_FINGERDOWN) {
	    			isTouching=true;
	    			startGame=true;
	    	}
		if (event.type == SDL_FINGERUP) {
			isTouching=false;
			}
		}
	
}


void update(SDL_Renderer* renderer){
	
	
	
	backgroundrect.x-=2;
	backgroundrect2.x-=2;
	piperect.x-=1;
	piperect2.x-=1;
	
	if(backgroundrect.x+backgroundrect.w<0){
		backgroundrect.x=715;
		}
	if(backgroundrect2.x+backgroundrect2.w<0){
		backgroundrect2.x=715;
		}
	if(isTouching){
		birdrect.y-=birdVY;
	birdVY=-5;
		}else{birdVY+=0.1;}
	if(piperect.x==0-200){piperect.x=720;}
	if(piperect2.x==0-200){piperect2.x=720;}
	if(piperect.x==50){gameScore++;
	gameScoreS = to_string(gameScore);
    gameScoreSur= TTF_RenderText_Solid(font, gameScoreS.c_str(), colorw);
    gameScoreTxt = SDL_CreateTextureFromSurface(renderer,gameScoreSur);
    
    }
    
    //if the pipe is in the very back...
    if(piperect.x==720){
    	//random pipe sequence
    {random1=rand()%300+250;
    random2=rand()%300+250;
    
    piperect.y=random1/30-20;
    piperect2.y=(random2/1.4)+(1544-random2*2);
 
    piperect.h=random1;
    piperect2.h=random2;
    cout<<rand()%500+300<<"hi";}
    //end random pipe sequence
    	}
	birdrect.y+=birdVY;
	}

void render(SDL_Renderer* renderer){
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,backgroundTxt,NULL,&backgroundrect);
	SDL_RenderCopy(renderer,backgroundTxt,NULL,&backgroundrect2);
	SDL_RenderCopy(renderer,pipeTxt,NULL,&piperect);
	SDL_RenderCopy(renderer,pipeTxt,NULL,&piperect2);
	SDL_RenderCopy(renderer,birdTxt,NULL,&birdrect);
	SDL_RenderCopy(renderer,gameScoreTxt,NULL,&gameScorerect);
	if(!isRunning){
		writeText(renderer,"Game Over",100,600,4);
		}
	SDL_RenderPresent(renderer);
	}


int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("FlaPUP",0,0,720,1544,0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,0,0);
	TTF_Init();
    font = TTF_OpenFont("/system/fonts/Roboto-Regular.ttf", 256);
   gameScorerect = {720/2-75/2,10,75,150};

    
    
    
//Initialize Variables
init(renderer);
//Game Loop
while(1){
	eventHandler();
	if(startGame){
	
	update(renderer);
	render(renderer);
//	SDL_Delay(10);

if(SDL_HasIntersection(&birdrect, &piperect)||SDL_HasIntersection(&birdrect, &piperect2)||birdrect.y<0||birdrect.y>1544){
	isRunning=false;
	  render(renderer);
	SDL_Delay(1000);
SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
   SDL_Quit();
   return 0;
}
}
else{
	SDL_RenderClear(renderer);
	writeText(renderer,"Press to Start",120,600,3);
	SDL_RenderPresent(renderer);
	}
}
	}

void func(){}
void print1_10(){}
void factorial(){}
void printeven(){}

int maín()
{
	
	int choice=0;
	
	while(choice<=4){
	
	clrscr();
	func();
	
	cout<<"Main Menu\n"
				"1 - For Loop (Print 1 to 10)\n"
				"2 - While Loop (Print Even from 1 to 10)\n"
				"3 - Do While (Print Factorial)\n"
				"4 - Exit\n\n"
				"Input your choice: ";
	cin>>choice;
	
	clrscr();
	
	switch(choice){
		
		case 1:
		print1_10();
		break;
		
		case 2:
		printeven();
		break;
		
		case 3:
		factorial();
		break;
		
		case 4:
		exit(0);
		break;
		
		default: exit(0);
		}
	getch();
	getch();
	}
}