#include "imageloader.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImageLoader w;
	w.show();
	return a.exec();
}
