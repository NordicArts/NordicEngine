#include <NordicEngine/Files/Format/Lua/Lua.hpp>
#include <NordicEngine/String/String.hpp>
#include <NordicEngine/Logger/Logger.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            Lua::Lua() : m_pLogger(nullptr) {
                m_pLua = luaL_newstate();

                luaL_openlibs(m_pLua);
            }
            Lua::Lua(Logger *pLogger) : m_pLogger(pLogger) {
                m_pLua = luaL_newstate();
                
                luaL_openlibs(m_pLua);
            }

            Lua::~Lua() {
                lua_close(m_pLua);
            }

            lua_State *Lua::getLua() const {
                return m_pLua;
            }

            void Lua::loadLuaFromFile(const std::string &cFileName) {
                int iState = luaL_dofile(m_pLua, cFileName.c_str());
    
                return reportErrors(iState);
            }

            void Lua::loadLuaFromScript(const std::string &cScript) {
                int iState = luaL_dostring(m_pLua, cScript.c_str());
            
                return reportErrors(iState);
            }

            void Lua::reportErrors(int iState) {
                if (iState != 0) {
                    const char *cError = lua_tostring(m_pLua, iState);

                    lua_pop(m_pLua, 1);

                    std::string cEndError = cError;
                    cEndError += ": ";
                    cEndError += getString(iState);
            
                    if (m_pLogger) { 
                        m_pLogger->log(cEndError); 
                    } else {
                        printIt(cEndError);
                    }
                }
            }
        };
    };
};
