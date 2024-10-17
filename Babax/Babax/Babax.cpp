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
    {{200, 390, 200, 10}},  //нижняя стена1
    {{100, 300, 200, 10}},  //верхняя стена1
    {{300, 400, 10, 300}}, //правая стена1
    {{400, 160, 10, 150}}, //левая стена2
    {{400, 390, 300, 10}},  //нижняя стена2
    {{500, 300, 300, 10}},  //верхняя стена2
    {{790, 0, 10, 500}}, //правая стена2
    {{400, 30, 10, 100}}, //левая стена3
    {{500, 500, 50, 10}},  //нижняя стена3
    {{400, 150, 300, 10}},  //верхняя стена3
    {{100, 300, 10, 200}}, //правая стена3
    {{500, 250, 10, 50}}, //правая стена4
    {{400, 500, 400, 10}},  //нижняя стена6
    {{400, 300, 10, 100}}, //левая стена7
    {{200, 200, 200, 10}},  //нижняя стена7
    {{100, 100, 200, 10}},  //верхняя стена7
    {{400, 100, 10, 50}}, //правая стена7
    {{500, 10, 10, 50}}, //левая стена8
    {{100, 500, 100, 10}},  //нижняя стена8
    {{600, 100, 10, 50}}, //правая стена8
    {{700, 10, 10, 50}}, //левая стена9
    {{690, 160, 10, 50}}, //правая стена9
    {{600, 400, 10, 15}}, //левая стенаF
    {{400, 400, 10, 15}}, //правая стенаF
    {{500, 490, 10, 20}}, //левая стенаZ
    };

    bool checkCollision(const SDL_Rect & character, const vector<Wall>&walls) {
        for (const auto& wall : walls) {
            if (SDL_HasIntersection(&character, &wall.rect)) {
                return true; // Столкновение произошло
            }
        }
        return false; // Столкновений нет
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

        // Проверка на выход за границы окна
        if (characterRect.x < 0) characterRect.x = 0;
        if (characterRect.x + characterRect.w > windowWidth)
            characterRect.x = windowWidth - characterRect.w;
        if (characterRect.y < 0) characterRect.y = 0;
        if (characterRect.y + characterRect.h > windowHeight)
            characterRect.y = windowHeight - characterRect.h;

        // Проверка столкновений
        if (!checkCollision(tempRect, walls)) {
            characterRect = tempRect; // Перемещаем персонажа только если нет столкновений
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