#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#define ROW 29
#define COL 20
#define LEFT 75
#define DOWN 80
#define RIGHT 77
#define SPACE 32
#define ESC 27
int max,grade;
void color(int num);
void InitBlock();
void DrawBlock(int shape,int form,int x,int y);
void DrawSpace(int shape,int form,int x,int y);
void HideCursor();
int isLeagle(int shape,int form,int x,int y);
void InitInterface();
int JudeFunc();
void StartGame();
void ReadGrade();
void WriteGrade();
struct Face{
    int data[ROW][COL+10];
    int color[ROW][COL+10];
}face;
struct Block{
    int space[4][4];
}block[7][4];
int main(){
   max=0;grade=0;
   system("title 俄罗斯方块");
   system("mode con lines=29 cols=60");
   HideCursor();
   ReadGrade();
   InitInterface();
   InitBlock();
   srand((unsigned int)time(NULL));
   StartGame();
   return 0;
}
//初始化方块 0：T  1:L  2:J  3:Z  4: S  5:O  6:I
void InitBlock(){
    for(int i=0;i<=2;i++){
        block[0][0].space[1][i]=1;
        block[0][0].space[2][1]=1;
    }
     for(int i=1;i<=3;i++){
        block[1][0].space[i][1]=1;
        block[1][0].space[3][2]=1;
        block[2][0].space[i][2]=1;
        block[2][0].space[3][1]=1;
    }
     for(int i=0;i<=1;i++){
        block[3][0].space[1][i]=1;
        block[4][0].space[2][i]=1;
    }
     for(int i=1;i<=2;i++){
        block[4][0].space[1][i]=1;
        block[3][0].space[2][i]=1;
        block[5][0].space[1][i]=1;
        block[5][0].space[2][i]=1;
    }
     for(int i=0;i<=3;i++){
        block[6][0].space[i][1]=1;
    }
    int temp[4][4];
    for(int shape=0;shape<7;shape++){
        for(int form=0;form<3;form++){
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                  temp[i][j]=block[shape][form].space[i][j];
                }
            }
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                block[shape][form+1].space[i][j]=temp[3-j][i];
            }
        }
        }
    }
}
void CursorJump(int x,int y){
    COORD pos;
    pos.X =x;
    pos.Y =y;
    HANDLE handle =GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle,pos);
}
void InitInterface(){
    color(7);
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL+10;j++){
            if(j==0||j==COL-1||j==COL+9){
                face.data[i][j]=1;
                CursorJump(j*2,i);
                printf("■");
            }
            else if(i==ROW-1){
                face.data[i][j]=1;
                printf(" ■");
            }else{
                face.data[i][j]=0;
            }
        }
    }
    for(int i=COL;i<COL+10;i++){
        face.data[8][i]=1;
        CursorJump(2*i,8);
        printf("■");
    }
    CursorJump(2*COL,1);
    printf("下一个方块：");
    CursorJump(2 * COL + 4, ROW - 19);
	printf("左移：←");
	
	CursorJump(2 * COL + 4, ROW - 17);
	printf("右移：→");
	
	CursorJump(2 * COL + 4, ROW - 15);
	printf("加速：↓");
	
	CursorJump(2 * COL + 4, ROW - 13);
	printf("旋转：空格");
	
	CursorJump(2 * COL + 4, ROW - 11);
	printf("暂停: S");
	
	CursorJump(2 * COL + 4, ROW - 9);
	printf("退出: Esc");
	
	CursorJump(2 * COL + 4, ROW - 7);
	printf("重新开始:R");
	
	CursorJump(2 * COL + 4, ROW - 5);
	printf("最高纪录:");
	
	CursorJump(2 * COL + 4, ROW - 3);
	printf("当前分数:");
}
void color(int c){
    switch(c)
    {
        case 0 :
        c=13;
        break;
        case 1 :
        case 2 :
        c=12;
        break;
        case 3 :
        case 4 :
        c=10;
        break;
        case 5 :
        c =14;
        break;
        case 6 :
        c=11;
        break;
        default :
        c=7;
        break;
        
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void DrawBlock(int shape,int form,int x,int y){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(block[shape][form].space[i][j]==1){
                CursorJump(2*(x+j),y+i);
                printf("■");
            }
        }
    }
}
void DrawSpace(int shape,int form,int x,int y){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(block[shape][form].space[i][j]==1){
                CursorJump(2*(x+j),y+i);
                printf(" ");
            }
        }
    }
}
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; //定义光标信息的结构体变量
	curInfo.dwSize = 1;  //如果没赋值的话，隐藏光标无效
	curInfo.bVisible = FALSE; //将光标设置为不可见
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorInfo(handle, &curInfo); //设置光标信息
}

int isLeagle(int shape,int form,int x,int y){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if((block[shape][form].space[i][j]==1)&&(face.data[y+i][x+j]==1)){
                return 0;
                
            }
        }
    }
    return 1;//leagle
} 
int JudeFunc(){
    for(int i=ROW-2;i>4;i--){
         int sum=0;
        for(int j=1;j<COL-1;j++){
           sum+=face.data[i][j];
        }
        if(sum==0){
            break;
        }
        if(sum==COL-2){
            grade+=10;
            color(7);
            CursorJump(2*COL+13,ROW-3);
            printf("%d",grade);
            for(int j=1;j<COL-1;j++){
                face.data[i][j]=0;
                CursorJump(2*j,i);
                printf("  ");
            }
            for(int m=i;m>1;m--){
                sum=0;
                for(int n=1;n<COL-1;n++){
                    sum+=face.data[m-1][n];
                    face.data[m][n]=face.data[m-1][n];
                    face.color[m][n]=face.color[m-1][n];
                    if(face.data[m][n]==1){
                        CursorJump(2*n,m);
                        color(face.color[m][n]);
                        printf("■");
                    }else{
                        CursorJump(2*n,m);
                        printf(" ");
                    }
                    
                }
                if(sum==0)return 1;
            }

        }
    }
        for(int j=1;j<COL-1;j++){
            if(face.data[1][j]==1){
                Sleep(1000);
                system("cls");
                color(7);
                CursorJump(2*(COL/3),ROW/2);
                if(grade>max){
                    printf("恭喜打破最高记录,最高纪录为%d",grade);
                    WriteGrade();
                }else if(grade==max){
                    printf("与最高记录持平,继续加油");
                }
                CursorJump(2*(COL/3),ROW/2);
                printf("GAME OVER");
                while(1){
                    char ch;
                    CursorJump(2*(COL/3),ROW/2+3);
                    printf("再来一局?(y/n):");
                    scanf("%c",&ch);
                    if(ch=='y'||ch=='Y'){
                        system("cls");
                        main();
                    }else if(ch=='n'||ch=='N'){
                        CursorJump(2*(COL/3),ROW/2+5);
                        exit(0);
                    }else
				{
					CursorJump(2 * (COL / 3), ROW / 2 + 4);
					printf("选择错误，请再次选择");
                }
            }

        }
    }
    return 0;
}
void StartGame(){
    int shape=rand()%7,form=rand()%4;
    while(1){
        int t =0;
        int nextShape=rand()%7,nextForm =rand()%4;
        int x =COL/2-2,y=0;
        color(nextShape);
        DrawBlock(nextShape,nextForm,COL+3,3);
        while(1){
            color(shape);
            DrawBlock(shape,form,x,y);
            if(t==0){
                t=12500;
            }
            while(--t){
                if(kbhit()!=0){
                    break;
                }
            }
            if(t==0){
                if(isLeagle(shape,form,x,y+1)==0){
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            if(block[shape][form].space[i][j]==1){
                                face.data[y+i][x+j]=1;
                                face.color[y+i][x+j]=shape;
                            }
                        }
                    }
                    while(JudeFunc());
                    break;
                }else{
                    DrawSpace(shape,form,x,y);
                    y++;
                }
                
            }else{
                char ch =getch();
                switch (ch)
                {
                    case DOWN :
                    if(isLeagle(shape,form,x,y+1)==1){
                        DrawSpace(shape,form,x,y);
                        y++;
                    }
                    break;
                    case LEFT :
                    if(isLeagle(shape,form,x-1,y)==1){
                        DrawSpace(shape,form,x,y);
                        x--;
                    }
                    break;
                    case RIGHT :
                    if(isLeagle(shape,form,x+1,y)==1){
                        DrawSpace(shape,form,x,y);
                        x++;
                    }
                    break;
                    case SPACE :
                    if(isLeagle(shape,(form+1)%4,x,y+1)==1){
                        DrawSpace(shape,form,x,y);
                        y++;
                        form=(form+1)%4;
                    }
                    break;
                    case ESC :
                    system("cls");
                    color(7);
                    CursorJump(COL,ROW/2);
                    printf("游戏结束");
                    CursorJump(COL,ROW/2+2);
                    exit(0);
                    case 's' :
                    case 'S' :
                    system("pause>nul");
                    break;
                    case 'r' :
                    case 'R' :
                    system("cls");
                    main();
                }
            }
        
        }
        shape =nextShape,form =nextForm;
        DrawSpace(nextShape,nextForm,COL+3,3);
    }
}
void ReadGrade(){
    FILE* pf =fopen("俄罗斯方块最高纪录.txt","r");
    if(pf==NULL){
        pf=fopen("俄罗斯方块最高纪录.txt","w");
        fwrite(&grade,sizeof(int),1,pf);
    }
    fseek(pf,0,SEEK_SET);
    fread(&max,sizeof(int),1,pf);
    fclose(pf);
    pf=NULL;
}
void WriteGrade(){
    FILE* pf =fopen("俄罗斯方块最高纪录.txt","w");
    if(pf==NULL){
        printf("保存最高得分记录失败\n");
        exit(0);
    }
    fwrite(&grade,sizeof(int),1,pf);
    fclose(pf);
    pf=NULL;

}