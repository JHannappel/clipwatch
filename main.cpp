#include <QApplication>
#include "clipWatch.h"


int main(int argc, char** argv) {
	QApplication app(argc, argv);
	app.setApplicationName("clipwatch");
	clipWatch foo;
	foo.show();
	return app.exec();
}
