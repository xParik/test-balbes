#include <SDL.h>
#include <iostream>
#include <vector>
using namespace std;

// Структура для стен лабиринта 
struct Wall {
    SDL_Rect rect;
};

// Функция для отрисовки лабиринта 
void drawMaze(SDL_Renderer* renderer, const vector<Wall>& walls) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Красный цвет для стен 
    for (const auto& wall : walls) {
        SDL_RenderFillRect(renderer, &wall.rect);
    }
}

int main(int argc, char* argv[]) {
    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Создаем окно
    SDL_Window* window = SDL_CreateWindow("Простая игра на SDL2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Ошибка создания окна: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Создаем рендер
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Ошибка создания рендера: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Загрузка изображения персонажа
    SDL_Surface* tempSurface = SDL_LoadBMP("character.bmp");
    if (!tempSurface) {
        cout << "Ошибка загрузки изображения: " << SDL_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Texture* characterTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_Rect characterRect = { 20, 35, 64, 64 }; // Положение и размер персонажа
    const int speed = 1; // Скорость перемещения

    int windowWidth = 800;
    int windowHeight = 600;

    // Создаем лабиринт (стены) 
    vector<Wall> walls = {
    {{0, 0, 10, 300}}, //левая стена
    {{0, 590, 3000, 10}},  //нижняя стена
    {{0, 0, 3000, 10}},  //верхняя стена
    {{100, 0, 10, 300}}, //правая стена
    {{0, 300, 10, 300}}, //левая стена1
    {{100, 390, 300, 10}},  //нижняя стена1
    {{100, 300, 300, 10}},  //верхняя стена1
    {{300, 400, 10, 300}}, //правая стена1
    {{400, 160, 10, 150}}, //левая стена2
    {{500, 390, 300, 10}},  //нижняя стена2
    {{500, 300, 300, 10}},  //верхняя стена2
    {{790, 0, 10, 500}}, //правая стена2
    {{400, 390, 10, 100}}, //левая стена3
    {{500, 500, 200, 10}},  //нижняя стена3
    {{400, 150, 300, 10}},  //верхняя стена3
    {{100, 400, 10, 100}}, //правая стена3
    {{100, 390, 300, 10}},  //нижняя стена1
    {{100, 300, 300, 10}},  //верхняя стена1
    {{300, 400, 10, 300}}, //правая стена1
    {{400, 160, 10, 150}}, //левая стена2
    {{500, 390, 300, 10}},  //нижняя стена2
    {{500, 300, 300, 10}},  //верхняя стена2
    {{790, 0, 10, 500}}, //правая стена2
    {{400, 390, 10, 100}}, //левая стена3
    {{500, 500, 200, 10}},  //нижняя стена3
    {{400, 150, 300, 10}},  //верхняя стена3
    {{100, 400, 10, 100}} //правая стена3
    };

    // Основной цикл игры
    bool isRunning = true;
    SDL_Event event;


    while (isRunning) {
        // Обрабатываем события
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Получение состояния клавиш
        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        // Обработка нажатий клавиш WASD
        if (keystate[SDL_SCANCODE_W]) {
            characterRect.y -= speed;
        }
        if (keystate[SDL_SCANCODE_S]) {
            characterRect.y += speed;
        }
        if (keystate[SDL_SCANCODE_A]) {
            characterRect.x -= speed;
        }
        if (keystate[SDL_SCANCODE_D]) {
            characterRect.x += speed;
        }

        // Очищаем экран
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Черный фон
        SDL_RenderClear(renderer);

        // Отрисовка лабиринта 
        drawMaze(renderer, walls);

        // Отрисовка персонажа
        SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect);

        // Обновляем экран
        SDL_RenderPresent(renderer);
    }

    // Очищаем ресурсы
    SDL_DestroyTexture(characterTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}