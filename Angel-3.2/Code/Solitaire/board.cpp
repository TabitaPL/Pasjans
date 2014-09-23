#include "board.h"
#include "game.h"
#include "solitairelogic.h"

Board::Board(): _nameOfClickedCard("")
{
    registerCardFilenames();
    theWorld.Initialize(1024, 768, "Solitaire", false, false, false);
    theWorld.SetBackgroundColor(Color(0.0f, 0.60f, 0.16f));
    drawCards();
}

Board::~Board()
{
    while (!_objects.empty())
    {
        _objects.back()->Destroy();
        delete _objects.back();
        _objects.pop_back();
    }
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

void Board::setCards(std::vector<Card> *cards)
{
    std::vector<Card> allLogicCards;

    //concatenate all 4 rows into one
    for (int i = 0; i < 4; i++)
        allLogicCards.insert(allLogicCards.end(), cards[i].begin(), cards[i].end());

    auto currentLogicCard = allLogicCards.begin();
    ActorSet actorCardsOnBoard = theTagList.GetObjectsTagged("card");
    for (Actor* card : actorCardsOnBoard)
       {
           if (currentLogicCard != allLogicCards.end())
           {
               card->SetSprite(_cardsRegistry[Card((*currentLogicCard).type, (*currentLogicCard).value)]);
               currentLogicCard++;
           }
           else
               break;
       }
}

void Board::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
    Vector2 clickedPlace = MathUtil::ScreenToWorld(screenCoordinates.X, screenCoordinates.Y);
    ActorSet cards = theTagList.GetObjectsTagged("card");

    for (Actor* card : cards )
    {
        BoundingBox boundingBox = card->GetBoundingBox();
        if (boundingBox.Intersects(clickedPlace, 0))
        {
            if (_nameOfClickedCard == "")
            {
                _nameOfClickedCard = card->GetName();
                card->SetColor(Color(0.0, 0.0, 1.0));
            }
            else
            {
                Actor *previous = Actor::GetNamed(_nameOfClickedCard);
                //swap graphic of previous and a
                if (previous != nullptr)
                {
                    previous->MoveTo(card->GetPosition(), 1.0);
                    card->MoveTo(previous->GetPosition(), 1.0);
                    _nameOfClickedCard = "";
                    previous->SetColor(Color(1.0, 1.0, 1.0));
                }
                break;
            }
            break;
        }
    }
}

void Board::registerCardFilenames()
{
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::TWO), std::string("Resources/Images/Deck/CLUB/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::THREE), std::string("Resources/Images/Deck/CLUB/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::FOUR), std::string("Resources/Images/Deck/CLUB/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::FIVE), std::string("Resources/Images/Deck/CLUB/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::SIX), std::string("Resources/Images/Deck/CLUB/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::SEVEN), std::string("Resources/Images/Deck/CLUB/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::EIGHT), std::string("Resources/Images/Deck/CLUB/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::NINE), std::string("Resources/Images/Deck/CLUB/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::TEN), std::string("Resources/Images/Deck/CLUB/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::JACK), std::string("Resources/Images/Deck/CLUB/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::QUEEN), std::string("Resources/Images/Deck/CLUB/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::KING), std::string("Resources/Images/Deck/CLUB/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::ACE), std::string("Resources/Images/Deck/CLUB/A.png")));

    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::TWO), std::string("Resources/Images/Deck/DIAMOND/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::THREE), std::string("Resources/Images/Deck/DIAMOND/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::FOUR), std::string("Resources/Images/Deck/DIAMOND/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::FIVE), std::string("Resources/Images/Deck/DIAMOND/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::SIX), std::string("Resources/Images/Deck/DIAMOND/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::SEVEN), std::string("Resources/Images/Deck/DIAMOND/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::EIGHT), std::string("Resources/Images/Deck/DIAMOND/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::NINE), std::string("Resources/Images/Deck/DIAMOND/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::TEN), std::string("Resources/Images/Deck/DIAMOND/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::JACK), std::string("Resources/Images/Deck/DIAMOND/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::QUEEN), std::string("Resources/Images/Deck/DIAMOND/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::KING), std::string("Resources/Images/Deck/DIAMOND/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::ACE), std::string("Resources/Images/Deck/DIAMOND/A.png")));

    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::TWO), std::string("Resources/Images/Deck/HEART/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::THREE), std::string("Resources/Images/Deck/HEART/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::FOUR), std::string("Resources/Images/Deck/HEART/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::FIVE), std::string("Resources/Images/Deck/HEART/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::SIX), std::string("Resources/Images/Deck/HEART/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::SEVEN), std::string("Resources/Images/Deck/HEART/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::EIGHT), std::string("Resources/Images/Deck/HEART/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::NINE), std::string("Resources/Images/Deck/HEART/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::TEN), std::string("Resources/Images/Deck/HEART/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::JACK), std::string("Resources/Images/Deck/HEART/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::QUEEN), std::string("Resources/Images/Deck/HEART/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::KING), std::string("Resources/Images/Deck/HEART/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::ACE), std::string("Resources/Images/Deck/HEART/A.png")));

    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::TWO), std::string("Resources/Images/Deck/SPADE/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::THREE), std::string("Resources/Images/Deck/SPADE/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::FOUR), std::string("Resources/Images/Deck/SPADE/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::FIVE), std::string("Resources/Images/Deck/SPADE/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::SIX), std::string("Resources/Images/Deck/SPADE/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::SEVEN), std::string("Resources/Images/Deck/SPADE/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::EIGHT), std::string("Resources/Images/Deck/SPADE/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::NINE), std::string("Resources/Images/Deck/SPADE/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::TEN), std::string("Resources/Images/Deck/SPADE/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::JACK), std::string("Resources/Images/Deck/SPADE/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::QUEEN), std::string("Resources/Images/Deck/SPADE/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::KING), std::string("Resources/Images/Deck/SPADE/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::ACE), std::string("Resources/Images/Deck/SPADE/A.png")));
}
