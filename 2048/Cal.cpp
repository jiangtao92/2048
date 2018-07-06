#include "Cal.h"

#include <random>
#include <cassert>
#include <QtDebug>
#include <map>

using namespace std;

// style

#define Style_Sheet_Default -1

// todo: ʵ��һ���������ɫ�����㷨
static std::map<int, QString> Global_style_sheet =
{
	{-1, "QPushButton{ background: #FC3843; color: #F9F6F2; font: bold large \"Times New Roman\"; font-size: 50px}}" }, // default
	{0, "QPushButton{ background: #CDC0B5 }"}, // �հ�
	{2, "QPushButton{ background: #EEE4DA; color: #776E65; font: bold large \"Times New Roman\"; font-size: 50px}" },
	{4, "QPushButton{ background: #EDE0C8; color: #776E65; font: bold large \"Times New Roman\"; font-size: 50px}}" },
	{8, "QPushButton{ background: #F2B179; color: #F9F6F2; font: bold large \"Times New Roman\"; font-size: 50px}}" },
	{16,"QPushButton{ background: #F59563; color: #F9F6F2; font: bold large \"Times New Roman\"; font-size: 50px}}" },
	{32,"QPushButton{ background: #F67C5F; color: #F9F6F2; font: bold large \"Times New Roman\"; font-size: 50px}}" },
	{64,"QPushButton{ background: #F15C42; color: #F9F6F2; font: bold large \"Times New Roman\"; font-size: 50px}}" },
	{128,"QPushButton{ background: #EBCE78; color: #F9F6F2; font: bold large \"Times New Roman\"; font-size: 50px}}" },
	{256,"QPushButton{ background: #ECCA69; color: #F9F6F2; font: bold large \"Times New Roman\"; font-size: 50px}}" },
	{512,"QPushButton{ background: #EBC65A; color: #F9F6F2; font: bold large \"Times New Roman\"; font-size: 50px}}" },
	{1024,"QPushButton{ background: #ECC34D; color: #F9F6F2; font: bold large \"Times New Roman\"; font-size: 50px}}" },
	{2048,"QPushButton{ background: #ECC03F; color: #F9F6F2; font: bold large \"Times New Roman\"; font-size: 50px}}" },
	{4096,"QPushButton{ background: #FC3843; color: #F9F6F2; font: bold large \"Times New Roman\"; font-size: 50px}}" },
};


Cal::Cal(int size)
	: size_(size)
	, items_(size_, vector<int>(size_, 0))
{
}

void Cal::init(int size)
{
	size_ = size;

	items_ = vector<vector<int>>(size_, vector<int>(size_, 0));

	insertRandom(size_ * size_);
}

bool Cal::Operation(Direction direction)
{
	int noEmpty = 0;
	bool bMoved = false;
	// �ƶ�
	if (Direction::kLeft == direction) {
		for (int i = 0; i < size_; i++) {
			int count = 0;
			//bool flag = true;
			for (int j = count; j < size_; j++) {
				if (items_[i][j] != 0) {
					if (count != j) {
						items_[i][count] = items_[i][j];
						items_[i][j] = 0;
						bMoved = true;
					}
					// fix ���ڶ�����Ժϲ���ʱ��,����е㲻һ��, ÿ��ֻ���Ժϲ�һ��
					if (count > 0 && items_[i][count] == items_[i][count - 1]) {
						items_[i][count - 1] *= 2;
						items_[i][count] = 0;
						bMoved = true;
					}
					else {
						count++;
					}
				}
			}
			//qDebug() << count;
			noEmpty += count;
			//qDebug() << "noEmpty: " << noEmpty;
		}
	}
	else if (Direction::kUp == direction) {
		for (int i = 0; i < size_; i++) {
			int count = 0;
			for (int j = count; j < size_; j++) {
				if (items_[j][i] != 0) {
					if (count != j) {
						items_[count][i] = items_[j][i];
						items_[j][i] = 0;
						bMoved = true;
					}
					if (count > 0 && items_[count][i] == items_[count - 1][i]) {
						items_[count - 1][i] *= 2;
						items_[count][i] = 0;
						bMoved = true;
					}
					else {
						count++;
					}
				}
			}
			noEmpty += count;
		}
	}
	else if (Direction::kRight == direction) {
		for (int i = 0; i < size_; i++) {
			int count = size_ - 1;
			for (int j = count; j >=0 ; j--) {
				if (items_[i][j] != 0) {
					if (count != j) {
						items_[i][count] = items_[i][j];
						items_[i][j] = 0;
						bMoved = true;
					}
					if (count < size_ - 1 && items_[i][count] == items_[i][count + 1]) {
						items_[i][count + 1] *= 2;
						items_[i][count] = 0;
						bMoved = true;
					}
					else {
						count--;
					}
				}
			}
			noEmpty += size_ - count - 1;
		}
	}
	else if (Direction::kDown == direction) {
		for (int i = 0; i < size_; i++) {
			int count = size_ - 1;
			for (int j = count; j >= 0; j--) {
				if (items_[j][i] != 0) {
					if (count != j) {
						items_[count][i] = items_[j][i];
						items_[j][i] = 0;
						bMoved = true;
					}
					if (count < size_ - 1 && items_[count][i] == items_[count + 1][i]) {
						items_[count + 1][i] *= 2;
						items_[count][i] = 0;
						bMoved = true;
					}
					else {
						count--;
					}
				}
			}
			noEmpty += size_ - count - 1;
		}
	}

	// �������һ��2
	int empty = size_ * size_ - noEmpty;

	//qDebug() << "empty: " << empty;
	/* �Ѿ�ȫ�������� */
	if (empty <= 0 && !checkGameOver()) {
		return false;
	}
	/* �ϲ����ƶ�֮��,��Ҫ����һ�����ֵ */
	if (bMoved) {
		insertRandom(empty);
	}

	if (empty > 1)
		return true;

	return checkGameOver();
}

void Cal::Display(std::vector<std::vector<QPushButton *>> buttons)
{
	for (int i = 0; i < size_; i++)
	{
		for (int j = 0; j < size_; j++)
		{
			buttons[i][j]->setText(items_[i][j] ? QString::number(items_[i][j]): "");

			auto pos = Global_style_sheet.find(items_[i][j]);
			if (pos != std::end(Global_style_sheet)) {
				buttons[i][j]->setStyleSheet(pos->second);
			}
			else {
				buttons[i][j]->setStyleSheet(Global_style_sheet[Style_Sheet_Default]);
			}
		}
	}
}

void Cal::insertRandom(int szEmpty)
{
	assert(szEmpty > 0);
	int index = std::rand() % (szEmpty)+1;
	int count = 0;
	for (int i = 0; i < size_; i++)
	{
		for (int j = 0; j < size_; j++)
		{
			if (items_[i][j] == 0 && ++count == index)
			{
				items_[i][j] = 2;
			}
		}
	}
}

bool Cal::checkGameOver()
{
	for (int i = 0; i < size_; i++)
	{
		for (int j = 0; j < size_; j++)
		{
			if (j > 0 && items_[i][j - 1] == items_[i][j])
				return true;
			if (i > 0 && items_[i - 1][j] == items_[i][j])
				return true;
			if (j < size_ - 1 && items_[i][j + 1] == items_[i][j])
				return true;
			if (i < size_ - 1 && items_[i + 1][j] == items_[i][j])
				return true;
		}
	}
	return false;
}