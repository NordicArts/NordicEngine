#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Exceptions/Exceptions.hpp>
#include <NordicEngine/Storage/Storage.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Settings::Settings() : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3), m_cGameName("NordicArts"), m_bSettingsDone(false) {
        }
        Settings::Settings(std::string cGameName) : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3), m_cGameName(cGameName), m_bSettingsDone(false) {
        }

        Settings::~Settings() {
        }

        void Settings::registerLua(Lua *pLua) {
            lua_State *pState = pLua->getLua();

            luabridge::getGlobalNamespace(pState)
                .beginNamespace("NordicArts")
                    .beginClass<Settings>("Settings")
                        .addConstructor<void(*)()>()
                        
                        .addProperty("gameName", &Settings::getGameName, &Settings::setGameName)
                        .addProperty("seed", &Settings::getRandomSeed, &Settings::setRandomSeed)
                        .addProperty("fov", &Settings::getFOV, &Settings::setFOV)
                        .addProperty("windowMode", &Settings::isWindowed, &Settings::setWindowMode)
                        .addProperty("fsaa", &Settings::getFSAA, &Settings::setFSAA)
                        .addProperty("physicsSpeed", &Settings::getPhysicsRefresh, &Settings::setPhysicsRefresh)
                        .addProperty("vsync", &Settings::getVSync, &Settings::setVSync)
                        
                        .addProperty("getOpenGLMajor", &Settings::getOpenGLMajor)
                        .addProperty("getOpenGLMinor", &Settings::getOpenGLMinor)
                        .addFunction("setOpenGL", &Settings::setOpenGLVerbose)

                        .addProperty("getResolutionWidth", &Settings::getResolutionWidth)
                        .addProperty("getResolutionHeight", &Settings::getResolutionHeight)
                        .addFunction("setResolution", &Settings::setResolutionVerbose)
                        
                        .addFunction("createSettings", &Settings::createTable)
                    .endClass()
                .endNamespace();

            return;
        }

        void Settings::setGameName(std::string cGameName) {
            m_cGameName = cGameName;

            if (m_bSettingsDone) {
                Storage oStorage(cGameName);
                oStorage.setTable("general_settings");
                oStorage.setValue("gameName", cGameName);
                oStorage.update();
            }

            return;
        }
        std::string Settings::getGameName() const {
            return m_cGameName;
        }

        void Settings::setRandomSeed(int iSeed) {
            m_iRandomNumberSeed = iSeed;
    
            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setValue("randomSeed", iSeed);
            oStorage.update();

            return;
        }
        int Settings::getRandomSeed() const {
            int iSeed;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setColumn("randomSeed");
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iSeed = atoi(it->second.c_str());
            }

            return iSeed;
        }

        void Settings::setFOV(float fFOV) {
            m_fFOV = fFOV;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setValue("fov", fFOV);
            oStorage.update();

            return;
        }
        float Settings::getFOV() const {
            float fFOV;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setColumn("fov");
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                fFOV = atof(it->second.c_str());
            }

            return fFOV;
        }       

        void Settings::setWindowMode(bool bWindowed) {
            m_bWindowMode = bWindowed;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setValue("windowMode", bWindowed);
            oStorage.update();

            return;
        }
        bool Settings::isWindowed() const {
            bool bWindowed = false;
            int iWindowed;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setColumn("windowMode");
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iWindowed = atoi(it->second.c_str());
            }
            
            // Turn it into windowed mode
            if (iWindowed) { bWindowed = true; }

            return bWindowed;
        }

        void Settings::setFSAA(int iFSAA) {
            m_iFSAA = iFSAA;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setValue("fsaa", iFSAA);
            oStorage.update();
        }
        int Settings::getFSAA() const {
            int iFSAA;
    
            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setColumn("fsaa");
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iFSAA = atoi(it->second.c_str());
            }

            return iFSAA;
        }

        void Settings::setPhysicsRefresh(int iRefresh) {
            m_iPhysicsRefreshRate = iRefresh;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setValue("physics", iRefresh);
            oStorage.update();
        }
        int Settings::getPhysicsRefresh() const {
            int iPhysics;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setColumn("physics");
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iPhysics = atoi(it->second.c_str());
            }

            return iPhysics;
        }

        void Settings::setVSync(bool bSync) {
            m_bVSync = bSync;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setValue("vsync", bSync);
            oStorage.update();
        }
        bool Settings::getVSync() const {
            bool bVSync = false;
            int iVSync;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setColumn("vSync");
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iVSync = atoi(it->second.c_str());
            }

            if (iVSync) { bVSync = true; }

            return bVSync;
        }

        void Settings::setOpenGL(const glm::uvec2 &vOpenGL) {
            setOpenGLVerbose(vOpenGL.x, vOpenGL.y);
        }
        void Settings::setOpenGLVerbose(int iMajor, int iMinor) {
            m_vOpenGL.x = iMajor;
            m_vOpenGL.y = iMinor;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setValue("opengl_major", iMajor);
            oStorage.setValue("opengl_minor", iMinor);
            oStorage.update();
        }
        int Settings::getOpenGLMajor() const {
            int iMajor;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setColumn("opengl_major");
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iMajor = atoi(it->second.c_str());
            }
        
            return iMajor;
        }
        int Settings::getOpenGLMinor() const {
            int iMinor;
            
            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setColumn("opengl_minor");
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iMinor = atoi(it->second.c_str());
            }

            return iMinor;
        }

        void Settings::setResolution(const glm::uvec2 &vResolution) {
            setResolutionVerbose(vResolution.x, vResolution.y);
        }
        void Settings::setResolutionVerbose(int iWidth, int iHeight) {
            m_vResolution.x = iWidth;
            m_vResolution.y = iHeight;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setValue("resolution_width", iWidth);
            oStorage.setValue("resolution_height", iHeight);
            oStorage.update();
        }
        int Settings::getResolutionWidth() const {
            int iWidth;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setColumn("resolution_width");
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iWidth = atoi(it->second.c_str());
            }
            
            return iWidth;
        }
        int Settings::getResolutionHeight() const {
            int iHeight;
            
            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setColumn("resolution_height");
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                iHeight = atoi(it->second.c_str());
            }
        
            return iHeight;
        }

        bool Settings::checkDefaults() {
            std::string cGameName;
            bool bReturn = false;

            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            oStorage.setColumn("gameName");
            oStorage.setWhere("gameName", m_cGameName);
            oStorage.select();
            std::map<std::string, std::string> mResult = oStorage.getResult();
            for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                cGameName = it->second;
            }

            if (cGameName != "") { bReturn = true; }

            return bReturn;
        }            
        void Settings::setDefaults() {
            m_bSettingsDone = checkDefaults();

            if (!m_bSettingsDone) {
                Storage  oStorage(m_cGameName);
    
                oStorage.setTable("general_settings");
        
                oStorage.setValue("gameName", m_cGameName);
                oStorage.setValue("windowMode", m_bWindowMode);
                oStorage.setValue("vsync", true);
                oStorage.setValue("fov", 45);
                oStorage.setValue("opengl_major", (int)m_vOpenGL.x);
                oStorage.setValue("opengl_minor", (int)m_vOpenGL.y);
                oStorage.setValue("resolution_width", 800);
                oStorage.setValue("resolution_height", 600);
                oStorage.setValue("fsaa", 0);
                oStorage.setValue("physics", (int)m_iPhysicsRefreshRate);
                oStorage.setValue("randomSeed", 2015);

                oStorage.insert();
    
                m_bSettingsDone = true;
            }

            return;
        }

        void Settings::createTable() {
            Storage  oStorage(m_cGameName);

            oStorage.setTable("general_settings");

            oStorage.addText("gameName");
            oStorage.addBool("windowMode");
            oStorage.addBool("vsync");
            oStorage.addReal("fov");
            oStorage.addInt("opengl_major");
            oStorage.addInt("opengl_minor");
            oStorage.addInt("resolution_width");
            oStorage.addInt("resolution_height");
            oStorage.addInt("fsaa");
            oStorage.addInt("physics");
            oStorage.addInt("randomSeed");
                
            oStorage.createTable();

            setDefaults();

            return;
        }
    };
};
