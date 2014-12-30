#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Exceptions/Exceptions.hpp>

namespace NordicArts {
    namespace NordicEngine {
        static Settings *g_pSettings = nullptr;

        Settings* const Settings::get() {
            if (g_pSettings == nullptr) {
                char cError[1024];
                std::sprintf(cError, "%s Failed to use Settings", __FUNCTION__);

                throw Exceptions(cError);
            }

            return g_pSettings;
        }

        Settings::Settings() : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3) {
            g_pSettings = this;

            // Storage
            Storage oStorage;
            m_pStorage = &oStorage;

            // Create table
            createTable();
            
        }
        Settings::Settings(Storage *pStorage) : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3) {
            g_pSettings = this;

            m_pStorage = pStorage;

            createTable();
        }
        Settings::Settings(std::string cDB) : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3) {
            g_pSettings = this;

            Storage        oStorage(cDB);
            m_pStorage  = &oStorage;

            createTable();
        }

        Settings::~Settings() {
            g_pSettings = nullptr;
        }

        void Settings::registerLua(Lua *pLua) {
            lua_State *pState = pLua->getLua();
    

            luabridge::getGlobalNamespace(pState)
                .beginNamespace("NordicArts")
                    .beginClass<Settings>("Settings")
                        .addConstructor<void(*)(void)>()
                        .addFunction("setSeed", &Settings::setRandomSeed)
                        .addFunction("getSeed", &Settings::getRandomSeed)
                    .endClass()
                .endNamespace();
        }

        void Settings::setRandomSeed(int16_t iSeed) {
            m_iRandomNumberSeed = iSeed;
        
            m_pStorage->setTable("general_settings");
            m_pStorage->setValue("randomSeed", iSeed);
            m_pStorage->update();
        }

        int16_t Settings::getRandomSeed() const {
            int iSeed;
            m_pStorage->select("SELECT randomSeed FROM general_settings");
            std::map<std::string, std::string> mResult = m_pStorage->getResult();
            printIt(mResult["randomSeed"]);

            return m_iRandomNumberSeed;
        }

        void Settings::createTable() {
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

            m_pStorage->createTable();
        }
    };
};
