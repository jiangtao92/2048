#pragma once

#ifndef __CAl_H_
#define __CAl_H_

#include <vector>
#include <QPushButton>

enum class Direction {
	kLeft,
	kUp,
	kRight,
	kDown
};

class Cal {
public:
	Cal(int size = 4);

	void init(int size);

	// return false ±Ì æ”Œœ∑ ß∞‹
	bool Operation(Direction direction);

	// debug
	void Display(std::vector<std::vector<QPushButton*>> buttons);

private:
	void insertRandom(int szEmpty);

	bool checkGameOver();

private:
	int size_;
	std::vector<std::vector<int>> items_;
};

#endif
