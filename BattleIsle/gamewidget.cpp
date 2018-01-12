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
    gameWidGame(nullptr),
    gameWidGameScene(new QGraphicsScene(this)), gameWidInfoScene(new QGraphicsScene(this)),
    gameWidOptionsScene(new QGraphicsScene(this)), gameWidButtonScene(new QGraphicsScene(this)),
    sizeX(50), sizeY(20)
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

void GameWidget::gameWidCreateMatchfield()
{


    for(unsigned int i = 0; i < gameWidGame->getVectorVectorHexagonMatchfield().size(); i++)
    {
        for(unsigned int j = 0; j < (gameWidGame->getVectorVectorHexagonMatchfield()[i]).size(); j++)
        {
            HexagonMatchfield* hex = gameWidGame->getVectorVectorHexagonMatchfield()[i][j];

            //Groesse der Bilder
            int PicSizeX = hex->pixmap().size().width();
            int PicSizeY = hex->pixmap().size().height();
            if(i & 1)
            {
                hex->setPos( i * 2 * PicSizeX / 3, j * PicSizeY + (PicSizeY / 2));
            }
            else
            {
                hex->setPos( i * 2 * PicSizeX / 3, j * PicSizeY);
            }
            gameWidGameScene->addItem(hex);
        }
    }
    ui->graphicsView_gameView->setScene( gameWidGameScene );
}

void GameWidget::gameWidcreateButtonBar()
{
    int spacingX = 70;

    for(unsigned int i = 0; i < gameWidGame->getButton_menueBar().size(); i++)
    {
        gameWidGame->getButton_menueBar()[i]->setPos(i*spacingX,0);
        gameWidButtonScene->addItem(gameWidGame->getButton_menueBar()[i]);
    }
    gameWidButtonScene->update();
}

HexagonDisplayInfo::HexagonDisplayInfo(HexagonMatchfield *ptr_hexMfield)
:QObject(0), QGraphicsRectItem(QRectF(-50,-50,230,100), 0), hexToDisplay(ptr_hexMfield)
{
    update();
}

void HexagonDisplayInfo::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-50 ,-50, hexToDisplay->pixmap());
    painter->drawText(QRectF(20,-50,200,20),qStringHexDispHexType);

    if(hexToDisplay->getUnit_stationed() != nullptr)
    {
        painter->drawPixmap(-50,-50, hexToDisplay->getUnit_stationed()->pixmap());
        painter->drawText(QRectF(20,-30,200,20),qStringUnitDispUnitType);
        painter->drawText(QRectF(20,-10,200,20),qStringUnitDispUnitLife);
        painter->drawText(QRectF(20,10,200,20),qStringUnitDispMovement);
        painter->drawText(QRectF(20,30,200,20),qStringUnitDispUnitAttack);
    }
}

void HexagonDisplayInfo::update()
{
    qStringHexDispHexType = "Hex Typ: " + hexToDisplay->getHexMatchfieldType();

    if(hexToDisplay->getUnit_stationed() != nullptr)
    {
        qStringUnitDispUnitType = "Unit Typ: " + hexToDisplay->getUnit_stationed()->getUnitType();
        qStringUnitDispUnitLife = "HP: " + QString::number(hexToDisplay->getUnit_stationed()->getUnitCurrentHP()) + "/"
                                            + QString::number(hexToDisplay->getUnit_stationed()->getUnitHP());
        if(hexToDisplay->getUnit_stationed()->getUnitMoveRange() > 0)
        {
            qStringUnitDispMovement = "MoveRange: " + QString::number(hexToDisplay->getUnit_stationed()->getUnitMoveRange()) + "/"
                    + QString::number(hexToDisplay->getUnit_stationed()->getUnitCurrentMoveRange());
        }else{
            qStringUnitDispMovement = "";
        }
        if(hexToDisplay->getUnit_stationed()->getUnitAirAtt() == 0
                && hexToDisplay->getUnit_stationed()->getUnitGroundAtt() == 0
                && hexToDisplay->getUnit_stationed()->getUnitWaterAtt() == 0)
        {

            qStringUnitDispUnitAttack = "Attack: " + QString::number(hexToDisplay->getUnit_stationed()->getUnitAirAtt()) + "/"
                    + QString::number(hexToDisplay->getUnit_stationed()->getUnitGroundAtt()) + "/"
                    + QString::number(hexToDisplay->getUnit_stationed()->getUnitWaterAtt());
        }else{
            qStringUnitDispUnitAttack = "";
        }
    }
}
