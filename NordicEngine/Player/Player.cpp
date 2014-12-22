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
            return incrementLife(1);
        }
        int Player::incrementLife(int iLife) {
            m_iLife += iLife;
        
            return m_iLife;
        }

        int Player::decrementLife() {
            return decrementLife(1);
        }
        int Player::decrementLife(int iLife) {
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
            std::string cReturn = "";
            
            cReturn += getName();
            cReturn += ": ";
            cReturn += getString(getLife());

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
                    .endClass()
                .endNamespace();
        }
    };
};
