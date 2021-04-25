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
   
    int checkfalselv1 = 0;
    int checktruelv1 = 0;
    int checkwin1 = 1;
    int checktruelv2 = 0;
    int checkfalselv2 = 0;

    SDL_Event mouse_lv1; // biến xử lý sự kiện trong level 1
    SDL_Event mouse_lv2; // biến xử lý sự kiện trong level 2
    SDL_Event check_win1; // xử lý sự kiện nếu thắng level 1
    SDL_Event menu_game; // biến xử lý sự kiện trong menu game
    SDL_Event choose_level; // biến xử lý sự kiện khi chọn level
    SDL_Event mouse_lv3; // biến xử lý sự kiện trong level 3
    //------------------

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
    //------------------------------------------------
    
    SDL_Texture* bgr1 = loadTexture("image//10x10lv1.bmp", renderer);
    //Nạp ảnh vào một biến texture 
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
    SDL_Texture* gameov1 = loadTexture("image//gameov1.bmp", renderer);
    SDL_Texture* knighthat = loadTexture("image//cpt1.bmp", renderer);
    SDL_Texture* win = loadTexture("image//winlv1.bmp", renderer);
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
    SDL_Texture* kunai = loadTexture("image//kunai.bmp", renderer);
    SDL_Texture* mainmenu = loadTexture("menu//mainmenu.bmp", renderer);
    SDL_Texture* tieptuc = loadTexture("menu//continue.bmp", renderer);
    //Nếu có lỗi thì giải phóng hai texture đã nạp, rồi kết thúc
    if (mainmenu == nullptr||tieptuc == nullptr ||kunai == nullptr||redheart == nullptr|| iffalsered == nullptr || movelv1 == nullptr|| movelv2 == nullptr || movelv3 == nullptr || movelv4 == nullptr|| movelv5 == nullptr ||pickstage == nullptr ||plgame == nullptr ||guide == nullptr || exit == nullptr||lose1 == nullptr || bgr2 == nullptr || knighthat1 == nullptr || win == nullptr || knighthat == nullptr || gameov1 == nullptr || bgr1 == nullptr || pickfalse == nullptr || picktrue == nullptr|| greenheart == nullptr || iffalse == nullptr || mouseexit == nullptr || mouseplg == nullptr || checkg == nullptr || guidetext == nullptr || clickbck == nullptr)
    {
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
                        loadmixer("music//tick.wav");
                        renderTexture(guidetext, renderer, 920, 187, 650, 600);
                        SDL_RenderPresent(renderer);
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
        if (checkchoose == 1 || checkmenu == 1)
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

                
            }

            if (choose_level.type == SDL_MOUSEBUTTONDOWN)
            {
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
                        renderTexture(movelv2, renderer, 262, 160, 176, 170);
                        SDL_RenderPresent(renderer);
                        checklevel = 2;
                        break;
                    }
                }
            }

        }

        if (checklevel == 1 || checklevel == 2)
        {
            checkchoose = 0;
            break;
        }
    }


    
    
//--------------------------màn chơi số 1 , được kích hoạt khi biến checklevel = 1 ----------------------------------//
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
                                        renderTexture(picktrue, renderer, 941 + 52 * i, 244 + 52 * j + j, 54, 54);
                                        SDL_RenderPresent(renderer);
                                        level1[j][i] = 0;
                                    }

                                    if (level1[j][i] == 2)
                                    {
                                        checkfalselv1++;
                                        loadmixer("music//false.wav");
                                        renderTexture(pickfalse, renderer, 941 + 52 * i, 244 + 52 * j + j, 54, 54);
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
                    checkwin1 = 2;
                    renderTexture(iffalse, renderer, 857, 172, 54, 54);
                    SDL_RenderPresent(renderer);                    
                    SDL_Delay(300);
                    loadmixer("music//gameover.wav");
                    checklevel = 0;
                    break;
                }


                //nếu chiến thắng
                if (checktruelv1 == 1)
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
            if (checktruelv1 == 1 || checkfalselv1 == 4)
            {
                break;
            }
        }

       
        



//-----------------------------màn chơi số 2 , được kích hoạt nếu biến checklevel = 2 -------------------------------------//
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
                                        renderTexture(picktrue, renderer, 941 + 52 * i, 244 + 52 * j + j, 54, 54);
                                        SDL_RenderPresent(renderer);
                                        level2[j][i] = 0;
                                    }

                                    if (level2[j][i] == 2)
                                    {
                                        checkfalselv2++;
                                        loadmixer("music//false.wav");
                                        renderTexture(pickfalse, renderer, 941 + 52 * i, 244 + 52 * j +j, 54, 54);
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
                    renderTexture(iffalsered, renderer, 857, 172, 54, 54);
                    SDL_RenderPresent(renderer);
                    renderTexture(lose1, renderer, 200, 180, 460, 250);
                    SDL_RenderPresent(renderer);
                    loadmixer("music//gameover.wav");
                   
                    break;
                }


                //nếu chiến thắng
                if (checktruelv2 == 1)
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
                    checkwin1 = 1;
                    renderTexture(win, renderer, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
                    SDL_RenderPresent(renderer);
                    
                    break;
                }
            }
            if (checktruelv2 == 1 || checkfalselv2 == 4)
            {
                break;
            }
        }


// --------------- xử lý sự kiện trong giao diện win level 1 ----------------

        while (checkwin1 == 1)
        {
            renderTexture(win, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_RenderPresent(renderer);
            if (SDL_WaitEvent(&check_win1) == 0) continue;
            if (check_win1.type == SDL_QUIT) break;
            if (check_win1.type == SDL_KEYDOWN && check_win1.key.keysym.sym == SDLK_ESCAPE) break;

            while (SDL_PollEvent(&check_win1))
            {
                if (check_win1.type == SDL_QUIT) return 0;                
                if (check_win1.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_win1.button.y <= 260 && check_win1.button.y >= 150)
                    {
                        if (check_win1.button.x <= 730 && check_win1.button.x >= 170)
                        {
                           
                            checkmenu = 0;
                            checkwin1 = 0;
                            goto menu;
                            break;
                        }

                    }

                    if (check_win1.button.y <= 260 && check_win1.button.y >= 151)
                    {
                        if (check_win1.button.x <= 1252 && check_win1.button.x >= 784)
                        {
                            checklevel = 2;
                            checkwin1 = 0;
                            break;
                        }

                    }
                }

            }
            cout << checkmenu << endl;
            if (checkwin1 == 0)
            {
                break;
            }
        }
    
       
    //Đợi 1 phím bất kỳ trước khi đóng cửa sổ
    waitUntilKeyPressed();

    return 0;
}