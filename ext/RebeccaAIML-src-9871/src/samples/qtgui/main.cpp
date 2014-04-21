
//QT includes
#include <QApplication>
#include <QTimer>

//qtgui includes
#include <MainWindow.h>
#include <Arguments.h>
using namespace qtgui;

/*
 * Initialize our static variable that
 * holds our singleton instance for Arguments.h.
 */
Arguments *Arguments::m_instance = 0;


int main(int argc, char *argv[])
{
	Arguments::setArguments(argc, argv);

	/*
	 * Standard QApplication object
	 */
	QApplication app(argc, argv);


	/*
	 * Instantiate our main window 
	 * object, resize it to what
	 * we would like it to be, and
	 * finally show it.
	 */
	MainWindow mainWindow;
	mainWindow.resize(845, 654);
	mainWindow.show();
	return app.exec();
} 

