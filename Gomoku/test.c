#include <SDL2/SDL.h>

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	int running = 1;
	SDL_Event event;
	while (running){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
				running = 0;
		}
		}

		SDL_SetRenderDrawColor(renderer, 255, 204, 51, 255);
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		for(int i = 1; i< 100; i++){
			SDL_RenderDrawLine(renderer, 1+i*20, 0, 1+i*20, 480);
			SDL_RenderDrawLine(renderer, 0, 1+i*20, 640, 1+i*20);
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}
