#pragma once
#include "Draw.h"
#include "Ball.h"
#include "Paddle.h"
#include "Screen.h"

// các trạng thái có thể của game ( 4 trạng thái ): END, MENU, PLAYING, INTRO
enum gamestate { END = 0, MENU = 1, PLAYING = 2, INTRO = 3 };

class Pong
{
private:

	// biến thể hiện tốc độ gốc của banh
	float _original_speed;


	// biến thể hiện tốc độ của banh 
	float _speed;


	// biến kiểm tra banh có thể được dùng để vẽ hay chưa ( true == có và false == chưa )
	bool _ball_availability = true;


	// biến kiểm tra thanh trượt có thể được dùng để vẽ hay chưa ( true == có và false == chưa )
	bool _paddle_availability = true;


	// biến thể hiện tình trạng của game
	gamestate _game_state;


	// biến thể hiện điểm của người chơi 1 
	int _score1;


	// biến thể hiện điểm của người chơi 2
	int _score2;


	// biến thể hiện điểm mà người chơi cần để dành chiến thắng 
	int _max_score;


	// bien tren
	int _top;


	// bien duoi
	int _bot;

	//bien trai
	int _left;

	//bien phai
	int _right;

	// con trỏ thể hiện thanh trượt trên
	Paddle* _playerTop;


	// con trỏ thể hiện thanh trượt dưới
	Paddle* _playerBottom;


	// con trỏ thể hiện trái banh
	Ball* _ball;


	// hàm chạy khi kết thúc trò chơi
	//void runEndGame();


	// hàm để cập nhật banh
	void updateBall(SDL_Renderer*& gRenderer);


	// hàm để cập nhật thanh trượt
	void updatePaddle(SDL_Renderer*& gRenderer);


	// hàm cập nhật các vật thể di chuyển trong trò chơi
	void updateGame(SDL_Renderer*& gRenderer);


	// hàm thể hiện bảng điểm 
	void showScoreBoard();


	// hàm cập nhật bảng điểm 
	//void updateScoreBoard();


	// hàm tạo lại tốc độ của banh
	void resetSpeed();


	// hàm gán tốc độ mới với biến đầu vào float thể hiện tốc độ mới 
	void setSpeed(float speed);


	// hàm tạo lại thông tin trò chơi 
	void resetGameInfo();


	// hàm vào giao diện chọn lựa của trò chơi
	//void runMenu();


	// hàm gán điểm tối đa mà người chơi cần đạt được để chiến thắng với biến đầu vào kiểu int thể hiện điểm mới 
	void setMaxScore(int max_score);


	// hàm lấy điểm tối đa hiện tại với biến trả về dạng int là tốc độ hiện tại
	int getMaxScore();


	// hàm cho thanh trượt dưới tự động di chuyển
	float calculatePosBottom(float& dest_pos);

	// hàm cho thanh trượt trên tự động di chuyển 
	float calculatePosTop(float& dest_pos);


	// hàm dùng tốc độ của banh trong trò chơi 
	//void useBallSpeed();


	// hàm làm thanh trượt chậm lại
	void delayPaddle();
public:
	// hàm chạy khi vào màn hình chơi
	void runGame(SDL_Window*& window, SDL_Renderer*& renderer);

	// hàm bắt đàu trò chơi
	void start();


	// constructor của lớp Pong với biến đầu vào lần lượt là chiều rộng , chiều cao màn hình chơi và trạng thái của game 
	Pong(int top, int bot, int left, int right, gamestate game_state);


	// destructor của lớp Pong ( xóa các con trỏ )
	~Pong();
};

