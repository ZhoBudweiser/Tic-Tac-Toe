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
void	initStart		(bool&);													//��ʼ����ʼ����
bool	initBoard		(Board& bd, int size);										//��ʼ������
void	destroyBoard	(Board& bd);												//��������
void	chooseMode		(int&, bool&);												//ѡ��ģʽ PVP or PVC
void	chooseSize		(Board& bd);												//ѡ�����̴�С
void	chooseDiff		(int&);														//ѡ���Ѷ�
void	chooseOrder		(int&);														//ѡ�����˳��
void	chooseAgainPVC	(bool&, bool&, int[3]);										//ѡ���Ƿ����
void	chooseAgainPVP	(bool&, int[3]);											//ѡ���Ƿ����
int		getRet			(Board&);													//ȡ�ñ������
int		getVal			(Board&, char);												//��ù��⺯����ֵ
void	inputChess		(Board&, char);												//����������λ��
void	displayMes		(char);														//չʾ������Ϣ
void	displayChess	(Board&, string, char);										//չʾ����
void	displayRet		(int);														//չʾ���
void	displayScorePVC	(int[3]);													//չʾPVC����ҵĵ÷�
void	displayScorePVP	(int[3]);													//չʾPVP�����˫���ĵ÷�
void	ModePVC			();															//PVCģʽ
void	ModePVP			();															//PVPģʽ
void	ModeDiff		(Board&, int&, bool&, void (*inputModeDiff)(Board& bd));	//�����Ѷ�ģʽ
void	inputModeEasy	(Board&);													//��ģʽ�µ��Գ���
void	inputModeHard	(Board&);													//����ģʽ�µ��Գ���
void	MinMax			(Board&, Node*, char, int);									//����С����
/***********FUNCTION*END********************/

#endif // !TicTacToe

/***********HEARDER*END********************/

