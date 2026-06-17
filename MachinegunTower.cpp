#include "MachineGunTower.h"
#include "Enemy.h"
#include "Projectile.h"

// Karabin maszynowy: zasięg 150, strzał co 0.2s, obrażenia 5
MachineGunTower::MachineGunTower(sf::Vector2f position)
    : Tower("asets/textures/machine2.png", position, 150.0f, 0.2f, 25,"Karabin",700.f) 
{
    //grafika
    texture.loadFromFile("asets/textures/machine2.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);

    sprite.setOrigin(
        texture.getSize().x / 2.f,
        texture.getSize().y / 2.f
    );

    sprite.setPosition(position);

    float targetSize = 90.f;

    sprite.setScale(
        targetSize / texture.getSize().x,
        targetSize / texture.getSize().y
    );
    baseScale = sprite.getScale();

    //dzwiek
    if (shotBuffer.loadFromFile("asets/sounds/machine.wav"))
    {
        shotSound.setBuffer(shotBuffer);
        shotSound.setVolume(10.f);
    }
}

