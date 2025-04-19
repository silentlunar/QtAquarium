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

class FishFirst : public Fish {
public:
    explicit FishFirst(QObject *parent = nullptr);
};

class FishSecond : public Fish {
public:
    explicit FishSecond(QObject *parent = nullptr);
};

class FishThird : public Fish {
public:
    explicit FishThird(QObject *parent = nullptr);
};

#endif // FISH_H
