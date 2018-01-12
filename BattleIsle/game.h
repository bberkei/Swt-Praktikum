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

#ifndef GAME_H
#define GAME_H

#include "options.h"
#include "hexagonmatchfield.h"
#include "button.h"
#include "gamewidget.h"
#include "unit.h"

#include <vector>
#include <QTime>
#include <QObject>
#include <queue>

class GameWidget; //Vorwärtsdeklaration
class HexagonMatchfield;
class Unit;
class Button;

class Game : public QObject
{
    Q_OBJECT
private:
    HexagonMatchfield* SelectionCache;
    std::vector<HexagonMatchfield*> TargetChache;
    std::vector<std::vector<HexagonMatchfield*>> hexagonMatchfield_gameGrid;
    std::vector<std::vector<Unit*>> unit_UnitGrid;
    std::vector<Button*> button_menueBar;
    Options* gameOptions;
    GameWidget* ptr_gameGameWid;

    std::map<HexagonMatchfield*, HexagonMatchfield*> came_from;
    std::map<HexagonMatchfield*, int> current_cost;

    static std::vector<QPoint> vector_oddNeighbors;
    static std::vector<QPoint> vector_evenNeighbors;
public:
    Game(Options* init_options, GameWidget* ptr_gameWid);
    void processSelection(HexagonMatchfield* selection);
    //Game(QString pathToSaveFile);
    //void loadGame(QString pathToSaveFile);
    //void saveGame();
    //void endGame();
    //int showUnitNumber(Player* player);
    //int showTotalEnergie(Player* player);
    void Dijkstra();
    //void calculateActionTargets();
    void buttonPressedMove();
    void buttonPressedAction();
    //void buttonPressedInformation();
    //void buttonPressedMap();
    void buttonPressedMenue();
    void buttonPressedChangePhase();
    void resetStateHex(); // Nicht im UML-Diagramm, ist nur eine Hilfsfunktion für processSelection

/*TestFunktionen*/
    void showNeighbors(HexagonMatchfield*);
/*TestFunktionen Ende*/

    // get und set Methoden
    std::vector<std::vector<HexagonMatchfield*>> getVectorVectorHexagonMatchfield();
    std::vector<Button *> getButton_menueBar();
    void setButton_menueBar(const std::vector<Button *> &value);

public slots:
};
class Compare
{
public:
    bool operator ()(std::pair<HexagonMatchfield *, int> a, std::pair<HexagonMatchfield *, int> b);
};
#endif // GAME_H
