#include "board.h"
#include "game.h"
#include "solitairelogic.h"
#include "cardcontroller.h"

Board::Board()
    : _nameOfClickedCard("")
    , _cards(int(Card::Type::COUNT), std::vector<CardController*>(int(Card::Value::COUNT)))
{
    for (int i = 0; i < _cards.size(); i++)
        for (int j = 0; j < _cards[i].size(); j++)
            _cards[i][j] = nullptr;

    registerCardFilenames();
    theWorld.Initialize(1024, 768, "Solitaire", false, false, false);
    theWorld.SetBackgroundColor(Color(0.0f, 0.60f, 0.16f));
}

Board::~Board()
{
    for (int i = 0; i < _cards.size(); i++)
        for (int j = 0; j < _cards[i].size(); j++)
        {
            _cards[i][j]->Destroy();
            delete _cards[i][j];
        }
}

void Board::parseMoveInfo(const MoveInfo& moveInfo)
{
    for (auto& c : moveInfo.getCreations())
    {
        if (_cards[c.position.row][c.position.offset] != nullptr)
            sysLog.Log("Creating card on top of a previous one.");
        else
            _cards[c.position.row][c.position.offset] =
                    new CardController();

        CardController* cc = _cards[c.position.row][c.position.offset];
        cc->setCard(c.card);
        std::stringstream ss;
        ss << c.card.toString() << " (" << c.position.row << "," << c.position.offset << ")";
        sysLog.Log(ss.str());

        cc->SetName("Card");
        cc->Tag("card");
        cc->SetSprite(_cardsRegistry[c.card]);

        // I don't like it. TODO:
        // we should calculate those in window resize handler and keep stored.
        Vector2 topRight = theCamera.GetWorldMaxVertex();
        Vector2 bottomLeft = theCamera.GetWorldMinVertex();
        Vector2 topLeft (bottomLeft.X, topRight.Y);
        float screenWidth = topRight.X + MathUtil::Abs(topLeft.X);
        float cardWidth = screenWidth / (14.0f + screenWidth * 0.1);
        float cardHeight = cardWidth / 0.65f;
        cc->SetSize(cardWidth, cardHeight);

        cc->SetDrawShape(ADS_Square);
        // TODO: get rid of magic numbers
        cc->SetPosition(cardWidth + bottomLeft.X + c.position.offset * cardWidth + c.position.offset * 2.6f/14.0f,
                        topLeft.Y - cardHeight - c.position.row * cardHeight - c.position.row * 1.0f);
        theWorld.Add(cc);
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
