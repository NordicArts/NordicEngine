#ifndef NordicArts_NordicEngine_Files_Format_Lua_H
#define NordicArts_NordicEngine_Files_Format_Lua_H

#include <NordicEngine/Engine.hpp>

#include <NordicEngine/ThirdParty/lua/lua/include/lua.hpp>
#include <NordicEngine/ThirdParty/LuaBridge/Source/LuaBridge/LuaBridge.h>

namespace NordicArts {
    namespace NordicEngine {
        class Logger;

        namespace Files {
            class Lua {
            // Variables
            public:
            protected:
            private:
                lua_State *m_pLua;

                Logger    *m_pLogger;

            // Methods
            public:
                Lua();
                Lua(Logger *pLogger);
                Lua(const Lua &oOther);

                ~Lua();

                lua_State *getLua() const;

                void loadLuaFromFile(const std::string &cFileName);
                void loadLuaFromScript(const std::string &cScript);

                Lua &operator =(const Lua &);

            protected:
            private:
                void reportErrors(int iState);

            };
        };
    };
};

#endif
