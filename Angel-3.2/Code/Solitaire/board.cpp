#include "board.h"
#include "game.h"

Board::Board()
{
    theWorld.Initialize(1024, 768, "Solitaire", false, false, true);

    //YOUR GAME SETUP CODE HERE
    //set background
//    Actor *background = new Actor();
//    background->SetColor(0.0f, 0.60f, 0.16f);
//    background->SetSize(100.0f);
//    background->SetDrawShape(ADS_Square);

//    theWorld.Add(background);
    theWorld.SetBackgroundColor(Color(0.0f, 0.60f, 0.16f));
    theWorld.Add(new GridActor());
    drawCards();

    theGame.start();
}

Board::~Board()
{
}

void Board::drawCards()
{
    Vector2 topRight = theCamera.GetWorldMaxVertex();
    Vector2 bottomLeft = theCamera.GetWorldMinVertex();
    Vector2 topLeft (bottomLeft.X, topRight.Y);
    Vector2 bottomRight (topRight.X, bottomLeft.Y);

    //sysLog.Log("maxVec: " + std::to_string(maxVec.X) + " " + std::to_string(maxVec.Y));
    //sysLog.Log("minVec: " + std::to_string(minVec.X) + " " + std::to_string(minVec.Y));
    for (int i = 0; i < 13; i++) //columns
        for (int j = 0; j < 3; j++)
        {
            sysLog.Log("i, j: " + std::to_string(i) + " " + std::to_string(j));
            Actor *card = new Actor();
            card->SetName("Card");
            card->SetColor(0.50f, 0.0f, 0.16f);
            card->SetSize(3.0f, 5.0f);
            card->SetDrawShape(ADS_Square);
            card->SetPosition(bottomLeft.X + i * 3.0 + i * 1.0f, topLeft.Y - j * 5.0 - j * 1.0f);
            theWorld.Add(card);
        }
}
