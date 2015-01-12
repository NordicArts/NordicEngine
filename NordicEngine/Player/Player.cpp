#include <NordicEngine/Player/Player.hpp>
#include <NordicEngine/String/String.hpp>
#include <NordicEngine/Storage/Storage.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Player::Player() : m_cGameName("NordicArts"), m_cName("Geoff"), m_bSetupDone(false) {
        }
        Player::Player(std::string cGameName) : m_cGameName(cGameName), m_cName("Geoff"), m_bSetupDone(false) {
        }
        Player::Player(int iLife) : m_iLife(iLife) {
        }

        void Player::setup() {
            Storage oStorage(m_cGameName);
            
            oStorage.setTable("general_player");
            oStorage.addPrimary("playerId");
            oStorage.addText("playerName");
            oStorage.addInt("life");
            oStorage.createTable();
        }
        void Player::setupGame(std::string cGameName) {
            m_cGameName = cGameName;
            setup();

            m_bSetupDone = true;
        }

        void Player::setName(std::string cName) {
            m_cName = cName;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_player");
            oStorage.setValue("playerName", cName);
            oStorage.setWhere("playerId", m_iId);
            oStorage.update();
        }
        std::string Player::getName() const {
            std::string cName;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_player");
            oStorage.setColumn("playerName");
            oStorage.setWhere("playerId", m_iId);
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                cName = it->second;
            }

            return cName;
        }

        void Player::setPlayerId(int iId) {
            m_iId = iId;
        }
        int Player::getPlayerId() const {
            int iId;
        
            Storage oStorage(m_cGameName);
            oStorage.setTable("general_player");
            oStorage.setColumn("playerId");
            oStorage.setWhere("playerName", m_cName);
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iId = atoi(it->second.c_str());
            }

            return iId;
        }

        void Player::addPlayer() {
            Storage oStorage(m_cGameName);
            oStorage.setTable("general_player");
            oStorage.setValue("playerName", m_cName);
            oStorage.setValue("life", m_iLife);
            oStorage.insert();

            int iPlayerId = getPlayerId();
            setPlayerId(iPlayerId);
        }

        void Player::setLife(int iLife) {
            m_iLife = iLife;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_player");
            oStorage.setValue("life", iLife);
            oStorage.setWhere("playerId", m_iId);
            oStorage.update();
        }
        int Player::getLife() const {
            int iLife;
        
            Storage oStorage(m_cGameName);
            oStorage.setTable("general_player");
            oStorage.setColumn("life");
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iLife = atoi(it->second.c_str());
            }

            return iLife;
        }

        int Player::incrementLife() {
            return incrementLifeAmount(1);
        }
        int Player::incrementLifeAmount(int iLife) {
            m_iLife += iLife;

            setLife(m_iLife);
        
            return m_iLife;
        }

        int Player::decrementLife() {
            return decrementLifeAmount(1);
        }
        int Player::decrementLifeAmount(int iLife) {
            m_iLife -= iLife;

            setLife(m_iLife);

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

                        .addFunction("setup", &Player::setupGame)
                        .addFunction("getDetails", &Player::getDetails)
                        .addFunction("decrementLife", &Player::decrementLife)
                        .addFunction("decrementLifeAmount", &Player::decrementLifeAmount)
                        .addFunction("incrementLife", &Player::incrementLife)
                        .addFunction("incrementLifeAmount", &Player::incrementLifeAmount)
                        .addFunction("addPlayer", &Player::addPlayer)
                       
                        .addProperty("name", &Player::getName, &Player::setName) 
                        .addProperty("life", &Player::getLife, &Player::setLife)
                        .addProperty("id", &Player::getPlayerId, &Player::setPlayerId)
                        .addProperty("alive", &Player::isAlive)
                    .endClass()
                .endNamespace();
        }
    };
};
