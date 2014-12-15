#ifndef NordicArts_NordicEngine_Input_Definitions_H
#define NordicArts_NordicEngine_Input_Definitions_H

#include <NordicEngine/glfw/include/GLFW/glfw3.h>

namespace NordicArts {
    namespace NordicEngine {
        enum NEKStatus {
            NEK_RELEASE  = GLFW_RELEASE,
            NEK_PRESS    = GLFW_PRESS,
            NEK_REPEAT   = GLFW_REPEAT
        };
    
        enum NEMouse {
            NEM_BUTTON1  = GLFW_MOUSE_BUTTON_1,
            NEM_BUTTON2  = GLFW_MOUSE_BUTTON_2,
            NEM_BUTTON3  = GLFW_MOUSE_BUTTON_3,
            NEM_BUTTON4  = GLFW_MOUSE_BUTTON_4,
            NEM_BUTTON5  = GLFW_MOUSE_BUTTON_5,
            NEM_BUTTON6  = GLFW_MOUSE_BUTTON_6,
            NEM_BUTTON7  = GLFW_MOUSE_BUTTON_7,
            NEM_BUTTON8  = GLFW_MOUSE_BUTTON_8,

            NEM_LAST     = NEM_BUTTON8,
            NEM_LEFT     = NEM_BUTTON1,
            NEM_MIDDLE   = NEM_BUTTON3,
            NEM_RIGHT    = NEM_BUTTON2
        };
        
        enum NEKeyboard {
            // Letters
            NEK_A = GLFW_KEY_A,
            NEK_B = GLFW_KEY_B,
            NEK_C = GLFW_KEY_C,
            NEK_D = GLFW_KEY_D,
            NEK_E = GLFW_KEY_E,
            NEK_F = GLFW_KEY_F,
            NEK_G = GLFW_KEY_G,
            NEK_H = GLFW_KEY_H,
            NEK_I = GLFW_KEY_I,
            NEK_J = GLFW_KEY_J,
            NEK_L = GLFW_KEY_L,
            NEK_M = GLFW_KEY_M,
            NEK_N = GLFW_KEY_N,
            NEK_O = GLFW_KEY_O,
            NEK_P = GLFW_KEY_P,
            NEK_Q = GLFW_KEY_Q,
            NEK_R = GLFW_KEY_R,
            NEK_S = GLFW_KEY_S,
            NEK_T = GLFW_KEY_T,
            NEK_U = GLFW_KEY_U,
            NEK_V = GLFW_KEY_V,
            NEK_W = GLFW_KEY_W,
            NEK_X = GLFW_KEY_X,
            NEK_Y = GLFW_KEY_Y,
            NEK_Z = GLFW_KEY_Z,

            // Numbers
            NEK_0    = GLFW_KEY_0,
            NEK_1    = GLFW_KEY_1,
            NEK_2    = GLFW_KEY_2,
            NEK_3    = GLFW_KEY_3,
            NEK_4    = GLFW_KEY_4,
            NEK_5    = GLFW_KEY_5,
            NEK_6    = GLFW_KEY_6,
            NEK_7    = GLFW_KEY_7,
            NEK_8    = GLFW_KEY_8,
            NEK_9    = GLFW_KEY_9,
            NEK_KP_0 = GLFW_KEY_KP_0,
            NEK_KP_1 = GLFW_KEY_KP_1,
            NEK_KP_2 = GLFW_KEY_KP_2,
            NEK_KP_3 = GLFW_KEY_KP_3,
            NEK_KP_4 = GLFW_KEY_KP_4,
            NEK_KP_5 = GLFW_KEY_KP_5,
            NEK_KP_6 = GLFW_KEY_KP_6,
            NEK_KP_7 = GLFW_KEY_KP_7,
            NEK_KP_8 = GLFW_KEY_KP_8,
            NEK_KP_9 = GLFW_KEY_KP_9,

            // F Keys
            NEK_F1   = GLFW_KEY_F1,
            NEK_F2   = GLFW_KEY_F2,
            NEK_F3   = GLFW_KEY_F3,
            NEK_F4   = GLFW_KEY_F4,
            NEK_F5   = GLFW_KEY_F5,
            NEK_F6   = GLFW_KEY_F6,
            NEK_F7   = GLFW_KEY_F7,
            NEK_F8   = GLFW_KEY_F8,
            NEK_F9   = GLFW_KEY_F9,
            NEK_F10  = GLFW_KEY_F10,
            NEK_F11  = GLFW_KEY_F11,
            NEK_F12  = GLFW_KEY_F12,
            NEK_F13  = GLFW_KEY_F13,
            NEK_F14  = GLFW_KEY_F14,
            NEK_F15  = GLFW_KEY_F15,

            // Maths
            NEK_MINUS        = GLFW_KEY_MINUS,
            NEK_EQUAL        = GLFW_KEY_EQUAL,
            NEK_KP_DECIMAL   = GLFW_KEY_KP_DECIMAL,
            NEK_KP_DIVIDE    = GLFW_KEY_KP_DIVIDE,
            NEK_KP_MULTIPLY  = GLFW_KEY_KP_MULTIPLY,
            NEK_KP_SUBTRACT  = GLFW_KEY_KP_SUBTRACT,
            NEK_KP_ADD       = GLFW_KEY_KP_ADD,
            NEK_KP_EQUAL     = GLFW_KEY_KP_EQUAL,

            // Modifier
            NEK_LEFT_SHIFT   = GLFW_KEY_LEFT_SHIFT,
            NEK_RIGHT_SHIFT  = GLFW_KEY_RIGHT_SHIFT,
            NEK_LEFT_CTRL    = GLFW_KEY_LEFT_CONTROL,
            NEK_RIGHT_CTRL   = GLFW_KEY_RIGHT_CONTROL,
            NEK_LEFT_ALT     = GLFW_KEY_LEFT_ALT,
            NEK_RIGHT_ALT    = GLFW_KEY_RIGHT_ALT,
            NEK_LEFT_SUPER   = GLFW_KEY_LEFT_SUPER,
            NEK_RIGHT_SUPER  = GLFW_KEY_RIGHT_SUPER,
        
            // Locks
            NEK_CAPS         = GLFW_KEY_CAPS_LOCK,
            NEK_SCROLL       = GLFW_KEY_SCROLL_LOCK,
            NEK_NUM          = GLFW_KEY_NUM_LOCK,
            
            // Arrows
            NEK_UP           = GLFW_KEY_UP,
            NEK_DOWN         = GLFW_KEY_DOWN,
            NEK_LEFT         = GLFW_KEY_LEFT,
            NEK_RIGHT        = GLFW_KEY_RIGHT,

            // Puncutation
            NEK_APOSTROPHE       = GLFW_KEY_APOSTROPHE,
            NEK_COMMA            = GLFW_KEY_COMMA,
            NEK_SEMICOLON        = GLFW_KEY_SEMICOLON,
            NEK_PERIOD           = GLFW_KEY_PERIOD,
            NEK_SLASH            = GLFW_KEY_SLASH,
            NEK_GRAVE_ACCENT     = GLFW_KEY_GRAVE_ACCENT,
            
            // General
            NEK_SPACE            = GLFW_KEY_SPACE,
            NEK_BACKSLASH        = GLFW_KEY_BACKSLASH,
            NEK_LEFT_BRACKET     = GLFW_KEY_LEFT_BRACKET,
            NEK_RIGHT_BRACKET    = GLFW_KEY_RIGHT_BRACKET,
            NEK_ESCAPE           = GLFW_KEY_ESCAPE,
            NEK_TAB              = GLFW_KEY_TAB,
            NEK_BACKSPACE        = GLFW_KEY_BACKSPACE,
            NEK_INSERT           = GLFW_KEY_INSERT,
            NEK_DELETE           = GLFW_KEY_DELETE,
            NEK_PAGE_UP          = GLFW_KEY_PAGE_UP,
            NEK_PAGE_DOWN        = GLFW_KEY_PAGE_DOWN,
            NEK_HOME             = GLFW_KEY_HOME,
            NEK_END              = GLFW_KEY_END,
            NEK_ENTER            = GLFW_KEY_ENTER,
            NEK_KP_ENTER         = GLFW_KEY_KP_ENTER,
            NEK_PAUSE            = GLFW_KEY_PAUSE,
            NEK_WORLD1           = GLFW_KEY_WORLD_1,
            NEK_WORLD2           = GLFW_KEY_WORLD_2,
            NEK_MENU             = GLFW_KEY_MENU,

            // Others
            NEK_UNKNOWN          = GLFW_KEY_UNKNOWN,
            NEK_LAST             = NEK_MENU   
        };

        struct MouseInfo {
            double xPos;
            double yPos;

            NEKStatus mouse1;
            NEKStatus mouse2;
            NEKStatus mouse3;
            NEKStatus mouse4;
            NEKStatus mouse5;
            NEKStatus mouse6;
            NEKStatus mouse7;
            NEKStatus mouse8;
    
            MouseInfo() : xPos(0), yPos(0) {}
            MouseInfo(double x, double y) : xPos(x), yPos(y) {}
        };

        struct KeyboardInfo {
            NEKStatus A;
            NEKStatus B;
            NEKStatus C;
            NEKStatus D;
            NEKStatus E;
            NEKStatus F;
            NEKStatus G;
            NEKStatus H;
            NEKStatus I;
            NEKStatus J;
            NEKStatus K;
            NEKStatus L;
            NEKStatus M;
            NEKStatus N;
            NEKStatus O;
            NEKStatus P;
            NEKStatus Q;
            NEKStatus R;
            NEKStatus S;
            NEKStatus T;
            NEKStatus U;
            NEKStatus V;
            NEKStatus W;
            NEKStatus X;
            NEKStatus Y;
            NEKStatus Z;
            
            KeyboardInfo() {};
        };
    };
};

#endif
