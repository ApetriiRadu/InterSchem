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
struct variabila
{
    char nume;
    float val;
};

struct expresie
{
    char text[MAX2];
    float val;
};

struct bloc
{
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
string s;
map<char,double>variabile;
char e[1600];
int p,i;
int eval(), t(), f();


void deseneaza(bloc B, int culoare)
{
    B.inaltime=30;
    setcolor(culoare);
    circle(B.x,B.y+B.inaltime/2,5);

    char s1[MAX2], s2[MAX2];
    switch (B.tip)
    {
    case 's':
        B.latime=10+textwidth("START");
        myOutTextXY(B.x,B.y,"START");
        ellipse(B.x,B.y,0,360,B.latime,B.inaltime);
        break;
    case 't':
        B.latime=10+textwidth("STOP");
        myOutTextXY(B.x,B.y,"STOP");
        ellipse(B.x,B.y,0,360,B.latime,B.inaltime);
        break;
    case 'c':
        s2[0]=B.v.nume;
        s2[1]='\0';
        strcat(s2,"<-");
        strcat(s2,B.e.text);
        myOutTextXY(B.x,B.y,s2);
        B.latime=10+textwidth(s2);
        rectangle(B.x-B.latime/2,B.y-B.inaltime/2,B.x+B.latime/2,B.y+B.inaltime/2);
        break;
    case 'i':
        s2[0]=B.v.nume;
        s2[1]='\0';
        strcpy(s1,"citeste ");
        strcat(s1,s2);
        myOutTextXY(B.x,B.y,s1);
        B.latime=10+textwidth(s1);
        rectangle(B.x-B.latime/2,B.y-B.inaltime/2,B.x+B.latime/2,B.y+B.inaltime/2);
        break;
    case 'o':
        strcpy(s1,"afiseaza ");
        strcat(s1,B.e.text);
        myOutTextXY(B.x,B.y,s1);
        B.latime=10+textwidth(s1);
        rectangle(B.x-B.latime/2,B.y-B.inaltime/2,B.x+B.latime/2,B.y+B.inaltime/2);
        break;
    case 'd':
        strcpy(s1,B.e.text);
        B.latime=50+3*textwidth(s1);
        line(B.x-B.latime/2,B.y+B.inaltime/2,B.x,B.y-B.inaltime/2);
        line(B.x+B.latime/2,B.y+B.inaltime/2,B.x,B.y-B.inaltime/2);
        line(B.x-B.latime/2,B.y+B.inaltime/2,B.x+B.latime/2,B.y+B.inaltime/2);
        myOutTextXY(B.x,B.y+3,s1);
        myOutTextXY(B.x-70,B.y+3,"DA");
        myOutTextXY(B.x+70,B.y+3,"NU");
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
            xMouse=mousex();
            yMouse=mousey();
            click=true;
            B.x=xMouse;
            B.y=yMouse;
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
            xMouse=mousex();
            yMouse=mousey();

            click=true;
            B.x=xMouse;
            B.y=yMouse;
            deseneaza(B,WHITE);
        }
    while (!click);
}
void refreshImage()
{
    for(int j=1; j<=nrBlocuri; j++)
        if(activ[j])
            deseneaza(B[j],WHITE);
    for(int j=1; j<=l; j++)
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


            xMouse=mousex();
            yMouse=mousey();


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
                                if(GetAsyncKeyState(VK_INSERT))
                                {
                                    if(B[i].tip=='i')
                                    {
                                        //B[i].v.nume='\0';
                                        int z=getch();
                                        if(z!=0)
                                        {
                                            char c=(char) z;
                                            B[i].v.nume=c;
                                        }
                                        else
                                        {
                                            getch();
                                        }
                                    }
                                    if(B[i].tip=='o')
                                    {
                                        int lg=-1;
                                        int ok=1;
                                        memset(B[i].e.text,0,sizeof(B[i].e.text));
                                        while(ok)
                                        {
                                        int z=getch();
                                        if(z!=0)
                                        {
                                            char c=(char) z;
                                            if(c!=VK_RETURN)
                                                B[i].e.text[++lg]=c;
                                            else
                                                ok=0;

                                        }
                                        else
                                        {
                                            getch();
                                        }
                                        }
                                    }
                                    if(B[i].tip=='c')
                                    {
                                        int lg=-1;
                                        int ok=1;
                                        int acum=-1;
                                        memset(B[i].e.text,0,sizeof(B[i].e.text));
                                        char input[50];
                                        while(ok)
                                        {
                                        int z=getch();
                                        if(z!=0)
                                        {
                                            char c=(char) z;
                                            if(c!=VK_RETURN)
                                                input[++lg]=c;
                                            else
                                                ok=0;

                                        }
                                        else
                                        {
                                            getch();
                                        }
                                        }
                                        B[i].v.nume=input[0];
                                        for(int j=2;j<=lg;j++)
                                            B[i].e.text[++acum]=input[j];
                                    }
                                    if(B[i].tip=='d')
                                    {
                                        int lg=-1;
                                        int ok=1;
                                        memset(B[i].e.text,0,sizeof(B[i].e.text));
                                        while(ok)
                                        {
                                        int z=getch();
                                        if(z!=0)
                                        {
                                            char c=(char) z;
                                            if(c!=VK_RETURN)
                                                B[i].e.text[++lg]=c;
                                            else
                                                ok=0;

                                        }
                                        else
                                        {
                                            getch();
                                        }
                                        }
                                    }
                                }

                            }
                        clearmouseclick(WM_RBUTTONDOWN);

                    }

                clearmouseclick(WM_LBUTTONDOWN);
                nrBlocuri++;
                switch(r)
                {
                case 0:
                    B[nrBlocuri].tip='s';
                    break;
                case 1:
                    B[nrBlocuri].tip='t';
                    break;
                case 2:
                    B[nrBlocuri].tip='c';
                    B[nrBlocuri].v.nume='X';
                    strcpy(B[nrBlocuri].e.text,"A+B");
                    break;
                case 3:
                    B[nrBlocuri].tip='i';
                    B[nrBlocuri].v.nume='X';
                    break;
                case 4:
                    B[nrBlocuri].tip='o';
                    strcpy(B[nrBlocuri].e.text,"A*B-X");
                    break;
                case 5:
                    B[nrBlocuri].tip='d';
                    strcpy(B[nrBlocuri].e.text,"X^2<Y+3");
                    break;
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
        for(int i=1; i<=nrBlocuri; i++)
            if(xMouse>=B[i].x-clickable && xMouse<=B[i].x+clickable && yMouse<=B[i].y+clickable && yMouse>=B[i].y-clickable)
                i1=i;
    }
    else
    {
        for(int i=1; i<=nrBlocuri; i++)
            if(xMouse>=B[i].x-clickable && xMouse<=B[i].x+clickable && yMouse<=B[i].y+clickable && yMouse>=B[i].y-clickable)
                i2=i;
        linie[++l]= {i1,i2};
        i1=0;
        i2=0;
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
vector<int>vecini[100];
int viz[100];
int dfs(int nod)
{
    viz[nod]=1;
    if(B[nod].tip=='s')
        {for(auto v:vecini[nod])
            if(!viz[v])
             return dfs(v);
        }
    else if(B[nod].tip=='t') return 0;
    else if(B[nod].tip=='i')
    {
        cout<<"Introduceti valoarea lui "<<B[nod].v.nume<<endl;
        cin>>variabile[B[nod].v.nume];
        for(auto v:vecini[nod])
            if(!viz[v])
            return dfs(v);
    }
    else if(B[nod].tip=='o')
    {
        //calculam si afisam expresia
        memset(e,0,sizeof(e));
        int lg=-1;
        for(int j=0;B[nod].e.text[j];j++)
        {
            char c=B[nod].e.text[j];
            if(!variabile[c])
            {
                e[++lg]=c;
            }
            else
            {
                stringstream ss;
                ss << variabile[c];
                string s = ss.str();
                //string s= to_string(variabile[c]);
                for(int i=0;i<s.size();i++)
                    e[++lg]=s[i];
            }
        }
        cout<<eval()<<endl;
        for(auto v:vecini[nod])
            if(!viz[v])
            return dfs(v);
    }
    else if(B[nod].tip=='c')
    {
        //facem expresia si atribuiea
         memset(e,0,sizeof(e));
        int lg=-1;
        for(int j=0;B[nod].e.text[j];j++)
        {
            char c=B[nod].e.text[j];
            if(!variabile[c])
            {
                e[++lg]=c;
            }
            else
            {
                stringstream ss;
                ss << variabile[c];
                string s = ss.str();
                //string s= to_string(variabile[c]);
                for(int i=0;i<s.size();i++)
                    e[++lg]=s[i];
            }
        }
        variabile[B[nod].v.nume]=eval();
        for(auto v:vecini[nod])
            if(!viz[v])
            return dfs(v);
    }
    return 1;
    /*else if(B[nod].tip=='d')
    {
        //calculam expresiile si facem if-ul
    }
*/

}




int eval(){
int r;
p=0;
i=0;
r= t();
while (e[p]=='-'||e[p]=='+')
{
    if (e[p]=='-')
    {
        p++;
        r-=t();
    }
    else
    {
        p++;
        r+=t();
    }
}
return r;
}
int t(){
int r=f();
while (e[p]=='*'||e[p]=='/')
{
    if (e[p]=='/')
    {
        p++;
        r/=f();
    }
    else
    {
        p++;
        r*=f();
    }
}
return r;
}

int f(){
int r=0;
if (e[p]=='(')
{
    p++;
    r=eval();
    p++;
}
else while (e[p]>='0'&&e[p]<='9')
{
    r=r*10+e[p]-'0';
    p++;
}
return r;
}

int main()
{
    ifstream fin;
    ofstream fout;

    while(1)
    {
    cout<<"Introduceti instructiunea \n";
    cin>>s;
    if(s=="edit")
    {
    cin>>s;
    //ifstream fin(s);
    fin.open(s);

    if(fin)
    {
        initwindow(width,height,"InterSchem");
        fin>>nrBlocuri;
        for(int i=1; i<=nrBlocuri; i++)
        {
            string sir;
            fin>>B[i].tip;
            fin>>B[i].v.nume>>B[i].v.val;
            fin>>sir;
            for(int j=0; j<sir.size(); j++)
                B[i].e.text[j]=sir[j];
            fin>>B[i].e.val;
            fin>>B[i].x>>B[i].y>>B[i].latime>>B[i].inaltime;
        }
        for(int i=1; i<=nrBlocuri; i++)
            fin>>activ[i];
        fin>>l;
        for(int i=1; i<=l; i++)
            fin>>linie[i].first>>linie[i].second;

        refreshImage();
        cout<<"exista deja \n";
        do
        {
            onClick();
        }
        while (esc);
    }
    else
    {
        initwindow(width,height,"InterSchem");
        int xd=1820,yd=100;
        for(int i=0; i<=5; i++)
        {
            nrBlocuri++;
            switch(r)
            {
            case 0:
                B[nrBlocuri].tip='s';
                break;
            case 1:
                B[nrBlocuri].tip='t';
                break;
            case 2:
                B[nrBlocuri].tip='c';
                B[nrBlocuri].v.nume='X';
                strcpy(B[nrBlocuri].e.text,"A+B");
                break;
            case 3:
                B[nrBlocuri].tip='i';
                B[nrBlocuri].v.nume='X';
                break;
            case 4:
                B[nrBlocuri].tip='o';
                strcpy(B[nrBlocuri].e.text,"A*B-X");
                break;
            case 5:
                B[nrBlocuri].tip='d';
                strcpy(B[nrBlocuri].e.text,"X^2<Y+3");
                break;
            }
            B[nrBlocuri].x=xd;
            B[nrBlocuri].y=yd;
            activ[nrBlocuri]=1;
            deseneaza(B[nrBlocuri],WHITE);
            r++;
            yd+=150;
        }
        r=0;

        do
        {
            onClick();
        }
        while (esc);

    }

    fin.close();
    //ofstream fout(s);
    fout.open(s);
    fout<<nrBlocuri<<endl;

    for(int i=1; i<=nrBlocuri; i++)
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
    for(int i=1; i<=nrBlocuri; i++)
        fout<<activ[i]<<' ';
    fout<<endl;
    fout<<l<<endl;
    for(int i=1; i<=l; i++)
    {
        fout<<linie[i].first<<' '<<linie[i].second;
        fout<<endl;
    }
    fout.close();
    esc=1;
    closegraph();
    }
    else
    if(s=="cpp")
    {
        cout<<"Codificare \n";
    }
    else
    if(s=="exe")
    {
        cout<<"Executare \n";
        for(int j=0;j<80;j++)
            vecini[j].clear();
        cin>>s;
        fin.open(s);
        if(fin)
        {
        fin>>nrBlocuri;
        for(int i=1; i<=nrBlocuri; i++)
        {
            string sir;
            fin>>B[i].tip;
            fin>>B[i].v.nume>>B[i].v.val;
            fin>>sir;
            for(int j=0; j<sir.size(); j++)
                B[i].e.text[j]=sir[j];
            fin>>B[i].e.val;
            fin>>B[i].x>>B[i].y>>B[i].latime>>B[i].inaltime;
        }
        for(int i=1; i<=nrBlocuri; i++)
            fin>>activ[i];
        fin>>l;
        for(int i=1; i<=l; i++)
            fin>>linie[i].first>>linie[i].second;
        fin.close();

        int start=0;
        int stop=0;
        int contor=0;
        int contor2=0;
        for(auto i:linie)
        if(activ[i.first] && activ[i.second])
        {
            vecini[i.first].push_back(i.second);
            vecini[i.second].push_back(i.first);
            if(B[i.first].tip=='s')
                start=i.first,contor++;
            else
                if(B[i.second].tip=='s')
                  start=i.second,contor++;

            if(B[i.first].tip=='t')
                stop=i.first,contor2++;
            else
                if(B[i.second].tip=='t')
                  stop=i.second,contor2++;
        }
        if(contor!=1 || contor2!=1)
        {
            cout<<"Schema invalida \n";
        }
        else
        {
            cout<<"Schema valida \n";
            memset(viz,0,sizeof(viz));
            int status=dfs(start);
            cout<<"Schema s-a executat cu statusul de return "<<status<<endl;

        }
        }
        else
        {
            cout<<"Nu exista aceasta schema \n";
        }

    }
    else
        if(s=="exit")
        {
            cout<<"Am terminat de executat! \n";
            return 0;
        }
        else
        {
            cout<<"Comanda invalida. "<<endl;
            cout<<"Verifica ReadMe pentru instructiuni \n"<<endl;
            cout<<"Pentru a iesi din program, scrie exit \n";
        }
    }
    return 0;
}
