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
    void addGoldfish();
    void addClownfish();
    void addBlueTang();
    void addFishKoi();
    void addFishBlueNeon();
    void addFishAngelfish();
    void addFishGuppy();
    void addFishButterfly();
    void addFishJellyfish();

private:
    void setupButtons();
    void addDecoration(const QString& imagePath, const QPointF& pos);

    QGraphicsScene *scene;
    QGraphicsView *view;
    QTimer *timer;
    QString selectedDecoration;
};

#endif
