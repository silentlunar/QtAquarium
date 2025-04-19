#include "mainwindow.h"
#include "fish.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMouseEvent>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene)),
      timer(new QTimer(this))
{
    setFixedSize(1250, 600);
    scene->setSceneRect(0, 0, 1250, 600);

    QPixmap bgPix(":/aquarium.jpg");
    QGraphicsPixmapItem *background = scene->addPixmap(bgPix);
    background->setPos(0, 0);

    view->setRenderHint(QPainter::Antialiasing);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1250, 600);

    setupButtons();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer->start(30);
}

void MainWindow::setupButtons()
{
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *controlLayout = new QVBoxLayout();

    // Группа кнопок для рыб
    QGroupBox *fishGroup = new QGroupBox("Рыбы");
    QVBoxLayout *fishLayout = new QVBoxLayout();

    QStringList fishButtons = {
        "Золотая рыбка", "Рыба-клоун", "Голубой хирург",
        "Карп кои", "Синий неон", "Рыба-ангел", "Гуппи", "Рыба-бабочка",
        "Медуза"
    };

    for (int i = 0; i < fishButtons.size(); ++i) {
        QPushButton *btn = new QPushButton(fishButtons[i]);
        fishLayout->addWidget(btn);

        switch (i) {
            case 0: connect(btn, &QPushButton::clicked, this, &MainWindow::addGoldfish); break;
            case 1: connect(btn, &QPushButton::clicked, this, &MainWindow::addClownfish); break;
            case 2: connect(btn, &QPushButton::clicked, this, &MainWindow::addBlueTang); break;
            case 3: connect(btn, &QPushButton::clicked, this, &MainWindow::addFishKoi); break;
            case 4: connect(btn, &QPushButton::clicked, this, &MainWindow::addFishBlueNeon); break;
            case 5: connect(btn, &QPushButton::clicked, this, &MainWindow::addFishAngelfish); break;
            case 6: connect(btn, &QPushButton::clicked, this, &MainWindow::addFishGuppy); break;
            case 7: connect(btn, &QPushButton::clicked, this, &MainWindow::addFishButterfly); break;
            case 8: connect(btn, &QPushButton::clicked, this, &MainWindow::addFishJellyfish); break;
        }
    }
    fishGroup->setLayout(fishLayout);

    // Группа кнопок для декораций
    QGroupBox *decorGroup = new QGroupBox("Украшения");
    QVBoxLayout *decorLayout = new QVBoxLayout();

    // Растения (5 видов)
    QGroupBox *plantGroup = new QGroupBox("Растения");
    QHBoxLayout *plantLayout = new QHBoxLayout();
    for (int i = 1; i <= 2; ++i) {
        QPushButton *btn = new QPushButton(QString("%1").arg(i));
        btn->setFixedSize(40, 30);
        connect(btn, &QPushButton::clicked, [this, i]() {
            selectedDecoration = QString(":/plant%1.png").arg(i);
        });
        plantLayout->addWidget(btn);
    }
    plantGroup->setLayout(plantLayout);

    // Ракушки (3 вида)
    QGroupBox *shellGroup = new QGroupBox("Ракушки");
    QHBoxLayout *shellLayout = new QHBoxLayout();
    for (int i = 1; i <= 3; ++i) {
        QPushButton *btn = new QPushButton(QString("%1").arg(i));
        btn->setFixedSize(40, 30);
        connect(btn, &QPushButton::clicked, [this, i]() {
            selectedDecoration = QString(":/shell%1.png").arg(i);
        });
        shellLayout->addWidget(btn);
    }
    shellGroup->setLayout(shellLayout);

    // Камни (2 вида)
    QGroupBox *rockGroup = new QGroupBox("Камни");
    QHBoxLayout *rockLayout = new QHBoxLayout();
    for (int i = 1; i <= 2; ++i) {
        QPushButton *btn = new QPushButton(QString("%1").arg(i));
        btn->setFixedSize(40, 30);
        connect(btn, &QPushButton::clicked, [this, i]() {
            selectedDecoration = QString(":/rock%1.png").arg(i);
        });
        rockLayout->addWidget(btn);
    }
    rockGroup->setLayout(rockLayout);

    // Специальные украшения
    QGroupBox *specialGroup = new QGroupBox("Особые");
    QHBoxLayout *specialLayout = new QHBoxLayout();

    QPushButton *btnCastle = new QPushButton("Замок");
    QPushButton *btnStarfish = new QPushButton("Морская звезда");
    QPushButton *btnCoral = new QPushButton("Коралл");

    connect(btnCastle, &QPushButton::clicked, [this]() {
        selectedDecoration = ":/castle.png";
    });
    connect(btnStarfish, &QPushButton::clicked, [this]() {
        selectedDecoration = ":/starfish.png";
    });
    connect(btnCoral, &QPushButton::clicked, [this]() {
        selectedDecoration = ":/coral1.png";
    });

    specialLayout->addWidget(btnCastle);
    specialLayout->addWidget(btnStarfish);
    specialLayout->addWidget(btnCoral);
    specialGroup->setLayout(specialLayout);

    // Компоновка всех элементов декора
    decorLayout->addWidget(plantGroup);
    decorLayout->addWidget(shellGroup);
    decorLayout->addWidget(rockGroup);
    decorLayout->addWidget(specialGroup);
    decorGroup->setLayout(decorLayout);

    // Основная компоновка
    controlLayout->addWidget(fishGroup);
    controlLayout->addWidget(decorGroup);
    controlLayout->addStretch();

    mainLayout->addLayout(controlLayout);
    mainLayout->addWidget(view);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !selectedDecoration.isEmpty()) {
        QPointF scenePos = view->mapToScene(event->pos());
        addDecoration(selectedDecoration, scenePos);
    }
}

void MainWindow::addDecoration(const QString& imagePath, const QPointF& pos)
{
    QPixmap pix(imagePath);
    pix = pix.scaled(80, 80, Qt::KeepAspectRatio);

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pix);
    item->setPos(pos);
    scene->addItem(item);
}

void MainWindow::addGoldfish()
{
    Goldfish *fish = new Goldfish();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}

void MainWindow::addClownfish()
{
    Clownfish *fish = new Clownfish();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}

void MainWindow::addBlueTang()
{
    BlueTang *fish = new BlueTang();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}

void MainWindow::addFishKoi()
{
    FishKoi *fish = new FishKoi();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}

void MainWindow::addFishBlueNeon()
{
    FishBlueNeon *fish = new FishBlueNeon();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}

void MainWindow::addFishAngelfish()
{
    FishAngelfish *fish = new FishAngelfish();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}

void MainWindow::addFishGuppy()
{
    FishGuppy *fish = new FishGuppy();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}

void MainWindow::addFishButterfly()
{
    FishButterfly *fish = new FishButterfly();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}

void MainWindow::addFishJellyfish()
{
    FishJellyfish *fish = new FishJellyfish();
    fish->setPos(QRandomGenerator::global()->bounded(scene->width()),
                QRandomGenerator::global()->bounded(scene->height()));
    scene->addItem(fish);
}

