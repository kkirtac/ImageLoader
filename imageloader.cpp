#include "imageloader.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QGuiApplication>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QRect>
#include <QtWidgets/QGridLayout>


ImageLoader::ImageLoader(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	const QString fileName("C:/Users/Public/Pictures/Sample Pictures/Koala.jpg");

	image = new QImage(fileName);
	scene = new myGraphicsScene(this);

	connect(scene, SIGNAL(sceneMousePressed()), this, SLOT(sceneMousePressedHandler()));

	if (image->isNull()) {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
			tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
		setWindowFilePath(QString());

		scene->addPixmap(QPixmap());
		 
		return;
	}

	scene->addPixmap(QPixmap::fromImage(*image));
	scene->setSceneRect(0, 0, image->width(), image->height());
	setWindowFilePath(fileName);


	CMainView* graphicsView_Image;
	graphicsView_Image = new CMainView(scene, ui.frame);
	graphicsView_Image->setObjectName(QStringLiteral("graphicsView_Image"));
	ui.gridLayout->addWidget(graphicsView_Image, 0, 0, 1, 1);

	graphicsView_Image->show();
}

ImageLoader::~ImageLoader()
{

}

void ImageLoader::sceneMousePressedHandler()
{
	ui.label_LeftEyeXY->setText(QString("(%1,%2)").arg(scene->LeftEyeX()).arg(scene->LeftEyeY()));
	ui.label_RightEyeXY->setText(QString("(%1,%2)").arg(scene->RightEyeX()).arg(scene->RightEyeY()));
}

