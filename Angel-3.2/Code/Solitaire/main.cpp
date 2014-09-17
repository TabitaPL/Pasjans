#include <iostream>
#include <Angel.h>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    // get things going
    //  optional parameters:
    //		int windowWidth			default: 1024
    //		int windowHeight		default: 768
    //		std::string windowName	default: "Angel Engine"
    //		bool antiAliasing		default: false
    //		bool fullScreen			default: false
    //		bool resizable			default: false
    theWorld.Initialize(1024, 768, "Solitaire", false, false, true);

    //adds the default grid so you can more easily place Actors

    //YOUR GAME SETUP CODE HERE
    Actor *background = new Actor();
    background->SetColor(0.0f, 0.60f, 0.16f);
    background->SetSize(100.0f);
    background->SetDrawShape(ADS_Square);
    theWorld.Add(background);

    // do all your setup first, because this function won't return until you're exiting
    theWorld.StartGame();

    sysLog.Log("Start of the game");

    // any cleanup can go here
    theWorld.Destroy();
    return 0;
}

