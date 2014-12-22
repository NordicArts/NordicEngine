#include <NordicEngine/Files/Handler/Lua/Lua.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Lua::Lua() : m_pLua(luaL_newstate()) {
            luaL_openlibs(m_pLua);
        }

        Lua::~Lua() {
            lua_close(m_pLua);
        }           

        lua_State *Lua::getLua() const {
            return m_pLua;
        }

        void Lua::reportErrors(int iState) {
            if (iState != 0) {
                const char *cError = lua_tostring(m_pLua, iState);
                lua_pop(m_pLua, 1);

                printIt(cError);

                throw Exceptions(cError);
            }
        }

        void Lua::loadLuaFromFile(const std::string &cFile) {
            int iState = luaL_dofile(m_pLua, cFile.c_str());
            reportErrors(iState);
        }

        void Lua::executeLuaScript(const std::string &cScript) {
            int iState = luaL_dostring(m_pLua, cScript.c_str());
            reportErrors(iState);
        }
    };
};
