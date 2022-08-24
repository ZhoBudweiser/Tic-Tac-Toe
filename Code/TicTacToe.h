/***********HEARDER*START********************/

#ifndef TicTacToe

#define TicTacToe

/***********INCLUDE*START********************/
#include <iostream>
#include <string>
#include <graphics.h>
#include <ctime>
using namespace std;
/***********INCLUDE*END********************/

/***********DEFINE*START********************/
#define N 3
#define MAX true
#define MIN false
#define PINF 50
#define NINF -50
/***********DEFINE*END********************/

/***********DS*START********************/
typedef struct {
	char** cell;
	int size;
	int emptyNum;
}Board;

typedef struct tree{
	int val;
	int row;
	int col;
	int alpha;
	int beta;
	bool level;
	struct tree* firstChild;
	struct tree* nextSibling;
}Node, *Tree;
/***********DS*END********************/

/***********FUNCTION*START********************/
void	initStart		(bool&);													//初始化开始界面
bool	initBoard		(Board& bd, int size);										//初始化棋盘
void	destroyBoard	(Board& bd);												//销毁棋盘
void	chooseMode		(int&, bool&);												//选择模式 PVP or PVC
void	chooseSize		(Board& bd);												//选择棋盘大小
void	chooseDiff		(int&);														//选择难度
void	chooseOrder		(int&);														//选择出棋顺序
void	chooseAgainPVC	(bool&, bool&, int[3]);										//选择是否继续
void	chooseAgainPVP	(bool&, int[3]);											//选择是否继续
int		getRet			(Board&);													//取得比赛结果
int		getVal			(Board&, char);												//获得估测函数的值
void	inputChess		(Board&, char);												//获得玩家落棋位置
void	displayMes		(char);														//展示出棋信息
void	displayChess	(Board&, string, char);										//展示棋子
void	displayRet		(int);														//展示结果
void	displayScorePVC	(int[3]);													//展示PVC下玩家的得分
void	displayScorePVP	(int[3]);													//展示PVP下玩家双方的得分
void	ModePVC			();															//PVC模式
void	ModePVP			();															//PVP模式
void	ModeDiff		(Board&, int&, bool&, void (*inputModeDiff)(Board& bd));	//各种难度模式
void	inputModeEasy	(Board&);													//简单模式下电脑出棋
void	inputModeHard	(Board&);													//困难模式下电脑出棋
void	MinMax			(Board&, Node*, char, int);									//极大极小搜索
/***********FUNCTION*END********************/

#endif // !TicTacToe

/***********HEARDER*END********************/

