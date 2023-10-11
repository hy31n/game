#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h> // 노래 추가  
#pragma comment(lib,"winmm.lib")

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // 선택 스페이스  

int keyControl();
void init();
void titleDraw();
int menuDraw();
int quizList(); 
int drawQuiz();
void gotoxy(int, int);
int score = 0;

const char *category[] = {
    "수학",
    "국어",
	"영어" 
};

int main(void)
{
	PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP); // 배경음악 
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
            		quizList(); // 카테고리 화면으로 돌아가기 
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
			return 0; // 종료  
		}
		system("cls");
	}
    
    return 0;
}

void init()
{
    system("mode con cols=56 lines=20 | title quiz!"); // 콘솔창 크기 설정
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
    printf("> 게임시작");
    gotoxy(x, y+1);
    printf("  종료   ");
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
    printf("                    [카테고리 선택]\n");

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
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    char line[600]; // 한 줄을 읽어올 버퍼
    char question[500]; // 홀수 줄은 문제에 저장 
    char answer[500];   // 짝수 줄은 정답에 저장  
    int isOddLine = 1; // 줄 번호가 홀수인지 판단 

    while (fgets(line, sizeof(line), inFile) != NULL) {
        Sleep(2000); 
        system("cls");

        if (isOddLine) {
        	printf("\n\n");
            printf("\t\t%s", line); // 홀수 줄을 문제로 출력
        } else {
            // 짝수 줄은 정답으로 저장
            strcpy(answer, line);
        }

        if (!isOddLine) {
            char userAnswer[500];
            printf("\n\n");
            printf("\t\t답 : ");
            scanf("%s", userAnswer);

            if (strcmp(answer, userAnswer) == 0) {
                printf("\n");
                printf("\t\t정답입니다.\n");
                score++;
                printf("\t\t현재 점수 : %d", score); 
            } else {
            	printf("\n");
                printf("\t\t오답입니다.\n");
                printf("\t\t정답 : %s\n", answer);
                score--;
                printf("\t\t현재 점수 : %d", score); 
            }
        }

        isOddLine = !isOddLine; // 홀수, 짝수 줄을 번갈아가며 처리
    }
	Sleep(2000); 
    fclose(inFile);
    score = 0;
    return 0;
}


 
