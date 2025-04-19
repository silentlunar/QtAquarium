#include "mainwindow.h"
#include "fish.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene)),
      timer(new QTimer(this))
{
    setFixedSize(1024, 600);
    scene->setSceneRect(0, 0, 1022, 573);

    QPixmap bgPix(":/aquarium.jpg");

    QGraphicsPixmapItem *background = scene->addPixmap(bgPix);
    background->setPos(0, 0);

    view->setRenderHint(QPainter::Antialiasing);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1022, 573);

    setupButtons();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer->start(30);
}

void MainWindow::setupButtons() {
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *controlLayout = new QVBoxLayout();

    QGroupBox *fishGroup = new QGroupBox("Рыбы");
    QVBoxLayout *fishLayout = new QVBoxLayout();

    QPushButton *btnGoldFish = new QPushButton("Золотая рыбка");
    QPushButton *btnClownFish = new QPushButton("Рыба-клоун");
    QPushButton *btnBlueTang = new QPushButton("Голубой хирург");

    connect(btnGoldFish, &QPushButton::clicked, this, &MainWindow::addFishFirst);
    connect(btnClownFish, &QPushButton::clicked, this, &MainWindow::addFishSecond);
    connect(btnBlueTang, &QPushButton::clicked, this, &MainWindow::addFishThird);

    fishLayout->addWidget(btnGoldFish);
    fishLayout->addWidget(btnClownFish);
    fishLayout->addWidget(btnBlueTang);
    fishGroup->setLayout(fishLayout);

    QGroupBox *decorGroup = new QGroupBox("Украшения");
    QVBoxLayout *decorLayout = new QVBoxLayout();

    QPushButton *btnPlant = new QPushButton("Растение");
    QPushButton *btnRock = new QPushButton("Камень");
    QPushButton *btnShell = new QPushButton("Ракушка");
    QPushButton *btnCoral = new QPushButton("Коралл");

    connect(btnPlant, &QPushButton::clicked, this, &MainWindow::selectPlant);
    connect(btnRock, &QPushButton::clicked, this, &MainWindow::selectRock);
    connect(btnShell, &QPushButton::clicked, this, &MainWindow::selectShell);
    connect(btnCoral, &QPushButton::clicked, this, &MainWindow::selectCoral);

    decorLayout->addWidget(btnPlant);
    decorLayout->addWidget(btnRock);
    decorLayout->addWidget(btnShell);
    decorLayout->addWidget(btnCoral);
    decorGroup->setLayout(decorLayout);

    controlLayout->addWidget(fishGroup);
    controlLayout->addWidget(decorGroup);
    controlLayout->addStretch();

    mainLayout->addLayout(controlLayout);
    mainLayout->addWidget(view);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && !selectedDecoration.isEmpty()) {
        QPointF scenePos = view->mapToScene(event->pos());
        addDecoration(selectedDecoration, scenePos);
    }
}

void MainWindow::addDecoration(const QString& imagePath, const QPointF& pos) {
    QPixmap pix(imagePath);
    pix = pix.scaled(80, 80, Qt::KeepAspectRatio);

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pix);
    item->setPos(pos);
    scene->addItem(item);
}

void MainWindow::addFishFirst() {
    FishFirst *fish = new FishFirst();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}

void MainWindow::addFishSecond() {
    FishSecond *fish = new FishSecond();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}
void MainWindow::addFishThird() {
    FishThird *fish = new FishThird();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}

// Слоты для выбора декораций
void MainWindow::selectPlant() { selectedDecoration = ":/plant1.png"; }
void MainWindow::selectRock() { selectedDecoration = ":/rock1.png"; }
void MainWindow::selectShell() { selectedDecoration = ":/shell.png"; }
void MainWindow::selectCoral() { selectedDecoration = ":/coral.png"; }
