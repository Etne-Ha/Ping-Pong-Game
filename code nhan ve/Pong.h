#pragma once
#include "Draw.h"
#include "Ball.h"
#include "Paddle.h"

// các trạng thái có thể của game ( 4 trạng thái ): END, MENU, PLAYING, INTRO
enum gamestate { END = 0, MENU = 1, PLAYING = 2, INTRO = 3 };

class Pong : protected Draw
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


	// biến thể hiện chiều cao màn hình chơi 
	int _height;


	// biến thể hiện chiều rộng màn hình chơi
	int _width;


	// con trỏ thể hiện thanh trượt trên
	Paddle* _playerTop;


	// con trỏ thể hiện thanh trượt dưới
	Paddle* _playerBottom;


	// con trỏ thể hiện trái banh
	Ball* _ball;


	// hàm chạy khi vào màn hình chơi
	void runGame();


	// hàm chạy khi kết thúc trò chơi
	void runEndGame();


	// hàm để cập nhật banh
	void updateBall();


	// hàm để cập nhật thanh trượt
	void updatePaddle();


	// hàm cập nhật các vật thể di chuyển trong trò chơi
	void updateGame();


	// hàm thể hiện bảng điểm 
	void showScoreBoard();


	// hàm cập nhật bảng điểm 
	void updateScoreBoard();


	// hàm tạo lại tốc độ của banh
	void resetSpeed();


	// hàm gán tốc độ mới với biến đầu vào float thể hiện tốc độ mới 
	void setSpeed(float speed);


	// hàm tạo lại thông tin trò chơi 
	void resetGameInfo();


	// hàm vào giao diện chọn lựa của trò chơi
	void runMenu();


	// hàm gán điểm tối đa mà người chơi cần đạt được để chiến thắng với biến đầu vào kiểu int thể hiện điểm mới 
	void setMaxScore(int max_score);


	// hàm lấy điểm tối đa hiện tại với biến trả về dạng int là tốc độ hiện tại
	int getMaxScore();


	// hàm cho thanh trượt dưới tự động di chuyển
	int calculatePosBottom(int& dest_pos);

	// hàm cho thanh trượt trên tự động di chuyển 
	int calculatePosTop(int& dest_pos);


	// hàm dùng tốc độ của banh trong trò chơi 
	void useBallSpeed();


	// hàm làm thanh trượt chậm lại
	void delayPaddle();
public:

	// hàm bắt đàu trò chơi
	void start();


	// constructor của lớp Pong với biến đầu vào lần lượt là chiều rộng , chiều cao màn hình chơi và trạng thái của game 
	Pong(int width, int height, gamestate game_state);


	// destructor của lớp Pong ( xóa các con trỏ )
	~Pong();
};

