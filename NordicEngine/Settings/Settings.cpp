#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Exception/Exception.hpp>
#include <NordicEngine/Storage/Storage.hpp>
#include <NordicEngine/Files/Format/Lua/Lua.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Settings::Settings() : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3), m_vResolution(800, 600), m_cGameName("NordicArts"), m_bSettingsDone(false), m_pLogger(nullptr) {
        }
        Settings::Settings(std::string cGameName) : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3), m_vResolution(800, 600), m_cGameName(cGameName), m_bSettingsDone(false), m_pLogger(nullptr) {
        }
        Settings::Settings(Logger *pLogger, std::string cGameName) : m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_iRandomNumberSeed(0), m_vOpenGL(3, 3), m_vResolution(800, 600), m_cGameName(cGameName), m_bSettingsDone(false), m_pLogger(pLogger) {
        }

        Settings::~Settings() {
        }

        void Settings::setup() {
            bool bCreated = createTable();
            if (bCreated) {
                setDefaults();
            }
        }

        void Settings::registerLua(Files::Lua *pLua) {
            lua_State *pState = pLua->getLua();

            luabridge::getGlobalNamespace(pState)
                .beginNamespace("NordicArts")
                    .beginClass<Settings>("Settings")
                        .addConstructor<void(*)()>()
                        
                        .addProperty("gameName", &Settings::getGameName, &Settings::setGameName)
                        .addProperty("seed", &Settings::getRandomSeed, &Settings::setRandomSeed)
                        .addProperty("fov", &Settings::getFOV, &Settings::setFOV)
                        .addProperty("fovCalc", &Settings::getFOVCalc)
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
                        
                        .addFunction("createSettings", &Settings::setup)
                    .endClass()
                .endNamespace();

            return;
        }

        void Settings::setGameName(std::string cGameName) {
            if (m_pLogger) {
                m_pLogger->log("Set Gamename: " + cGameName);
            }

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

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setValue("randomSeed", iSeed);
                oStorage.update();
            }

            return;
        }
        int Settings::getRandomSeed() const {
            int iSeed = m_iRandomNumberSeed;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setColumn("randomSeed");
                oStorage.select();
                std::map<std::string, std::string> mResult = oStorage.getResult();
                for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                    iSeed = atoi(it->second.c_str());
                }
            }

            return iSeed;
        }

        void Settings::setFOV(float fFOV) {
            m_fFOV = fFOV;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setValue("fov", fFOV);
                oStorage.update();
            }

            return;
        }
        float Settings::getFOV() const {
            float fFOV = m_fFOV;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setColumn("fov");
                oStorage.select();
                std::map<std::string, std::string> mResult = oStorage.getResult();
                for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                    fFOV = atof(it->second.c_str());
                }
            }

            return fFOV;
        }      
        float Settings::getFOVCalc() const {
            float fFOV = getFOV();
        
            if (fFOV >= 0.1) { fFOV *= 2; }

            return fFOV;
        }

        void Settings::setWindowMode(bool bWindowed) {
            m_bWindowMode = bWindowed;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setValue("windowMode", bWindowed);
                oStorage.update();
            }

            return;
        }
        bool Settings::isWindowed() const {
            bool bWindowed = m_bWindowMode;
            int iWindowed;

            if (m_bSettingsDone) {
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
            }

            return bWindowed;
        }

        void Settings::setFSAA(int iFSAA) {
            m_iFSAA = iFSAA;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setValue("fsaa", iFSAA);
                oStorage.update();
            }
        }
        int Settings::getFSAA() const {
            int iFSAA = m_iFSAA;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setColumn("fsaa");
                oStorage.select();
                std::map<std::string, std::string> mResult = oStorage.getResult();
                for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                    iFSAA = atoi(it->second.c_str());
                }
            }

            return iFSAA;
        }

        void Settings::setPhysicsRefresh(int iRefresh) {
            m_iPhysicsRefreshRate = iRefresh;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setValue("physics", iRefresh);
                oStorage.update();
            }
        }
        int Settings::getPhysicsRefresh() const {
            int iPhysics = m_iPhysicsRefreshRate;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setColumn("physics");
                oStorage.select();
                std::map<std::string, std::string> mResult = oStorage.getResult();
                for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                    iPhysics = atoi(it->second.c_str());
                }
            }

            return iPhysics;
        }

        void Settings::setVSync(bool bSync) {
            m_bVSync = bSync;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setValue("vsync", bSync);
                oStorage.update();
            }
        }
        bool Settings::getVSync() const {
            bool bVSync = m_bVSync;
            int iVSync;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setColumn("vSync");
                oStorage.select();
                std::map<std::string, std::string> mResult = oStorage.getResult();
                for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                    iVSync = atoi(it->second.c_str());
                }

                if (iVSync) { bVSync = true; }
            }

            return bVSync;
        }

        void Settings::setOpenGL(const glm::uvec2 &vOpenGL) {
            setOpenGLVerbose(vOpenGL.x, vOpenGL.y);
        }
        void Settings::setOpenGLVerbose(int iMajor, int iMinor) {
            m_vOpenGL.x = iMajor;
            m_vOpenGL.y = iMinor;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setValue("opengl_major", iMajor);
                oStorage.setValue("opengl_minor", iMinor);
                oStorage.update();
            }
        }
        int Settings::getOpenGLMajor() const {
            int iMajor = m_vOpenGL.x;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setColumn("opengl_major");
                oStorage.select();
                std::map<std::string, std::string> mResult = oStorage.getResult();
                for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                    iMajor = atoi(it->second.c_str());
                }
            }
        
            return iMajor;
        }
        int Settings::getOpenGLMinor() const {
            int iMinor = m_vOpenGL.y;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setColumn("opengl_minor");
                oStorage.select();
                std::map<std::string, std::string> mResult = oStorage.getResult();
                for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                    iMinor = atoi(it->second.c_str());
                }
            }

            return iMinor;
        }
        const glm::uvec2 Settings::getOpenGL() const {            
            return m_vOpenGL;
        }

        void Settings::setResolution(const glm::uvec2 &vResolution) {
            setResolutionVerbose(vResolution.x, vResolution.y);
        }
        void Settings::setResolutionVerbose(int iWidth, int iHeight) {
            m_vResolution.x = iWidth;
            m_vResolution.y = iHeight;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setValue("resolution_width", iWidth);
                oStorage.setValue("resolution_height", iHeight);
                oStorage.update();
            }
        }
        int Settings::getResolutionWidth() const {
            int iWidth = m_vResolution.x;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setColumn("resolution_width");
                oStorage.select();
                std::map<std::string, std::string> mResult = oStorage.getResult();
                for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                    iWidth = atoi(it->second.c_str());
                }
            }
            
            return iWidth;
        }
        int Settings::getResolutionHeight() const {
            int iHeight = m_vResolution.y;

            if (m_bSettingsDone) {
                Storage oStorage(m_cGameName);
                oStorage.setTable("general_settings");
                oStorage.setColumn("resolution_height");
                oStorage.select();
                std::map<std::string, std::string> mResult = oStorage.getResult();
                for (std::map<std::string, std::string>::iterator it = mResult.begin(); it != mResult.end(); it++) {
                    iHeight = atoi(it->second.c_str());
                }
            }
        
            return iHeight;
        }
        const glm::uvec2 Settings::getResolution() const {
            return m_vResolution;
        }

        bool Settings::checkDefaults() {
            std::string cGameName;
            bool bReturn = false;

            if (m_pLogger) { m_pLogger->log("Checking Defaults"); }

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

            if (m_pLogger) { m_pLogger->log("Checked Defaults"); }

            return bReturn;
        }   

        bool Settings::checkTableExists() {
            bool bReturn = false;
        
            if (m_pLogger) { m_pLogger->log("Checking Table Exists"); }
            
            Storage oStorage(m_cGameName);
            oStorage.setTable("general_settings");
            bReturn = oStorage.checkTable();
            
            if (m_pLogger) { m_pLogger->log("Checked Table Exists"); }

            return bReturn;
        }
         
        void Settings::setDefaults() {
            m_bSettingsDone = checkDefaults();

            if (!m_bSettingsDone) {
                if (m_pLogger) { m_pLogger->log("Setting Defaults"); }

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

                if (m_pLogger) { m_pLogger->log("Set Defaults"); }
            }

            return;
        }

        bool Settings::createTable() {
            if (checkTableExists()) { return true; }

            if (m_pLogger) { m_pLogger->log("Creating Settings Table"); } 

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
                
            if (oStorage.createTable()) { return true; }

            if (m_pLogger) { m_pLogger->log("Created Settings Table"); }

            return false;
        }
    };
};
