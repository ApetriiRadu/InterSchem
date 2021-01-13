#include <bits/stdc++.h>

#include <stdio.h>
#include <winbgim.h>
#include <string.h>
#include <stdlib.h>

#define MAX1 40
#define MAX2 100
#define MAX3 200

using namespace std;


const int spatiuDreapta=200;
const int width=1920;
const int height=1080;
struct variabila {
    char nume;
    float val;
};

struct expresie {
    char text[MAX2];
    float val;
};

struct bloc {
    char tip;
    variabila v;
    expresie e;
    int x,y,latime,inaltime;
    bloc *urm, *urmA, *urmF;
};

void myOutTextXY(int x,int y,char *text)
{
    settextjustify(1,1);
    outtextxy(x,y+5,text);
}

bloc B[MAX3];
int nrBlocuri=0;
int r,l;
int i1,i2;/// blocurile de selectat
pair<int,int>linie[MAX3];
int page=0;
int okLinie;
int activ[MAX3];
int clickable=50;
int esc=1;

void deseneaza(bloc B, int culoare)
{
    B.inaltime=30;
    setcolor(culoare);
    circle(B.x,B.y+B.inaltime/2,5);

    char s1[MAX2], s2[MAX2];
    switch (B.tip) {
      case 's': B.latime=10+textwidth("START");
                myOutTextXY(B.x,B.y,"START");
                ellipse(B.x,B.y,0,360,B.latime,B.inaltime);
                break;
      case 't': B.latime=10+textwidth("STOP");
                myOutTextXY(B.x,B.y,"STOP");
                ellipse(B.x,B.y,0,360,B.latime,B.inaltime);
                break;
      case 'c': s2[0]=B.v.nume; s2[1]='\0';
                strcat(s2,"<-"); strcat(s2,B.e.text);
                myOutTextXY(B.x,B.y,s2);
                B.latime=10+textwidth(s2);
                rectangle(B.x-B.latime/2,B.y-B.inaltime/2,B.x+B.latime/2,B.y+B.inaltime/2);
                break;
      case 'i': s2[0]=B.v.nume; s2[1]='\0'; strcpy(s1,"citeste ");
                strcat(s1,s2); myOutTextXY(B.x,B.y,s1);
                B.latime=10+textwidth(s1);
                rectangle(B.x-B.latime/2,B.y-B.inaltime/2,B.x+B.latime/2,B.y+B.inaltime/2);
                break;
      case 'o': strcpy(s1,"afiseaza "); strcat(s1,B.e.text);
                myOutTextXY(B.x,B.y,s1); B.latime=10+textwidth(s1);
                rectangle(B.x-B.latime/2,B.y-B.inaltime/2,B.x+B.latime/2,B.y+B.inaltime/2);
                break;
      case 'd': strcpy(s1,B.e.text);
                B.latime=50+3*textwidth(s1);
                line(B.x-B.latime/2,B.y+B.inaltime/2,B.x,B.y-B.inaltime/2);
                line(B.x+B.latime/2,B.y+B.inaltime/2,B.x,B.y-B.inaltime/2);
                line(B.x-B.latime/2,B.y+B.inaltime/2,B.x+B.latime/2,B.y+B.inaltime/2);
                myOutTextXY(B.x,B.y+3,s1);
                break;
    }
}

void puneBloc(bloc& B)
{
    bool click=false;
    int xMouse,yMouse;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex(); yMouse=mousey();
            click=true; B.x=xMouse; B.y=yMouse;
            deseneaza(B,WHITE);
        }
    while (!click);
}
void selecteazaBloc(bloc& B)
{
    bool click=false;
    int xMouse,yMouse;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex(); yMouse=mousey();

            click=true; B.x=xMouse; B.y=yMouse;
            deseneaza(B,WHITE);
        }
    while (!click);
}
void refreshImage()
{
    for(int j=1; j<=nrBlocuri; j++)
        if(activ[j])
        deseneaza(B[j],WHITE);
     for(int j=1;j<=l;j++)
     {
         int i1=linie[j].first;
         int i2=linie[j].second;
         if(activ[i1]&&activ[i2] && i1>=7 && i2>=7)
         line(B[i1].x,B[i1].y,B[i2].x,B[i2].y);
     }
}

void onLeftClick()
{
    bool click2=false;
    int xMouse,yMouse;


    bool click=false;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {


            xMouse=mousex(); yMouse=mousey();


            if(xMouse<width-200)
                {
                int ok=0,da=0,backspace=0;
            for(int i=1; i<=nrBlocuri; i++)
            if(activ[i])
            {

                if(xMouse>=B[i].x-clickable && xMouse<=B[i].x+clickable && yMouse<=B[i].y+clickable && yMouse>=B[i].y-clickable)
                    while(!ismouseclick(WM_RBUTTONDOWN) && !backspace)
                    {
                        swapbuffers();
                       cleardevice();
                        da=1;
                        refreshImage();
                        B[i].x=mousex();
                        B[i].y=mousey();
                        if(GetAsyncKeyState(VK_BACK))
                        {
                            activ[i]=0;
                            backspace=1;
                        }

                    }
                clearmouseclick(WM_RBUTTONDOWN);

            }

                    clearmouseclick(WM_LBUTTONDOWN);
                    nrBlocuri++;
                    switch(r){
                case 0: B[nrBlocuri].tip='s'; break;
                case 1: B[nrBlocuri].tip='t'; break;
                case 2: B[nrBlocuri].tip='c';
                    B[nrBlocuri].v.nume='X';
                    strcpy(B[nrBlocuri].e.text,"A+B"); break;
                case 3: B[nrBlocuri].tip='i';
                    B[nrBlocuri].v.nume='X'; break;
                case 4: B[nrBlocuri].tip='o';
                    strcpy(B[nrBlocuri].e.text,"A*B-X"); break;
                case 5: B[nrBlocuri].tip='d';
                    strcpy(B[nrBlocuri].e.text,"X^2<Y+3"); break;
                }
                B[nrBlocuri].x=xMouse;
                B[nrBlocuri].y=yMouse;
                activ[nrBlocuri]=1;
                if(da)
                    nrBlocuri--;

                swapbuffers();
                cleardevice();
                refreshImage();
                swapbuffers();
                }
            else
                {

                   int x=xMouse;
                   int y=yMouse;
                   r=y/150;
                   clearmouseclick(WM_LBUTTONDOWN);
                }

            click=true;

        }
    while (!click);
}
void onRightClick()
{
    int xMouse=mousex();
    int yMouse=mousey();
    if(xMouse>width-200)
    {
        clearmouseclick(WM_RBUTTONDOWN);
        return;
    }
    if(i1==0)
    {
     for(int i=1;i<=nrBlocuri;i++)
        if(xMouse>=B[i].x-clickable && xMouse<=B[i].x+clickable && yMouse<=B[i].y+clickable && yMouse>=B[i].y-clickable)
            i1=i;
    }
    else
    {
       for(int i=1;i<=nrBlocuri;i++)
        if(xMouse>=B[i].x-clickable && xMouse<=B[i].x+clickable && yMouse<=B[i].y+clickable && yMouse>=B[i].y-clickable)
            i2=i;
       linie[++l]={i1,i2};
       i1=0;i2=0;
    }
   clearmouseclick(WM_RBUTTONDOWN);
}
void onClick()
{
    if(ismouseclick(WM_LBUTTONDOWN))
        onLeftClick();
    if(ismouseclick(WM_RBUTTONDOWN))
       onRightClick();
    if(GetAsyncKeyState(VK_ESCAPE))
        esc=0;
    swapbuffers();
    cleardevice();
    refreshImage();
    delay(1);
}

string s;
int main()
{
    cout<<"Introduceti numele fisierului. Daca nu exista, va fi creat unul nou cu acest nume: ";
    cin>>s;
    ifstream fin(s);
    if(fin)
    {


        initwindow(width,height,"InterSchem");
        fin>>nrBlocuri;
        for(int i=1;i<=nrBlocuri;i++)
        {
            string sir;
            fin>>B[i].tip;
            fin>>B[i].v.nume>>B[i].v.val;
            fin>>sir;
            for(int j=0;j<sir.size();j++)
                B[i].e.text[j]=sir[j];
            fin>>B[i].e.val;
            fin>>B[i].x>>B[i].y>>B[i].latime>>B[i].inaltime;
        }
        for(int i=1;i<=nrBlocuri;i++)
            fin>>activ[i];
        fin>>l;
        for(int i=1;i<=l;i++)
            fin>>linie[i].first>>linie[i].second;

        refreshImage();
        cout<<"exista deja";
        do {

        onClick();
        } while (esc);
    }
    else
    {
    initwindow(width,height,"InterSchem");
    int xd=1820,yd=100;
    for(int i=0;i<=5;i++)
    {
        nrBlocuri++;
        switch(r){
                case 0: B[nrBlocuri].tip='s'; break;
                case 1: B[nrBlocuri].tip='t'; break;
                case 2: B[nrBlocuri].tip='c';
                    B[nrBlocuri].v.nume='X';
                    strcpy(B[nrBlocuri].e.text,"A+B"); break;
                case 3: B[nrBlocuri].tip='i';
                    B[nrBlocuri].v.nume='X'; break;
                case 4: B[nrBlocuri].tip='o';
                    strcpy(B[nrBlocuri].e.text,"A*B-X"); break;
                case 5: B[nrBlocuri].tip='d';
                    strcpy(B[nrBlocuri].e.text,"X^2<Y+3"); break;
                }
       B[nrBlocuri].x=xd;
       B[nrBlocuri].y=yd;
       activ[nrBlocuri]=1;
       deseneaza(B[nrBlocuri],WHITE);
       r++;
       yd+=150;
    }
    r=0;

    do {

        onClick();
    } while (esc);

    }

    fin.close();
    ofstream fout(s);
    fout<<nrBlocuri<<endl;

    for(int i=1;i<=nrBlocuri;i++)
        {
            bloc o=B[i];
            fout<<o.tip<<' ';
            if(o.v.nume)
            fout<<o.v.nume;
            else
                fout<<'-';
            fout<<' '<<o.v.val<<' ';
            if(strlen(o.e.text)>0)
            fout<<o.e.text;
            else
                fout<<"none";
            fout<<' '<<o.e.val<<' ';
            fout<<o.x<<' '<<o.y<<' '<<o.latime<<' '<<o.inaltime<<' ';
            fout<<endl;
        }
    for(int i=1;i<=nrBlocuri;i++)
        fout<<activ[i]<<' ';
    fout<<endl;
    fout<<l<<endl;
    for(int i=1;i<=l;i++)
       {
           fout<<linie[i].first<<' '<<linie[i].second;
           fout<<endl;
       }
    fout.close();
    return 0;
}
