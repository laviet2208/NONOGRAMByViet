#pragma once

#include <iostream>
#include "bitmap.h"
#include <SDL.h>



void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect, const bool leftMouse = false);


// Xoá và vẽ lại toàn bộ màn hình với 1 hình chữ nhật
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer,
    const SDL_Rect& filled_rect, const bool leftMouse)
{


    // Vẽ hình chữ nhật với màu tuỳ thuộc nút chuột trái hay phải được nhấn
    if (leftMouse)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
    else
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   // green
    SDL_RenderFillRect(renderer, &filled_rect);

    // Dùng lệnh hiển thị (đưa) hình đã vẽ ra mành hình
   //Khi thông thường chạy với môi trường bình thường ở nhà
    SDL_RenderPresent(renderer);

}


