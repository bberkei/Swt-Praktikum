#ifndef BUTTON_H
#define BUTTON_H
#include "hexagonbase.h"
#include <QDebug>
class Button : public HexagonBase
{
    Q_OBJECT
public:
    Button(QPoint qpoint_center, int int_size, QPoint qpoint_position);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


/*New Class*/
class ButtonMove : public Button
{
    Q_OBJECT
public:
    ButtonMove(QPoint qpoint_center, int int_size, QPoint qpoint_position);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void printType();
signals:
    void clicked(ButtonMove*);
};


/*New Class*/
class ButtonAction : public Button
{
    Q_OBJECT
public:
    ButtonAction(QPoint qpoint_center, int int_size, QPoint qpoint_position);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void printType();
signals:
    void clicked(ButtonAction*);

};


/*New Class*/
class ButtonMap : public Button
{
    Q_OBJECT
public:
    ButtonMap(QPoint qpoint_center, int int_size, QPoint qpoint_position);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void printType();
signals:
    void clicked(ButtonMap*);

};


/*New Class*/
class ButtonInformation : public Button
{
    Q_OBJECT
public:
    ButtonInformation(QPoint qpoint_center, int int_size, QPoint qpoint_position);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void printType();
signals:
    void clicked(ButtonInformation*);

};


/*New Class*/
class ButtonChangePhase : public Button
{
    Q_OBJECT
public:
    ButtonChangePhase(QPoint qpoint_center, int int_size, QPoint qpoint_position);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void printType();
signals:
    void clicked(ButtonChangePhase*);

};


/*New Class*/
class ButtonMenue : public Button
{
    Q_OBJECT
public:
    ButtonMenue(QPoint qpoint_center, int int_size, QPoint qpoint_position);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void printType();
signals:
    void clicked(ButtonMenue*);

};
#endif // BUTTON_H