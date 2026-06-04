// New Enhanced Plasma Rifle Weapon
#ifndef PLASMA_RIFLE_H
#define PLASMA_RIFLE_H

#include "weapons.h"

#define PLASMA_RIFLE_AMMO_CAPACITY 200

class CPlasmaRifle : public CBasePlayerWeapon
{
public:
    void Spawn() override;
    void Precache() override;
    
    bool GetItemInfo(ItemInfo* p) override;
    bool Deploy() override;
    void Holster() override;
    
    void PrimaryAttack() override;
    void SecondaryAttack() override;
    void Reload() override;
    void WeaponIdle() override;
    
    void FirePlasmaShot();
    void FirePlasmaBlast(); // Secondary attack
    
    float m_flNextSecondaryTime;
    int m_iBeamIndex;
    
private:
    enum PlasmaRifleAnim
    {
        PLASMA_IDLE = 0,
        PLASMA_FIRE1 = 1,
        PLASMA_FIRE2 = 2,
        PLASMA_RELOAD = 3,
        PLASMA_DRAW = 4,
        PLASMA_HOLSTER = 5,
        PLASMA_SECONDARY = 6,
    };
};

#endif
