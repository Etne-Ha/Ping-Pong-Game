#include "Draw.h"
#include <windows.h>
#include <iostream>
using namespace std;

//  hàm dùng để vẽ tường cho trò chơi với tham số đầu vào lần lượt là chiều rộng, chiều cao, tọa độ x và tọa độ y của điểm mà ở đó ta bắt đâu vẽ tường
void Draw::drawWall(int width, int height, int x = 0, int y = 0) // hàm có giá trị x và y mặc định là 0 và trong trò chơi ta cũng sẽ in tường từ tọa độ (0,0) 
{
	this->GotoXY(x, y); // gọi hàm di chuyển con trỏ để đưa con trỏ tới vị trí (x,y) để bắt đầu vẽ tường
	cout << 'X'; // tường là những từ 'X' nằm cạnh nhau nên ở vị trí (x,y) ta in ra 'X'
	for (int i = 1; i <= width; i++) // vòng lặp for chạy từ i == 1 tới i == width chính là in ra tường trên của trò chơi ( in tiếp tục từ vị trí (x,y) ban đầu theo chiều ngang ( hàng y )) với width là chiều rộng tường 
	{
		cout << 'X'; // in ra kí tự 'X'
	}
	for (int i = y + 1; i < height + y; i++) // vòng lặp for chạy từ i == y + 1 tới i == height + y tức là in ra tường trái và tường phải của trò chơi ( in từ vị trí y + 1 tức là bỏ qua hàng y đã được in xong ở dòng trên và in theo chiều dọc ) với height là chiều cao của tường
	{
		this->GotoXY(x, i); // tới vị trí của tường trái trò chơi ( có tọa độ x cố định và i thay đổi theo dòng for )
		cout << 'X'; // in ra kí tự 'X'
		this->GotoXY(x + width, i); // tới vị trí của tường phải  trò chơi ( có tọa độ x == witdh + x cố định và i thay đổi theo dòng for )
		cout << 'X'; // in ra kí tự 'X'
	}
	this->GotoXY(x, height + y); // tới vị trí của tường dưới ( có tọa độ x cố định và y == height + y cố định ( hàng y + height ))
	cout << 'X'; // in ra kí tự 'X'
	for (int i = 1; i <= width; i++) // từ vị trí đầu tiên của tường dưới đã được in ở dòng trên ta tiếp tục in cho xong các kí tự 'X' dọc theo chiều ngang của tường ( từ i == 1 tới i == width )
	{
		cout << 'X'; // in ra kí tự 'X'
	}
	this->GotoXY(x, height + 1); // đưa con trỏ xuống ngay bên dưới của tường
}


// hàm dùng để vẽ tường khi kết thúc trò chơi ( có thêm hiệu ứng so với hàm vẽ tường thông thường ) với tham số đầu vào lần lượt là chiều rộng, chiều cao, tọa độ x và tọa độ y của điểm mà ở đó ta bắt đâu vẽ tường
void Draw::drawWallEndGame(int width, int height, int x = 0, int y = 0) // hàm vẽ tường này chỉ là một biến thể cùa hàm vẽ tường gốc nên các dòng code là tương tự nhau chỉ có mốt số ít thay đổi
{
	int i = 0; // biến đếm cho việc lặp in màn hình và tạo hiệu ứng
	this->changeTextColorBlue(); // đổi chữ thành màu xanh dương 
	while (i < 2) // việc in ra màn hinh sẽ được lặp lại 2 lần với 2 màu khác nhau
	{
		this->GotoXY(x, y); // tới tọa độ (x,y)
		cout << 'X'; // in ra kí tự 'X'
		for (int i = 1; i <= width; i++) // dòng for để tiến hành in ra tường trên 
		{
			cout << 'X'; // in ra kí tự 'X'
			Sleep(100); // cho hàm ngủ 100ms để việc in ra màn hình được diễn ra từ từ 
		}
		for (int i = y + 1; i < height + y; i++) // dòng for để vẽ tường trái và tường phải 
		{
			this->GotoXY(x, i); // tới vị trí tường trái
			cout << 'X'; // in ra kí tự 'X'
			Sleep(100); // cho hàm ngủ 100ms
			this->GotoXY(x + width, i); // tới vị trí tường phải 
			cout << 'X'; // in ra kí tự 'X'
			Sleep(100); // cho hàm ngủ 100ms
		}
		this->GotoXY(x, height + y); // tới vị trí tường dưới 
		cout << 'X'; // in ra kí tự 'X'
		for (int i = 1; i <= width; i++) // dòng for để tiến hành in ra tường dưới  
		{
			cout << 'X'; // in ra kí tự 'X'
			Sleep(100); // cho hàm ngủ 100ms
		}
		this->GotoXY(x, height + 1); // đưa con trỏ xuống ngay bên dưới của tường
		this->changeTextColorGreen(); // chuyển màu chữ xang màu xanh lá cho lần in tường thứ 2 
		++i; // tăng biến đếm lên
	}
	this->changeTextColorWhite(); // chuyển màu chữ trở lại thành màu đen
}


// hàm dùng để đưa con trỏ tới vị trí có tọa độ (x,y) trên màn hình
void Draw::GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


// hàm dùng để đổi màu của chữ sang màu xanh dương
void Draw::changeTextColorBlue()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}


// hàm dùng để dổi màu của chữ sang màu đỏ 
void Draw::changeTextColorRed()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}


// hàm dùng để dổi màu của chữ sang màu trắng
void Draw::changeTextColorWhite()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
}


// hàm dùng để đổi màu của chữ sang màu xanh lá
void Draw::changeTextColorGreen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}