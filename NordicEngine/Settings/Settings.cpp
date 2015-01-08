#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Exceptions/Exceptions.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Settings::Settings() : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3) {
        }
        Settings::Settings(Storage *pStorage) : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3) {
            m_pStorage = pStorage;
        }
        Settings::Settings(std::string cDB) : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3) {
            Storage        oStorage(cDB);
            m_pStorage  = &oStorage;
        }

        Settings::~Settings() {
            m_pStorage = nullptr;
        }

        void Settings::registerLua(Lua *pLua) {
            lua_State *pState = pLua->getLua();

            luabridge::getGlobalNamespace(pState)
                .beginNamespace("NordicArts")
                    .beginClass<Settings>("Settings")
                        .addConstructor<void(*)()>()
                        .addProperty("gameName", &Settings::getGameName, &Settings::setGameName)
                        .addFunction("setGame", &Settings::setGameName)
                        .addFunction("getSeed", &Settings::getRandomSeed)
                        .addFunction("setSeed", &Settings::setRandomSeed)
                        .addFunction("createSettings", &Settings::createTable)
                    .endClass()
                .endNamespace();

            return;
        }

        void Settings::setGameName(std::string cGameName) {
            m_cGameName = cGameName;
    
            if (m_pStorage) {
                m_pStorage->setDB(cGameName);
            }

            return;
        }
        std::string Settings::getGameName() const {
            return m_cGameName;
        }

        void Settings::setRandomSeed(int16_t iSeed) {
            m_iRandomNumberSeed = iSeed;

            printIt("Set Seed 1");

            if (m_pStorage) {     
                printIt("Set Seed 2");
                printIt(m_pStorage->getDB());

                printIt("Set Seed 3");
                m_pStorage->setTable("general_settings");
                printIt("Set Seed 4");

                printIt("Set Seed 5");
                m_pStorage->setValue("randomSeed", iSeed);
                printIt("Set Seed 6");
            
                printIt("Set Seed 7");
                m_pStorage->update();
                printIt("Set Seed 8");
            }
    
            printIt("Set Seed 9");

            return;
        }

        int16_t Settings::getRandomSeed() const {
            int iSeed;

            printIt("Get Seed 1");

            if (m_pStorage) {
                printIt("Get Seed 2");
                m_pStorage->select("SELECT randomSeed FROM general_settings");
                printIt("Get Seed 3");

                printIt("Get Seed 4");
                std::map<std::string, std::string> mResult = m_pStorage->getResult();
                for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                    iSeed = atoi(it->second.c_str());
                }
                printIt("Get Seed 5");
            }

            printIt("Get Seed 6");
            return m_iRandomNumberSeed;
        }

        void Settings::createTable() {
            if (m_pStorage) {
                m_pStorage->setTable("general_settings");
               
                m_pStorage->addBool("windowMode");
                m_pStorage->addBool("vsync");
                m_pStorage->addReal("fov");
                m_pStorage->addInt("opengl_major");
                m_pStorage->addInt("opengl_minor");
                m_pStorage->addInt("resolution_x");
                m_pStorage->addInt("resolution_y");
                m_pStorage->addInt("fsaa");
                m_pStorage->addInt("physics");
                m_pStorage->addInt("randomSeed");

                printIt("Create Table 7");
                m_pStorage->createTable();
                printIt("Create Table 8"); 
            }

            return;
        }
    };
};
