// الانتقال الى الجنب.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "الانتقال الى الجنب.h"
#include "mmsystem.h"

#include <fstream>
#include <string>
#include <windows.h>


constexpr auto MAX_LOADSTRING = 100;
#pragma comment (lib,"msimg32.lib")
#pragma comment (lib,"winmm.lib")


using namespace std;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

enum gamestate
{
    STATE_INTRO,STATE_MENU,STATE_PLAYING,STATE_SETTING, STATE_EXIT
};
gamestate currentGameState = STATE_MENU;



class my_class
{
private:
    HDC backdc = NULL;
    HBITMAP backbit = NULL;
    int windth = 10, hight = 10;

    HBITMAP the_hurts = NULL, back_row = NULL, minus_png = NULL, blus_png = NULL, start = NULL, start_ar = NULL, setting_b = NULL;
    HBITMAP  setting_b_ar = NULL, exit_b = NULL, exit_b_ar = NULL, are_you_sure = NULL, are_you_sure_ar = NULL;
    HBITMAP  yes_sure = NULL, yes_sure_ar = NULL, no_back = NULL, no_back_ar = NULL;
    HBITMAP you_will_lose = NULL, you_will_lose_ar = NULL,box_you_will_lose=NULL,box_you_will_lose_ar=NULL;
    HBITMAP change_color_blus = NULL, change_color_minus = NULL,recolor=NULL, altaj=NULL;
    HBITMAP languag_arab_bit = NULL, language_english_bit = NULL,ligo=NULL;
    int hurts_num = 5;
    bool livil_up = 1, go_to_first=false,game_over=false,shift=0,enter=0;//رفع مرحله ...وعوده اللااعب الى اول المرحله عند لمس عدو...اذا نفذت القلوب...قفز تعليمات اللعب عند بدايه اللعب...ثم بعد عرض الانترو يدخل  الى القائمه الرئيسيه
    int livils = 0;//عدد المراحل
    int enemys_num =1, new_enemys_place = 150;
    int space = 0;
    struct enemys_inf
    {
        int placex = 100, placey = 0, sizex = placex + 50, sizey = placey + 120,speed=4;
       
        COLORREF enemy_color = RGB(20, 100, 45);
    };
    struct the_playr
    {
        int placex = 0, placey =300 /*hight/2*/, sizex = placex + 50, sizey = placey + 50, speed = 5;
        
        int color_r = 20, color_g = 100, color_b = 100;
        COLORREF playr_color = RGB(color_r, color_g, color_b);
        bool left = 0, right = 0, up = 0, down = 0, tap = 0;

    };
    struct new_enemy
    {
        int placex1 = 0 /*= windth*/, placey1 = 0/* = 0*/, sizex1 = 0/* = windth - 10*/, sizey1 = 0  /*=10*/,speedx1=2,speedy1=1;
        int placex2=0 /*= windth*/, placey2 = 0 /*=hight*/, sizex2 = 0 /*= windth - 10*/, sizey2 = 0 /*=hight- 10*/, speedx2 = 2, speedy2 = 1;
        bool new_enemy_show = 1;
        int max_tgarb1 = 0, max_tgarb2=0;
        COLORREF new_enemy_color = RGB(100, 50, 20);

    };
    struct mover_enemy 
    {
        int placex1 = 110 /*= windth*/, placey1 = 30/* = 0*/, sizex1 = placex1+120/* = windth - 10*/, sizey1 = placey1+50  /*=10*//* speedx1 = 4*/, speedy1 = 4;
        int placex2 = 1000  /*= windth*/, placey2 = 30 /*=hight*/, sizex2 = placex2 + 120 /*= windth - 10*/, sizey2 = placey2 + 50 /*=hight- 10*//*, speedx2 = 4,*/, speedy2 = 4;
        int placex3 = 500  /*= windth*/, placey3 = 30 /*=hight*/, sizex3 = placex3 + 120 /*= windth - 10*/, sizey3 = placey3 + 50 /*=hight- 10*//*, speedx3 = 4,*/, speedy3 = 4;
       
        COLORREF new_enemy_color = RGB(255,10, 105);
    };
    struct mouse_bottom
    {
        RECT the_bottom = {};
        wstring the_text=L"";
        bool mouse_efact = 0;
    };
    struct mous_blace
    {
        int x = 0, y = 0;
    };

    struct alashom_to_back
    {
        RECT allaiebr = { 0,0,50,20 };
     
        bool activ_color = 0,actev_boton=0;
    };

    struct setting
    {
        RECT language_arabi_rect = { 640,70, 640+170, 70+90 }, language_english_rect = { 460,70, 460+170, 70+ 90 };//رسم ازرار اللغه
        bool ar_choos = 0, eng_choos = 1;
        bool ar_evact = 0, eng_evact = 0;

        RECT sound_round_up_r = { 495,216,495 + 25,216 + 25 }, sound_round_under_r = { 495, 225, 495 + 330, 225 + 8 }, sound_rectangle_r = { 230,80,230 + 100,80 + 50 };
        RECT sound_blus = { 450,210,450 + 40,210 + 40 }, sound_mainas = { 830,210,830 + 40,210 + 40 }; bool minas_activ = 0,blus_activ = 0;
        bool sound_choos = 0, sound_activ = 0,mouse_down=0;
        double audio_num = 100;//نسبه الصوت العام
        double audio_change = 3.226;//نسبه التغيير

        bool color_bluse_activ_1 = 0, color_bluse_activ_2 = 0, color_minus_activ_1 = 0, color_minus_activ_2 = 0;
        bool color_bluse_chos_1 = 0, color_bluse_chos_2 = 0, color_minus_chos_1 = 0, color_minus_chos_2 = 0;
        bool recolor_active = 0;
        int comf_color = 1;
        RECT playr_blus = { 375,355,375+40,355+40 }, playr_minus = { 485, 355,485 + 40, 355+40 };
        RECT win_blus = { 655 ,355 ,655+40,355+40 }, win_minus = { 765 ,355 ,765+40,355+40 };
        RECT recolor_rect = { 880 ,320,880 + 90, 320 + 90 };
        int  change_color = 20;
    };
   
    struct the_enemy_back_main_setting_state
    {
        int new_blace = 0;
        int blacex = 100, blacey = 10, sizex = blacex+50, sizey = blacey+120,speed=2;
      
    };

    struct exit
    {
      
        RECT close = {}, cloce_ar = {}, yes = {}, yes_ar = {};
        bool activ_close = 0,activ_close_ar=0, activ_yes = 0,activ_yes_ar=0;
        bool chos_close = 0, chos_close_ar = 0, chos_yes = 0, chos_yes_ar = 0;
        bool blockExit = 0;//حق يوم تضغط الغاء فيضغط مره ثانيه على اكسيت..وهذي تخليه مره واحده


    };
    int bottons_in_main = 3;
   
    int mouse_placex = 0, mouse_placey = 0;

    bool game_saved = 0;

    int back_win_color_r = 210, back_win_color_g = 100, back_win_color_b = 200;
    COLORREF back_color = RGB(back_win_color_r, back_win_color_g, back_win_color_b);
   
    //صنع ملف ووضع  قيمه ترو اذا انهى اللعبه لرسم تاج في النافذه الرئيسيه 
    bool game_finished = 0,tcheck_on_time_if_game_finish=1,message_one_time_show=1;
    //الثاني لعدم تكرار الحفظ وسيتم دمجه مع داله الحفض اسفل
public:

  
   

    // IUnknown methods
  


  
    enemys_inf* en_in = new enemys_inf[100];
    the_playr pl;
    new_enemy n_e;
    mover_enemy m_e;
    int the_livils = livils;
    mouse_bottom* m_b = new mouse_bottom[3];
    mous_blace mouse_place;
    alashom_to_back alashom;
    the_enemy_back_main_setting_state t_e_b[11];
    setting set;
    exit ex;


  

  





    //livils++

    //داله رسم ازرار البدايه                              ********
    void bottom_text_but() 
    {
       
        
        for (int i = 0; i < bottons_in_main; i++)
        {
            m_b[i].the_bottom = { (windth / 2) - 130,(hight / 2) - 100 + (100 * i)+27,((windth / 2) - 50) + 137,((hight / 2) - 100 + (100 * i)) + 90 };

        }
    }
//داله تغيير لون الزر عند ملامسه السهم له(بعد ان يستلم متغير ماوس الحاله)ء                     ******
    void  botton_paint_activ() const
    {

      
        HDC h[3] = { 0 };
        for (int i = 0; i < bottons_in_main; i++)
        {
            h[i] = CreateCompatibleDC(backdc);
            if(i==0)
            {
                if(m_b[i].mouse_efact)
                {
                    if (set.ar_choos)
                    {
                        SelectObject(h[i], start_ar);
                        TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 245, 70/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 541, 197, RGB(255, 255, 255));


                    }

                    if (set.eng_choos)
                    {
                        SelectObject(h[i], start);

                        TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 245, 70/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 531, 178, RGB(255, 255, 255));
                    }
                }
                else
                {
                    if (set.ar_choos)
                    {
                        SelectObject(h[i], start_ar);
                        TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 250, 80, h[i], 0, 0, 541, 189, RGB(255, 255, 255));

                    }

                    if (set.eng_choos)
                    {
                        SelectObject(h[i], start);

                        TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 250, 80, h[i], 0, 0, 531, 178, RGB(255, 255, 255));
                    }
                }

            }
            if (i == 1)
            {
                if (m_b[i].mouse_efact)
                {
                    if (set.ar_choos)
                    {
                        SelectObject(h[i], setting_b_ar);
                        TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 245, 70/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 530, 189, RGB(255, 255, 255));

                    }

                    if (set.eng_choos)
                    {
                        SelectObject(h[i], setting_b);
                        TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 245, 70/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 531, 183, RGB(255, 255, 255));
                    }
                }
                else
                {
                    if (set.ar_choos)
                    {
                        SelectObject(h[i], setting_b_ar);
                        TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 250, 80/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 530, 189, RGB(255, 255, 255));

                    }

                    if (set.eng_choos)
                    {
                        SelectObject(h[i], setting_b);
                        TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 250, 80/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 531, 183, RGB(255, 255, 255));
                    }


                }
            }
            if (i == 2)
            {
                if (m_b[i].mouse_efact)
                {

                    if (set.ar_choos)
                    {
                        if(game_saved)
                        {
                            SelectObject(h[i], you_will_lose_ar);
                            TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 245, 70/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 1680, 640, RGB(255, 255, 255));

                        }
                        else
                        {
                            SelectObject(h[i], exit_b_ar);
                            TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 245, 70/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 533, 192, RGB(255, 255, 255));

                        }

                    }

                    if (set.eng_choos)
                    {
                        if(game_saved)
                        {
                            SelectObject(h[i], you_will_lose);
                            TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 245, 70/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 1680, 640, RGB(255, 255, 255));
                        }
                        else
                        {

                            SelectObject(h[i], exit_b);
                            TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 245, 70/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 1728, 622, RGB(255, 255, 255));

                        }
                    }
                }
                else
                {
                    if (set.ar_choos)
                    {
                        if (game_saved)
                        {
                            SelectObject(h[i], you_will_lose_ar);
                            TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 250, 80/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 1680, 640, RGB(255, 255, 255));
                        }
                        else
                        {

                            SelectObject(h[i], exit_b_ar);
                            TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 250, 80/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 533, 192, RGB(255, 255, 255));

                        }

                    }

                    if (set.eng_choos)
                    {
                        if (game_saved)
                        {
                            SelectObject(h[i], you_will_lose);
                            TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 250, 80/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 1680, 640, RGB(255, 255, 255));
                        }
                        else
                        {
                            SelectObject(h[i], exit_b);
                            TransparentBlt(backdc, (windth / 2) - 130, (hight / 2) - 100 + (100 * i) + 27, 250, 80/*m_b[i].the_bottom.left, m_b[i].the_bottom.top, m_b[i].the_bottom.right, m_b[i].the_bottom.bottom*/, h[i], 0, 0, 1728, 622, RGB(255, 255, 255));

                        }
                    }

                }

            }
          DeleteDC(h[i]);
        }
        
    }
    //داله ارسال متغير (ماوس الحاله)عند ملامسته للزر /////////////////////////////////
    void mouse_activ(int mousee_placex,int mousee_placey)
    {
       
        int bottons_in_main = 3;

        for (int i = 0; i < bottons_in_main; i++)
        {
            if (PtInRect(&m_b[i].the_bottom, { mousee_placex ,mousee_placey }))
                m_b[i].mouse_efact = 1;
            else
                m_b[i].mouse_efact = 0;
        }
       


    }
    //داله مكان ضغطه الماوس ........              **************
    void mouse_botton(int mouse_placex, int mouse_placey)
    {
        mouse_place.x = mouse_placex;
        mouse_place.y = mouse_placey;

    }
    //داله الدخول الى اللعب او الاعدادات او الخروج       *************
   
    void change_the_main_state() 
    {
        if (currentGameState != STATE_MENU) return;
        if (PtInRect(&m_b[0].the_bottom, { mouse_place.x, mouse_place.y }))
        {
            if (currentGameState != STATE_PLAYING) // تجنب التكرار
            {
                StopAllMusic();
                PlayGameMusic();
                currentGameState = STATE_PLAYING;
                mouse_place = { 0, 0 };
            }
        }
        else if (PtInRect(&m_b[1].the_bottom, { mouse_place.x, mouse_place.y }))
        {
            if (currentGameState != STATE_SETTING)
            {
                currentGameState = STATE_SETTING;
                mouse_place = { 0, 0 };
            }
        }
        else if (PtInRect(&m_b[2].the_bottom, { mouse_place.x, mouse_place.y }))
        {
            if (currentGameState != STATE_EXIT && !ex.blockExit)
            {
               

                    currentGameState = STATE_EXIT;
                    
                
               
            }
        }
       
    }
     

    void save_the_game()
    {
        if (livils > 2)
            game_saved = 1;
    }

    //رسم السهم                           ***********
    void sheem_the_back_pint() const
    {
       
       
        HDC h=CreateCompatibleDC(backdc);
        SelectObject(h, back_row);
        TransparentBlt(backdc, alashom.allaiebr.left, alashom.allaiebr.top, alashom.allaiebr.right, alashom.allaiebr.bottom, h, 0, 0, 721, 589, RGB(255, 255, 255));
        DeleteDC(h);
       
    }
  
    //ارجاع قيه ان الزر انضغط                     *********       
    void sheem_actev(int mouse_placex, int mouse_placey)
    {
        if (PtInRect(&alashom.allaiebr, { mouse_placex,mouse_placey }))
        {
            alashom.actev_boton = 1;
           
        }
        else
            alashom.actev_boton = 0;


    }
    //الرجوع للخلف                *************
    void activ_back()
    {
        if (alashom.actev_boton)
        {
            StopAllMusic();           // إيقاف موسيقى اللعب
            PlayMenuMusic();          // تشغيل الخلفية مرة أخرى
            currentGameState = STATE_MENU;
            alashom.actev_boton = 0;

        }
    }






    //لون النافذه الخلفيه فقط                    *******
    void  repaint_the_back_win(PAINTSTRUCT ps) const
    {
        HBRUSH back_brush;
       
            back_brush = CreateSolidBrush(back_color);
            FillRect(backdc, &ps.rcPaint, back_brush);
            DeleteObject(back_brush);
          

       
    }

   
    


     //رسم مواقع الاعداء القيام الاول
    void  enemys_place()
    {
       
        if(livil_up)
        {
            enemys_num = (livils + 1);
           
            for (int i = 0; i < enemys_num; i++)
            {
                en_in[i].placex = 100 + (if_enemys_more_7() * i);
                en_in[i].sizex = en_in[i].placex + 50;
                en_in[i].speed = livils + 2 + i;
                en_in[i].enemy_color = RGB(20 * i + 100, 100 * 2 * i + 50, 45 + i * 3);
            }
            livil_up = 0;
        }
    }
    //اعاده رسم مواقع الاعداء القيام عند زيادتهم
    int if_enemys_more_7()
    {
        if (enemys_num <= 7)
        {
            new_enemys_place = 150;
            return 150;
        }
        if (enemys_num > 7 && enemys_num <= 10)
        {
            new_enemys_place = 120;
         

            return 120;
        }
         if (enemys_num > 10&& enemys_num <12)
        {
           
             new_enemys_place = 110;
             return 110;
        }
         if (enemys_num >= 12)
         {
           
             enemys_num = 12;
             new_enemys_place = 110;
             return 110;
         }
        
       
        return new_enemys_place;
    }
    //اقصى تقارب للجدار المتحرك
    void new_enemy_if_enemys_more_7()
    {
        if (enemys_num > 7 && enemys_num <= 10)
        {

            n_e.max_tgarb1 = (hight / 2) - 120;
            n_e.max_tgarb2 = (hight / 2) + 120;
        }
        if (enemys_num > 10 && enemys_num < 12)
        {
            n_e.max_tgarb1 = (hight / 2) - 100;
            n_e.max_tgarb2 = (hight / 2) + 100;
        }
        if (enemys_num >= 12)
        {
            n_e.max_tgarb1 = (hight / 2) - 80;
            n_e.max_tgarb2 = (hight / 2) + 80;
        }
    }
    


    //الداله الكامله للاعداء الممددين
    void mover_enemy_show(RECT playr_rect,RECT mr1, RECT mr2, RECT mr3)
    {
        HBRUSH color1 = CreateSolidBrush(m_e.new_enemy_color), color2 = CreateSolidBrush(m_e.new_enemy_color),color3=CreateSolidBrush(m_e.new_enemy_color);
        RECT mover_enemy_rect1 = { m_e.placex1, m_e.placey1, m_e.sizex1, m_e.sizey1 }, mover_enemy_rect2 = { m_e.placex2, m_e.placey2, m_e.sizex2, m_e.sizey2 }, mover_enemy_rect3 = { m_e.placex3, m_e.placey3, m_e.sizex3, m_e.sizey3 };

        if((livils>=3&& livils <5)|| (livils >= 13 && livils < 15))
        {
            SelectObject(backdc, color1);
            Rectangle(backdc, m_e.placex1, m_e.placey1, m_e.sizex1, m_e.sizey1);
            if (IntersectRect(&mr1, &playr_rect, &mover_enemy_rect1))
            {
             //   PlaySound(MAKEINTRESOURCE(IDR_WAVE2), hInst, SND_RESOURCE | SND_ASYNC);
                go_to_first = true;
                hurts_num--;
                if (hurts_num == 0)
                {
                    game_over = true;
                }
            }
           
        }
        if ((livils >= 5 && livils < 8) || (livils >= 15 && livils < 18))
        {
            SelectObject(backdc, color1);
            Rectangle(backdc, m_e.placex1, m_e.placey1, m_e.sizex1, m_e.sizey1);
            SelectObject(backdc, color3);
            Rectangle(backdc, m_e.placex3, m_e.placey3, m_e.sizex3, m_e.sizey3);
            if (IntersectRect(&mr1, &playr_rect, &mover_enemy_rect1))
            {
               // PlaySound(MAKEINTRESOURCE(IDR_WAVE2), hInst, SND_RESOURCE | SND_ASYNC);
                go_to_first = true;
                hurts_num--;
                if (hurts_num == 0)
                {
                    game_over = true;
                }
            }
            if (IntersectRect(&mr3, &playr_rect, &mover_enemy_rect3))
            {
               // PlaySound(MAKEINTRESOURCE(IDR_WAVE2), hInst, SND_RESOURCE | SND_ASYNC);
                go_to_first = true;
                hurts_num--;
                if (hurts_num == 0)
                {
                    game_over = true;
                }
            }
        }
        if (livils >= 8 && livils < 10|| livils >= 18 && livils < 20)
        {
            SelectObject(backdc, color1);
            Rectangle(backdc, m_e.placex1, m_e.placey1, m_e.sizex1, m_e.sizey1);
            SelectObject(backdc, color3);
            Rectangle(backdc, m_e.placex3, m_e.placey3, m_e.sizex3, m_e.sizey3);
            SelectObject(backdc, color2);
            Rectangle(backdc, m_e.placex2, m_e.placey2, m_e.sizex2, m_e.sizey2);
            if (IntersectRect(&mr1, &playr_rect, &mover_enemy_rect1))
            {
              //  PlaySound(MAKEINTRESOURCE(IDR_WAVE2), hInst, SND_RESOURCE | SND_ASYNC);
                go_to_first = true;
                hurts_num--;
                if (hurts_num == 0)
                {
                    game_over = true;
                }
            }

            if (IntersectRect(&mr2, &playr_rect, &mover_enemy_rect2))
            {
               // PlaySound(MAKEINTRESOURCE(IDR_WAVE2), hInst, SND_RESOURCE | SND_ASYNC);
                go_to_first = true;
                hurts_num--;
                if (hurts_num == 0)
                {
                    game_over = true;
                }
            }

            if (IntersectRect(&mr3, &playr_rect, &mover_enemy_rect3))
            {
               // PlaySound(MAKEINTRESOURCE(IDR_WAVE2), hInst, SND_RESOURCE | SND_ASYNC);
                go_to_first = true;
                hurts_num--;
                if (hurts_num == 0)
                {
                    game_over = true;
                }
            }
        }
        DeleteObject(color1);
        DeleteObject(color2);
        DeleteObject(color3);

       
    }
  

    //رسائل ارشادات اللعب في START PLAY               ******
    void the_biginar()
    {
        if (livils == 0)
        {
            if(shift==0)
            {
                wchar_t text_hurts[80]=L"";
                if (set.eng_choos) wsprintf(text_hurts, L"PREES [SPACE] TO CONTINUE..PREES [SHIFT] TO SKIP.");
                if (set.ar_choos)wsprintf(text_hurts, L".لتخطي التعليمات [SHIFT] , للاستمار [SPACE] اظغط");
                TextOut(backdc, 400, 10, text_hurts, lstrlen(text_hurts));
                enemys_num = 0;
                if (space == 0)
                {
                    wchar_t text_hurts[100] = L"";
                    if (set.eng_choos)  wsprintf(text_hurts, L"HI MY FRIND..!");
                    if (set.ar_choos) wsprintf(text_hurts, L"!...السلام عليكم صديقي");
                    TextOut(backdc, windth / 2, hight / 2, text_hurts, lstrlen(text_hurts));

                }
                if (space == 1)
                {
                    wchar_t text_hurts[100] = L"";
                    if (set.eng_choos) wsprintf(text_hurts, L"YOU CAN MOVE BY ARROW ←↑↓→.");
                    if (set.ar_choos)wsprintf(text_hurts, L". ←↑↓→ يمكنك التحكم باللاعب بواسطه الاسهم");
                    TextOut(backdc, windth / 2, hight / 2, text_hurts, lstrlen(text_hurts));

                }
                if (space == 2)
                {
                    wchar_t text_hurts[100] = L"";
                    if (set.eng_choos)  wsprintf(text_hurts, L"PREES [TAP] TO SPEED UP.");
                    if (set.ar_choos)wsprintf(text_hurts, L". لزيادة السرعه [TAP] اظعط على زر");
                    TextOut(backdc, windth / 2, hight / 2, text_hurts, lstrlen(text_hurts));

                }
                if (space == 3)
                {
                    wchar_t text_hurts[70] = L"";
                    if (set.eng_choos)   wsprintf(text_hurts, L"LOOK DOWN AND LEFT, YOU CAN SEE YOUR HURTS.");
                    if (set.ar_choos)  wsprintf(text_hurts, L". اذا نظرت الى يسارك الاسفل سترى فرصك على شكل قلوب");
                    TextOut(backdc, 10, 300, text_hurts, lstrlen(text_hurts));

                }
                if (space == 4)
                {

                    wchar_t text_hurts[100] = L"";
                    if (set.eng_choos)  wsprintf(text_hurts, L"LOOK UP LEFT, YOU CAN SEE YOUR SCORE.");
                    if (set.ar_choos) wsprintf(text_hurts, L". واذا نظرت الى يسارك الاعلى يمكنك رؤية رقم المرحله");
                    TextOut(backdc, 10, 200, text_hurts, lstrlen(text_hurts));

                }
                if (space == 5)
                {
                    wchar_t text_hurts[100] = L"";
                    if (set.eng_choos)  wsprintf(text_hurts, L"THERE ARE YOUR ENEMY ...DONT TOUCH THIM..!");
                    if (set.ar_choos) wsprintf(text_hurts, L"!... هاؤلاء هم اعدائك ...لا انصحك بلمسهم");
                    TextOut(backdc, 220, 200, text_hurts, lstrlen(text_hurts));


                }
                if (space == 6)
                {
                    wchar_t text_hurts[100]=L"";
                    if (set.eng_choos)  wsprintf(text_hurts, L"MAKE THE SCREEN FULL TO GET BEST PERFORMANCE");
                    if (set.ar_choos) wsprintf(text_hurts, L". اجعل النافذه في وضع ملئ الشاشه للحصول على افضل اداء");
                    TextOut(backdc, windth / 2, hight / 2, text_hurts, lstrlen(text_hurts));

                }

                if (space == 7)
                {
                    wchar_t text_hurts[100] = L"";
                    if (set.eng_choos)  wsprintf(text_hurts, L"EVERE THING OK.....GOOD LUCK.");
                    if (set.ar_choos) wsprintf(text_hurts, L"! كل شيئ على ما يرام ...حظا موفقا");
                    TextOut(backdc, windth / 2, hight / 2, text_hurts, lstrlen(text_hurts));

                }
            }
        }
        if (livils == 1)
        {
            if (set.ar_choos) TextOut(backdc, windth / 2, hight / 2, L"اوه نسيت ..في حال ضغطك على سهم الرجوع سيتم حفض موقعك مالم تخرج من اللعبه", 73);
            if (set.eng_choos) TextOut(backdc, windth / 2, hight / 2, L"ah yah...if you brees a arrow to back the game will saved without exit the game.", 81);

        }
    }
    //تحرك الاعداء المنبطحين فقط داخل التايمر                        ************
    void mover_enemy_timer()
    {
        m_e.placey1 += m_e.speedy1;
        m_e.sizey1 = m_e.placey1+50;

        m_e.placey2 += m_e.speedy2;
        m_e.sizey2 = m_e.placey2 + 50;

        m_e.placey3 += m_e.speedy3;
        m_e.sizey3 = m_e.placey3 + 50;

        if (m_e.sizey1 >= hight - 30|| m_e.placey1<=30)
        {
            m_e.speedy1 = -m_e.speedy1;
        }
        if (m_e.sizey2 >= hight - 30 || m_e.placey2 <= 30)
        {
            m_e.speedy2 = -m_e.speedy2;
        }
        if (m_e.sizey3 >= hight - 30 || m_e.placey3 <= 30)
        {
            m_e.speedy3 = -m_e.speedy3;
        }
      
    }
    //داله رسم الجدران المتحركه            داخلenemy_playr_show            ***********
    void new_enemy_paint()const
    {
        if(livils>=11)
        {
            HBRUSH enemy_new_paint = CreateSolidBrush(n_e.new_enemy_color);
            SelectObject(backdc, enemy_new_paint);
            Rectangle(backdc, n_e.placex1, n_e.placey1, n_e.sizex1, n_e.sizey1);
            Rectangle(backdc, n_e.placex2, n_e.placey2, n_e.sizex2, n_e.sizey2);
            DeleteObject(enemy_new_paint);

        }
    }
    //داله حركه الجدران المتحركه
    void new_enemy_timer()
    {
      
        if (livils >= 11 )
        {/*
;*/
           
            if (n_e.new_enemy_show)
            {
                // العدو العلوي
                n_e.placex1 = windth/* - 30*/;
                n_e.placey1 = 0;
                n_e.sizex1 = windth-10;
                n_e.sizey1 = 0;

                // العدو السفلي
                n_e.placex2 = windth/* - 30*/;
                n_e.placey2 = hight/* - 10*/;
                n_e.sizex2 = windth;
                n_e.sizey2 = hight;

                n_e.new_enemy_show = 0;
            }
            if(n_e.sizex1 >0)
            {
                n_e.sizex1 -= n_e.speedx1;
                n_e.sizex2 -= n_e.speedx2;
            }
            if(n_e.sizex1 <=0)
            {
                n_e.sizex1 =0;
                n_e.sizex2 =0;
            }
            if (n_e.sizex1 <= 0)
            {
                n_e.sizey1 += n_e.speedy1;
                n_e.sizey2 -= n_e.speedy2;
            }
          
            if (n_e.sizey1 >= n_e.max_tgarb1)
            {
                n_e.sizey1 = n_e.max_tgarb1;
            }

            if (n_e.sizey2 <= n_e.max_tgarb2)
            {
                n_e.sizey2 = n_e.max_tgarb2;
            }

            if (n_e.placex1 < windth)
            {
                n_e.placex1 = windth;
           }
            if (n_e.placex2 < windth)
            {
                n_e.placex2 = windth;
            }
            if (n_e.placey1 > 0)
            {
                n_e.placex1 = 0;
            }
            if (n_e.placey2 < hight)
            {
                n_e.placey2 = hight;
            }


        }
         
     
    }
    //داله رسم اللاعب والاعداء وقتلهم والجدران وقتلهم وداخلها كل ما يتعلق بدوال الاعداء وداخلها الدوال
    void enemy_playr_show() 
    {
       
        RECT enemy_rect;
    
        if (livils >= 11)
        {
            enemys_num = livils - 5;
           
          
        }
        if (livils != 0)
        {

            for (int i = 0; i < enemys_num; i++)
            {
                HBRUSH enemy_brush = CreateSolidBrush(en_in[i].enemy_color);
                SelectObject(backdc, enemy_brush);
                Rectangle(backdc, en_in[i].placex, en_in[i].placey, en_in[i].sizex, en_in[i].sizey);
                DeleteObject(enemy_brush);

            }
            
        }
        if (livils == 0 && space == 5)
        {
            HBRUSH color = CreateSolidBrush(RGB(120, 200, 100));
            SelectObject(backdc, color);
            Rectangle(backdc, 220, 40, 220 + 50, 40 + 120);
            DeleteObject(color);
        }
       
            HBRUSH plyr_brush = CreateSolidBrush(pl.playr_color);
            SelectObject(backdc, plyr_brush);
            Rectangle(backdc, pl.placex, pl.placey, pl.sizex, pl.sizey);
            DeleteObject(plyr_brush);
            if (livils != 0)
            {
              
                   
                
                RECT playr_rect = { pl.placex, pl.placey, pl.sizex, pl.sizey };
                RECT release, r1, r2, mr1{}, mr2{}, mr3{};

               

                for (int i = 0; i < enemys_num; i++)
                {
                    enemy_rect = { en_in[i].placex,  en_in[i].placey,  en_in[i].sizex,  en_in[i].sizey };


                    if (IntersectRect(&release, &playr_rect, &enemy_rect))
                    {
                      //  PlaySound(MAKEINTRESOURCE(IDR_WAVE2), hInst,  SND_RESOURCE | SND_NOSTOP| SND_ASYNC);
                        go_to_first = true;
                        hurts_num--;
                        if (hurts_num == 0)
                        {
                            game_over = true;
                        }
                    }

                }

                RECT new_enemy_rect1 = {
            min(n_e.placex1, n_e.sizex1),
            min(n_e.placey1, n_e.sizey1),
            max(n_e.placex1, n_e.sizex1),
            max(n_e.placey1, n_e.sizey1)
                };

                RECT new_enemy_rect2 = {
                    min(n_e.placex2, n_e.sizex2),
                    min(n_e.placey2, n_e.sizey2),
                    max(n_e.placex2, n_e.sizex2),
                    max(n_e.placey2, n_e.sizey2)
                };

                if (IntersectRect(&r1, &playr_rect, &new_enemy_rect1))
                {
                   // PlaySound(MAKEINTRESOURCE(IDR_WAVE2), hInst, SND_RESOURCE | SND_ASYNC);
                    go_to_first = true;
                    hurts_num--;
                    if (hurts_num == 0)
                    {
                        game_over = true;
                    }
                }
                if (IntersectRect(&r2, &playr_rect, &new_enemy_rect2))
                {
                  //  PlaySound(MAKEINTRESOURCE(IDR_WAVE2), hInst, SND_RESOURCE | SND_ASYNC);
                    go_to_first = true;
                    hurts_num--;
                    if (hurts_num == 0)
                    {
                        game_over = true;
                    }

                   
                }
                if(livils>=3)
                {
                    mover_enemy_show(playr_rect, mr1, mr2, mr3);
                }
            }
    }
    //داله نقل محتوا الشاشه القديمه الى الجديدهDOUBLE BUFER
    void back_bitblt(HDC hdc) const
    {
        BitBlt(hdc, 0, 0, windth, hight, backdc, 0, 0, SRCCOPY);
    } 



    //داله ارتداد اللاعب والعدو القائم
    void rebound_enemys_player()
    {
        for (int i = 0; i < enemys_num; i++)
        {
            en_in[i].placey += en_in[i].speed;
            en_in[i].sizey+= en_in[i].speed;
            if (en_in[i].placey >= hight-120 || en_in[i].placey <=0)
            {
                en_in[i].speed = -en_in[i].speed;
            }
            if (en_in[i].sizey > hight )
            {
                en_in[i].placey = hight-120;
                en_in[i].sizey = en_in[i].placey + 120;

            }
            if (hight <= 120)
            {
                en_in[i].placey = 10;
                en_in[i].sizey = hight - 10;
                en_in[i].speed = 0;
               
                return;
            }
           /* if (i != 0)
               */
        }
        if (pl.placey < 0)
        {
            pl.placey = 0;
           pl.sizey= pl.placey + 50;
        }
        if (pl.sizey >hight)
        {
            pl.placey = hight-50;
            pl.sizey = pl.placey + 50;
        }
        if (pl.placex < 0)
        {
            pl.placex = 0;
            pl.sizex = pl.placex + 50;
        }
        if(windth>900)
        {
            if (pl.placex > 1230)
            {
                pl.placex = 0;
                pl.sizex = pl.placex + 50;
                livil_up = 1;
                n_e.new_enemy_show = 1;
                livils++;
                taaj_altakteem();
            }

        }
        if (windth < 900)
        {
            if (pl.placex > 900)
            {
                pl.placex = 0;
                pl.sizex = pl.placex + 50;
                livil_up = 1;
                n_e.new_enemy_show = 1;
                livils++;
                taaj_altakteem();
            }

        }
    }
    //داله اعاده اللاعب الى بدايه تلك المرحله وتنقص منه حياه
    void go_player_first()
    {
        if (go_to_first)
        {
            pl.placex = 0; pl.placey =  hight/2; pl.sizex = pl.placex + 50;pl.sizey = pl.placey + 50;
            go_to_first = false;
        }
    }
   
  //DOUBLE BUFERداله الاحجام لل                                                       *******
    void back_win_in_size(HWND hwnd,LPARAM lparam)
    {
        if (backbit) DeleteObject(backbit);
        if (backdc) DeleteDC(backdc);
        windth = LOWORD(lparam);
        hight = HIWORD(lparam);

        HDC hdc = GetDC(hwnd);
        backbit = CreateCompatibleBitmap(hdc, windth, hight);
        backdc = CreateCompatibleDC(hdc);
        SelectObject(backdc, backbit);
        ReleaseDC(hwnd, hdc);
       
    }
    //داله حذف الادوات
   


    //للقلوب والحياه************************************** BITMAPداله ال
    void bitmap_the_images()
    {
            the_hurts = LoadBitmap(hInst, MAKEINTRESOURCE(131));
            back_row = LoadBitmap(hInst, MAKEINTRESOURCE(143));
            minus_png = LoadBitmap(hInst, MAKEINTRESOURCE(148));
            blus_png = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10));
            start = LoadBitmap(hInst, MAKEINTRESOURCE(146));
            setting_b = LoadBitmap(hInst, MAKEINTRESOURCE(145));
            exit_b = LoadBitmap(hInst, MAKEINTRESOURCE(177));
            start_ar = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP12));
            setting_b_ar = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP14));
            exit_b_ar = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP13));
            are_you_sure = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP15));
            are_you_sure_ar = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP16));
            yes_sure = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP17));
            no_back= LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP18));
            yes_sure_ar = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP19));
                        no_back_ar= LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP20));
                        you_will_lose = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP21));
                        you_will_lose_ar = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP22));
                        box_you_will_lose = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP23));
                        box_you_will_lose_ar = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP24));
                        change_color_blus = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP25));
                        change_color_minus = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP26));
                        recolor = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP27));
                        altaj = LoadBitmap(hInst, MAKEINTRESOURCE(193));
                        languag_arab_bit = LoadBitmap(hInst, MAKEINTRESOURCE(195));
                        language_english_bit = LoadBitmap(hInst, MAKEINTRESOURCE(194));
                        ligo = LoadBitmap(hInst, MAKEINTRESOURCE(198));
                      



    }
    //داله رسم القلب والمربع اللي خلفها حتا تضهر القلوب بوضوح
    void hurts_in_baint()const
    {
        HBRUSH back_hurt = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(backdc,back_hurt);
        Rectangle(backdc, 85+100, hight-10,10, hight - 50);
        DeleteObject(back_hurt);
      
        for (int i = 0; i < hurts_num; i++)
        {
            HDC back_hurts = CreateCompatibleDC(backdc);
            SelectObject(back_hurts, the_hurts);

            int x = 15 + i * (28 + 5); // 127 + i*30

            TransparentBlt( backdc, x, hight - 45,33, 33, back_hurts, 0, 0,1254, 1254,RGB(255, 255, 255));

            DeleteDC(back_hurts);
        }

    }
    void distrued()const
    {
        DeleteObject(backbit);
        DeleteDC(backdc);
        DeleteObject(the_hurts);
        DeleteObject(back_row);
        DeleteObject(minus_png);
        DeleteObject(blus_png);
        DeleteObject(start);
        DeleteObject(setting_b);
        DeleteObject(exit_b);
        DeleteObject(start_ar);
        DeleteObject(setting_b_ar);
        DeleteObject(exit_b_ar);
        DeleteObject(are_you_sure);
        DeleteObject(are_you_sure_ar);
        DeleteObject(yes_sure);
        DeleteObject(no_back);
        DeleteObject(yes_sure_ar);
        DeleteObject(no_back_ar);
        DeleteObject(you_will_lose);
        DeleteObject(you_will_lose_ar);
        DeleteObject(box_you_will_lose);
        DeleteObject(box_you_will_lose_ar);
        DeleteObject(change_color_blus);
        DeleteObject(change_color_minus);
        DeleteObject(recolor);
        DeleteObject(altaj);
        DeleteObject(language_english_bit);
        DeleteObject(languag_arab_bit);
        DeleteObject(ligo);





    }
    void brint_livils()const
    {
            wchar_t text_hurts[100];
            wsprintf(text_hurts, L"livils : %d",livils);
            TextOut(backdc,60,0, text_hurts, lstrlen(text_hurts));

        
  }

   
        //داله ارسال قيمه ترو عند ظغط الازرار
    void keydown(WPARAM wpa)
    {if(currentGameState==STATE_PLAYING)
        {
            switch (wpa)
            {
            case VK_LEFT:
            {

                pl.left = 1;
            }break;
            case VK_RIGHT:
            {

                pl.right = 1;
            }break;
            case VK_UP:
            {

                pl.up = 1;
            }break;
            case VK_DOWN:
            {

                pl.down = 1;
            }break;
            case VK_TAB:
            {
                pl.speed = 10;
                pl.tap = 1;
            }break;
            case VK_SPACE:
            {
                space++;
            }break;
            case VK_SHIFT:
            {
                shift = 1;
            }break;

            }
        }
    }
    //داله تحريك اللاعب عند استلام قيمه الترو
    void in_timer_player_move()//
    {
        if (pl.left)
        {
            pl.placex -= pl.speed;
            pl.sizex = pl.placex + 50;
        }
        if (pl.right)
        {
            pl.placex += pl.speed;
            pl.sizex = pl.placex + 50;
        }
        if (pl.up)
        {
            pl.placey -= pl.speed;
            pl.sizey = pl.placey + 50;
        }
        if (pl.down)
        {
            pl.placey += pl.speed;
            pl.sizey = pl.placey + 50;
        }
    }
     //داله ارسال قيمه فولس عند رفع الزر
    void keyup(WPARAM wpa)
    {
        switch (wpa)
        {
        case VK_LEFT:
        {
            pl.left = 0;
        }break;
        case VK_RIGHT:
        {
            pl.right = 0;
        }break;
        case VK_UP:
        {
            pl.up = 0;
        }break;
        case VK_DOWN:
        {
            pl.down = 0;
        }break;
        case VK_TAB:
        {
            pl.speed = 5;
            pl.tap = 0;
        }break;
        }
    }
   //داله ارسال اللاعب الى بدايه المكان عند قتله من قبل العدو
    void game_over_end(HWND hwnd)
    {
        if (game_over)
        {
            game_over = false; // يمنع التكرار
            game_saved = 0;
           
            livils = 0;
            pl.placey = hight / 2;
            pl.speed = 0;
            StopAllMusic();
            PlayMenuMusic();
           if(set.eng_choos) MessageBoxW(hwnd, L"you are lost..brees OK to restart !", L"game over", MB_OK);
           if (set.ar_choos) MessageBoxW(hwnd, L".للاعاده OK لقد نفذت فرصك..لا تيأس..اضغط", L"game over", MB_OK);

            hurts_num = 5;
            pl.left = 0;
            pl.right = 0;
            pl.up = 0;
            pl.down = 0;

            pl.speed = 5;
          
            currentGameState = STATE_MENU;
           // KillTimer(hwnd, 1);
           
           
        }
    }



    ////////////////////////////////////////////
    //داله الاعداء اللي مالهم داعي خلف القائمه الرئيسيه والاعدادات
    void enemys_back_main_and_setting_state()
    {
        if (currentGameState != STATE_MENU && currentGameState != STATE_SETTING) return;
        int r=0, g=0, b=0;
       
        HBRUSH enemy_new_paint_in_main[11]={NULL}, playr_rectan = { NULL };
        for (int i = 0; i < 11; i++)
        {
            t_e_b[i].new_blace = 120 * i;
            int r = ((i * 31)+200) % 256;
            int g = (i * 73) % 256;
            int b = (i * 131) % 256;
            
         
            enemy_new_paint_in_main[i] = CreateSolidBrush(RGB(r,g,b));
            SelectObject(backdc, enemy_new_paint_in_main[i]);
            Rectangle(backdc, t_e_b[i].blacex+ t_e_b[i].new_blace/*+ (120 * i)*/, t_e_b[i].blacey/*+ t_e_b[i].speed*/,  t_e_b[i].sizex+ t_e_b[i].new_blace, t_e_b[i].sizey /*+ t_e_b[i].speed*/);
            DeleteObject(enemy_new_paint_in_main[i]);
           
           
           
        }
        playr_rectan = CreateSolidBrush(pl.playr_color);
        SelectObject(backdc, playr_rectan);
        Rectangle(backdc,4, 300, 54, 350);
        DeleteObject(playr_rectan);
    }
  //  حركه الاعداء الوهميين داخل التايمر
    void move_enemys_back_main_and_setting_state()
    {
        if (currentGameState != STATE_MENU && currentGameState != STATE_SETTING) return; // منع التشغيل أثناء اللعب
        for (int i = 0; i < 11; i++)
        {
          
            t_e_b[i].blacey += t_e_b[i].speed;
            t_e_b[i].sizey = /*t_e_b[i].speed +*/t_e_b[i].blacey + 120 ;
            if (t_e_b[i].blacey >= hight - 120 || t_e_b[i].blacey <= 0)
            {
                t_e_b[i].speed = -t_e_b[i].speed;
            }
            if (t_e_b[i].sizey >= hight)
            {
                t_e_b[i].blacey = hight - 120;
                t_e_b[i].sizey = t_e_b[i].blacey + 120;

            }
            if (hight <= 120)
            {
                t_e_b[i].blacey = 10;
                t_e_b[i].sizey = hight - 10;
                t_e_b[i].speed = 0;
                return ;
            }
          

       }
       
    

    }
    //تعيين سرعه الاعداء الوهميين 
    void _enemys_back_main_and_setting_state_speed()
    {
        for (int i = 0; i < 11; i++)
        {
            t_e_b[i].speed = 1 + i;
            if (t_e_b[i].speed >= 11)
            {
                t_e_b[i].speed = 11;
            }
        }
    }



    ////////////////////////////////////////////////setting    language
//فقط رسم الازرار والكتابات اللي فوقها                             *************
    void seting_language_baint() const
    {

        HDC arab_dc = CreateCompatibleDC(backdc), english_dc = CreateCompatibleDC(backdc);
        SelectObject(arab_dc, languag_arab_bit);
        SelectObject(english_dc, language_english_bit);

        ///////////////////////////////////////////english
      
       
        if (set.eng_evact || set.eng_choos)
           
            TransparentBlt(backdc, set.language_english_rect.left + 5, set.language_english_rect.top + 5,160, 80, english_dc, 0, 0, 766, 392, RGB(255, 255, 255));
        else
            TransparentBlt(backdc, set.language_english_rect.left , set.language_english_rect.top , 170 , 90 , english_dc, 0, 0, 766, 392, RGB(255, 255, 255));

     
       
        if(set.ar_evact|| set.ar_choos)
            TransparentBlt(backdc, set.language_arabi_rect.left + 5, set.language_arabi_rect.top + 5,160, 80, arab_dc, 0, 0, 754, 403, RGB(255, 255, 255));
        else
            TransparentBlt(backdc, set.language_arabi_rect.left , set.language_arabi_rect.top , 170, 90, arab_dc, 0, 0, 754, 403, RGB(255, 255, 255));

      
        if (set.ar_choos)
        TextOut(backdc, 700 + 120, 80 + 25, L".... الكثير من اللغات سوف تاتي قريبا",37);
        if (set.eng_choos)
            TextOut(backdc, 700 + 120, 80 + 25, L"more language will comeing soon .....", 38);

        DeleteDC(arab_dc);
        DeleteDC(english_dc);

      
    }
    //ارجاع حاله مكان الماوس                     **************
    void seting_language_activ_in_mouse_move(int x,int y)
    {
        if (PtInRect(&set.language_arabi_rect, { x,y }))
        {
            set.ar_evact = 1;
        }
        else
            set.ar_evact = 0;
        if (PtInRect(&set.language_english_rect, { x,y }))
        {
            set.eng_evact = 1;
        }
        else
            set.eng_evact = 0;

    }
    //ارجاع حاله الضغط بالماوس                            *****************
    void seting_language_activ_in_mouse_botton(int x, int y)
    {
        if (PtInRect(&set.language_arabi_rect, { x,y }))
        {
            set.ar_choos = 1;
            set.eng_choos = 0;
           
        }
      
        if (PtInRect(&set.language_english_rect, { x,y }))
        {
            set.eng_choos = 1;
            set.ar_choos = 0;
        }
      

    }

    //////////////////////////////////////////////////setting    sound
    //رسم مكان حق الصوت الدوائر والكلام
    void sound_paint_blace()const
    {
        if (set.eng_choos)
            TextOut(backdc, 580, 180, L"Sounds and music :", 19);
        if (set.ar_choos)
            TextOut(backdc, 580, 180, L": الصوت والموسيقى", 18);


        HBRUSH sound_round_up_br, sound_round_down_br=CreateSolidBrush(RGB(80,80,80));
        SelectObject(backdc, sound_round_down_br);
        Rectangle(backdc, 495, 225, 495 + 330, 225 + 8);//المربع اللي خلف الدائره
        if (set.sound_activ)
         sound_round_up_br = CreateSolidBrush(RGB(100, 50, 205));
        else 
            sound_round_up_br = CreateSolidBrush(RGB(150, 100, 255));

        SelectObject(backdc, sound_round_up_br);
        Ellipse(backdc, set.sound_round_up_r.left, set.sound_round_up_r.top,
            set.sound_round_up_r.right, set.sound_round_up_r.bottom);//الدائره نفسها

        HBRUSH blus,minas ;
        if(set.blus_activ)
            blus = CreateSolidBrush(RGB(100, 120, 120));
        else
            blus = CreateSolidBrush(RGB(80, 100, 160));
        if(set.minas_activ)
            minas = CreateSolidBrush(RGB(100, 120, 120));
        else
            minas = CreateSolidBrush(RGB(80, 100, 160));
        FillRect(backdc, &set.sound_blus, blus);
        FillRect(backdc, &set.sound_mainas, minas);

        HDC blus_dc = CreateCompatibleDC(backdc),minus_dc=CreateCompatibleDC(backdc);
        SelectObject(blus_dc, blus_png);
        TransparentBlt(backdc,450,210 , 40   , 40 , blus_dc, 0, 0, 880, 877, RGB(255, 255, 255));

        SelectObject(minus_dc, minus_png);
        TransparentBlt(backdc, 828, 215, 45, 30, minus_dc, 0, 0, 621, 355, RGB(255, 255, 255));

        DeleteObject(blus);
        DeleteDC(minus_dc);
        DeleteObject(minas);

        DeleteObject(sound_round_up_br);
        DeleteObject(sound_round_down_br);
        DeleteDC(blus_dc);

    }
    //داله ارجاع حاله لمس القس حق الصوت             ***************
    void sound_in_mouse_move(int x, int y)
    {
        if (PtInRect(&set.sound_round_up_r, { x,y }))
            set.sound_activ = 1;

        else
            set.sound_activ =0;
        if (PtInRect(&set.sound_blus, { x,y }))
            set.blus_activ = 1;
        else
            set.blus_activ = 0;
        if (PtInRect(&set.sound_mainas, { x,y }))
            set.minas_activ = 1;
        else
            set.minas_activ = 0;
    }
    //داله تحريك دائره عداد الصوت بارجاع قيمه ترو عند ملامسه الماوس للمؤشر والضغط عنده        ********
    void audio_bointr_move_lbotton_down(int x, int y)
    {
        if ( PtInRect(&set.sound_blus, { x,y }))
        {
            set.sound_round_up_r.left -= 10;
            set.sound_round_up_r.right -= 10;
            set.audio_num+=set.audio_change;//رفع الصوت
            if (set.audio_num >= 100)
            {
                set.audio_num = 100;
            }
            if (set.sound_round_up_r.left <= set.sound_round_under_r.left)
            {
                set.sound_round_up_r.left = set.sound_round_under_r.left;
                set.sound_round_up_r.right = set.sound_round_up_r.left + 25;
            }
        }
        if (PtInRect(&set.sound_mainas, { x,y }))
        {
            set.sound_round_up_r.left += 10;
            set.sound_round_up_r.right += 10;
            set.audio_num -= set.audio_change;//خفض الصوت
           
            if (set.audio_num <= 0)
            {
                set.audio_num = 0;
            }
            if (set.sound_round_up_r.right > set.sound_round_under_r.right)
            {
                set.sound_round_up_r.right = set.sound_round_under_r.right ;
                set.sound_round_up_r.left = set.sound_round_up_r.right - 25;
            }
        }
        SetSystemVolume();


   }
    void PlayMenuMusic()
    {
        // استخدم PlaySound مع ملف WAV مضمن كـ resource (SND_LOOP للتكرار)
       
        PlaySound(MAKEINTRESOURCE(IDR_WAVE4), hInst, SND_RESOURCE | SND_ASYNC | SND_LOOP);
    }

    void PlayGameMusic()
    {
        StopAllMusic();
        PlaySound(MAKEINTRESOURCE(IDR_WAVE3), hInst, SND_RESOURCE | SND_ASYNC | SND_LOOP);
    }

    void StopAllMusic()
    {
        PlaySound(NULL, NULL, 0);
    }

    // مستوى الصوت (0 إلى 100)
    void SetSystemVolume()const
    {
        // تحويل النسبة 0-100 إلى القيمة المطلوبة من winmm (0 - 0xFFFF)
        DWORD dwVolume = (DWORD)((set.audio_num * 0xFFFF) / 100);
        // تعيين الصوت لكل من القناتين اليمنى واليسرى
        dwVolume = (dwVolume & 0xFFFF) | (dwVolume << 16);
        waveOutSetVolume(0, dwVolume);
    }

    //رسم خيارات اللون الزياده والنقصان
    void bint_change_color()const
    {
        if (set.eng_choos) 
        {
            TextOut(backdc, 400, 330, L"PLAYER COLOR", 13);
            TextOut(backdc, 650, 330, L"BACKGROUND COLOR", 17);
        }
        if(set.ar_choos) 
        {
            TextOut(backdc, 420, 330, L"لون اللاعب", 11);
            TextOut(backdc, 704, 330, L"لون الخلفية", 12);

        }

        HBRUSH playr_box = CreateSolidBrush(pl.playr_color), back_win_box = CreateSolidBrush(back_color);
        RECT playr_rec = { 420,350,420 + 60,350 + 50 };// , back_win_rec = { 570,350,570 + 60,350 + 50 };
       // HDC back_win_dc = CreateCompatibleDC(backdc);
        FillRect(backdc, &playr_rec, playr_box);
        SelectObject(backdc, back_win_box);

        Rectangle(backdc, 700, 350, 700 + 60, 350 + 50);
       // FillRect(backdc, &back_win_rec, back_win_box);

        DeleteObject(playr_box);
        DeleteObject(back_win_box);

        HDC blus = CreateCompatibleDC(backdc), minuse = CreateCompatibleDC(backdc);
        SelectObject(blus, change_color_blus);
        SelectObject(minuse, change_color_minus);

        if (set.color_bluse_activ_1)
            TransparentBlt(backdc, set.playr_blus.left + 4, set.playr_blus.top + 4,32, 32, blus, 0, 0, 497, 498, RGB(255, 255, 255));
        else
            TransparentBlt(backdc, set.playr_blus.left, set.playr_blus.top, 40, 40, blus, 0, 0, 497, 498, RGB(255, 255, 255));


        if (set.color_minus_activ_1)
            TransparentBlt(backdc, set.playr_minus.left + 4, set.playr_minus.top + 4,32,32, minuse, 0, 0, 455, 456, RGB(255, 255, 255));
        else
            TransparentBlt(backdc, set.playr_minus.left, set.playr_minus.top, 40, 40, minuse, 0, 0, 455, 456, RGB(255, 255, 255));




        if (set.color_bluse_activ_2)
            TransparentBlt(backdc, set.win_blus.left + 4, set.win_blus.top + 4, 32, 32, blus, 0, 0, 497, 498, RGB(255, 255, 255));
        else
            TransparentBlt(backdc, set.win_blus.left, set.win_blus.top, 40, 40, blus, 0, 0, 497, 498, RGB(255, 255, 255));

        if (set.color_minus_activ_2)
            TransparentBlt(backdc, set.win_minus.left + 4, set.win_minus.top + 4, 32, 32, minuse, 0, 0, 455, 456, RGB(255, 255, 255));
        else
            TransparentBlt(backdc, set.win_minus.left, set.win_minus.top, 40, 40, minuse, 0, 0, 455, 456, RGB(255, 255, 255));


        DeleteDC(blus);
        DeleteDC(minuse);


        HDC recolor_dc = CreateCompatibleDC(backdc);
        SelectObject(recolor_dc, recolor);
       if(set.recolor_active)
           TransparentBlt(backdc, set.recolor_rect.left+4, set.recolor_rect.top+4, 82, 82, recolor_dc, 0, 0, 735, 735, RGB(255, 255, 255));
       else
           TransparentBlt(backdc, set.recolor_rect.left, set.recolor_rect.top, 90, 90, recolor_dc, 0, 0, 735, 735, RGB(255, 255, 255));

       DeleteDC(recolor_dc);
        if (set.eng_choos) TextOut(backdc, 830, 315, L"RE-SET COLORS COMFORTABLY", 26);
        if (set.ar_choos) TextOut(backdc, 830, 315, L"اعادة تعيين الالوان بشكل مريح للعين", 36);
    }
    //داله ارجاع قيمه اللمس في الالوان 
    void change_color_activ(int x, int y)
    {
        if (PtInRect(&set.playr_blus, { x,y }))
            set.color_bluse_activ_1 = 1;
        else
            set.color_bluse_activ_1 = 0;

        if (PtInRect(&set.playr_minus, { x,y }))
            set.color_minus_activ_1 = 1;
        else
            set.color_minus_activ_1 = 0;


        if (PtInRect(&set.win_blus, { x,y }))
            set.color_bluse_activ_2 = 1;
        else
            set.color_bluse_activ_2 = 0;

        if (PtInRect(&set.win_minus, { x,y }))
            set.color_minus_activ_2 = 1;
        else
            set.color_minus_activ_2 = 0;
    }
    //ارجاع قيمه الضغط
    void change_color_chos_b(int x, int y)
    { 

        if (PtInRect(&set.playr_blus, { x,y }))
        {
            pl.color_r += set.change_color;
            pl.color_g += set.change_color;
            pl.color_b += set.change_color;
            if (pl.color_r >= 255) pl.color_r = 255;
            if (pl.color_g >= 255) pl.color_g = 255;
            if (pl.color_b >= 255) pl.color_b = 255;

           
        }
       

        if (PtInRect(&set.playr_minus, { x,y }))
        {
            pl.color_r -= set.change_color;
            pl.color_g -= set.change_color;
            pl.color_b -= set.change_color;

            if (pl.color_r <= 0) pl.color_r = 0;
            if (pl.color_g <= 0) pl.color_g = 0;
            if (pl.color_b <= 0) pl.color_b = 0;
        }
       
      


        if (PtInRect(&set.win_blus, { x,y }))
        {
            back_win_color_r += set.change_color;
            back_win_color_g += set.change_color;
            back_win_color_b += set.change_color;

            if (back_win_color_r >= 255)back_win_color_r = 255;
            if (back_win_color_g >= 255)back_win_color_g = 255;
            if (back_win_color_b >= 255)back_win_color_b = 255;
        }
     

        if (PtInRect(&set.win_minus, { x,y }))
        {
            back_win_color_r -= set.change_color;
            back_win_color_g -= set.change_color;
            back_win_color_b -= set.change_color;

            if (back_win_color_r <= 0) back_win_color_r = 0;
            if (back_win_color_g <= 0) back_win_color_g = 0;
            if (back_win_color_b <= 0) back_win_color_b = 0;
        }
    
        pl.playr_color = RGB(pl.color_r, pl.color_g, pl.color_b);
        back_color = RGB(back_win_color_r, back_win_color_g, back_win_color_b);
    }
//اعاده تعيين الالوان الجيده
    void recolor_activ_fun(int x, int y)
    {
        if(PtInRect(&set.recolor_rect,{x,y}))
            set.recolor_active=1;
      
        else
            set.recolor_active = 0;

    }
    //داله تغيير الالوان المريحه للعين
    void comf_colors(int x, int y)
    {
        if (!PtInRect(&set.recolor_rect, { x, y }))
            return;
        if (PtInRect(&set.recolor_rect, { x,y }))
            set.comf_color += 1;

        if(set.comf_color >5)
            set.comf_color =1;

        if (set.comf_color == 1)
        {
            pl.color_r = 20;
            pl.color_g = 100;
            pl.color_b = 100;
            back_win_color_r = 210;
            back_win_color_g = 100;
            back_win_color_b = 200;
        }

        if (set.comf_color == 2)
        {
            pl.color_r = 45;  
            pl.color_g = 45; 
            pl.color_b = 80;
            back_win_color_r = 25;
            back_win_color_g = 25;
            back_win_color_b = 35;
        }



        if (set.comf_color == 3)
        {
            pl.color_r = 70;
            pl.color_g = 130;
            pl.color_b = 110;
            back_win_color_r = 200;
            back_win_color_g = 220;
            back_win_color_b = 210;
        }



        if (set.comf_color == 4)
        {
            pl.color_r = 90;
            pl.color_g = 100;
            pl.color_b = 150;
            back_win_color_r = 210;
            back_win_color_g = 215;
            back_win_color_b = 225;
        }
        if (set.comf_color == 5)
        {
            pl.color_r = 220;
            pl.color_g = 180;
            pl.color_b = 140; 
            back_win_color_r = 225;
            back_win_color_g = 215;
            back_win_color_b = 200;
        }

        pl.playr_color = RGB(pl.color_r, pl.color_g, pl.color_b);
        back_color = RGB(back_win_color_r, back_win_color_g, back_win_color_b);


       
    }
    //set.audio_num += set.audio_change;
   

    ////////////////////////////////////////////////////////////
    //رسم رساله هل انت متاكد
    void exit()const
    {
        HDC h=CreateCompatibleDC(backdc);
        if(game_saved)
        {
            if (set.ar_choos)
            {
                SelectObject(h, box_you_will_lose_ar);
            }
            if (set.eng_choos)
            {
                SelectObject(h, box_you_will_lose);

            }
            TransparentBlt(backdc, (windth / 2) - 300, (hight / 2) - 200, 600, 300, h, 0, 0, 1680, 640, RGB(255, 255, 255));
        }
        else
        {
            if (set.ar_choos)
            {
                SelectObject(h, are_you_sure_ar);
            }
            if (set.eng_choos)
            {
                SelectObject(h, are_you_sure);

            }
            TransparentBlt(backdc, (windth / 2) - 300, (hight / 2) - 200, 600, 300, h, 0, 0, 1680, 640, RGB(255, 255, 255));

        }
        DeleteDC(h);
    }
    //رسم ازرار التاكد والخروج....paint
    void exit_sure()const
    {
        HDC sure_dc = CreateCompatibleDC(backdc), no_sure_dc = CreateCompatibleDC(backdc);

        if (set.eng_choos)
        {
            if(ex.activ_yes)
            {
                SelectObject(sure_dc, yes_sure);

                TransparentBlt(backdc, (windth / 2) - 180, (hight / 2) + 100, 170, 80, sure_dc, 0, 0, 539, 216, RGB(255, 255, 255));

            }
            else
            {
                SelectObject(sure_dc, yes_sure);

                TransparentBlt(backdc, (windth / 2) - 190, (hight / 2) + 90, 190, 100, sure_dc, 0, 0, 539, 216, RGB(255, 255, 255));

            }
        }

        if (set.ar_choos)
        {
            if(ex.activ_yes_ar)
            {
                SelectObject(sure_dc, yes_sure_ar);
                TransparentBlt(backdc, (windth / 2)-10/* - 200*/, (hight / 2) + 100, 170, 80, sure_dc, 0, 0, 557, 234, RGB(255, 255, 255));
            }
            else
            {
                SelectObject(sure_dc, yes_sure_ar);
                TransparentBlt(backdc, (windth / 2)/* - 200*/, (hight / 2) + 90, 190, 100, sure_dc, 0, 0, 557, 234, RGB(255, 255, 255));

            }
        }
        if (set.eng_choos)
        {
            if (ex.activ_close)
            {
                SelectObject(no_sure_dc, no_back);
                TransparentBlt(backdc, (windth / 2)/* - 200*/, (hight / 2) + 100, 170, 80, no_sure_dc, 0, 0, 1615, 640, RGB(255, 255, 255));
            }
            else
            {
                SelectObject(no_sure_dc, no_back);
                TransparentBlt(backdc, (windth / 2) + 10/* - 200*/, (hight / 2) + 90, 190, 100, no_sure_dc, 0, 0, 1615, 640, RGB(255, 255, 255));

            }

        }
        if (set.ar_choos)
        {
            if (ex.activ_close_ar)
            {
                SelectObject(no_sure_dc, no_back_ar);
                TransparentBlt(backdc, (windth / 2) - 190, (hight / 2) + 105, 170, 75, no_sure_dc, 0, 0, 521, 194, RGB(255, 255, 255));
            }
            else
            {
                 SelectObject(no_sure_dc, no_back_ar);
                TransparentBlt(backdc, (windth / 2) - 200, (hight / 2) + 95, 190, 95, no_sure_dc, 0, 0, 521, 194, RGB(255, 255, 255));
          
            }

        }
        DeleteDC(sure_dc);
        DeleteDC(no_sure_dc);

    }
    //داله توضع داخل باينت لرد قيمه اماكن الازرار من اجل ريكت التفاعل.....داخل paint
    void rect_the_clse_botton()
    {
        if(set.eng_choos)
        {
            ex.close = { (windth / 2) + 10/* - 200*/, (hight / 2) + 90,  (windth / 2) + 10 + 190, (hight / 2) + 90 + 100 };
            ex.yes = { (windth / 2) - 190, (hight / 2) + 90, (windth / 2) - 190 + 190, (hight / 2) + 90 + 100 };
        }
        else
        {
            ex.close = {  };
            ex.yes = { };
        }
        if(set.ar_choos)
        {
            ex.cloce_ar = { (windth / 2) - 200, (hight / 2) + 95, (windth / 2) - 200 + 190, (hight / 2) + 95 + 95 };
            ex.yes_ar = { (windth / 2)/* - 200*/, (hight / 2) + 90, (windth / 2) + 190, (hight / 2) + 90 + 100 };
        }
        else
        {
            ex.cloce_ar = {  };
            ex.yes_ar = { };
        }
    }
    //داله ارجاع قيمه اقتراب الوشر من الازرار....mouse move
    void botton_exit_active(int x, int y)
    {
        if (PtInRect(&ex.close, { x,y })/*&& set.eng_choos*/)
        {
            ex.activ_close = 1;
        }
        else
        {
            ex.activ_close = 0;
        }
        if (PtInRect(&ex.cloce_ar, { x,y })/*&& set.ar_choos*/)
        {
            ex.activ_close_ar = 1;
        }
        else
        {
            ex.activ_close_ar = 0;
        }




        if (PtInRect(&ex.yes, { x,y })/*&& set.eng_choos*/)
        {
            ex.activ_yes = 1;
        }
        else
        {
            ex.activ_yes = 0;
        }
        if (PtInRect(&ex.yes_ar, { x,y })/*&& set.ar_choos*/)
        {
            ex.activ_yes_ar = 1;
        }
        else
        {
            ex.activ_yes_ar = 0;
        }
    }
    //داله ارجاع قيمه الاختيار 
    void botton_exit_chos(int x, int y)
    {
        mouse_place = { 0, 0 };
        if (PtInRect(&ex.close, { x,y }))
        {
            ex.chos_close = 1;

        }
        else
        {
            ex.chos_close = 0;
        }
        if (PtInRect(&ex.cloce_ar, { x,y }))
        {
            ex.chos_close_ar = 1;
        }
        else
        {
            ex.chos_close_ar = 0;
        }

        if (PtInRect(&ex.yes, { x,y }))
        {
            ex.chos_yes = 1;
        }
        else
        {
            ex.chos_yes = 0;
        }
        if (PtInRect(&ex.yes_ar, { x,y }))
        {
            ex.chos_yes_ar = 1;
        }
        else
        {
            ex.chos_yes_ar = 0;
        }
    }
    //داله استقبال الاختيار
    void botton_exit_chos(HWND h) 
    {
      
        if (ex.chos_close||ex.chos_close_ar)
        {
            ex.chos_close = 0;
            ex.chos_close_ar = 0;
         
          
            
                currentGameState = STATE_MENU;
               
            

            

          
        }
        if (ex.chos_yes || ex.chos_yes_ar)
        {
            ex.chos_yes = 0;
            ex.chos_yes_ar = 0;
            KillTimer(h, 1);
            DestroyWindow(h);
        }
       
    }
    //داله انه ما يكرر دخوله للتاكد وايكست في نفس الوقت
  
   








    ~my_class()
    {
        delete[]en_in;
        delete[]m_b;
    }


    //داله التاكد من حاله التختيم داخل wm_pint
    void taaj_altakteem()
    {
        if (livils > 15 && tcheck_on_time_if_game_finish)
        {
            ofstream finish("System Data.txt");
            if (finish.is_open()) {
                finish << "1" << endl;
                finish.close();
                tcheck_on_time_if_game_finish = 0;

            }
        }
    }
    void loadGameFinishedState()
    {
        ifstream read("System Data.txt");
        if (read.is_open())
        {
            int val;
            read >> val;
            game_finished = (val == 1);
            read.close();
        }
        else
            game_finished = 0;  // الملف غير موجود يعني اللعبة لم تختتم بعد
    }
    //رسم التاج في حاله التختيم داخل wm_timet
    void bint_taaj_altakteem()const
    {
        if (game_finished)
        {
            HDC al_taj = CreateCompatibleDC(backdc);
            SelectObject(al_taj, altaj);
            TransparentBlt(backdc, (windth / 2) - 40, (hight / 2) - 120, 75, 50, al_taj, 0, 0, 669, 362, RGB(255, 255, 255));
            DeleteDC(al_taj);
        }
    }
    void message_game_fiish(HWND h) 
    {
        if (livils > 15 && message_one_time_show)
        {
            if(set.eng_choos)
            MessageBoxW(h, L"Thanks For Playing \"Check...Run!\" Demo Stay Tuned For Full Version ❤️\nRegards from the programmer: 4D .", L"THANK YOU ❤️", MB_OK);
            if (set.ar_choos)
                MessageBoxW(h, L"ترقبوا النسخه الكامله باذن الله \"Check...Run!\"شكرا للعبك النسخة التجريبيه من لعبه\n. 4D : تحيات مطور اللعبه", L"❤️ شكرا", MB_OK);

            message_one_time_show = 0;
        }
    }


    void ligo_bint() const
    {
        HDC ligo_dc = CreateCompatibleDC(backdc);
        SelectObject(ligo_dc, ligo);
        TransparentBlt(backdc, (windth / 2) - 250,(hight/2)- 230, 490, 220, ligo_dc, 0, 0, 1702, 608, RGB(255, 255, 255));
        DeleteDC(ligo_dc);
    }

};

// تنفيذ الدوال
my_class th_cl/*=new my_class*/;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = { 0 };

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
  
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   
   th_cl.bitmap_the_images();
  
   UpdateWindow(hWnd);

  
  
  
   return 1;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  
    switch (message)
    {
    case WM_COMMAND:
        {
      
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
   
    case WM_PAINT:
        {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
            th_cl.repaint_the_back_win(ps);
            switch (currentGameState)
            {//الفيديو يتم عرضه فعليا في البرنامج بعد عرض النافذه
            case STATE_INTRO://حاله فيديو مقدمه الانترو AAA
            {
              

            }break;
            case STATE_MENU://حاله القائمه الرئيسيه
            {

               
                th_cl.enemys_back_main_and_setting_state();
                th_cl.bottom_text_but();
                th_cl.botton_paint_activ();
                th_cl.bint_taaj_altakteem();
                th_cl.ligo_bint();
            }break;
           
           
            case STATE_PLAYING://حاله بدايه اللعب عند ضغط start
            {
              
                th_cl.brint_livils();
                th_cl.the_biginar();
              
               
               
                th_cl.enemy_playr_show();
               
               th_cl.new_enemy_paint();
               
                th_cl.hurts_in_baint();
                
                th_cl.sheem_the_back_pint();
                th_cl.game_over_end(hWnd);
                  
            }break;
            case STATE_SETTING://حاله الاعدادات 
            {
                th_cl.enemys_back_main_and_setting_state();
                th_cl.seting_language_baint();
                th_cl.sheem_the_back_pint();
             
                th_cl.sound_paint_blace();
                th_cl.bint_change_color();

            }break;
            case STATE_EXIT:
            {
              
                th_cl.rect_the_clse_botton();
                th_cl.exit();
                th_cl.exit_sure();
              

            }
            break;
            }

            // TODO: Add any drawing code that uses hdc here...
            th_cl.back_bitblt(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CREATE:
    { 
        th_cl._enemys_back_main_and_setting_state_speed();
        th_cl.PlayMenuMusic();
        th_cl.loadGameFinishedState();
      
        SetTimer(hWnd, 1, 30, NULL);
      
    }break;
    case WM_SIZE:
    {
       

        th_cl.back_win_in_size(hWnd, lParam);
       
      
      
       
       
    }break;
    case WM_MOUSEMOVE:
    {
        int mouse_plcex, mouse_placey;
        mouse_placey = HIWORD(lParam);
        mouse_plcex = LOWORD(lParam);
        th_cl.mouse_activ(mouse_plcex, mouse_placey);
       

        ///////////////////////setting
        th_cl.change_color_activ(mouse_plcex, mouse_placey);

        th_cl.seting_language_activ_in_mouse_move(mouse_plcex, mouse_placey);
        th_cl. recolor_activ_fun(mouse_plcex, mouse_placey);
        th_cl.sound_in_mouse_move(mouse_plcex, mouse_placey);
        th_cl.botton_exit_active(mouse_plcex, mouse_placey);
       
    }break;
    case WM_KEYDOWN:
    {
        th_cl.keydown(wParam);
        
    }break;
    case WM_KEYUP:
    {
        th_cl.keyup(wParam);
    }break;
    case WM_LBUTTONDOWN:
    {
      

        int mouse_plcex, mouse_placey;
        mouse_placey = HIWORD(lParam);
        mouse_plcex = LOWORD(lParam);
        if(currentGameState!=STATE_EXIT)
        {
            th_cl.sheem_actev(mouse_plcex, mouse_placey);
        }
        if (currentGameState == STATE_SETTING)
        {
          
            th_cl.seting_language_activ_in_mouse_botton(mouse_plcex, mouse_placey);
            th_cl.audio_bointr_move_lbotton_down(mouse_plcex, mouse_placey);
            th_cl.comf_colors(mouse_plcex, mouse_placey);
            th_cl.change_color_chos_b(mouse_plcex, mouse_placey);
        }
        if (currentGameState == STATE_EXIT)
        {
          
            th_cl.botton_exit_chos(mouse_plcex, mouse_placey);
        }
        if (currentGameState == STATE_MENU)
        {
               
            th_cl.mouse_botton(mouse_plcex, mouse_placey);

        }
      

      
    }break;
    case WM_LBUTTONUP:
    {
    }break;
    case WM_TIMER:
    {
        
        th_cl.change_the_main_state();

        th_cl.move_enemys_back_main_and_setting_state();

       
        // باقي الكود ...
    
        th_cl.activ_back();
        th_cl.enemys_place();
        th_cl.in_timer_player_move();
        th_cl.rebound_enemys_player();
        th_cl.go_player_first();
        th_cl.if_enemys_more_7();
        th_cl.mover_enemy_timer();
        th_cl.new_enemy_if_enemys_more_7();
        th_cl.new_enemy_timer();
        th_cl.botton_exit_chos(hWnd);
        th_cl.save_the_game();
        th_cl.message_game_fiish(hWnd);
     
      
        InvalidateRect(hWnd, NULL, FALSE);
    }break;
    case WM_DESTROY:
        th_cl.StopAllMusic();

        th_cl.distrued();
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
  

    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
