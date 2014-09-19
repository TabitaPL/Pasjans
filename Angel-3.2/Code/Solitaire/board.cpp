#include "board.h"
#include "game.h"

Board::Board(): _nameOfClickedCard("")
{
    theWorld.Initialize(1024, 768, "Solitaire", false, false, false);

    //YOUR GAME SETUP CODE HERE
    theWorld.SetBackgroundColor(Color(0.0f, 0.60f, 0.16f));
    drawCards();
}

Board::~Board()
{
    std::vector<Renderable*>::iterator it = _objects.begin();
        while(_objects.end() != it)
        {
            (*it)->Destroy();
            it++;
        }
        _objects.clear();
}

void Board::drawCards()
{
    Vector2 topRight = theCamera.GetWorldMaxVertex();
    Vector2 bottomLeft = theCamera.GetWorldMinVertex();
    Vector2 topLeft (bottomLeft.X, topRight.Y);
    //Vector2 bottomRight (topRight.X, bottomLeft.Y);

    float screenWeidth = topRight.X + MathUtil::Abs(topLeft.X);

    float cardWidth = screenWeidth / (14.0f + screenWeidth * 0.1);
    float cardHeight = cardWidth / 0.65f;

    for (int i = 0; i < 14; i++) //columns
        for (int j = 0; j < 4; j++)
        {
            Actor *card = new Actor();
            card->SetName("Card");
            card->Tag("card");
            card->SetSprite("Resources/Images/Deck/Back_SunFlower.png");
            card->SetSize(cardWidth, cardHeight);
            card->SetDrawShape(ADS_Square);
            card->SetPosition(cardWidth + bottomLeft.X + i * cardWidth + i * 2.6f/14.0f, topLeft.Y - cardHeight - j * cardHeight - j * 1.0f);
            theWorld.Add(card);
            _objects.push_back(card);
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
            if (_nameOfClickedCard == "")
            {
                _nameOfClickedCard = a->GetName();
                a->SetSprite("Resources/Images/angel.png");
            }
            else
            {
                Actor *previous = Actor::GetNamed(_nameOfClickedCard);
                //swap graphic of previous and a
                previous->MoveTo(a->GetPosition(), 1.0);
                a->MoveTo(previous->GetPosition(), 1.0);
                _nameOfClickedCard = "";
                previous = NULL;
                delete previous;
                break;
            }
            break;
        }
    }
}
