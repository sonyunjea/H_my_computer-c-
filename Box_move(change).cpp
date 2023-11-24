//#include <iostream>
//#include<Windows.h>
//#include<time.h>
//#include<stdlib.h>
//#include<conio.h>
//
//using namespace std;
//
//class CLA {
//private:
//	int map[8][8] =
//	{
//		{1,1,1,1,1,1,1,1},
//		{1,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,1},
//		{1,1,1,1,1,1,1,1},
//	};
//	int sx, sy;
//
//	char ch;
//
//public:
//	void Pro_Manage();
//	void Make_St();
//	void St_Walk();
//	void St_Up();
//	void St_Down();
//	void St_Left();
//	void St_Right();
//	void Draw_Bow();
//	void space();
//	void Move_and_swich();
//	void clear();
//};
//
//void CLA::clear() {
//	bool isAllOne = 1;
//
//	for (int i = 0; i < 8; ++i) {
//		for (int j = 0; j < 8; ++j) {
//			if (map[i][j] != 1) {
//				isAllOne = 0;
//				break;
//			}
//		}
//		if (!isAllOne)
//			break;
//	}
//
//	if (isAllOne==1) {
//		exit(0);
//	}
//}
//
//
//
//
//
//void CLA::Pro_Manage() {
//	Draw_Bow();
//	Make_St();
//	St_Walk();
//}
//
//
//void CLA::Make_St() {
//
//	srand(time(NULL));
//	sx = (rand() % 6) + 1;
//	sy = (rand() % 6) + 1;
//	map[sy][sx] = 2;
//
//}
//
//
//void CLA::St_Walk() {
//	ch = 0;
//	while (ch != 27)
//	{
//		ch = _getch();
//		switch (ch)
//		{
//		case 72: St_Up();
//			break;
//		case 80: St_Down();
//			break;
//		case 75: St_Left();
//			break;
//		case 77: St_Right();
//			break;
//
//		case 32: space();
//			break;
//
//		}
//		clear();
//		system("cls");
//		Draw_Bow();
//
//	}
//
//
//}
//
//void CLA::space() {
//
//	map[sy][sx] = 1;
//
//}
//
//void CLA::St_Up() {
//
//	if (sy > 1)
//	{
//		--sy;
//	}
//	if (map[sy][sx] == 0)
//	{
//		map[sy][sx] = 2;
//
//	}
//	if (map[sy + 1][sx]==2)
//	{
//		map[sy + 1][sx] = 0;
//
//	}
//
//}
//
//void CLA::St_Down()
//{
//	if (sy < 6)
//	{
//		++sy;
//	}
//	if (map[sy][sx] == 0)
//	{
//		map[sy][sx] = 2;
//
//	}
//	if (map[sy -1][sx] == 2)
//	{
//		map[sy - 1][sx] = 0;
//
//	}
//
//}
//
//
//void CLA::St_Left() {
//	if (sx > 1)
//	{
//		--sx;
//	}
//	if (map[sy][sx] == 0)
//	{
//		map[sy][sx] = 2;
//
//	}
//	if (map[sy ][sx+1]==2)
//	{
//		map[sy ][sx+1] = 0;
//
//	}
//
//};
//
//void CLA::St_Right() {
//
//	if (sx < 6)
//	{
//		++sx;
//	}
//	if (map[sy][sx] == 0)
//	{
//		map[sy][sx] = 2;
//
//	}
//	if (map[sy][sx-1] == 2)
//	{
//		map[sy][sx-1] = 0;
//
//	}
//
//}
//
//
//
//
//void CLA::Draw_Bow() {
//	int a, b;
//	for (a = 0; a < 8; a++)
//	{
//		for (b = 0; b <8;b++) {
//			if (map[a][b] == 0)
//			{
//				cout << "  ";
//
//			}
//			if (map[a][b] == 1)
//			{
//				cout << "¡á";
//			}
//			
//			if (map[a][b] == 2)
//			{
//				cout << "¢¼";
//			}
//
//		
//		}
//		cout << endl;
//	}
//}
//
//int main() {
//
//	CLA nm;
//	nm.Pro_Manage();
//	return 0;
//}


 
 
 
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

class CLA {
private:
    int map[10][10] =
    {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1},
    };
    int sx1, sy1; // Position of the first character
    int sx2, sy2; // Position of the second character
    char ch1, ch2;

public:
    void Pro_Manage();
    void Make_Characters();
    void Move_Character(int& x, int& y, char& ch);
    void Draw_Map();
};

void CLA::Pro_Manage() {
    Make_Characters();
    while (ch1 != 27 && ch2 != 27) { // Continue until either player presses 'Esc'
        Move_Character(sx1, sy1, ch1);
        Move_Character(sx2, sy2, ch2);
        system("cls");
        Draw_Map();
    }
}

void CLA::Make_Characters() {
    srand(time(NULL));
    sx1 = (rand() % 8) + 1;
    sy1 = (rand() % 8) + 1;
    sx2 = (rand() % 8) + 1;
    sy2 = (rand() % 8) + 1;
    map[sy1][sx1] = 2; // Character 1
    map[sy2][sx2] = 3; // Character 2
}

void CLA::Move_Character(int& x, int& y, char& ch) {
    ch = _getch();
    int prevX = x, prevY = y;
    switch (ch) {
    case 72: // Up arrow
        if (y > 1) y--;
        break;
    case 80: // Down arrow
        if (y < 8) y++;
        break;
    case 75: // Left arrow
        if (x > 1) x--;
        break;
    case 77: // Right arrow
        if (x < 8) x++;
        break;
    case 27: // Esc key
        break;
    }
    // Clear the previous position and update the new position
    map[prevY][prevX] = 0;
    if (ch == 27) return; // If 'Esc' is pressed, don't update the new position
    map[y][x] = (ch == ch1) ? 2 : 3; // Set different characters for the two players
}

void CLA::Draw_Map() {
    for (int a = 0; a < 10; a++) {
        for (int b = 0; b < 10; b++) {
            if (map[a][b] == 0) {
                cout << "  ";
            }
            else if (map[a][b] == 1) {
                cout << "¡á";
            }
            else if (map[a][b] == 2) {
                cout << "¢¼";
            }
            else if (map[a][b] == 3) {
                cout << "¢À";
            }
        }
        cout << endl;
    }
}

int main() {
    CLA game;
    game.Pro_Manage();
    return 0;
}
