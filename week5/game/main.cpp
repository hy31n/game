#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h> // �뷡 �߰�  
#pragma comment(lib,"winmm.lib")

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // ���� �����̽�  

int keyControl();
void init();
void titleDraw();
int menuDraw();
int quizList(); 
int drawQuiz();
void gotoxy(int, int);
int score = 0;

const char *category[] = {
    "����",
    "����",
	"����" 
};

int main(void)
{
	PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP); // ������� 
    init();
    while(1){
    	titleDraw();
    	int menuCode = menuDraw(); 
    	if(menuCode == 0){
    		int n = quizList();
    		for (int i = 0; i < 11; i++) {
        		if (n == 1) {
            		drawQuiz();
            		Sleep(1000);
            		n = 0;
            		quizList(); // ī�װ� ȭ������ ���ư��� 
       			} else if(n == 2){
       				drawQuiz();
            		Sleep(1000);
            		n = 0;
            		quizList(); 
				} else if(n == 3){
       				drawQuiz();
            		Sleep(1000);
            		n = 0;
            		quizList(); 
				}
   			}
		} else if(menuCode == 1){
			return 0; // ����  
		}
		system("cls");
	}
    
    return 0;
}

void init()
{
    system("mode con cols=56 lines=20 | title quiz!"); // �ܼ�â ũ�� ����
}

int keyControl(){
	char temp = getch();
	
	if (temp == 'w' || temp == 'W') {
        return UP;
    } else if (temp == 's' || temp == 'S') {
        return DOWN;
    } else if (temp == 'a' || temp == 'A') {
        return LEFT;
    } else if (temp == 'd' || temp == 'D') {
        return RIGHT;
    } else if (temp == ' ') {
        return SUBMIT;
	}
}

void titleDraw()
{
    printf("\n\n\n\n");
    printf("                 ##  ##   ######   ######     ##\n");
    printf("                 ##  ##     ##        ##      ##\n");
    printf("        ######   ##  ##     ##       ##       ##\n");
    printf("        ##  ##   ##  ##     ##      ##        ##\n");
    printf("        ######   ##  ##     ##     ##\n");
    printf("            ##   ######   ######   ######     ##\n");
    printf("            ##\n");
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int menuDraw()
{
	int x = 24;
	int y = 12;
    gotoxy(x - 2, y);
    printf("> ���ӽ���");
    gotoxy(x, y+1);
    printf("  ����   ");
    while(1){
    	int n = keyControl();
		switch(n){
			case UP: {
				if(y > 12){
					gotoxy(x-2, y);
					printf(" ");
					gotoxy(x-2, --y);
					printf(">");
				}
				break;
			}
			
			case DOWN: {
				if(y < 13){
					gotoxy(x-2, y);
					printf(" ");
					gotoxy(x-2, ++y);
					printf(">");	
				}
				break;
			}
			
			case SUBMIT: {
				return y-12;
				break;
			}
		}	 
	}
}

int quizList() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    int x = 24;
    int y = 6;
    int selectedQuiz = 0;

    system("cls");

    printf("\n\n");
    printf("                    [ī�װ� ����]\n");

    gotoxy(x - 2, y);

    for (int i = 0; i < 3; i++) {
        gotoxy(x - 2, y + i + 1);
        if (i == selectedQuiz) {
            printf(">");
        } else {
            printf(" ");
        }
        printf("%d: %s", i + 1, category[i]);
    }

    while (1) {
        int n = keyControl();

        switch (n) {
            case UP:
                if (selectedQuiz > 1) {
                    gotoxy(x-2, y);
                    printf(" ");
                    gotoxy(x-2, --y);
                    printf(">");
                    selectedQuiz--;
                }
                break;
            case DOWN:
                if (selectedQuiz < 3) {
                    gotoxy(x-2, y);
                    printf(" ");
                    gotoxy(x-2, ++y);
                    printf(">");
                    selectedQuiz++;
                }
                break;
            case SUBMIT:
                return y-6;
        }
    }
}

int drawQuiz() {
    system("cls");
    FILE *inFile = fopen("QUIZ.txt", "r");

    if (inFile == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    char line[600]; // �� ���� �о�� ����
    char question[500]; // Ȧ�� ���� ������ ���� 
    char answer[500];   // ¦�� ���� ���信 ����  
    int isOddLine = 1; // �� ��ȣ�� Ȧ������ �Ǵ� 

    while (fgets(line, sizeof(line), inFile) != NULL) {
        Sleep(2000); 
        system("cls");

        if (isOddLine) {
        	printf("\n\n");
            printf("\t\t%s", line); // Ȧ�� ���� ������ ���
        } else {
            // ¦�� ���� �������� ����
            strcpy(answer, line);
        }

        if (!isOddLine) {
            char userAnswer[500];
            printf("\n\n");
            printf("\t\t�� : ");
            scanf("%s", userAnswer);

            if (strcmp(answer, userAnswer) == 0) {
                printf("\n");
                printf("\t\t�����Դϴ�.\n");
                score++;
                printf("\t\t���� ���� : %d", score); 
            } else {
            	printf("\n");
                printf("\t\t�����Դϴ�.\n");
                printf("\t\t���� : %s\n", answer);
                score--;
                printf("\t\t���� ���� : %d", score); 
            }
        }

        isOddLine = !isOddLine; // Ȧ��, ¦�� ���� �����ư��� ó��
    }
	Sleep(2000); 
    fclose(inFile);
    score = 0;
    return 0;
}


 
