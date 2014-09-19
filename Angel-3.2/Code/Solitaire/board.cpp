#include "board.h"
#include "game.h"

Board::Board(): nameOfClickedCard("")
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
    for (int i = 0; i < 13; i++) //columns
        for (int j = 0; j < 4; j++)
        {
            Actor *card = new Actor();
            card->SetName("Card");
            card->Tag("card");
            card->SetSprite("Resources/Images/Deck/Back_SunFlower.png");
            card->SetSize(cardWidth, cardHeight);
            card->SetDrawShape(ADS_Square);
            card->SetPosition(cardWidth + bottomLeft.X + i * cardWidth + i * 2.6f/13.0f, topLeft.Y - cardHeight - j * cardHeight - j * 1.0f);
            theWorld.Add(card);
        }
}

void Board::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
    Vector2 clickedPlace = MathUtil::ScreenToWorld(screenCoordinates.X, screenCoordinates.Y);
    ActorSet cards = theTagList.GetObjectsTagged("card");

    for (Actor* a : cards )
    {
        BoundingBox bbox = a->GetBoundingBox();
        if ( bbox.Intersects(clickedPlace, 0) )
        {
            if (nameOfClickedCard == "")
            {
                nameOfClickedCard = a->GetName();
                a->SetSprite("Resources/Images/angel.png");
            }
            else
            {
                Actor *previous = Actor::GetNamed(nameOfClickedCard);
                sysLog.Log("Previous name: " + previous->GetName());
                sysLog.Log("Current name: " + a->GetName());
                //swap graphic of previous and a
                previous->MoveTo(a->GetPosition(), 2.0);
                a->MoveTo(previous->GetPosition(), 2.0);
                nameOfClickedCard = "";
                previous = NULL;
                break;
            }
            break;
        }
    }
}
