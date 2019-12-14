#include "Menus.h"
//Ham tao Surface dua tren mot chuoi String
SDL_Surface* CreateSurfaceFromString(const char* str, TTF_Font* font, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, str, color);
	return surface;
}

//Khoi tao cac gia tri dau cho viec tao man hinh choi game
//Cau hinh 1257, 730
void Init(SDL_Window*& window, SDL_Renderer*& renderer)
{

	//initializes  the subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return;
	}

	//Create window
	window = SDL_CreateWindow("Ping Pong Game Ultimate!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1257, 730, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		return;
	}


	//create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		return;
	}

	TTF_Init();

}

//Ham hhuy cac gia tri khoi tao man hinh
void Del_Init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer)
{
	//Destroy Renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//Bang menu dau game
int Menu(SDL_Window*& window, SDL_Renderer*& renderer)
{
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect sourceRect;
	SDL_Rect desRect;

	int x, y;
	TTF_Font* font;
	font = TTF_OpenFont("test.ttf", 50);
	const int NUMMENU = 4;
	bool selected[NUMMENU] = {0, 0, 0, 0 };
	//Khoi tao ten cho cac nut man hinh Menu
	const char* menu[NUMMENU] = { "Start", "Score", "Load", "Exit" };
	SDL_Surface* menus[NUMMENU];
	SDL_Rect pos[NUMMENU];

	//Mau khi cham va khong cham cua cac nut man hinh Menu
	SDL_Color color[2] = { { 255, 255, 255 }, { 255, 0, 0 } };

	for (int i = 0; i < NUMMENU; i++)
	{
		menus[i] = TTF_RenderText_Solid(font, menu[i], color[0]);
	}

	SDL_Texture* Message[NUMMENU];
	for (int i = 0; i < NUMMENU; i++)
	{
		Message[i] = SDL_CreateTextureFromSurface(renderer, menus[i]);
	}

	//Khoi tao mang chua vi tri cac nut man hinh Menu
	SDL_Rect despos[NUMMENU];

	for (int i = 0; i < NUMMENU; i++)
	{
		TTF_SizeText(font, menu[i], &pos[i].w, &pos[i].h);
		pos[i].x = 0;
		pos[i].y = 0;

		despos[i].x = 1050 - pos[0].w / 2;
		despos[i].y = 170 + i * 100;

		despos[i].w = pos[i].w;
		despos[i].h = pos[i].h;

	}


	//Background cua man hinh Menu
	//create a tempSurface
	tempSurface = IMG_Load("Image\\background.jpg");
	//create a texutre from surface
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//free surface
	SDL_FreeSurface(tempSurface);
	SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 1257;
	sourceRect.h = 730;

	desRect.x = 0;
	desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;

	//set background color black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//main loop
	SDL_Event e;
	int isRunning = -1;
	while (isRunning==-1)
	{
		// clear the window to black
		SDL_RenderClear(renderer);
		//main event
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			//User - requested quit
			case SDL_QUIT:
			{
				isRunning = 3;
			}
			case SDL_MOUSEMOTION:
			{
				x = e.motion.x;
				y = e.motion.y;
				for (int i = 0; i < NUMMENU; i += 1) {
					if (x >= despos[i].x && x <= despos[i].x + despos[i].w && y >= despos[i].y && y <= despos[i].y + despos[i].h)
					{
						if (!selected[i])
						{
							selected[i] = 1;
							SDL_FreeSurface(menus[i]);
							menus[i] = TTF_RenderText_Solid(font, menu[i], color[1]);
							Message[i] = SDL_CreateTextureFromSurface(renderer, menus[i]);
						}
					}
					else
					{
						if (selected[i])
						{
							selected[i] = 0;
							SDL_FreeSurface(menus[i]);
							menus[i] = TTF_RenderText_Solid(font, menu[i], color[0]);
							Message[i] = SDL_CreateTextureFromSurface(renderer, menus[i]);
						}
					}
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				x = e.motion.x;
				y = e.motion.y;
				for (int i = 0; i < NUMMENU; i += 1) {
					if (x >= despos[i].x && x <= despos[i].x + despos[i].w && y >= despos[i].y && y <= despos[i].y + despos[i].h)
					{
						switch (i)
						{
						case 0:
						{
							pre_start(window, renderer);
							break;
						}
						case 1:
						{
							score(window, renderer);
							break;
						}
						case 2:
						{
							//load(window, renderer);
							break;
						}
						case 3:
						{
							exit(window, renderer);
							isRunning = 3;
							break;
						}
						default:
							break;
						}
					}
				}
				break;
			}
			default:
			{
				break;
			}
			}
		}

		// copy a portion of the texture to the current rendering target.
		SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);


		//Chen cac nut vao man hinh
		for (int i = 0; i < NUMMENU; i++)
		{
			SDL_RenderCopy(renderer, Message[i], &pos[i], &despos[i]);
		}

		SDL_RenderPresent(renderer);

	}

	SDL_FreeSurface(menus[0]);
	SDL_FreeSurface(menus[1]);
	SDL_FreeSurface(menus[2]);
	SDL_FreeSurface(menus[3]);
	
	

	return isRunning;
}

//Nhap ten nguoi choi
string EnterPlayerName(SDL_Window*& window, SDL_Renderer*& renderer)
{
	TTF_Font* font;
	font = TTF_OpenFont("test.ttf", 50);
	SDL_Color color = { 255, 255, 255 };

	//Background cua man hinh
	SDL_Surface* backgr = NULL;
	SDL_Texture* background = NULL;
	SDL_Rect sourceRect;
	SDL_Rect desRect;

	backgr = IMG_Load("Image\\inname.jpg");
	background = SDL_CreateTextureFromSurface(renderer, backgr);
	SDL_FreeSurface(backgr);
	SDL_QueryTexture(background, NULL, NULL, &sourceRect.w, &sourceRect.h);

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 1257;
	sourceRect.h = 730;

	desRect.x = 0;
	desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;

	//Nut Back 
	SDL_Surface* bc=NULL;
	SDL_Texture* back = NULL;
	SDL_Rect rect;
	SDL_Rect b_rect;
	const char* back_k = "Back";
	bc = TTF_RenderText_Solid(font, back_k, color);
	back = SDL_CreateTextureFromSurface(renderer, bc);
	SDL_FreeSurface(bc);
	TTF_SizeText(font, back_k, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;

	b_rect.x = 100 - rect.w / 2;
	b_rect.y = 600;

	b_rect.w = rect.w;
	b_rect.h = rect.h;


	string text = "";
	SDL_StartTextInput();
	SDL_Surface* temp;
	SDL_Texture* texture;

	
	SDL_Rect pos;
	SDL_Rect despos;
	SDL_Event e;
	pos.x = 0;
	pos.y = 0;

	despos.y = 340;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	int x, y;
	SDL_RenderCopy(renderer, background, &sourceRect, &desRect);
	bool selected = false;
	bool isRunning = true;
	while (isRunning)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			//Getting the quit and  the keyboard events
			switch (e.type)
			{
			case SDL_QUIT:
			{
				SDL_Quit();
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				x = e.motion.x;
				y = e.motion.y;
				if (x >= b_rect.x && x <= b_rect.x + b_rect.w && y >= b_rect.y && y <= b_rect.y + b_rect.h)
				{
					return "";
				}
				break;
			}
			default:
			{
				break;
			}
			}


			if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN)
			{
				if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN) && text.length() > 0)
					return text;
				SDL_RenderCopy(renderer, background, &sourceRect, &desRect);
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE &&text.length() > 0)
					text = text.substr(0, text.length() - 1);
				else if (e.type == SDL_TEXTINPUT && text.size() <= 15)
					text += e.text.text;
				const int n = text.length();
				temp = CreateSurfaceFromString(text.c_str(), font, color);
				texture = SDL_CreateTextureFromSurface(renderer, temp);
				SDL_FreeSurface(temp);
				TTF_SizeText(font, text.c_str(), &pos.w, &pos.h);

				despos.x = 600 - pos.w / 2;

				despos.w = pos.w;
				despos.h = pos.h;

				SDL_RenderCopy(renderer, texture, &pos, &despos);
			}
		}
		SDL_RenderCopy(renderer, back, &rect, &b_rect);
		SDL_RenderPresent(renderer);

	}

	SDL_StopTextInput();

	return text;
}

//Bang Chon the loai choi 
int pre_start(SDL_Window*& window, SDL_Renderer*& renderer)
{
	string name_player = EnterPlayerName(window, renderer);
	if (name_player == "")
		return 0;
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect sourceRect;
	SDL_Rect desRect;

	int x, y;
	TTF_Font* font;
	font = TTF_OpenFont("test.ttf", 50);
	const int NUMMENU = 3;
	bool selected[NUMMENU] = { 0, 0, 0};
	//Khoi tao ten cho cac nut man hinh Menu
	const char* menu[NUMMENU] = { "Modern", "Classic", "Back" };
	SDL_Surface* menus[NUMMENU];
	SDL_Rect pos[NUMMENU];

	//Mau khi cham va khong cham cua cac nut man hinh Menu
	SDL_Color color[2] = { { 255, 255, 255 }, { 255, 0, 0 } };

	for (int i = 0; i < NUMMENU; i++)
	{
		menus[i] = TTF_RenderText_Solid(font, menu[i], color[0]);
	}

	SDL_Texture* Message[NUMMENU];
	for (int i = 0; i < NUMMENU; i++)
	{
		Message[i] = SDL_CreateTextureFromSurface(renderer, menus[i]);
	}

	//Khoi tao mang chua vi tri cac nut man hinh Menu
	SDL_Rect despos[NUMMENU];

	for (int i = 0; i < NUMMENU; i++)
	{
		TTF_SizeText(font, menu[i], &pos[i].w, &pos[i].h);
		pos[i].x = 0;
		pos[i].y = 0;

		despos[i].x = 1075 - pos[0].w / 2;
		despos[i].y = 200 + i * 100;

		despos[i].w = pos[i].w;
		despos[i].h = pos[i].h;

	}


	//Background cua man hinh Menu
	//create a tempSurface
	tempSurface = IMG_Load("Image\\typegame.jpeg");
	//create a texutre from surface
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//free surface
	SDL_FreeSurface(tempSurface);
	SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 1257;
	sourceRect.h = 730;

	desRect.x = 0;
	desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	
	//Tao cac demo choi game
	SDL_Surface* demo = NULL;
	SDL_Texture* demo1 = NULL;
	SDL_Texture* demo2 = NULL;
	SDL_Rect d_rect1, d_rect2, d_desrect1, d_desrect2;

	demo = IMG_Load("Image//demo1.bmp");
	demo1 = SDL_CreateTextureFromSurface(renderer, demo);

	demo = IMG_Load("Image//demo2.bmp");
	demo2 = SDL_CreateTextureFromSurface(renderer, demo);

	//Set toa do cua cac hinh demo

	d_rect1.x = 0;
	d_rect1.y = 0;
	d_rect1.w = 340;
	d_rect1.h = 470;

	d_desrect1.x = 209;
	d_desrect1.y = 130;
	d_desrect1.w = d_rect1.w;
	d_desrect1.h = d_rect1.h;

	d_rect2.x = 0;
	d_rect2.y = 0;
	d_rect2.w = 340;
	d_rect2.h = 470;

	d_desrect2.x = 209;
	d_desrect2.y = 130;
	d_desrect2.w = d_rect2.w;
	d_desrect2.h = d_rect2.h;

	

	//set background color black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_Event e;
	int isRunning = -1;
	while (isRunning == -1)
	{
		// clear the window to black
		SDL_RenderClear(renderer);
		//main event
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				//User - requested quit
			case SDL_QUIT:
			{
				SDL_Quit();
			}
			case SDL_MOUSEMOTION:
			{
				x = e.motion.x;
				y = e.motion.y;
				for (int i = 0; i < NUMMENU; i += 1) {
					if (x >= despos[i].x && x <= despos[i].x + despos[i].w && y >= despos[i].y && y <= despos[i].y + despos[i].h)
					{
						if (!selected[i])
						{
							selected[i] = 1;
							SDL_FreeSurface(menus[i]);
							menus[i] = TTF_RenderText_Solid(font, menu[i], color[1]);
							Message[i] = SDL_CreateTextureFromSurface(renderer, menus[i]);
						}
						
						
					}
					else
					{
						if (selected[i])
						{
							selected[i] = 0;
							SDL_FreeSurface(menus[i]);
							menus[i] = TTF_RenderText_Solid(font, menu[i], color[0]);
							Message[i] = SDL_CreateTextureFromSurface(renderer, menus[i]);
						}
					}
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				x = e.motion.x;
				y = e.motion.y;
				for (int i = 0; i < NUMMENU; i += 1) {
					if (x >= despos[i].x && x <= despos[i].x + despos[i].w && y >= despos[i].y && y <= despos[i].y + despos[i].h)
					{
						isRunning = i;
						switch (isRunning)
						{
						case 0:
						{
							Start_new(window, renderer, name_player);
							break;
						}
						case 1:
						{
							//Start_classic();
							break;
						}
						case 2:
						{
							return -1;
						}
						default:
							break;
						}
					}
				}
				break;
			}
			default:
			{
				break;
			}
			}
		}

		// copy a portion of the texture to the current rendering target.
		SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);


		//Chen cac nut vao man hinh
		for (int i = 0; i < NUMMENU; i++)
		{
			SDL_RenderCopy(renderer, Message[i], &pos[i], &despos[i]);
		}
		if (selected[0])
			SDL_RenderCopy(renderer, demo1, &d_rect1, &d_desrect1);

		if (selected[1])
			SDL_RenderCopy(renderer, demo2, &d_rect2, &d_desrect2);

		SDL_RenderPresent(renderer);

	}

	return 0;
}

//Bang Top nhung nguoi choi co so diem cao nhat
void score(SDL_Window*& window, SDL_Renderer*& renderer)
{
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect sourceRect;
	SDL_Rect desRect;
	char* back = "Back";

	int x, y;
	TTF_Font* font;
	font = TTF_OpenFont("test.ttf", 50);
	const int highScore = 10;
	bool selected;
	//Khoi tao ten cho cac nut man hinh high score
	char menu[highScore][11];

	FILE* file;
	file= fopen("HighScore.txt", "r");
	if (file == NULL)
	{
		cout << "Loi mo file\n";
	}
	for (int j = 0; j < highScore;j++)
	{
		fscanf(file, "%s[^\n]", menu[j]);
	}
	fclose(file);

	//Mau khi cham va khong cham cua cac nut man hinh high score
	SDL_Color color[2] = { { 255, 255, 255 }, { 255, 0, 0 } };
	
	SDL_Surface* menus[highScore];
	SDL_Surface* back_b;
	SDL_Rect pos[highScore];
	

	back_b = TTF_RenderText_Solid(font, back, color[0]);

	for (int i = 0; i < highScore; i++)
	{
		menus[i] = CreateSurfaceFromString(menu[i], font, color[0]);
	}

	SDL_Texture* Message[highScore];
	SDL_Texture* mess_back;
	mess_back = SDL_CreateTextureFromSurface(renderer, back_b);

	for (int i = 0; i < highScore; i++)
	{
		Message[i] = SDL_CreateTextureFromSurface(renderer, menus[i]);
	}

	//Khoi tao mang chua vi tri cac nut man hinh high score
	SDL_Rect despos[highScore];

	for (int i = 0; i < highScore; i+=2)
	{
		TTF_SizeText(font, menu[i], &pos[i].w, &pos[i].h);
		pos[i].x = 0;
		pos[i].y = 0;

		despos[i].x = 430 - pos[0].w / 2;
		despos[i].y = 180 + i/2 * 94;

		despos[i].w = pos[i].w;
		despos[i].h = pos[i].h;

		TTF_SizeText(font, menu[i+1], &pos[i+1].w, &pos[i+1].h);
		pos[i+1].x = 0;
		pos[i+1].y = 0;

		despos[i+1].x = 750 - pos[1].w / 2;
		despos[i+1].y = 180 + i/2 * 94;

		despos[i+1].w = pos[i+1].w;
		despos[i+1].h = pos[i+1].h;

	}
	//Nut Back
	SDL_Rect b_pos;
	SDL_Rect b_despos;
	TTF_SizeText(font, back, &b_pos.w, &b_pos.h);
	b_pos.x = 0;
	b_pos.y = 0;

	b_despos.x = 100 - b_pos.w / 2;
	b_despos.y = 600;

	b_despos.w = b_pos.w;
	b_despos.h = b_pos.h;

	//Background cua man hinh high score
	//create a tempSurface
	tempSurface = IMG_Load("Image\\highscore.jpg");
	//create a texutre from surface
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//free surface
	SDL_FreeSurface(tempSurface);
	SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 1257;
	sourceRect.h = 730;

	desRect.x = 0;
	desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;

	//set background color black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_Event e;
	int isRunning = -1;
	while (isRunning == -1)
	{
		// clear the window to black
		SDL_RenderClear(renderer);
		//main event
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				//User - requested quit
			case SDL_QUIT:
			{
				SDL_Quit();
			}
			case SDL_MOUSEMOTION:
			{
				x = e.motion.x;
				y = e.motion.y;
				if (x >= b_despos.x && x <= b_despos.x + b_despos.w && y >= b_despos.y && y <= b_despos.y + b_despos.h)
				{
					if (!selected)
					{
						selected = 1;
						SDL_FreeSurface(back_b);
						back_b = TTF_RenderText_Solid(font, back, color[1]);
						mess_back = SDL_CreateTextureFromSurface(renderer, back_b);
					}
				}
				else
				{
					if (selected)
					{
						selected = 0;
						SDL_FreeSurface(back_b);
						back_b = TTF_RenderText_Solid(font, back, color[0]);
						mess_back = SDL_CreateTextureFromSurface(renderer, back_b);
					}
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				x = e.motion.x;
				y = e.motion.y;
				for (int i = 0; i < highScore; i += 1) {
					if (x >= b_despos.x && x <= b_despos.x + b_despos.w && y >= b_despos.y && y <= b_despos.y + b_despos.h)
					{
						return;
					}
				}
				break;
			}
			default:
			{
				break;
			}
			}
		}

		// copy a portion of the texture to the current rendering target.
		SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);


		//Chen cac nut vao man hinh
		for (int i = 0; i < highScore; i++)
		{
			SDL_RenderCopy(renderer, Message[i], &pos[i], &despos[i]);
		}

		SDL_RenderCopy(renderer, mess_back, &b_pos, &b_despos);

		SDL_RenderPresent(renderer);

	}

	return;
}

//Bang load Game da save
void load(SDL_Window*& window, SDL_Renderer*& renderer);

//Ham thoat game
void exit(SDL_Window*& window, SDL_Renderer*& renderer)
{
	Del_Init(window, renderer);
}

//Choi game the loai moi
void Start_new(SDL_Window*& window, SDL_Renderer*& renderer, string name)
{
	const int numb_obj = 160;
	int ox[numb_obj];
	int oy[numb_obj];
	int key[numb_obj];
	int numb = 0;
	ifstream file;
	file.open("map//4.txt");
	if (!file)
	{
		cout << "mo file loi" << endl;
	}
	while (!file.eof())
	{
		file >> ox[numb] >> oy[numb] >> key[numb];
		numb++;
	}
	//Bo dong cuoi cung trong file map
	numb--;
	file.close();

	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect sourceRect;
	SDL_Rect desRect;

	int x, y;
	//Creat object from file
	SDL_Surface* obj[3];
	obj[0] = IMG_Load("init\\obj_1.bmp");
	obj[1] = IMG_Load("init\\obj_2.bmp");
	obj[2] = IMG_Load("init\\obj_3.bmp");
	SDL_Texture* object[numb_obj];

	SDL_Rect rect[numb_obj];
	SDL_Rect keyRect[numb_obj];
	for (int i = 0; i < numb; i++)
	{
		object[i] = SDL_CreateTextureFromSurface(renderer, obj[key[i] - 1]);
		SDL_QueryTexture(object[i], NULL, NULL, &rect[i].w, &rect[i].h);
		rect[i].x = 0;
		rect[i].y = 0;

		keyRect[i].x = ox[i] + 444;
		keyRect[i].y = oy[i] + 140;

		keyRect[i].w = rect[i].w;
		keyRect[i].h = rect[i].h;
	}

	//Save Game
	SDL_Surface* s;
	SDL_Texture* save;
	SDL_Color color[2] = { { 255, 255, 255 }, { 255, 0, 0 } };
	const char* sa = "Save";
	SDL_Rect s_rect;
	SDL_Rect s_desrect;
	TTF_Font* font;
	font = TTF_OpenFont("test.ttf" , 50);

	s = TTF_RenderText_Solid(font, sa, color[0]);
	save = SDL_CreateTextureFromSurface(renderer, s);

	TTF_SizeText(font, sa, &s_rect.w, &s_rect.h);
	s_rect.x = 0;
	s_rect.y = 0;

	s_desrect.x = 150 - s_rect.w / 2;
	s_desrect.y = 600;

	s_desrect.w = s_rect.w;
	s_desrect.h = s_rect.h;

	//Khung diem so
	SDL_Surface* temp;
	SDL_Texture* text;
	SDL_Rect sc_rect, sc_desrect;

	sc_rect.x = 0;
	sc_rect.y = 0;

	sc_desrect.y = 150;

	//Background cua man hinh Menu
	//create a tempSurface
	tempSurface = IMG_Load("Image\\ingame.bmp");
	//create a texutre from surface
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//free surface
	SDL_FreeSurface(tempSurface);
	SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 1257;
	sourceRect.h = 730;

	desRect.x = 0;
	desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;

	int score = 0;
	int last_score = 0;
	string score_text="100";
	SDL_Event e;
	int selected =0;
	while (true)
	{
		SDL_RenderClear(renderer);
		//main event
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				//User - requested quit
			case SDL_QUIT:
			{
				SDL_Quit();
			}
			case SDL_MOUSEMOTION:
			{
				x = e.motion.x;
				y = e.motion.y;

				if (x >= s_desrect.x && x <= s_desrect.x + s_desrect.w && y >= s_desrect.y && y <= s_desrect.y + s_desrect.h)
				{
					if (!selected)
					{
						selected = 1;
						SDL_FreeSurface(s);
						s = TTF_RenderText_Solid(font, sa, color[1]);
						save = SDL_CreateTextureFromSurface(renderer, s);
					}
				}
				else
				{
					if (selected)
					{
						selected = 0;
						SDL_FreeSurface(s);
						s = TTF_RenderText_Solid(font, sa, color[0]);
						save = SDL_CreateTextureFromSurface(renderer, s);
					}
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				x = e.motion.x;
				y = e.motion.y;

				if (x >= s_desrect.x && x <= s_desrect.x + s_desrect.w && y >= s_desrect.y && y <= s_desrect.y + s_desrect.h)
				{
					ofstream file;
					string str = "save\\" + name + ".txt";
					file.open(str);
					for (int i = 0; i < numb; i++)
					{
						if (key[i] != 0)
						{
							file << ox[i] << "	" << oy[i] << "	" << key[i] << endl;
						}
					}

					file.close();
					Save(window, renderer, name);

					SDL_Surface* shit;
					SDL_Texture* shit_t;
					SDL_Rect t_rect, t_desrect;

					TTF_Font* font1 = TTF_OpenFont("test.ttf", 100);


					const char* sh = "Saved";

					shit = TTF_RenderText_Solid(font1, sh, color[0]);
					shit_t = SDL_CreateTextureFromSurface(renderer, shit);

					TTF_SizeText(font1, sh, &t_rect.w, &t_rect.h);

					t_rect.x = 0;
					t_rect.y = 0;

					t_desrect.x = 400 + t_rect.w / 2;
					t_desrect.y = 500 / 2 + t_rect.h / 2;
					t_desrect.w = t_rect.w;
					t_desrect.h = t_rect.h;

					SDL_FreeSurface(shit);

					int k = 0;
					int i = 0;
					SDL_RenderCopy(renderer, shit_t, &t_rect, &t_desrect);
					SDL_RenderPresent(renderer);
					while (true)
					{
						while (SDL_PollEvent(&e))
						{
							
						}
						SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
						SDL_RenderCopy(renderer, text, &sc_rect, &sc_desrect);
						//Chen cac object vao man hinh
						for (int i = 0; i < numb; i++)
						{
							SDL_RenderCopy(renderer, object[i], &rect[i], &keyRect[i]);
						}

						SDL_RenderCopy(renderer, save, &s_rect, &s_desrect);
						SDL_RenderCopy(renderer, shit_t, &t_rect, &t_desrect);
						SDL_RenderPresent(renderer);
						if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN))
						{
							break;
						}
					}
				}
				break;
			}
			default:
			{
				break;
			}
			}
		}
		score++;
		if (score != last_score)
		{
			last_score = score;
			score_text = to_string(last_score);
			temp = CreateSurfaceFromString(score_text.c_str(), font, color[0]);
			text = SDL_CreateTextureFromSurface(renderer, temp);
			SDL_FreeSurface(temp);
			TTF_SizeText(font, score_text.c_str(), &sc_rect.w, &sc_rect.h);

			sc_desrect.x = 150 - sc_rect.w / 2;

			sc_desrect.w = sc_rect.w;
			sc_desrect.h = sc_rect.h;
		}
		
		SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
		SDL_RenderCopy(renderer, text, &sc_rect, &sc_desrect);
		//Chen cac object vao man hinh
		for (int i = 0; i < numb; i++)
		{
			SDL_RenderCopy(renderer, object[i], &rect[i], &keyRect[i]);
		}
		
		SDL_RenderCopy(renderer, save, &s_rect, &s_desrect);
		SDL_RenderPresent(renderer);
	}
}

//Choi game the loai co dien dooi khang 1v1
void Start_classic();

//Khung save game
void Save(SDL_Window*& window, SDL_Renderer*& renderer, string name)
{
	fstream file;
	file.open("save\\dat.txt");
	string str;
	bool ktr = true;
	while (!file.eof())
	{
		getline(file, str);
		if (str.compare(name) == 0)
		{
			ktr = false;
			break;
		}
	}
	if (ktr == true)
	{
		file << name << endl;
	}

	file.close();
}