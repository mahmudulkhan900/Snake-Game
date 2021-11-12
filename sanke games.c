#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

void gotoxy(short x, short y);
void clrscr(void);
void ret_color(void);
void setcolor(int color);
void colorfn(void);
void display_food(void);
void welcome_mesg();
void buildwalls();
void fs();
void check_hi_scores(int score);


int fdx,fdy;

main()
{
    fs();
    int rst=0;
restart:
    clrscr();
    int x,y;
    x=24;
    y=35;
    char cont;
    int snakelength=4;
    int spx[200]= {24,24,24,24,24};
    int spy[200]= {31,32,33,34,35};
    int i;

    int foodflag=0;

    int xychanged=1;
    int collisionflag=0;

    int level=0;
    int delaytime;
    delaytime=100;
    int score=0;

    char keypressed='i';
    if(rst==0)
        welcome_mesg();
    buildwalls();

    gotoxy(0,0);
    printf("\nPress q during gameplay to quit the game...\n");

    while(1)
    {

        if(foodflag==0)
        {
            display_food();

            for(i=0; i<(snakelength-1); i++)
            {
                if((spx[i]==fdx)&&(spy[i]==fdy))
                {
                    display_food();
                    break;
                }
            }
            foodflag=1;
        }

        spx[snakelength]=x;
        spy[snakelength]=y;

        if(xychanged==1)
            for(i=0; i<snakelength; i++)
            {
                spx[i]=spx[i+1];
                spy[i]=spy[i+1];
            }
        xychanged=0;

        gotoxy(x,y);
        setcolor(11);
        printf("%c",178);
        ret_color();

        gotoxy(spx[0],spy[0]);
        setcolor(0);
        printf("%c",178);
        ret_color();


        while(kbhit())
        {
            keypressed=getch();

            while(kbhit())
                keypressed=getch();
        }

        Sleep(delaytime);

        switch(keypressed)
        {
        case 72:
            xychanged=1;
            y--;
            break;

        case 75:
            xychanged=1;
            x--;
            break;

        case 80:
            xychanged=1;
            y++;
            break;

        case 77:
            xychanged=1;
            x++;
            break;

        case 'q':
        {
            gotoxy(0,0);
            printf("Are You Sure You Want to Quit (Y/N)?                        \n");
            printf("Press 'g' for New game...                                   \n");

            gotoxy(0,2);
            fflush(stdin);
            scanf("%c",&cont);
            if((cont=='y')||(cont=='Y'))
            {
                clrscr();
                check_hi_scores(score);
                printf("\nExiting\nPlease Wait...");
                Sleep(500);
                exit(1);
            }
            else if((cont=='g'))
            {
                check_hi_scores(score);
                clrscr();
                rst=1;
                goto restart;
            }
        }
        keypressed='p';
        gotoxy(0,0);
        printf("press q during gameplay to quit the game...\n                                         \n");
        break;

        default:
            break;
        }



        if((x>=73)||(x<=2)||(y>=48)||(y<=5))
            collisionflag=1;

        else
        {
            for(i=0; i<(snakelength-2); i++)
            {
                if((snakelength>5)&&(spx[i]==x)&&(spy[i]==y))
                {
                    collisionflag=1;
                    break;
                }
            }
        }

        if(collisionflag==1)

        {
            Sleep(1000);

            gotoxy(34,24);
            printf("            ");
            setcolor(10);
            gotoxy(34,24);
            printf("GAME OVER!!");
            Sleep(500);
            gotoxy(34,24);
            printf("           ");
            Sleep(500);
            gotoxy(34,24);
            printf("GAME OVER!!");
            Sleep(500);
            gotoxy(34,24);
            printf("           ");
            Sleep(500);
            gotoxy(34,24);
            printf("GAME OVER!!");
            Sleep(1000);
            clrscr();
            check_hi_scores(score);
            clrscr();
            gotoxy(1,2);
            printf("New Game?(Y/N)\n ");
            fflush(stdin);
            scanf("%c",&cont);
            if(cont=='y')
            {
                clrscr();
                ret_color();
                rst=1;
                goto restart;
            }

            else
            {
                clrscr();
                ret_color();
                printf("\nExiting...");
                Sleep(500);
                exit(1);
            }
        }

        if((fdx==x)&&(fdy==y))
        {
            foodflag=0;
            score++;
            snakelength++;
            if((score%10)==0)
            {
                level++;
                gotoxy(64,1);
                printf("LEVEL: %d",level);


                delaytime=abs(delaytime-15);
            }
            gotoxy(64,3);
            printf("SCORE: %d",score*10);


        }
    }
}




void gotoxy(short x, short y)
{

    HANDLE hConsoleOutput;
    COORD Cursor_Pos = {x, y};

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void clrscr(void)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;

    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    SetConsoleCursorPosition(hStdOut, coord);
}

void ret_color()
{
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,7);
}

void setcolor(int color)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,color);
}

void colorfn()
{
    int color;
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    srand ( time(NULL) );
    color=rand() % 10 + 5;

    SetConsoleTextAttribute(hConsole,color);
}

void display_food()
{
    int x,y;

    srand ( time(NULL) );
    x=rand() % 68+ 3;  /*2 to 73 and 5 to 48*/
    y=rand() % 40 + 6;

    fdx=x;
    fdy=y;

    gotoxy(x,y);
    colorfn();
    printf("%c",177);
    ret_color();
}

void welcome_mesg()
{
    int u;
    setcolor(10);
    for(u=1; u<=77; u++)
    {
        gotoxy(u,5);
        printf("%c",176);
        gotoxy(78-u,15);
        printf("%c",176);
        Sleep(25);
    }

    gotoxy(30,9);
    setcolor(14);
    printf("Snake Game \n");
    setcolor(11);
    gotoxy(32,11);
    printf("By Mahmudul hasan Niloy");
    ret_color();
    Sleep(1000);
    gotoxy(16,20);
    printf("Rules: Lead the Caterpillar to its food and gain Points...");
    gotoxy(16,21);
    printf("       Avoid hitting the Walls and don't eat yourself up!!");
    gotoxy(16,22);
    printf("       Level increases with increase in the points you gain");
    gotoxy(16,25);
    printf("Controls: Use Arrow Keys To Navigate");

    gotoxy(16,31);
    printf("Press any key to Start Game...");
    getch();
    clrscr();

}

void buildwalls()
{
    int wx,wy;

    setcolor(14);
    for(wx=2; wx<=73; wx++)
    {
        gotoxy(wx,5);
        printf("%c",205);
    }

    for(wx=2; wx<=73; wx++)
    {
        gotoxy(wx,48);
        printf("%c",205);
    }

    for(wy=5; wy<=48; wy++)
    {
        gotoxy(2,wy);
        printf("%c",186);
    }

    for(wy=5; wy<=48; wy++)
    {
        gotoxy(73,wy);
        printf("%c",186);
    }

    gotoxy(2,5);
    printf("%c",201);

    gotoxy(2,48);
    printf("%c",200);

    gotoxy(73,5);
    printf("%c",187);

    gotoxy(73,48);
    printf("%c",188);
    ret_color();
}

void fs()
{
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0X1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void check_hi_scores(int score)
{
    clrscr();
    static char tempname[30];

    int namelen=0;

    score=score*10;
    FILE *fp;

    int i=0,j,k,m,temp;
    char stemp[5];
    int sort=0;

    struct player
    {
        char name[5];
        int score;
    };
    struct player p[5];


    fp=fopen("hiscores.txt","r");

    if(fp==NULL)
    {
        printf("\nError:Unable to open file!\n");
        getch();
        exit(1);
    }


    while((fscanf(fp,"%s    %d",p[i].name,&p[i].score))!= EOF)
    {
        i++;
    }

    fclose(fp);


    for(m=0; m<5; m++)
    {
        if(score>p[m].score)
        {
            setcolor(11);
            printf("\n\n\t\t\tHIGH SCORE!!\n");
            setcolor(7);
            printf("\n\nEnter your name(Maximum of 5 characters)\n");
            fflush(stdin);
            scanf("%s",tempname);
            namelen=strlen(tempname);

            if(namelen>=5)
            {
                for(i=0; i<5; i++)
                    p[4].name[i]=tempname[i];
                p[4].name[i]='\0';
            }

            else
            {
                for(i=0; i<namelen; i++)
                    p[4].name[i]=tempname[i];

                for(i=namelen; i<5; i++)
                    p[4].name[i]='_';
                p[4].name[i]='\0';

            }


            p[4].score=score;

            sort=1;
            break;
        }
    }



    if(sort==1)
    {
        for(j=0; j<i; j++)
        {
            for(k=0; k<i-1; k++)
            {
                if(p[k].score<p[k+1].score)
                {
                    temp=p[k].score;
                    strcpy(stemp,p[k].name);
                    p[k].score=p[k+1].score;
                    strcpy(p[k].name,p[k+1].name);
                    p[k+1].score=temp;
                    strcpy(p[k+1].name,stemp);
                }
            }
        }
    }

    printf("\n\t\t\tHIGH  SCORES");
    setcolor(14);
    printf("\n\n\n\t\t\tName      Score\n");
    setcolor(8);
    printf("\t\t\t***************\n");
    setcolor(11);
    for(m=0; m<i; m++)
        printf("\t\t\t%s    %d\n",p[m].name,p[m].score);
    setcolor(8);
    printf("\t\t\t***************\n");
    setcolor(7);



    fp=fopen("hiscores.txt","w");

    if(fp==NULL)
    {
        printf("Error\nUnable to open file");
        Sleep(500);
        exit(1);
    }

    for(i=0; i<5; i++)
        fprintf(fp,"%s    %d\n",p[i].name,p[i].score);

    fclose(fp);
    printf("\n\n\t\t\tHigh Scores saved!\n");
    printf("\n\t\t\tPress Any Key to Continue...");

    getch();


}

