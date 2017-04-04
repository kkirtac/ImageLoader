#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QtWidgets/QMainWindow>
#include "ui_imageloader.h"
#include <QtGui/QResizeEvent>
#include <QtGui/QShowEvent>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtGui/QWheelEvent>

class CMainView : public QGraphicsView 
{
public:
	CMainView() : QGraphicsView() {}
	CMainView(QWidget *parent = 0) : QGraphicsView(parent) {}
	CMainView(QGraphicsScene* scene, QWidget *parent = 0) : QGraphicsView(scene, parent) {}
	~CMainView() {}

protected:

	virtual void wheelEvent(QWheelEvent *event){

		setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

		double scaleFactor = 1.15;

		if (event->delta() > 0)
		{
			scale(scaleFactor, scaleFactor);
		} 
		else
		{
			scale(1.0/scaleFactor, 1.0 / scaleFactor);
		}

	}

};

class myGraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	myGraphicsScene(QObject * parent = 0) : QGraphicsScene(parent){
		leftEyeX =-1;
		leftEyeY =-1;
		rightEyeX =-1;
		rightEyeY =-1;
	}
	myGraphicsScene(const QRectF & sceneRect, QObject * parent = 0) : 
		QGraphicsScene(sceneRect, parent = 0){
			leftEyeX =-1;
			leftEyeY =-1;
			rightEyeX =-1;
			rightEyeY =-1;
	}
	myGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0) : 
		QGraphicsScene(x, y, width, height, parent){
			leftEyeX =-1;
			leftEyeY =-1;
			rightEyeX =-1;
			rightEyeY =-1;
	}

	int LeftEyeX()
	{
		return leftEyeX;
	}

	int LeftEyeY()
	{
		return leftEyeY;
	}

	int RightEyeX()
	{
		return rightEyeX;
	}

	int RightEyeY()
	{
		return rightEyeY;
	}

signals: 
	void sceneMousePressed();

protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event)
	{

		QGraphicsScene::mousePressEvent(event);

		if (event->button() == Qt::MouseButton::LeftButton)
		{
			leftEyeX = event->pos().x();
			leftEyeY = event->pos().y();
		}
		else if (event->button() == Qt::MouseButton::RightButton)
		{
			rightEyeX = event->pos().x();
			rightEyeY = event->pos().y();
		}
		else{}

		emit sceneMousePressed();
	}

	//virtual void wheelEvent(QGraphicsSceneWheelEvent *event){

	//	QGraphicsScene::wheelEvent(event);
	//}

private:
	int leftEyeX;
	int leftEyeY;
	int rightEyeX;
	int rightEyeY;
};


class ImageLoader : public QMainWindow
{
	Q_OBJECT

public:
	ImageLoader(QWidget *parent = 0);
	~ImageLoader();

public slots:
	void sceneMousePressedHandler();

private:
	Ui::ImageLoaderClass ui;
	myGraphicsScene* scene;
	QImage *image;

};




#endif // IMAGELOADER_H
