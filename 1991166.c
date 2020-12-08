// ���α׷��ַ� �� ������Ʈ
// 1991166 ������
// 2�ο� Tetris Battle(��Ʋ ��Ʈ����) ����

// ���� Ÿ��Ʋ & �޴� ȭ��
// PLAY �޴�, RANKING �޴�, EXIT �޴�

// ���� �ߴ� or ����� or ������ ���

// ���� ���� :
// 1. ���� ����(��� �� ��� ���� �ӵ� ����) �� LEVEL
// 2. �÷��̾� ������ ������ ��� �÷��̾���� ���� �� �� SCORE
// 3. ������ ������ ��� ��� �� NEXT
// 4. ���� �� ���� ������ ��� ���� �� �� TUPLE
// 5. ������ ��� ��� �� HOLD
// 6. ������ �� ��� ���� �� �� SENT

// 2�� Play�� ���� ��Ʈ���� ��(10 X 20) 2��
// ����ȭ�� â ũ��� �ʺ� 100, ���� 30�� ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// ���� ����
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

#define ENTER 0xd // �޴� ���� or player �̸� �Է�
#define ESC 0x1b //  ����(���α׷�) ����
#define PAUSE 'p' // ���� �ߴ�

// ��� ����
#define TAB 0x9 // PLAYER1
#define SPACE 0x20 // PLAYER2

// ��� ����
#define HOLD1 'x' // PLAYER1
#define HOLD2 '/' // PLAYER2

#define SPECIAL1 0xe0 // Ư�� Ű�� 0xe0 + key ������ ����

// PLAYER2�� ��� �̵� ���� - ȭ��ǥ
#define UP  0x48 // Up key (0xe0 + 0x48)
#define DOWN 0x50 // Down key (0xe0 + 0x50)
#define LEFT 0x4b // Left key (0xe0 + 0x4b)
#define RIGHT 0x4d // Right key (0xe0 + 0x4d)

// PLAYER1�� ��� �̵� ���� - WASD
#define UP2		'w'
#define DOWN2	's'
#define LEFT2	'a'
#define RIGHT2	'd'

// ��Ʈ���� �ʰ� �پ��� ������ ������ ����
#define B_WIDTH 18 // ���� �ʺ�
#define B_HEIGHT 22 // ���� ����

// ��Ʈ���� ���� �ʺ�� ����
#define M_WIDTH 10 // �� �ʺ�
#define M_HEIGHT 20 // �� ����

#define BOX "��" // ���� �׵θ� ���

// ��ϵ� Player �̸��� ���� ������ ���� ����ü Ÿ�� Rank
typedef struct {
	char player[20]; // Player �̸�
	int score; // ����
} Rank;

// �� �÷��̾��� ���� ���� ��ǥ
int B_X[2] = { 10, 56 };
int B_Y[2] = { 3, 3 };

// 1 ~ 5�� ��� �� �۾� ����
int ranking_color[5] = { RED1, YELLOW1, GREEN1, BLUE1, MAGENTA1 };

// ��Ʈ���� ��� �迭 ����
// ���� �ٸ� 7���� ��� ���� ȸ��(�ð� ����) �� ��� ��� ǥ��
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

char* block_type[2] = { "��", "��" }; // ���߿� �� ���� ���� �ٴڿ� ������ ���� ���� ��� ���
int block_color[7] = { RED1, YELLOW1, GREEN1, CYAN1, BLUE1, MAGENTA1, GRAY1 }; // ���� �ٸ� 7���� ��� ����

// RANKING�� �ʿ��� Player �̸� ���� �迭 
char player1_name[20]; // Player1
char player2_name[20]; // Player2

int map[2][M_HEIGHT + 2][M_WIDTH + 2] = { 0 }; // 2�ο� ��Ʈ���� ��
int map_color[2][M_HEIGHT][M_WIDTH] = { 0 }; // �� �� ��ϵ��� ����
int now[2] = { 0 }; // ���� �̵� ���� ��� ���
int rotate[2] = { 0 }; // ���� �̵� ���� ����� ȸ����
int pos_x[2] = { 0 }; // ���� �̵� ���� ����� ��ġ�� x ��ǥ
int pos_y[2] = { 0 }; // ���� �̵� ���� ����� ��ġ�� y ��ǥ
int level[2] = { 0 }; // ���� ����
int score[2] = { 0 }; // ���� ����
int next[2] = { 0 }; // ���� ��� ���
int tuple[2] = { 0 }; // ���� �� ���� ������ ��� ���� ��
int hold[2] = { 0 }; // ������ ��� ���
int sent[2] = { 0 }; // ���ŵ� �� ��� ���� ��
int new_block_flag[2] = { 0 }; // ���ο� ��� �ʿ� ���� (0 : �ʿ� ����, 1 : �ʿ���)
int game_over[2] = { 0 }; // ���� ���� ���� (0 : ���� ��, 1 : ����)

// ���� ��� �� �ӵ� ����
int frame_count = 0; // ���� �����Ǵ� frame
int p1_frame_sync = 13; // Player1 ó�� ������ 13 frame ���� �̵�
int p2_frame_sync = 13; // Player2 ó�� ������ 13 frame ���� �̵�

void gotoxy(int x, int y) // ���ϴ� ��ġ(��ǥ)�� Ŀ���� �̵������ִ� �Լ�
{
	COORD pos; // windows.h �� ����
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(int fg_color, int bg_color) // �۾��� ��� ������ �������ִ� �Լ�
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

// ���ϴ� ��� �������� ȭ���� �����ִ� �Լ�
void cls(int bg_color, int text_color)
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);

}

void removeCursor(void) { // Ŀ���� ������ �ʵ��� �ϴ� �Լ�
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void printxy(int x, int y, char* str) // ���ϴ� ��ġ(��ǥ)�� ���ڿ��� ������ִ� �Լ�
{
	gotoxy(x, y);
	printf(str);
}

// ���� Ÿ��Ʋ & �޴� ȭ���� ����ϰ� ���õ� �޴��� ��ȯ�ϴ� �Լ�
int show_menu() 
{
	int i = 0, x = 50, y = 19, menu; // x,y : PLAY �޴��� �̵� �� Ŀ�� ��ġ, menu : ���õ� �޴�(1 ~ 3)
	unsigned char ch; // �޴� ���� �� �ԷµǴ� Ű

	// ���� Ÿ��Ʋ ���
	textcolor(CYAN1, CYAN2);
	printxy(23, 4, "������������������������������������������������������");
	printxy(23, 5, "��                                                  ��");
	printxy(23, 6, "��                                                  ��");
	printxy(23, 7, "��                                                  ��");
	printxy(23, 8, "��                                                  ��");
	printxy(23, 9, "��                                                  ��");
	printxy(23, 10, "����������������������          ����������������������");
	printxy(43, 11, "��          ��");
	printxy(43, 12, "��          ��");
	printxy(43, 13, "��          ��");
	printxy(43, 14, "��          ��");
	printxy(43, 15, "��������������");

	textcolor(RED1, BLACK);
	printxy(25, 5, " �����\n");
	printxy(25, 6, "    ��   \n");
	printxy(25, 7, "    ��   \n");
	printxy(25, 8, "    ��   \n");
	printxy(25, 9, "    ��   \n");
	textcolor(YELLOW1, BLACK);
	printxy(34, 5, " ����\n");
	printxy(34, 6, " ��    \n");
	printxy(34, 7, " ����\n");
	printxy(34, 8, " ��    \n");
	printxy(34, 9, " ����\n");
	textcolor(YELLOW2, BLACK);
	printxy(41, 5, " �����\n");
	printxy(41, 6, "    ��   \n");
	printxy(41, 7, "    ��   \n");
	printxy(41, 8, "    ��   \n");
	printxy(41, 9, "    ��   \n");
	textcolor(GREEN1, BLACK);
	printxy(50, 5, " ����  \n");
	printxy(50, 6, " ��   �� \n");
	printxy(50, 7, " ����  \n");
	printxy(50, 8, " ��   �� \n");
	printxy(50, 9, " ��    ��\n");
	textcolor(BLUE2, BLACK);
	printxy(59, 5, " ����\n");
	printxy(59, 6, "   ��  \n");
	printxy(59, 7, "   ��  \n");
	printxy(59, 8, "   ��  \n");
	printxy(59, 9, " ����\n");
	textcolor(MAGENTA2, BLACK);
	printxy(66, 5, "  ���� \n");
	printxy(66, 6, " ��      \n");
	printxy(66, 7, "  ���� \n");
	printxy(66, 8, "       ��\n");
	printxy(66, 9, "  ���� \n");

	// �� �÷��̾��� ��� Ű �ȳ�
	textcolor(GRAY2, BLACK);
	printxy(3, 19, "����< P1 Key >����");
	printxy(3, 20, "��  UP       w  ��");
	printxy(3, 21, "�� DOWN      s  ��");
	printxy(3, 22, "�� LEFT      a  ��");
	printxy(3, 23, "�� RIGHT     d  ��");
	printxy(3, 24, "��DIRECT    Tab ��");
	printxy(3, 25, "�� HOLD      x  ��");
	printxy(3, 26, "������������������");

	printxy(79, 19, "����< P2 Key >����");
	printxy(79, 20, "��  UP      ��  ��");
	printxy(79, 21, "�� DOWN     ��  ��");
	printxy(79, 22, "�� LEFT     ��  ��");
	printxy(79, 23, "�� RIGHT    ��  ��");
	printxy(79, 24, "��DIRECT   SPACE��");
	printxy(79, 25, "�� HOLD      /  ��");
	printxy(79, 26, "������������������");

	// ǥ���� �ٲ�� �ִϸ��̼�
	while (1) {
		textcolor(WHITE, BLACK);
		if (i % 20 < 10) {
			printxy(45, 10, "          \n");
			printxy(45, 11, "  ��  ��  \n");
			printxy(45, 12, " �� �� �� \n");
			printxy(45, 13, "    ��    \n");
			printxy(45, 14, "          \n");
		}
		else {
			printxy(45, 10, "          \n");
			printxy(45, 11, "  >    <  \n");
			printxy(45, 12, " *  ��  * \n");
			printxy(45, 13, "    ��    \n");
			printxy(45, 14, "          \n");
		}
		i++;

		// 3���� ���� �޴� ���(�ش� �޴��� �̵� �� �ٸ� �������� ǥ��)
		if (y == 19)
			textcolor(BLUE2, BLACK);
		printxy(23, 18, "������������������������������������������������������");
		printxy(23, 19, "��                       PLAY                       ��");
		printxy(23, 20, "������������������������������������������������������");
		textcolor(WHITE, BLACK);

		if (y == 22)
			textcolor(GREEN2, BLACK);
		printxy(23, 21, "������������������������������������������������������");
		printxy(23, 22, "��                      RANKING                     ��");
		printxy(23, 23, "������������������������������������������������������");
		textcolor(WHITE, BLACK);

		if (y == 25)
			textcolor(RED2, BLACK);
		printxy(23, 24, "������������������������������������������������������");
		printxy(23, 25, "��                       EXIT                       ��");
		printxy(23, 26, "������������������������������������������������������");
		textcolor(WHITE, BLACK);

		gotoxy(x, y); // ó�� Ŀ�� ��ġ�� PLAY �޴�
		if (kbhit() == 1) {  // Ű���尡 ������ ���� ���
			ch = getch();
			if (ch == ENTER) { // ENTER ������ �޴� ����
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
				return menu; // �޴� ���õǸ� ��ȯ
			}
			// �ٸ� �޴��� �̵�
			if (ch == SPECIAL1) { // Ư�� Ű�� ������ �ִ� ���
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

// ���� ������ ����ϴ� �Լ�
void show_level(int player)
{
	// ���� ���� ��� ��ġ ����
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

// ���� ������ ����ϴ� �Լ�
void show_score()
{
	// Player1 ���� ���
	gotoxy(36, 7);
	printf("%7d", score[0]);

	// Player2 ���� ���
	gotoxy(82, 7);
	printf("%7d", score[1]);

	// Player1�� Player2�� ���� �� ���
	if (score[0] > score[1]) { // Player1�� ������ �� ���� ���
		// Player1
		gotoxy(34, 8);
		printf("(+%7d)", score[0] - score[1]);

		// Player2
		gotoxy(80, 8);
		printf("(-%7d)", score[0] - score[1]);
	}
	else if (score[0] == score[1]) { // �� ������ ���� ���
		// Player1
		gotoxy(34, 8);
		printf("(+%7d)", 0);

		// Player2
		gotoxy(80, 8);
		printf("(+%7d)", 0);
	}
	else { // Player2�� ������ �� ���� ���
		// Player1
		gotoxy(34, 8);
		printf("(-%7d)", score[1] - score[0]);

		// Player2
		gotoxy(80, 8);
		printf("(+%7d)", score[1] - score[0]);
	}
}

// ���� ��� ����� ����ϴ� �Լ�
void show_next(int player)
{
	int i, j, x, y;

	// ���� ��� ��� ��� ��ġ ����
	switch (player) {
	case 0: // Player1
		if (next[player] == 3) { // ���� ��� ����� ���簢�� ����� ���
			x = 37;
			y = 10;
		}
		else if (next[player] == 6) { // ���� ��� ����� ����� ����� ���
			x = 35;
			y = 10;
		}
		else { // ���� ��� ����� ������ ����� ���
			x = 36;
			y = 10;
		}
		break;
	case 1: // Player2
		if (next[player] == 3) { // ���� ��� ����� ���簢�� ����� ���
			x = 83;
			y = 10;
		}
		else if (next[player] == 6) { // ���� ��� ����� ����� ����� ���
			x = 81;
			y = 10;
		}
		else { // ���� ��� ����� ������ ����� ���
			x = 82;
			y = 10;
		}
		break;
	}

	// ������ ���� ��� ��� ����� 
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

	// ���� ��� ��� ���
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

// ���� �� ���� ������ ��� ���� ���� ����ϴ� �Լ�
void show_tuple(int player)
{
	// ���� �� ���� ������ ��� ���� �� ��� ��ġ ����
	switch (player) {
	case 0: // Player1
		gotoxy(35, 16);
		break;
	case 1: // Player2
		gotoxy(81, 16);
		break;
	}
	if (tuple[player]) { // ���� ������ ��� ������ �ϳ� �̻��� ���
		switch (tuple[player]) {
		case 1:
			printf(" SINGLE  "); // ������ ��� ���� 1��
			break;
		case 2:
			printf(" DOUBLE  "); // ������ ��� ���� 2��
			break;
		case 3:
			printf(" TRIPLE  "); // ������ ��� ���� 3��
			break;
		case 4:
			printf("QUADRUPLE"); // ������ ��� ���� 3��
			break;
		}
		Sleep(500); // ��� ��� ����
		printf("\b\b\b\b\b\b\b\b\b         "); // �ش� ĭ ����
		tuple[player] = 0; // ���� �� ���� ������ ��� ���� �� 0���� �ٽ� �ǵ�����
	}
}

// ������ ��� ����� ����ϴ� �Լ�
void show_hold(int player)
{
	int i, j, x, y;

	// ������ ��� ��� ��� ��ġ ����
	switch (player) {
	case 0: // Player1
		if (hold[player] == 3) { // ������ ��� ����� ���簢�� ����� ���
			x = 37;
			y = 18;
		}
		else if (hold[player] == 6) { // ������ ��� ����� ����� ����� ���
			x = 35;
			y = 18;
		}
		else { // ������ ��� ����� ������ ����� ���
			x = 36;
			y = 18;
		}
		break;
	case 1: // Player2
		if (hold[player] == 3) { // ������ ��� ����� ���簢�� ����� ���
			x = 83;
			y = 18;
		}
		else if (hold[player] == 6) { // ������ ��� ����� ����� ����� ���
			x = 81;
			y = 18;
		}
		else { // ������ ��� ����� ������ ����� ���
			x = 82;
			y = 18;
		}
		break;
	}

	// ������ �����ƴ� ��� ��� �����
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

	// ������ ��� ��� ���
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

// ������ �� ��� ���� ���� ����ϴ� �Լ�
void show_sent(int player)
{
	// ������ �� ��� ���� �� ��� ��ġ ����
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

int start_star = 0; // ���� ���� �� �� �ӿ��� ���� �����̴� �ִϸ��̼��� �ֱ� ���� ����

int box[B_HEIGHT][B_WIDTH] = { // ��Ʈ���� ���� ������ ���� ����
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

// ch ���ڿ��� ��Ʈ���� ���� ������ ���ڸ� �׷��ִ� �Լ�
// �� ������ �� �� ��ǥ�� �ѱ� ���� ����� ���� ���ڿ��� �Ű������� ����
void draw_box(int x1, int y1, int x2, int y2, char* ch)
{
	int i = 0, x, y;

	while (1) { // ���� ���� �� ���� �����̴� ���� ���ڸ� �ݺ��Ͽ� �׸���
		for (y = 0; y < B_HEIGHT; y++) {
			for (x = 0; x < B_WIDTH; x++) {
				// Player1
				// �� ���� Player1 ���
				gotoxy(x1 + 15, y1 - 2);
				printf("Player1");
				// Player1 ���� �׸���
				gotoxy(x * 2 + x1, y + y1);
				switch (box[y][x]) {
				case 0: // �� ��
					// ���� ���� �� ���� �����̴� �ִϸ��̼� ����
					if (start_star % 2)
						printf("**"); 
					else
						printf("  ");
					break;
				case 2: // ���� �׵θ�
					printf("%s", ch);
					break;
				case 3: // ���� ���� ��� ĭ
					printf("<LEVEL> ");
					break;
				case 4: // ���� ���� ��� ĭ
					printf("<SCORE> ");
					break;
				case 5: // ���� ��� ��� ��� ĭ
					printf("<NEXT>");
					break;
				case 6: // ���� �� ���� ������ ��� ���� �� ��� ĭ
					printf("<TUPLE> ");
					break;
				case 7: // ������ ��� ��� ��� ĭ
					printf("<HOLD>");
					break;
				case 8: // ������ �� ��� ���� �� ��� ĭ
					printf("<SENT>");
					break;
				default: // 9�� ��� ��� �α� 
					break;
				}
				// Player2
				// �� ���� Player2 ���
				gotoxy(x2 + 15, y2 - 2);
				printf("Player2");
				gotoxy(x * 2 + x2, y + y2);
				// Player2 ���� �׸���
				switch (box[y][x]) { 
				case 0: // �� ��
				// ���� ���� �� ���� �����̴� �ִϸ��̼� ����
					if (start_star % 2)
						printf("**");
					else
						printf("  ");
					break;
				case 2: // ���� �׵θ�
					printf("%s", ch);
					break;
				case 3: //���� ���� ��� ĭ
					printf("<LEVEL> ");
					break;
				case 4: // ���� ���� ��� ĭ
					printf("<SCORE> ");
					break;
				case 5: // ���� ��� ��� ��� ĭ
					printf("<NEXT>");
					break;
				case 6: // ���� �� ���� ������ ��� ���� �� ��� ĭ
					printf("<TUPLE> ");
					break;
				case 7: // ������ ��� ��� ��� ĭ
					printf("<HOLD>");
					break;
				case 8: // ������ �� ��� ���� �� ��� ĭ
					printf("<SENT>");
					break;
				default: // 9�� ��� ��� �α� 
					break;
				}
			}
		}
		if (start_star < 4) // ���� �����̴� Ƚ�� ����
			start_star++;
		else // �� �ӿ��� ���� �������� �ʰ� ����� ����
			break;
		Sleep(100);
	}

	// ���� ������ �˸�
	textcolor(RED2, CYAN2);
	i = 0;
	while (i < 10) {
		printxy(49, 12, "Game");
		printxy(48, 13, "Start!");
		i++;
		Sleep(100); // ��� ��� ����
	}

	// ���� �˸� ǥ�� �����
	textcolor(WHITE, BLACK);
	printxy(49, 12, "    ");
	printxy(48, 13, "      ");
}

// ���� ���� ���¸� �ʱ�ȭ�ϴ� �Լ�
// ���� ���� or �����
void init_game()
{
	int i, j;
	start_star = 0; // ���� �����̹Ƿ� ������� ��� �ٽ� 0���� �ʱ�ȭ

	cls(BLACK, WHITE); // ���� ȭ�� �����
	// Player1�� Player2 �̸� �Է� �ޱ�
	textcolor(YELLOW1, BLACK);
	printxy(40, 11, "Enter your name (20)");
	textcolor(GRAY2, BLACK);
	printxy(22, 23, "(�ѱ� ��� �� ���� ���� ���� ��/�� Ű�� �ٽ� �����ּ���.)"); // ���� �� ���� Ű�� ����ϱ� ����
	textcolor(WHITE, BLACK);
	// Player1
	printxy(39, 14, "Player1 : ");
	printxy(35, 15, "����������������������������");
	gotoxy(51, 14);
	scanf(" %[^\n]s", player1_name); // ENTER�� ������ ������ ���� ���� �̸� �Է� �ޱ�
	// Player2
	printxy(39, 17, "Player2 : ");
	printxy(35, 18, "����������������������������");
	gotoxy(51, 17);
	scanf(" %[^\n]s", player2_name);  // ENTER�� ������ ������ ���� ���� �̸� �Է� �ޱ�

	// Player1�� Player2�� ��Ʈ���� �� ����
	for (i = 0; i < M_HEIGHT + 2; i++) {
		for (j = 0; j < M_WIDTH + 2; j++)
			map[0][i][j] = map[1][i][j] = box[i][j];
	}

	// Player1�� Player2�� ��Ʈ���� �� �� ��� ���� �ʱ�ȭ
	for (i = 0; i < M_HEIGHT; i++) {
		for (j = 0; j < M_WIDTH; j++)
			map_color[0][i][j] = map_color[1][i][j] = BLACK;
	}

	srand(time(NULL)); // rand() ��� ����
	// ���� �̵� ���� ��� ��� ���� ����
	now[0] = rand() % 7; // Player1
	now[1] = rand() % 7; // Player2
	rotate[0] = rotate[1] = 0; // Player1�� Player2�� ���� �̵� ���� ��� ȸ���� ȸ������ ���� ���·� �ʱ�ȭ
	// ���� �̵� ���� ����� ��Ÿ�� ��ġ ����
	pos_x[0] = pos_x[1] = 4; // Player1�� Player2�� ���� �̵� ���� ����� x ��ǥ�� �ʱ�ȭ
	pos_y[0] = pos_y[1] = 0; // Player1�� Player2�� ���� �̵� ���� ����� y ��ǥ�� �ʱ�ȭ
	level[0] = level[1] = 1; // Player1�� Player2�� ���� ���� 1�� �ʱ�ȭ
	score[0] = score[1] = 0; // Player1�� Player2�� ���� ���� 0���� �ʱ�ȭ
	tuple[0] = tuple[1] = 0; // Player1�� Player2�� ���� �� ���� ������ ��� ���� �� 0���� �ʱ�ȭ
	// ���� ��� ��� ���� ����
	next[0] = rand() % 7; // Player1
	next[1] = rand() % 7; // Player2
	hold[0] = hold[1] = -1; // Player1�� Player2�� ������ ��� ����� �����Ƿ� -1�� �ʱ�ȭ
	sent[0] = sent[1] = 0; // Player1�� Player2�� ������ �� ��� ���� �� 0���� �ʱ�ȭ
	new_block_flag[0] = new_block_flag[1] = 0; // Player1�� Player2�� ���ο� ����� �ʿ����� �����Ƿ� 0���� �ʱ�ȭ
	game_over[0] = game_over[1] = 0; // Player1�� Player2�� ������ ���۵Ǿ����Ƿ� 0���� �ʱ�ȭ

	frame_count = 0; // ������ ���۵ǹǷ� frame 0���� �ʱ�ȭ
	p1_frame_sync = 13; // ������ ���۵ǹǷ� Player1 sync 13���� �ʱ�ȭ
	p2_frame_sync = 13; // ������ ���۵ǹǷ� Player2 sync 13���� �ʱ�ȭ

	cls(BLACK, WHITE); // Player �̸� �Է� ȭ�� �����
	draw_box(B_X[0], B_Y[0], B_X[1], B_Y[1], BOX); // Player1�� Player2�� ���� �׸���
	show_level(0); show_level(1); // Player1�� Player2�� ���� ���� ���
	show_score(); // Player1�� Player2�� ���� ������ ������ ���� �� ���
	show_next(0); show_next(1); // Player1�� Player2�� ���� ��� ��� ���
	show_sent(0); show_sent(1); // Player1�� Player2�� ������ �� ��� ���� �� ���
}

// ��Ʈ���� �� �ӿ� ���� �̵� ���� ����� �׷��ִ� �Լ�
// ����� ���߿� �� ���� ���� �ٴڿ� �����Ͽ��� ���� �����ϱ� ���� ��� ��� Ÿ���� �Ű������� ����
void show_block(int player, int type) {
	int i, j;

	// ���� �̵� ���� ��� �׸���
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

// ��Ʈ���� �� �� ���� �̵� ���� ����� ���� ��ġ���� �����ִ� �Լ�
void erase_block(int player) {
	int i, j;

	// ���� �̵� ���� ��� ���� ��ġ���� �����
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			gotoxy(B_X[player] + (pos_x[player] + j) * 2, B_Y[player] + pos_y[player] + i);
			if (BLOCK[now[player]][rotate[player]][i][j])
				printf("  ");
		}
	}
}

// ��Ʈ���� �� �ӿ��� Ư�� ��ġ�� ����� ������ �� �ִ��� �Ǵ��ϴ� �Լ� (0 : �Ұ���, 1 : ����)
// ȸ�� �ÿ��� �˻��� �� �ֵ��� ȸ������ �Ű������� ����
int can_move(int player, int rotate, int x, int y) {
	int i, j;

	// ���� �̵� ���� ��� ���� �� �� ä���� �κ��� ��ĥ ��� 0�� ��ȯ
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (BLOCK[now[player]][rotate][i][j]) {
				if (map[player][y + i][x + j])
					return 0;
			}
		}
	}
	return 1; // ���� �̵� ���� ��� ���� �� �� ä���� �κ��� ��ġ�� ������ 1�� ��ȯ
}

// ���� �̵� ���� ����� �ٴڿ� �����Ͽ��� �� ��� ������ ������� Ȯ�� ��
// ��� ������ �����ϸ� ��� ������ ��� �������ִ� �Լ�
void remove_line(int player) {
	// count : ���� �� ���� ������ ��� ���� ���� ���� ���� ����
	// old_level : ���� ������ ����Ͽ����� Ȯ���ϱ� ���� ���� ���� ���� ����
	int i, j, k, l, m, count = 0, old_level;

	// ���� �̵� ���� ����� �ٴڿ� �����Ͽ��� �� �� �� �ش� ����� ��ġ�� �ش� ����� ���� ����
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (BLOCK[now[player]][rotate[player]][i][j])
				map_color[player][pos_y[player] + i - 1][pos_x[player] + j - 1] = now[player];
		}
	}

	// ��� ������ �����ϴ��� Ȯ�� �� �����ϸ� ��� ���� ��� ����
	for (i = M_HEIGHT; i >= 1; i--) { // ���� 1��(���� �Ʒ�)���� Ȯ��
		// ��� ������ ��������� ���ؼ��� �ش� ���� �� ������ ����� ��
		for (j = 1; j <= M_WIDTH; j++) {
			if (!map[player][i][j])
				break;
		}
		// �ش� ���� �� ������ ���� ��� �ش� ���� ��� ���� ����
		if (map[player][i][j]) {
			// �� �� ä���� ����� �� ���� ������ 
			for (k = i; k >= 2; k--) {
				for (j = 1; j <= M_WIDTH; j++) {
					map[player][k][j] = map[player][k - 1][j];
					map_color[player][k - 1][j - 1] = map_color[player][k - 2][j - 1];
				}
			}
			// �� ���� ��� ����
			for (l = 1; l <= M_HEIGHT; l++) {
				for (m = 1; m <= M_WIDTH; m++) {
					gotoxy(m * 2 + B_X[player], l + B_Y[player]);
					printf("  ");
				}
			}
			// �� �� ä���� ����� �ٽ� �׷��ֱ�
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
			count++; // ���� �� ���� ������ ��� ���� �� ����
			i++; // �ش� ���� ����� ���� �����Ա� ������ ��� ������ �����ϴ��� �ٽ� �� �� �˻� 
		}
	}

	tuple[player] = count; // ���� �� ���� ������ ��� ���� �� ����
	sent[player] += count; // ������ �� ���� ���� ���� �� ���� ������ ��� ���� �� ����

	// ���� ������ ���� �� ���� ������ ��� ���� ���� ���� �߰��Ǵ� ������ �ٸ����� ����
	switch (count) {
	case 0: // ���� �� ���� ������ ��� ���� �� 0���� ���
		// �߰� ���� ����
		break;
	case 1: // ���� �� ���� ������ ��� ���� �� 1���� ���
		score[player] += 40 * level[player]; // (���� ���� * 40)�� �߰�
		break;
	case 2: // ���� �� ���� ������ ��� ���� �� 2���� ���
		score[player] += 100 * level[player]; // (���� ���� * 100)�� �߰�
		break;
	case 3: // ���� �� ���� ������ ��� ���� �� 3���� ���
		score[player] += 300 * level[player]; // (���� ���� * 300)�� �߰�
		break;
	case 4: // ���� �� ���� ������ ��� ���� �� 4���� ���
		score[player] += 1200 * level[player]; // (���� ���� * 1200)�� �߰�
		break;
	}

	old_level = level[player]; // ���� ���� ���� ����

	// ���� ���� ���� ����
	// ���� ������ ������ �� ��� ���� ���� ���� ����
	if (sent[player] >= 0 && sent[player] <= 9) // ������ �� ��� ���� ���� �� �ڸ����� ���
		level[player] = 1; // ���� ���� 1
	else if (sent[player] >= 10 && sent[player] <= 19) // ������ �� ��� ���� ���� ���� �ڸ��� 1�� ���
		level[player] = 2; // ���� ���� 2
	else if (sent[player] >= 20 && sent[player] <= 29) // ������ �� ��� ���� ���� ���� �ڸ��� 2�� ���
		level[player] = 3; // ���� ���� 3
	else if (sent[player] >= 30 && sent[player] <= 39) // ������ �� ��� ���� ���� ���� �ڸ��� 3�� ���
		level[player] = 4; // ���� ���� 4
	else if (sent[player] >= 40 && sent[player] <= 49) // ������ �� ��� ���� ���� ���� �ڸ��� 4�� ���
		level[player] = 5; // ���� ���� 5
	else if (sent[player] >= 50 && sent[player] <= 59) // ������ �� ��� ���� ���� ���� �ڸ��� 5�� ���
		level[player] = 6; // ���� ���� 6
	else if (sent[player] >= 60 && sent[player] <= 69) // ������ �� ��� ���� ���� ���� �ڸ��� 6�� ���
		level[player] = 7; // ���� ���� 7
	else if (sent[player] >= 70 && sent[player] <= 79) // ������ �� ��� ���� ���� ���� �ڸ��� 7�� ���
		level[player] = 8; // ���� ���� 8
	else if (sent[player] >= 80 && sent[player] <= 89) // ������ �� ��� ���� ���� ���� �ڸ��� 8�� ���
		level[player] = 9; // ���� ���� 9
	else if (sent[player] >= 90 && sent[player] <= 99) // ������ �� ��� ���� ���� ���� �ڸ��� 9�� ���
		level[player] = 10; // ���� ���� 10

	if (level[player] > old_level) { // ���� ������ ����Ͽ��� ���
		if (player == 0) // Player1
			p1_frame_sync--; // Player1 sync 1 ����
		else // Player2
			p2_frame_sync--; // Player2 sync 1 ����
	}

	show_level(player); // ���� ���� ���
	show_score(); // ���� ������ ������ ���� �� ���
	show_tuple(player); // ���� �� ���� ������ ��� ���� �� ���
	show_sent(player); // ������ �� ��� ���� �� ���

	if (score[player] >= 10000000) // ������ ���� �ӿ� ����� �� �ִ� ������ �ʰ��� ���
		game_over[player] = 1; // ���� ����
}

// ������ ����Ǹ� �� ���� ������ �ʵ��� �����ִ� �Լ�
void cover_map(int player) {
	int i, j;

	// �� ���� ������ �ʵ��� �����ֱ�
	textcolor(GRAY2, BLACK);
	for (i = 1; i < M_HEIGHT + 1; i++) {
		for (j = 1; j < M_WIDTH + 1; j++) {
			gotoxy(j * 2 + B_X[player], i + B_Y[player]);
			printf("��");
		}
	}
}

// Player1�� ������ �����ϴ� ���� �ݺ������� ȣ��Ǵ� �Լ�
// Player1�� ���õ� Ű�� ������ ���� ��� ���� �̵� ���� ����� �̵� ���� �Ǵ� ���� ����
// ���� �̵� ���� ����� �� �� �����;� �ϴ��� Ȯ�� �� ������ ����ϸ� ����
// ���� �̵� ���� ����� �ٴڿ� �����Ͽ��� �� ���ο� ����� �����Ͽ� ���� �̵� ���� ������� ����
void player1(unsigned char ch)
{
	int i, j, temp; // temp : ���� �̵� ���� ��ϰ� ������ ����� ���� �ٲٱ� ���� �ʿ��� ����

	// ���� �̵� ���� ��� �����
	// �� ���� ���ο� ����� ó�� ��Ÿ���� ��ġ�� �̹� �����ϴ� ��ϰ� ��ġ�� �κ��� ���� ���
	for (i = 1; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (BLOCK[now[0]][rotate[0]][i][j]) {
				if (map[0][i][4 + j])
					break;
			}
		}
	}
	// ���� �̵� ���� ����� ��ġ�� �״�� ����
	if (BLOCK[now[0]][rotate[0]][i][j] && map[0][i][4 + j]) {
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (BLOCK[now[0]][rotate[0]][i][j])
					map[0][pos_y[0] + i][pos_x[0] + j] = 1;
			}
		}
		show_block(0, 1);
	}

	// �� �ӿ��� ���ο� ����� ó�� ��Ÿ���� ��ġ�� �̹� ����� ä���� ������ ���� ���� 
	for (i = 1; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (map[0][i][4 + j]) { // �� �ӿ��� ���ο� ����� ó�� ��Ÿ���� ��ġ�� �̹� ����� ä���� ���� ���
				game_over[0] = 1; // ���� ����
				cover_map(0); // �� ���� ������ �ʵ��� �����ֱ�
				return; // �ش� �Լ� ����
			}
		}
	}

	if (new_block_flag[0]) { // ���ο� ��� ������ �ʿ��� ���
		now[0] = next[0]; // ���� ��� ����� ���� �̵� ���� ��� ������� ����
		rotate[0] = 0; // ���� �̵� ���� ����� ȸ������ 0���� �ʱ�ȭ

		// ���ο� ����� ó�� ��Ÿ�� ��ġ ����
		pos_x[0] = 4; // ���ο� ����� ó�� ��Ÿ�� ��ġ�� x ��ǥ
		pos_y[0] = 0; // ���ο� ����� ó�� ��Ÿ�� ��ġ�� y ��ǥ

		next[0] = rand() % 7; // ���� ��� ����� ���� ����
		show_next(0); // ���� ��� ��� ���
		show_block(0, 0); // ���� �̵� ���� ��� �׸���
		new_block_flag[0] = 0; // ���ο� ��� ������ �ʿ����� ����
	}

	if (ch) { // Player1�� ���õ� Ű�� ������ ���� ��� 
		switch (ch) {
		case UP2: // �ð� �������� ���� �̵� ���� ��� ȸ���� �����ϸ� ����
			// �ð� �������� ���� �̵� ���� ��� ȸ���� ������ ���
			if (can_move(0, (rotate[0] + 1) % 4, pos_x[0], pos_y[0])) {
				erase_block(0); // ���� �̵� ���� ����� ���� ��ġ���� ����� 
				rotate[0] = (rotate[0] + 1) % 4; // �ð� �������� ���� �̵� ���� ��� ȸ��
				show_block(0, 0); // ���� �̵� ���� ��� �׸���
			}
			break;
		case DOWN2: // ���� �̵� ���� ����� �� �� ������ �� ������ ����
			// ���� �̵� ���� ����� �� �� ������ �� ���� ��� 
			if (can_move(0, rotate[0], pos_x[0], pos_y[0] + 1)) {
				erase_block(0); // ���� �̵� ���� ����� ���� ��ġ���� �����
				pos_y[0]++; // ���� �̵� ���� ��� ��ġ�� y ��ǥ �� 1 ����
				show_block(0, 0); // ���� �̵� ���� ��� �׸���
			}
			else { // ���� �̵� ���� ����� �ٴڿ� �����Ͽ��� ��� 
				show_block(0, 1); // �̵��ϴ� ����� ���� �����Ͽ� ���
				// ���� �̵� ���� ����� ��ġ�� �״�� ����
				for (i = 0; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						if (BLOCK[now[0]][rotate[0]][i][j])
							map[0][pos_y[0] + i][pos_x[0] + j] = 1;
					}
				}
				remove_line(0); // ��� ������ ������� Ȯ�� �� �����ϸ� ��� ����

				// �� �ӿ��� ���ο� ����� ó�� ��Ÿ���� ��ġ�� �̹� ����� ä���� ������ ���� ����
				for (i = 1; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						// �� �ӿ��� ���ο� ����� ó�� ��Ÿ���� ��ġ�� �̹� ����� ä���� ���� ���
						if (map[0][i][4 + j]) { 
							game_over[0] = 1; // ���� ����
							cover_map(0); // �� ���� ������ �ʵ��� �����ֱ�
							return; // �ش� �Լ� ����
						}
					}
				}
				// �� �ӿ��� ���ο� ����� ó�� ��Ÿ���� ��ġ�� ä���� ����� ���� ���
				new_block_flag[0] = 1; // ���ο� ��� ���� �ʿ��� 
			}
			break;
		case LEFT2: // ���� �̵� ���� ����� �������� �� ĭ �̵��� �� ������ ����
			// ���� �̵� ���� ����� �������� �� ĭ �̵��� �� ���� ���
			if (can_move(0, rotate[0], pos_x[0] - 1, pos_y[0])) {
				erase_block(0); // ���� �̵� ���� ����� ���� ��ġ���� �����
				pos_x[0]--; // ���� �̵� ���� ��� ��ġ�� x ��ǥ �� 1 ����
				show_block(0, 0); // ���� �̵� ���� ��� �׸���
			}
			break;
		case RIGHT2: // ���� �̵� ���� ����� ���������� �� ĭ �̵��� �� ������ ����
			// ���� �̵� ���� ����� ���������� �� ĭ �̵��� �� ���� ���
			if (can_move(0, rotate[0], pos_x[0] + 1, pos_y[0])) {
				erase_block(0); // ���� �̵� ���� ����� ���� ��ġ���� �����
				pos_x[0]++; // ���� �̵� ���� ��� ��ġ�� x ��ǥ �� 1 ����
				show_block(0, 0); // ���� �̵� ���� ��� �׸���
			}
			break;
		case TAB: // ���� �̵� ���� ����� �����Ͽ� �ٴڿ� �����ϵ��� ��
			// ���� �̵� ���� ����� �� �� ������ �� ���� ������
			while (can_move(0, rotate[0], pos_x[0], pos_y[0] + 1)) {
				erase_block(0); // ���� �̵� ���� ����� ���� ��ġ���� �����
				pos_y[0]++; // ���� �̵� ���� ��� ��ġ�� y ��ǥ �� 1 ����
				show_block(0, 0); // ���� �̵� ���� ��� �׸���
			}
			show_block(0, 1); // �̵��ϴ� ����� ���� �����Ͽ� ���
			// ���� �̵� ���� ����� ��ġ�� �״�� ����
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					if (BLOCK[now[0]][rotate[0]][i][j])
						map[0][pos_y[0] + i][pos_x[0] + j] = 1;
				}
			}
			remove_line(0); // ��� ������ ������� Ȯ�� �� �����ϸ� ��� ����

			// �� �ӿ��� ���ο� ����� ó�� ��Ÿ���� ��ġ�� �̹� ����� ä���� ������ ���� ����
			for (i = 1; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					// �� �ӿ��� ���ο� ����� ó�� ��Ÿ���� ��ġ�� �̹� ����� ä���� ���� ���
					if (map[0][i][4 + j]) {
						game_over[0] = 1; // ���� ����
						cover_map(0); // �� ���� ������ �ʵ��� �����ֱ�
						return; // �ش� �Լ� ����
					}
				}
			}
			// �� �ӿ��� ���ο� ����� ó�� ��Ÿ���� ��ġ�� ä���� ����� ���� ���
			new_block_flag[0] = 1; // ���ο� ��� ���� �ʿ���
			break;
		case HOLD1: // ���� �̵� ���� ����� �����ϰ� �����Ǿ� �ִ� ����� �ִٸ� �ٽ� ���� ���
			if (hold[0] == -1) { // �����Ǿ� �ִ� ����� ���� ���
				erase_block(0); // ���� �̵� ���� ����� ���� ��ġ���� �����
				hold[0] = now[0]; // �̵��ϴ� ����� ����
				new_block_flag[0] = 1; // �̵��� ����� �־�� �ϹǷ� ���ο� ��� ���� �ʿ���
			}
			else { // �����Ǿ� �ִ� ����� ���� ���
				erase_block(0); // ���� �̵� ���� ����� ���� ��ġ���� �����
				// ���� �̵� ���� ��ϰ� �����Ǿ� �ִ� ��� �ٲٱ�
				temp = now[0];
				now[0] = hold[0];
				hold[0] = temp;
				rotate[0] = 0; // ���� �̵� ���� ����� ȸ���� 0���� �ʱ�ȭ
				// ���� �̵� ���� ����� ��ġ���� �ٲ� ����� ����� �� ���� ��� 
				if (!can_move(0, rotate[0], pos_x[0], pos_y[0])) {
					while (1) {
						if (pos_x[0] < 5) // ���� �̵� ���� ��� ��ġ�� x ��ǥ ���� 5���� ���� ���
							pos_x[0]++; // ���� �̵� ���� ��� ��ġ�� x ��ǥ �� 1 ����
						else // ���� �̵� ���� ��� ��ġ�� x ��ǥ ���� 5���� Ŭ ��� 
							pos_x[0]--; // ���� �̵� ���� ��� ��ġ�� x ��ǥ �� 1 ����
						// ���� �̵� ���� ����� ��ġ���� �ٲ� ����� ����� ������ ���
						if (can_move(0, rotate[0], pos_x[0], pos_y[0]))
							break; // while�� ��������
					}
				}
				show_block(0, 0); // ���� �̵� ���� ��� �׸���
			}
			show_hold(0); // ������ ��� ��� ���
			break;
		}
	}

	if (frame_count % p1_frame_sync == 0) { // frame_count�� frame_sync�� �������� �� �������� 0�� ���
		// ���� �̵� ���� ����� �� �� ������ �� ���� ��� 
		if (can_move(0, rotate[0], pos_x[0], pos_y[0] + 1)) {
			erase_block(0); // ���� �̵� ���� ����� ���� ��ġ���� �����
			pos_y[0]++; // ���� �̵� ���� ��� ��ġ�� y ��ǥ �� 1 ����
			show_block(0, 0); // ���� �̵� ���� ��� �׸���
		}
		else {
			if (new_block_flag[0] == 0) { // ���� ��Ȳ�� �̹� ó������ �ʾ��� ���
				show_block(0, 1); // �̵��ϴ� ����� ���� �����Ͽ� ���
				// ���� �̵� ���� ����� ��ġ�� �״�� ����
				for (i = 0; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						if (BLOCK[now[0]][rotate[0]][i][j])
							map[0][pos_y[0] + i][pos_x[0] + j] = 1;
					}
				}
				remove_line(0); // ��� ������ ������� Ȯ�� �� �����ϸ� ��� ����

				// �� �ӿ��� ���ο� ����� ó�� ��Ÿ���� ��ġ�� �̹� ����� ä���� ������ ���� ����
				for (i = 1; i < 4; i++) {
					for (j = 0; j < 4; j++) {
						// �� �ӿ��� ���ο� ����� ó�� ��Ÿ���� ��ġ�� �̹� ����� ä���� ���� ���
						if (map[0][i][4 + j]) {
							game_over[0] = 1; // ���� ����
							cover_map(0); // �� ���� ������ �ʵ��� �����ֱ�
							return; // �ش� �Լ� ����
						}
					}
				}
				// �� �ӿ��� ���ο� ����� ó�� ��Ÿ���� ��ġ�� ä���� ����� ���� ���
				new_block_flag[0] = 1; // ���ο� ��� ���� �ʿ���
			}
		}
	}
}

// Player2�� ������ �����ϴ� ���� �ݺ������� ȣ��Ǵ� �Լ�
// Player1�� ���� ������� �۵��ϹǷ� �ּ� ����
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

// 2�ο� ��Ʋ ��Ʈ���� ���� ���α׷��� ���� �Լ�
// �޴� ���ÿ� ���� ���� ����
int main()
{
	int i, j, x, y, menu; // x, y : �ٸ� �޴��� �̵� �� Ŀ�� ��ġ, menu : ���õ� �޴�(1 ~3)
	unsigned char ch; // Ű�� �Է� �� ���Ǵ� ����

	Rank ranking[128]; // Player�� �̸��� ���� ������ ���� ����ü ����

	removeCursor(); // ��Ʈ���� ������ ����Ǵ� �������� Ŀ���� ������ �ʵ��� ��

	menu = show_menu(); // show_menu�� ��ȯ���� ���õ� �޴� ��ȣ

	// ���õ� �޴��� ���� ���� ����
	if (menu == 1) { // PLAY �޴� ���� ��
	START: // ������� ���� 
		init_game(); // ���� ���� ���¸� �ʱ�ȭ

		while (!game_over[0] || !game_over[1]) // Player1�� Player2 ����� ������ ������ ������ �ݺ�
		{
			if (kbhit() == 1) {  // Ű���尡 ������ ���� ���
				char c1;
				c1 = getch(); // Ű ���� �д´�
				if (c1 == '\0') // VS �� NULL ���� Error
					continue;
				else
					ch = c1;
				// ESC ������ ���α׷� ����
				if (ch == ESC) {
					cls(BLACK, WHITE); // ȭ�� �����
					gotoxy(30, 14); // ���� �� Ŀ�� ��ġ ����
					return 0; // ���α׷� ����
				}
				// 'p' ������ ���� �ߴ�
				if (ch == PAUSE) {
					// PAUSED �޴� ȭ���� ��� ���� �޴� ȭ��� ��� ����� �����ϹǷ� �ּ� ����
					unsigned char c2;
					x = 50, y = 13;
					cls(BLACK, WHITE);
					textcolor(MAGENTA2, YELLOW2);
					printxy(47, 7, "PAUSED");
					while (1) {
						textcolor(WHITE, BLACK);

						if (y == 13)
							textcolor(BLUE2, BLACK);
						printxy(22, 12, "������������������������������������������������������");
						printxy(22, 13, "��                       RESUME                     ��");
						printxy(22, 14, "������������������������������������������������������");
						textcolor(WHITE, BLACK);

						if (y == 18)
							textcolor(GREEN2, BLACK);
						printxy(22, 17, "������������������������������������������������������");
						printxy(22, 18, "��                       RETRY                      ��");
						printxy(22, 19, "������������������������������������������������������");
						textcolor(WHITE, BLACK);

						if (y == 23)
							textcolor(RED2, BLACK);
						printxy(22, 22, "������������������������������������������������������");
						printxy(22, 23, "��                       EXIT                       ��");
						printxy(22, 24, "������������������������������������������������������");
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
					if (y == 13) { // RESUME �޴� ���� �� �����ϴ� ���� �ٽ� ����
						cls(BLACK, WHITE); // PAUSE �޴� ȭ�� �����
						// Player1�� Player2�� ���� �ٽ� �׸���
						draw_box(B_X[0], B_Y[0], B_X[1], B_Y[1], BOX);
						// Player1�� ������ ������� �ʾҴٸ� �� �� ��� �ٽ� �׸���
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
						else { // Player1�� ������ ����Ǿ��� ���
							cover_map(0); // �� ���� ������ �ʵ��� �����ֱ�
						}
						// Player2�� ������ ������� �ʾҴٸ� �� �� ��� �ٽ� �׸���
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
						else { // Player2�� ������ ����Ǿ��� ���
							cover_map(1); // �� ���� ������ �ʵ��� �����ֱ�
						}
						
						textcolor(WHITE, BLACK);
						if(!game_over[0]) // Player1�� ������ ������� �ʾ��� ���
							show_block(0, 0); // ���� �̵� ���� ��� �׸���
						if(!game_over[1]) // Player2�� ������ ������� �ʾ��� ���
							show_block(1, 0); // ���� �̵� ���� ��� �׸���
						show_level(0); show_level(1); // Player1�� Player2�� ���� ���� ���
						show_score(); // Player1�� Player2�� ���� ������ ������ ���� �� ���
						show_next(0); show_next(1); // Player1�� Player2�� ���� ��� ��� ���
						// ������ ��� ��� ���
						if (hold[0] != -1) // Player1�� ������ ����� ���� ���
							show_hold(0); // Player1�� ������ ��� ��� ���
						if (hold[1] != -1) // Player2�� ������ ����� ���� ���
							show_hold(1); // Player2�� ������ ��� ��� ���
						show_sent(0); show_sent(1); // Player1�� Player2�� ������ �� ��� ���� �� ���
					}
					else if (y == 18) // RETRY �޴� ���� ��
						goto START; // ���� �����
					else { // EXIT �޴� ���� ��
						cls(BLACK, WHITE); // PAUSE �޴� ȭ�� �����
						gotoxy(30, 14); // ���� �� Ŀ�� ��ġ ����
						return 0; // ���α׷� ����
					}
				}
				// �� �÷��̾��� ������ ������� ������ player �Լ� ���������� ȣ��
				if (ch == SPECIAL1) { // Ư�� Ű�� ������ �ִ� ���
					ch = getch();
					switch (ch) {
					// Player2�� ���� Ű�� �̵�
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
						// frame_count�� frame_sync�� �������� �� �������� 0�� ��� Player �Լ� ȣ��
						if (!game_over[0] && (frame_count % p1_frame_sync == 0))
							player1(0);
						if (!game_over[1] && (frame_count % p2_frame_sync == 0))
							player2(0);
					}
				}
				else { // ������ �ִ� Ű�� Ư�� Ű�� �ƴ� ���
					switch (ch) {
					case SPACE:
					case HOLD2:
						if (!game_over[0])
							player1(0);
						if (!game_over[1])
							player2(ch);
						break;
					// Player1�� WASD Ű�� �̵�
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
						// frame_count�� frame_sync�� �������� �� �������� 0�� ��� Player �Լ� ȣ��
						if (!game_over[0] && (frame_count % p1_frame_sync == 0))
							player1(0);
						if (!game_over[1] && (frame_count % p2_frame_sync == 0))
							player2(0);
					}
				}
			}
			else { // Ű���尡 ������ ���� ���� ���
				// frame_count�� frame_sync�� �������� �� �������� 0�� ��� Player �Լ� ȣ��
				if (!game_over[0] && (frame_count % p1_frame_sync == 0))
					player1(0);
				if (!game_over[1] && (frame_count % p2_frame_sync == 0))
					player2(0);
			}
			Sleep(50);
			frame_count++; // �ӵ� ������ ���� frame_count ����
		}
	}
	else if (menu == 2) { // RANKING �޴� ���� ��
		FILE* infile1; // Player �̸� ����
		FILE* infile2; // Player ���� ����
		int n, player_num = 0;

		infile1 = fopen("player.txt", "r"); // Player �̸� ���� ����
		infile2 = fopen("score.txt", "r"); // Player ���� ���� ����

		// ���� �� Player �̸��� ����ü ranking�� player �迭�� ����
		while (1) {
			n = fscanf(infile1, "%s", &ranking[player_num].player);

			if (n != 1)
				break;

			player_num++;
		}

		player_num = 0; // ��ϵ� �̸� �� 0���� �ʱ�ȭ

		// ���� �� Player ������ ����ü ranking�� score ������ ����
		while (1) {
			n = fscanf(infile2, "%d", &ranking[player_num].score);

			if (n != 1)
				break;

			player_num++;
		}

		// ���� ���� ������ ����ü ranking ����
		for (i = 0; i < player_num; i++) {
			for (j = i + 1; j < player_num; j++) {
				if (ranking[i].score < ranking[j].score) {
					// ���� ���� ������ ����ü ranking�� score ����
					int temp1 = ranking[i].score;
					ranking[i].score = ranking[j].score;
					ranking[j].score = temp1;
					// ���� ���� ������ ����ü ranking�� player ����
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

		cls(BLACK, WHITE); // ���� �޴� ȭ�� �����
		printxy(45, 4, "Ranking\n");

		y = 7;
		if (player_num < 5) { // ��ϵ� Player�� ���� 5���� ���� ���
			// ��ϵ� Player�� ���� ���
			for (i = 0; i < player_num; i++) {
				textcolor(ranking_color[i], BLACK);
				printxy(22, y - 1, "��������������������������������������������������");
				gotoxy(22, y);
				printf("      %d       %s                                   ", i + 1, ranking[i].player);
				gotoxy(57, y);
				printf("%7d", ranking[i].score);
				printxy(22, y + 1, "��������������������������������������������������");
				y += 4;
			}
			// ������ ������ ��� �α�
			for (i = player_num; i < 5; i++) {
				textcolor(ranking_color[i], BLACK);
				printxy(22, y - 1, "��������������������������������������������������");
				gotoxy(22, y);
				printf("      %d       ---                      ---         ", i + 1);
				printxy(22, y + 1, "��������������������������������������������������");
				y += 4;
			}
		}
		else { // ��ϵ� Player�� ���� 5�� ���ų� 5���� ū ���
			// ��ϵ� Player�� ���� ���
			for (i = 0; i < 5; i++) {
				textcolor(ranking_color[i], BLACK);
				printxy(22, y - 1, "��������������������������������������������������");
				gotoxy(22, y);
				printf("      %d       %s                                   ", i + 1, ranking[i].player);
				gotoxy(57, y);
				printf("%7d", ranking[i].score);
				printxy(22, y + 1, "��������������������������������������������������");
				y += 4;
			}
		}
		fclose(infile1); // Player �̸� ���� �ݱ�
		fclose(infile2); // Player ���� ���� �ݱ�
		textcolor(WHITE, BLACK);
		gotoxy(30, 26); // ���� �� Ŀ�� ��ġ ����
		return 0; // ���α׷� ����
	}
	else { // EXIT �޴� ���� ��
		cls(BLACK, WHITE); // ���� �޴� ȭ�� �����
		gotoxy(30, 14); // ���� �� Ŀ�� ��ġ ����
		return 0; // ���α׷� ����
	}

	FILE* outfile1; // Player �̸� ����
	FILE* outfile2; // Player ���� ����

	outfile1 = fopen("player.txt", "a"); // Player �̸� ���� ����
	outfile2 = fopen("score.txt", "a"); // Player ���� ���� ����

	// Player1�� �̸� Player �̸� ���Ͽ� ����ϱ�
	fputs(player1_name, outfile1);
	fprintf(outfile1, "\n");
	// Player2�� �̸� Player �̸� ���Ͽ� ����ϱ�
	fputs(player2_name, outfile1);
	fprintf(outfile1, "\n");

	fprintf(outfile2, "%d\n", score[0]); // Player1�� ���� Player ���� ���Ͽ� ����ϱ�
	fprintf(outfile2, "%d\n", score[1]); // Player2�� ���� Player ���� ���Ͽ� ����ϱ�

	fclose(outfile1); // Player �̸� ���� �ݱ�
	fclose(outfile2); // Player ���� ���� �ݱ�

	cls(BLACK, WHITE); // ��Ʈ���� ���� ȭ�� �����
	// ���� ��� ���
	textcolor(GREEN2, BLACK);
	if (score[0] > score[1]) // Player1�� ������ Player2�� �������� ū ���
		printxy(40, 9, "WINNER IS PLAYER1!!  ");
	else if (score[0] < score[1]) // Player2�� ������ Player1�� �������� ū ���
		printxy(40, 9, "WINNER IS PLAYER2!!  ");
	else // Player1�� Player2�� ������ ������ ���
		printxy(40, 9, "       DRAW!!        ");

	x = 50, y = 17;
	while (1) {
		int f_color, b_color; // Game Over ��¿� ���� �۾��� ��� ����
		unsigned char c2; // Game Over �޴� ���� �� ���Ǵ� ����

		do {
			f_color = rand() % 15 + 1; // �۾� ���� ���� ����
			b_color = rand() % 15 + 1; // ��� ���� ���� ����
		} while (f_color == b_color); // �۾��� ��� ������ ���� ���� ������ �ݺ�
		// �۾��� ��� ������ �����ϸ鼭 Game Over Ʋ �׵θ� ���
		textcolor(f_color, b_color);
		for (i = 42; i <= 54; i += 2) {
			for (j = 11; j <= 13; j += 2) {
				printxy(i, j, "��");
			}
		}
		printxy(40, 11, "��");
		printxy(56, 11, "��");
		printxy(40, 12, "��");
		printxy(56, 12, "��");
		printxy(40, 13, "��");
		printxy(56, 13, "��");
		// �۾� ������ �����ϸ� Game Over ���
		textcolor(f_color, BLACK);
		printxy(42, 12, "**Game Over**");

		// Game Over �޴� ȭ���� ��� ���� ȭ�� ��� ��İ� �����ϹǷ� �ּ� ����
		textcolor(WHITE, BLACK);

		if (y == 17)
			textcolor(BLUE2, BLACK);
		printxy(22, 16, "������������������������������������������������������");
		printxy(22, 17, "��                      RESTART                     ��");
		printxy(22, 18, "������������������������������������������������������");
		textcolor(WHITE, BLACK);

		if (y == 21)
			textcolor(RED2, BLACK);
		printxy(22, 20, "������������������������������������������������������");
		printxy(22, 21, "��                       EXIT                       ��");
		printxy(22, 22, "������������������������������������������������������");
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
	if (y == 17) // RESTART �޴� ���� ��
		goto START; // ���� �����
	else { // EXIT �޴� ���� ��
		cls(BLACK, WHITE); // Game Over �޴� ȭ�� �����
		gotoxy(30, 14); // ���� �� Ŀ�� ��ġ ����
		return 0; // ���α׷� ����
	}
}