#ifndef CALCWIDGET_H
#define CALCWIDGET_H
// Where we control screen painting, but we aren't doing screen painting... oops

#include <QGLWidget>
#include <QTimerEvent>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>

class calcwidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit calcwidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

signals:

public slots:

};

#endif // CALCWIDGET_H
