#include "ObjectManager.h"
#include "Player.h"
ObjectManager* ObjectManager::m_pInst = nullptr;
ObjectManager::ObjectManager()
    : m_pPlayer(nullptr)
{
}

ObjectManager::~ObjectManager()
{
    SAFE_DELETE(m_pPlayer);
}

bool ObjectManager::Init()
{
    m_pPlayer = new Player;
    return true;
}

void ObjectManager::Update()
{
    m_pPlayer->Update();
}
