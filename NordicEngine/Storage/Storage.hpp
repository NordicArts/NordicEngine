#ifndef NordicArts_NordicEngine_Storage_H
#define NordicArts_NordicEngine_Storage_H

// SQLite
extern "C" {
    #include <NordicEngine/ThirdParty/sqlite/sqlite3.h>
}

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Logger/Logger.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class Storage {
        // Variables
        public:
        protected:
        private:
            sqlite3 *m_pDB;

            Logger *m_pLogger;
            
            std::string m_cTable;

            std::vector<std::string> m_vColumns;

            // Values
            std::vector<std::string> m_vNullValues;
            std::map<std::string, std::string> m_mValues;

            // Wheres
            std::vector<std::string> m_vNullWheres;
            std::map<std::string, std::string> m_mWheres;

        // Methods
        public:
            Storage();
            Storage(std::string cDB);
            Storage(Logger *pLogger, std::string cDB);

            ~Storage();
    
            // set the table todo actions on
            void setTable(std::string cTable);

            // Table columns
            void addPrimary(std::string cName);
            void addInt(std::string cName);
            void addInt(std::string cName, int iLength);
            void addInt(std::string cName, int iLength, bool bNullable);
            void addInt(std::string cName, int iLength, bool bNullable, bool bIndex);
            void addInt(std::string cName, int iLength, bool bNullable, bool bIndex, bool bPrimary);

            void addChar(std::string cName);
            void addChar(std::string cName, int iLength);
            void addChar(std::string cName, bool bNullable);
            void addChar(std::string cName, int iLength, bool bNullable);

            void addText(std::string cName);
            void addText(std::string cName, bool bNullable);

            void addReal(std::string cName);
            void addReal(std::string cName, bool bNullable);
            
            void addBlob(std::string cName);
            void addBlob(std::string cName, bool bNullable);

            void addBool(std::string cName);
            void addBool(std::string cName, bool bNullable);
            void addBool(std::string cName, bool bNullable, bool bIndex);

            void addDate(std::string cName);
            void addDate(std::string cName, bool bNullable);

            // Create table
            void createTable();
            void createTable(std::string cSQL);

            // Add index to table
            void addIndex();
            void addIndex(std::string cColumn);
            void addIndex(std::string cName, std::vector<std::string> vColumns);
            void addIndex(std::string cName, std::string cColumn);
            void addIndex(std::string cName, std::string cColumn, std::string cTable);

            // Executbe abitrary SQL
            void execute(std::string cSQL);

            // Set Column for select
            void setColumn(std::string cColumn);

            // Set values for insert/update
            void setValue(std::string cColumn);
            void setValue(std::string cColumn, int iValue);
            void setValue(std::string cColumn, float fValue);   
            void setValue(std::string cColumn, bool bValue);
            void setValue(std::string cColumn, std::string cValue);

            // Set where clauses
            void setWhere(std::string cColumn);
            void setWhere(std::string cColumn, int iValue);
            void setWhere(std::string cColumn, float fValue);
            void setWhere(std::string cColumn, bool bValue);
            void setWhere(std::string cColumn, std::string cValue);

            // Update
            void update();
            void update(std::string cSQL);

            // Insert
            void insert();
            void insert(std::string cSQL);

            // Delete
            void del();
            void del(std::string cSQL);

            // Select
            void select();
            void select(std::string cSQL);
            
            // Results
            static int setResult(void *pData, int iArgc, char **cArgv, char **cColumn);
            std::map<std::string, std::string> getResult();
            
        protected:
        private:
            void connectDB(std::string cDB);

        };
    };
};


#endif
