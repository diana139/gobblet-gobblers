#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include "meniu.h"
#include <fstream>
using namespace std;
ofstream fout("castigatori.txt", ios::app);

struct piesa{
    int player;
    int dimensiune;///1-mic  2-mediu   3-mare
    bool peTabla;
    struct {
    int Ox, Oy;
    } centru;
    piesa *sub;
};

struct cell{
    int ctPiese;
    piesa *stiva;
};
int winner;
cell T[3][3];  ///TABLA DE JOC
piesa P[2][6]; ///Cei 2 PLAYERI
int nrPiesa,linie,coloana;
bool testOpt;


void deschideGrafica() {
   int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");
    //initwindow(1000, 800);
}

const int x = 150, y = 100, latura = 100;

void deseneazaCerc(int cx, int cy, int r, int culoare) {
    setcolor(culoare);
    setfillstyle(SOLID_FILL, culoare);
    fillellipse(cx, cy, r, r);
}
void deseneazaTabla() {
       for (int i = 1; i < 3; i++) {

        setcolor(GREEN);
        line(x, y + i * latura, x + 3 * latura, y + i * latura);

    }
    for (int i = 1; i< 3; i++) {
        setcolor(FOREGROUND_RED );
        line(x + i * latura, y, x + i * latura, y + 3 * latura);
    }

int idx = 0;
for(int i = 1; i <= 3; i++)
{
     deseneazaCerc(30, 50 + 65 * i, 10 * i, RED);
      P[0][idx].player = 1;
        P[0][idx].dimensiune = i*10;
        P[0][idx].peTabla = false;
        P[0][idx].sub = nullptr;
        P[0][idx].centru.Ox=30;
        P[0][idx].centru.Oy=50+65*i;
        idx++;
     deseneazaCerc(100, 50 + 65 * i, 10 * i, RED);
      P[0][idx].player = 1;
        P[0][idx].dimensiune = i*10;
        P[0][idx].peTabla = false;
        P[0][idx].sub = nullptr;
        P[0][idx].centru.Ox=100;
        P[0][idx].centru.Oy=50+65*i;
        idx++;
}
idx = 0;
for(int i = 1; i <= 3; i++)
{
     deseneazaCerc(getmaxx() - 30, 50 + 65 * i, 10 * i, GREEN);
     P[1][idx].player = 2;
        P[1][idx].dimensiune = i*10;
        P[1][idx].peTabla = false;
        P[1][idx].sub = nullptr;
        P[1][idx].centru.Ox=getmaxx()-30;
        P[1][idx].centru.Oy=50+65*i;
        idx++;

     deseneazaCerc(getmaxx() - 100, 50 + 65 * i, 10 * i, GREEN);
      P[1][idx].player = 2;
        P[1][idx].dimensiune = i*10;
        P[1][idx].peTabla = false;
        P[1][idx].sub = nullptr;
         P[1][idx].centru.Ox=getmaxx()-100;
        P[1][idx].centru.Oy=50+65*i;
        idx++;
}
}

bool esteClickInCerc(int clickX, int clickY, int centruX, int centruY, int raza) {
    int dx = clickX - centruX;
    int dy = clickY - centruY;
    return (dx * dx + dy * dy) <= (raza * raza);
}
///const int x = 150, y = 100, latura = 100;
const int DIMENSIUNE_TABLA = 3;

int tabla[DIMENSIUNE_TABLA][DIMENSIUNE_TABLA] = {0};
int centruX, centruY, raza;
bool poatePunePiesa(int linie, int coloana, int dimensiune) {
    if (T[linie][coloana].ctPiese > 0) {
        if (T[linie][coloana].stiva->dimensiune >= dimensiune) {
            return false;
        }
    }
    return true;
}

void actualizeazaTabla(int linie, int coloana, int dimensiune) {
    tabla[linie][coloana] = dimensiune;
}
bool WinCases(cell T[3][3]){
    int i;
    ///LINIE
    for(i=0;i<3;i++){
        if(T[i][0].ctPiese && T[i][1].ctPiese && T[i][2].ctPiese && T[i][0].stiva->player == T[i][1].stiva->player && T[i][0].stiva->player == T[i][2].stiva->player)
            {winner=T[i][0].stiva->player;return 1;}
    }

    ///COLOANA
    for(i=0;i<3;i++){
        if(T[0][i].ctPiese && T[1][i].ctPiese && T[2][i].ctPiese && T[0][i].stiva->player == T[1][i].stiva->player && T[0][i].stiva->player == T[2][i].stiva->player)
            {winner=T[0][i].stiva->player;return 1;}
    }

    ///DIAGONALE
    if(T[0][0].ctPiese && T[1][1].ctPiese && T[2][2].ctPiese &&T[0][0].stiva->player==T[1][1].stiva->player && T[0][0].stiva->player==T[2][2].stiva->player)
        {winner=T[0][0].stiva->player;return 1;}
    if(T[0][2].ctPiese && T[1][1].ctPiese && T[2][0].ctPiese && T[0][2].stiva->player==T[1][1].stiva->player && T[1][1].stiva->player==T[2][0].stiva->player)
        {winner=T[1][1].stiva->player;return 1;}

    return 0;
}
piesa* scoatePiesaDinStiva(int linie, int coloana) {
    if (T[linie][coloana].ctPiese > 0) {
        piesa* piesaScoasa = T[linie][coloana].stiva;
        T[linie][coloana].stiva = piesaScoasa->sub;
        T[linie][coloana].ctPiese--;

        if (T[linie][coloana].ctPiese == 0) {
            T[linie][coloana].stiva = nullptr;
        }

        return piesaScoasa;
    }
    return nullptr;
}

int castig(int a)
{
    return a;
}
string nume_player1, nume_player2;
void introduceNumeJucatori() {
    cout << "jucatorul 1 (RED): ";
    cin >> nume_player1;
    cout << "jucatorul 2 (GREEN): ";
    cin >>nume_player2;
}
void salveazaCastigatorul(int winner) {
    if (!fout.is_open()) {
        cout << "eroare" << endl;
        return;
    }

    if (winner == 1)
        fout << "Castigtor: " << nume_player1 << " (RED)" << endl;
     else if (winner == 2)
        fout << "Castigator: " << nume_player2 << " (GREEN)" << endl;

    fout.close();
}
int gestioneazaIntrariMeniu() {
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            Beep(500, 60);

            if (x >= 200 && x <= 440 && y >= 200 && y <= 260)
                return 1;

            else if (x >= 200 && x <= 440 && y >= 280 && y <= 340)
                return 2;

            else if (x >= 200 && x <= 440 && y >= 360 && y <= 420)
                return 3;

        }
    }
}
int gestioneazainstructiuni() {
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            Beep(500, 60);

            if (x >= 200 && x <= 480 && y >= 270 && y <= 330)
                return 1;

            else if (x >= 200 && x <= 480 && y >= 350 && y <= 410)
                return 2;
                else if(x>=getmaxx()-100 && x<=getmaxx() && y>=getmaxy()-60 && y<=getmaxy())
                return 3;

        }
    }
}
void reset(){
 for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            T[i][j].ctPiese = 0;
            T[i][j].stiva = nullptr;
        }
    }
}
bool esteTablaPlina() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (T[i][j].ctPiese == 0) {
                return false;
            }
        }
    }
    return true; // toate celulele au cel puțin 1 piesă
}
void gestioneazaMutari();
void mutarecalcrand();

void gestioneazaMutari()
{ bool selectat = false;
    int culoareSelectata = 0;
    int dimensiuneSelectata = 0;
    int ok=1, dim,i, idx;
    reset();
    introduceNumeJucatori();
    while (true) {
            idx;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            clearmouseclick(WM_LBUTTONDOWN);
            Beep(500, 60);
            int mouseX = mousex();
            int mouseY = mousey();
            int xanterior, yanterior;
            if (!selectat) {
                // Selectarea unui pion
                for (i = 1; i <= 3; i++) {
                    // Pioni roșii
                    if (mouseX < 150 && ok==1) {
                        centruX = (mouseX < 65) ? 30 : 100;
                        if(centruX==30)
                            idx=0;
                        else idx=1;
                        centruY = 50 + 65 * i;
                        raza = 10 * i;

                        if (esteClickInCerc(mouseX, mouseY, centruX, centruY, raza) && P[0][(i-1)*2+idx].peTabla==false) {
                            selectat = true;
                            culoareSelectata = RED;
                            dim=dimensiuneSelectata;
                            dimensiuneSelectata = 10 * i;
                            setcolor(BLACK);
                            setfillstyle(SOLID_FILL, BLACK);
                            fillellipse(centruX, centruY, raza, raza);
                            xanterior=centruX;
                            yanterior=centruY;
                            if (dimensiuneSelectata == 10 && esteTablaPlina())
                            {
                                setcolor(WHITE);
                                settextstyle(0, 0, 2);
                                outtextxy(60, 60, (char*)"Mutare imposibila!");
                                outtextxy(60, 80, (char*)"Alegeti alta piesa");
                                while (!ismouseclick(WM_LBUTTONDOWN)) {
                                }
                                clearmouseclick(WM_LBUTTONDOWN);
                                setcolor(BLACK);
                                setfillstyle(SOLID_FILL, BLACK);
                                bar(50, 50, 450, 120);
                                if (culoareSelectata == RED) {
                                    deseneazaCerc(centruX, centruY, raza, RED);
                                    P[0][(i - 1) * 2 + idx].peTabla = false;
                                }
                                else {
                                    deseneazaCerc(centruX, centruY, raza, GREEN);
                                    P[1][(i - 1) * 2 + idx].peTabla = false;
                                }
                                selectat = false;
                                break;
                            }

                            P[0][(i-1)*2+idx].peTabla=true;
                            ok=2;
                            break;
                        }
                    }
                    // Pioni verzi
                    if (mouseX > getmaxx() - 150 && ok==2) {
                        centruX = (mouseX > getmaxx() - 65) ? getmaxx() - 30 : getmaxx() - 100;
                        centruY = 50 + 65 * i;
                        if(centruX==getmaxx()-30)
                            idx=0;
                        else idx=1;
                        raza = 10 * i;

                        if (esteClickInCerc(mouseX, mouseY, centruX, centruY, raza) && P[1][(i-1)*2+idx].peTabla==false) {
                            selectat = true;
                            culoareSelectata = GREEN;
                            dimensiuneSelectata = 10 * i;
                            dim=dimensiuneSelectata;
                            setcolor(BLACK);
                            setfillstyle(SOLID_FILL, BLACK);
                            xanterior=centruX;
                            yanterior=centruY;
                            fillellipse(centruX, centruY, raza, raza);
                              if (dimensiuneSelectata == 10 && esteTablaPlina())
                            {
                                setcolor(WHITE);
                                settextstyle(0, 0, 2);
                                outtextxy(60, 60, (char*)"Mutare imposibila!");
                                outtextxy(60, 80, (char*)"Alegeti alta piesa");
                                while (!ismouseclick(WM_LBUTTONDOWN)) {
                                }
                                clearmouseclick(WM_LBUTTONDOWN);
                                setcolor(BLACK);
                                setfillstyle(SOLID_FILL, BLACK);
                                bar(50, 50, 450, 120);
                                if (culoareSelectata == RED) {
                                    deseneazaCerc(centruX, centruY, raza, RED);
                                    P[0][(i - 1) * 2 + idx].peTabla = false;
                                }
                                else {
                                    deseneazaCerc(centruX, centruY, raza, GREEN);
                                    P[1][(i - 1) * 2 + idx].peTabla = false;
                                }
                                selectat = false;
                                break;
                            }

                        ok=1;
                            P[1][(i-1)*2+idx].peTabla=true;
                            break;
                        }

                    }


                    //Pt alea de pe tabla pe care vreau sa le mut
                    if(mouseX > 150 && mouseX < getmaxx() - 150)
                    {
                        if(ok==1){

                         int linie = (mouseY - y) / latura;
                         int coloana = (mouseX - x) / latura;

                         if (T[linie][coloana].ctPiese != 0 && T[linie][coloana].stiva->player == 1) {
                            piesa* piesaSelectata = scoatePiesaDinStiva(linie, coloana);
                            if (piesaSelectata != nullptr) {
                                selectat = true;
                                culoareSelectata = RED;
                                dimensiuneSelectata = piesaSelectata->dimensiune;

                                deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2,30, BLACK);
                                 if (T[linie][coloana].ctPiese > 0){
                                        if(T[linie][coloana].stiva->player==1)
                               deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, T[linie][coloana].stiva->dimensiune,RED);
                               else if(T[linie][coloana].stiva->player==2)
                               deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, T[linie][coloana].stiva->dimensiune,GREEN);
                                 }

                                ok=2;
                                break;
    }
}

                         }
                         else if(ok==2){
                         int linie = (mouseY - y) / latura;
                         int coloana = (mouseX - x) / latura;
                         if(T[linie][coloana].ctPiese != 0 )
                         if (T[linie][coloana].ctPiese != 0 && T[linie][coloana].stiva->player == 2) {
                            piesa* piesaSelectata = scoatePiesaDinStiva(linie, coloana);
                            if (piesaSelectata != nullptr) {
                                selectat = true;
                                culoareSelectata = GREEN;
                                dimensiuneSelectata = piesaSelectata->dimensiune;

                                deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, 30, BLACK);
                                 if (T[linie][coloana].ctPiese > 0){
                                        if(T[linie][coloana].stiva->player==1)
                               deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, T[linie][coloana].stiva->dimensiune,RED);
                               else if(T[linie][coloana].stiva->player==2)
                               deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, T[linie][coloana].stiva->dimensiune,GREEN);
                                 }


                                ok=1;
                                break;
    }
}
                         }
                }


}
}            else if(selectat){
    int continua = 1;
                if  ((mouseX < 150) || (mouseX > getmaxx() - 150)) {
                        if (culoareSelectata == RED )
                                {deseneazaCerc(P[0][(i-1)*2+idx].centru.Ox, P[0][(i-1)*2+idx].centru.Oy, P[0][(i-1)*2+idx].dimensiune, RED);
                                P[0][(i-1)*2+idx].peTabla=false;
                                ok=1;
                                }

                        else if (culoareSelectata == GREEN){
                        deseneazaCerc(P[1][(i-1)*2+idx].centru.Ox, P[1][(i-1)*2+idx].centru.Oy, P[1][(i-1)*2+idx].dimensiune, GREEN);
                        P[1][(i-1)*2+idx].peTabla=false;ok=2;
                        }
                        selectat = false;
                        continua=0;

                     //   break;

}
else if (continua == 1){
                int linie = (mouseY - y) / latura;
                int coloana = (mouseX - x) / latura;

                if (linie >= 0 && linie < DIMENSIUNE_TABLA && coloana >= 0 && coloana < DIMENSIUNE_TABLA) {
                    if (poatePunePiesa(linie, coloana, dimensiuneSelectata)) {
                        centruX = x + coloana * latura + latura / 2;
                        centruY = y + linie * latura + latura / 2;


                        deseneazaCerc(centruX, centruY, dimensiuneSelectata, culoareSelectata);

                        piesa *p = new piesa;
                        p->player = (culoareSelectata == RED) ? 1 : 2;
                        p->dimensiune = dimensiuneSelectata ;
                        p->peTabla = true;
                        p->sub = T[linie][coloana].stiva;
                        T[linie][coloana].stiva = p;
                        T[linie][coloana].ctPiese++;
                        p->peTabla=1;

                        if (WinCases(T)) {

            cleardevice();
            setbkcolor(BLACK);
            readimagefile("winner.jpg", 0, 0, 200, 200);
            settextstyle(0, HORIZ_DIR, 5);

            if (winner == 1) {
                outtextxy(150, 100, (char*)nume_player1.c_str());
            } else if (winner == 2) {
                outtextxy(150, 100, (char*)nume_player2.c_str());
            }

            readimagefile("ANOTHEROUND.jpg", 200, 200, 440, 260);
            readimagefile("LEAVE.jpg", 200, 280, 440, 340);

            int optiune = 0;

            while (optiune == 0) {
                if (ismouseclick(WM_LBUTTONDOWN)) {
                    clearmouseclick(WM_LBUTTONDOWN);
                    Beep(500, 60);
                    int mx = mousex();
                    int my = mousey();
                    salveazaCastigatorul(winner);

                    if (mx >= 200 && mx <= 440 && my >= 200 && my <= 260) {
                            cumjoci();
                            int mod = gestioneazacumjoci();
                            if(mod==2)
                            {
                             cleardevice();
                             deseneazaTabla();
                             readimagefile("logo.jpg", 120, 0, 500, 70);
                             gestioneazaMutari();
                            }

                        else{
                         cleardevice();
                         deseneazaTabla();
                         readimagefile("logo.jpg", 120, 0, 500, 100);
                         srand(time(0));
                         mutarecalcrand();
                    }
                    } else if (mx >= 200 && mx <= 440 && my >= 280 && my <= 340) {
                         closegraph();
                exit(0);
                    }
                }
            }

        }

                        selectat = false;
                    }
                }
            }
}

        }
    }

}
int alegepiesa()
{

    int alespiesa=rand()%6;
    if (P[1][alespiesa].peTabla == false)
        return alespiesa;
    else return alegepiesa();
}
bool calc_are_piese()
{
    for(int i=0; i<=5; i++)
        if(P[1][i].peTabla==false)
            return true;
    return false;
}
int piese_ramase()
{
    int nr=0;
    for(int i=0; i<=5; i++)
        if(P[1][i].peTabla==false)
            nr++;
    return nr;
}

bool poatemuta()
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(T[i][j].ctPiese > 0 && T[i][j].stiva != nullptr)
                if(T[i][j].stiva->player == 2)
                    return true;
    return false;
}

void mutarecalcrand() {
    cleardevice();
    deseneazaTabla();
    readimagefile("logo.jpg", 120, 0, 500, 100);

    bool selectat = false;
    int culoareSelectata = 0;
    int dimensiuneSelectata = 0, tura=1;
    int mouseX, mouseY;
    int idx = 0;
    int centruX, centruY, raza;
    bool mutat = false;


    while (true) {
        if (tura == 1) { // Mutarea jucătorului
            if (!selectat) {
                if (ismouseclick(WM_LBUTTONDOWN)) {
                    clearmouseclick(WM_LBUTTONDOWN);
                    Beep(500, 60);
                    mouseX = mousex();
                    mouseY = mousey();

                    // Selectare piesă din zona jucătorului
                    for (int i = 1; i <= 3; i++) {
                        if (mouseX < 150) {
                            centruX = (mouseX < 65) ? 30 : 100;
                            if (centruX == 30)
                                idx = 0;
                            else
                                idx = 1;
                            centruY = 50 + 65 * i;
                            raza = 10 * i;

                            if (esteClickInCerc(mouseX, mouseY, centruX, centruY, raza) && P[0][(i-1)*2+idx].peTabla==false) {
                                selectat = true;
                                culoareSelectata = RED;
                                dimensiuneSelectata = 10 * i;
                                setcolor(BLACK);
                                setfillstyle(SOLID_FILL, BLACK);
                                fillellipse(centruX, centruY, raza, raza);
                                 if (dimensiuneSelectata == 10 && esteTablaPlina())
                            {
                                setcolor(WHITE);
                                settextstyle(0, 0, 2);
                                outtextxy(60, 60, (char*)"Mutare imposibila!");
                                outtextxy(60, 80, (char*)"Alegeti alta piesa");
                                while (!ismouseclick(WM_LBUTTONDOWN)) {
                                }
                                clearmouseclick(WM_LBUTTONDOWN);
                                setcolor(BLACK);
                                setfillstyle(SOLID_FILL, BLACK);
                                bar(50, 50, 450, 120);
                                if (culoareSelectata == RED) {
                                    deseneazaCerc(centruX, centruY, raza, RED);
                                    P[0][(i - 1) * 2 + idx].peTabla = false;
                                }
                                else {
                                    deseneazaCerc(centruX, centruY, raza, GREEN);
                                    P[1][(i - 1) * 2 + idx].peTabla = false;
                                }
                                selectat = false;
                                break;
                            }
                                 P[0][(i-1)*2+idx].peTabla=true;
                                break;
                            }

                        }


                    // Selectare piesă de pe tablă
                    else if (mouseX > 150 && mouseX < getmaxx() - 150) {
                        int linie = (mouseY - y) / latura;
                        int coloana = (mouseX - x) / latura;

                        if (T[linie][coloana].ctPiese != 0 && T[linie][coloana].stiva->player == 1) {
                            piesa* piesaSelectata = scoatePiesaDinStiva(linie, coloana);
                            if (piesaSelectata != nullptr) {
                                selectat = true;
                                culoareSelectata = RED;
                                dimensiuneSelectata = piesaSelectata->dimensiune;

                                deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, 30, BLACK);

                                if (T[linie][coloana].ctPiese > 0) {
                                    deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, T[linie][coloana].stiva->dimensiune, RED);
                                }
                              // break;
                            }
                        }
                    }
                  }
                }
            }  else{
                     if (ismouseclick(WM_LBUTTONDOWN)) {
                    clearmouseclick(WM_LBUTTONDOWN);
                    Beep(500, 60);
                    mouseX = mousex();
                    mouseY = mousey();
                    int linie = (mouseY - y) / latura;
                    int coloana = (mouseX - x) / latura;

                    if (linie >= 0 && linie < DIMENSIUNE_TABLA && coloana >= 0 && coloana < DIMENSIUNE_TABLA) {
                        if (poatePunePiesa(linie, coloana, dimensiuneSelectata)) {
                            deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, dimensiuneSelectata, culoareSelectata);

                            piesa* p = new piesa;
                            p->player = 1;
                            p->dimensiune = dimensiuneSelectata;
                            p->peTabla = true;
                            p->sub = T[linie][coloana].stiva;
                            T[linie][coloana].stiva = p;
                            T[linie][coloana].ctPiese++;
                            selectat = false;
                            tura = 2; // Schimbă la calculator
                        }
                    }
                }
            }
        }
         else if (tura == 2) { // Muta calculatorul

           // int piesacalc = alegepiesa();
            int piesacalc, schimb=1;
           // srand(time(0));
           int muta_plaseaza = rand()%2;
           if(piese_ramase()==0)
            muta_plaseaza=0;
           if(piese_ramase()==6)
            muta_plaseaza=1;
            if(muta_plaseaza==0)


            if(muta_plaseaza==0 &&  poatemuta()){ //piese_ramase() <6 &&
                    schimb=0;

                    if(poatemuta())
                while(true) {
                        linie = rand()% 3;
                        coloana = rand()% 3;
                        if( T[linie][coloana].ctPiese > 0 && T[linie][coloana].stiva != nullptr && T[linie][coloana].stiva->player==2)
                        {

                            schimb=1;
                            break;
                        }
                    }
                    else schimb=0;

                         if (T[linie][coloana].ctPiese > 0 && T[linie][coloana].stiva != nullptr && T[linie][coloana].stiva->player == 2 && schimb==1) {
                            piesa* piesaSelectata = scoatePiesaDinStiva(linie, coloana);
                            if (piesaSelectata != nullptr) {
                                selectat = true;
                                culoareSelectata = GREEN;
                                dimensiuneSelectata = piesaSelectata->dimensiune;

                                deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, 30, BLACK);
                                Beep(500, 60);
                                 if (T[linie][coloana].ctPiese > 0){
                                        if(T[linie][coloana].stiva->player==1)
                                           deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, T[linie][coloana].stiva->dimensiune,RED);
                                 else if(T[linie][coloana].stiva->player==2)
                                           deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, T[linie][coloana].stiva->dimensiune,GREEN);
                                 }

                            while(true) {

                                linie = rand()% 3;
                                coloana = rand()% 3;

                                if(poatePunePiesa(linie, coloana, dimensiuneSelectata))
                                break;
                            }

                            break;

            }
                         }

        }
        if(((calc_are_piese() && muta_plaseaza==1) || schimb==0)&& tura==2){
                        piesacalc=alegepiesa();
                        deseneazaCerc(P[1][piesacalc].centru.Ox, P[1][piesacalc].centru.Oy, P[1][piesacalc].dimensiune,BLACK);
                        Beep(500, 60);
                        while(true) {
                                linie = rand()% 3;
                                coloana = rand()% 3;

                                if(poatePunePiesa(linie, coloana, P[1][piesacalc].dimensiune))
                                    break;
                        }
                         P[1][piesacalc].peTabla=true;
                         dimensiuneSelectata=P[1][piesacalc].dimensiune;

        }

                        deseneazaCerc(x + coloana * latura + latura / 2, y + linie * latura + latura / 2, dimensiuneSelectata, GREEN);
                        Beep(500, 60);

                        piesa* p = new piesa;
                        p->player = 2;
                        p->dimensiune =dimensiuneSelectata;
                        p->peTabla = true;
                        p->sub = T[linie][coloana].stiva;
                        T[linie][coloana].stiva = p;
                        T[linie][coloana].ctPiese++;


                        tura = 1;

        }

        // Verifică dacă cineva a câștigat
        if (WinCases(T)) {
            cleardevice();
            setbkcolor(BLACK);
            readimagefile("winner.jpg", 0, 0, 200, 200);
            settextstyle(0, HORIZ_DIR, 5);

            if (winner == 1) {
                outtextxy(150, 100, "RED WINS");
            } else if (winner == 2) {
                outtextxy(150, 100, "GREEN WINS");
            }

            readimagefile("ANOTHEROUND.jpg", 200, 200, 440, 260);
            readimagefile("LEAVE.jpg", 200, 280, 440, 340);
            reset();
            int optiune = 0;
            while (optiune == 0) {
                if (ismouseclick(WM_LBUTTONDOWN)) {
                    clearmouseclick(WM_LBUTTONDOWN);
                    int mx = mousex();
                    int my = mousey();

                    if (mx >= 200 && mx <= 440 && my >= 200 && my <= 260) {
                            cumjoci();
                            int mod = gestioneazacumjoci();
                            if(mod==2)
                            {
                             cleardevice();
                             deseneazaTabla();
                             readimagefile("logo.jpg", 120, 0, 500, 70);
                             gestioneazaMutari();
                            }

                        else{
                         cleardevice();
                         deseneazaTabla();
                         readimagefile("logo.jpg", 120, 0, 500, 100);
                         srand(time(0));
                         mutarecalcrand();
                    }
                    } else if (mx >= 200 && mx <= 440 && my >= 280 && my <= 340) {
                         closegraph();
                exit(0);
                    }
                }
            }

        }
    }
}
void joc()
{
    cleardevice();
     deseneazaMeniuPrincipal();
        int optiune = gestioneazaIntrariMeniu();

        if (optiune == 1) {
                cumjoci();
                int mod = gestioneazacumjoci();
                if(mod==2)
                {
            cleardevice();
            deseneazaTabla();
             readimagefile("logo.jpg", 120, 0, 500, 70);
            gestioneazaMutari();
                }

            else if(mod==1){
            cleardevice();
            deseneazaTabla();
             readimagefile("logo.jpg", 120, 0, 500, 100);
             srand(time(0));
           mutarecalcrand();
                        }
            else joc();
        }
        else if (optiune == 2)
            {
                cleardevice();
                afiseazaInstrucțiuni();
                int alege=gestioneazainstructiuni();
                Beep(500, 60);
                if(alege==2)
                {
            cleardevice();
            deseneazaTabla();
             readimagefile("logo.jpg", 120, 0, 500, 70);
            gestioneazaMutari();
                }

            else if( alege == 1){
            cleardevice();
            deseneazaTabla();
             readimagefile("logo.jpg", 120, 0, 500, 100);
             srand(time(0));
           mutarecalcrand();
                        }
                else if(alege == 3)
                    joc();

            }

        else if (optiune == 3) {

            closegraph();
            exit(0);
        }
}

int main()
{
    if (!fout.is_open()) {
        cerr << "Eroare la deschiderea fișierului pentru salvare!" << endl;
    }
    deschideGrafica();
        deseneazaMeniuPrincipal();
        int optiune = gestioneazaIntrariMeniu();

        if (optiune == 1) {
                cumjoci();
                int mod = gestioneazacumjoci();
                if(mod==2)
                {
            cleardevice();
            deseneazaTabla();
             readimagefile("logo.jpg", 120, 0, 500, 70);
            gestioneazaMutari();
                }

            else if(mod ==1){
            cleardevice();
            deseneazaTabla();
             readimagefile("logo.jpg", 120, 0, 500, 100);
             srand(time(0));
           mutarecalcrand();
                        }
                else joc();
        }
        else if (optiune == 2)
            {
                cleardevice();
                afiseazaInstrucțiuni();
                int alege=gestioneazainstructiuni();
                Beep(500, 60);
                if(alege==2)
                {
            cleardevice();
            deseneazaTabla();
             readimagefile("logo.jpg", 120, 0, 500, 70);
            gestioneazaMutari();
                }

            else if(alege==1){
            cleardevice();
            deseneazaTabla();
             readimagefile("logo.jpg", 120, 0, 500, 100);
             srand(time(0));
           mutarecalcrand();
                        }
            else joc();

            }

        else if (optiune == 3) {

            closegraph();
            exit(0);
        }


    return 0;
}
