#ifndef _PONG_H_
#define _PONG_H_

#define PLAYER_SPEED 3
#define PLAYER_HEIGHT 120
#define PLAYER_WIDTH 25
#define PLAYER_TOP 30
#define PLAYER_BOTTOM 640
#define MAX_SCORE 3
#define SCORE_WIDTH 4
#define SCORE_HEIGHT 5
#define BALL_SIZE 20
#define BALL_SPEED 5

enum STATE {GAME_OVER = 0,PLAYING };
enum DIRECTION {DOWN = 0, UP};
void draw_board(void);
void draw_game(void);
void draw_players(void);
void draw_scores(void);
void draw_player_n_score(int n, int x, int y);
void draw_ball();
void player_move(int n, enum DIRECTION dir);
void play(void);
void init_game(void);
void game_loop(void);
void player_score(int n);
void restart_game(void);
void move_ball(void);
void delete_players(void);
void delete_ball(void);
void game_over(void);

typedef struct{
	int x,y, score;
} player_position;

typedef struct{
	int x,y, down, right;
} ball_t;

#endif
