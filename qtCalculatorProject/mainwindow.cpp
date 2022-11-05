#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_mainwindow.h"

// Global variables.
double firstNumber;
bool userTyping = false;

// Constructor | inheriting from QMainWindow and ui.
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	// Make the display only readable so the user
	// can't type numbers in the QLineEdit display.
	ui->numberDisplay->setReadOnly(true);

	// Connect all of the digit buttons in order
	// to be able to interact with the calculator.
	// Whenever the user clicks a digit and then
	// releases it, the released signal will be sent
	// to the our custom digitPressed function.
	connect(ui->zeroButton   , SIGNAL(released() ), this, SLOT(digitPressed() ) );
	connect(ui->oneButton    , SIGNAL(released() ), this, SLOT(digitPressed() ) );
	connect(ui->twoButton    , SIGNAL(released() ), this, SLOT(digitPressed() ) );
	connect(ui->threeButton , SIGNAL(released() ), this, SLOT(digitPressed() ) );
	connect(ui->fourButton   , SIGNAL(released() ), this, SLOT(digitPressed() ) );
	connect(ui->fiveButton    , SIGNAL(released() ), this, SLOT(digitPressed() ) );
	connect(ui->sixButton     , SIGNAL(released() ), this, SLOT(digitPressed() ) );
	connect(ui->sevenButton, SIGNAL(released() ), this, SLOT(digitPressed() ) );
	connect(ui->eightButton  , SIGNAL(released() ), this, SLOT(digitPressed() ) );
	connect(ui->nineButton   , SIGNAL(released() ), this, SLOT(digitPressed() ) );

	// Connect the decimal button.
	// Whenever the user clicks the decimal button
	// and then releases it, the released signal will
	// be sent to our custom decimalPressed function.
	connect(ui->decimalButton, SIGNAL(released() ), this, SLOT(decimalPressed() ) );

	// Connect the change sign button.
	// Whenever the user clicks the change sign
	// button and then releases it, the released signal
	// will be sent to our custom changeSignPressed function.
	connect(ui->changeSignButton, SIGNAL(released() ), this, SLOT(changeSignPressed() ) );

	// Connect the percent sign button.
	// Whenever the user clicks the percent sign
	// button and then releases it, the released signal
	// will be sent to our custom percentSignPressed function.
	connect(ui->percentButton, SIGNAL(released() ), this, SLOT(percentSignPressed() ) );

	// Connect the clearButton, whenever
	// the user clicks this button, the calculator
	// will clear the number from memory
	// and then it will reset all the binaryOperation buttons.
	connect(ui->clearButton, SIGNAL(released() ), this, SLOT(clearSignPressed() ) );

	// Connect the clearEntryButton, whenever
	// the user clicks this button, the calculator
	// will clear the secondNumber entered.
	connect(ui->clearEntryButton, SIGNAL(released() ), this, SLOT(clearEntrySignPressed() ) );

	// Connect the equal button and the binaryOperation buttons.
	connect(ui->equalButton, SIGNAL(released() ), this, SLOT(equalSignPressed() ) );

	connect(ui->addButton         , SIGNAL(released() ), this, SLOT(binaryOperationPressed() ) );
	connect(ui->substractButton, SIGNAL(released() ), this, SLOT(binaryOperationPressed() ) );
	connect(ui->multiplyButton  , SIGNAL(released() ), this, SLOT(binaryOperationPressed() ) );
	connect(ui->divideButton     , SIGNAL(released() ), this, SLOT(binaryOperationPressed() ) );

	// We use this property to check if these buttons have been pressed.
	ui->addButton->setCheckable(true);
	ui->substractButton->setCheckable(true);
	ui->multiplyButton->setCheckable(true);
	ui->divideButton->setCheckable(true);

	// Connect the delete button, whenever
	// the user clicks this button, one digit
	// is removed from the displayed number.
	connect(ui->deleteButton, SIGNAL(released() ), this, SLOT(deleteSignPressed() ) );

	// Connect the square root button, whenever
	// the user clicks this button, the square root
	// operation is performed on the given number.
	connect(ui->squareRootButton, SIGNAL(released() ), this, SLOT(squareRootPressed() ) );

	// Connect the power button, whenever the user
	// clicks this button, the power operation is
	// performed on the given number.
	connect(ui->powerButton, SIGNAL(released() ), this, SLOT(powerSignPressed() ) );

	// Connect the inverse button, whenever the user
	// clicks this button, the given number will be
	// raised to the power -1, meaning it will
	// divide 1 to the given number.
	connect(ui->inverseButton, SIGNAL(released() ), this, SLOT(inverseSignPressed() ) );
}

// Deconstructor.
MainWindow::~MainWindow()
{
	delete ui;
}

// Button functions.
void MainWindow::digitPressed()
{
	// This determines which digit was pressed and puts it
	// into a QPushButton variable.
	QPushButton *digit = qobject_cast<QPushButton *>(sender() );
	double digitValue;
	QString newValue;

	if((ui->addButton->isChecked() || ui->substractButton->isChecked() ||
	   ui->multiplyButton->isChecked() || ui->divideButton->isChecked() ) && userTyping == false)
	{
		// Keep only the new digit.
		digitValue = digit->text().toDouble();
		userTyping = true;

		// Create a QString to store the new integer
		// in order to be able to update the numberDisplay.
		// We also give the newValue a limit of 15 digits.
		newValue = QString::number(digitValue, 'g', 15);
	}
	else
	{
		if(ui->numberDisplay->text().contains('.') && digit->text() == "0")
		{
			newValue = ui->numberDisplay->text() + digit->text();
		}
		else
		{
			// Append the new digit to the old numberDisplay.
			digitValue = (ui->numberDisplay->text() + digit->text() ).toDouble();
			newValue = QString::number(digitValue, 'g', 15);
		}
	}

	// If the digitValue entered is 0 and numberDisplay is 0 do nothing.
	if(ui->numberDisplay->text() == "0" && digit->text().toInt() == 0.0)
	{
		return ;
	}
	else
	{
		// If the length of the displayed text is less than 12
		// then we keep the same font, otherwise we scale
		// down the font in order to be able to fit it across
		// the numberDisplay's length.
		if(ui->numberDisplay->text().length() < 12)
		{
			ui->numberDisplay->setText(newValue);
		}
		else
		{
			ui->numberDisplay->setStyleSheet("font-size: 35px");
			ui->numberDisplay->setText(newValue);
		}
	}
}

void MainWindow::decimalPressed()
{
	// If the decimal has already been
	// pressed, don't show another decimal
	// point to the screen.
	if(!ui->numberDisplay->text().contains('.') )
	{
		ui->numberDisplay->setText(ui->numberDisplay->text() + ".");
	}
}

void MainWindow::changeSignPressed()
{
	double numberValue;
	QString newValue;

	// Convert the current numberDisplay value to
	// double then change its sign by multiplying it to -1.
	numberValue = ui->numberDisplay->text().toDouble();
	numberValue *= -1;

	// Store the new numberValue in a newValue variable
	// then display the new value on the calculator screen.
	newValue = QString::number(numberValue, 'g', 15);
	ui->numberDisplay->setText(newValue);
}

void MainWindow::percentSignPressed()
{
	double numberValue;
	QString newValue;

	// Convert the numberDisplay value to
	// double then divide it by 100 to known its percentage.
	numberValue = ui->numberDisplay->text().toDouble();
	numberValue /= 100;

	newValue = QString::number(numberValue, 'g', 15);
	ui->numberDisplay->setText(newValue);
}

void MainWindow::clearSignPressed()
{
	// Clears the calculator's memory.
	if(ui->numberDisplay->text() != "0")
	{
		ui->addButton->setChecked(false);
		ui->substractButton->setChecked(false);
		ui->multiplyButton->setChecked(false);
		ui->divideButton->setChecked(false);
		ui->numberDisplay->setText("0");
	}
}

void MainWindow::clearEntrySignPressed()
{
	if(ui->numberDisplay->text() != "0")
	{
		ui->numberDisplay->setText("0");
	}
}

void MainWindow::deleteSignPressed()
{
	QString newDisplay;

	newDisplay = ui->numberDisplay->text();
	// This line removes one character from the end of the numberDisplay.
	newDisplay.chop(1);

	if(newDisplay.isEmpty() )
	{
		newDisplay = "0";
	}

	ui->numberDisplay->setText(newDisplay);
}

void MainWindow::squareRootPressed()
{
	double newValue;
	newValue = ui->numberDisplay->text().toDouble();
	newValue = qSqrt(newValue);

	QString newDisplay;
	newDisplay = QString::number(newValue, 'g', 15);

	ui->numberDisplay->setStyleSheet("font-size: 35px");
	ui->numberDisplay->setText(newDisplay);
}

void MainWindow::powerSignPressed()
{
	double newValue;
	newValue = ui->numberDisplay->text().toDouble();
	newValue = qPow(newValue, 2);

	QString newDisplay;
	newDisplay = QString::number(newValue, 'g', 15);

	ui->numberDisplay->setStyleSheet("font-size: 35px");
	ui->numberDisplay->setText(newDisplay);
}

void MainWindow::inverseSignPressed()
{
	double newValue;
	newValue = ui->numberDisplay->text().toDouble();
	newValue = 1 / newValue;

	QString newDisplay;
	newDisplay = QString::number(newValue, 'g', 15);

	ui->numberDisplay->setStyleSheet("font-size: 35px");
	ui->numberDisplay->setText(newDisplay);
}

void MainWindow::equalSignPressed()
{
	double newNumber;
	double secondNumber;
	QString newDisplay;

	secondNumber = ui->numberDisplay->text().toDouble();

	// If any of the binary operation buttons are pressed
	// perform the given operations.
	if(ui->addButton->isChecked() )
	{
		newNumber = firstNumber + secondNumber;
		newDisplay = QString::number(newNumber, 'g', 15);
		ui->numberDisplay->setText(newDisplay);
		ui->addButton->setChecked(false);
	}
	else if(ui->substractButton->isChecked() )
	{
		newNumber = firstNumber - secondNumber;
		newDisplay = QString::number(newNumber, 'g', 15);
		ui->numberDisplay->setText(newDisplay);
		ui->substractButton->setChecked(false);
	}
	else if(ui->divideButton->isChecked() )
	{
		if(secondNumber == 0)
		{
			return ;
		}
		else
		{
			newNumber = firstNumber / secondNumber;
			newDisplay = QString::number(newNumber, 'g', 10);
			ui->numberDisplay->setText(newDisplay);
			ui->divideButton->setChecked(false);
		}
	}
	else if(ui->multiplyButton->isChecked() )
	{
		newNumber = firstNumber * secondNumber;
		newDisplay = QString::number(newNumber, 'g', 15);
		ui->numberDisplay->setText(newDisplay);
		ui->multiplyButton->setChecked(false);
	}

	userTyping = false;
}

void MainWindow::binaryOperationPressed()
{
	QPushButton *button = qobject_cast<QPushButton *>(sender() );

	firstNumber = ui->numberDisplay->text().toDouble();
	button->setChecked(true);
}
