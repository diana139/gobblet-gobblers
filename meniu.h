#include <iostream>
#include <graphics.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;


void deseneazaMeniuPrincipal() {
   cleardevice();
readimagefile("poza.jpg",0, 0, getmaxx(), getmaxy());

    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);

    readimagefile("START.jpg", 200, 200, 440, 260);

    readimagefile("INSTRUCTIONS.jpg", 200, 280, 440, 340);

   readimagefile("LEAVE.jpg", 200, 360, 440, 420);

}
void cumjoci()
{
    cleardevice();
     readimagefile("logo.jpg", 120, 0, 500, 70);

    readimagefile("SINGLEPLAYER.jpg", 200, 200, 480, 260);
    readimagefile("MULTIPLAYER.jpg", 200, 280, 480, 340);
     setcolor(RED);
    rectangle(getmaxx()-100, getmaxy()-60, getmaxx(), getmaxy());
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(getmaxx()-80, getmaxy()-30, "BACK");



}
int gestioneazacumjoci()
{
int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            Beep(500, 60);

            if (x >= 200 && x <= 480 && y >= 200 && y <= 260)
                return 1;

            else if (x >= 200 && x <= 480 && y >= 280 && y <= 340)
                return 2;
                            else if(x>=getmaxx()-100 && x<=getmaxx() && y>=getmaxy()-60 && y<=getmaxy())
                return 3;

    }
}
}



void afiseazaInstrucțiuni() {

    cleardevice();
    setbkcolor(BLACK);
    setcolor(YELLOW);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
    outtextxy(320, 100, "INSTRUCTIUNI");

    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    outtextxy(50, 150, "1. Selecteaza pionul pe care doresti sa il muti.");
    outtextxy(50, 180, "2. Aseaza pionul pe o casuta goala sau peste unul mai mic.");
    outtextxy(50, 210, "3. Castiga prin alinierea a 3 piese de aceeasi culoare.");
    outtextxy(50, 240, "4. Pentru a reveni, apasa click pe unul dintre butoane.");

   // readimagefile("inapoi.png", getmaxx()-50)
    readimagefile("SINGLEPLAYER.jpg", 200, 270, 480, 330);
    readimagefile("MULTIPLAYER.jpg", 200, 350, 480, 410);
    setcolor(RED);
    rectangle(getmaxx()-100, getmaxy()-60, getmaxx(), getmaxy());
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(getmaxx()-80, getmaxy()-30, "BACK");



}

