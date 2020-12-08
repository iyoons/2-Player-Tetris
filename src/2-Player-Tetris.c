// 2인용 Tetris Battle(배틀 테트리스) 게임

// 메인 타이틀 & 메뉴 화면
// PLAY 메뉴, RANKING 메뉴, EXIT 메뉴

// 게임 중단 or 재시작 or 나가기 기능

// 제공 정보 :
// 1. 게임 레벨(상승 시 블록 낙하 속도 증가) → LEVEL
// 2. 플레이어 본인의 점수와 상대 플레이어와의 점수 차 → SCORE
// 3. 다음에 내려올 블록 모양 → NEXT
// 4. 현재 한 번에 삭제된 블록 라인 수 → TUPLE
// 5. 보관된 블록 모양 → HOLD
// 6. 삭제된 총 블록 라인 수 → SENT

// 2인 Play를 위한 테트리스 맵(10 X 20) 2개
// 실행화면 창 크기는 너비 100, 높이 30로 설정

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// 색상 정의
#define BLACK	0
#define BLUE1	1
#define GREEN1	2
#define CYAN1	3
#define RED1	4
#define MAGENTA1 5
#define YELLOW1	6
#define GRAY1	7
#define GRAY2	8
#define BLUE2	9
#define GREEN2	10
#define CYAN2	11
#define RED2	12
#define MAGENTA2 13
#define YELLOW2	14
#define WHITE	15

#define ENTER 0xd // 메뉴 선택 or player 이름 입력
#define ESC 0x1b //  게임(프로그램) 종료
#define PAUSE 'p' // 게임 중단

// 블록 직하
#define TAB 0x9 // PLAYER1
#define SPACE 0x20 // PLAYER2

// 블록 보관
#define HOLD1 'x' // PLAYER1
#define HOLD2 '/' // PLAYER2

#define SPECIAL1 0xe0 // 특수 키는 0xe0 + key 값으로 구성

// PLAYER2의 블록 이동 방향 - 화살표
#define UP  0x48 // Up key (0xe0 + 0x48)
#define DOWN 0x50 // Down key (0xe0 + 0x50)
#define LEFT 0x4b // Left key (0xe0 + 0x4b)
#define RIGHT 0x4d // Right key (0xe0 + 0x4d)

// PLAYER1의 블록 이동 방향 - WASD
#define UP2		'w'
#define DOWN2	's'
#define LEFT2	'a'
#define RIGHT2	'd'

// 테트리스 맵과 다양한 정보를 포함한 상자
#define B_WIDTH 18 // 상자 너비
#define B_HEIGHT 22 // 상자 높이

// 테트리스 맵의 너비와 높이
#define M_WIDTH 10 // 맵 너비
#define M_HEIGHT 20 // 맵 높이

#define BOX "▩" // 상자 테두리 모양

// 기록된 Player 이름과 점수 정렬을 위한 구조체 타입 Rank
typedef struct {
	char player[20]; // Player 이름
	int score; // 점수
} Rank;

// 각 플레이어의 상자 시작 좌표
int B_X[2] = { 10, 56 };
int B_Y[2] = { 3, 3 };

// 1 ~ 5위 출력 시 글씨 색상
int ranking_color[5] = { RED1, YELLOW1, GREEN1, BLUE1, MAGENTA1 };

// 테트리스 블록 배열 구현
// 서로 다른 7개의 블록 모양과 회전(시계 방향) 시 블록 모양 표현
int BLOCK[7][4][4][4] = {
	{ 0,0,0,0,
	  0,0,0,0,
	  1,1,0,0,
	  0,1,1,0,

	  0,0,0,0,
	  0,1,0,0,
	  1,1,0,0,
	  1,0,0,0,

	  0,0,0,0,
	  0,0,0,0,
	  1,1,0,0,
	  0,1,1,0,

	  0,0,0,0,
	  0,1,0,0,
	  1,1,0,0,
	  1,0,0,0 },

	{ 0,0,0,0,
	  0,0,0,0,
	  1,0,0,0,
	  1,1,1,0,

	  0,0,0,0,
	  1,1,0,0,
	  1,0,0,0,
	  1,0,0,0,

	  0,0,0,0,
	  0,0,0,0,
	  1,1,1,0,
	  0,0,1,0,

	  0,0,0,0,
	  0,1,0,0,
	  0,1,0,0,
	  1,1,0,0 },

	{ 0,0,0,0,
	  0,0,0,0,
	  0,1,0,0,
	  1,1,1,0,

	  0,0,0,0,
	  1,0,0,0,
	  1,1,0,0,
	  1,0,0,0,

	  0,0,0,0,
	  0,0,0,0,
	  1,1,1,0,
	  0,1,0,0,

	  0,0,0,0,
	  0,1,0,0,
	  1,1,0,0,
	  0,1,0,0 },

	{ 0,0,0,0,
	  0,0,0,0,
	  1,1,0,0,
	  1,1,0,0,

	  0,0,0,0,
	  0,0,0,0,
	  1,1,0,0,
	  1,1,0,0,

	  0,0,0,0,
	  0,0,0,0,
	  1,1,0,0,
	  1,1,0,0,

	  0,0,0,0,
	  0,0,0,0,
	  1,1,0,0,
	  1,1,0,0 },

	{ 0,0,0,0,
	  0,0,0,0,
	  0,1,1,0,
	  1,1,0,0,

	  0,0,0,0,
	  1,0,0,0,
	  1,1,0,0,
	  0,1,0,0,

	  0,0,0,0,
	  0,0,0,0,
	  0,1,1,0,
	  1,1,0,0,

	  0,0,0,0,
	  1,0,0,0,
	  1,1,0,0,
	  0,1,0,0 },

	{ 0,0,0,0,
	  0,0,0,0,
	  0,0,1,0,
	  1,1,1,0,

	  0,0,0,0,
	  1,0,0,0,
	  1,0,0,0,
	  1,1,0,0,

	  0,0,0,0,
	  0,0,0,0,
	  1,1,1,0,
	  1,0,0,0,

	  0,0,0,0,
	  1,1,0,0,
	  0,1,0,0,
	  0,1,0,0 },

	{ 0,0,0,0,
	  0,0,0,0,
	  1,1,1,1,
	  0,0,0,0,

	  0,1,0,0,
	  0,1,0,0,
	  0,1,0,0,
	  0,1,0,0,

	  0,0,0,0,
	  0,0,0,0,
	  1,1,1,1,
	  0,0,0,0,

	  0,1,0,0,
	  0,1,0,0,
	  0,1,0,0,
	  0,1,0,0 }
};

char* block_type[2] = { "▣", "■" }; // 공중에 떠 있을 때와 바닥에 놓여져 있을 때의 블록 모양
int block_color[7] = { RED1, YELLOW1, GREEN1, CYAN1, BLUE1, MAGENTA1, GRAY1 }; // 서로 다른 7개의 블록 색상

// RANKING에 필요한 Player 이름 저장 배열 
char player1_name[20]; // Player1
char player2_name[20]; // Player2

int map[2][M_HEIGHT + 2][M_WIDTH + 2] = { 0 }; // 2인용 테트리스 맵
int map_color[2][M_HEIGHT][M_WIDTH] = { 0 }; // 맵 속 블록들의 색상
int now[2] = { 0 }; // 현재 이동 중인 블록 모양
int rotate[2] = { 0 }; // 현재 이동 중인 블록의 회전값
int pos_x[2] = { 0 }; // 현재 이동 중인 블록이 위치한 x 좌표
int pos_y[2] = { 0 }; // 현재 이동 중인 블록이 위치한 y 좌표
int level[2] = { 0 }; // 게임 레벨
int score[2] = { 0 }; // 현재 점수
int next[2] = { 0 }; // 다음 블록 모양
int tuple[2] = { 0 }; // 현재 한 번에 삭제된 블록 라인 수
int hold[2] = { 0 }; // 보관된 블록 모양
int sent[2] = { 0 }; // 제거된 총 블록 라인 수
int new_block_flag[2] = { 0 }; // 새로운 블록 필요 여부 (0 : 필요 없음, 1 : 필요함)
int game_over[2] = { 0 }; // 게임 종료 여부 (0 : 진행 중, 1 : 종료)

// 레벨 상승 시 속도 조절
int frame_count = 0; // 점점 증가되는 frame
int p1_frame_sync = 13; // Player1 처음 시작은 13 frame 마다 이동
int p2_frame_sync = 13; // Player2 처음 시작은 13 frame 마다 이동

void gotoxy(int x, int y) // 원하는 위치(좌표)로 커서를 이동시켜주는 함수
{
	COORD pos; // windows.h 에 정의
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(int fg_color, int bg_color) // 글씨와 배경 색상을 지정해주는 함수
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

// 원하는 배경 색상으로 화면을 지워주는 함수
void cls(int bg_color, int text_color)
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);

}

void removeCursor(void) { // 커서가 보이지 않도록 하는 함수
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void printxy(int x, int y, char* str) // 원하는 위치(좌표)에 문자열을 출력해주는 함수
{
	gotoxy(x, y);
	printf(str);
}

// 메인 타이틀 & 메뉴 화면을 출력하고 선택된 메뉴를 반환하는 함수
int show_menu() 
{
	int i = 0, x = 50, y = 19, menu; // x,y : PLAY 메뉴로 이동 시 커서 위치, menu : 선택된 메뉴(1 ~ 3)
	unsigned char ch; // 메뉴 선택 시 입력되는 키

	// 메인 타이틀 출력
	textcolor(CYAN1, CYAN2);
	printxy(23, 4, "┌─────────────────────────┐");
	printxy(23, 5, "│                                                  │");
	printxy(23, 6, "│                                                  │");
	printxy(23, 7, "│                                                  │");
	printxy(23, 8, "│                                                  │");
	printxy(23, 9, "│                                                  │");
	printxy(23, 10, "└─────────┐          ┌─────────┘");
	printxy(43, 11, "│          │");
	printxy(43, 12, "│          │");
	printxy(43, 13, "│          │");
	printxy(43, 14, "│          │");
	printxy(43, 15, "└─────┘");

	textcolor(RED1, BLACK);
	printxy(25, 5, " ■■■■\n");
	printxy(25, 6, "    ■   \n");
	printxy(25, 7, "    ■   \n");
	printxy(25, 8, "    ■   \n");
	printxy(25, 9, "    ■   \n");
	textcolor(YELLOW1, BLACK);
	printxy(34, 5, " ■■■\n");
	printxy(34, 6, " ■    \n");
	printxy(34, 7, " ■■■\n");
	printxy(34, 8, " ■    \n");
	printxy(34, 9, " ■■■\n");
	textcolor(YELLOW2, BLACK);
	printxy(41, 5, " ■■■■\n");
	printxy(41, 6, "    ■   \n");
	printxy(41, 7, "    ■   \n");
	printxy(41, 8, "    ■   \n");
	printxy(41, 9, "    ■   \n");
	textcolor(GREEN1, BLACK);
	printxy(50, 5, " ■■■  \n");
	printxy(50, 6, " ■   ■ \n");
	printxy(50, 7, " ■■■  \n");
	printxy(50, 8, " ■   ■ \n");
	printxy(50, 9, " ■    ■\n");
	textcolor(BLUE2, BLACK);
	printxy(59, 5, " ■■■\n");
	printxy(59, 6, "   ■  \n");
	printxy(59, 7, "   ■  \n");
	printxy(59, 8, "   ■  \n");
	printxy(59, 9, " ■■■\n");
	textcolor(MAGENTA2, BLACK);
	printxy(66, 5, "  ■■■ \n");
	printxy(66, 6, " ■      \n");
	printxy(66, 7, "  ■■■ \n");
	printxy(66, 8, "       ■\n");
	printxy(66, 9, "  ■■■ \n");

	// 각 플레이어의 사용 키 안내
	textcolor(GRAY2, BLACK);
	printxy(3, 19, "┌─< P1 Key >─┐");
	printxy(3, 20, "│  UP       w  │");
	printxy(3, 21, "│ DOWN      s  │");
	printxy(3, 22, "│ LEFT      a  │");
	printxy(3, 23, "│ RIGHT     d  │");
	printxy(3, 24, "│DIRECT    Tab │");
	printxy(3, 25, "│ HOLD      x  │");
	printxy(3, 26, "└───────┘");

	printxy(79, 19, "┌─< P2 Key >─┐");
	printxy(79, 20, "│  UP      ↑  │");
	printxy(79, 21, "│ DOWN     ↓  │");
	printxy(79, 22, "│ LEFT     ←  │");
	printxy(79, 23, "│ RIGHT    →  │");
	printxy(79, 24, "│DIRECT   SPACE│");
	printxy(79, 25, "│ HOLD      /  │");
	printxy(79, 26, "└───────┘");

	// 표정이 바뀌는 애니메이션
	while (1) {
		textcolor(WHITE, BLACK);
		if (i % 20 < 10) {
			printxy(45, 10, "          \n");
			printxy(45, 11, "  ⊙  ⊙  \n");
			printxy(45, 12, " ♪ º ♬ \n");
			printxy(45, 13, "    ▼    \n");
			printxy(45, 14, "          \n");
		}
		else {
			printxy(45, 10, "          \n");
			printxy(45, 11, "  >    <  \n");
			printxy(45, 12, " *  ㅣ  * \n");
			printxy(45, 13, "    〓    \n");
			printxy(45, 14, "          \n");
		}
		i++;

		// 3가지 메인 메뉴 출력(해당 메뉴로 이동 시 다른 색상으로 표시)
		if (y == 19)
			textcolor(BLUE2, BLACK);
		printxy(23, 18, "┌─────────────────────────┐");
		printxy(23, 19, "│                       PLAY                       │");
		printxy(23, 20, "└─────────────────────────┘");
		textcolor(WHITE, BLACK);

		if (y == 22)
			textcolor(GREEN2, BLACK);
		printxy(23, 21, "┌─────────────────────────┐");
		printxy(23, 22, "│                      RANKING                     │");
		printxy(23, 23, "└─────────────────────────┘");
		textcolor(WHITE, BLACK);

		if (y == 25)
			textcolor(RED2, BLACK);
		printxy(23, 24, "┌─────────────────────────┐");
		printxy(23, 25, "│                       EXIT                       │");
		printxy(23, 26, "└─────────────────────────┘");
		textcolor(WHITE, BLACK);

		gotoxy(x, y); // 처음 커서 위치는 PLAY 메뉴
		if (kbhit() == 1) {  // 키보드가 눌려져 있을 경우
			ch = getch();
			if (ch == ENTER) { // ENTER 누르면 메뉴 선택
				switch (y) {
				case 19:
					menu = 1;
					break;
				case 22:
					menu = 2;
					break;
				case 25:
					menu = 3;
					break;
				}
				return menu; // 메뉴 선택되면 반환
			}
			// 다른 메뉴로 이동
			if (ch == SPECIAL1) { // 특수 키가 눌러져 있는 경우
				ch = getch();
				switch (ch) {
				case UP:
					if (y == 19)
						y = 25;
					else
						y -= 3;
					break;
				case DOWN:
					if (y == 25)
						y = 19;
					else
						y += 3;
					break;
				}
			}
		}
		Sleep(50);
	}
}

// 게임 레벨을 출력하는 함수
void show_level(int player)
{
	// 게임 레벨 출력 위치 지정
	switch (player) {
	case 0: // Player1
		gotoxy(42, 4);
		printf("%2d", level[player]);
		break;
	case 1: // Player2
		gotoxy(88, 4);
		printf("%2d", level[player]);
		break;
	}
}

// 현재 점수를 출력하는 함수
void show_score()
{
	// Player1 점수 출력
	gotoxy(36, 7);
	printf("%7d", score[0]);

	// Player2 점수 출력
	gotoxy(82, 7);
	printf("%7d", score[1]);

	// Player1과 Player2의 점수 차 출력
	if (score[0] > score[1]) { // Player1의 점수가 더 높을 경우
		// Player1
		gotoxy(34, 8);
		printf("(+%7d)", score[0] - score[1]);

		// Player2
		gotoxy(80, 8);
		printf("(-%7d)", score[0] - score[1]);
	}
	else if (score[0] == score[1]) { // 두 점수가 같을 경우
		// Player1
		gotoxy(34, 8);
		printf("(+%7d)", 0);

		// Player2
		gotoxy(80, 8);
		printf("(+%7d)", 0);
	}
	else { // Player2의 점수가 더 높을 경우
		// Player1
		gotoxy(34, 8);
		printf("(-%7d)", score[1] - score[0]);

		// Player2
		gotoxy(80, 8);
		printf("(+%7d)", score[1] - score[0]);
	}
}

// 다음 블록 모양을 출력하는 함수
void show_next(int player)
{
	int i, j, x, y;

	// 다음 블록 모양 출력 위치 지정
	switch (player) {
	case 0: // Player1
		if (next[player] == 3) { // 다음 블록 모양이 정사각형 모양일 경우
			x = 37;
			y = 10;
		}
		else if (next[player] == 6) { // 다음 블록 모양이 막대기 모양일 경우
			x = 35;
			y = 10;
		}
		else { // 다음 블록 모양이 나머지 모양일 경우
			x = 36;
			y = 10;
		}
		break;
	case 1: // Player2
		if (next[player] == 3) { // 다음 블록 모양이 정사각형 모양일 경우
			x = 83;
			y = 10;
		}
		else if (next[player] == 6) { // 다음 블록 모양이 막대기 모양일 경우
			x = 81;
			y = 10;
		}
		else { // 다음 블록 모양이 나머지 모양일 경우
			x = 82;
			y = 10;
		}
		break;
	}

	// 이전의 다음 블록 모양 지우기 
	if (player == 0) { // Player1
		for (i = 1; i < 4; i++) {
			for (j = 0; j < 5; j++) {
				gotoxy(34 + j * 2, 10 + i);
				printf("  ");
			}
		}
	}
	else { // Player2
		for (i = 1; i < 4; i++) {
			for (j = 0; j < 5; j++) {
				gotoxy(80 + j * 2, 10 + i);
				printf("  ");
			}
		}
	}

	// 다음 블록 모양 출력
	textcolor(block_color[next[player]], BLACK);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			gotoxy(x + j * 2, y + i);
			if (BLOCK[next[player]][0][i][j])
				printf("%s", block_type[0]);
		}
	}
	textcolor(WHITE, BLACK);
}

// 현재 한 번에 삭제된 블록 라인 수를 출력하는 함수
void show_tuple(int player)
{
	// 현재 한 번에 삭제된 블록 라인 수 출력 위치 지정
	switch (player) {
	case 0: // Player1
		gotoxy(35, 16);
		break;
	case 1: // Player2
		gotoxy(81, 16);
		break;
	}
	if (tuple[player]) { // 현재 삭제된 블록 라인이 하나 이상일 경우
		switch (tuple[player]) {
		case 1:
			printf(" SINGLE  "); // 삭제된 블록 라인 1줄
			break;
		case 2:
			printf(" DOUBLE  "); // 삭제된 블록 라인 2줄
			break;
		case 3:
			printf(" TRIPLE  "); // 삭제된 블록 라인 3줄
			break;
		case 4:
			printf("QUADRUPLE"); // 삭제된 블록 라인 3줄
			break;
		}
		Sleep(500); // 잠시 출력 유지
		printf("\b\b\b\b\b\b\b\b\b         "); // 해당 칸 비우기
		tuple[player] = 0; // 현재 한 번에 삭제된 블록 라인 수 0으로 다시 되돌리기
	}
}

// 보관된 블록 모양을 출력하는 함수
void show_hold(int player)
{
	int i, j, x, y;

	// 보관된 블록 모양 출력 위치 지정
	switch (player) {
	case 0: // Player1
		if (hold[player] == 3) { // 보관된 블록 모양이 정사각형 모양일 경우
			x = 37;
			y = 18;
		}
		else if (hold[player] == 6) { // 보관된 블록 모양이 막대기 모양일 경우
			x = 35;
			y = 18;
		}
		else { // 보관된 블록 모양이 나머지 모양일 경우
			x = 36;
			y = 18;
		}
		break;
	case 1: // Player2
		if (hold[player] == 3) { // 보관된 블록 모양이 정사각형 모양일 경우
			x = 83;
			y = 18;
		}
		else if (hold[player] == 6) { // 보관된 블록 모양이 막대기 모양일 경우
			x = 81;
			y = 18;
		}
		else { // 보관된 블록 모양이 나머지 모양일 경우
			x = 82;
			y = 18;
		}
		break;
	}

	// 이전에 보관됐던 블록 모양 지우기
	if (player == 0) { // Player1
		for (i = 1; i < 4; i++) {
			for (j = 0; j < 5; j++) {
				gotoxy(34 + j * 2, 18 + i);
				printf("  ");
			}
		}
	}
	else { // Player2
		for (i = 1; i < 4; i++) {
			for (j = 0; j < 5; j++) {
				gotoxy(80 + j * 2, 18 + i);
				printf("  ");
			}
		}
	}

	// 보관된 블록 모양 출력
	textcolor(block_color[hold[player]], BLACK);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			gotoxy(x + j * 2, y + i);
			if (BLOCK[hold[player]][0][i][j])
				printf("%s", block_type[0]);
		}
	}
	textcolor(WHITE, BLACK);
}

// 삭제된 총 블록 라인 수를 출력하는 함수
void show_sent(int player)
{
	// 삭제된 총 블록 라인 수 출력 위치 지정
	switch (player) {
	case 0: // Player1
		gotoxy(41, 23);
		printf("%3d", sent[player]);
		break;
	case 1: // Player2
		gotoxy(87, 23);
		printf("%3d", sent[player]);
		break;
	}
}

int start_star = 0; // 게임 시작 시 맵 속에서 별이 깜박이는 애니메이션을 넣기 위한 변수

int box[B_HEIGHT][B_WIDTH] = { // 테트리스 맵을 포함한 상자 구현
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
2,0,0,0,0,0,0,0,0,0,0,2,3,9,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,4,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,9,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,9,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,5,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,9,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,9,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,9,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,6,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,9,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,7,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,9,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,9,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,9,9,9,9,9,2,
2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,
2,0,0,0,0,0,0,0,0,0,0,2,8,9,9,9,9,2,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
};

// ch 문자열로 테트리스 맵을 포함한 상자를 그려주는 함수
// 각 상자의 양 끝 좌표와 한글 문자 사용을 위해 문자열을 매개변수로 받음
void draw_box(int x1, int y1, int x2, int y2, char* ch)
{
	int i = 0, x, y;

	while (1) { // 게임 시작 시 별이 깜박이는 동안 상자를 반복하여 그리기
		for (y = 0; y < B_HEIGHT; y++) {
			for (x = 0; x < B_WIDTH; x++) {
				// Player1
				// 맵 위에 Player1 출력
				gotoxy(x1 + 15, y1 - 2);
				printf("Player1");
				// Player1 상자 그리기
				gotoxy(x * 2 + x1, y + y1);
				switch (box[y][x]) {
				case 0: // 맵 속
					// 게임 시작 시 별이 깜박이는 애니메이션 구현
					if (start_star % 2)
						printf("**"); 
					else
						printf("  ");
					break;
				case 2: // 상자 테두리
					printf("%s", ch);
					break;
				case 3: // 게임 레벨 출력 칸
					printf("<LEVEL> ");
					break;
				case 4: // 현재 점수 출력 칸
					printf("<SCORE> ");
					break;
				case 5: // 다음 블록 모양 출력 칸
					printf("<NEXT>");
					break;
				case 6: // 현재 한 번에 삭제된 블록 라인 수 출력 칸
					printf("<TUPLE> ");
					break;
				case 7: // 보관된 블록 모양 출력 칸
					printf("<HOLD>");
					break;
				case 8: // 삭제된 총 블록 라인 수 출력 칸
					printf("<SENT>");
					break;
				default: // 9일 경우 비워 두기 
					break;
				}
				// Player2
				// 맵 위에 Player2 출력
				gotoxy(x2 + 15, y2 - 2);
				printf("Player2");
				gotoxy(x * 2 + x2, y + y2);
				// Player2 상자 그리기
				switch (box[y][x]) { 
				case 0: // 맵 속
				// 게임 시작 시 별이 깜박이는 애니메이션 구현
					if (start_star % 2)
						printf("**");
					else
						printf("  ");
					break;
				case 2: // 상자 테두리
					printf("%s", ch);
					break;
				case 3: //게임 레벨 출력 칸
					printf("<LEVEL> ");
					break;
				case 4: // 현재 점수 출력 칸
					printf("<SCORE> ");
					break;
				case 5: // 다음 블록 모양 출력 칸
					printf("<NEXT>");
					break;
				case 6: // 현재 한 번에 삭제된 블록 라인 수 출력 칸
					printf("<TUPLE> ");
					break;
				case 7: // 보관된 블록 모양 출력 칸
					printf("<HOLD>");
					break;
				case 8: // 삭제된 총 블록 라인 수 출력 칸
					printf("<SENT>");
					break;
				default: // 9일 경우 비워 두기 
					break;
				}
			}
		}
		if (start_star < 4) // 별이 깜박이는 횟수 지정
			start_star++;
		else // 맵 속에서 별이 깜박이지 않고 비워져 있음
			break;
		Sleep(100);
	}

	// 게임 시작을 알림
	textcolor(RED2, CYAN2);
	i = 0;
	while (i < 10) {
		printxy(49, 12, "Game");
		printxy(48, 13, "Start!");
		i++;
		Sleep(100); // 잠시 출력 유지
	}

	// 시작 알림 표시 지우기
	textcolor(WHITE, BLACK);
	printxy(49, 12, "    ");
	printxy(48, 13, "      ");
}

// 게임 진행 상태를 초기화하는 함수
// 게임 시작 or 재시작
void init_game()
{
	int i, j;
	start_star = 0; // 전역 변수이므로 재시작일 경우 다시 0으로 초기화

	cls(BLACK, WHITE); // 이전 화면 지우기
	// Player1과 Player2 이름 입력 받기
	textcolor(YELLOW1, BLACK);
	printxy(40, 11, "Enter your name (20)");
	textcolor(GRAY2, BLACK);
	printxy(22, 23, "(한글 사용 시 게임 시작 전에 한/영 키를 다시 눌러주세요.)"); // 게임 중 영어 키를 사용하기 때문
	textcolor(WHITE, BLACK);
	// Player1
	printxy(39, 14, "Player1 : ");
	printxy(35, 15, "──────────────");
	gotoxy(51, 14);
	scanf(" %[^\n]s", player1_name); // ENTER가 눌리기 전까지 공백 포함 이름 입력 받기
	// Player2
	printxy(39, 17, "Player2 : ");
	printxy(35, 18, "──────────────");
	gotoxy(51, 17);
	scanf(" %[^\n]s", player2_name);  // ENTER가 눌리기 전까지 공백 포함 이름 입력 받기

	// Player1과 Player2의 테트리스 맵 구현
	for (i = 0; i < M_HEIGHT + 2; i++) {
		for (j = 0; j < M_WIDTH + 2; j++)
			map[0][i][j] = map[1][i][j] = box[i][j];
	}

	// Player1과 Player2의 테트리스 맵 속 블록 색상 초기화
	for (i = 0; i < M_HEIGHT; i++) {
		for (j = 0; j < M_WIDTH; j++)
			map_color[0][i][j] = map_color[1][i][j] = BLACK;
	}

	srand(time(NULL)); // rand() 사용 위함
	// 현재 이동 중인 블록 모양 랜덤 생성
	now[0] = rand() % 7; // Player1
	now[1] = rand() % 7; // Player2
	rotate[0] = rotate[1] = 0; // Player1과 Player2의 현재 이동 중인 블록 회전값 회전하지 않은 상태로 초기화
	// 현재 이동 중인 블록이 나타날 위치 선정
	pos_x[0] = pos_x[1] = 4; // Player1과 Player2의 현재 이동 중인 블록의 x 좌표값 초기화
	pos_y[0] = pos_y[1] = 0; // Player1과 Player2의 현재 이동 중인 블록의 y 좌표값 초기화
	level[0] = level[1] = 1; // Player1과 Player2의 게임 레벨 1로 초기화
	score[0] = score[1] = 0; // Player1과 Player2의 현재 점수 0으로 초기화
	tuple[0] = tuple[1] = 0; // Player1과 Player2의 현재 한 번에 삭제된 블록 라인 수 0으로 초기화
	// 다음 블록 모양 랜덤 생성
	next[0] = rand() % 7; // Player1
	next[1] = rand() % 7; // Player2
	hold[0] = hold[1] = -1; // Player1과 Player2의 보관된 블록 모양이 없으므로 -1로 초기화
	sent[0] = sent[1] = 0; // Player1과 Player2의 삭제된 총 블록 라인 수 0으로 초기화
	new_block_flag[0] = new_block_flag[1] = 0; // Player1과 Player2의 새로운 블록이 필요하지 않으므로 0으로 초기화
	game_over[0] = game_over[1] = 0; // Player1과 Player2의 게임이 시작되었으므로 0으로 초기화

	frame_count = 0; // 게임이 시작되므로 frame 0으로 초기화
	p1_frame_sync = 13; // 게임이 시작되므로 Player1 sync 13으로 초기화
	p2_frame_sync = 13; // 게임이 시작되므로 Player2 sync 13으로 초기화

	cls(BLACK, WHITE); // Player 이름 입력 화면 지우기
	draw_box(B_X[0], B_Y[0], B_X[1], B_Y[1], BOX); // Player1과 Player2의 상자 그리기
	show_level(0); show_level(1); // Player1과 Player2의 게임 레벨 출력
	show_score(); // Player1과 Player2의 현재 점수와 상대와의 점수 차 출력
	show_next(0); show_next(1); // Player1과 Player2의 다음 블록 모양 출력
	show_sent(0); show_sent(1); // Player1과 Player2의 삭제된 총 블록 라인 수 출력
}

// 테트리스 맵 속에 현재 이동 중인 블록을 그려주는 함수
// 블록이 공중에 떠 있을 때와 바닥에 도착하였을 때를 구분하기 위해 블록 출력 타입을 매개변수로 받음
void show_block(int player, int type) {
	int i, j;

	// 현재 이동 중인 블록 그리기
	textcolor(block_color[now[player]], BLACK);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			gotoxy(B_X[player] + (pos_x[player] + j) * 2, B_Y[player] + pos_y[player] + i);
			if (BLOCK[now[player]][rotate[player]][i][j])
				printf("%s", block_type[type]);
		}
	}
	textcolor(WHITE, BLACK);
}

// 테트리스 맵 속 현재 이동 중인 블록을 이전 위치에서 지워주는 함수
void erase_block(int player) {
	int i, j;

	// 현재 이동 중인 블록 이전 위치에서 지우기
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			gotoxy(B_X[player] + (pos_x[player] + j) * 2, B_Y[player] + pos_y[player] + i);
			if (BLOCK[now[player]][rotate[player]][i][j])
				printf("  ");
		}
	}
}

// 테트리스 맵 속에서 특정 위치의 블록이 움직일 수 있는지 판단하는 함수 (0 : 불가능, 1 : 가능)
// 회전 시에도 검사할 수 있도록 회전값을 매개변수로 받음
int can_move(int player, int rotate, int x, int y) {
	int i, j;

	// 현재 이동 중인 블록 모양과 맵 속 채워진 부분이 겹칠 경우 0을 반환
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (BLOCK[now[player]][rotate][i][j]) {
				if (map[player][y + i][x + j])
					return 0;
			}
		}
	}
	return 1; // 현재 이동 중인 블록 모양과 맵 속 채워진 부분이 겹치지 않으면 1을 반환
}

// 현재 이동 중인 블록이 바닥에 도착하였을 때 블록 라인이 생겼는지 확인 후
// 블록 라인이 존재하면 블록 라인을 모두 삭제해주는 함수
void remove_line(int player) {
	// count : 현재 한 번에 삭제된 블록 라인 수를 세기 위한 변수
	// old_level : 게임 레벨이 상승하였는지 확인하기 위한 이전 레벨 저장 변수
	int i, j, k, l, m, count = 0, old_level;

	// 현재 이동 중인 블록이 바닥에 도착하였을 때 맵 속 해당 블록의 위치에 해당 블록의 색상 저장
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (BLOCK[now[player]][rotate[player]][i][j])
				map_color[player][pos_y[player] + i - 1][pos_x[player] + j - 1] = now[player];
		}
	}

	// 블록 라인이 존재하는지 확인 후 존재하면 블록 라인 모두 삭제
	for (i = M_HEIGHT; i >= 1; i--) { // 맵의 1층(가장 아래)부터 확인
		// 블록 라인이 만들어지기 위해서는 해당 층에 빈 공간이 없어야 함
		for (j = 1; j <= M_WIDTH; j++) {
			if (!map[player][i][j])
				break;
		}
		// 해당 층에 빈 공간이 없을 경우 해당 층의 블록 라인 삭제
		if (map[player][i][j]) {
			// 맵 속 채워진 블록을 한 층씩 내려줌 
			for (k = i; k >= 2; k--) {
				for (j = 1; j <= M_WIDTH; j++) {
					map[player][k][j] = map[player][k - 1][j];
					map_color[player][k - 1][j - 1] = map_color[player][k - 2][j - 1];
				}
			}
			// 맵 속을 모두 비우기
			for (l = 1; l <= M_HEIGHT; l++) {
				for (m = 1; m <= M_WIDTH; m++) {
					gotoxy(m * 2 + B_X[player], l + B_Y[player]);
					printf("  ");
				}
			}
			// 맵 속 채워진 블록을 다시 그려주기
			for (l = 1; l <= M_HEIGHT; l++) {
				for (m = 1; m <= M_WIDTH; m++) {
					if (map[player][l][m]) {
						gotoxy(m * 2 + B_X[player], l + B_Y[player]);
						textcolor(block_color[map_color[player][l - 1][m - 1]], BLACK);
						printf("%s", block_type[1]);
					}
				}
			}
			textcolor(WHITE, BLACK);
			count++; // 현재 한 번에 삭제된 블록 라인 수 증가
			i++; // 해당 층에 블록이 새로 내려왔기 때문에 블록 라인이 존재하는지 다시 한 번 검사 
		}
	}

	tuple[player] = count; // 현재 한 번에 삭제된 블록 라인 수 저장
	sent[player] += count; // 삭제된 총 라인 수에 현재 한 번에 삭제된 블록 라인 수 더함

	// 게임 레벨과 현재 한 번에 삭제된 블록 라인 수에 따라 추가되는 점수가 다르도록 설정
	switch (count) {
	case 0: // 현재 한 번에 삭제된 블록 라인 수 0줄일 경우
		// 추가 점수 없음
		break;
	case 1: // 현재 한 번에 삭제된 블록 라인 수 1줄일 경우
		score[player] += 40 * level[player]; // (게임 레벨 * 40)점 추가
		break;
	case 2: // 현재 한 번에 삭제된 블록 라인 수 2줄일 경우
		score[player] += 100 * level[player]; // (게임 레벨 * 100)점 추가
		break;
	case 3: // 현재 한 번에 삭제된 블록 라인 수 3줄일 경우
		score[player] += 300 * level[player]; // (게임 레벨 * 300)점 추가
		break;
	case 4: // 현재 한 번에 삭제된 블록 라인 수 4줄일 경우
		score[player] += 1200 * level[player]; // (게임 레벨 * 1200)점 추가
		break;
	}

	old_level = level[player]; // 이전 게임 레벨 저장

	// 현재 게임 레벨 저장
	// 게임 레벨은 삭제된 총 블록 라인 수에 따라 결정
	if (sent[player] >= 0 && sent[player] <= 9) // 삭제된 총 블록 라인 수가 한 자릿수일 경우
		level[player] = 1; // 게임 레벨 1
	else if (sent[player] >= 10 && sent[player] <= 19) // 삭제된 총 블록 라인 수의 십의 자리가 1일 경우
		level[player] = 2; // 게임 레벨 2
	else if (sent[player] >= 20 && sent[player] <= 29) // 삭제된 총 블록 라인 수의 십의 자리가 2일 경우
		level[player] = 3; // 게임 레벨 3
	else if (sent[player] >= 30 && sent[player] <= 39) // 삭제된 총 블록 라인 수의 십의 자리가 3일 경우
		level[player] = 4; // 게임 레벨 4
	else if (sent[player] >= 40 && sent[player] <= 49) // 삭제된 총 블록 라인 수의 십의 자리가 4일 경우
		level[player] = 5; // 게임 레벨 5
	else if (sent[player] >= 50 && sent[player] <= 59) // 삭제된 총 블록 라인 수의 십의 자리가 5일 경우
		level[player] = 6; // 게임 레벨 6
	else if (sent[player] >= 60 && sent[player] <= 69) // 삭제된 총 블록 라인 수의 십의 자리가 6일 경우
		level[player] = 7; // 게임 레벨 7
	else if (sent[player] >= 70 && sent[player] <= 79) // 삭제된 총 블록 라인 수의 십의 자리가 7일 경우
		level[player] = 8; // 게임 레벨 8
	else if (sent[player] >= 80 && sent[player] <= 89) // 삭제된 총 블록 라인 수의 십의 자리가 8일 경우
		level[player] = 9; // 게임 레벨 9
	else if (sent[player] >= 90 && sent[player] <= 99) // 삭제된 총 블록 라인 수의 십의 자리가 9일 경우
		level[player] = 10; // 게임 레벨 10

	if (level[player] > old_level) { // 게임 레벨이 상승하였을 경우
		if (player == 0) // Player1
			p1_frame_sync--; // Player1 sync 1 감소
		else // Player2
			p2_frame_sync--; // Player2 sync 1 감소
	}

	show_level(player); // 게임 레벨 출력
	show_score(); // 현재 점수와 상대와의 점수 차 출력
	show_tuple(player); // 현재 한 번에 삭제된 블록 라인 수 출력
	show_sent(player); // 삭제된 총 블록 라인 수 출력

	if (score[player] >= 10000000) // 점수가 상자 속에 기록할 수 있는 범위를 초과할 경우
		game_over[player] = 1; // 게임 종료
}

// 게임이 종료되면 맵 속이 보이지 않도록 막아주는 함수
void cover_map(int player) {
	int i, j;

	// 맵 속이 보이지 않도록 막아주기
	textcolor(GRAY2, BLACK);
	for (i = 1; i < M_HEIGHT + 1; i++) {
		for (j = 1; j < M_WIDTH + 1; j++) {
			gotoxy(j * 2 + B_X[player], i + B_Y[player]);
			printf("▒");
		}
	}
}

// Player1가 게임을 진행하는 동안 반복적으로 호출되는 함수
// Player1과 관련된 키가 눌러져 있을 경우 현재 이동 중인 블록의 이동 방향 또는 보관 수행
// 현재 이동 중인 블록이 한 층 내려와야 하는지 확인 후 조건을 통과하면 수행
// 현재 이동 중인 블록이 바닥에 도착하였을 때 새로운 블록을 생성하여 현재 이동 중인 블록으로 설정
void player1(unsigned char ch)
{
	int i, j, temp; // temp : 현재 이동 중인 블록과 보관된 블록을 서로 바꾸기 위해 필요한 변수

	// 현재 이동 중인 블록 모양이
	// 맵 속의 새로운 블록이 처음 나타나는 위치에 이미 존재하는 블록과 겹치는 부분이 있을 경우
	for (i = 1; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (BLOCK[now[0]][rotate[0]][i][j]) {
				if (map[0][i][4 + j])
					break;
			}
		}
	}
	// 현재 이동 중인 블록의 위치를 그대로 고정
	if (BLOCK[now[0]][rotate[0]][i][j] && map[0][i][4 + j]) {
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (BLOCK[now[0]][rotate[0]][i][j])
					map[0][pos_y[0] + i][pos_x[0] + j] = 1;
			}
		}
		show_block(0, 1);
	}

	// 맵 속에서 새로운 블록이 처음 나타나는 위치에 이미 블록이 채워져 있으면 게임 종료 
	for (i = 1; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (map[0][i][4 + j]) { // 맵 속에서 새로운 블록이 처음 나타나는 위치에 이미 블록이 채워져 있을 경우
				game_over[0] = 1; // 게임 종료
				cover_map(0); // 맵 속이 보이지 않도록 막아주기
				return; // 해당 함수 종료
			}
		}
	}

	if (new_block_flag[0]) { // 새로운 블록 생성이 필요한 경우
		now[0] = next[0]; // 다음 블록 모양을 현재 이동 중인 블록 모양으로 설정
		rotate[0] = 0; // 현재 이동 중인 블록의 회전값은 0으로 초기화

		// 새로운 블록이 처음 나타날 위치 지정
		pos_x[0] = 4; // 새로운 블록이 처음 나타날 위치의 x 좌표
		pos_y[0] = 0; // 새로운 블록이 처음 나타날 위치의 y 좌표

		next[0] = rand() % 7; // 다음 블록 모양을 랜덤 생성
		show_next(0); // 다음 블록 모양 출력
		show_block(0, 0); // 현재 이동 중인 블록 그리기
		new_block_flag[0] = 0; // 새로운 블록 생성이 필요하지 않음
	}

	if (ch) { // Player1과 관련된 키가 눌러져 있을 경우 
		switch (ch) {
		case UP2: // 시계 방향으로 현재 이동 중인 블록 회전이 가능하면 수행
			// 시계 방향으로 현재 이동 중인 블록 회전이 가능할 경우
			if (can_move(0, (rotate[0] + 1) % 4, pos_x[0], pos_y[0])) {
				erase_block(0); // 현재 이동 중인 블록을 이전 위치에서 지우기 
				rotate[0] = (rotate[0] + 1) % 4; // 시계 방향으로 현재 이동 중인 블록 회전
				show_block(0, 0); // 현재 이동 중인 블록 그리기
			}
			break;
		case DOWN2: // 현재 이동 중인 블록이 한 층 내려갈 수 있으면 수행
			// 현재 이동 중인 블록이 한 층 내려갈 수 있을 경우 
			if (can_move(0, rotate[0], pos_x[0], pos_y[0] + 1)) {
				erase_block(0); // 현재 이동 중인 블록을 이전 위치에서 지우기
				pos_y[0]++; // 현재 이동 중인 블록 위치의 y 좌표 값 1 증가
				show_block(0, 0); // 현재 이동 중인 블록 그리기
			}
			else { // 현재 이동 중인 블록이 바닥에 도착하였을 경우 
				show_block(0, 1); // 이동하던 블록의 형태 변경하여 출력
				// 현재 이동 중인 블록의 위치를 그대로 고정
				for (i = 0; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						if (BLOCK[now[0]][rotate[0]][i][j])
							map[0][pos_y[0] + i][pos_x[0] + j] = 1;
					}
				}
				remove_line(0); // 블록 라인이 생겼는지 확인 후 존재하면 모두 삭제

				// 맵 속에서 새로운 블록이 처음 나타나는 위치에 이미 블록이 채워져 있으면 게임 종료
				for (i = 1; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						// 맵 속에서 새로운 블록이 처음 나타나는 위치에 이미 블록이 채워져 있을 경우
						if (map[0][i][4 + j]) { 
							game_over[0] = 1; // 게임 종료
							cover_map(0); // 맵 속이 보이지 않도록 막아주기
							return; // 해당 함수 종료
						}
					}
				}
				// 맵 속에서 새로운 블록이 처음 나타나는 위치에 채워진 블록이 없을 경우
				new_block_flag[0] = 1; // 새로운 블록 생성 필요함 
			}
			break;
		case LEFT2: // 현재 이동 중인 블록이 왼쪽으로 한 칸 이동할 수 있으면 수행
			// 현재 이동 중인 블록이 왼쪽으로 한 칸 이동할 수 있을 경우
			if (can_move(0, rotate[0], pos_x[0] - 1, pos_y[0])) {
				erase_block(0); // 현재 이동 중인 블록을 이전 위치에서 지우기
				pos_x[0]--; // 현재 이동 중인 블록 위치의 x 좌표 값 1 감소
				show_block(0, 0); // 현재 이동 중인 블록 그리기
			}
			break;
		case RIGHT2: // 현재 이동 중인 블록이 오른쪽으로 한 칸 이동할 수 있으면 수행
			// 현재 이동 중인 블록이 오른쪽으로 한 칸 이동할 수 있을 경우
			if (can_move(0, rotate[0], pos_x[0] + 1, pos_y[0])) {
				erase_block(0); // 현재 이동 중인 블록을 이전 위치에서 지우기
				pos_x[0]++; // 현재 이동 중인 블록 위치의 x 좌표 값 1 증가
				show_block(0, 0); // 현재 이동 중인 블록 그리기
			}
			break;
		case TAB: // 현재 이동 중인 블록이 직하하여 바닥에 도착하도록 함
			// 현재 이동 중인 블록이 한 층 내려갈 수 있을 때까지
			while (can_move(0, rotate[0], pos_x[0], pos_y[0] + 1)) {
				erase_block(0); // 현재 이동 중인 블록을 이전 위치에서 지우기
				pos_y[0]++; // 현재 이동 중인 블록 위치의 y 좌표 값 1 증가
				show_block(0, 0); // 현재 이동 중인 블록 그리기
			}
			show_block(0, 1); // 이동하던 블록의 형태 변경하여 출력
			// 현재 이동 중인 블록의 위치를 그대로 고정
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					if (BLOCK[now[0]][rotate[0]][i][j])
						map[0][pos_y[0] + i][pos_x[0] + j] = 1;
				}
			}
			remove_line(0); // 블록 라인이 생겼는지 확인 후 존재하면 모두 삭제

			// 맵 속에서 새로운 블록이 처음 나타나는 위치에 이미 블록이 채워져 있으면 게임 종료
			for (i = 1; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					// 맵 속에서 새로운 블록이 처음 나타나는 위치에 이미 블록이 채워져 있을 경우
					if (map[0][i][4 + j]) {
						game_over[0] = 1; // 게임 종료
						cover_map(0); // 맵 속이 보이지 않도록 막아주기
						return; // 해당 함수 종료
					}
				}
			}
			// 맵 속에서 새로운 블록이 처음 나타나는 위치에 채워진 블록이 없을 경우
			new_block_flag[0] = 1; // 새로운 블록 생성 필요함
			break;
		case HOLD1: // 현재 이동 중인 블록을 보관하고 보관되어 있던 블록이 있다면 다시 꺼내 사용
			if (hold[0] == -1) { // 보관되어 있던 블록이 없을 경우
				erase_block(0); // 현재 이동 중인 블록을 현재 위치에서 지우기
				hold[0] = now[0]; // 이동하던 블록을 보관
				new_block_flag[0] = 1; // 이동할 블록이 있어야 하므로 새로운 블록 생성 필요함
			}
			else { // 보관되어 있던 블록이 있을 경우
				erase_block(0); // 현재 이동 중인 블록을 현재 위치에서 지우기
				// 현재 이동 중인 블록과 보관되어 있던 블록 바꾸기
				temp = now[0];
				now[0] = hold[0];
				hold[0] = temp;
				rotate[0] = 0; // 현재 이동 중인 블록의 회전값 0으로 초기화
				// 현재 이동 중인 블록의 위치에서 바뀐 블록을 출력할 수 없는 경우 
				if (!can_move(0, rotate[0], pos_x[0], pos_y[0])) {
					while (1) {
						if (pos_x[0] < 5) // 현재 이동 중인 블록 위치의 x 좌표 값이 5보다 작을 경우
							pos_x[0]++; // 현재 이동 중인 블록 위치의 x 좌표 값 1 증가
						else // 현재 이동 중인 블록 위치의 x 좌표 값이 5보다 클 경우 
							pos_x[0]--; // 현재 이동 중인 블록 위치의 x 좌표 값 1 감소
						// 현재 이동 중인 블록의 위치에서 바뀐 블록을 출력이 가능한 경우
						if (can_move(0, rotate[0], pos_x[0], pos_y[0]))
							break; // while문 빠져나감
					}
				}
				show_block(0, 0); // 현재 이동 중인 블록 그리기
			}
			show_hold(0); // 보관된 블록 모양 출력
			break;
		}
	}

	if (frame_count % p1_frame_sync == 0) { // frame_count를 frame_sync로 나누었을 때 나머지가 0인 경우
		// 현재 이동 중인 블록이 한 층 내려갈 수 있을 경우 
		if (can_move(0, rotate[0], pos_x[0], pos_y[0] + 1)) {
			erase_block(0); // 현재 이동 중인 블록을 이전 위치에서 지우기
			pos_y[0]++; // 현재 이동 중인 블록 위치의 y 좌표 값 1 증가
			show_block(0, 0); // 현재 이동 중인 블록 그리기
		}
		else {
			if (new_block_flag[0] == 0) { // 같은 상황이 이미 처리되지 않았을 경우
				show_block(0, 1); // 이동하던 블록의 형태 변경하여 출력
				// 현재 이동 중인 블록의 위치를 그대로 고정
				for (i = 0; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						if (BLOCK[now[0]][rotate[0]][i][j])
							map[0][pos_y[0] + i][pos_x[0] + j] = 1;
					}
				}
				remove_line(0); // 블록 라인이 생겼는지 확인 후 존재하면 모두 삭제

				// 맵 속에서 새로운 블록이 처음 나타나는 위치에 이미 블록이 채워져 있으면 게임 종료
				for (i = 1; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						// 맵 속에서 새로운 블록이 처음 나타나는 위치에 이미 블록이 채워져 있을 경우
						if (map[0][i][4 + j]) {
							game_over[0] = 1; // 게임 종료
							cover_map(0); // 맵 속이 보이지 않도록 막아주기
							return; // 해당 함수 종료
						}
					}
				}
				// 맵 속에서 새로운 블록이 처음 나타나는 위치에 채워진 블록이 없을 경우
				new_block_flag[0] = 1; // 새로운 블록 생성 필요함
			}
		}
	}
}

// Player2가 게임을 진행하는 동안 반복적으로 호출되는 함수
// Player1과 같은 방식으로 작동하므로 주석 생략
void player2(unsigned char ch)
{
	int i, j, temp;

	for (i = 1; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (BLOCK[now[1]][rotate[1]][i][j]) {
				if (map[1][i][4 + j])
					break;
			}
		}
	}
	if (BLOCK[now[1]][rotate[1]][i][j] && map[1][i][4 + j]) {
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (BLOCK[now[1]][rotate[1]][i][j])
					map[1][pos_y[1] + i][pos_x[1] + j] = 1;
			}
		}
		show_block(1, 1);
	}

	for (i = 1; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (map[1][i][4 + j]) {
				game_over[1] = 1;
				cover_map(1);
				return;
			}
		}
	}

	if (new_block_flag[1]) {
		now[1] = next[1];
		rotate[1] = 0;

		pos_x[1] = 4;
		pos_y[1] = 0;

		next[1] = rand() % 7;
		show_next(1);
		show_block(1, 0);
		new_block_flag[1] = 0;
	}

	if (ch) {
		switch (ch) {
		case UP:
			if (can_move(1, (rotate[1] + 1) % 4, pos_x[1], pos_y[1])) {
				erase_block(1);
				rotate[1] = (rotate[1] + 1) % 4;
				show_block(1, 0);
			}
			break;
		case DOWN:
			if (can_move(1, rotate[1], pos_x[1], pos_y[1] + 1)) {
				erase_block(1);
				pos_y[1]++;
				show_block(1, 0);
			}
			else {
				show_block(1, 1);
				for (i = 0; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						if (BLOCK[now[1]][rotate[1]][i][j])
							map[1][pos_y[1] + i][pos_x[1] + j] = 1;
					}
				}
				remove_line(1);

				for (i = 1; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						if (map[1][i][4 + j]) {
							game_over[1] = 1;
							cover_map(1);
							return;
						}
					}
				}
				new_block_flag[1] = 1;
			}
			break;
		case LEFT:
			if (can_move(1, rotate[1], pos_x[1] - 1, pos_y[1])) {
				erase_block(1);
				pos_x[1]--;
				show_block(1, 0);
			}
			break;
		case RIGHT:
			if (can_move(1, rotate[1], pos_x[1] + 1, pos_y[1])) {
				erase_block(1);
				pos_x[1]++;
				show_block(1, 0);
			}
			break;
		case SPACE:
			while (can_move(1, rotate[1], pos_x[1], pos_y[1] + 1)) {
				erase_block(1);
				pos_y[1]++;
				show_block(1, 0);
			}
			show_block(1, 1);
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					if (BLOCK[now[1]][rotate[1]][i][j])
						map[1][pos_y[1] + i][pos_x[1] + j] = 1;
				}
			}
			remove_line(1);

			for (i = 1; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					if (map[1][i][4 + j]) {
						game_over[1] = 1;
						cover_map(1);
						return;
					}
				}
			}
			new_block_flag[1] = 1;
			break;
		case HOLD2:
			if (hold[1] == -1) {
				erase_block(1);
				hold[1] = now[1];
				new_block_flag[1] = 1;
			}
			else {
				erase_block(1);
				temp = now[1];
				now[1] = hold[1];
				hold[1] = temp;
				rotate[1] = 0;
				if (!can_move(1, rotate[1], pos_x[1], pos_y[1])) {
					while (1) {
						if (pos_x[1] < 5)
							pos_x[1]++;
						else
							pos_x[1]--;
						if (can_move(1, rotate[1], pos_x[1], pos_y[1]))
							break;
					}
				}
				show_block(1, 0);
			}
			show_hold(1);
			break;
		}
	}

	if (frame_count % p2_frame_sync == 0) {
		if (can_move(1, rotate[1], pos_x[1], pos_y[1] + 1)) {
			erase_block(1);
			pos_y[1]++;
			show_block(1, 0);
		}
		else {
			if (new_block_flag[1] == 0) {
				show_block(1, 1);
				for (i = 0; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						if (BLOCK[now[1]][rotate[1]][i][j])
							map[1][pos_y[1] + i][pos_x[1] + j] = 1;
					}
				}
				remove_line(1);

				for (i = 1; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						if (map[1][i][4 + j]) {
							game_over[1] = 1;
							cover_map(1);
							return;
						}
					}
				}
				new_block_flag[1] = 1;
			}
		}
	}
}

// 2인용 배틀 테트리스 게임 프로그램의 메인 함수
// 메뉴 선택에 따른 역할 수행
int main()
{
	int i, j, x, y, menu; // x, y : 다른 메뉴로 이동 시 커서 위치, menu : 선택된 메뉴(1 ~3)
	unsigned char ch; // 키를 입력 시 사용되는 변수

	Rank ranking[128]; // Player의 이름과 점수 정렬을 위해 구조체 생성

	removeCursor(); // 테트리스 게임이 진행되는 과정에서 커서가 보이지 않도록 함

	menu = show_menu(); // show_menu의 반환값이 선택된 메뉴 번호

	// 선택된 메뉴에 따라 역할 수행
	if (menu == 1) { // PLAY 메뉴 선택 시
	START: // 재시작을 위함 
		init_game(); // 게임 진행 상태를 초기화

		while (!game_over[0] || !game_over[1]) // Player1과 Player2 모두의 게임이 끝나기 전까지 반복
		{
			if (kbhit() == 1) {  // 키보드가 눌려져 있을 경우
				char c1;
				c1 = getch(); // 키 값을 읽는다
				if (c1 == '\0') // VS 의 NULL 값은 Error
					continue;
				else
					ch = c1;
				// ESC 누르면 프로그램 종료
				if (ch == ESC) {
					cls(BLACK, WHITE); // 화면 지우기
					gotoxy(30, 14); // 종료 시 커서 위치 지정
					return 0; // 프로그램 종료
				}
				// 'p' 누르면 게임 중단
				if (ch == PAUSE) {
					// PAUSED 메뉴 화면의 경우 메인 메뉴 화면과 출력 방식이 유사하므로 주석 생략
					unsigned char c2;
					x = 50, y = 13;
					cls(BLACK, WHITE);
					textcolor(MAGENTA2, YELLOW2);
					printxy(47, 7, "PAUSED");
					while (1) {
						textcolor(WHITE, BLACK);

						if (y == 13)
							textcolor(BLUE2, BLACK);
						printxy(22, 12, "┌─────────────────────────┐");
						printxy(22, 13, "│                       RESUME                     │");
						printxy(22, 14, "└─────────────────────────┘");
						textcolor(WHITE, BLACK);

						if (y == 18)
							textcolor(GREEN2, BLACK);
						printxy(22, 17, "┌─────────────────────────┐");
						printxy(22, 18, "│                       RETRY                      │");
						printxy(22, 19, "└─────────────────────────┘");
						textcolor(WHITE, BLACK);

						if (y == 23)
							textcolor(RED2, BLACK);
						printxy(22, 22, "┌─────────────────────────┐");
						printxy(22, 23, "│                       EXIT                       │");
						printxy(22, 24, "└─────────────────────────┘");
						textcolor(WHITE, BLACK);

						gotoxy(x, y);
						if (kbhit() == 1) {
							c2 = getch();
							if (c2 == ENTER) {
								break;
							}
							if (c2 == SPECIAL1) { 
								c2 = getch();
								switch (c2) {
								case UP:
									if (y == 13)
										y = 23;
									else
										y -= 5;
									break;
								case DOWN:
									if (y == 23)
										y = 13;
									else
										y += 5;
									break;
								}
							}
						}
						Sleep(50);
					}
					if (y == 13) { // RESUME 메뉴 선택 시 진행하던 게임 다시 진행
						cls(BLACK, WHITE); // PAUSE 메뉴 화면 지우기
						// Player1과 Player2의 상자 다시 그리기
						draw_box(B_X[0], B_Y[0], B_X[1], B_Y[1], BOX);
						// Player1의 게임이 종료되지 않았다면 맵 속 블록 다시 그리기
						if (!game_over[0]) {
							for (i = 1; i <= M_HEIGHT; i++) {
								for (j = 1; j <= M_WIDTH; j++) {
									if (map[0][i][j]) {
										gotoxy(j * 2 + B_X[0], i + B_Y[0]);
										textcolor(block_color[map_color[0][i - 1][j - 1]], BLACK);
										printf("%s", block_type[1]);
									}
								}
							}
						}
						else { // Player1의 게임이 종료되었을 경우
							cover_map(0); // 맵 속이 보이지 않도록 막아주기
						}
						// Player2의 게임이 종료되지 않았다면 맵 속 블록 다시 그리기
						if (!game_over[1]) {
							for (i = 1; i <= M_HEIGHT; i++) {
								for (j = 1; j <= M_WIDTH; j++) {
									if (map[1][i][j]) {
										gotoxy(j * 2 + B_X[1], i + B_Y[1]);
										textcolor(block_color[map_color[1][i - 1][j - 1]], BLACK);
										printf("%s", block_type[1]);
									}
								}
							}
						}
						else { // Player2의 게임이 종료되었을 경우
							cover_map(1); // 맵 속이 보이지 않도록 막아주기
						}
						
						textcolor(WHITE, BLACK);
						if(!game_over[0]) // Player1의 게임이 종료되지 않았을 경우
							show_block(0, 0); // 현재 이동 중인 블록 그리기
						if(!game_over[1]) // Player2의 게임이 종료되지 않았을 경우
							show_block(1, 0); // 현재 이동 중인 블록 그리기
						show_level(0); show_level(1); // Player1과 Player2의 게임 레벨 출력
						show_score(); // Player1과 Player2의 현재 점수와 상대와의 점수 차 출력
						show_next(0); show_next(1); // Player1과 Player2의 다음 블록 모양 출력
						// 보관된 블록 모양 출력
						if (hold[0] != -1) // Player1의 보관된 블록이 있을 경우
							show_hold(0); // Player1의 보관된 블록 모양 출력
						if (hold[1] != -1) // Player2의 보관된 블록이 있을 경우
							show_hold(1); // Player2의 보관된 블록 모양 출력
						show_sent(0); show_sent(1); // Player1과 Player2의 삭제된 총 블록 라인 수 출력
					}
					else if (y == 18) // RETRY 메뉴 선택 시
						goto START; // 게임 재시작
					else { // EXIT 메뉴 선택 시
						cls(BLACK, WHITE); // PAUSE 메뉴 화면 지우기
						gotoxy(30, 14); // 종료 시 커서 위치 지정
						return 0; // 프로그램 종료
					}
				}
				// 각 플레이어의 게임이 종료되지 않으면 player 함수 정상적으로 호출
				if (ch == SPECIAL1) { // 특수 키가 눌려져 있는 경우
					ch = getch();
					switch (ch) {
					// Player2만 방향 키로 이동
					case UP:
					case DOWN:
					case LEFT:
					case RIGHT:
						if (!game_over[0])
							player1(0);
						if (!game_over[1])
							player2(ch);
						break;
					default: 
						// frame_count를 frame_sync로 나누었을 때 나머지가 0인 경우 Player 함수 호출
						if (!game_over[0] && (frame_count % p1_frame_sync == 0))
							player1(0);
						if (!game_over[1] && (frame_count % p2_frame_sync == 0))
							player2(0);
					}
				}
				else { // 눌러져 있는 키가 특수 키가 아닌 경우
					switch (ch) {
					case SPACE:
					case HOLD2:
						if (!game_over[0])
							player1(0);
						if (!game_over[1])
							player2(ch);
						break;
					// Player1만 WASD 키로 이동
					case UP2:
					case DOWN2:
					case LEFT2:
					case RIGHT2:
					case TAB:
					case HOLD1:
						if (!game_over[0])
							player1(ch);
						if (!game_over[1])
							player2(0);
						break;
					default: 
						// frame_count를 frame_sync로 나누었을 때 나머지가 0인 경우 Player 함수 호출
						if (!game_over[0] && (frame_count % p1_frame_sync == 0))
							player1(0);
						if (!game_over[1] && (frame_count % p2_frame_sync == 0))
							player2(0);
					}
				}
			}
			else { // 키보드가 눌러져 있지 않을 경우
				// frame_count를 frame_sync로 나누었을 때 나머지가 0인 경우 Player 함수 호출
				if (!game_over[0] && (frame_count % p1_frame_sync == 0))
					player1(0);
				if (!game_over[1] && (frame_count % p2_frame_sync == 0))
					player2(0);
			}
			Sleep(50);
			frame_count++; // 속도 조절을 위해 frame_count 증가
		}
	}
	else if (menu == 2) { // RANKING 메뉴 선택 시
		FILE* infile1; // Player 이름 파일
		FILE* infile2; // Player 점수 파일
		int n, player_num = 0;

		infile1 = fopen("player.txt", "r"); // Player 이름 파일 열기
		infile2 = fopen("score.txt", "r"); // Player 점수 파일 열기

		// 파일 속 Player 이름을 구조체 ranking의 player 배열에 저장
		while (1) {
			n = fscanf(infile1, "%s", &ranking[player_num].player);

			if (n != 1)
				break;

			player_num++;
		}

		player_num = 0; // 기록된 이름 수 0으로 초기화

		// 파일 속 Player 점수를 구조체 ranking의 score 변수에 저장
		while (1) {
			n = fscanf(infile2, "%d", &ranking[player_num].score);

			if (n != 1)
				break;

			player_num++;
		}

		// 높은 점수 순으로 구조체 ranking 정렬
		for (i = 0; i < player_num; i++) {
			for (j = i + 1; j < player_num; j++) {
				if (ranking[i].score < ranking[j].score) {
					// 높은 점수 순으로 구조체 ranking의 score 정렬
					int temp1 = ranking[i].score;
					ranking[i].score = ranking[j].score;
					ranking[j].score = temp1;
					// 높은 점수 순으로 구조체 ranking의 player 정렬
					int k;
					char temp2[20];
					for (k = 0; k < strlen(ranking[i].player); k++) {
						temp2[k] = ranking[i].player[k];
					}
					temp2[k] = '\0';
					for (k = 0; k < strlen(ranking[j].player); k++) {
						ranking[i].player[k] = ranking[j].player[k];
					}
					ranking[i].player[k] = '\0';
					for (k = 0; k < strlen(temp2); k++) {
						ranking[j].player[k] = temp2[k];;
					}
					ranking[j].player[k] = '\0';
				}
			}
		}

		cls(BLACK, WHITE); // 메인 메뉴 화면 지우기
		printxy(45, 4, "Ranking\n");

		y = 7;
		if (player_num < 5) { // 기록된 Player의 수가 5보다 작은 경우
			// 기록된 Player의 순위 출력
			for (i = 0; i < player_num; i++) {
				textcolor(ranking_color[i], BLACK);
				printxy(22, y - 1, "─────────────────────────");
				gotoxy(22, y);
				printf("      %d       %s                                   ", i + 1, ranking[i].player);
				gotoxy(57, y);
				printf("%7d", ranking[i].score);
				printxy(22, y + 1, "─────────────────────────");
				y += 4;
			}
			// 나머지 순위는 비워 두기
			for (i = player_num; i < 5; i++) {
				textcolor(ranking_color[i], BLACK);
				printxy(22, y - 1, "─────────────────────────");
				gotoxy(22, y);
				printf("      %d       ---                      ---         ", i + 1);
				printxy(22, y + 1, "─────────────────────────");
				y += 4;
			}
		}
		else { // 기록된 Player의 수가 5와 같거나 5보다 큰 경우
			// 기록된 Player의 순위 출력
			for (i = 0; i < 5; i++) {
				textcolor(ranking_color[i], BLACK);
				printxy(22, y - 1, "─────────────────────────");
				gotoxy(22, y);
				printf("      %d       %s                                   ", i + 1, ranking[i].player);
				gotoxy(57, y);
				printf("%7d", ranking[i].score);
				printxy(22, y + 1, "─────────────────────────");
				y += 4;
			}
		}
		fclose(infile1); // Player 이름 파일 닫기
		fclose(infile2); // Player 점수 파일 닫기
		textcolor(WHITE, BLACK);
		gotoxy(30, 26); // 종료 시 커서 위치 지정
		return 0; // 프로그램 종료
	}
	else { // EXIT 메뉴 선택 시
		cls(BLACK, WHITE); // 메인 메뉴 화면 지우기
		gotoxy(30, 14); // 종료 시 커서 위치 지정
		return 0; // 프로그램 종료
	}

	FILE* outfile1; // Player 이름 파일
	FILE* outfile2; // Player 점수 파일

	outfile1 = fopen("player.txt", "a"); // Player 이름 파일 열기
	outfile2 = fopen("score.txt", "a"); // Player 점수 파일 열기

	// Player1의 이름 Player 이름 파일에 기록하기
	fputs(player1_name, outfile1);
	fprintf(outfile1, "\n");
	// Player2의 이름 Player 이름 파일에 기록하기
	fputs(player2_name, outfile1);
	fprintf(outfile1, "\n");

	fprintf(outfile2, "%d\n", score[0]); // Player1의 점수 Player 점수 파일에 기록하기
	fprintf(outfile2, "%d\n", score[1]); // Player2의 점수 Player 점수 파일에 기록하기

	fclose(outfile1); // Player 이름 파일 닫기
	fclose(outfile2); // Player 점수 파일 닫기

	cls(BLACK, WHITE); // 테트리스 게임 화면 지우기
	// 게임 결과 출력
	textcolor(GREEN2, BLACK);
	if (score[0] > score[1]) // Player1의 점수가 Player2의 점수보다 큰 경우
		printxy(40, 9, "WINNER IS PLAYER1!!  ");
	else if (score[0] < score[1]) // Player2의 점수가 Player1의 점수보다 큰 경우
		printxy(40, 9, "WINNER IS PLAYER2!!  ");
	else // Player1과 Player2의 점수가 동점인 경우
		printxy(40, 9, "       DRAW!!        ");

	x = 50, y = 17;
	while (1) {
		int f_color, b_color; // Game Over 출력에 사용될 글씨와 배경 색상
		unsigned char c2; // Game Over 메뉴 선택 시 사용되는 변수

		do {
			f_color = rand() % 15 + 1; // 글씨 색상 랜덤 생성
			b_color = rand() % 15 + 1; // 배경 색상 랜덤 생성
		} while (f_color == b_color); // 글씨와 배경 색상이 같지 않을 때까지 반복
		// 글씨와 배경 색상을 변경하면서 Game Over 틀 테두리 출력
		textcolor(f_color, b_color);
		for (i = 42; i <= 54; i += 2) {
			for (j = 11; j <= 13; j += 2) {
				printxy(i, j, "▤");
			}
		}
		printxy(40, 11, "▨");
		printxy(56, 11, "▧");
		printxy(40, 12, "▥");
		printxy(56, 12, "▥");
		printxy(40, 13, "▧");
		printxy(56, 13, "▨");
		// 글씨 색상을 변경하며 Game Over 출력
		textcolor(f_color, BLACK);
		printxy(42, 12, "**Game Over**");

		// Game Over 메뉴 화면의 경우 메인 화면 출력 방식과 유사하므로 주석 생략
		textcolor(WHITE, BLACK);

		if (y == 17)
			textcolor(BLUE2, BLACK);
		printxy(22, 16, "┌─────────────────────────┐");
		printxy(22, 17, "│                      RESTART                     │");
		printxy(22, 18, "└─────────────────────────┘");
		textcolor(WHITE, BLACK);

		if (y == 21)
			textcolor(RED2, BLACK);
		printxy(22, 20, "┌─────────────────────────┐");
		printxy(22, 21, "│                       EXIT                       │");
		printxy(22, 22, "└─────────────────────────┘");
		textcolor(WHITE, BLACK);

		gotoxy(x, y);
		if (kbhit() == 1) {
			c2 = getch();
			if (c2 == ENTER) {
				break;
			}
			if (c2 == SPECIAL1) {
				c2 = getch();
				switch (c2) {
				case UP:
					if (y == 17)
						y = 21;
					else
						y -= 4;
					break;
				case DOWN:
					if (y == 21)
						y = 17;
					else
						y += 4;
					break;
				}
			}
		}
		Sleep(50);
	}
	if (y == 17) // RESTART 메뉴 선택 시
		goto START; // 게임 재시작
	else { // EXIT 메뉴 선택 시
		cls(BLACK, WHITE); // Game Over 메뉴 화면 지우기
		gotoxy(30, 14); // 종료 시 커서 위치 지정
		return 0; // 프로그램 종료
	}
}
