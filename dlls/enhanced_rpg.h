// Enhanced RPG - الصاروخ المحسّن
// تحسينات: سرعة أعلى، ضرر أكبر، وقت إعادة تحميل أقل

#ifndef ENHANCED_RPG_H
#define ENHANCED_RPG_H

#include "weapons.h"

// RPG محسّن - ضرر 200 بدلاً من 150
#define ENHANCED_RPG_DAMAGE 200
#define ENHANCED_RPG_RADIUS 200
#define ENHANCED_RPG_SPEED 1000 // سرعة صاروخ محسّنة
#define ENHANCED_RPG_RELOAD_TIME 1.5 // وقت إعادة تحميل أسرع

class CEnhancedRPG : public CBasePlayerWeapon
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
    
    void FireRocket();
    
    bool m_fSpotActive;
    int m_cActiveRockets;
    
private:
    enum EnhancedRPGAnim
    {
        RPG_IDLE = 0,
        RPG_FIDGET = 1,
        RPG_FIRE = 2,
        RPG_HOLSTER = 3,
        RPG_DRAW = 4,
        RPG_RELOAD = 5,
    };
};

// صاروخ محسّن - أسرع وأقوى
class CEnhancedRPGRocket : public CGrenade
{
public:
    void Spawn() override;
    void Precache() override;
    
    void EXPORT RocketTouch(CBaseEntity* pOther);
    void EXPORT RocketExplode();
    void EXPORT RocketThink();
    
    int m_iTrail;
    float m_flIgniteTime;
    
    virtual int Save(CSave& save);
    virtual int Restore(CRestore& restore);
    static TYPEDESCRIPTION m_SaveData[];
};

#endif
