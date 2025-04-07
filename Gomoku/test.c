#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


typedef enum{
	STATE_GAME
}GameState;

typedef struct {
    int x, y;
	int iswhite;
} CirclePos;

CirclePos circles[100];
int circleCount = 0;
int iswhiteturn = 1;

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	IMG_Init(IMG_INIT_JPG); //JPG 지원 활성화

	SDL_Surface* imgSurface = IMG_Load("image.jpg"); //불러올 이미지 파일
	SDL_Texture* circleTexture = IMG_LoadTexture(renderer, "백.png");
	SDL_Texture* circleTexture2 = IMG_LoadTexture(renderer, "흑.png");
	if(!imgSurface) {

		printf("이미지를 불러올 수 없습니다! 오류:%s\n", IMG_GetError());
		return -1;
	}
	if (!circleTexture) {
		 printf("백.png를 불러올 수 없습니다: %s\n", IMG_GetError());
		 return -1;
	}
	if (!circleTexture2) {
    printf("흑.png를 불러올 수 없습니다: %s\n", IMG_GetError());
    return -1;
}
//
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imgSurface);
	SDL_FreeSurface(imgSurface);

	SDL_Rect buttonRect = {120, 70, 401, 71}; //시작 클릭 가능 영역
	SDL_Rect buttonRect2 = {120, 210, 401, 211}; //설정 클릭 가능 영역
	SDL_Rect buttonRect3 = {120, 350, 401, 351}; // 종료 클릭 가능 영역
	SDL_Rect backButton = {0, 0, 161, 41}; //뒤로가기 클릭 가능 영
	int GameScreen = 0;	//현재 화면 상태(0 = 첫번째화면 1 = 두번째역화면)

	int running = 1;
	SDL_Event event;
	while (running){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
				running = 0; // 첫 번째로 뜨는 스크린 화면
			}

		if(event.type == SDL_MOUSEBUTTONDOWN){
			int mouseX = event.button.x; //x좌표 확인
			int mouseY = event.button.y; //y좌표 확인
			if(GameScreen == 0){
				if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w && 
					mouseY >= buttonRect.y &&mouseY <= buttonRect.y + buttonRect.h){
					GameScreen = 1; //화면전환
				}
				if (mouseX >= buttonRect2.x && mouseX <= buttonRect2.x + buttonRect2.w &&
					mouseY >= buttonRect2.y && mouseY <= buttonRect2.y + buttonRect2.h){
					GameScreen = 2; //2번화면 전환
				}
				if (mouseX >= buttonRect3.x && mouseX <= buttonRect3.x + buttonRect3.w &&
					mouseY >= buttonRect3.y && mouseY <= buttonRect3.y + buttonRect3.h){
					running = 0;
				}
			}
			if(GameScreen == 1){//GameScreen 이 1일때 (게임시작화면일때)
				if (mouseX >= backButton.x && mouseX <= backButton.x + backButton.w &&
					mouseY >= backButton.y && mouseY <= backButton.y + backButton.h){
					GameScreen = 0; // 메인메뉴로 돌아간다
				}
				else {
       			 // 게임 화면에서 클릭 시 동그라미 위치 저장
        			if (circleCount < 100) {
            			circles[circleCount].x = mouseX;
            			circles[circleCount].y = mouseY;
						circles[circleCount].iswhite = iswhiteturn;
            			circleCount++;
						iswhiteturn = !iswhiteturn;
        			}
    			}
			}
			if(GameScreen == 2){//GameScreen 이 2일때 (설정화면일때)
				if (mouseX >= backButton.x && mouseX <= backButton.x + backButton.w &&
					mouseY >= backButton.y && mouseY <= backButton.y + backButton.h){
					GameScreen = 0; // 메인메뉴로 돌아간다
				}
			}
		}				
	}						
		if(GameScreen==0){
			SDL_SetRenderDrawColor(renderer, 255, 204, 51, 255);
			SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		for(int i = 1; i < 7; i++){//메인메뉴 가로줄 6개 만드는 코드
			SDL_RenderDrawLine(renderer, 120, i*70, 520, i*70);
		}
		for(int i = 1; i < 4; i++){//메인메뉴 왼쪽오른쪽 세로줄 3개 만드는 코드
				SDL_RenderDrawLine(renderer, 120, (i*140)-70, 120, i*140);
				SDL_RenderDrawLine(renderer, 520, (i*140)-70, 520, i*140);
		}
		SDL_Rect destRect = {120, 70, 401, 71}; //이미지 크기
		SDL_RenderCopy(renderer, texture, NULL, &destRect);
	}
		else if(GameScreen==1){
			SDL_SetRenderDrawColor(renderer, 255, 205, 51, 255);
			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			for(int i = 1; i< 100; i++){
				SDL_RenderDrawLine(renderer, 1+i*20, 40, 1+i*20, 480); //99개의 가로줄 생성
				SDL_RenderDrawLine(renderer, 0, 20+i*20, 640, 20+i*20); // 99개의 세로줄 생성
			}
			for(int i = 1; i < 4; i++){
				SDL_RenderDrawLine(renderer, 1+i*160, 0, 1+i*160, 480); //상단 메뉴바 줄 생성
			}
			// 동그라미 이미지 그리기
			for (int i = 0; i < circleCount; i++) {
    			SDL_Rect dstRect = {
        		circles[i].x - 9.5,
        		circles[i].y - 9.5,
        		19,
        		19
    			};
    			if (circles[i].iswhite) {
        			SDL_RenderCopy(renderer, circleTexture, NULL, &dstRect);  // 백돌 이미지
    				}
				else {
        			SDL_RenderCopy(renderer, circleTexture2, NULL, &dstRect);  // 흑돌 이미지
    			}
			}
		}
		else if(GameScreen==2){
			SDL_SetRenderDrawColor(renderer, 255, 205, 51, 255);	
			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderDrawLine(renderer, 0, 40, 160, 40); // 상단 메뉴바 가로 줄
			SDL_RenderDrawLine(renderer, 160, 0, 160, 40); //상단 메뉴바 세로 줄
		}
		SDL_RenderPresent(renderer);
}
	SDL_DestroyTexture(texture);					
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();   // SDL_image 종료
	SDL_Quit();   // SDL 종료
	return 0;

}
