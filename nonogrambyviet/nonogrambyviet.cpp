#include "bitmap.h"
#include "mouse.h"
#include "music.h"


using namespace std;


int main(int argc, char* argv[])
{
    //phần khai báo biến
    int checklevel = 0; // biến dùng để chọn level trong game
    int checkmenu = 0; // khi biến này bằng 0 thì sẽ load ra menu của game
    int checkchoose = 0;
    int checkguide = 0;
   
    int checkpause = 0;
    int checkfalselv1 = 0;
    int checktruelv1 = 0;
    int checkwin1 = 0;
    int checklose = 0;
    int checktruelv2 = 0;
    int checkfalselv2 = 0;
    int checktruelv3 = 0;
    int checkfalselv3 = 0;
    int checktruelv4 = 0;
    int checkfalselv4 = 0;
    int checktruelv5 = 0;
    int checkfalselv5 = 0;

    SDL_Event mouse_guide;
    SDL_Event mouse_lv1; // biến xử lý sự kiện trong level 1
    SDL_Event mouse_lv2; // biến xử lý sự kiện trong level 2
    SDL_Event mouse_lv3; // biến xử lý sự kiện trong level 3
    SDL_Event mouse_lv4; // biến xử lý sự kiện trong level 4
    SDL_Event mouse_lv5; //biến xử lý sự kiện trong level 5
    SDL_Event check_win1; // xử lý sự kiện nếu thắng level 1
    SDL_Event check_lose1;
    SDL_Event check_lose2;
    SDL_Event check_lose3;
    SDL_Event check_lose4;
    SDL_Event check_lose5;
    SDL_Event check_win2; // xử lý sự kiện nếu thắng level 2
    SDL_Event check_winlv3; // xử lý sự kiện nếu thắng level 3
    SDL_Event check_winlv4; // xử lý sự kiện nếu thắng level 4
    SDL_Event check_winlv5;
    SDL_Event menu_game; // biến xử lý sự kiện trong menu game
    SDL_Event choose_level; // biến xử lý sự kiện khi chọn level   
    

    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return -1;
    }

    // các ma trận lưu đáp án của các level trong game
    int level1[10][10] = { {0,0,1,1,0,2,1,1,0,0} , {0,2,2,1,0,0,1,2,0,2}, {2,1,1,1,0,0,1,1,1,0} , {1,1,0,2,0,0,0,2,1,1} , {1,1,2,2,1,1,0,0,1,1} , {0,1,1,1,1,1,1,1,1,0} , {0,2,1,0,2,0,2,1,2,2},{2,0,1,1,2,2,1,1,2,2},{2,0,1,1,0,2,1,1,2,0},{2,2,0,1,2,2,1,0,0,2} };
    int level1t[10][10] = { {0,0,1,1,0,2,1,1,0,0} , {0,2,2,1,0,0,1,2,0,2}, {2,1,1,1,0,0,1,1,1,0} , {1,1,0,2,0,0,0,2,1,1} , {1,1,2,2,1,1,0,0,1,1} , {0,1,1,1,1,1,1,1,1,0} , {0,2,1,0,2,0,2,1,2,2},{2,0,1,1,2,2,1,1,2,2},{2,0,1,1,0,2,1,1,2,0},{2,2,0,1,2,2,1,0,0,2} };
    int level2t[10][10] = { {1,1,1,1,1,2,1,1,1,1} , {1,1,1,1,2,2,1,1,1,1} , {1,1,1,2,1,2,1,1,1,1}, {1,1,1,2,1,2,2,2,1,1} , {2,2,2,2,1,1,1,1,2,1} , {1,2,1,1,1,1,2,2,2,2} , {1,1,2,2,2,1,2,1,1,1},{1,1,1,1,2,1,2,1,1,1},{1,1,1,1,2,2,1,1,1,1},{1,1,1,1,2,1,1,1,1,1} };
    int level2[10][10] = { {1,1,1,1,1,2,1,1,1,1} , {1,1,1,1,2,2,1,1,1,1} , {1,1,1,2,1,2,1,1,1,1}, {1,1,1,2,1,2,2,2,1,1} , {2,2,2,2,1,1,1,1,2,1} , {1,2,1,1,1,1,2,2,2,2} , {1,1,2,2,2,1,2,1,1,1},{1,1,1,1,2,1,2,1,1,1},{1,1,1,1,2,2,1,1,1,1},{1,1,1,1,2,1,1,1,1,1} };
    int level4[10][10] = { {2,2,2,1,1,2,1,1,2,2} , {2,2,2,1,1,1,1,1,2,2},{2,2,2,1,1,1,1,1,2,2} , {2,2,2,1,1,1,1,1,2,2} , {2,2,2,1,1,1,1,1,1,1} , {2,2,2,1,1,1,1,1,1,2} , {2,2,2,1,1,1,1,1,1,2}, {2,2,1,1,1,1,1,1,2,2},{1,2,1,1,1,1,1,1,2,2},{1,1,1,1,1,1,1,1,1,2} };
    int level3[10][10] = { {2,1,2,1,2,1,2,2,2,2},{2,1,2,1,1,1,1,2,2,2} , {2,1,2,2,1,1,1,1,2,2} , {2,1,2,1,1,1,1,1,1,2} , {2,1,1,1,1,1,1,1,1,1},{2,1,2,2,1,1,1,2,2,2} , {2,1,2,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1} ,{2,1,2,2,1,1,1,1,1,2},{2,1,1,1,1,1,1,1,1,2} };
    int level3t[10][10] = { {2,1,2,1,2,1,2,2,2,2},{2,1,2,1,1,1,1,2,2,2} , {2,1,2,2,1,1,1,1,2,2} , {2,1,2,1,1,1,1,1,1,2} , {2,1,1,1,1,1,1,1,1,1},{2,1,2,2,1,1,1,2,2,2} , {2,1,2,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1} ,{2,1,2,2,1,1,1,1,1,2},{2,1,1,1,1,1,1,1,1,2} };
    int level4t[10][10] = { {2,2,2,1,1,2,1,1,2,2} , {2,2,2,1,1,1,1,1,2,2},{2,2,2,1,1,1,1,1,2,2} , {2,2,2,1,1,1,1,1,2,2} , {2,2,2,1,1,1,1,1,1,1} , {2,2,2,1,1,1,1,1,1,2} , {2,2,2,1,1,1,1,1,1,2}, {2,2,1,1,1,1,1,1,2,2},{1,2,1,1,1,1,1,1,2,2},{1,1,1,1,1,1,1,1,1,2} };
    int level5[15][15] = { {2,2,2,2,1,1,1,1,1,2,2,2,2,2,2},{2,2,2,1,1,1,1,1,2,2,1,1,2,2,2},{2,2,2,1,1,1,1,2,2,1,1,1,1,2,2},{2,1,1,2,2,1,1,2,1,1,1,1,1,2,2},{1,1,1,1,2,2,1,2,1,1,2,2,1,1,2},{1,1,1,1,2,2,2,1,1,2,1,1,1,1,1},{1,1,1,1,1,2,1,2,2,1,1,1,1,1,1},{2,1,1,1,1,1,1,2,1,1,1,1,1,1,2},{2,2,1,1,2,1,1,1,1,1,1,1,1,2,2},{2,2,2,2,2,1,1,1,1,1,2,2,2,2,2},{2,2,2,2,2,1,1,1,1,1,2,2,2,2,2},{2,2,2,2,1,1,1,1,1,1,1,2,2,2,2},{2,2,2,2,1,1,1,1,1,1,1,2,2,2,2},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
    int level5t[15][15] = { {2,2,2,2,1,1,1,1,1,2,2,2,2,2,2},{2,2,2,1,1,1,1,1,2,2,1,1,2,2,2},{2,2,2,1,1,1,1,2,2,1,1,1,1,2,2},{2,1,1,2,2,1,1,2,1,1,1,1,1,2,2},{1,1,1,1,2,2,1,2,1,1,2,2,1,1,2},{1,1,1,1,2,2,2,1,1,2,1,1,1,1,1},{1,1,1,1,1,2,1,2,2,1,1,1,1,1,1},{2,1,1,1,1,1,1,2,1,1,1,1,1,1,2},{2,2,1,1,2,1,1,1,1,1,1,1,1,2,2},{2,2,2,2,2,1,1,1,1,1,2,2,2,2,2},{2,2,2,2,2,1,1,1,1,1,2,2,2,2,2},{2,2,2,2,1,1,1,1,1,1,1,2,2,2,2},{2,2,2,2,1,1,1,1,1,1,1,2,2,2,2},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
    //------------------------------------------------
    Mix_Music* music_menu = Mix_LoadMUS("music//soundtrack1.wav");
    SDL_Texture* bgr1 = loadTexture("image//10x10lv1.bmp", renderer);
    //Nạp ảnh vào một biến texture 
    SDL_Texture* pauseimg = loadTexture("image//pauseimg.bmp", renderer);
    SDL_Texture* pause = loadTexture("image//pause.bmp",renderer);
    SDL_Texture* tree = loadTexture("level5//tree.bmp", renderer);
    SDL_Texture* bgr4 = loadTexture("level4//10x10lv4.bmp", renderer);
    SDL_Texture* blueheart = loadTexture("level4//blueheart.bmp", renderer);
    SDL_Texture* win4 = loadTexture("level4//winlv4.bmp", renderer);
    SDL_Texture* luckycat = loadTexture("level4//luckycat.bmp", renderer);
    SDL_Texture* iftrue4 = loadTexture("level4//picktruelv4.bmp", renderer);
    SDL_Texture* iffalse4 = loadTexture("level4//iffalse4.bmp", renderer);
    SDL_Texture* bgr3 = loadTexture("level3//10x10lv3.bmp", renderer);
    SDL_Texture* ninja = loadTexture("level3//ninja.bmp", renderer);
    SDL_Texture* iftrue3 = loadTexture("level3//picktruelv3.bmp", renderer);
    SDL_Texture* tieptuc3 = loadTexture("level3//continue.bmp", renderer);
    SDL_Texture* mainmenu3 = loadTexture("level3//mainmenu.bmp", renderer);
    SDL_Texture* winlv3 = loadTexture("level3//winlv3.bmp", renderer);
    SDL_Texture* redheart = loadTexture("image//redheart.bmp", renderer);
    SDL_Texture* iffalsered = loadTexture("image//iffalsered.bmp", renderer);
    SDL_Texture* knighthat1 = loadTexture("image//cpt1.1.bmp", renderer);
    SDL_Texture* picktrue = loadTexture("image//picktrue.bmp", renderer);
    SDL_Texture* pickfalse = loadTexture("image//pickfalse.bmp", renderer);
    SDL_Texture* greenheart = loadTexture("image//greenheart.bmp", renderer);
    SDL_Texture* iffalse = loadTexture("image//iffalse.bmp", renderer);
    SDL_Texture* mouseexit = loadTexture("menu//checkexit.bmp", renderer);
    SDL_Texture* mouseplg = loadTexture("menu//checkplg.bmp", renderer);
    SDL_Texture* checkg = loadTexture("menu//checkg.bmp", renderer);
    SDL_Texture* guidetext = loadTexture("menu//guidetext.bmp", renderer);
    SDL_Texture* clickbck = loadTexture("menu//back.bmp", renderer);
    SDL_Texture* knighthat = loadTexture("image//cpt1.bmp", renderer);
    SDL_Texture* win = loadTexture("image//win1.bmp", renderer);
    SDL_Texture* bgr2 = loadTexture("image//10x10lv2.bmp", renderer);
    SDL_Texture* lose1 = loadTexture("image//gameovlv1.bmp", renderer);
    SDL_Texture* menu = loadTexture("menu//menu.bmp", renderer);
    SDL_Texture* plgame = loadTexture("menu//playgame.bmp", renderer);
    SDL_Texture* guide = loadTexture("menu//guide.bmp", renderer);
    SDL_Texture* exit = loadTexture("menu//exitgame.bmp", renderer);
    SDL_Texture* pickstage = loadTexture("menu//picklevel.bmp", renderer);
    SDL_Texture* movelv1 = loadTexture("menu//movelv1.bmp", renderer);
    SDL_Texture* movelv2 = loadTexture("menu//movelv2.bmp", renderer);
    SDL_Texture* movelv3 = loadTexture("menu//movelv3.bmp", renderer);
    SDL_Texture* movelv4 = loadTexture("menu//movelv4.bmp", renderer);
    SDL_Texture* movelv5 = loadTexture("menu//movelv5.bmp", renderer);
    SDL_Texture* kunai = loadTexture("level2//kunai.bmp", renderer);
    SDL_Texture* mainmenu = loadTexture("menu//mainmenu.bmp", renderer);
    SDL_Texture* tieptuc = loadTexture("menu//continue.bmp", renderer);
    SDL_Texture* mainmenu4 = loadTexture("level4//mainmenu.bmp", renderer);
    SDL_Texture* tieptuc4 = loadTexture("level4//continue.bmp", renderer);
    SDL_Texture* tieptuc2 = loadTexture("level2//continue.bmp", renderer);
    SDL_Texture* mainmenu2 = loadTexture("level2//mainmenu.bmp", renderer);
    SDL_Texture* win2 = loadTexture("level2//winlv2.bmp", renderer);
    SDL_Texture* menuinplv = loadTexture("menu//menuinplv.bmp", renderer);
    SDL_Texture* playag1 = loadTexture("menu//playag1.bmp", renderer);
    SDL_Texture* gameov1 = loadTexture("menu//gameov1.bmp", renderer);
    SDL_Texture* lose2 = loadTexture("level2//loselv2.bmp", renderer);
    SDL_Texture* plag2 = loadTexture("level2//plag2.bmp", renderer);
    SDL_Texture* plag3 = loadTexture("level3//plag3.bmp", renderer);
    SDL_Texture* lose3 = loadTexture("level3//lose3.bmp", renderer);
    SDL_Texture* lose4 = loadTexture("level4//lose4.bmp", renderer);
    SDL_Texture* plag4 = loadTexture("level4//plag4.bmp", renderer);
    SDL_Texture* bgr5 = loadTexture("level5//10x10lv5.bmp", renderer);
    SDL_Texture* picktrue5 = loadTexture("level5//picktruelv5.bmp", renderer);
    SDL_Texture* false5 = loadTexture("level5//iffalse.bmp", renderer);
    SDL_Texture* heart5 = loadTexture("level5//heart.bmp", renderer);
    SDL_Texture* exit5 = loadTexture("level5//exit.bmp", renderer);
    SDL_Texture* win5 = loadTexture("level5//win5.bmp", renderer);
    //Nếu có lỗi thì giải phóng hai texture đã nạp, rồi kết thúc
    if (win5 == nullptr||exit5 == nullptr||tree == nullptr||picktrue5 == nullptr || false5 == nullptr || heart5 == nullptr||bgr5 == nullptr||lose4 == nullptr||plag4 == nullptr||lose3 == nullptr||plag3==nullptr||lose2 == nullptr || plag2 == nullptr||playag1 == nullptr||gameov1 == nullptr||menuinplv == nullptr||mainmenu2 == nullptr||tieptuc2 == nullptr||win2 == nullptr||mainmenu4 == nullptr||tieptuc4 == nullptr||iffalse4 == nullptr||bgr4 == nullptr||blueheart==nullptr||win4 == nullptr|| luckycat == nullptr ||iftrue4 == nullptr || bgr3 ==nullptr||ninja == nullptr ||iftrue3==nullptr||tieptuc3 == nullptr||mainmenu3 == nullptr||winlv3 == nullptr||mainmenu == nullptr||tieptuc == nullptr ||kunai == nullptr||redheart == nullptr|| iffalsered == nullptr || movelv1 == nullptr|| movelv2 == nullptr || movelv3 == nullptr || movelv4 == nullptr|| movelv5 == nullptr ||pickstage == nullptr ||plgame == nullptr ||guide == nullptr || exit == nullptr||lose1 == nullptr || bgr2 == nullptr || knighthat1 == nullptr || win == nullptr || knighthat == nullptr || bgr1 == nullptr || pickfalse == nullptr || picktrue == nullptr|| greenheart == nullptr || iffalse == nullptr || mouseexit == nullptr || mouseplg == nullptr || checkg == nullptr || guidetext == nullptr || clickbck == nullptr)
    {
        SDL_DestroyTexture(win5);
        SDL_DestroyTexture(exit5);
        SDL_DestroyTexture(tree);
        SDL_DestroyTexture(picktrue5);
        SDL_DestroyTexture(false5);
        SDL_DestroyTexture(heart5);
        SDL_DestroyTexture(bgr5);
        SDL_DestroyTexture(lose4);
        SDL_DestroyTexture(plag4);
        SDL_DestroyTexture(gameov1);
        SDL_DestroyTexture(playag1);
        SDL_DestroyTexture(bgr3);
        SDL_DestroyTexture(ninja);
        SDL_DestroyTexture(iftrue3);
        SDL_DestroyTexture(tieptuc3);
        SDL_DestroyTexture(mainmenu3);
        SDL_DestroyTexture(winlv3);
        SDL_DestroyTexture(menuinplv);

        SDL_DestroyTexture(mainmenu2);
        SDL_DestroyTexture(tieptuc2);
        SDL_DestroyTexture(win2);
        SDL_DestroyTexture(plag2);
        SDL_DestroyTexture(lose2);
        SDL_DestroyTexture(lose3);
        SDL_DestroyTexture(plag3);

        SDL_DestroyTexture(bgr4);
        SDL_DestroyTexture(win4);
        SDL_DestroyTexture(iftrue4);
        SDL_DestroyTexture(luckycat);
        SDL_DestroyTexture(blueheart);
        SDL_DestroyTexture(iffalse4);
        SDL_DestroyTexture(mainmenu4);
        SDL_DestroyTexture(tieptuc4);

        SDL_DestroyTexture(mainmenu);
        SDL_DestroyTexture(tieptuc);
        SDL_DestroyTexture(kunai);
        SDL_DestroyTexture(movelv1);
        SDL_DestroyTexture(movelv2);
        SDL_DestroyTexture(movelv3);
        SDL_DestroyTexture(movelv4);
        SDL_DestroyTexture(movelv5);
        SDL_DestroyTexture(redheart);
        SDL_DestroyTexture(iffalsered);
        SDL_DestroyTexture(pickstage);
        SDL_DestroyTexture(exit);
        SDL_DestroyTexture(guide);
        SDL_DestroyTexture(plgame);
        SDL_DestroyTexture(bgr2);
        SDL_DestroyTexture(bgr1);
        SDL_DestroyTexture(pickfalse);
        SDL_DestroyTexture(picktrue);
        SDL_DestroyTexture(menu);
        SDL_DestroyTexture(greenheart);
        SDL_DestroyTexture(iffalse);
        SDL_DestroyTexture(mouseexit);
        SDL_DestroyTexture(mouseplg);
        SDL_DestroyTexture(checkg);
        SDL_DestroyTexture(guidetext);
        SDL_DestroyTexture(clickbck);
        SDL_DestroyTexture(gameov1);
        SDL_DestroyTexture(knighthat);
        SDL_DestroyTexture(win);
        SDL_DestroyTexture(knighthat1);
        SDL_DestroyTexture(lose1);
        quitSDL(window, renderer);
    }
    
   

    //Xoá màn hình
    SDL_RenderClear(renderer);


    //-------------------------MENU cho game-----------------------------------------
 
       
    
    menu:
    while (checkmenu == 0)
    {

        renderTexture(menu, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_RenderPresent(renderer);
        if (SDL_WaitEvent(&menu_game) == 0) continue;
        if (menu_game.type == SDL_QUIT) break;
        if (menu_game.type == SDL_KEYDOWN && menu_game.key.keysym.sym == SDLK_ESCAPE) break;
        while (SDL_PollEvent(&menu_game))
        {
            if (menu_game.type == SDL_QUIT) return 0;
            if (menu_game.type == SDL_MOUSEMOTION)
            {
               if (menu_game.button.x >= 1384 && menu_game.button.x <= 1539)
                {
                    if (menu_game.button.y >= 380 && menu_game.button.y <= 460)
                    {
                        renderTexture(checkg, renderer, 1384, 380, 155, 80);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(300);
                    }
                }
                if (menu_game.button.x >= 1257 && menu_game.button.x <= 1541 )
                {
                    if( menu_game.button.y >= 181 && menu_game.button.y <= 267)
                    {
                        renderTexture(mouseplg, renderer, 1257, 181, 284, 86);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(500);
                    }
                }

                if (menu_game.button.x >= 1328 && menu_game.button.x <= 1547)
                {
                    if (menu_game.button.y >= 280 && menu_game.button.y <= 360)
                    {
                        renderTexture(mouseexit, renderer, 1328, 280, 219, 90);                        
                        SDL_RenderPresent(renderer);
                        SDL_Delay(500);
                    }
                }
            }
            if (menu_game.type == SDL_MOUSEBUTTONDOWN)
            {
                if (menu_game.button.x >= 1350 && menu_game.button.x <= 1547)
                {
                    if (menu_game.button.y >= 360&& menu_game.button.y <= 450)
                    {
                        loadmixer("music//tick.wav");
                        checkguide = 1;
                        checkmenu = 1;
                        break;
                        SDL_Delay(500);
                    }
                }
                if (menu_game.button.x >= 1257 && menu_game.button.x <= 1541)
                {
                    if (menu_game.button.y >= 181 && menu_game.button.y <= 267)
                    {
                        loadmixer("music//tick.wav");
                        checkchoose = 1;
                        checkmenu = 1;
                        break;
                    }
                }

                if (menu_game.button.x >= 1328 && menu_game.button.x <= 1547)
                {
                    if (menu_game.button.y >= 280 && menu_game.button.y <= 370)
                    {
                        loadmixer("music//tick.wav");
                        SDL_Delay(10);
                        menu_game.type = SDL_QUIT;
                        return 0;
                    }
                }
            }

        }
        if (checkchoose == 1 || checkmenu == 1 || checkguide == 1)
        {
            break;
        }

    }
    


    //-----------------sự kiện trong guide-----------------------------//
    while (true && checkguide == 1)
    {
        if (SDL_WaitEvent(&mouse_guide) == 0) continue;
        if(mouse_guide.type == SDL_QUIT) break;
        if (mouse_guide.type == SDL_KEYDOWN && mouse_guide.key.keysym.sym == SDLK_ESCAPE) break;

        renderTexture(guidetext, renderer, 920, 187, 650, 600);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&mouse_guide))
        {
            if (mouse_guide.type == SDL_QUIT) return 0;
            if (mouse_guide.type == SDL_MOUSEMOTION)
            {
                if (mouse_guide.button.y >= 700 && mouse_guide.button.y <= 800)
                {
                    if (mouse_guide.button.x >= 1450 && mouse_guide.button.x <= 1600)
                    {
                        renderTexture(clickbck, renderer, 1480, 730, 80, 50);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(200);
                    }
                }
            }
            if (mouse_guide.type == SDL_MOUSEBUTTONDOWN)
            {
                if (mouse_guide.button.y >= 700 && mouse_guide.button.y <= 800)
                {
                    if (mouse_guide.button.x >= 1450 && mouse_guide.button.x <= 1600)
                    {
                        loadmixer("music//tick.wav");
                        checkguide = 0;
                        checkmenu = 0;
                        goto menu;
                        break;
                    }
                }
            }
        }
        if (checkguide == 0)
        {
            break;
        }

    }
    //----------------phần chọn level cho game-------------------------//
    while (true && checkchoose == 1)
    {

        if (SDL_WaitEvent(&choose_level) == 0) continue;
        if (choose_level.type == SDL_QUIT) break;
        if (choose_level.type == SDL_KEYDOWN && choose_level.key.keysym.sym == SDLK_ESCAPE) break;

        //Vẽ ảnh nền giao diện chọn level
        renderTexture(pickstage, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_RenderPresent(renderer);
                                                   
        while (SDL_PollEvent(&choose_level))
        {
            if (choose_level.type == SDL_QUIT) return 0;
            // nếu di chuột vào đúng vị trí thì sẽ hiển thị để nhận biết
            if (choose_level.type == SDL_MOUSEMOTION)
            {
                
                if (choose_level.button.x >= 896 && choose_level.button.x <= 1091)
                {
                    if (choose_level.button.y >= 540 && choose_level.button.y <= 590)
                    {
                        renderTexture(menuinplv, renderer, 896, 540, 195, 50);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(200);
                    }
                }
                if (choose_level.button.x >= 73 && choose_level.button.x <= 250)
                {
                    if (choose_level.button.y >= 160 && choose_level.button.y <= 330)
                    {
                        renderTexture(movelv1, renderer, 73, 160, 176, 170);
                        SDL_RenderPresent(renderer);
                    }
                }

                if (choose_level.button.x >= 262 && choose_level.button.x <= 438)
                {
                    if (choose_level.button.y >= 160 && choose_level.button.y <= 330)
                    {
                        renderTexture(movelv2, renderer, 262, 160, 176, 170);
                        SDL_RenderPresent(renderer);
                    }
                }

                if (choose_level.button.x >= 454 && choose_level.button.x <= 630)
                {
                    if (choose_level.button.y >= 160 && choose_level.button.y <= 330)
                    {
                        renderTexture(movelv3, renderer, 454, 160, 176, 170);
                        SDL_RenderPresent(renderer);
                    }
                }

                if (choose_level.button.x >= 638 && choose_level.button.x <= 814)
                {
                    if (choose_level.button.y >= 340 && choose_level.button.y <= 510)
                    {
                        renderTexture(movelv4, renderer, 638, 340, 176, 170);
                        SDL_RenderPresent(renderer);
                    }
                }

                if (choose_level.button.x >= 830 && choose_level.button.x <= 1006)
                {
                    if (choose_level.button.y >= 340 && choose_level.button.y <= 510)
                    {
                        renderTexture(movelv5, renderer, 830, 340, 176, 170);
                        SDL_RenderPresent(renderer);
                    }
                }

                
            }

            if (choose_level.type == SDL_MOUSEBUTTONDOWN)
            {
                if (choose_level.button.x >= 896 && choose_level.button.x <= 1091)
                {
                    if (choose_level.button.y >= 540 && choose_level.button.y <= 590)
                    {
                        loadmixer("music//tick.wav");
                        checkchoose = 0;
                        checkmenu = 0;
                        goto menu;
                        break;
                    }
                }

                if (choose_level.button.x >= 73 && choose_level.button.x <= 250)
                {
                    if (choose_level.button.y >= 160 && choose_level.button.y <= 330)
                    {
                        loadmixer("music//tick.wav");
                        checklevel = 1;
                        break;
                    }
                }

                if (choose_level.button.x >= 262 && choose_level.button.x <= 438)
                {
                    if (choose_level.button.y >= 160 && choose_level.button.y <= 330)
                    {
                        loadmixer("music//tick.wav");
                        checklevel = 2;
                        break;
                    }
                }

                if (choose_level.button.x >= 454 && choose_level.button.x <= 630)
                {
                    if (choose_level.button.y >= 160 && choose_level.button.y <= 330)
                    {
                        renderTexture(movelv3, renderer, 454, 160, 176, 170);
                        SDL_RenderPresent(renderer);
                        loadmixer("music//tick.wav");
                        SDL_Delay(50);
                        checklevel = 3;
                        break;
                    }
                }
                if (choose_level.button.x >= 638 && choose_level.button.x <= 814)
                {
                    if (choose_level.button.y >= 340 && choose_level.button.y <= 510)
                    {
                        renderTexture(movelv4, renderer, 638, 340, 176, 170);
                        SDL_RenderPresent(renderer);
                        loadmixer("music//tick.wav");
                        SDL_Delay(50);
                        checklevel = 4;
                        break;
                    }
                }

                if (choose_level.button.x >= 830 && choose_level.button.x <= 1006)
                {
                    if (choose_level.button.y >= 340 && choose_level.button.y <= 510)
                    {
                        renderTexture(movelv5, renderer, 830, 340, 176, 170);
                        SDL_RenderPresent(renderer);
                        loadmixer("music//tick.wav");
                        SDL_Delay(50);
                        checklevel = 5;
                        break;
                    }
                }
            }

        }

        if (checklevel == 1 || checklevel == 2 || checklevel == 3 || checklevel == 4 || checklevel == 5|| checkmenu == 0)
        {
            checkchoose = 0;
            break;
        }
    }

    
    
//--------------------------màn chơi số 1 , được kích hoạt khi biến checklevel = 1 ----------------------------------//
    drlv1:
    if (checklevel == 1)
    {
        //Vẽ ảnh nền level1
        renderTexture(bgr1, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_RenderPresent(renderer);
        renderTexture(greenheart, renderer, 805, 120, 54, 54);
        SDL_RenderPresent(renderer);
        renderTexture(greenheart, renderer, 805, 172, 54, 54);
        SDL_RenderPresent(renderer);
        renderTexture(greenheart, renderer, 857, 120, 54, 54);
        SDL_RenderPresent(renderer);
        renderTexture(greenheart, renderer, 857, 172, 54, 54);
        SDL_RenderPresent(renderer);        
    }
    pllv1:
    while (true && checklevel == 1)
        {
           
            if (SDL_WaitEvent(&mouse_lv1) == 0) continue;
            if (mouse_lv1.type == SDL_QUIT) break;
            if (mouse_lv1.type == SDL_KEYDOWN && mouse_lv1.key.keysym.sym == SDLK_ESCAPE) break;

            

            while (SDL_PollEvent(&mouse_lv1))
            {
                if (mouse_lv1.type == SDL_QUIT) return 0;

                if (mouse_lv1.type == SDL_MOUSEBUTTONDOWN)
                {
                    
                    // level1 game play
                    for (int j = 0; j <= 10; j++)
                    {

                        if (mouse_lv1.button.y >= 244 + 52 * j && mouse_lv1.button.y <= 297 + 52 * j)
                        {
                            for (int i = 0; i < 10; i++)
                            {
                                if (mouse_lv1.button.x >= 941 + 52 * i && mouse_lv1.button.x <= 993 + 52 * i)
                                {

                                    if (level1[j][i] == 1)
                                    {
                                        checktruelv1++;
                                        loadmixer("music//true.wav");
                                        renderTexture(picktrue, renderer, 941 + 52 * i, 244 + 51.8 * j + j, 54, 54);
                                        SDL_RenderPresent(renderer);
                                        level1[j][i] = 0;
                                    }

                                    if (level1[j][i] == 2)
                                    {
                                        checkfalselv1++;
                                        loadmixer("music//false.wav");
                                        renderTexture(pickfalse, renderer, 941 + 52 * i, 244 + 51.8 * j + j, 54, 54);
                                        SDL_RenderPresent(renderer);
                                        level1[j][i] = 0;
                                    }
                                }
                            }
                        }
                    }

                }

                //nếu chọn sai 1 lần
                if (checkfalselv1 == 1)
                {
                    renderTexture(iffalse, renderer, 805, 120, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 2 lần
                if (checkfalselv1 == 2)
                {
                    renderTexture(iffalse, renderer, 805, 172, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 3 lần
                if (checkfalselv1 == 3)
                {
                    renderTexture(iffalse, renderer, 857, 120, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 4 lần
                if (checkfalselv1 == 4)
                {
                    checklose = 1;
                    checklevel = 0;
                    checktruelv1 = 0;
                    checkfalselv1 = 0;
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            level1[i][j] = level1t[i][j];
                        }

                    }
                    renderTexture(iffalse, renderer, 857, 172, 54, 54);
                    SDL_RenderPresent(renderer);                    
                    SDL_Delay(300);
                    loadmixer("music//gameover.wav");
                    
                    break;
                }


                //nếu chiến thắng
                if (checktruelv1 == 42)
                {
                    loadmixer("music//gamewin.wav");
                    renderTexture(knighthat, renderer, 941, 244, 528, 531);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(500);
                    renderTexture(knighthat1, renderer, 941, 244, 528, 531);
                    SDL_RenderPresent(renderer);
                    checktruelv1 = 0;
                    checkfalselv1 = 0;
                    checklevel = 0;
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            level1[i][j] = level1t[i][j];
                        }

                    }
                    SDL_Delay(2000);
                    checkwin1 = 1;
                    
                    break;
                }
            }
            if (checktruelv1 == 42 || checkfalselv1 == 4)
            {
                break;
            }
        }

              
//-----------------------------màn chơi số 2 , được kích hoạt nếu biến checklevel = 2 -------------------------------------//
        drlv2:
        if (checklevel == 2)
        {
            //Vẽ ảnh nền level2
            renderTexture(bgr2, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_RenderPresent(renderer);
            renderTexture(redheart, renderer, 805, 120, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(redheart, renderer, 805, 172, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(redheart, renderer, 857, 120, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(redheart, renderer, 857, 172, 54, 54);
            SDL_RenderPresent(renderer);
        }
        pllv2:
        while (true && checklevel == 2)
        {

            if (SDL_WaitEvent(&mouse_lv2) == 0) continue;
            if (mouse_lv2.type == SDL_QUIT) break;
            if (mouse_lv2.type == SDL_KEYDOWN && mouse_lv2.key.keysym.sym == SDLK_ESCAPE) break;



            while (SDL_PollEvent(&mouse_lv2))
            {
                if (mouse_lv2.type == SDL_QUIT) return 0;
                if (mouse_lv2.type == SDL_MOUSEBUTTONDOWN)
                {

                    // level2 game play
                    for (int j = 0; j <= 10; j++)
                    {
                        if (mouse_lv2.button.y >= 244 + 52 * j && mouse_lv2.button.y <= 297 + 52 * j)
                        {
                            for (int i = 0; i < 10; i++)
                            {
                                if (mouse_lv2.button.x >= 941 + 52 * i && mouse_lv2.button.x <= 993 + 52 * i)
                                {

                                    if (level2[j][i] == 1)
                                    {
                                        checktruelv2++;
                                        loadmixer("music//true.wav");
                                        renderTexture(picktrue, renderer, 941 + 51.9 * i, 244 + 51.8 * j + j, 54, 54);
                                        SDL_RenderPresent(renderer);
                                        level2[j][i] = 0;
                                    }

                                    if (level2[j][i] == 2)
                                    {
                                        checkfalselv2++;
                                        loadmixer("music//false.wav");
                                        renderTexture(pickfalse, renderer, 941 + 52 * i, 244 + 53 * j , 54, 54);
                                        SDL_RenderPresent(renderer);
                                        level2[j][i] = 0;
                                    }
                                }
                            }
                        }
                    }

                }

                //nếu chọn sai 1 lần
                if (checkfalselv2 == 1)
                {
                    renderTexture(iffalsered, renderer, 805, 120, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 2 lần
                if (checkfalselv2 == 2)
                {
                    renderTexture(iffalsered, renderer, 805, 172, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 3 lần
                if (checkfalselv2 == 3)
                {
                    renderTexture(iffalsered, renderer, 857, 120, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 4 lần
                if (checkfalselv2 == 4)
                {

                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            level2[i][j] = level2t[i][j];
                        }
                    }
                    checklose = 2;
                    checklevel = 0;
                    checkfalselv2 = 0;
                    checktruelv2 = 0;                 
                    renderTexture(iffalsered, renderer, 857, 172, 54, 54);
                    SDL_RenderPresent(renderer);
                    loadmixer("music//gameover.wav");
                   
                    break;
                }


                //nếu chiến thắng
                if (checktruelv2 == 72)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            level2[i][j] = level2t[i][j];
                        }
                    }
                    checkfalselv2 = 0;
                    checktruelv2 = 0;
                    checklevel = 0;
                    loadmixer("music//gamewin.wav");
                    renderTexture(kunai, renderer, 941, 244, 528, 531);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(2000);
                    checkwin1 = 2;
                    
                    
                    break;
                }
            }
            if (checktruelv2 == 72 || checkfalselv2 == 4)
            {
                break;
            }
        }

//-------------------------------màn chơi số 3 , được kích hoạt khi biến checklevel = 3 ----------------------------------//        
        drlv3:
        if (checklevel == 3)
        {
            //Vẽ ảnh nền level3
            renderTexture(bgr3, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_RenderPresent(renderer);
            renderTexture(redheart, renderer, 805, 120, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(redheart, renderer, 805, 172, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(redheart, renderer, 857, 120, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(redheart, renderer, 857, 172, 54, 54);
            SDL_RenderPresent(renderer);
        }
        pllv3:
        while (true && checklevel == 3)
        {

            if (SDL_WaitEvent(&mouse_lv3) == 0) continue;
            if (mouse_lv3.type == SDL_QUIT) break;
            if (mouse_lv3.type == SDL_KEYDOWN && mouse_lv3.key.keysym.sym == SDLK_ESCAPE) break;



            while (SDL_PollEvent(&mouse_lv3))
            {
                if (mouse_lv3.type == SDL_QUIT) return 0;
                if (mouse_lv3.type == SDL_MOUSEBUTTONDOWN)
                {

                    // level3 game play
                    for (int j = 0; j <= 10; j++)
                    {
                        if (mouse_lv3.button.y >= 244 + 52 * j && mouse_lv3.button.y <= 297 + 52 * j)
                        {
                            for (int i = 0; i < 10; i++)
                            {
                                if (mouse_lv3.button.x >= 941 + 52 * i && mouse_lv3.button.x <= 993 + 52 * i)
                                {

                                    if (level3[j][i] == 1)
                                    {
                                        checktruelv3++;
                                        loadmixer("music//true.wav");
                                        renderTexture(iftrue3, renderer, 941 + 52 * i, 244 + 52.8 * j , 54, 54);
                                        SDL_RenderPresent(renderer);
                                        level3[j][i] = 0;
                                    }

                                    if (level3[j][i] == 2)
                                    {
                                        checkfalselv3++;
                                        loadmixer("music//false.wav");
                                        renderTexture(pickfalse, renderer, 941 + 52 * i, 244 + 52 * j + j, 54, 54);
                                        SDL_RenderPresent(renderer);
                                        level3[j][i] = 0;
                                    }
                                }
                            }
                        }
                    }

                }

                //nếu chọn sai 1 lần
                if (checkfalselv3 == 1)
                {
                    renderTexture(iffalsered, renderer, 805, 120, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 2 lần
                if (checkfalselv3 == 2)
                {
                    renderTexture(iffalsered, renderer, 805, 172, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 3 lần
                if (checkfalselv3 == 3)
                {
                    renderTexture(iffalsered, renderer, 857, 120, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 4 lần
                if (checkfalselv3 == 4)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            level3[i][j] = level3t[i][j];
                        }
                    }
                    checkfalselv3 = 0;
                    checktruelv3 = 0;
                    checklevel = 0;
                    checklose = 3;
                    renderTexture(iffalsered, renderer, 857, 172, 54, 54);
                    SDL_RenderPresent(renderer);
                    renderTexture(lose1, renderer, 200, 180, 460, 250);
                    SDL_RenderPresent(renderer);
                    loadmixer("music//gameover.wav");
                    break;
                }


                //nếu chiến thắng
                if (checktruelv3 == 65)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            level3[i][j] = level3t[i][j];
                        }
                    }
                    checkfalselv3 = 0;
                    checktruelv3 = 0;
                    checklevel = 0;
                    loadmixer("music//gamewin.wav");
                    renderTexture(ninja, renderer, 941, 244, 528, 531);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(2000);
                    checkwin1 = 3;
                    break;
                }
            }
            if (checktruelv3 == 65|| checkfalselv3 == 4)
            {
                break;
            }
        }

//------------------------------màn chơi số 4, được kích hoạt khi biến checklevel = 4 ----------------------------------//
        drlv4:
        if (checklevel == 4)
        {
            //Vẽ ảnh nền level4
            renderTexture(bgr4, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_RenderPresent(renderer);
            renderTexture(blueheart, renderer, 805, 120, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(blueheart, renderer, 805, 172, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(blueheart, renderer, 857, 120, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(blueheart, renderer, 857, 172, 54, 54);
            SDL_RenderPresent(renderer);
        }
        pllv4:
        while (true && checklevel == 4)
        {

            if (SDL_WaitEvent(&mouse_lv4) == 0) continue;
            if (mouse_lv4.type == SDL_QUIT) break;
            if (mouse_lv4.type == SDL_KEYDOWN && mouse_lv4.key.keysym.sym == SDLK_ESCAPE) break;



            while (SDL_PollEvent(&mouse_lv4))
            {
                if (mouse_lv4.type == SDL_QUIT) return 0;
                if (mouse_lv4.type == SDL_MOUSEBUTTONDOWN)
                {

                    // level4 game play
                    for (int j = 0; j <= 10; j++)
                    {
                        if (mouse_lv4.button.y >= 244 + 52 * j && mouse_lv4.button.y <= 297 + 52 * j)
                        {
                            for (int i = 0; i < 10; i++)
                            {
                                if (mouse_lv4.button.x >= 941 + 52 * i && mouse_lv4.button.x <= 993 + 52 * i)
                                {

                                    if (level4[j][i] == 1)
                                    {
                                        checktruelv4++;
                                        loadmixer("music//true.wav");
                                        renderTexture(iftrue4, renderer, 941 + 52 * i, 244 + 52 * j + j, 54, 54);
                                        SDL_RenderPresent(renderer);
                                        level4[j][i] = 0;
                                    }

                                    if (level4[j][i] == 2)
                                    {
                                        checkfalselv4++;
                                        loadmixer("music//false.wav");
                                        renderTexture(pickfalse, renderer, 941 + 52 * i, 244 + 52 * j + j, 54, 54);
                                        SDL_RenderPresent(renderer);
                                        level4[j][i] = 0;
                                    }
                                }
                            }
                        }
                    }

                }

                //nếu chọn sai 1 lần
                if (checkfalselv4 == 1)
                {
                    renderTexture(iffalse4, renderer, 805, 120, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 2 lần
                if (checkfalselv4 == 2)
                {
                    renderTexture(iffalse4, renderer, 805, 172, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 3 lần
                if (checkfalselv4 == 3)
                {
                    renderTexture(iffalse4, renderer, 857, 120, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 4 lần
                if (checkfalselv4 == 4)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            level4[i][j] = level4t[i][j];
                        }
                    }
                    checkfalselv4 = 0;
                    checktruelv4 = 0;
                    checklevel = 0;
                    checklose = 4;
                    renderTexture(iffalse4, renderer, 857, 172, 54, 54);
                    SDL_RenderPresent(renderer);
                    renderTexture(lose1, renderer, 200, 180, 460, 250);
                    SDL_RenderPresent(renderer);
                    loadmixer("music//gameover.wav");
                    break;
                }


                //nếu chiến thắng
                if (checktruelv4 == 60)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            level4[i][j] = level4t[i][j];
                        }
                    }
                    checkfalselv4 = 0;
                    checktruelv4 = 0;
                    checklevel = 0;
                    loadmixer("music//gamewin.wav");
                    renderTexture(luckycat, renderer, 941, 244, 528, 531);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(2000);
                    checkwin1 = 4;
                    break;
                }
            }
            if (checktruelv4 == 60 || checkfalselv4 == 4)
            {
                break;
            }
        }

//----------------------------màn chơi số 5. được kích hoạt khi biến checklevel = 5----------------------------------//
    drlv5:
        if (checklevel == 5)
        {
            //Vẽ ảnh nền level5
            renderTexture(bgr5, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_RenderPresent(renderer);
            renderTexture(heart5, renderer, 500, 74, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(heart5, renderer, 500, 127, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(heart5, renderer, 554, 74, 54, 54);
            SDL_RenderPresent(renderer);
            renderTexture(heart5, renderer, 554, 127, 54, 54);
            SDL_RenderPresent(renderer);
        }
    pllv5:
        while (true && checklevel == 5)
        {

            if (SDL_WaitEvent(&mouse_lv5) == 0) continue;
            if (mouse_lv5.type == SDL_QUIT) break;
            if (mouse_lv5.type == SDL_KEYDOWN && mouse_lv5.key.keysym.sym == SDLK_ESCAPE) break;



            while (SDL_PollEvent(&mouse_lv5))
            {
                if (mouse_lv5.type == SDL_QUIT) return 0;
                if (mouse_lv5.type == SDL_MOUSEBUTTONDOWN)
                {

                    // level5 game play
                    for (int j = 0; j <= 15; j++)
                    {
                        if (mouse_lv5.button.y >= 192 + 39.5 * j && mouse_lv5.button.y <= 231.5 + 39.5 * j)
                        {
                            for (int i = 0; i < 15; i++)
                            {
                                if (mouse_lv5.button.x >= 633 + 39 * i && mouse_lv5.button.x <= 672 + 39 * i)
                                {

                                    if (level5[j][i] == 1)
                                    {
                                        checktruelv5++;
                                        loadmixer("music//true.wav");
                                        renderTexture(picktrue5, renderer, 632 + 39 * i, 192 + 39.5 * j, 40, 40);
                                        SDL_RenderPresent(renderer);
                                        level5[j][i] = 0;
                                    }

                                    if (level5[j][i] == 2)
                                    {
                                        checkfalselv5++;
                                        loadmixer("music//false.wav");
                                        renderTexture(pickfalse, renderer, 632 + 39 * i, 192 + 39.5 * j , 40, 40);
                                        SDL_RenderPresent(renderer);
                                        level5[j][i] = 0;
                                    }
                                }
                            }
                        }
                    }

                }

                //nếu chọn sai 1 lần
                if (checkfalselv5 == 1)
                {
                    renderTexture(false5, renderer, 500, 74, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 2 lần
                if (checkfalselv5 == 2)
                {
                    renderTexture(false5, renderer, 500, 127, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 3 lần
                if (checkfalselv5 == 3)
                {
                    renderTexture(false5, renderer, 554, 75, 54, 54);
                    SDL_RenderPresent(renderer);
                }
                //nếu chọn sai 4 lần
                if (checkfalselv5 == 4)
                {
                    for (int i = 0; i < 15; i++)
                    {
                        for (int j = 0; j < 15; j++)
                        {
                            level5[i][j] = level5t[i][j];
                        }
                    }
                    checkfalselv5 = 0;
                    checktruelv5 = 0;
                    checklevel = 0;
                    checklose = 5;
                    renderTexture(false5, renderer, 554, 127, 54, 54);
                    SDL_RenderPresent(renderer);
                    loadmixer("music//gameover.wav");
                    break;
                }


                //nếu chiến thắng
                if (checktruelv5 == 137)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            level5[i][j] = level5t[i][j];
                        }
                    }
                    checkfalselv5 = 0;
                    checktruelv5 = 0;
                    checklevel = 0;
                    loadmixer("music//gamewin.wav");
                    renderTexture(tree, renderer, 633, 192, 590, 595);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(2000);
                    checkwin1 = 5;
                    break;
                }
            }
            if (checktruelv5 == 137 || checkfalselv5 == 4)
            {
                break;
            }
        }


// --------------- xử lý sự kiện trong giao diện win level 1 ----------------
        while (checkwin1 == 1)
        {
            renderTexture(win, renderer, 220, 150, 830, 500);
            SDL_RenderPresent(renderer);
            if (SDL_WaitEvent(&check_win1) == 0) continue;
            if (check_win1.type == SDL_QUIT) break;
            if (check_win1.type == SDL_KEYDOWN && check_win1.key.keysym.sym == SDLK_ESCAPE) break;

            while (SDL_PollEvent(&check_win1))
            {
                if (check_win1.type == SDL_QUIT) return 0;
                if (check_win1.type == SDL_MOUSEMOTION)
                {
                    if (check_win1.button.y <= 450 && check_win1.button.y >= 390)
                    {
                        if (check_win1.button.x <= 693 && check_win1.button.x >= 370)
                        {
                            renderTexture(mainmenu, renderer, 370, 390, 323, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(800);
                        }

                    }

                    if (check_win1.button.y <= 450 && check_win1.button.y >= 390)
                    {
                        if (check_win1.button.x <= 1010 && check_win1.button.x >= 710)
                        {
                            renderTexture(tieptuc, renderer, 710, 390, 299, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(800);
                        }

                    }
                }
                if (check_win1.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_win1.button.y <= 450 && check_win1.button.y >= 390)
                    {
                        if (check_win1.button.x <= 693 && check_win1.button.x >= 370)
                        {
                            loadmixer("music//tick.wav");
                            checkmenu = 0;
                            checkwin1 = 0;
                            goto menu;
                            break;
                        }

                    }

                    if (check_win1.button.y <= 450 && check_win1.button.y >= 390)
                    {
                        if (check_win1.button.x <= 1010 && check_win1.button.x >= 710)
                        {
                            loadmixer("music//tick.wav");
                            checklevel = 2;
                            checkwin1 = 0;
                            SDL_Delay(1000);
                            goto drlv2;
                            goto pllv2;
                            break;
                        }

                    }
                }

            }
            if (checkwin1 == 0)
            {
                break;
            }
        }
        while (checklose == 1)
        {
            renderTexture(gameov1, renderer, 220, 150, 830, 500);
            SDL_RenderPresent(renderer);
            if (SDL_WaitEvent(&check_lose1) == 0) continue;
            if (check_lose1.type == SDL_QUIT) break;
            if (check_lose1.type == SDL_KEYDOWN && check_lose1.key.keysym.sym == SDLK_ESCAPE) break;

            while (SDL_PollEvent(&check_lose1))
            {
                if (check_lose1.type == SDL_QUIT) return 0;
                if (check_lose1.type == SDL_MOUSEMOTION)
                {
                    if (check_lose1.button.y <= 450 && check_lose1.button.y >= 390)
                    {
                        if (check_lose1.button.x <= 693 && check_lose1.button.x >= 370)
                        {
                            renderTexture(mainmenu, renderer, 370, 390, 323, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(800);
                        }

                    }

                    if (check_lose1.button.y <= 450 && check_lose1.button.y >= 390)
                    {
                        if (check_lose1.button.x <= 1010 && check_lose1.button.x >= 710)
                        {
                            renderTexture(playag1, renderer, 710, 390, 299, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(800);
                        }

                    }
                }
                if (check_lose1.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_lose1.button.y <= 450 && check_lose1.button.y >= 390)
                    {
                        if (check_lose1.button.x <= 693 && check_lose1.button.x >= 370)
                        {
                            loadmixer("music//tick.wav");
                            checkmenu = 0;
                            checklose = 0;
                            goto menu;
                            break;
                        }

                    }

                    if (check_lose1.button.y <= 450 && check_lose1.button.y >= 390)
                    {
                        if (check_lose1.button.x <= 1010 && check_lose1.button.x >= 710)
                        {
                            loadmixer("music//tick.wav");
                            checklevel = 1;
                            checklose = 0;
                            SDL_Delay(100);
                            goto drlv1;
                            goto pllv1;
                            break;
                        }

                    }
                }

            }
            if (checklose == 0)
            {
                break;
            }
        }

// ------------------ xử lý sự kiện trong giao diện win level 2 --------------
        while (checkwin1 == 2)
        {
            renderTexture(win2, renderer, 220, 150, 830, 500);
            SDL_RenderPresent(renderer);
            if (SDL_WaitEvent(&check_win2) == 0) continue;
            if (check_win2.type == SDL_QUIT) break;
            if (check_win2.type == SDL_KEYDOWN && check_win2.key.keysym.sym == SDLK_ESCAPE) break;

            while (SDL_PollEvent(&check_win2))
            {
                if (check_win2.type == SDL_QUIT) return 0;
                if (check_win2.type == SDL_MOUSEMOTION)
                {
                    if (check_win2.button.y <= 450 && check_win2.button.y >= 390)
                    {
                        if (check_win2.button.x <= 693 && check_win2.button.x >= 370)
                        {
                            renderTexture(mainmenu2, renderer, 370, 390, 323, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }

                    if (check_win2.button.y <= 450 && check_win2.button.y >= 390)
                    {
                        if (check_win2.button.x <= 1010 && check_win2.button.x >= 710)
                        {
                            renderTexture(tieptuc2, renderer, 710, 390, 299, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }
                }
                if (check_win2.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_win2.button.y <= 450 && check_win2.button.y >= 390)
                    {
                        if (check_win2.button.x <= 693 && check_win2.button.x >= 370)
                        {
                            loadmixer("music//tick.wav");
                            checkmenu = 0;
                            checkwin1 = 0;
                            goto menu;
                            break;
                        }

                    }

                    if (check_win2.button.y <= 450 && check_win2.button.y >= 390)
                    {
                        if (check_win2.button.x <= 1010 && check_win2.button.x >= 710)
                        {
                            loadmixer("music//tick.wav");
                            checklevel = 3;
                            checkwin1 = 0;
                            SDL_Delay(1000);
                            goto drlv3;
                            goto pllv3;
                            break;
                        }

                    }
                }

            }
            if (checkwin1 == 0)
            {
                break;
            }
        }
        while (checklose == 2)
        {
            renderTexture(lose2, renderer, 220, 150, 830, 500);
            SDL_RenderPresent(renderer);
            if (SDL_WaitEvent(&check_lose2) == 0) continue;
            if (check_lose2.type == SDL_QUIT) break;
            if (check_lose2.type == SDL_KEYDOWN && check_lose2.key.keysym.sym == SDLK_ESCAPE) break;

            while (SDL_PollEvent(&check_lose2))
            {
                if (check_lose2.type == SDL_QUIT) return 0;
                if (check_lose2.type == SDL_MOUSEMOTION)
                {
                    if (check_lose2.button.y <= 450 && check_lose2.button.y >= 390)
                    {
                        if (check_lose2.button.x <= 693 && check_lose2.button.x >= 370)
                        {
                            renderTexture(mainmenu2, renderer, 370, 390, 323, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }

                    if (check_lose2.button.y <= 450 && check_lose2.button.y >= 390)
                    {
                        if (check_lose2.button.x <= 1010 && check_lose2.button.x >= 710)
                        {
                            renderTexture(plag2, renderer, 710, 390, 299, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }
                }
                if (check_lose2.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_lose2.button.y <= 450 && check_lose2.button.y >= 390)
                    {
                        if (check_lose2.button.x <= 693 && check_lose2.button.x >= 370)
                        {

                            checkmenu = 0;
                            checklose = 0;
                            goto menu;
                            break;
                        }

                    }

                    if (check_lose2.button.y <= 450 && check_lose2.button.y >= 390)
                    {
                        if (check_lose2.button.x <= 1010 && check_lose2.button.x >= 710)
                        {
                            checklevel = 2;
                            checklose = 0;
                            SDL_Delay(100);
                            goto drlv2;
                            goto pllv2;
                            break;
                        }

                    }
                }

            }
            if (checklose == 0)
            {
                break;
            }
        }
// ---------------- xử lý sự kiện trong giao diện win level 3 ------------
        while (checkwin1 == 3)
        {
            renderTexture(winlv3, renderer, 220, 150, 830, 500);
            SDL_RenderPresent(renderer);
            if (SDL_WaitEvent(&check_winlv3) == 0) continue;
            if (check_winlv3.type == SDL_QUIT) break;
            if (check_winlv3.type == SDL_KEYDOWN && check_winlv3.key.keysym.sym == SDLK_ESCAPE) break;

            while (SDL_PollEvent(&check_winlv3))
            {
                if (check_winlv3.type == SDL_QUIT) return 0;
                if (check_winlv3.type == SDL_MOUSEMOTION)
                {
                    if (check_winlv3.button.y <= 450 && check_winlv3.button.y >= 390)
                    {
                        if (check_winlv3.button.x <= 693 && check_winlv3.button.x >= 370)
                        {
                            renderTexture(mainmenu3, renderer, 370, 390, 323, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }
                    if (check_winlv3.button.y <= 450 && check_winlv3.button.y >= 390)
                    {
                        if (check_winlv3.button.x <= 1010 && check_winlv3.button.x >= 710)
                        {
                            renderTexture(tieptuc3, renderer, 709, 390, 299, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }
                }
                if (check_winlv3.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_winlv3.button.y <= 450 && check_winlv3.button.y >= 390)
                    {
                        if (check_winlv3.button.x <= 693 && check_winlv3.button.x >= 370)
                        {
                            loadmixer("music//tick.wav");
                            checkmenu = 0;
                            checkwin1 = 0;
                            goto menu;
                            break;
                        }

                    }

                    if (check_winlv3.button.y <= 450 && check_winlv3.button.y >= 390)
                    {
                        if (check_winlv3.button.x <= 1010 && check_winlv3.button.x >= 710)
                        {
                            loadmixer("music//tick.wav");
                            checkwin1 = 0;
                            checklevel = 4;
                            SDL_Delay(1000);
                            goto drlv4;
                            goto pllv4;                            
                            break;
                        }

                    }
                }

            }
            if (checkwin1 == 0)
            {
                break;
            }
        }
        while (checklose == 3)
        {
            renderTexture(lose3, renderer, 220, 150, 830, 500);
            SDL_RenderPresent(renderer);
            if (SDL_WaitEvent(&check_lose3) == 0) continue;
            if (check_lose3.type == SDL_QUIT) break;
            if (check_lose3.type == SDL_KEYDOWN && check_lose3.key.keysym.sym == SDLK_ESCAPE) break;

            while (SDL_PollEvent(&check_lose3))
            {
                if (check_lose3.type == SDL_QUIT) return 0;
                if (check_lose3.type == SDL_MOUSEMOTION)
                {
                    if (check_lose3.button.y <= 450 && check_lose3.button.y >= 390)
                    {
                        if (check_lose3.button.x <= 693 && check_lose3.button.x >= 370)
                        {
                            renderTexture(mainmenu3, renderer, 370, 390, 323, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }

                    if (check_lose3.button.y <= 450 && check_lose3.button.y >= 390)
                    {
                        if (check_lose3.button.x <= 1010 && check_lose3.button.x >= 710)
                        {
                            renderTexture(plag3, renderer, 710, 390, 299, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }
                }
                if (check_lose3.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_lose3.button.y <= 450 && check_lose3.button.y >= 390)
                    {
                        if (check_lose3.button.x <= 693 && check_lose3.button.x >= 370)
                        {
                            loadmixer("music//tick.wav");
                            checkmenu = 0;
                            checklose = 0;
                            goto menu;
                            break;
                        }

                    }

                    if (check_lose3.button.y <= 450 && check_lose3.button.y >= 390)
                    {
                        if (check_lose3.button.x <= 1010 && check_lose3.button.x >= 710)
                        {
                            loadmixer("music//tick.wav");
                            checklevel = 3;
                            checklose = 0;
                            SDL_Delay(100);
                            goto drlv3;
                            goto pllv3;
                            break;
                        }

                    }
                }

            }
            if (checklose == 0)
            {
                break;
            }
        }

//----------------xử lý sự kiện trong giao diện win level 4-----------------
        while (checkwin1 == 4)
        {
            renderTexture(win4, renderer, 220, 150, 830, 500);
            SDL_RenderPresent(renderer);
            if (SDL_WaitEvent(&check_winlv4) == 0) continue;
            if (check_winlv4.type == SDL_QUIT) break;
            if (check_winlv4.type == SDL_KEYDOWN && check_winlv4.key.keysym.sym == SDLK_ESCAPE) break;

            while (SDL_PollEvent(&check_winlv4))
            {
                if (check_winlv4.type == SDL_QUIT) return 0;
                if (check_winlv4.type == SDL_MOUSEMOTION)
                {
                    if (check_winlv4.button.y <= 450 && check_winlv4.button.y >= 390)
                    {
                        if (check_winlv4.button.x <= 693 && check_winlv4.button.x >= 370)
                        {
                            renderTexture(mainmenu4, renderer, 370, 390, 323, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }

                    if (check_winlv4.button.y <= 450 && check_winlv4.button.y >= 390)
                    {
                        if (check_winlv4.button.x <= 1010 && check_winlv4.button.x >= 710)
                        {
                            renderTexture(tieptuc4, renderer, 700, 390, 299, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }
                }
                if (check_winlv4.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_winlv4.button.y <= 450 && check_winlv4.button.y >= 390)
                    {
                        if (check_winlv4.button.x <= 693 && check_winlv4.button.x >= 370)
                        {

                            checkmenu = 0;
                            checkwin1 = 0;
                            goto menu;
                            break;
                        }

                    }

                    if (check_winlv4.button.y <= 450 && check_winlv4.button.y >= 390)
                    {
                        if (check_winlv4.button.x <= 1010 && check_winlv4.button.x >= 710)
                        {
                            checkwin1 = 0;
                            checklevel = 5;
                            SDL_Delay(500);
                            goto drlv5;
                            goto pllv5;
                            break;
                        }

                    }
                }

            }
            if (checkwin1 == 0)
            {
                break;
            }
        }
        while (checklose == 4)
        {
            renderTexture(lose4, renderer, 220, 150, 830, 500);
            SDL_RenderPresent(renderer);
            if (SDL_WaitEvent(&check_lose4) == 0) continue;
            if (check_lose4.type == SDL_QUIT) break;
            if (check_lose4.type == SDL_KEYDOWN && check_lose4.key.keysym.sym == SDLK_ESCAPE) break;

            while (SDL_PollEvent(&check_lose4))
            {
                if (check_lose4.type == SDL_QUIT) return 0;
                if (check_lose4.type == SDL_MOUSEMOTION)
                {
                    if (check_lose4.button.y <= 450 && check_lose4.button.y >= 390)
                    {
                        if (check_lose4.button.x <= 693 && check_lose4.button.x >= 370)
                        {
                            renderTexture(mainmenu4, renderer, 370, 390, 323, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }
                    if (check_lose4.button.y <= 450 && check_lose4.button.y >= 390)
                    {
                        if (check_lose4.button.x <= 1010 && check_lose4.button.x >= 710)
                        {
                            renderTexture(plag4, renderer, 710, 390, 299, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }
                }
                if (check_lose4.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_lose4.button.y <= 450 && check_lose4.button.y >= 390)
                    {
                        if (check_lose4.button.x <= 693 && check_lose4.button.x >= 370)
                        {
                            loadmixer("music//tick.wav");
                            checkmenu = 0;
                            checklose = 0;
                            goto menu;
                            break;
                        }

                    }

                    if (check_lose4.button.y <= 450 && check_lose4.button.y >= 390)
                    {
                        if (check_lose4.button.x <= 1010 && check_lose4.button.x >= 710)
                        {
                            loadmixer("music//wav.wav");
                            checklevel = 4;
                            checklose = 0;
                            SDL_Delay(100);
                            goto drlv4;
                            goto pllv4;
                            break;
                        }

                    }
                }

            }
            if (checklose == 0)
            {
                break;
            }
        }

//---------------xử lý sự kiện trong giao diện win level 5--------------------
        while (checkwin1 == 5)
        {
            renderTexture(win5, renderer, 220, 150, 830, 500);
            SDL_RenderPresent(renderer);
            if (SDL_WaitEvent(&check_winlv5) == 0) continue;
            if (check_winlv5.type == SDL_QUIT) break;
            if (check_winlv5.type == SDL_KEYDOWN && check_winlv5.key.keysym.sym == SDLK_ESCAPE) break;

            while (SDL_PollEvent(&check_winlv5))
            {
                if (check_winlv5.type == SDL_QUIT) return 0;
                if (check_winlv5.type == SDL_MOUSEMOTION)
                {
                    if (check_winlv5.button.y <= 450 && check_winlv5.button.y >= 390)
                    {
                        if (check_winlv5.button.x <= 693 && check_winlv5.button.x >= 370)
                        {
                            renderTexture(mainmenu, renderer, 370, 390, 323, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }

                    if (check_winlv5.button.y <= 450 && check_winlv5.button.y >= 390)
                    {
                        if (check_winlv5.button.x <= 1010 && check_winlv5.button.x >= 710)
                        {
                            renderTexture(exit5, renderer, 710, 390, 299, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
                        }

                    }
                }
                if (check_winlv5.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_winlv5.button.y <= 450 && check_winlv5.button.y >= 390)
                    {
                        if (check_winlv5.button.x <= 693 && check_winlv5.button.x >= 370)
                        {
                            loadmixer("music//tick.wav");
                            checkmenu = 0;
                            checkwin1 = 0;
                            goto menu;
                            break;
                        }

                    }

                    if (check_winlv5.button.y <= 450 && check_winlv5.button.y >= 390)
                    {
                        if (check_winlv5.button.x <= 1010 && check_winlv5.button.x >= 710)
                        {
                            checkwin1 = 0;
                            checklevel = 0;
                            SDL_Delay(500);
                            check_winlv5.type = SDL_QUIT;
                            return 0;
                        }

                    }
                }

            }
            if (checkwin1 == 0)
            {
                break;
            }
        }
        while (checklose == 5)
        {
            renderTexture(gameov1, renderer, 220, 150, 830, 500);
            SDL_RenderPresent(renderer);
            if (SDL_WaitEvent(&check_lose5) == 0) continue;
            if (check_lose5.type == SDL_QUIT) break;
            if (check_lose5.type == SDL_KEYDOWN && check_lose5.key.keysym.sym == SDLK_ESCAPE) break;

            while (SDL_PollEvent(&check_lose5))
            {
                if (check_lose5.type == SDL_QUIT) return 0;
                if (check_lose5.type == SDL_MOUSEMOTION)
                {
                    if (check_lose5.button.y <= 450 && check_lose5.button.y >= 390)
                    {
                        if (check_lose5.button.x <= 693 && check_lose5.button.x >= 370)
                        {
                            renderTexture(mainmenu, renderer, 370, 390, 323, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(800);
                        }

                    }

                    if (check_lose5.button.y <= 450 && check_lose5.button.y >= 390)
                    {
                        if (check_lose5.button.x <= 1010 && check_lose5.button.x >= 710)
                        {
                            renderTexture(playag1, renderer, 710, 390, 299, 60);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(800);
                        }

                    }
                }
                if (check_lose5.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_lose5.button.y <= 450 && check_lose5.button.y >= 390)
                    {
                        if (check_lose5.button.x <= 693 && check_lose5.button.x >= 370)
                        {
                            loadmixer("music//tick.wav");
                            checkmenu = 0;
                            checklose = 0;
                            goto menu;
                            break;
                        }

                    }

                    if (check_lose5.button.y <= 450 && check_lose5.button.y >= 390)
                    {
                        if (check_lose5.button.x <= 1010 && check_lose5.button.x >= 710)
                        {
                            loadmixer("music//tick.wav");
                            checklevel = 5;
                            checklose = 0;
                            SDL_Delay(100);
                            goto drlv5;
                            goto pllv5;
                            break;
                        }

                    }
                }

            }
            if (checklose == 0)
            {
                break;
            }
        }

    //Đợi 1 phím bất kỳ trước khi đóng cửa sổ
    waitUntilKeyPressed();

    return 0;
}