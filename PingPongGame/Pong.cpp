#include "Pong.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include <time.h>
#define SPEED 500 // tốc độ mặc định
#define WIDTH 1257 // chiều rộng màn hình mặc định
#define HEIGHT 730 // chiều cao màn hinh mặc định
#define DEFAULT_POS -1 // vị trí để thanh trượt tự động di chuyển mặc định
#define MAXSCORE 10 // điểm tối đa mặc định
#define DELAY_TIME 50 // thời gian bị trễ của thanh trượt
using namespace std;


// hàm vào giao diện chọn lựa của trò chơi
void Pong::runMenu()
{
	if (this->_game_state == MENU) // nếu trạng thái hiện tại là MENU thì xuất giao diện lựa chọn cho người chơi
	{
		//system("cls"); // xóa màn hình 
		//this->changeTextColorGreen(); // chuyển font chữ thành màu xanh
		cout << " Press S to start playing " << endl; // in ra yêu cầu bấm 'S' để chơi
		cout << " Press ESC to exit " << endl; // in ra yêu cầu bấm 'ESC' để thoát
		//this->changeTextColorWhite(); // chuyển font chữ thành màu tr 
		while (1) // chờ người dùng nhập lựa chọn
		{
			if (GetAsyncKeyState(VkKeyScan('s')) || GetAsyncKeyState(VkKeyScan('S'))) // nếu ngươi dùng chọn 'S' hoặc 's' ( có Caps hoặc không )
			{
				this->_game_state = PLAYING; // thì chuyển trạng thái sang đang chơi 
				this->runGame(); // chạy hàm vào màn hình chơi
			}
			else
			{
				if (GetAsyncKeyState(VK_ESCAPE)) // trường hợp nhấn phím 'ESC'
				{
					exit(0); // thì thoát khỏi console
				}
			}
		}
	}
}


// hàm để cập nhật banh
void Pong::updateBall(SDL_Renderer*& gRenderer)
{
	if (this->_ball->impactBottom(this->_playerBottom)) // kiểm tra va chạm với thanh trượt dưới 
	{
		// nếu xảy ra va chạm thì thực hiện loạt các hoạt động sau 
		//this->_ball->draw(); // vẽ 
		//this->_ball->clear(); // xóa
		//this->_ball->move(); // di chuyển 
		//this->changeTextColorRed(); // đổi màu font chữ sang đỏ 
		//this->_ball->draw(gRenderer); // vẽ 
		//this->changeTextColorWhite(); // đổi màu font chứ sang trắng 
		//this->_speed -= this->_speed * 0.1; // giảm thời gian chờ vẽ banh - tăng tốc độ banh xuất hiện trên màn hình 

		//tang van toc 10%
		if (sqrt(_ball->VX() * _ball->VX() + _ball->VY() * _ball->VY()) < MAX_V)
		{
			_ball->SetVX(_ball->VX() * 110 / 100);
			_ball->SetVY(_ball->VY() * 110 / 100);
		}
	}
	else
	{
		if (this->_ball->impactTop(this->_playerTop)) // kiểm tra va chạm với thanh trượt trên
		{
			// cũng làm tương tự các hoạt động trên 
			//this->_ball->draw(); // vẽ 
			//this->_ball->clear(); // xóa
			//this->_ball->move(); // di chuyển 

			//this->changeTextColorRed(); // đổi màu font chữ sang đỏ 
			//this->_ball->draw(); // vẽ 
			//this->changeTextColorWhite(); // đổi màu font chứ sang trắng 
			//this->_speed -= this->_speed * 0.1; // giảm thời gian chờ vẽ banh - tăng tốc độ banh xuất hiện trên màn hình 

			//tang van toc 10%
			if (sqrt(_ball->VX() * _ball->VX() + _ball->VY() * _ball->VY()) < MAX_V)
			{
				_ball->SetVX(_ball->VX() * 110 / 100);
				_ball->SetVY(_ball->VY() * 110 / 100);
			}
		}
		else
		{
			if (this->_ball->impactWall(_top, _bot, _left, _right)) // kiểm tra va chạm với wall
			{
				// tượng tự trên
				//this->_ball->draw(); // vẽ 
				//this->_ball->clear(); // xóa
				//this->_ball->move(); // di chuyển 
				//this->changeTextColorRed(); // đổi màu font chữ sang đỏ 
				//this->_ball->draw(); // vẽ 
				//this->changeTextColorWhite(); // đổi màu font chứ sang trắng 
				//this->_speed -= this->_speed * 0.1; // giảm thời gian chờ vẽ banh - tăng tốc độ banh xuất hiện trên màn hình 
			}
			else // trường hợp không có va chạm xảy ra
			{
				//this->_ball->draw(gRenderer); // vẽ 
				//this->_ball->clear(); // xóa 
				//this->_ball->move(); // di chuyển 
				//this->_ball->draw(); // vẽ
			}
		}
	}
	this->_ball->move(_playerBottom, _playerTop);
	this->_ball->draw(gRenderer);
}


// hàm để cập nhật thanh trượt
void Pong::updatePaddle(SDL_Renderer*& gRenderer)
{
	//this->_playerBottom->clear(); // xóa 
	//this->_playerTop->clear(); // xóa
	this->_playerBottom->move(); // di chuyển 
	this->_playerTop->move(); // di chuyển

	this->_playerBottom->draw(gRenderer); // vẽ
	this->_playerTop->draw(gRenderer); // vẽ 
}


// hàm chạy khi vào màn hình chơi
void Pong::runGame()
{
	//system("cls"); // xóa màn hình 

	// khai báo các biến cần thiết 

	//tao man hinh
	Screen screen;

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	this->setMaxScore(MAXSCORE); // tạo điểm chơi tối đa

	Paddle p1((_right + _left) / 2, _top + 100, 120, _left, _right, "bar1.png", screen.GRenderer(), NONE); // tạo thanh trượt trên
	this->_playerTop = &p1; // trỏ tới thanh trượt trên

	Paddle p2((_right + _left) / 2, _bot - 100, 120, _left, _right, "bar1.png", screen.GRenderer(), NONE); // tạo thanh trượt dưới 
	this->_playerBottom = &p2; // trỏ tới thanh trượt dưới

	Ball b((_right + _left) / 2, (_top + _bot) / 2, SPEED, "ball.png", screen.GRenderer(), DOWN); // tạo trái banh
	this->_ball = &b; // trỏ tới trái banh

	this->setSpeed(this->_ball->getSpeed()); // láy tốc độ của banh

	// vễ màn hình chơi

	this->_playerTop->draw(screen.GRenderer()); // vẽ thanh trượt trên 
	this->_playerBottom->draw(screen.GRenderer()); // vẽ thanh trượt dưới
	this->_ball->draw(screen.GRenderer()); // vẽ trái banh
	//this->drawWall(this->_width, this->_height, 0, 0); // vẽ tường 
	//this->showScoreBoard(); // hiện bảng điểm

	// tạo các tiểu trình 

	//thread ball(&Pong::useBallSpeed, this); // tiểu trình thể hiện tốc độ xuất hiện của banh
	//thread paddle(&Pong::delayPaddle, this); // tiểu trình làm trễ thanh trượt

	while (this->_game_state == PLAYING && !quit) // nếu trạng thái là đang chơi thì trò chơi được bắt đầu
	{
		this->_playerBottom->setDir(NONE); // sau cập nhật xong thanh trượt thì hướng di chuyển sễ là đứng yên 
		this->_playerTop->setDir(NONE); // tương tự dòng trên 
		if (GetAsyncKeyState(VkKeyScan('A')) || GetAsyncKeyState(VkKeyScan('a'))) //  nếu phím 'a' được nhấn 
		{
			this->_playerTop->setDir(PLEFT); // thanh trượt trên di chuyển sang trái 
		}
		else
		{
			if (GetAsyncKeyState(VkKeyScan('D')) || GetAsyncKeyState(VkKeyScan('d'))) //  nếu phím 'd' đước nhấn
			{
				this->_playerTop->setDir(PRIGHT); // thanh trượt trên di chuyển sang phải
			}
		}
		if (GetAsyncKeyState(VK_LEFT)) //nếu phím mũi tên trái được nhấn
		{
			this->_playerBottom->setDir(PLEFT); // thanh trượt dưới sẽ di chuyển trái
		}
		else
		{
			if (GetAsyncKeyState(VK_RIGHT)) //nếu phím mũi tên phải được nhấn 
			{
				this->_playerBottom->setDir(PRIGHT); // thanh trượt dưới sẽ di chuyển sang phải 
			}
		}

		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//xoa man hinh
		screen.Clear();

		this->updateGame(screen.GRenderer()); // cập nhật các vật thể
		this->resetGameInfo(); // tạo lại trò chơi nếu cần

		//cap nhat man hinh
		screen.Update();
	}

	screen.Close();
}


// constructor của lớp Pong với biến đầu vào lần lượt là chiều rộng , chiều cao màn hình chơi và trạng thái của game 
Pong::Pong(int top, int bot, int left, int right, gamestate game_state)
{
	this->_score1 = 0; // gán điểm người chơi 1 băng 0 
	this->_score2 = 0; // gán điểm người chơi 2 bằng 0

	//bien tren
	this->_top = top;
	//bien duoi
	this->_bot = bot; 
	//bien trai
	this->_left = left;
	//bien phai
	this->_right = right;

	this->_game_state = game_state; // gán trạng thái của trò chơi 
}


// hàm thể hiện bảng điểm 
void Pong::showScoreBoard()
{
	//this->GotoXY(this->_width + 5, this->_height / 2); // tới vị trí này để hiển điểm 
	//cout << _score1 << ":" << _score2; // xuất ra điểm của người chơi
}


// hàm cập nhật bảng điểm 
//void Pong::updateScoreBoard()
//{
//	point ball_pos = this->_ball->getPos(); // lấy vị trí của trái banh hiện tại
//	if (ball_pos.y == 1) // nếu tọa độ y == 1 tức là chạm tường trên 
//	{
//		this->_score2 = this->_score2 + 1; // người chơi 2 tăng điểm 
//	}
//	else
//	{
//		if (ball_pos.y == this->_height - 1) // nếu ở vị trí chiều cao - 1 tức là chạm tường dưới 
//		{
//			this->_score1 = this->_score1 + 1; // người chơi dưới tăng điểm
//		}
//	}
//	if (this->_score1 == this->_max_score || this->_score2 == this->_max_score) // nếu một trong 2 người chơi đạt điểm tối đa
//	{
//		if (this->_game_state == PLAYING) // nếu trạng thái đang là chơi 
//		{
//			this->_game_state = END; // thì trò chơi kết thúc
//		}
//		else // còn lại là vẫn đang ở Intro
//		{
//			this->_game_state = INTRO; // tiếp tục giữ nguyên trạng thái
//		}
//	}
//}


// hàm tạo lại tốc độ của banh
void Pong::resetSpeed()
{
	this->setSpeed(this->_ball->getSpeed()); // gán lại tốc độ ban đầu
}


// hàm gán tốc độ mới với biến đầu vào float thể hiện tốc độ mới 
void Pong::setSpeed(float speed)
{
	this->_speed = speed; // gán speed cho tốc độ hiện tại
	this->_original_speed = speed; // gán speed cho tốc độ gốc
}


// hàm chạy khi kết thúc trò chơi
void Pong::runEndGame()
{
	//system("cls"); // xóa màn hình 

	//this->GotoXY((this->_width / 2) - 6, this->_height / 2); // tới vị trí này 
	//this->changeTextColorRed(); // đổi font chữ sang màu đỏ
	if (this->_score1 > this->_score2) // nếu điểm ngưới chơi 1 lớn hơn 
	{
		cout << "PLAYER 1 WIN"; // xuât ra màn hình thông báo người chơi 1 thắng
	}
	else // ngược lại
	{
		cout << "PLAYER 2 WIN"; // xuất ra màn hình thông báo người chơi 2 thắng
	}
	//this->drawWallEndGame(this->_width, this->_height, 0, 0); // vẽ màn hình kết thúc trò chơi
	//this->GotoXY(0, this->_height + 1); // tới vị trí bên dưới tường 
	cout << "Press ESC to exit or R to start a new game" << endl; // in ra yêu cầu

	while (1) // chờ người chơi nhập lụa chọn
	{
		if (GetAsyncKeyState(VkKeyScan('r')) || GetAsyncKeyState(VkKeyScan('R'))) // nếu người dùng nhập 'r' thì chơi lại
		{
			this->_game_state = PLAYING; // trạng thái trở về đang chơi 
			this->_score1 = 0; // gán lại điểm 1 
			this->_score2 = 0; // gán lại điểm 2
			this->runGame(); // vào màn hình chơi 
		}
		else
		{
			if (GetAsyncKeyState(VK_ESCAPE)) // nếu nhận được phím 'ESC' 
			{
				exit(0); // thì thoát trò chơi
			}
		}
	}

}


// hàm cập nhật các vật thể di chuyển trong trò chơi
void Pong::updateGame(SDL_Renderer*& gRenderer)
{
	this->updatePaddle(gRenderer); // cập nhật thnah trượt 
	this->updateBall(gRenderer); // cập nhật banh 
	//if (this->_paddle_availability == TRUE) // nếu thanh trượt có thể được vẽ 
	//{
	//	
	//	this->_paddle_availability = FALSE; // quay lại tình trạng không thể vẽ 
	//}
	//if (this->_ball_availability == TRUE) // nếu banh có thể được vẽ 
	//{
	//	
	//	this->_ball_availability = FALSE; // quay lại tình trạng không thể vẽ
	//}
}


// hàm tạo lại thông tin trò chơi 
void Pong::resetGameInfo()
{
	if (this->_ball->getDir() == STOP) // nếu trạng thai của banh là STOP - không di chuyển 
	{
		//this->updateScoreBoard(); // cập nhật bảng điểm 
		if (this->_game_state == END) // nếu trạng thái của trò chơi chuyển thành END - kết thúc
		{
			this->runEndGame(); // tới hàm kết thúc 
		}
		this->showScoreBoard(); // xuất bảng điểm
		this->_ball->clear(); // xóa banh
		this->_playerTop->clear(); // xóa thanh trượt trên 
		this->_playerBottom->clear(); // xóa thanh trượt dưới 
		this->_ball->reset(); // tạo lại banh
		this->_playerTop->reset(); // tạo lại thanh trượt trên
		this->_playerBottom->reset();; // tạo lại thanh trượt dưới 
		this->resetSpeed(); // tạo lại tốc độ 
	}
}


// hàm bắt đàu trò chơi
void Pong::start()
{
	//system("cls"); // xóa màn hình 

	// khai báo các biến cần thiết 

	//tao man hinh
	Screen screen;

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	this->setMaxScore(MAXSCORE); // tạo điểm chơi tối đa

	Ball b(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SPEED, "ball.png", screen.GRenderer(), DOWN); // tạo trái banh
	this->_ball = &b; // trỏ tới trái banh

	Paddle p1(SCREEN_WIDTH / 2, 100, 40, 0, SCREEN_WIDTH, "bar1.png", screen.GRenderer(), NONE); // tạo thanh trượt trên
	this->_playerTop = &p1; // trỏ tới thanh trượt trên

	Paddle p2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 40, 0, SCREEN_WIDTH, "bar2.png", screen.GRenderer(), NONE); // tạo thanh trượt dưới 
	this->_playerBottom = &p2; // trỏ tới thanh trượt dưới

	float calculated_pos_bottom = DEFAULT_POS; // vị trí mặc định của thanh trượt dưới khi tự động di chuyển 
	float calculated_pos_top = DEFAULT_POS; // vị trí mặc định của thanh trượt trên khi tự động di chuyển

	//this->setSpeed(this->_ball->getSpeed()); // láy tốc độ của banh

	// vễ màn hình chơi

	this->_playerTop->draw(screen.GRenderer()); // vẽ thanh trượt trên 
	this->_playerBottom->draw(screen.GRenderer()); // vẽ thanh trượt dưới
	this->_ball->draw(screen.GRenderer()); // vẽ trái banh
	//cap nhat man hinh
	screen.Update();

	//this->drawWall(this->_width, this->_height, 0, 0); // vẽ tường 
	//this->showScoreBoard(); // hiện bảng điểm
	//this->GotoXY(0, this->_height + 1); // tới vị trí phía dưới tường chơi 
	//this->changeTextColorGreen(); // chuyển font chữ sang màu xanh
	//cout << "Press F to go to menu"; // xuât ra màn hình yêu cầu nhán 'F' để vào giao diện chính
	//this->changeTextColorWhite(); // chuyển font chữ sang màu trắng 

	// tạo các tiểu trình 

	//thread ball(&Pong::useBallSpeed, this); // tiểu trình thể hiện tốc độ xuất hiện của banh
	//thread paddle(&Pong::delayPaddle, this); // tiểu trình làm trễ thanh trượt


	while (this->_game_state == INTRO && !(GetAsyncKeyState(VkKeyScan('F') && GetAsyncKeyState(VkKeyScan('f')))) && !quit) // nếu trạng thái là INTRO - phần giới thiệu và người dùng không nhấn 'F' thì tiếp tục chạy màn hình tự chơi
	{
		//xoa man hinh
		screen.Clear();

		//calculated_pos_bottom = calculatePosBottom(calculated_pos_bottom); // tính vị trí cần di chuyển của thanh trượt dưới 
		//calculated_pos_top = calculatePosTop(calculated_pos_top); // tính vị trí cần di chuyển của thanh trượt trên 
		
		this->updateGame(screen.GRenderer()); // cập nhật vật thể 

		//_ball->Render(_ball->getPos().x, _ball->getPos().y, screen.GRenderer());
		//_playerBottom->Render(_playerBottom->getPos().x, _playerBottom->getPos().y, screen.GRenderer());
		//_playerTop->Render(_playerTop->getPos().x, _playerTop->getPos().y, screen.GRenderer());
		if (this->_ball->getDir() == STOP) // nếu trạng thái banh là  dừng 
		{
			//calculated_pos_bottom = DEFAULT_POS; // gán lại vị trí mặc định cho thanh trượt 
			//calculated_pos_top = DEFAULT_POS; // tương tự dòng trên 

			//this->updateScoreBoard(); // cập nhật bảng điểm 
			//this->showScoreBoard(); // hiện bảng điểm
			//this->_ball->clear(); //  xóa banh
			//this->_playerTop->clear(); // xóa thanh trượt
			//this->_playerBottom->clear(); // như trên 
			this->_ball->reset(); // khởi tạo lại banh
			this->_playerTop->reset(); // khởi tạo lại thanh trượt trên 
			this->_playerBottom->reset(); // khởi tạo lại thanh trượt dưới 
			this->resetSpeed(); // khỏi tạo lại tốc độ
		}
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		screen.Update();
	}
	this->_game_state = MENU; // thoát ra khỏi trạng thái intro thì chuyển sang trạng thái menu
	this->runMenu(); // tiến vào giao diện chính
}


// destructor của lớp Pong ( xóa các con trỏ )
Pong::~Pong()
{
	delete _playerBottom; // xóa con trỏ thanh trượt trên
	delete _playerTop; // xóa con trỏ thanh trượt dưới 
	delete _ball; // xóa con trỏ trái banh
}


// hàm gán điểm tối đa mà người chơi cần đạt được để chiến thắng với biến đầu vào kiểu int thể hiện điểm mới 
void Pong::setMaxScore(int max_score)
{
	this->_max_score = max_score; // gán max_score cho điểm tối đa hiện tại
}


// hàm lấy điểm tối đa hiện tại với biến trả về dạng int là tốc độ hiện tại
int Pong::getMaxScore()
{
	return this->_max_score; // trả về điểm tối đa hiện tại
}


// hàm dùng tốc độ của banh trong trò chơi 
//void Pong::useBallSpeed()
//{
//	while (_game_state == PLAYING || _game_state == INTRO) // nếu đang trong trạng thái PLAYING và INTRO thì tiểu hàm sẽ chạy
//	{
//		//if (this->_ball_availability == FALSE) // nếu đang trong tình trạng không thể vẽ banh
//		//{
//		//	Sleep(this->_speed); // cho ngủ khoảng thời gian tương ứng với tốc độ của banh ( _speed càng giảm thì banh càng nhanh )
//		//	this->_ball_availability = TRUE; // banh có thể được vẽ 
//		//}
//		_ball->move();
//	}
//}


// hàm làm thanh trượt chậm lại
void Pong::delayPaddle()
{
	while (_game_state == PLAYING || _game_state == INTRO) // nếu đang trong trạng thái PLAYING và INTRO thì tiểu hàm sẽ chạy
	{
		//if (this->_paddle_availability == FALSE) // nếu đang trong tình trạng không thể vẽ thanh trượt
		//{
		//	Sleep(DELAY_TIME); // cho ngủ khoảng thời gian tương ứng với độ trễ của thanh trượt 
		//	this->_paddle_availability = TRUE; // thanh trượt có thể vẽ 
		//}
		_playerBottom->move();

		_playerTop->move();
	}
}


// hàm cho thanh trượt dưới tự động di chuyển 
float Pong::calculatePosBottom(float& dest_pos)
{
	balldirection ball_dir = this->_ball->getDir(); // lấy hướng hiện tại của banh
	point ball_pos = this->_ball->getPos(); // lấy vị trí hiện tại của banh
	if (dest_pos == DEFAULT_POS) // nếu đang là vị trí mặc định
	{
		if (ball_dir == UP) // hướng banh đi lên 
		{
			dest_pos = 0; // thì thanh trượt không di chuyển mà trả về vị trí là 0
		}
		if (ball_pos.y + _ball->R() >= _bot - _playerBottom->Height() / 2) // nếu không xảy ra trường hợp trên và vị trí mặc định được giữ cho tới khi trái banh nằm ở vị trí ngay trên thanh trượt
		{
			//while (_ball_availability == FALSE) //  đợi banh có thể được vẽ 
			//{

			//}
			//while (_paddle_availability == FALSE) // đợi thanh trượt có thể được vẽ 
			//{

			//}
			srand((unsigned int)time(NULL)); // tạo seed cho biến tạo số ngẫu nhiên 
			int random = rand() % 2; // tạo số ngẫu nhiên trong khoảng 0 - 1 
			switch (random) // xét trường hợp của biến ngẫu nhiên
			{
			case 0: // nếu là 0
				this->_playerBottom->setDir(PRIGHT); // thanh trượt di chuyển sang phải 
				return 0; // trả về vị trí 0
			case 1: // nếu là 1 
				this->_playerBottom->setDir(PLEFT); // thanh trượt di chuyển sang trái 
				return 0; // trả về vị trí 0
			}
		}
		return dest_pos; // trả về vị trí 
	}
	if (this->_playerBottom->getRightLimit() - dest_pos <= this->_playerBottom->getSideDistance() && dest_pos != 0) // nếu vị trí cần di chuyển tới năm trong khoảng (right limit - side distance, right limit ) thì ta trừ đi cho 2 vì vị trí của thanh trượt được thể hiện luôn là vị trí giữa 
	{
		dest_pos -= (this->_playerBottom->getSideDistance() + 1); // trừ đi khoảng di chuyển dư 
		return dest_pos; // trả về vị trí 
	}
	else
	{
		if (dest_pos - this->_playerBottom->getLeftLimit() <= 2 && dest_pos != 0) // khoảng ( left limit, left limit + 2 )
		{
			dest_pos += (this->_playerBottom->getSideDistance() + 1); // trừ đi khoảng di chuyển dư 
			return dest_pos; // trả về vị trí
		}
	}
	if (this->_playerBottom->getPos().x == dest_pos) // nếu tọa độ hiện tại của thanh trượt == với tọa độ cần đên 
	{
		dest_pos = 0; // thì vị trí cần đến là 0
	}
	if (dest_pos == 0) // tiếp tục xét khi vị trí đã là 0
	{
		this->_playerBottom->setDir(NONE); // thì thanh trượt ngừng di chuyển
	}
	if (dest_pos == 0 && ball_pos.y == 3 && (ball_dir == DOWN || ball_dir == DOWNLEFT || ball_dir == DOWNRIGHT)) // nếu vị trí cần chuyển tới là 0 , vị trí của banh đang là cách thanh trượt trên 1 đơn vị và đang di chuyển xuống thì thanh trượt bắt đầu tính toán vị trí cần tới mới 
	{
		int distance_height = this->_playerBottom->getPos().y - ball_pos.y - 1; // khoảng cách từ banh tới biên đối diện ( tường dưới )
		int pos = this->_playerBottom->getPos().x - ball_pos.x; // tính vị trị tương đối giữa thanh trượt và trái banh theo tọa độ x
		if (ball_dir == DOWNLEFT) // trường hợp banh di chuyển xuống qua trái 
		{
			int distance_width = ball_pos.x - 1 - _left; // khoảng cách từ banh tới tường trái 
			if (distance_width >= distance_height) // trường hợp banh di chuyển chéo màn hình mà không va chạm với tường 
			{
				if (pos > 0 || (pos < 0 && abs(pos) < distance_height) || pos == 0) // xét các vị trí thanh trượt năm bên phải banh hoặc thanh trượt nằm bên trái banh nhưng vị trí tượng đối của nó nhỏ hơn khoảng cách tới tường dưới ( theo x - tức là di chuyển một khoảng x thì banh sẽ chạm đáy )
				{
					this->_playerBottom->setDir(PLEFT); // thanh trượt sẽ di chuyển sang trái 
					return ball_pos.x - distance_height; // trả về tọa độ x là vị trí banh trừ cho khoảng cách của banh tới đáy dưới 
				}
				if (pos < 0 && abs(pos) > distance_height) // trường hợp thanh trượt nằm bên trái quả banh và vị trí tương đối của nó lớn hơn khoảng cách từ thanh trượt tới đáy ( theo x )
				{
					this->_playerBottom->setDir(PRIGHT); // thanh trượt di chuyển sang phải 
					return ball_pos.x - distance_height; // trả về tọa độ x là vị trí banh trừ cho khoảng cách của banh tới đáy dưới  
				}
			}
			else // trường hợp banh di chuyển chéo màn hình có va chạm với tường 
			{
				int distance = distance_height - distance_width; // do banh chỉ di chuyển theo gốc 45 độ nên khi lấy khoảng cách từ banh tới tường dưới trừ cho khoảng cách từ banh tới tường trái ta sẽ có được khoảng cách từ tường trái cho đến vị trí banh sẽ đáp xuống ở tường dưới 
				if ((pos < 0 && distance > this->_playerBottom->getPos().x) || (pos > 0 && distance > this->_playerBottom->getPos().x) || (pos == 0 && distance > this->_playerBottom->getPos().x)) // xét trường hợp vị trí khi thanh trượt nằm bên trái hoặc bên phải hoặc ngang bằng với trái banh và khoảng cách từ tường trái cho đến vị trí đáp xuống ở tường dưới của banh lớn hơn khoảng cách của thanh trượt tới tường trái 
				{
					this->_playerBottom->setDir(PRIGHT);  // thanh trượt di chuyển sang phải 
					return distance; // trả về khoảng cách được tính ở trên 
				}
				if ((pos < 0 && distance < this->_playerBottom->getPos().x) || (pos > 0 && distance < this->_playerBottom->getPos().x) || (pos == 0 && distance < this->_playerBottom->getPos().x)) // xét trường hợp vị trí khi thanh trượt nằm bên trái hoặc bên phải hoặc ngang bằng với trái banh và khoảng cách từ tường trái cho đến vị trí đáp xuống ở tường dưới của banh nhỏ hơn khoảng cách của thanh trượt tới tường trái 
				{
					this->_playerBottom->setDir(PLEFT); // thanh trượt di chuyển sang trái 
					return distance; // trả về khoảng cách được tính ở trên
				}
			}
		}
		else
		{
			if (ball_dir == DOWNRIGHT) // trường hợp banh di chuyển xuống qua phải 
			{
				int distance_width = this->_right - ball_pos.x; // khoảng cách từ banh tới tường phải 
				if (distance_width >= distance_height) // trường hợp ban di chuyển chéo màn hình mà không va chạm với tường 
				{
					if (pos < 0 || pos > 0 && distance_height > pos || pos == 0) // xét trường hợp thanh trượt nằm bên trái banh hoặc trường hợp thanh trượt nằm bên phải banh và khoảng cách từ banh tới tường dưới lớn hơn vị trí tương đối của thanh trượt hoặc vị trí của thanh trượt ngang với trái banh
					{
						this->_playerBottom->setDir(PRIGHT); // thanh trượt di chuyển sang phải 
						return ball_pos.x + distance_height; // trả về vị trí của banh trừ cho khoảng cách của banh tới tường dưới 
					}
					if (pos > 0 && distance_height < pos) // thanh trượt nằm bên phải trái banh và khoảng cách từ banh tới biên đối diện nhỏ hơn vị trí tương đối của banh
					{
						this->_playerBottom->setDir(PLEFT); // thanh trượt di chuyển sang trái 
						return ball_pos.x + distance_height; // trả về vị trí của banh trừ cho khoảng cách của banh tới tường dưới 
					}
				}
				else // trường hợp banh di chuyển chéo màn hình có va chạm với tường
				{
					int distance = distance_height - distance_width; // do banh chỉ di chuyển theo gốc 45 độ nên khi lấy khoảng cách từ banh tới tường dưới trừ cho khoảng cách từ banh tới tường phải ta sẽ có được khoảng cách từ tường phải cho đến vị trí banh sẽ đáp xuống ở tường dưới 
					int player_distance_to_right_wall = this->_right - this->_playerBottom->getPos().x; // khoảng cách từ thanh trượt tới tường phải 
					if ((pos < 0 && player_distance_to_right_wall > distance) || (pos > 0 && player_distance_to_right_wall > distance) || (pos == 0 && player_distance_to_right_wall > distance)) // xét trường hợp banh nằm bên trái hoặc bên phải hoặc bằng thanh trượt và khoảng cách từ thanh trượt tới tường phải lớn hơn khoảng cách từ tường phải tới vị trí banh đáp xuống
					{
						this->_playerBottom->setDir(PRIGHT); // thanh trượt di chuyển sang phải 
						return this->_right - distance; // trả về độ rộng màn hình trừ cho khoảng cách từ tường phải tới vị trí đáp xuống của nó ở tường dưới 
					}
					if ((pos < 0 && distance >player_distance_to_right_wall) || (pos > 0 && distance > player_distance_to_right_wall) || (pos == 0 && distance > player_distance_to_right_wall)) // xét trường hợp banh nằm bên trái hoặc bên phải hoặc bằng thanh trượt và khoảng cách từ thanh trượt tới tường phải nhỏ hơn khoảng cách từ tường phải tới vị trí banh đáp xuống
					{
						this->_playerBottom->setDir(PLEFT); // thanh trượt di chuyển sang trái 
						return this->_right - distance; // trả về độ rộng màn hình trừ cho khoảng cách từ tường phải tới vị trí đáp xuống của nó ở tường dưới 
					}
				}
			}
		}
	}
	return dest_pos; // trả về vị trí 
}


// hàm cho thanh trượt trên tự động di chuyển
float Pong::calculatePosTop(float& dest_pos)
{
	balldirection ball_dir = this->_ball->getDir(); // lấy hướng hiện tại của banh
	point ball_pos = this->_ball->getPos(); // lấy vị trí hiện tại của banh
	if (dest_pos == DEFAULT_POS) // nếu đang là vị trí mặc định
	{
		if (ball_dir == DOWN) // hướng banh đi xuống 
		{
			dest_pos = 0; // thì thanh trượt không di chuyển mà trả về vị trí là 0
		}
		if (ball_pos.y == 2) // nếu không xảy ra trường hợp trên và vị trí mặc định được giữ cho tới khi trái banh nằm ở vị trí dưới trên thanh trượt
		{
			//while (_ball_availability == FALSE) //  đợi banh có thể được vẽ 
			//{
			//
			//}
			//while (_paddle_availability == FALSE) // đợi thanh trượt có thể được vẽ 
			//{
			//
			//}
			srand((unsigned int)time(NULL)); // tạo seed cho biến tạo số ngẫu nhiên 
			int random = rand() % 2; // tạo số ngẫu nhiên trong khoảng 0 - 1 
			switch (random) // xét trường hợp của biến ngẫu nhiên
			{
			case 0: // nếu là 0
				this->_playerTop->setDir(PRIGHT); // thanh trượt di chuyển sang phải 
				return 0; // trả về vị trí 0
			case 1: // nếu là 1 
				this->_playerTop->setDir(PLEFT); // thanh trượt di chuyển sang trái 
				return 0; // trả về vị trí 0
			}
		}
		return dest_pos; // trả về vị trí 
	}
	if (this->_playerTop->getRightLimit() - dest_pos <= this->_playerTop->getSideDistance() && dest_pos != 0) // nếu vị trí cần di chuyển tới năm trong khoảng (right limit - side distance, right limit ) thì ta trừ đi cho 2 vì vị trí của thanh trượt được thể hiện luôn là vị trí giữa 
	{
		dest_pos -= (this->_playerTop->getSideDistance() + 1); // trừ đi khoảng di chuyển dư 
		return dest_pos; // trả về vị trí 
	}
	else
	{
		if (dest_pos - this->_playerTop->getLeftLimit() <= 2 && dest_pos != 0) // khoảng ( left limit, left limit + 2 )
		{
			dest_pos += (this->_playerTop->getSideDistance() + 1); // trừ đi khoảng di chuyển dư 
			return dest_pos; // trả về vị trí
		}
	}
	if (this->_playerTop->getPos().x == dest_pos) // nếu tọa độ hiện tại của thanh trượt == với tọa độ cần đên 
	{
		dest_pos = 0; // thì vị trí cần đến là 0
	}
	if (dest_pos == 0) // tiếp tục xét khi vị trí đã là 0
	{
		this->_playerTop->setDir(NONE); // thì thanh trượt ngừng di chuyển
	}
	if (dest_pos == 0 && ball_pos.y == this->_bot - 3 && (ball_dir == UP || ball_dir == UPLEFT || ball_dir == UPRIGHT)) // nếu vị trí cần chuyển tới là 0 , vị trí của banh đang là cách thanh trượt dưới 1 đơn vị và đang di chuyển lên thì thanh trượt bắt đầu tính toán vị trí cần tới mới 
	{
		int distance_height = ball_pos.y - this->_playerTop->getPos().y - 1; // khoảng cách từ banh tới biên đối diện ( tường trên )
		int pos = this->_playerTop->getPos().x - ball_pos.x; // tính vị trị tương đối giữa thanh trượt và trái banh theo tọa độ x
		if (ball_dir == UPLEFT) // trường hợp banh di chuyển lên qua trái
		{
			int distance_width = ball_pos.x - 1; // khoảng cách từ banh tới tường trái 
			if (distance_width >= distance_height) // trường hợp banh di chuyển chéo màn hình mà không va chạm với tường 
			{
				if (pos > 0 || (pos < 0 && abs(pos) < distance_height) || pos == 0) // xét các vị trí thanh trượt năm bên phải banh hoặc thanh trượt nằm bên trái banh nhưng vị trí tượng đối của nó nhỏ hơn khoảng cách tới tường trên ( theo x - tức là di chuyển một khoảng x thì banh sẽ chạm tường trên )
				{
					this->_playerTop->setDir(PLEFT); // thanh trượt sẽ di chuyển sang trái 
					return ball_pos.x - distance_height; // trả về tọa độ x là vị trí banh trừ cho khoảng cách của banh tới đáy trên
				}
				if (pos < 0 && abs(pos) > distance_height) // trường hợp thanh trượt nằm bên trái quả banh và vị trí tương đối của nó lớn hơn khoảng cách từ thanh trượt tới đáy ( theo x )
				{
					this->_playerTop->setDir(PRIGHT); // thanh trượt di chuyển sang phải 
					return ball_pos.x - distance_height; // trả về tọa độ x là vị trí banh trừ cho khoảng cách của banh tới đáy trên
				}
			}
			else // trường hợp banh di chuyển chéo màn hình có va chạm với tường 
			{
				int distance = distance_height - distance_width; // do banh chỉ di chuyển theo gốc 45 độ nên khi lấy khoảng cách từ banh tới tường trên trừ cho khoảng cách từ banh tới tường trái ta sẽ có được khoảng cách từ tường trái cho đến vị trí banh sẽ đáp xuống ở tường trên
				if ((pos < 0 && distance > this->_playerTop->getPos().x) || (pos > 0 && distance > this->_playerTop->getPos().x) || (pos == 0 && distance > this->_playerTop->getPos().x)) // xét trường hợp vị trí khi thanh trượt nằm bên trái hoặc bên phải hoặc ngang bằng với trái banh và khoảng cách từ tường trái cho đến vị trí đáp xuống ở tường trên của banh lớn hơn khoảng cách của thanh trượt tới tường trái 
				{
					this->_playerTop->setDir(PRIGHT);  // thanh trượt di chuyển sang phải 
					return distance; // trả về khoảng cách được tính ở trên 
				}
				if ((pos < 0 && distance < this->_playerTop->getPos().x) || (pos > 0 && distance < this->_playerTop->getPos().x) || (pos == 0 && distance < this->_playerTop->getPos().x)) // xét trường hợp vị trí khi thanh trượt nằm bên trái hoặc bên phải hoặc ngang bằng với trái banh và khoảng cách từ tường trái cho đến vị trí đáp xuống ở tường trên của banh nhỏ hơn khoảng cách của thanh trượt tới tường trái 
				{
					this->_playerTop->setDir(PLEFT); // thanh trượt di chuyển sang trái 
					return distance; // trả về khoảng cách được tính ở trên
				}
			}
		}
		else
		{
			if (ball_dir == UPRIGHT) // trường hợp banh di chuyển lên qua phải 
			{
				int distance_width = this->_right - ball_pos.x; // khoảng cách từ banh tới tường phải
				if (distance_width >= distance_height) // trường hợp ban di chuyển chéo màn hình mà không va chạm với tường 
				{
					if (pos < 0 || pos > 0 && distance_height > pos || pos == 0) // xét trường hợp thanh trượt nằm bên trái banh hoặc trường hợp thanh trượt nằm bên phải banh và khoảng cách từ banh tới tường trên lớn hơn vị trí tương đối của thanh trượt hoặc vị trí của thanh trượt ngang với trái banh
					{
						this->_playerTop->setDir(PRIGHT); // thanh trượt di chuyển sang phải 
						return ball_pos.x + distance_height; // trả về vị trí của banh trừ cho khoảng cách của banh tới tường trên
					}
					if (pos > 0 && distance_height < pos) // thanh trượt nằm bên phải trái banh và khoảng cách từ banh tới biên đối diện nhỏ hơn vị trí tương đối của banh
					{
						this->_playerTop->setDir(PLEFT); // thanh trượt di chuyển sang trái 
						return ball_pos.x + distance_height; // trả về vị trí của banh trừ cho khoảng cách của banh tới tường trên
					}
				}
				else // trường hợp banh di chuyển chéo màn hình có va chạm với tường
				{
					int distance = distance_height - distance_width; // do banh chỉ di chuyển theo gốc 45 độ nên khi lấy khoảng cách từ banh tới tường trên trừ cho khoảng cách từ banh tới tường phải ta sẽ có được khoảng cách từ tường phải cho đến vị trí banh sẽ đáp xuống ở tường trên
					int player_distance_to_right_wall = this->_right - this->_playerTop->getPos().x; // khoảng cách từ thanh trượt tới tường phải 
					if ((pos < 0 && player_distance_to_right_wall > distance) || (pos > 0 && player_distance_to_right_wall > distance) || (pos == 0 && player_distance_to_right_wall > distance)) // xét trường hợp banh nằm bên trái hoặc bên phải hoặc bằng thanh trượt và khoảng cách từ thanh trượt tới tường phải lớn hơn khoảng cách từ tường phải tới vị trí banh đáp xuống
					{
						this->_playerTop->setDir(PRIGHT); // thanh trượt di chuyển sang phải 
						return this->_right - distance; // trả về độ rộng màn hình trừ cho khoảng cách từ tường phải tới vị trí đáp xuống của nó ở tường trên
					}
					if ((pos < 0 && distance >player_distance_to_right_wall) || (pos > 0 && distance > player_distance_to_right_wall) || (pos == 0 && distance > player_distance_to_right_wall)) // xét trường hợp banh nằm bên trái hoặc bên phải hoặc bằng thanh trượt và khoảng cách từ thanh trượt tới tường phải nhỏ hơn khoảng cách từ tường phải tới vị trí banh đáp xuống
					{
						this->_playerTop->setDir(PLEFT); // thanh trượt di chuyển sang trái 
						return this->_right - distance; // trả về độ rộng màn hình trừ cho khoảng cách từ tường phải tới vị trí đáp xuống của nó ở tường trên
					}
				}

			}
		}
	}
	return dest_pos; // trả về vị trí 
}