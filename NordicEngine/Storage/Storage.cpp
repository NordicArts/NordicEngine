#include <NordicEngine/Storage/Storage.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        std::map<std::string, std::string> gResult;

        Storage::Storage() : m_pDB(nullptr), m_pLogger(nullptr) {
        }

        Storage::Storage(std::string cDB) : m_pDB(nullptr), m_pLogger(nullptr) {
            connectDB(cDB);
        } 

        Storage::Storage(Logger *pLogger, std::string cDB) : m_pDB(nullptr), m_pLogger(pLogger) {
            connectDB(cDB);
        }

        Storage::~Storage() {
            if (m_pDB) {
                sqlite3_close(m_pDB);
            }

            m_pDB       = nullptr;
            m_pLogger   = nullptr;
        }

        void Storage::connectDB(std::string cDB) {
            int iConnection = sqlite3_open(cDB.c_str(), &m_pDB);
            if (iConnection) {
                throw ExceptionHandler(sqlite3_errmsg(m_pDB), true);
            }
        }

        void Storage::setTable(std::string cTable) {
            m_cTable = cTable;
        }

        // INT columns
        void Storage::addPrimary(std::string cName) {
            return addInt(cName, 8, false, false, true);
        }
        void Storage::addInt(std::string cName) {
            return addInt(cName, 8, false, false, false);
        }
        void Storage::addInt(std::string cName, int iLength) {
            return addInt(cName, iLength, false, false, false);
        }
        void Storage::addInt(std::string cName, int iLength, bool bNullable) {
            return addInt(cName, iLength, bNullable, false, false);
        }
        void Storage::addInt(std::string cName, int iLength, bool bNullable, bool bIndex) {
            return addInt(cName, iLength, bNullable, bIndex, false);
        }
        void Storage::addInt(std::string cName, int iLength, bool bNullable, bool bIndex, bool bPrimary) {
            std::string cColumn;
            
            if (bIndex) {
                cColumn = (cName + " INTEGER(" + getString(iLength) + ") INDEX NOT NULL");
            } else {
                if (bPrimary) {
                    cColumn = (cName + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL");
                } else {
                    if (bNullable) {
                        cColumn = (cName + " INTEGER(" + getString(iLength) + ") NULL");
                    } else {
                        cColumn = (cName + " INTEGER(" + getString(iLength) + ") NOT NULL");
                    }
                }
            }

            if (cColumn.size() >= 1) {
                m_vColumns.insert(m_vColumns.end(), cColumn);
            }
        }

        // CHAR columns
        void Storage::addChar(std::string cName) {
            return addChar(cName, 100, false);
        }
        void Storage::addChar(std::string cName, bool bNullable) {
            return addChar(cName, 100, bNullable);
        }
        void Storage::addChar(std::string cName, int iLength) {
            return addChar(cName, iLength, false);
        }
        void Storage::addChar(std::string cName, int iLength, bool bNullable) {
            std::string cColumn;
            if (bNullable) {
                cColumn = (cName + " CHAR(" + getString(iLength) + ") NULL");
            } else {
                cColumn = (cName + " CHAR(" + getString(iLength) + ") NOT NULL");
            }

            if (cColumn.size() >= 1) {
                m_vColumns.insert(m_vColumns.end(), cColumn);
            }
        }

        // TEXT columns
        void Storage::addText(std::string cName) {
            return addText(cName, false);
        }
        void Storage::addText(std::string cName, bool bNullable) {
            std::string cColumn;
            
            if (bNullable) {
                cColumn = (cName + " TEXT NULL");
            } else {
                cColumn = (cName + " TEXT NOT NULL");
            }
        
            if (cColumn.size() >= 1) { 
                m_vColumns.insert(m_vColumns.end(), cColumn);
            }
        }

        // REAL columns
        void Storage::addReal(std::string cName) {
            return addReal(cName, false);
        }
        void Storage::addReal(std::string cName, bool bNullable) {
            std::string cColumn;
            
            if (bNullable) {
                cColumn = (cName + " REAL NULL");
            } else {
                cColumn = (cName + " REAL NOT NULL");
            }
        
            m_vColumns.insert(m_vColumns.end(), cColumn);
        }

        // BLOB columns
        void Storage::addBlob(std::string cName) {
            return addBlob(cName, false);
        }
        void Storage::addBlob(std::string cName, bool bNullable) {
            std::string cColumn;

            if (bNullable) {
                cColumn = (cName + " BLOB NULL");
            } else {
                cColumn = (cName + " BLOB NOT NULL");
            }

            if (cColumn.size() >= 1) {
                m_vColumns.insert(m_vColumns.end(), cColumn);
            }
        }

        // BOOL columns        
        void Storage::addBool(std::string cName) {
            return addBool(cName, false, false);
        }
        void Storage::addBool(std::string cName, bool bIndex) {
            return addBool(cName, bIndex, false);
        }
        void Storage::addBool(std::string cName, bool bIndex, bool bNullable) {
            addInt(cName, 1, bNullable, bIndex);
        }

        // DATE columns
        void Storage::addDate(std::string cName) {
            addDate(cName, false);
        }
        void Storage::addDate(std::string cName, bool bNullable) {
            addText(cName, bNullable);
        }

        // Create Table
        void Storage::createTable() {    
            if (m_vColumns.size() >= 1) {
                std::string cSQL = "CREATE TABLE " + m_cTable + "(";

                for (int i = 0; i != m_vColumns.size(); i++) {
                   cSQL = (cSQL + m_vColumns.at(i));
                
                    if (i != (m_vColumns.size() - 1)) {
                        cSQL = (cSQL + ", ");
                    }
                }

                cSQL = (cSQL + ");");
                m_vColumns.clear();
                createTable(cSQL);
            }
        }
        void Storage::createTable(std::string cSQL) {
            return execute(cSQL);
        }

        // Create Index
        void Storage::addIndex(std::string cName) {
            addIndex(cName, cName);
        }
        void Storage::addIndex(std::string cName, std::string cColumn) {
            addIndex(cName, cColumn, m_cTable);
        }
        void Storage::addIndex(std::string cName, std::vector<std::string> vColumns) {
            std::string cColumns;

            for (int i = 0; i < vColumns.size(); i++) {
                cColumns = (cColumns + vColumns.at(i));
            
                if (i != (vColumns.size() - 1)) {
                    cColumns = (cColumns + ", ");
                }
            }
            addIndex(cName, cColumns, m_cTable);
        }
        void Storage::addIndex(std::string cName, std::string cColumn, std::string cTable) {
            std::string cSQL = ("CREATE INDEX " + cName + " ON " + cTable + "(" + cColumn + ");");

            return execute(cSQL);
        }

        // Executabe abitry SQL
        void Storage::execute(std::string cSQL) {
            char *mError = 0;

            int iCreate = sqlite3_exec(m_pDB, cSQL.c_str(), setResult, NULL, &mError);
            if (iCreate) {
                char cError[100];
                std::sprintf(cError, "SQL Error: %s", mError);
                sqlite3_free(mError);

                throw ExceptionHandler(cError, true);
            }
        }

        // Set Column
        void Storage::setColumn(std::string cColumn) {
            setValue(cColumn);
        }

        // Values to update
        void Storage::setValue(std::string cColumn) {
            m_vNullValues.insert(m_vNullValues.end(), cColumn);
        }
        void Storage::setValue(std::string cColumn, int iValue) {
            setValue(cColumn, getString(iValue));
        }
        void Storage::setValue(std::string cColumn, float fValue) {
            setValue(cColumn, getString(fValue));
        }
        void Storage::setValue(std::string cColumn, bool bValue) {
            setValue(cColumn, getString(bValue));
        }
        void Storage::setValue(std::string cColumn, std::string cValue) {
            m_mValues.insert(std::pair<std::string, std::string>(cColumn, cValue));
        }
    
        // Where clauses
        void Storage::setWhere(std::string cColumn) {
            m_vNullWheres.insert(m_vNullValues.end(), cColumn);
        }
        void Storage::setWhere(std::string cColumn, int iValue) {
            setWhere(cColumn, getString(iValue));
        }
        void Storage::setWhere(std::string cColumn, float fValue) {
            setWhere(cColumn, getString(fValue));
        }
        void Storage::setWhere(std::string cColumn, bool bValue) {
            setWhere(cColumn, getString(bValue));
        }
        void Storage::setWhere(std::string cColumn, std::string cValue) {
            m_mWheres.insert(std::pair<std::string, std::string>(cColumn, cValue));
        }

        // Update
        void Storage::update() {
            // make sure that there is actually values, where clause not always needed
            if (m_mValues.size() < 1) { return; }
    
            // inital part of query
            std::string cSQL = ("UPDATE " + m_cTable + " SET ");

            // values to update
            int i = 0;
            for (std::map<std::string, std::string>::iterator it = m_mValues.begin(); it != m_mValues.end(); it++) {
                cSQL = (cSQL + it->first + "='" + it->second + "'");

                if (i != (m_mValues.size() - 1)) {
                    cSQL = (cSQL + ",");
                }
                i++;
            }

            // null values
            i = 0;
            for (std::string cColumn : m_vNullValues) {
                cSQL = (cSQL + cColumn + " = NULL");

                if (i != (m_vNullValues.size() - 1)) {
                    cSQL = (cSQL + ",");
                }
                i++;
            }

            // where clauses
            i = 0;
            if (m_mWheres.size() >= 1) {
                cSQL = (cSQL + " WHERE ");
                for (std::map<std::string, std::string>::iterator it = m_mWheres.begin(); it != m_mWheres.end(); it++) {
                    cSQL = (cSQL + it->first + "='" + it->second + "'");
    
                    if (i != (m_mWheres.size() - 1)) {
                        cSQL = (cSQL + " AND ");
                    }
                    i++;
                }
            }

            // null wheres
            i = 0;
            if (m_vNullWheres.size() >= 1) {
                if (m_mWheres.size() >= 1) {
                    cSQL = (cSQL + " AND ");
                } else {
                    cSQL = (cSQL + " WHERE ");
                }
                for (std::string cWhere : m_vNullWheres) {
                    cSQL = (cSQL + cWhere + " = NULL");
                    
                    if (i != (m_vNullWheres.size() - 1)) {
                        cSQL = (cSQL + " AND ");
                    }
                    i++;
                }
            }

            // close the query
            cSQL = (cSQL + ";");

            return update(cSQL);
        }
        void Storage::update(std::string cSQL) {
            // clear the arrays to make sure
            m_mValues.clear();
            m_vNullValues.clear();
            m_mWheres.clear();
            m_vNullWheres.clear();
    
            return execute(cSQL);
        }

        // Insert
        void Storage::insert() {
            if (m_mValues.size() < 1) { return; }

            // inital part of query
            std::string cSQL = ("INSERT INTO " + m_cTable + "(");

            // keys for insert
            int i = 0;
            for (std::map<std::string, std::string>::iterator it = m_mValues.begin(); it != m_mValues.end(); it++) {
                cSQL = (cSQL + it->first);

                if (i != (m_mValues.size() - 1)) {
                    cSQL = (cSQL + ", ");
                }
                i++;
            }

            // null keys
            i = 0;
            if (m_vNullValues.size() >= 1) {
                if (m_mValues.size() >= 1) {
                    cSQL = (cSQL + ", ");
                }
        
                for (std::string cColumn : m_vNullValues) {
                    cSQL = (cSQL + cColumn);
                
                    if (i != (m_vNullValues.size() - 1)) {
                        cSQL = (cSQL + ", ");
                    }
                    i++;
                }
            }

            // values
            cSQL = (cSQL + ") VALUES (");
            i = 0;
            for (std::map<std::string, std::string>::iterator it = m_mValues.begin(); it != m_mValues.end(); it++) {
                cSQL = (cSQL + "'" + it->second + "'");
            
                if (i != (m_mValues.size() - 1)) {
                    cSQL = (cSQL + ", ");
                }
                i++;
            }

            // null values
            i = 0;
            if (m_vNullValues.size() >= 1) {
                if (m_mValues.size() >= 1) {
                    cSQL = (cSQL + ", ");
                }

                for (std::string cColumn : m_vNullValues) {
                    cSQL = (cSQL + "NULL");
            
                    if (i != (m_vNullValues.size() - 1)) {
                        cSQL = (cSQL + ", ");
                    }
                    i++;
                }
            }

            // close the insert
            cSQL = (cSQL + ");");

            return insert(cSQL);
        }
        void Storage::insert(std::string cSQL) {
            //clear the arrays, just to make sure
            m_mValues.clear();
            m_vNullValues.clear();
            m_mWheres.clear();
            m_vNullWheres.clear();

            return execute(cSQL);
        }

        // Delete
        void Storage::del() {
            std::string cSQL = ("DELETE FROM " + m_cTable);

            int i = 0;
            if (m_mWheres.size() >= 1) {
                cSQL = (cSQL + " WHERE ");
                for (std::map<std::string, std::string>::iterator it = m_mWheres.begin(); it != m_mWheres.end(); it++) {
                    cSQL = (cSQL + it->first + "='" + it->second + "'");

                    if (i != m_mWheres.size() - 1) {
                        cSQL = (cSQL + " AND ");
                    }
                    i++;
                }
            }

            // null wheres
            i = 0;
            if (m_vNullWheres.size() >= 1) {
                if (m_mWheres.size() >= 1) {
                    cSQL = (cSQL + " AND ");
                } else {
                    cSQL = (cSQL + " WHERE ");
                }

                for (std::string cWhere : m_vNullWheres) {
                    cSQL = (cSQL + cWhere + " = NULL");
            
                    if (i != (m_vNullWheres.size() - 1)) {
                        cSQL = (cSQL + " AND ");
                    }
                    i++;
                }
            }

            // close the query
            cSQL = (cSQL + ";");

            return del(cSQL);
        }
        void Storage::del(std::string cSQL) {
            // clear the arrays
            m_mValues.clear();
            m_vNullValues.clear();
            m_mWheres.clear();
            m_vNullWheres.clear();

            return execute(cSQL);
        }

        // Select
        void Storage::select() {
            std::string cSQL = ("SELECT ");
            
            int i = 0;
            if (m_vNullValues.size() >= 1) {
                for (std::string cColumn : m_vNullValues) {
                    cSQL = (cSQL + cColumn);

                    if (i != (m_vNullValues.size() - 1)) {
                        cSQL = (cSQL + ", ");
                    }
                    i++;
                }
            } else {
                cSQL = (cSQL + " * ");
            }

            // add table
            cSQL = (cSQL + " FROM " + m_cTable);
    
            // wheres
            i = 0;
            if (m_mWheres.size() >= 1) {
                cSQL = (cSQL + " WHERE ");

                for (std::map<std::string, std::string>::iterator it = m_mWheres.begin(); it != m_mWheres.end(); it++) {
                    cSQL = (cSQL + it->first + " = '" + it->second + "'");

                    if (i != (m_mWheres.size() - 1)) {
                        cSQL = (cSQL + " AND ");
                    }
                    i++;
                }
            }

            // null wheres
            i = 0;
            if (m_vNullWheres.size() >= 1) {
                if (m_mWheres.size() >= 1) {
                    cSQL = (cSQL + " AND ");
                } else {
                    cSQL = (cSQL + " WHERE ");
                }

                for (std::string cWhere : m_vNullWheres) {
                    cSQL = (cSQL + cWhere + " = NULL");

                    if (i != (m_vNullWheres.size() - 1)) {
                        cSQL = (cSQL + " AND ");
                    }
                    i++;
                }
            }

            // close the query
            cSQL = (cSQL + ";");

            return select(cSQL);
        }
        void Storage::select(std::string cSQL) {
            // clear the arrays
            m_mValues.clear();
            m_vNullValues.clear();
            m_mWheres.clear();
            m_vNullWheres.clear();

            // return data
            return execute(cSQL);
        }

        // Result
        int Storage::setResult(void *pObject, int iArgc, char **cArgv, char **cColumn) {
            std::map<std::string, std::string> mResult;

            for (int i = 0; i < iArgc; i++) {
                mResult.insert(std::pair<std::string, std::string>(cColumn[i], (cArgv[i] ? cArgv[i] : "NULL")));
            }

            gResult = mResult;

            return 0;
        }
        std::map<std::string, std::string> Storage::getResult() {
            std::map<std::string, std::string> mResult = gResult;
            gResult.clear();
            
            return mResult;
        }
    };
};