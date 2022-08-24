//*********************************************************
//程 序 名 称: 一  字  棋.cpp
//姓       名: 周  布  伟
//修 改 时 间: 2021/07/09
//学       号: 2019217192
//*********************************************************

/********************************FILE*START***********************************/

/***********INCLUDE*START********************/
#include "TicTacToe.h"
/***********INCLUDE*END********************/

/***********FUNCTION*START********************/

/*------------------------------------------------
/   函数名： main
/   作  用： 初始化界面，选择模式、是否继续游戏
/   参  数： 无
/   返回值： 整型
/-------------------------------------------------*/
int main(void)
{
	int mode = 0;
	bool againGame = 1;

	initStart(againGame);


	while (againGame)
	{
		mode = 0;
		chooseMode(mode, againGame);
		switch (mode)
		{
			case 1:
				ModePVP();
				break;
			case 2:
				ModePVC();
				break;
		}
	}


	return 0;
}

/*------------------------------------------------
/   函数名： initStart
/   作  用： 展示开始界面，选择是否开始游戏
/   参  数： start，布尔型，是否开始游戏
/   返回值： 无
/-------------------------------------------------*/
void initStart(bool &start)
{
	initgraph(1200, 800, SHOWCONSOLE);
	loadimage(0, _T("./图片/start.jpg"), 1200, 800);
	bool isChoose = false;	//玩家是否作出选择
	while (!isChoose)
	{
		if (MouseHit())
		{
			MOUSEMSG mouse = GetMouseMsg();
			if (mouse.uMsg == WM_LBUTTONDOWN)
			{
				if (mouse.y > 400 && mouse.y < 700 && mouse.x > 400 && mouse.x < 800)
				{
					start = 1;
					isChoose = true;
				}
				else if (mouse.y > 600 && mouse.y < 800 && mouse.x > 0 && mouse.x < 200)
				{
					start = 0;
					isChoose = true;
				}
			}
		}
	}

}

/*------------------------------------------------
/   函数名： initBoard
/   作  用： 初始化棋盘
/   参  数： bd，棋盘型，保存棋盘结果
/			 size, int型，设定棋盘大小
/   返回值： bool型，初始化结果
/-------------------------------------------------*/
bool initBoard(Board& bd, int size)
{
	if (size < 3 && size > 5)
	{
		return false;
	}

	bd.size = size;
	bd.cell = (char**)malloc(sizeof(char*) * size);
	if (bd.cell)
	{
		for (int i = 0; i < bd.size; i++)
		{
			bd.cell[i] = (char*)malloc(sizeof(char) * size);
		}
		for (int i = 0; i < bd.size; i++)
		{
			for (int j = 0; j < bd.size; j++)
			{
				bd.cell[i][j] = ' ';
			}
		}

		bd.emptyNum = bd.size * bd.size;
	}

	return true;
}

/*------------------------------------------------
/   函数名： destroyBoard
/   作  用： 销毁棋盘
/   参  数： bd，棋盘型，保存棋盘结果
/   返回值： 无
/-------------------------------------------------*/
void destroyBoard(Board& bd)
{
	for (int i = 0; i < bd.size; i++)
	{
		free(bd.cell[i]);
	}

	free(bd.cell);
}

/*------------------------------------------------
/   函数名： chooseSize
/   作  用： 选择棋盘大小
/   参  数： bd，棋盘型，保存棋盘结果
/   返回值： 无
/-------------------------------------------------*/
void chooseSize(Board& bd)
{
	loadimage(0, _T("./图片/SizeChoose.jpg"), 1200, 800);
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG mouse = GetMouseMsg();
			if (mouse.uMsg == WM_LBUTTONDOWN)
			{
				if (mouse.y > 0 && mouse.y < 350)
				{
					bd.size = 3;
					break;
				}
				else if (mouse.y > 350 && mouse.y < 550)
				{
					bd.size = 4;
					break;
				}
				else if (mouse.y > 550 && mouse.y < 690)
				{
					bd.size = 5;
					break;
				}
			}
		}
	}
}

/*------------------------------------------------
/   函数名： chooseMode
/   作  用： 选择游戏模式是PVP还是PVC
/   参  数： mode，int型，游戏模式
/			 againGame，布尔型，是否继续游戏
/   返回值： 无
/-------------------------------------------------*/
void chooseMode(int &mode, bool& againGame)
{
	
	loadimage(0, _T("./图片/ModeChoose.jpg"), 1200, 800);
	while (mode == 0)
	{
		if (MouseHit())
		{
			MOUSEMSG mouse = GetMouseMsg();
			if (mouse.uMsg == WM_LBUTTONDOWN)
			{
				if (mouse.x > 140 && mouse.x < 1060 && mouse.y > 160 && mouse.y < 350)
				{
					mode = 1;	//PVP模式
				}
				else if (mouse.x > 140 && mouse.x < 1060 && mouse.y > 480 && mouse.y < 680)
				{
					mode = 2;	//PVC模式
				}else if (mouse.x > 20 && mouse.x < 130 && mouse.y > 710 && mouse.y < 770)
				{
					againGame = 0;	//退出游戏
					break;
				}
			}
		}
	}
}

/*------------------------------------------------
/   函数名： chooseDiff
/   作  用： 选择难度是简单、中等还是困难
/   参  数： diff，短整型，游戏难度
/   返回值： 无
/-------------------------------------------------*/
void chooseDiff(int &diff)
{
	loadimage(0, _T("./图片/DiffChoose.jpg"), 1200, 800);
	while (!diff)
	{
		if (MouseHit())
		{
			MOUSEMSG mouse = GetMouseMsg();
			if (mouse.uMsg == WM_LBUTTONDOWN)
			{
				if (mouse.y > 0 && mouse.y < 350)
				{
					diff = 1;	//简单模式
				}else if (mouse.y > 350 && mouse.y < 550)
				{
					diff = 2;	//中等模式
				}else if (mouse.y > 550 && mouse.y < 690)
				{
					diff = 3;	//困难模式
				}
			}
		}
	}
}

/*------------------------------------------------
/   函数名： chooseOrder
/   作  用： 在PVC模式下，选择玩家和电脑的出棋顺序
/   参  数： order，int型，出棋顺序
/   返回值： 无
/-------------------------------------------------*/
void chooseOrder(int &order)
{
	loadimage(0, _T("./图片/OrderChoose.jpg"), 1200, 800);
	while (!order)
	{
		if (MouseHit())
		{
			MOUSEMSG mouse = GetMouseMsg();
			if (mouse.uMsg == WM_LBUTTONDOWN)
			{
				if (mouse.y > 0 && mouse.y < 450)
				{
					order = 1;	//玩家优先
				}
				else if (mouse.y > 450 && mouse.y < 800)
				{
					order = 2;	//计算机优先
				}
			}
		}
	}
}

/*------------------------------------------------
/   函数名： chooseAgainPVC
/   作  用： 一局游戏结束后选择再试一次、返回主菜单、清空结果
/   参  数： againMode，布尔型，是否再试一次该模式下的游戏
			 againPVC，布尔型，是否继续PVC
			 cntRet[3]，int型数组，保存该模式下的游戏结果
/   返回值： 无
/-------------------------------------------------*/
void chooseAgainPVC(bool &againMode, bool &againPVC, int cntRet[3])
{
	bool isChoose = 0;
	IMAGE imageEmpty;
	loadimage(0, _T("./图片/PVCResDisplay.jpg"), 1200, 800);
	displayScorePVC(cntRet);
	while (!isChoose)
	{
		if (MouseHit())
		{
			MOUSEMSG mouse = GetMouseMsg();
			if (mouse.uMsg == WM_LBUTTONDOWN)
			{
				if (mouse.x > 60 && mouse.x < 260 && mouse.y > 550 && mouse.y < 640)
				{
					againMode = 1;	//再来一次
					isChoose = 1;
				}else if (mouse.x > 470 && mouse.x < 720 && mouse.y > 550 && mouse.y < 640)
				{
					againPVC = 0;	//返回主菜单
					againMode = 0;
					for (int i = 0; i < 3; i++)	//清空得分
					{
						cntRet[i] = 0;
					}
					isChoose = 1;
				}else if (mouse.x > 920 && mouse.x < 1130 && mouse.y > 550 && mouse.y < 640)
				{
					loadimage(&imageEmpty, _T("./图片/empty.jpg"), 140, 90);
					putimage(315, 320, &imageEmpty);
					putimage(530, 320, &imageEmpty);
					putimage(720, 320, &imageEmpty);
					for (int i = 0; i < 3; i++)
					{
						cntRet[i] = 0;
					}
				}
			}
		}
	}
}

/*------------------------------------------------
/   函数名： chooseAgainPVP
/   作  用： 一局游戏结束后选择再试一次、返回主菜单、清空结果
/   参  数： againPVC，布尔型，是否继续PVC
			 cntRet[3]，int型数组，保存该模式下的游戏结果
/   返回值： 无
/-------------------------------------------------*/
void chooseAgainPVP(bool &againPVP, int cntRet[3])
{
	bool isChoose = 0;
	IMAGE imageEmpty;
	loadimage(0, _T("./图片/PVPResDisplay.jpg"), 1200, 800);
	displayScorePVP(cntRet);
	while (!isChoose)
	{
		if (MouseHit())
		{
			MOUSEMSG mouse = GetMouseMsg();
			if (mouse.uMsg == WM_LBUTTONDOWN)
			{
				if (mouse.x > 85 && mouse.x < 290 && mouse.y > 715 && mouse.y < 790)
				{
					againPVP = 1;	//再来一次
					isChoose = 1;
				}
				else if (mouse.x > 495 && mouse.x < 730 && mouse.y > 715 && mouse.y < 790)
				{
					againPVP = 0;	//返回主菜单
					for (int i = 0; i < 3; i++)	//清空得分
					{
						cntRet[i] = 0;
					}
					isChoose = 1;
				}
				else if (mouse.x > 945 && mouse.x < 1150 && mouse.y > 715 && mouse.y < 790)
				{
					loadimage(&imageEmpty, _T("./图片/empty.jpg"), 140, 90);
					putimage(430, 190, &imageEmpty);
					putimage(640, 190, &imageEmpty);
					putimage(840, 190, &imageEmpty);
					putimage(430, 490, &imageEmpty);
					putimage(640, 490, &imageEmpty);
					putimage(840, 490, &imageEmpty);
					for (int i = 0; i < 3; i++)
					{
						cntRet[i] = 0;
					}
				}
			}
		}
	}
}

/*------------------------------------------------
/   函数名： getRet
/   作  用： 判断比赛时的胜负或还在进行中
/   参  数： bd，棋盘型，保存棋盘结果
/   返回值： 短整型，0：游戏进行中；1：*胜利；2：@胜利；3：平局
/-------------------------------------------------*/
int getRet(Board& bd)
{
	//行
	for (int i = 0; i < bd.size; i++)
	{
		for (int j = 0; j <= bd.size - 3; j++)
		{
			if (bd.cell[i][j] != ' ' && bd.cell[i][j] == bd.cell[i][j + 1] && bd.cell[i][j + 1] == bd.cell[i][j + 2])
			{
				return bd.cell[i][j] == '*' ? 1 : 2;
			}
		}
	}

	//列
	for (int i = 0; i <= bd.size - 3; i++)
	{
		for (int j = 0; j < bd.size; j++)
		{
			if (bd.cell[i][j] != ' ' && bd.cell[i][j] == bd.cell[i + 1][j] && bd.cell[i + 1][j] == bd.cell[i + 2][j])
			{
				return bd.cell[i][j] == '*' ? 1 : 2;
			}
		}
	}

	//主上三角对角线
	for (int j = 0; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i][i + j] != ' ' && bd.cell[i][i + j] == bd.cell[i + 1][i + 1 + j] && bd.cell[i + 1][i + 1 + j] == bd.cell[i + 2][i + 2 + j])
			{
				return bd.cell[i][i + j] == '*' ? 1 : 2;
			}
		}
	}
	//主下三角对角线
	for (int j = 1; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i + j][i] != ' ' && bd.cell[i + j][i] == bd.cell[i + 1 + j][i + 1] && bd.cell[i + 1 + j][i + 1] == bd.cell[i + 2 + j][i + 2])
			{
				return bd.cell[i + j][i] == '*' ? 1 : 2;
			}
		}
	}

	//副上三角对角线
	for (int j = 0; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i][bd.size - i - 1 - j] != ' ' && bd.cell[i][bd.size - i - 1 - j] == bd.cell[i + 1][bd.size - i - 2 - j] && bd.cell[i + 1][bd.size - i - 2 - j] == bd.cell[i + 2][bd.size - i - 3 - j])
			{
				return bd.cell[i][i + j] == '*' ? 1 : 2;
			}
		}
	}
	//副下三角对角线
	for (int j = 1; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i + j][bd.size - i - 1] != ' ' && bd.cell[i + j][bd.size - i - 1] == bd.cell[i + 1 + j][bd.size - i - 2] && bd.cell[i + 1 + j][bd.size - i - 2] == bd.cell[i + 2 + j][bd.size - i - 3])
			{
				return bd.cell[i][i + j] == '*' ? 1 : 2;
			}
		}
	}

	if (bd.emptyNum == 0)
	{
		return 3; //平局
	}else
	{
		return 0; // 进行中
	}
}

/*------------------------------------------------
/   函数名： getVal
/   作  用： 选择棋盘大小
/   参  数： bd，棋盘型，保存棋盘结果
/			 player，char型，估值玩家
/   返回值： int，估值函数结果
/-------------------------------------------------*/
int getVal(Board& bd, char player)
{
	int val = 0;
	char oppo = player == '@' ? '*' : '@';

	//行
	for (int i = 0; i < bd.size; i++)
	{
		for (int j = 0; j <= bd.size - 3; j++)
		{
			if (bd.cell[i][j] != oppo && bd.cell[i][j + 1] != oppo && bd.cell[i][j + 2] != oppo)
			{
				val++;
			}
			if (bd.cell[i][j] == player && bd.cell[i][j + 1] == player && bd.cell[i][j + 2] == ' ')
			{
				val += 2;
			}
			if (bd.cell[i][j] == player && bd.cell[i][j + 1] == ' ' && bd.cell[i][j + 2] == player)
			{
				val += 2;
			}
			if (bd.cell[i][j] == ' ' && bd.cell[i][j + 1] == player && bd.cell[i][j + 2] == player)
			{
				val += 2;
			}
		}
	}

	//列
	for (int i = 0; i <= bd.size - 3; i++)
	{
		for (int j = 0; j < bd.size; j++)
		{
			if (bd.cell[i][j] != oppo && bd.cell[i + 1][j] != oppo &&bd.cell[i + 2][j] != oppo)
			{
				val++;
			}
			if (bd.cell[i][j] == player && bd.cell[i + 1][j] == player && bd.cell[i + 2][j] == ' ')
			{
				val += 2;
			}
			if (bd.cell[i][j] == player && bd.cell[i + 1][j] == ' ' && bd.cell[i + 2][j] == player)
			{
				val += 2;
			}
			if (bd.cell[i][j] == ' ' && bd.cell[i + 1][j] == player && bd.cell[i + 2][j] == player)
			{
				val += 2;
			}
		}
	}

	//主上三角对角线
	for (int j = 0; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i][i + j] != oppo && bd.cell[i + 1][i + 1 + j] != oppo && bd.cell[i + 2][i + 2 + j] != oppo)
			{
				val++;
			}
			if (bd.cell[i][i + j] == player && bd.cell[i + 1][i + 1 + j] == player && bd.cell[i + 2][i + 2 + j] == ' ')
			{
				val += 2;
			}
			if (bd.cell[i][i + j] == player && bd.cell[i + 1][i + 1 + j] == ' ' && bd.cell[i + 2][i + 2 + j] == player)
			{
				val += 2;
			}
			if (bd.cell[i][i + j] == ' ' && bd.cell[i + 1][i + 1 + j] == player && bd.cell[i + 2][i + 2 + j] == player)
			{
				val += 2;
			}
		}
	}
	//主下三角对角线
	for (int j = 1; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i + j][i] != oppo &&bd.cell[i + 1 + j][i + 1] != oppo && bd.cell[i + 2 + j][i + 2] != oppo)
			{
				val++;
			}
			if (bd.cell[i + j][i] == player && bd.cell[i + 1 + j][i + 1] == player && bd.cell[i + 2 + j][i + 2] == ' ')
			{
				val += 2;
			}
			if (bd.cell[i + j][i] == player && bd.cell[i + 1 + j][i + 1] == ' ' && bd.cell[i + 2 + j][i + 2] == player)
			{
				val += 2;
			}
			if (bd.cell[i + j][i] == ' ' && bd.cell[i + 1 + j][i + 1] == player && bd.cell[i + 2 + j][i + 2] == player)
			{
				val += 2;
			}
		}
	}

	//副上三角对角线
	for (int j = 0; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i][bd.size - i - 1 - j] != oppo && bd.cell[i + 1][bd.size - i - 2 - j] != oppo && bd.cell[i + 2][bd.size - i - 3 - j] != oppo)
			{
				val++;
			}
			if (bd.cell[i][bd.size - i - 1 - j] == player && bd.cell[i + 1][bd.size - i - 2 - j] == player && bd.cell[i + 2][bd.size - i - 3 - j] == ' ')
			{
				val += 2;
			}
			if (bd.cell[i][bd.size - i - 1 - j] == player && bd.cell[i + 1][bd.size - i - 2 - j] == ' ' && bd.cell[i + 2][bd.size - i - 3 - j] == player)
			{
				val += 2;
			}
			if (bd.cell[i][bd.size - i - 1 - j] == ' ' && bd.cell[i + 1][bd.size - i - 2 - j] == player && bd.cell[i + 2][bd.size - i - 3 - j] == player)
			{
				val += 2;
			}
		}
	}
	//副下三角对角线
	for (int j = 1; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i + j][bd.size - i - 1] != oppo && bd.cell[i + 1 + j][bd.size - i - 2] != oppo && bd.cell[i + 2 + j][bd.size - i - 3] != oppo)
			{
				val++;
			}
			if (bd.cell[i + j][bd.size - i - 1] == player && bd.cell[i + 1 + j][bd.size - i - 2] == player && bd.cell[i + 2 + j][bd.size - i - 3] == ' ')
			{
				val -= 2;
			}
			if (bd.cell[i + j][bd.size - i - 1] == player && bd.cell[i + 1 + j][bd.size - i - 2] == ' ' && bd.cell[i + 2 + j][bd.size - i - 3] == player)
			{
				val -= 2;
			}
			if (bd.cell[i + j][bd.size - i - 1] == ' ' && bd.cell[i + 1 + j][bd.size - i - 2] == player && bd.cell[i + 2 + j][bd.size - i - 3] == player)
			{
				val -= 2;
			}
		}
	}

	//行
	for (int i = 0; i < bd.size; i++)
	{
		for (int j = 0; j <= bd.size - 3; j++)
		{
			if (bd.cell[i][j] != player && bd.cell[i][j + 1] != player && bd.cell[i][j + 2] != player)
			{
				val--;
			}
			if (bd.cell[i][j] == oppo && bd.cell[i][j + 1] == oppo && bd.cell[i][j + 2] == ' ')
			{
				val -= 2;
			}
			if (bd.cell[i][j] == oppo && bd.cell[i][j + 1] == ' ' && bd.cell[i][j + 2] == oppo)
			{
				val -= 2;
			}
			if (bd.cell[i][j] == ' ' && bd.cell[i][j + 1] == oppo && bd.cell[i][j + 2] == oppo)
			{
				val -= 2;
			}
		}
	}

	//列
	for (int i = 0; i <= bd.size - 3; i++)
	{
		for (int j = 0; j < bd.size; j++)
		{
			if (bd.cell[i][j] != player && bd.cell[i + 1][j] != player && bd.cell[i + 2][j] != player)
			{
				val--;
			}
			if (bd.cell[i][j] == oppo && bd.cell[i + 1][j] == oppo && bd.cell[i + 2][j] == ' ')
			{
				val -= 2;
			}
			if (bd.cell[i][j] == oppo && bd.cell[i + 1][j] == ' ' && bd.cell[i + 2][j] == oppo)
			{
				val -= 2;
			}
			if (bd.cell[i][j] == ' ' && bd.cell[i + 1][j] == oppo && bd.cell[i + 2][j] == oppo)
			{
				val -= 2;
			}
		}
	}

	//主上三角对角线
	for (int j = 0; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i][i + j] != player && bd.cell[i + 1][i + 1 + j] != player && bd.cell[i + 2][i + 2 + j] != player)
			{
				val--;
			}
			if (bd.cell[i][i + j] == oppo && bd.cell[i + 1][i + 1 + j] == oppo && bd.cell[i + 2][i + 2 + j] == ' ')
			{
				val -= 2;
			}
			if (bd.cell[i][i + j] == oppo && bd.cell[i + 1][i + 1 + j] == ' ' && bd.cell[i + 2][i + 2 + j] == oppo)
			{
				val -= 2;
			}
			if (bd.cell[i][i + j] == ' ' && bd.cell[i + 1][i + 1 + j] == oppo && bd.cell[i + 2][i + 2 + j] == oppo)
			{
				val -= 2;
			}
		}
	}
	//主下三角对角线
	for (int j = 1; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i + j][i] != player && bd.cell[i + 1 + j][i + 1] != player && bd.cell[i + 2 + j][i + 2] != player)
			{
				val--;
			}
			if (bd.cell[i + j][i] == oppo && bd.cell[i + 1 + j][i + 1] == oppo && bd.cell[i + 2 + j][i + 2] == ' ')
			{
				val -= 2;
			}
			if (bd.cell[i + j][i] == oppo && bd.cell[i + 1 + j][i + 1] == ' ' && bd.cell[i + 2 + j][i + 2] == oppo)
			{
				val -= 2;
			}
			if (bd.cell[i + j][i] == ' ' && bd.cell[i + 1 + j][i + 1] == oppo && bd.cell[i + 2 + j][i + 2] == oppo)
			{
				val -= 2;
			}
		}
	}

	//副上三角对角线
	for (int j = 0; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i][bd.size - i - 1 - j] != player && bd.cell[i + 1][bd.size - i - 2 - j] != player && bd.cell[i + 2][bd.size - i - 3 - j] != player)
			{
				val--;
			}
			if (bd.cell[i][bd.size - i - 1 - j] == oppo && bd.cell[i + 1][bd.size - i - 2 - j] == oppo && bd.cell[i + 2][bd.size - i - 3 - j] == ' ')
			{
				val -= 2;
			}
			if (bd.cell[i][bd.size - i - 1 - j] == oppo && bd.cell[i + 1][bd.size - i - 2 - j] == ' ' && bd.cell[i + 2][bd.size - i - 3 - j] == oppo)
			{
				val -= 2;
			}
			if (bd.cell[i][bd.size - i - 1 - j] == ' ' && bd.cell[i + 1][bd.size - i - 2 - j] == oppo && bd.cell[i + 2][bd.size - i - 3 - j] == oppo)
			{
				val -= 2;
			}
		}
	}
	//副下三角对角线
	for (int j = 1; j <= bd.size - 3; j++)
	{
		for (int i = 0; i <= bd.size - 3 - j; i++)
		{
			if (bd.cell[i + j][bd.size - i - 1] != player && bd.cell[i + 1 + j][bd.size - i - 2] != player && bd.cell[i + 2 + j][bd.size - i - 3] != player)
			{
				val--;
			}
			if (bd.cell[i + j][bd.size - i - 1] == oppo && bd.cell[i + 1 + j][bd.size - i - 2] == oppo && bd.cell[i + 2 + j][bd.size - i - 3] == ' ')
			{
				val -= 2;
			}
			if (bd.cell[i + j][bd.size - i - 1] == oppo && bd.cell[i + 1 + j][bd.size - i - 2] == ' ' && bd.cell[i + 2 + j][bd.size - i - 3] == oppo)
			{
				val -= 2;
			}
			if (bd.cell[i + j][bd.size - i - 1] == ' ' && bd.cell[i + 1 + j][bd.size - i - 2] == oppo && bd.cell[i + 2 + j][bd.size - i - 3] == oppo)
			{
				val -= 2;
			}
		}
	}
	return val;
}

/*------------------------------------------------
/   函数名： inputChess
/   作  用： 检测鼠标选择的落棋位置
/   参  数： bd，棋盘型，保存棋盘结果
			 player，字符型，落棋的玩家
/   返回值： 无
/-------------------------------------------------*/
void inputChess(Board& bd, char player)
{
	//行分别编号为ABC，列分别编号为123
	bool isChoose = false;
	string ret = "00";
	while (!isChoose)
	{
		if (MouseHit())
		{
			MOUSEMSG mouse = GetMouseMsg();
			if (mouse.uMsg == WM_LBUTTONDOWN)
			{
				
				if (bd.size == 3)
				{
					// 检查行
					if (mouse.y >= 150 && mouse.y < 350)
					{
						ret[0] = 'A';
					}else if (mouse.y >= 350 && mouse.y < 550)
					{
						ret[0] = 'B';
					}else if (mouse.y >= 550 && mouse.y < 750)
					{
						ret[0] = 'C';
					}
					//检查列
					if (mouse.x >= 100 && mouse.x < 300)
					{
						ret[1] = '1';
					}
					else if (mouse.x >= 300 && mouse.x < 500)
					{
						ret[1] = '2';
					}
					else if (mouse.x >= 500 && mouse.x < 700)
					{
						ret[1] = '3';
					}
				}

				if (bd.size == 4)
				{
					// 检查行
					if (mouse.y >= 150 && mouse.y < 300)
					{
						ret[0] = 'A';
					}
					else if (mouse.y >= 300 && mouse.y < 450)
					{
						ret[0] = 'B';
					}
					else if (mouse.y >= 450 && mouse.y < 600)
					{
						ret[0] = 'C';
					}
					else if (mouse.y >= 600 && mouse.y < 750)
					{
						ret[0] = 'D';
					}
					//检查列
					if (mouse.x >= 100 && mouse.x < 250)
					{
						ret[1] = '1';
					}
					else if (mouse.x >= 250 && mouse.x < 400)
					{
						ret[1] = '2';
					}
					else if (mouse.x >= 400 && mouse.x < 550)
					{
						ret[1] = '3';
					}
					else if (mouse.x >= 550 && mouse.x < 700)
					{
						ret[1] = '4';
					}
				}

				if (bd.size == 5)
				{
					// 检查行
					if (mouse.y >= 150 && mouse.y < 270)
					{
						ret[0] = 'A';
					}
					else if (mouse.y >= 270 && mouse.y < 390)
					{
						ret[0] = 'B';
					}
					else if (mouse.y >= 390 && mouse.y < 510)
					{
						ret[0] = 'C';
					}
					else if (mouse.y >= 510 && mouse.y < 630)
					{
						ret[0] = 'D';
					}
					else if (mouse.y >= 630 && mouse.y < 750)
					{
						ret[0] = 'E';
					}
					//检查列
					if (mouse.x >= 100 && mouse.x < 220)
					{
						ret[1] = '1';
					}
					else if (mouse.x >= 220 && mouse.x < 340)
					{
						ret[1] = '2';
					}
					else if (mouse.x >= 340 && mouse.x < 460)
					{
						ret[1] = '3';
					}
					else if (mouse.x >= 460 && mouse.x < 580)
					{
						ret[1] = '4';
					}
					else if (mouse.x >= 580 && mouse.x < 700)
					{
						ret[1] = '5';
					}
				}
			}
		}
		//判断鼠标点击是否在棋盘上且为该位置无棋子
		if (ret[0] != '0' && ret[1] != '0' && bd.cell[ret[0] - 'A'][ret[1] - '1'] == ' ')
		{
			isChoose = true; 
		}
	}
	bd.cell[ret[0] - 'A'][ret[1] - '1'] = player;
	displayChess(bd, ret, player);
}

/*------------------------------------------------
/   函数名： displayMes
/   作  用： 展示轮到谁下棋
/   参  数： player，字符型，轮到落棋的玩家
/   返回值： 无
/-------------------------------------------------*/
void displayMes(char player)
{
	IMAGE  imageXmin, image0min;
	if (player == '*')
	{
		loadimage(&imageXmin, _T("./图片/Xmini.jpg"), 100, 100);
		putimage(1040, 190, &imageXmin);
	}else
	{
		loadimage(&image0min, _T("./图片/@mini.jpg"), 100, 100);
		putimage(1040, 190, &image0min);
	}
}

/*------------------------------------------------
/   函数名： displayChess
/   作  用： 展示该轮落棋的棋子
/   参  数： bd，棋盘型，保存棋盘结果
/			 loc，字符串型，落棋的位置
/			 player，字符型，落棋的玩家
/   返回值： 无
/-------------------------------------------------*/
void displayChess(Board& bd, string loc, char player)
{
	IMAGE image;
	if (bd.size == 3)
	{
		if (player == '*')
		{
			loadimage(&image, _T("./图片/X.jpg"), 180, 180);
		}
		else if (player == '@')
		{
			loadimage(&image, _T("./图片/@.jpg"), 180, 180);
		}
			 if (loc == "A1") putimage(110, 160, &image);
		else if (loc == "A2") putimage(314, 160, &image);
		else if (loc == "A3") putimage(518, 160, &image);
		else if (loc == "B1") putimage(110, 360, &image);
		else if (loc == "B2") putimage(314, 360, &image);
		else if (loc == "B3") putimage(518, 360, &image);
		else if (loc == "C1") putimage(110, 560, &image);
		else if (loc == "C2") putimage(314, 560, &image);
		else if (loc == "C3") putimage(518, 560, &image);

	}
	if (bd.size == 4)
	{
		if (player == '*')
		{
			loadimage(&image, _T("./图片/X.jpg"), 130, 130);
		}
		else if (player == '@')
		{
			loadimage(&image, _T("./图片/@.jpg"), 130, 130);
		}
			 if (loc == "A1") putimage(110, 160, &image);
		else if (loc == "A2") putimage(260, 160, &image);
		else if (loc == "A3") putimage(410, 160, &image);
		else if (loc == "A4") putimage(560, 160, &image);
		else if (loc == "B1") putimage(110, 310, &image);
		else if (loc == "B2") putimage(260, 310, &image);
		else if (loc == "B3") putimage(410, 310, &image);
		else if (loc == "B4") putimage(560, 310, &image);
		else if (loc == "C1") putimage(110, 460, &image);
		else if (loc == "C2") putimage(260, 460, &image);
		else if (loc == "C3") putimage(410, 460, &image);
		else if (loc == "C4") putimage(560, 460, &image);
		else if (loc == "D1") putimage(110, 610, &image);
		else if (loc == "D2") putimage(260, 610, &image);
		else if (loc == "D3") putimage(410, 610, &image);
		else if (loc == "D4") putimage(560, 610, &image);
	}
	if (bd.size == 5)
	{
		if (player == '*')
		{
			loadimage(&image, _T("./图片/X.jpg"), 100, 100);
		}
		else if (player == '@')
		{
			loadimage(&image, _T("./图片/@.jpg"), 100, 100);
		}
			 if (loc == "A1") putimage(110, 160, &image);
		else if (loc == "A2") putimage(230, 160, &image);
		else if (loc == "A3") putimage(350, 160, &image);
		else if (loc == "A4") putimage(470, 160, &image);
		else if (loc == "A5") putimage(590, 160, &image);
		else if (loc == "B1") putimage(110, 280, &image);
		else if (loc == "B2") putimage(230, 280, &image);
		else if (loc == "B3") putimage(350, 280, &image);
		else if (loc == "B4") putimage(470, 280, &image);
		else if (loc == "B5") putimage(590, 280, &image);
		else if (loc == "C1") putimage(110, 400, &image);
		else if (loc == "C2") putimage(230, 400, &image);
		else if (loc == "C3") putimage(350, 400, &image);
		else if (loc == "C4") putimage(470, 400, &image);
		else if (loc == "C5") putimage(590, 400, &image);
		else if (loc == "D1") putimage(110, 520, &image);
		else if (loc == "D2") putimage(230, 520, &image);
		else if (loc == "D3") putimage(350, 520, &image);
		else if (loc == "D4") putimage(470, 520, &image);
		else if (loc == "D5") putimage(590, 520, &image);
		else if (loc == "E1") putimage(110, 640, &image);
		else if (loc == "E2") putimage(230, 640, &image);
		else if (loc == "E3") putimage(350, 640, &image);
		else if (loc == "E4") putimage(470, 640, &image);
		else if (loc == "E5") putimage(590, 640, &image);
	}
}

/*------------------------------------------------
/   函数名： displayRet
/   作  用： 展示该轮游戏结果
/   参  数： ret，字符串型，游戏结果
/   返回值： 无
/-------------------------------------------------*/
void displayRet(int ret)
{
	IMAGE imageXwin, image0win, imageDraw;
	switch (ret)
	{
		case 1:
			loadimage(&imageXwin, _T("./图片/Xwin.jpg"), 390, 500);
			putimage(780, 100, &imageXwin);
			break;
		case 2:
			loadimage(&image0win, _T("./图片/@win.jpg"), 390, 500);
			putimage(780, 100, &image0win);
			break;
		case 3:
			loadimage(&imageDraw, _T("./图片/draw.jpg"), 390, 500);
			putimage(780, 100, &imageDraw);
			break;
	}
	Sleep(3000); 
}

/*------------------------------------------------
/   函数名： displayScorePVC
/   作  用： 展示PVC模式该难度下的得分结果
/   参  数： cntRet，字符型数组，得分结果
/   返回值： 无
/-------------------------------------------------*/
void displayScorePVC(int cntRet[3])
{
	TCHAR s1[5], s2[5], s3[5];
	
	setbkcolor(RGB(255, 127, 38)); 
	settextstyle(80, 40, _T("Times New Roman")); 
	settextcolor(WHITE); 
	swprintf_s(s1, _T("%d"), cntRet[0]);
	swprintf_s(s2, _T("%d"), cntRet[1]);
	swprintf_s(s3, _T("%d"), cntRet[2]);
	outtextxy(340, 310, s1);
	outtextxy(550, 310, s2);
	outtextxy(760, 310, s3);
}

/*------------------------------------------------
/   函数名： displayScorePVP
/   作  用： 展示PVP模式该难度下的得分结果
/   参  数： cntRet，int数组，得分结果
/   返回值： 无
/-------------------------------------------------*/
void displayScorePVP(int cntRet[3])
{
	TCHAR s1[5], s2[5], s3[5], s4[5], s5[5], s6[5];

	setbkcolor(RGB(255, 127, 38));
	settextstyle(80, 40, _T("Times New Roman"));
	settextcolor(WHITE);
	swprintf_s(s4, _T("%d"), cntRet[0]);
	swprintf_s(s5, _T("%d"), cntRet[1]);
	swprintf_s(s6, _T("%d"), cntRet[2]);
	swprintf_s(s1, _T("%d"), cntRet[1]);
	swprintf_s(s2, _T("%d"), cntRet[0]);
	swprintf_s(s3, _T("%d"), cntRet[2]);
	outtextxy(470, 190, s1);
	outtextxy(665, 190, s2);
	outtextxy(885, 190, s3);
	outtextxy(470, 495, s4);
	outtextxy(665, 495, s5);
	outtextxy(885, 495, s6);
}

/*------------------------------------------------
/   函数名： ModePVC
/   作  用： 进入PVC模式，选择PVC模式下的难度
/   参  数： 无
/   返回值： 无
/-------------------------------------------------*/
void ModePVC(void)
{
	int diff = 0, order = 0;
	bool againPVC = 1;
	Board bd;

	chooseSize(bd);
	initBoard(bd, bd.size);
	chooseDiff(diff);
	chooseOrder(order);


	while (againPVC)
	{
		switch (diff)
		{
			case 1:
				ModeDiff(bd, order, againPVC, inputModeEasy);
				break;
			case 3:
				ModeDiff(bd, order, againPVC, inputModeHard);
				break;
		}

	}

	destroyBoard(bd);
}

/*------------------------------------------------
/   函数名： ModePVP
/   作  用： 进入PVP模式，双方玩家对弈
/   参  数： 无
/   返回值： 无
/-------------------------------------------------*/
void ModePVP(void)
{
	bool againPVP = true;
	char player = '@';	//@玩家优先
	int ret = 0;
	int cntRet[3] = { 0 };
	Board bd;

	chooseSize(bd);
	initBoard(bd, bd.size);


	while (againPVP)
	{
		if (bd.size == 3)
		{
			loadimage(0, _T("./图片/Board_3-3.jpg"), 1200, 800);
		}
		else if (bd.size == 4)
		{
			loadimage(0, _T("./图片/Board_4-4.jpg"), 1200, 800);
		}
		else if (bd.size == 5)
		{
			loadimage(0, _T("./图片/Board_5-5.jpg"), 1200, 800);
		}
		while (!ret)
		{
			displayMes(player);
			if (player == '*')	//玩家1
			{
				inputChess(bd, player);
			}
			else if (player == '@')	//玩家2
			{
				inputChess(bd, player);
			}
			player = player == '*' ? '@' : '*';	//调换出棋顺序
			bd.emptyNum--;
			ret = getRet(bd);
		}
		if (ret == 1)
		{
			cntRet[0]++;
		}
		else if (ret == 2)
		{
			cntRet[1]++;
		}
		else if (ret == 3)
		{
			cntRet[2]++;
		}
		displayRet(ret);
		chooseAgainPVP(againPVP, cntRet);
		/*清空棋盘*/
		bd.emptyNum = bd.size * bd.size;
		ret = 0;
		for (int i = 0; i < bd.size; i++)
		{
			for (int j = 0; j < bd.size; j++)
			{
				bd.cell[i][j] = ' ';
			}
		}
	}
	destroyBoard(bd);
}

/*------------------------------------------------
/   函数名： ModeDiff
/   作  用： PVC模式，玩家与电脑对弈
/   参  数： bd，棋盘型，保存棋盘结果
			 order，短整型，玩家与电脑出棋的顺序
			 inputModeDiff，函数指针，不同难度下电脑的出棋结果
/   返回值： 无
/-------------------------------------------------*/
void ModeDiff(Board& bd, int& order, bool &againPVC, void (* inputModeDiff)(Board& bd))
{
	bool againDiff = 1;
	//short cntStep = 0;
	char player = '\0';
	short ret = 0;
	int cntRet[3] = { 0 };

	if (order == 1)
	{
		player = '*';
	}else if (order == 2)
	{
		player = '@';
	}
	while (againDiff)
	{
		if (bd.size == 3)
		{
			loadimage(0, _T("./图片/Board_3-3.jpg"), 1200, 800);
		}
		else if (bd.size == 4)
		{
			loadimage(0, _T("./图片/Board_4-4.jpg"), 1200, 800);
		}
		else if (bd.size == 5)
		{
			loadimage(0, _T("./图片/Board_5-5.jpg"), 1200, 800);
		}

		while (ret == 0)
		{
			displayMes(player);
			if (player == '*')	//玩家
			{
				inputChess(bd, player);
			}else if (player == '@')	//计算机
			{
				(*inputModeDiff)(bd);
			}
			bd.emptyNum--;
			player = player == '*' ? '@' : '*';	//调换出棋顺序
			//cntStep++;
			ret = getRet(bd);
		}
		if (ret == 1)
		{
			cntRet[0]++;
		}else if (ret == 2)
		{
			cntRet[1]++;
		}else if (ret == 3)
		{
			cntRet[2]++;
		}
		displayRet(ret);
		chooseAgainPVC(againDiff, againPVC, cntRet);
		bd.emptyNum = bd.size * bd.size;
		//cntStep = 0;
		ret = 0;
		for (int i = 0; i < bd.size; i++)
		{
			for (int j = 0; j < bd.size; j++)
			{
				bd.cell[i][j] = ' ';
			}
		}
	}

}

/*------------------------------------------------
/   函数名： inputModeEasy
/   作  用： 简单模式，得到电脑的出棋结果
/   参  数： bd，棋盘型，保存棋盘结果
/   返回值： 无
/-------------------------------------------------*/
void inputModeEasy(Board& bd)
{
	char n = '1';

	Sleep(1000);
	//空格编号
	for (int i = 0; i < bd.size; i++)
	{
		for (int j = 0; j < bd.size; j++)
		{
			if ((bd.cell[i][j] != '*') && (bd.cell[i][j] != '@'))
			{
				bd.cell[i][j] = n++; 
			}

		}
	}
	srand((unsigned)time(NULL));
	int ran = rand() % (n - '1') + '1'; 
	for (int i = 0; i < bd.size; i++)
	{
		for (int j = 0; j < bd.size; j++)
		{
			if (bd.cell[i][j] == ran)
			{
				bd.cell[i][j] = '@';
				char row = 'A' + i;
				char col = '1' + j;
				string ret = {row, col};
				displayChess(bd, ret, '@');
			}
		}
	}
	//编号复原
	for (int i = 0; i < bd.size; i++)
	{
		for (int j = 0; j < bd.size; j++)
		{
			if ((bd.cell[i][j] != '*') && (bd.cell[i][j] != '@'))
			{
				bd.cell[i][j] = ' '; 
			}

		}
	}
}

/*------------------------------------------------
/   函数名： inputModeHard
/   作  用： 困难模式，得到电脑的出棋结果
/   参  数： bd，棋盘型，保存棋盘结果
/   返回值： 无
/-------------------------------------------------*/
void inputModeHard(Board& bd)
{
	//Sleep(1000);
	Tree T = new Node;
	T->alpha = NINF;
	T->beta = PINF;
	T->level = MAX;
	T->row = -1;
	T->col = -1;
	T->firstChild = NULL;
	T->nextSibling = NULL;

	if (bd.size == 3 && bd.emptyNum == bd.size * bd.size)
	{
		T->row = 2;
		T->col = 0;
	}
	else if (bd.size == 4 && bd.emptyNum == bd.size * bd.size)
	{
		T->row = 2;
		T->col = 2;
	}
	else if (bd.size == 5 && bd.emptyNum == bd.size * bd.size)
	{
		T->row = 4;
		T->col = 4;
	}
	else
	{
		MinMax(bd, T, '@', 0);
	}

	if (T->row != -1 && T->col != -1)
	{
		bd.cell[T->row][T->col] = '@';
		char row = 'A' + T->row;
		char col = '1' + T->col;
		string ret = { row, col };
		displayChess(bd, ret, '@');
	}
	else
	{
		//inputModeEasy(bd);
	}
}

/*------------------------------------------------
/   函数名： MinMax
/   作  用： 实现极大极小搜索算法
/   参  数： bd，棋盘型，保存棋盘结果
			 T，结点指针，指向子树的根结点
			 player，字符型，上一层对应的玩家
			 step，整型，迭代步长
/   返回值： 无
/-------------------------------------------------*/
void MinMax(Board& bd, Node* T, char player, int step)
{
	bool isFirst = true;
	char oppo = player == '@' ? '*' : '@';
	Tree q = NULL;
	int lim = 1;
	if (bd.size == 3)	lim = 7;
	if (bd.size == 4)	lim = 2;
	if (bd.size == 5)	lim = 1;

	if (step <= lim && getRet(bd) == 0)
	{
		for (int i = 0; i < bd.size; i++)
		{
			for (int j = 0; j < bd.size; j++)
			{
				if (bd.cell[i][j] == ' ')
				{
					bd.cell[i][j] = oppo;
					bd.emptyNum--;

					Node* t = new Node;
					t->row = i;
					t->col = j;
					t->val = 0;
					t->alpha = T->alpha;
					t->beta = T->beta;
					t->level = !T->level;
					t->firstChild = NULL;
					t->nextSibling = NULL;
					
					for (int k = 0; k < bd.size; k++)
					{
						for (int l = 0; l < bd.size; l++)
						{
							cout << bd.cell[k][l] << "\t";
						}
						cout << endl;
					}
					cout << endl;
					
					if (isFirst)
					{
						T->firstChild = t;
						isFirst = false;
					}
					else
					{
						q->nextSibling = t;
					}
					q = t;

					cout << "Tlevel:" << T->level << " Tval: " << T->val << "  " << T->alpha << "  " << T->beta << endl;
					if (T->alpha < T->beta)
					{
						MinMax(bd, q, oppo, step + 1);
					}

					Node* p = T->firstChild;
					while (p)
					{
						//cout << T->level << " : " << p->val << endl;
						if (T->level == MIN)
						{
							if (p->val < T->beta)
							{
								T->beta = p->val;
								T->val = p->val;
								T->row = p->row;
								T->col = p->col;
							}
						}
						else if (T->level == MAX)
						{
							if (p->val > T->alpha)
							{
								T->alpha = p->val;
								T->val = p->val;
								T->row = p->row;
								T->col = p->col;
							}
						}
						p = p->nextSibling;
					}
					if (T->firstChild && T->firstChild->nextSibling == NULL)
					{
						T->val = T->firstChild->val;
						T->row = T->firstChild->row;
						T->col = T->firstChild->col;
					}
					
					//cout << T->level << " T: " << T->val << endl;

					bd.cell[i][j] = ' ';
					bd.emptyNum++;
				}
			}
		}
	}
	else
	{
		T->val = getVal(bd, player);
		//if (T->level)
		//	cout <<"MAX " << T->val << endl;
		//if (!T->level)
		//	cout << "MIN " << T->val << endl;
	}

}
/***********FUNCTION*END********************/

/********************************FILE*END***********************************/