#include "board.h"
#include "game.h"
#include "window.h"
#include "solitairelogic.h"
#include "cardactor.h"

Board::Board()
    : _nameOfClickedCard("")
    , _spaceBetweenCards(0.01f)
    , _cards(int(Card::Type::COUNT), std::vector<CardActor*>(int(Card::Value::COUNT) + 1))
	, _rowCount(int(Card::Type::COUNT))
	, _columnCount(int(Card::Value::COUNT) + 1)
	, _frames(int(Card::Type::COUNT), std::vector<Actor*>(int(Card::Value::COUNT) + 1))
{
    for (unsigned int i = 0; i < _cards.size(); i++)
		for (unsigned int j = 0; j < _cards[i].size(); j++)
        {
            _cards[i][j] = nullptr;
        }

    registerCardFilenames();
    theWindow.setHorizontalMargin(1.0);
    std::pair<int, int> resolution(640, 480);
    theWorld.Initialize(resolution.first, resolution.second,
                        "Solitaire", false, false, false);
    theWindow.setResolution(resolution);
    theWorld.SetBackgroundColor(Color(0.0f, 0.60f, 0.16f));

	_cardWidth = theWindow.getWorldScreenWidth() / 
		(static_cast<float>(Card::Value::COUNT) +
		theWindow.getHorizontalMargin() * 2 +
		_spaceBetweenCards * (static_cast<float>(Card::Value::COUNT) - 1));

	drawFrame();
}

Board::~Board()
{
    //delete cards and frames
    for (unsigned int i = 0; i < _cards.size(); i++)
        for (unsigned int j = 0; j < _cards[i].size(); j++)
        {
            _cards[i][j]->Destroy();
            delete _cards[i][j];
        }
    for (unsigned int i = 0; i < _frames.size(); i++)
        for (unsigned int j = 0; j < _frames[i].size(); j++)
        {
            _frames[i][j]->Destroy();
            delete _frames[i][j];
        }
}


void Board::drawFrame()
{
	//drawFrames
	float positionX, positionY;
	for (int row = 0; row < _rowCount; row++)
	{
		for (int column = 0; column < _columnCount; column++)
		{
			_frames[row][column] = new Actor();
			_frames[row][column]->SetSize(Vector2(_cardWidth, _cardWidth / 0.65f));
			_frames[row][column]->Tag("frame");
			_frames[row][column]->SetDrawShape(ADS_Square);
			_frames[row][column]->SetSprite("Resources/Images/frame.png");
			_frames[row][column]->SetLayer(1);

			positionX = _cardWidth + theWindow.minX() + column * _cardWidth +
				column * theWindow.getWorldScreenWidth() * _spaceBetweenCards /
				(static_cast<float>(Card::Type::COUNT) + theWindow.getHorizontalMargin() * 2.0);

			//std::cout << "positionX " << positionX << ": cardWidth " << _cardWidth << " " << theWindow.minX() << " " << column << " " << theWindow.getWorldScreenWidth()
			//	<< " " << _spaceBetweenCards << std::to_string(static_cast<float>(Card::Type::COUNT)) << " " << theWindow.getHorizontalMargin() <<std::endl;

			positionY = theWindow.maxY() - _frames[row][column]->GetSize().Y -
				row *_frames[row][column]->GetSize().Y - row;

			_frames[row][column]->SetPosition(positionX, positionY);
			theWorld.Add(_frames[row][column]);
		}
	}
}

void Board::createCard(Creation creation)
{
    float positionX, positionY;
    if (_cards[creation.position.row][creation.position.column] != nullptr)
        sysLog.Log("Creating card on top of a previous one.");
    else
        _cards[creation.position.row][creation.position.column] =
                new CardActor();

    if (creation.card != nullptr)
    {
        CardActor* cardActor = _cards[creation.position.row][creation.position.column];
        cardActor->setCard(creation.card);
		cardActor->setWidth(_cardWidth);
//        std::stringstream ss;
//        ss << c.card.toString() << " (" << c.position.row << "," << c.position.column << ")";
//        sysLog.Log(ss.str());

        cardActor->SetName("Card");
        cardActor->Tag("card");
        cardActor->SetLayer(2);
        if (_cardsRegistry.count(*creation.card) > 0)
            cardActor->SetSprite(_cardsRegistry[*creation.card]); // should we register pointers...? probably not

		cardActor->SetSize(_cardWidth, cardActor->GetSize().Y);
        cardActor->SetDrawShape(ADS_Square);
		positionX = _cardWidth + theWindow.minX() + creation.position.column * _cardWidth +
                creation.position.column * theWindow.getWorldScreenWidth() * _spaceBetweenCards/
                (static_cast<float>(Card::Type::COUNT) + theWindow.getHorizontalMargin() * 2.0);

        positionY = theWindow.maxY() - cardActor->GetSize().Y - creation.position.row * cardActor->GetSize().Y - creation.position.row;

        cardActor->SetPosition(positionX, positionY);

        theWorld.Add(cardActor);
    }
    else
    {
        // handle creating and setting the empty space
    }
}

void Board::parseMoveInfo(const MoveInfo& moveInfo)
{
    for (auto& creation : moveInfo.getCreations())
    {
        createCard(creation);
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
    std::string path = "Resources/Images/PNG-cards-1.3/";

    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::TWO), std::string(path + "CLUB/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::THREE), std::string(path + "CLUB/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::FOUR), std::string(path + "CLUB/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::FIVE), std::string(path + "CLUB/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::SIX), std::string(path + "CLUB/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::SEVEN), std::string(path + "CLUB/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::EIGHT), std::string(path + "CLUB/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::NINE), std::string(path + "CLUB/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::TEN), std::string(path + "CLUB/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::JACK), std::string(path + "CLUB/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::QUEEN), std::string(path + "CLUB/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::KING), std::string(path + "CLUB/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::CLUB, Card::Value::ACE), std::string(path + "CLUB/A.png")));

    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::TWO), std::string(path + "DIAMOND/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::THREE), std::string(path + "DIAMOND/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::FOUR), std::string(path + "DIAMOND/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::FIVE), std::string(path + "DIAMOND/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::SIX), std::string(path + "DIAMOND/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::SEVEN), std::string(path + "DIAMOND/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::EIGHT), std::string(path + "DIAMOND/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::NINE), std::string(path + "DIAMOND/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::TEN), std::string(path + "DIAMOND/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::JACK), std::string(path + "DIAMOND/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::QUEEN), std::string(path + "DIAMOND/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::KING), std::string(path + "DIAMOND/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::DIAMOND, Card::Value::ACE), std::string(path + "DIAMOND/A.png")));

    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::TWO), std::string(path + "HEART/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::THREE), std::string(path + "HEART/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::FOUR), std::string(path + "HEART/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::FIVE), std::string(path + "HEART/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::SIX), std::string(path + "HEART/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::SEVEN), std::string(path + "HEART/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::EIGHT), std::string(path + "HEART/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::NINE), std::string(path + "HEART/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::TEN), std::string(path + "HEART/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::JACK), std::string(path + "HEART/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::QUEEN), std::string(path + "HEART/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::KING), std::string(path + "HEART/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::HEART, Card::Value::ACE), std::string(path + "HEART/A.png")));

    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::TWO), std::string(path + "SPADE/2.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::THREE), std::string(path + "SPADE/3.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::FOUR), std::string(path + "SPADE/4.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::FIVE), std::string(path + "SPADE/5.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::SIX), std::string(path + "SPADE/6.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::SEVEN), std::string(path + "SPADE/7.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::EIGHT), std::string(path + "SPADE/8.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::NINE), std::string(path + "SPADE/9.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::TEN), std::string(path + "SPADE/10.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::JACK), std::string(path + "SPADE/J.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::QUEEN), std::string(path + "SPADE/Q.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::KING), std::string(path + "SPADE/K.png")));
    _cardsRegistry.insert(std::pair<Card, std::string>(Card(Card::Type::SPADE, Card::Value::ACE), std::string(path + "SPADE/A.png")));
}
