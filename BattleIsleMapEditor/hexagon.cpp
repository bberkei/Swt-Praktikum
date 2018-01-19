#include "hexagon.h"

Hexagon::Hexagon(QPoint qpoint, QString type, Unit *stationedUnit) :
    qpoint_gridPosition(qpoint), unit_stationed(stationedUnit),
    HexMatchfieldType(type),int_boltaniumCurrent(), qcolor_HexColor(Qt::black)
{
    if(HexMatchfieldType == "waterDeep")
        setPixmap(QPixmap(":/img/HexagonBilder/Meer.png"));
    else if(HexMatchfieldType == "waterSeashore")
        setPixmap(QPixmap(":/img/HexagonBilder/Kueste.png"));
    else if(HexMatchfieldType == "forrest")
        setPixmap(QPixmap(":/img/HexagonBilder/Forest.png"));
    else if(HexMatchfieldType == "grassland")
        setPixmap(QPixmap(":/img/HexagonBilder/Grass.png"));
    else if(HexMatchfieldType == "streetStraight")
        setPixmap(QPixmap(":/img/HexagonBilder/nordsued.png"));
    else if(HexMatchfieldType == "streetCurve")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_nordwest.png"));
    else if(HexMatchfieldType == "streetCrossing")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_kreuzung.png"));
    else if(HexMatchfieldType == "mountainTop")
        setPixmap(QPixmap(":/img/HexagonBilder/Mountain.png"));
    else if(HexMatchfieldType == "mountainSideStraight")
        setPixmap(QPixmap(":/img/HexagonBilder/BergSeiteGrade.png"));
    else if(HexMatchfieldType == "mountainSideCurve")
        setPixmap(QPixmap(":/img/HexagonBilder/BergSeiteSchräg.png"));
    else
    {
        setPixmap(QPixmap(":/img/HexagonBilder/Grass.png"));
        //"Warnung: Ein HexagonMatchfield ist vom Typ default (siehe switch(HexMatchfieldType) im Konstruktor)";
    }
    //Skalierung kann hier angepasst werden
    setPixmap(pixmap().scaled(64,64));

    if(int_boltaniumCurrent > 0)
    {
        qpixmap_boltanium.load(":/img/Boltanium/Boltanium_high.png");
        qpixmap_boltanium = qpixmap_boltanium.scaled(64,64);
    }
}

Unit *Hexagon::getUnit_stationed() const
{
    return unit_stationed;
}

void Hexagon::setUnit_stationed(Unit *value)
{
    unit_stationed = value;
}

QString Hexagon::getHexMatchfieldType()
{
    return HexMatchfieldType;
}

QColor Hexagon::getHexColor()
{
    return qcolor_HexColor;
}

void Hexagon::setHexColor(QColor c)
{
    qcolor_HexColor = c;
}

void Hexagon::setHexMatchfieldType(QString type)
{
    HexMatchfieldType = type;

    if(HexMatchfieldType == "waterDeep")
        setPixmap(QPixmap(":/img/HexagonBilder/Meer.png"));
    else if(HexMatchfieldType == "waterSeashore")
        setPixmap(QPixmap(":/img/HexagonBilder/Kueste.png"));
    else if(HexMatchfieldType == "forrest")
        setPixmap(QPixmap(":/img/HexagonBilder/Forest.png"));
    else if(HexMatchfieldType == "grassland")
        setPixmap(QPixmap(":/img/HexagonBilder/Grass.png"));
    else if(HexMatchfieldType == "streetStraight")
        setPixmap(QPixmap(":/img/HexagonBilder/nordsued.png"));
    else if(HexMatchfieldType == "streetCurve")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_nordwest.png"));
    else if(HexMatchfieldType == "streetCrossing")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_kreuzung.png"));
    else if(HexMatchfieldType == "mountainTop")
        setPixmap(QPixmap(":/img/HexagonBilder/Mountain.png"));
    else if(HexMatchfieldType == "mountainSideStraight")
        setPixmap(QPixmap(":/img/HexagonBilder/BergSeiteGrade.png"));
    else if(HexMatchfieldType == "mountainSideCurve")
        setPixmap(QPixmap(":/img/HexagonBilder/BergSeiteSchräg.png"));
    else
    {
        setPixmap(QPixmap(":/img/HexagonBilder/Grass.png"));
        //"Warnung: Ein HexagonMatchfield ist vom Typ default (siehe switch(HexMatchfieldType) im Konstruktor)";
    }
    //Skalierung kann hier angepasst werden
    setPixmap(pixmap().scaled(64,64));

    if(int_boltaniumCurrent > 0)
    {
        qpixmap_boltanium.load(":/img/Boltanium/Boltanium_high.png");
        qpixmap_boltanium = qpixmap_boltanium.scaled(64,64);
    }
}


void Hexagon::mousePressEvent( QGraphicsSceneMouseEvent * event)
{
    emit SIGNAL_clicked(this);
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);
        QPen pen;
        pen.setColor(qcolor_HexColor);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->drawPath(shape());
        if(int_boltaniumCurrent > 0)
        {
            painter->drawPixmap(0,0,qpixmap_boltanium);
        }
}

int Hexagon::getBoltaniumCurrent() const{
    return int_boltaniumCurrent;
}

void Hexagon::setBoltaniumCurrent(int value){
    int_boltaniumCurrent = value;
}

QPoint Hexagon::getQpoint_gridPosition() const
{
    return qpoint_gridPosition;
}
