/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum: 04.01.2018
 *
 * Author: Manuel
 * Version: 0.3
 * Datum: 12.01.2018
 * Kommentar: Buttons hinzugefuegt
 *
 * Author: Lucas, Manuel
 * Version: 0.4
 * Datum: 13.01.2018
 *
 * Author: Lucas
 * Version: 0.5
 * Datum: 14.01.2018
 * Kommentar: Label für den zustand des spiels eingefügt: player & playerUnitNumber
 * */
#include "gamewidget.h"
#include "ui_gamewidget.h"

void GameWidget::setInfoScene(HexagonDisplayInfo *info)
{
    for(auto &it : gameWidInfoScene->items())
    {
        gameWidInfoScene->removeItem(it);
    }
    gameWidInfoScene->addItem(info);
    gameWidInfoScene->update();
    gameWidGameScene->update();
}

void GameWidget::setPlayerLabel(QString text)
{
    ui->labelPlayerCurrent->setText(text);
}

void GameWidget::setPhaseLabel(QString text)
{
    ui->labelPhaseCurrent->setText(text);
}

void GameWidget::setPlayerOneUnitsLabel(int value)
{
    ui->labelPlayerOneUnitsCurrent->setText(QString::number(value));
}

void GameWidget::setPlayerTwoUnitsLabel(int value)
{
    ui->labelPlayerTwoUnitsCurrent->setText(QString::number(value));
}

void GameWidget::clearScenes()
{
    //leere gameWidInfoScene
    for(auto &it : gameWidInfoScene->items())
    {
        gameWidInfoScene->removeItem(it);
    }
    gameWidInfoScene->update();

    //leere gameWidOptionsScene
    for(auto &it : gameWidOptionsScene->items())
    {
        gameWidOptionsScene->removeItem(it);
    }
}


QGraphicsScene *GameWidget::getGameWidInfoScene() const
{
    return gameWidInfoScene;
}

int GameWidget::getSizeX() const
{
    return sizeX;
}

int GameWidget::getSizeY() const
{
    return sizeY;
}

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget),
    gameWidGameScene(new QGraphicsScene(this)), gameWidInfoScene(new QGraphicsScene(this)),
    gameWidOptionsScene(new QGraphicsScene(this)), gameWidButtonScene(new QGraphicsScene(this)),
    sizeX(15), sizeY(15)
{
    ui->setupUi(this);
    ui->graphicsView_buttonView->setScene(gameWidButtonScene);
    ui->graphicsView_gameView->setScene(gameWidGameScene);
    ui->graphicsView_informationsView->setScene(gameWidInfoScene);
    ui->graphicsView_optionsView->setScene(gameWidOptionsScene);
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::gameWidCreateMatchfield(std::vector<std::vector<HexagonMatchfield*>> &hexagonGrid)
{


    for(unsigned int i = 0; i < hexagonGrid.size(); i++)
    {
        for(unsigned int j = 0; j < hexagonGrid[i].size(); j++)
        {
            HexagonMatchfield* hex = hexagonGrid[i][j];

            //Groesse der Bilder
            int PicSizeX = hex->pixmap().size().width();
            int PicSizeY = hex->pixmap().size().height();

            int PicCoordX, PicCoordY; //Koordinaten der Bilder
            if(i & 1)
            {
                PicCoordX = i * 2 * PicSizeX / 3;
                PicCoordY = j * PicSizeY + (PicSizeY / 2);
            }
            else
            {
                PicCoordX = i * 2 * PicSizeX / 3;
                PicCoordY = j * PicSizeY;
            }

            if(hex->getUnit_stationed() != nullptr)
            {
                gameWidGameScene->addItem(hex->getUnit_stationed());
                hex->getUnit_stationed()->setPos(PicCoordX,PicCoordY);
            }

            hex->setPos(PicCoordX, PicCoordY);
            gameWidGameScene->addItem(hex);
        }
    }
    ui->graphicsView_gameView->setScene( gameWidGameScene );
}

void GameWidget::gameWidcreateButtonBar(std::vector<Button*> buttonVector)
{
    int spacingX = 70;

    for(unsigned int i = 0; i < buttonVector.size(); i++)
    {
        buttonVector[i]->setPos(i*spacingX,0);
        gameWidButtonScene->addItem(buttonVector[i]);
    }
    gameWidButtonScene->update();
}

HexagonDisplayInfo::HexagonDisplayInfo(HexagonMatchfield *ptr_hexMfield)
:QObject(0), QGraphicsRectItem(QRectF(-50,-50,230,100), 0), hexToDisplay(ptr_hexMfield)
{
    updateText();
}

void HexagonDisplayInfo::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    updateText();
    painter->drawPixmap(-50 ,-50, hexToDisplay->pixmap());
    painter->drawText(QRectF(20,-50,1000,200),qStringHexDispHexType);

    if(hexToDisplay->getUnit_stationed() != nullptr)
    {
        painter->drawPixmap(-50,-50, hexToDisplay->getUnit_stationed()->pixmap());
        painter->drawText(QRectF(20,-30,200,20),qStringUnitDispUnitName);
        painter->drawText(QRectF(20,-10, 200,20),qStringUnitDispUnitType);
        painter->drawText(QRectF(20,10,200,20),qStringUnitDispUnitLife);

        if(qStringUnitDispMovement != "NONE")
        {
            painter->drawText(QRectF(20,30,200,20),qStringUnitDispMovement);
        }
        if(qStringUnitDispUnitAttack != "NONE")
        {
            painter->drawText(QRectF(20,50,200,20),qStringUnitDispUnitAttack);
        }
    }
}

void HexagonDisplayInfo::updateText()
{
    qStringHexDispHexType = "Hex Typ: " + hexToDisplay->getHexMatchfieldType();

    if(hexToDisplay->getUnit_stationed() != nullptr)
    {
        qStringUnitDispUnitName = "Name: " + hexToDisplay->getUnit_stationed()->getUnitName();
        qStringUnitDispUnitType = "Unit Typ: " + hexToDisplay->getUnit_stationed()->getUnitType();
        qStringUnitDispUnitLife = "HP: " + QString::number(hexToDisplay->getUnit_stationed()->getUnitCurrentHP()) + "/"
                                            + QString::number(hexToDisplay->getUnit_stationed()->getUnitHP());
        if(hexToDisplay->getUnit_stationed()->getUnitMoveRange() > 0)
        {
            qStringUnitDispMovement = "MoveRange: " + QString::number(hexToDisplay->getUnit_stationed()->getUnitMoveRange()) + "/"
                    + QString::number(hexToDisplay->getUnit_stationed()->getUnitCurrentMoveRange());
        }else{
            qStringUnitDispMovement = "NONE";
        }
        if(hexToDisplay->getUnit_stationed()->getUnitAirAtt() == 0
                && hexToDisplay->getUnit_stationed()->getUnitGroundAtt() == 0
                && hexToDisplay->getUnit_stationed()->getUnitWaterAtt() == 0)
        {
            qStringUnitDispUnitAttack = "NONE";
        }else{
            qStringUnitDispUnitAttack = "Attack: A" + QString::number(hexToDisplay->getUnit_stationed()->getUnitAirAtt()) + "/"
                    + "G" + QString::number(hexToDisplay->getUnit_stationed()->getUnitGroundAtt()) + "/"
                    + "W" + QString::number(hexToDisplay->getUnit_stationed()->getUnitWaterAtt());
        }

    }else{
        qStringUnitDispUnitName = "";
        qStringUnitDispUnitType = "";
        qStringUnitDispUnitLife = "";
        qStringUnitDispMovement = "";
        qStringUnitDispUnitAttack = "";
    }
}
