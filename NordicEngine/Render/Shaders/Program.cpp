#include <NordicEngine/Render/Shaders/Program.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Shaders {
                Program::Program() : m_bIsLinked(false), m_pVertex(nullptr), m_pFragment(nullptr), m_pGeometry(nullptr) {
                    m_iID = glCreateProgram();
                }

                Program::Program(Shader *pVertex, Shader *pFragment) : m_bIsLinked(false) {
                    attachShader(pVertex);
                    attachShader(pFragment);
                }

                Program::~Program() {
                    glDeleteProgram(m_iID);
                }

                unsigned int Program::getID() const {
                    return m_iID;
                }

                void Program::attachShader(Shader *pShader) {
                    switch (pShader->getType()) {
                        case NES_VERTEX: {
                            this->m_pVertex = pShader;
                            break;
                        }

                        case NES_FRAGMENT: {
                            this->m_pFragment = pShader;
                            break;
                        }

                        case NES_GEOMETRY: {
                            this->m_pGeometry = pShader;
                            break;
                        }
                        
                        case NES_TESS_CONTROL: {
                            this->m_pTessCtrl = pShader;
                            break;
                        }

                        case NES_TESS_EVAL: {
                            this->m_pTessEval = pShader;
                            break;
                        }

                        case NES_COMPUTE:
                        default: {
                            break;
                        }
                    }

                    glAttachShader(m_iID, pShader->getID());
                }

                void Program::link() {
                    glLinkProgram(m_iID);    
                    check(GL_LINK_STATUS);

                    glValidateProgram(m_iID);
                    check(GL_VALIDATE_STATUS);

                    m_bIsLinked = true;
                    postLinkHook();

                    if (m_pVertex != nullptr) { glDetachShader(m_iID, m_pVertex->getID()); }
                    if (m_pFragment != nullptr) { glDetachShader(m_iID, m_pFragment->getID()); }
                    if (m_pGeometry != nullptr) { glDetachShader(m_iID, m_pGeometry->getID()); }
                }

                void Program::check(GLenum eCheck) {
                    int iStatus;
                    glGetProgramiv(m_iID, eCheck, &iStatus);
                    if (iStatus != GL_TRUE) {
                        int iLogLength;
                        glGetProgramiv(m_iID, GL_INFO_LOG_LENGTH, &iLogLength);

                        char *cInfoLog = new char[iLogLength];
                        glGetProgramInfoLog(m_iID, iLogLength, NULL, cInfoLog);
                        printIt(iLogLength);
                        printIt(m_iID);

                        std::string cWhat = "";
                        switch (eCheck) {
                            case GL_LINK_STATUS: {
                                cWhat = "linking";
                                break;
                            }

                            case GL_VALIDATE_STATUS: {
                                cWhat = "validation";
                                break;
                            }
                
                            case GL_COMPILE_STATUS: {
                                cWhat = "compilation";
                                break;
                            }

                            default: {
                                cWhat = "Unkown";
                                break;
                            }
                        }

                        throwError(__FUNCTION__, cWhat + std::string(", ") + std::string(cInfoLog));
                        SAFE_DELETE_ARRAY(cInfoLog);
                    }
                }

                void Program::use() {
                    glUseProgram(m_iID);
                }

                void Program::stopUsing() {
                    glUseProgram((unsigned int)0);
                }

                int Program::getUniformID(std::string cName) {
                    return glGetUniformLocation(m_iID, cName.c_str());
                }

                int Program::getAttributeID(std::string cName) {
                    if (m_bIsLinked) {
                        int iAttributeID = glGetAttribLocation(m_iID, cName.c_str());
                        if (iAttributeID == -1) {
                            dumpActiveAttributes();

                            throwError(__FUNCTION__ + std::string(" attribute is not found in linked shader, ") + cName);
                        } else {
                            return iAttributeID;
                        }
                    } else {
                        throwError(__FUNCTION__ + std::string(" you need to link the shader before doing attributes, ") + cName);
                    }

                    return -1;
                }

                void Program::setAttributeID(std::string cName, unsigned int iID) {
                    if (m_bIsLinked) {
                        glBindAttribLocation(m_iID, iID, cName.c_str());
                    } else {
                        throwError(__FUNCTION__ + std::string(" trying to assigned attributes after linking, ") + cName);
                    }
                }

                void Program::dumpActiveAttributes() {
                    int iNumAttributes;
                    glGetProgramiv(m_iID, GL_ACTIVE_ATTRIBUTES, &iNumAttributes);

                    int iMaxLength;
                    glGetProgramiv(m_iID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &iMaxLength);

                    for (int i = 0; i < iNumAttributes; i++) {
                        GLsizei iLength;
                        int iSize;
                        GLenum eType;
                        char *cName = new char[iMaxLength];
                        glGetActiveAttrib(m_iID, i, iMaxLength, &iLength, &iSize, &eType, cName);

                        SAFE_DELETE_ARRAY(cName);
                    }
                }

                void Program::attachData(int iColor, std::string cData) {
                    glBindFragDataLocation(m_iID, iColor, cData.c_str());
                }

                void Program::postLinkHook() {
                    //m_iPositionID = getAttributeID("vertex_position");
                    //m_iMatrixID   = getUniformID("mvp_matrix");
                }
            };
        };
    };
};
