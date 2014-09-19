#include "board.h"
#include "game.h"

Board::Board()
{
    theWorld.Initialize(800, 600, "Solitaire", false, false, false);

    //YOUR GAME SETUP CODE HERE
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
    //Vector2 bottomRight (topRight.X, bottomLeft.Y);

    float screenWeidth = topRight.X + MathUtil::Abs(topLeft.X);

    float cardWidth = screenWeidth / (13.0f + screenWeidth * 0.1);
    float cardHeight = cardWidth / 0.65f;


//    sysLog.Log("cardWeidth: " + std::to_string(cardWidth) + " " + std::to_string(cardHeight));
//    sysLog.Log("minVec: " + std::to_string(topRight.X) + " " + std::to_string(topLeft.X));
    for (int i = 0; i < 13; i++) //columns
        for (int j = 0; j < 4; j++)
        {
            Actor *card = new Actor();
            card->SetName("Card");
            card->SetColor(0.5f, 0.2f, 0.8f);
            card->SetSize(cardWidth, cardHeight);
            card->SetDrawShape(ADS_Square);
            card->SetPosition(cardWidth + bottomLeft.X + i * cardWidth + i * 2.6f/13.0f, topLeft.Y - cardHeight - j * cardHeight - j * 1.0f);
            theWorld.Add(card);
        }
}
