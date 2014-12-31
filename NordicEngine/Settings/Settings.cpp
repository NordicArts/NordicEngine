#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Exceptions/Exceptions.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Settings::Settings() : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3) {
            printIt("Settings C 1");
        }
        Settings::Settings(Storage *pStorage) : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3) {
            printIt("Settings C2 1");
            m_pStorage = pStorage;
            printIt("Settings C2 2");
        }
        Settings::Settings(std::string cDB) : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3) {
            printIt("Settings C3 1");
            Storage        oStorage(cDB);
            printIt("Settings C3 2");
            m_pStorage  = &oStorage;
            printIt("Settings C3 3");
        }

        Settings::~Settings() {
            m_pStorage = nullptr;
        }

        void Settings::registerLua(Lua *pLua) {
            lua_State *pState = pLua->getLua();

            luabridge::getGlobalNamespace(pState)
                .beginNamespace("NordicArts")
                    .beginClass<Settings>("Settings")
                        .addConstructor<void(*)(std::string)>()
                        .addFunction("setSeed", &Settings::setRandomSeed)
                        .addFunction("getSeed", &Settings::getRandomSeed)
                        .addFunction("createSettings", &Settings::createTable)
                    .endClass()
                .endNamespace();
        }

        void Settings::setRandomSeed(int16_t iSeed) {
            m_iRandomNumberSeed = iSeed;
       
            if (m_pStorage) {
                printIt("Seed 1"); 
                m_pStorage->setTable("general_settings");
                printIt("Seed 2");
                m_pStorage->setValue("randomSeed", iSeed);
                printIt("Seed 3");
                m_pStorage->update();
                printIt("Seed 4");
            }
        }

        int16_t Settings::getRandomSeed() const {
            int iSeed;

            if (m_pStorage) {
                printIt("Tester 1");
                m_pStorage->select("SELECT randomSeed FROM general_settings");
                printIt("Tester 2");
                std::map<std::string, std::string> mResult = m_pStorage->getResult();
                printIt("Tester 3");
                for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                    printIt("Tester 4");
                    iSeed = atoi(it->second.c_str());
                    printIt("Tester 5");
                }
                printIt("Tester 6");
            }

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

            printIt("Create 13");
            m_pStorage->createTable();
            printIt("Create 14");
        }
    };
};
