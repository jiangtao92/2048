#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication.h"
#include "QPushButton"

#include "Cal.h"


class QtGuiApplication : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication(QWidget *parent = Q_NULLPTR);

protected:

	void keyPressEvent(QKeyEvent *event) override;

private:
	const static int TotalSize = 4;
private:
	Ui::QtGuiApplicationClass ui;
	std::vector<std::vector<QPushButton*>> buttons;
	Cal cal_;
};
