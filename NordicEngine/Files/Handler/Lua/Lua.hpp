#ifndef NordicArts_NordicEngine_Files_Lua_H
#define NordicArts_NordicEngine_Files_Lua_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Texture/Texture.hpp>
#include <NordicEngine/Model/Model.hpp>
#include <NordicEngine/Files/Files.hpp>

extern "C" {
    #include <NordicEngine/ThirdParty/lua/src/lua.h>
    #include <NordicEngine/ThirdParty/lua/src/lauxlib.h>
    #include <NordicEngine/ThirdParty/lua/src/lualib.h>    
};

#include <NordicEngine/ThirdParty/LuaBridge/Source/LuaBridge/LuaBridge.h>

namespace NordicArts {
    namespace NordicEngine {
        class Lua {
        // Variables
        public:
        protected:
        private:
            lua_State *m_pLua;

        // Methods
        public:
            Lua();
            Lua(const Lua &oOther);

            ~Lua();

            Lua &operator =(const Lua &);

            lua_State *getLua() const;

            void loadLuaFromFile(const std::string &cFile);
            void executeLuaScript(const std::string &cScript);
            
        protected:
        private:
            void reportErrors(int iState);

        };
    };
};

#endif
