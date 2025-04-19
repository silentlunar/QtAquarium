#ifndef FISH_H
#define FISH_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QtMath>
#include <QGraphicsScene>

class Fish : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Fish(const QString& imagePath, QObject *parent = nullptr);
    virtual void advance(int phase) override;

protected:
    qreal speed;
    qreal direction;
    qreal maxSpeed = 5;
    qreal rotationSpeed = 0.5;

    void keepInBounds();
};

class Goldfish : public Fish {
public:
    explicit Goldfish(QObject *parent = nullptr);
};

class Clownfish : public Fish {
public:
    explicit Clownfish(QObject *parent = nullptr);
};

class BlueTang : public Fish {
public:
    explicit BlueTang(QObject *parent = nullptr);
};

class FishKoi : public Fish {
public:
    explicit FishKoi(QObject *parent = nullptr);
};

class FishBlueNeon : public Fish {
public:
    explicit FishBlueNeon(QObject *parent = nullptr);
};

class FishAngelfish : public Fish {
public:
    explicit FishAngelfish(QObject *parent = nullptr);
};

class FishGuppy : public Fish {
public:
    explicit FishGuppy(QObject *parent = nullptr);
};

class FishButterfly : public Fish {
public:
    explicit FishButterfly(QObject *parent = nullptr);
};

class FishJellyfish : public Fish {
public:
    explicit FishJellyfish(QObject *parent = nullptr);
};

#endif // FISH_H
