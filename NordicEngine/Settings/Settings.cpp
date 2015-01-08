#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Exceptions/Exceptions.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Settings::Settings() : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3), m_cGameName("NordicArts") {
        }
        Settings::Settings(std::string cGameName) : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3), m_cGameName(cGameName) {
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

            return;
        }
        std::string Settings::getGameName() const {
            return m_cGameName;
        }

        void Settings::setRandomSeed(int16_t iSeed) {
            m_iRandomNumberSeed = iSeed;

            Storage  oStorage(m_cGameName);
            Storage *pStorage = &oStorage;

            pStorage->setTable("general_settings");
           
            pStorage->setValue("randomSeed", iSeed);
            
            pStorage->update();

            return;
        }

        int16_t Settings::getRandomSeed() const {
            int iSeed;

            Storage  oStorage(m_cGameName);
            Storage *pStorage = &oStorage;

            pStorage->select("SELECT randomSeed FROM general_settings");
            std::map<std::string, std::string> mResult = pStorage->getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iSeed = atoi(it->second.c_str());
            }

            return m_iRandomNumberSeed;
        }

        void Settings::setDefaults() {
            Storage  oStorage(m_cGameName);
            Storage *pStorage = &oStorage;

            pStorage->setTable("general_settings");
        
            pStorage->setValue("windowMode", m_bWindowMode);
            pStorage->setValue("vsync", true);
            pStorage->setValue("fov", 45);
            pStorage->setValue("opengl_major", (int)m_vOpenGL.x);
            pStorage->setValue("opengl_minor", (int)m_vOpenGL.y);
            pStorage->setValue("resolution_x", 800);
            pStorage->setValue("resolution_y", 600);
            pStorage->setValue("fsaa", 0);
            pStorage->setValue("physics", (int)m_iPhysicsRefreshRate);
            pStorage->setValue("randomSeed", 2015);

            pStorage->insert();

            return;
        }

        void Settings::createTable() {
            Storage  oStorage(m_cGameName);
            Storage *pStorage = &oStorage;

            pStorage->setTable("general_settings");

            pStorage->addBool("windowMode");
            pStorage->addBool("vsync");
            pStorage->addReal("fov");
            pStorage->addInt("opengl_major");
            pStorage->addInt("opengl_minor");
            pStorage->addInt("resolution_x");
            pStorage->addInt("resolution_y");
            pStorage->addInt("fsaa");
            pStorage->addInt("physics");
            pStorage->addInt("randomSeed");
                
            pStorage->createTable();

            setDefaults();

            return;
        }
    };
};
