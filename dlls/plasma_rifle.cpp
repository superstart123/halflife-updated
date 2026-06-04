// Enhanced Plasma Rifle Implementation
#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "weapons.h"
#include "plasma_rifle.h"

LINK_ENTITY_TO_CLASS(weapon_plasma_rifle, CPlasmaRifle);

void CPlasmaRifle::Spawn()
{
    Precache();
    
    m_iId = WEAPON_PLASMA;
    SetObjectCollisionBox();
    
    pev->classname = MAKE_STRING("weapon_plasma_rifle");
    pev->model = MAKE_STRING("models/w_plasma_rifle.mdl");
    
    m_iDefaultAmmo = PLASMA_RIFLE_AMMO_CAPACITY;
    FallInit();
}

void CPlasmaRifle::Precache()
{
    PRECACHE_MODEL("models/w_plasma_rifle.mdl");
    PRECACHE_MODEL("models/v_plasma_rifle.mdl");
    PRECACHE_MODEL("models/p_plasma_rifle.mdl");
    
    PRECACHE_SOUND("weapons/plasma_fire.wav");
    PRECACHE_SOUND("weapons/plasma_reload.wav");
    PRECACHE_SOUND("weapons/plasma_secondary.wav");
    PRECACHE_SOUND("weapons/plasma_idle.wav");
    
    m_iBeamIndex = PRECACHE_MODEL("sprites/plasma_beam.spr");
}

bool CPlasmaRifle::GetItemInfo(ItemInfo* p)
{
    p->pszName = STRING(pev->classname);
    p->pszAmmo1 = "plasma_cells";
    p->iMaxAmmo1 = PLASMA_RIFLE_AMMO_CAPACITY;
    p->pszAmmo2 = NULL;
    p->iMaxAmmo2 = -1;
    p->iMaxClip = 50;
    p->iSlot = 4;
    p->iPosition = 3;
    p->iId = WEAPON_PLASMA;
    p->iWeight = 25;
    p->iFlags = 0;
    return true;
}

bool CPlasmaRifle::Deploy()
{
    return DefaultDeploy("models/v_plasma_rifle.mdl", "models/p_plasma_rifle.mdl", PLASMA_DRAW, "plasma");
}

void CPlasmaRifle::Holster()
{
    m_fInReload = false;
    SendWeaponAnim(PLASMA_HOLSTER);
    
    CBasePlayerWeapon::Holster();
}

void CPlasmaRifle::FirePlasmaShot()
{
    m_flNextPrimaryAttack = gpGlobals->time + 0.08f;
    m_flTimeWeaponIdle = gpGlobals->time + 2.0f;
    
    // ضرر محسّن: 40 نقطة بدلاً من الأسلحة العادية
    Vector vecSrc = m_pPlayer->GetGunPosition();
    Vector vecAiming = m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);
    
    Vector vecDir = vecAiming;
    vecDir = vecDir.Normalize();
    
    // تأثير بصري
    EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/plasma_fire.wav", 1.0, ATTN_NORM, 0, 94 + RANDOM_LONG(0, 15));
    
    SendWeaponAnim(PLASMA_FIRE1);
    
    // إطلاق المقذوف
    CBaseEntity* pPellet = NULL;
    for (int i = 0; i < 1; i++)
    {
        pPellet = m_pPlayer->FireBullets(1, vecSrc, vecDir, VECTOR_CONE_1DEGREES, 8192, BULLET_PLAYER_9MM, 2);
    }
    
    if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
        m_pPlayer->SetSuitUpdate("!HEV_AMO0", false, 0);
    
    m_iClip--;
}

void CPlasmaRifle::FirePlasmaBlast()
{
    // هجوم ثانوي قوي - شعاع بلازما
    m_flNextSecondaryAttack = gpGlobals->time + 0.5f;
    
    Vector vecSrc = m_pPlayer->GetGunPosition();
    Vector vecAiming = m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);
    
    EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/plasma_secondary.wav", 1.0, ATTN_NORM, 0, 100);
    
    SendWeaponAnim(PLASMA_SECONDARY);
    
    // ضرر أعلى للهجوم الثانوي: 60 نقطة
    TraceResult tr;
    UTIL_TraceLine(vecSrc, vecSrc + vecAiming * 8192, dont_ignore_monsters, m_pPlayer->edict(), &tr);
    
    if (tr.pHit)
    {
        CBaseEntity* pHit = CBaseEntity::Instance(tr.pHit);
        if (pHit)
        {
            pHit->TakeDamage(m_pPlayer->pev, m_pPlayer->pev, 60, DMG_ENERGYBEAM);
        }
    }
}

void CPlasmaRifle::PrimaryAttack()
{
    if (m_pPlayer->pev->waterlevel == 3)
    {
        PlayEmptySound();
        m_flNextPrimaryAttack = gpGlobals->time + 0.15;
        return;
    }
    
    if (m_iClip <= 0)
    {
        PlayEmptySound();
        m_flNextPrimaryAttack = gpGlobals->time + 0.15;
        return;
    }
    
    FirePlasmaShot();
}

void CPlasmaRifle::SecondaryAttack()
{
    if (m_pPlayer->pev->waterlevel == 3)
    {
        PlayEmptySound();
        m_flNextSecondaryAttack = gpGlobals->time + 1.0;
        return;
    }
    
    if (m_iClip <= 10)
    {
        PlayEmptySound();
        m_flNextSecondaryAttack = gpGlobals->time + 1.0;
        return;
    }
    
    // استهلاك 10 رصاصات للهجوم الثانوي
    m_iClip -= 10;
    FirePlasmaBlast();
}

void CPlasmaRifle::Reload()
{
    if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
        return;
    
    if (DefaultReload(50, PLASMA_RELOAD, 2.5))
    {
        EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/plasma_reload.wav", 1, ATTN_NORM, 0, PITCH_NORM);
    }
}

void CPlasmaRifle::WeaponIdle()
{
    ResetEmptySound();
    
    m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);
    
    if (m_flTimeWeaponIdle > gpGlobals->time)
        return;
    
    int iAnim;
    float flRand = RANDOM_FLOAT(0, 1);
    
    if (flRand <= 0.5)
    {
        iAnim = PLASMA_IDLE;
        m_flTimeWeaponIdle = gpGlobals->time + 3.0;
    }
    else
    {
        iAnim = PLASMA_IDLE;
        m_flTimeWeaponIdle = gpGlobals->time + 2.0;
    }
    
    SendWeaponAnim(iAnim);
}
