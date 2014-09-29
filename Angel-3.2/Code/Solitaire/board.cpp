#include "board.h"
#include "game.h"
#include "window.h"
#include "solitairelogic.h"
#include "cardactor.h"

Board::Board()
    : _nameOfClickedCard("")
    , _cards(int(Card::Type::COUNT), std::vector<CardActor*>(int(Card::Value::COUNT) + 1))
{
    for (int i = 0; i < _cards.size(); i++)
        for (int j = 0; j < _cards[i].size(); j++)
            _cards[i][j] = nullptr;

    registerCardFilenames();
    theWindow.setHorizontalMargin(1.0);
    theWindow.setResolution(std::pair<int, int>(1920, 1080));
    theWorld.Initialize(theWindow.getResolution().first, theWindow.getResolution().second,
                        "Solitaire", false, false, false);
    theWindow.setResolution(std::pair<int, int>(1920, 1080)); //again, because it has to be set after World Initialization
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
    //compute size of cards
    float spaceBetweenCards = 0.05; //in pixels
    float cardWidth = theWindow.getWorldScreenWidth() /
            (static_cast<float>(Card::Value::COUNT) +
             theWindow.getHorizontalMargin() * 2 +
             spaceBetweenCards * (static_cast<float>(Card::Value::COUNT) - 1));
    float cardPositionX, cardPositionY;
    for (auto& creation : moveInfo.getCreations())
    {
        if (_cards[creation.position.row][creation.position.column] != nullptr)
            sysLog.Log("Creating card on top of a previous one.");
        else
            _cards[creation.position.row][creation.position.column] =
                    new CardActor();


        if (creation.card != nullptr)
        {
            CardActor* cardActor = _cards[creation.position.row][creation.position.column];
            cardActor->setCard(creation.card);
            cardActor->setWidth(cardWidth);
//        std::stringstream ss;
//        ss << c.card.toString() << " (" << c.position.row << "," << c.position.column << ")";
//        sysLog.Log(ss.str());

            cardActor->SetName("Card");
            cardActor->Tag("card");
            if (_cardsRegistry.count(*creation.card) > 0)
                cardActor->SetSprite(_cardsRegistry[*creation.card]); // should we register pointers...? probably not
            else
                cardActor->SetSprite(std::string("Resources/Images/DeckPony/Back.png"));

            cardActor->SetSize(cardWidth, cardActor->getHeight());
            //sysLog.Log("Size of card: " + std::to_string(cardWidth) + " " + std::to_string(cc->getHeight()));
            cardActor->SetDrawShape(ADS_Square);
            cardPositionX = cardWidth + theWindow.minX() + creation.position.column * cardWidth +
                    creation.position.column * theWindow.getWorldScreenWidth() * spaceBetweenCards/
                    (static_cast<float>(Card::Type::COUNT) + theWindow.getHorizontalMargin() * 2.0);
            cardPositionY = theWindow.maxY() - cardActor->getHeight() - creation.position.row * cardActor->getHeight() - creation.position.row;

            cardActor->SetPosition(cardPositionX, cardPositionY);
            //sysLog.Log("Position of card: " + std::to_string(cardPositionX) + " " + std::to_string(cardPositionY));
            theWorld.Add(cardActor);
        }
        else
        {
            // handle creating and setting the empty space
        }
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
                //swap graphic of previous and current
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
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::TWO), std::string("Resources/Images/DeckPony/CLUB/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::THREE), std::string("Resources/Images/DeckPony/CLUB/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::FOUR), std::string("Resources/Images/DeckPony/CLUB/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::FIVE), std::string("Resources/Images/DeckPony/CLUB/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::SIX), std::string("Resources/Images/DeckPony/CLUB/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::SEVEN), std::string("Resources/Images/DeckPony/CLUB/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::EIGHT), std::string("Resources/Images/DeckPony/CLUB/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::NINE), std::string("Resources/Images/DeckPony/CLUB/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::TEN), std::string("Resources/Images/DeckPony/CLUB/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::JACK), std::string("Resources/Images/DeckPony/CLUB/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::QUEEN), std::string("Resources/Images/DeckPony/CLUB/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::KING), std::string("Resources/Images/DeckPony/CLUB/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::ACE), std::string("Resources/Images/DeckPony/CLUB/A.png")));

    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::TWO), std::string("Resources/Images/DeckPony/DIAMOND/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::THREE), std::string("Resources/Images/DeckPony/DIAMOND/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::FOUR), std::string("Resources/Images/DeckPony/DIAMOND/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::FIVE), std::string("Resources/Images/DeckPony/DIAMOND/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::SIX), std::string("Resources/Images/DeckPony/DIAMOND/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::SEVEN), std::string("Resources/Images/DeckPony/DIAMOND/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::EIGHT), std::string("Resources/Images/DeckPony/DIAMOND/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::NINE), std::string("Resources/Images/DeckPony/DIAMOND/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::TEN), std::string("Resources/Images/DeckPony/DIAMOND/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::JACK), std::string("Resources/Images/DeckPony/DIAMOND/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::QUEEN), std::string("Resources/Images/DeckPony/DIAMOND/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::KING), std::string("Resources/Images/DeckPony/DIAMOND/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::ACE), std::string("Resources/Images/DeckPony/DIAMOND/A.png")));

    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::TWO), std::string("Resources/Images/DeckPony/HEART/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::THREE), std::string("Resources/Images/DeckPony/HEART/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::FOUR), std::string("Resources/Images/DeckPony/HEART/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::FIVE), std::string("Resources/Images/DeckPony/HEART/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::SIX), std::string("Resources/Images/DeckPony/HEART/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::SEVEN), std::string("Resources/Images/DeckPony/HEART/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::EIGHT), std::string("Resources/Images/DeckPony/HEART/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::NINE), std::string("Resources/Images/DeckPony/HEART/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::TEN), std::string("Resources/Images/DeckPony/HEART/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::JACK), std::string("Resources/Images/DeckPony/HEART/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::QUEEN), std::string("Resources/Images/DeckPony/HEART/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::KING), std::string("Resources/Images/DeckPony/HEART/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::ACE), std::string("Resources/Images/DeckPony/HEART/A.png")));

    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::TWO), std::string("Resources/Images/DeckPony/SPADE/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::THREE), std::string("Resources/Images/DeckPony/SPADE/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::FOUR), std::string("Resources/Images/DeckPony/SPADE/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::FIVE), std::string("Resources/Images/DeckPony/SPADE/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::SIX), std::string("Resources/Images/DeckPony/SPADE/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::SEVEN), std::string("Resources/Images/DeckPony/SPADE/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::EIGHT), std::string("Resources/Images/DeckPony/SPADE/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::NINE), std::string("Resources/Images/DeckPony/SPADE/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::TEN), std::string("Resources/Images/DeckPony/SPADE/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::JACK), std::string("Resources/Images/DeckPony/SPADE/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::QUEEN), std::string("Resources/Images/DeckPony/SPADE/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::KING), std::string("Resources/Images/DeckPony/SPADE/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::ACE), std::string("Resources/Images/DeckPony/SPADE/A.png")));
}
