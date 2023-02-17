#define NUM_PIPES 5
#define PIPE_WIDTH 200
#define PIPE_HEIGHT 626
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 1544
#define PIPE_SPEED 2

SDL_Texture* pipeTxt;
SDL_Rect piperects[NUM_PIPES];

void init(SDL_Renderer* renderer){
    backgroundTxt = loadImage(renderer,"background.png");
    backgroundrect = {0,0,720,1544};
    backgroundrect2 = {720,0,720,1544};
    birdTxt = loadImage(renderer,"bird.png");
    birdrect = {0,0,150,107};
    createPipes(renderer);
}

void createPipes(SDL_Renderer* renderer) {
    pipeTxt = loadImage(renderer, "pipe.png");
    for(int i = 0; i < NUM_PIPES; i++) {
        int randomHeight = rand() % (SCREEN_HEIGHT - PIPE_HEIGHT * 2) + PIPE_HEIGHT;
        int randomYPos = rand() % 2 == 0 ? 0 : SCREEN_HEIGHT - randomHeight;
        piperects[i] = { SCREEN_WIDTH + i * PIPE_WIDTH, randomYPos, PIPE_WIDTH, randomHeight };
    }
}

void updatePipes() {
    for(int i = 0; i < NUM_PIPES; i++) {
        piperects[i].x -= PIPE_SPEED;
        if(piperects[i].x + PIPE_WIDTH < 0) {
            piperects[i].x = SCREEN_WIDTH;
            piperects[i].y = rand() % 2 == 0 ? 0 : SCREEN_HEIGHT - (rand() % (SCREEN_HEIGHT - PIPE_HEIGHT * 2) + PIPE_HEIGHT);
        }
        if(checkCollision(birdrect, piperects[i])) {
            endGame();
        }
    }
}

void renderPipes(SDL_Renderer* renderer) {
    for(int i = 0; i < NUM_PIPES; i++) {
        SDL_RenderCopy(renderer, pipeTxt, NULL, &piperects[i]);
    }
}

void update(){
    backgroundrect.x-=1;
    backgroundrect2.x-=1;
    birdrect.y+=4;
    updatePipes();
    if(backgroundrect.x+backgroundrect.w<0){
        backgroundrect.x=715;
    }
    if(backgroundrect2.x+backgroundrect2.w<0){
        backgroundrect2.x=715;
    }
    if(isTouching){birdrect.y-=10;}
}

void render(SDL_Renderer* renderer){
    SDL_RenderClear(renderer);
SDL_RenderCopy(renderer,backgroundTxt,NULL,&backgroundrect);
SDL_RenderCopy(renderer,backgroundTxt,NULL,&backgroundrect2);
renderPipes(renderer);
SDL_RenderCopy(renderer,birdTxt,NULL,&birdrect);
SDL_RenderPresent(renderer);
}

int main(){
SDL_Init(SDL_INIT_EVERYTHING);
SDL_Window* window = SDL_CreateWindow("FlaPUP",0,0,720,1544,0);
SDL_Renderer* renderer = SDL_CreateRenderer(window,0,0);
init(renderer);
//Game Loop
while(1){
eventHandler();
update();
render(renderer);
}
SDL_Delay(2000);
}