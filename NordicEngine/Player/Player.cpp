#include <NordicEngine/Player/Player.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Player::Player() {
        }
        Player::Player(int iLife) : m_iLife(iLife) {
        }

        void Player::setName(std::string cName) {
            m_cName = cName;
        }
        std::string Player::getName() const {
            return m_cName;
        }

        void Player::setLife(int iLife) {
            m_iLife = iLife;
        }
        int Player::getLife() const {
            return m_iLife;
        }

        int Player::incrementLife() {
            return incrementLifeAmount(1);
        }
        int Player::incrementLifeAmount(int iLife) {
            m_iLife += iLife;
        
            return m_iLife;
        }

        int Player::decrementLife() {
            return decrementLifeAmount(1);
        }
        int Player::decrementLifeAmount(int iLife) {
            m_iLife -= iLife;

            return m_iLife;
        }

        bool Player::alive() const {
            return isAlive();
        }
        bool Player::isAlive() const {
            if (m_iLife >= 1) {
                return true;
            }

            return false;
        }

        std::string Player::getDetails() const {
            std::string cReturn;

            cReturn += ("Name: " + getName());
            cReturn += (", Life: " + getString(getLife()));
            cReturn += (", Alive: " + getString(isAlive()));

            return cReturn;
        }

        void Player::registerLua(Lua *pLua) {
            lua_State *pState = pLua->getLua();
            
            luabridge::getGlobalNamespace(pState)
                .beginNamespace("NordicArts")
                    .beginClass<Player>("Player")
                        .addConstructor<void (*)(void)>()
                        .addFunction("setName", &Player::setName)
                        .addFunction("setLife", &Player::setLife)
                        .addFunction("getDetails", &Player::getDetails)
                        .addFunction("decrementLife", &Player::decrementLife)
                        .addFunction("decrementLifeAmount", &Player::decrementLifeAmount)
                        .addFunction("incrementLife", &Player::incrementLife)
                        .addFunction("incrementLifeAmount", &Player::incrementLifeAmount)
                        .addFunction("isAlive", &Player::isAlive)
                    .endClass()
                .endNamespace();
        }
    };
};
