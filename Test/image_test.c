#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL Image Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    // 첫 번째 이미지 로드
    SDL_Surface* imageSurface1 = IMG_Load("image.jpg");
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, imageSurface1);
    SDL_Rect destRect1 = {120, 70, 400, 70};

    // 두 번째 이미지 로드
    SDL_Surface* imageSurface2 = IMG_Load("image1.jpg");
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, imageSurface2);
    SDL_Rect destRect2 = {120, 210, 400, 70};

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
            }
        }

        SDL_RenderClear(renderer); // 화면 지우기
        SDL_RenderCopy(renderer, texture1, NULL, &destRect1); // 첫 번째 이미지 그리기
        SDL_RenderCopy(renderer, texture2, NULL, &destRect2); // 두 번째 이미지 그리기
        SDL_RenderPresent(renderer);
    }

    // 메모리 해제
    SDL_DestroyTexture(texture1);
    SDL_FreeSurface(imageSurface1);
    SDL_DestroyTexture(texture2);
    SDL_FreeSurface(imageSurface2);

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
