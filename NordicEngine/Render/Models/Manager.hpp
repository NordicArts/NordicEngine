#ifndef NordicArts_NordicEngine_Render_Model_Manager_H
#define NordicArts_NordicEngine_Render_Model_Manager_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Render/Models/Model.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Models {
                class Manager {
                // Variables
                public:
                    std::map<std::string, Model> m_mModels;
        
                protected:
                private:

                // Methods
                public:
                    Manager();

                    ~Manager();

                    void destroy();

                    Model addModel(std::string cName, std::string cFile, std::string cVertex, std::string cFragment);
                    Model getModel(std::string cName);

                protected:
                private:

                };
            };
        };
    };
};

#endif
