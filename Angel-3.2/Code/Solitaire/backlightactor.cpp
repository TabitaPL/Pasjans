#include "backlightactor.h"

BacklightActor::BacklightActor()
{
    cardActor.setLogicalPosition(0,0);
    cardActor.SetPosition(0,0);
    cardActor.setCard(new Card(Card::Type::CLUB, Card::Value::ACE));
    cardActor.SetSprite("Resources/Images/PNG-cards-1.3/CLUB/2.png");
    cardActor.SetSize(4,5);

    // I should accept some kind of rectangle as argument
    // like orign point and height & width
    // based on this, I'll be able set 4 particleActors

    ParticleActor *pa = new ParticleActor();
    pa->SetColor(1.0f, 1.0f, 0.0f);  // Sets the initial color of the particles.
                                     // Since the image file we'll be using already
                                     // has a color, we set this to pure white.

    pa->SetSize(Vector2(0.2f, 0.2f));  // The size of each particle, in GL units
    pa->SetMaxParticles(500);          // The maximum number of particles this system will ever handle.
    pa->SetParticlesPerSecond(100.0f); // Emission Rate
    pa->SetParticleLifetime(1.5f);     // How long each particles lasts before disappearing
    pa->SetSpread(MathUtil::Pi / 360); // The angle in radians at which particles will be emitted.
    pa->SetEndScale(2.0f);             // If you want the particles to change size over their lifetimes
    pa->SetEndColor(Color(1.0f, 1.0f, 1.0f, 0.0f)); // Our particles disappear over time
    pa->SetSpeedRange(3.0f, 4.0f);     // The minimum and maximum range of speeds (so you can have
                                       // some variation).
    pa->SetGravity(Vector2::Zero);     // You can pull the particles in a particular direction (default is
                                       // downwards, so zero it out if you need to).
    theWorld.Add(pa);

    theWorld.Add(&cardActor);
}
