#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QTimer>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void addFishFirst();
    void addFishSecond();
    void addFishThird();
    void selectPlant();
    void selectRock();
    void selectShell();
    void selectCoral();

private:
    void setupButtons();
    void addDecoration(const QString& imagePath, const QPointF& pos);

    QGraphicsScene *scene;
    QGraphicsView *view;
    QTimer *timer;
    QString selectedDecoration;
};

#endif
