#include "QtGuiApplication.h"

#include <QtDebug>
#include <QKeyEvent>
#include <QGridLayout>
#include <QMessageBox>

using namespace std;

QtGuiApplication::QtGuiApplication(QWidget *parent)
	: QMainWindow(parent)
	, buttons(vector<vector<QPushButton*>>(TotalSize, vector<QPushButton*>(TotalSize, nullptr)))
	, cal_(TotalSize)
{
	ui.setupUi(this);

	QGridLayout *gridLayout = new QGridLayout();
	for (int i = 0; i < TotalSize; i++) {
		for (int j = 0; j < TotalSize; j++) {
			QPushButton *button = new QPushButton();
			button->setEnabled(false);
			// 占满整个cell空间
			button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			QFont font = button->font();
			font.setPointSize(20);
			button->setFont(font);
			gridLayout->addWidget(button, i, j);
			buttons[i][j] = button;
		}
	}
	ui.centralWidget->setLayout(gridLayout);

	cal_.init(TotalSize);

	// fix: change to 信号槽
	cal_.Display(buttons);
}

void QtGuiApplication::keyPressEvent(QKeyEvent *event)
{
	bool ret = false;
	switch (event->key())
	{
	case Qt::Key_Left:
		ret = cal_.Operation(Direction::kLeft);
		break;
	case Qt::Key_Right:
		ret = cal_.Operation(Direction::kRight);
		break;
	case Qt::Key_Up:
		ret = cal_.Operation(Direction::kUp);
		break;
	case Qt::Key_Down:
		ret = cal_.Operation(Direction::kDown);
		break;
	default:
		return QMainWindow::keyPressEvent(event);
		break;
	}

	cal_.Display(buttons);
	if (!ret) {
		QMessageBox::warning(this, "", QStringLiteral("Game over!"));
	}
}
