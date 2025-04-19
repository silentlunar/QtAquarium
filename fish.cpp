#include "fish.h"

#include "fish.h"

Fish::Fish(const QString& imagePath, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem() {
    QPixmap pix(imagePath);
    pix = pix.scaled(50, 30, Qt::KeepAspectRatio);
    setPixmap(pix);

    speed = QRandomGenerator::global()->bounded(1, static_cast<int>(maxSpeed));
    direction = QRandomGenerator::global()->bounded(360) * M_PI / 180;
    setTransformOriginPoint(boundingRect().center());
}

void Fish::advance(int phase) {
    if (!phase) return;
    if (QRandomGenerator::global()->bounded(100) < 20) {
        qreal delta = QRandomGenerator::global()->generateDouble() *
                    2 * rotationSpeed - rotationSpeed;
        direction += delta;
        setRotation(qRadiansToDegrees(direction));
    }

    speed += QRandomGenerator::global()->generateDouble() * 0.4 - 0.2;
    speed = qBound(0.5, speed, maxSpeed);

    qreal dx = speed * qCos(direction);
    qreal dy = speed * qSin(direction);
    setPos(pos().x() + dx, pos().y() + dy);

    keepInBounds();
}
void Fish::keepInBounds() {
    if (!scene()) return;

    QRectF sceneRect = scene()->sceneRect();
    qreal padding = 30;
    bool changed = false;
    QPointF newPos = pos();

    if (x() < sceneRect.left() + padding) {
        direction = M_PI - direction;
        newPos.setX(sceneRect.left() + padding);
        changed = true;
    }
    else if (x() > sceneRect.right() - padding - boundingRect().width()) {
        direction = M_PI - direction;
        newPos.setX(sceneRect.right() - padding - boundingRect().width());
        changed = true;
    }

    if (y() < sceneRect.top() + padding) {
        direction = -direction;
        newPos.setY(sceneRect.top() + padding);
        changed = true;
    }
    else if (y() > sceneRect.bottom() - padding - boundingRect().height()) {
        direction = -direction;
        newPos.setY(sceneRect.bottom() - padding - boundingRect().height());
        changed = true;
    }

    if (changed) {
        setRotation(qRadiansToDegrees(direction));
        setPos(newPos);
        speed *= 0.5;
    }
}

FishFirst::FishFirst(QObject *parent)
    : Fish(":/fish1.png", parent) {
    maxSpeed = 3;
    rotationSpeed = 0.3;
}

FishSecond::FishSecond(QObject *parent)
    : Fish(":/fish4.png", parent) {
    maxSpeed = 4;
    rotationSpeed = 0.4;
}

FishThird::FishThird(QObject *parent)
    : Fish(":/fish3.png", parent) {
    maxSpeed = 5;
    rotationSpeed = 0.5;
}
