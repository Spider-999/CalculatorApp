#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QtMath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;

private slots:
	// These functions will be called whenever
	// the user clicks a button and triggers
	// the released signal.
	void digitPressed();
	void decimalPressed();
	void changeSignPressed();
	void percentSignPressed();
	void clearSignPressed();
	void clearEntrySignPressed();
	void equalSignPressed();
	void binaryOperationPressed();
	void deleteSignPressed();
	void squareRootPressed();
	void powerSignPressed();
	void inverseSignPressed();
};
#endif // CALCULATOR_H
