#ifndef ABSTRACTEVENTHANDLER_H
#define ABSTRACTEVENTHANDLER_H

#include <engine/math/vector.h>



namespace e172 {

/**
 *  \brief The SDL keyboard scancode representation.
 *
 *  Values of this type are used to represent keyboard keys, among other places
 *  in the \link Keysym::scancode key.keysym.scancode \endlink field of the
 *  Event structure.
 *
 *  The values in this enumeration are based on the USB usage page standard:
 *  https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
 */
typedef enum
{
    ScancodeUNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    ScancodeA = 4,
    ScancodeB = 5,
    ScancodeC = 6,
    ScancodeD = 7,
    ScancodeE = 8,
    ScancodeF = 9,
    ScancodeG = 10,
    ScancodeH = 11,
    ScancodeI = 12,
    ScancodeJ = 13,
    ScancodeK = 14,
    ScancodeL = 15,
    ScancodeM = 16,
    ScancodeN = 17,
    ScancodeO = 18,
    ScancodeP = 19,
    ScancodeQ = 20,
    ScancodeR = 21,
    ScancodeS = 22,
    ScancodeT = 23,
    ScancodeU = 24,
    ScancodeV = 25,
    ScancodeW = 26,
    ScancodeX = 27,
    ScancodeY = 28,
    ScancodeZ = 29,

    Scancode1 = 30,
    Scancode2 = 31,
    Scancode3 = 32,
    Scancode4 = 33,
    Scancode5 = 34,
    Scancode6 = 35,
    Scancode7 = 36,
    Scancode8 = 37,
    Scancode9 = 38,
    Scancode0 = 39,

    ScancodeRETURN = 40,
    ScancodeESCAPE = 41,
    ScancodeBACKSPACE = 42,
    ScancodeTAB = 43,
    ScancodeSPACE = 44,

    ScancodeMINUS = 45,
    ScancodeEQUALS = 46,
    ScancodeLEFTBRACKET = 47,
    ScancodeRIGHTBRACKET = 48,
    ScancodeBACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    ScancodeNONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate ScancodeBACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    ScancodeSEMICOLON = 51,
    ScancodeAPOSTROPHE = 52,
    ScancodeGRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    ScancodeCOMMA = 54,
    ScancodePERIOD = 55,
    ScancodeSLASH = 56,

    ScancodeCAPSLOCK = 57,

    ScancodeF1 = 58,
    ScancodeF2 = 59,
    ScancodeF3 = 60,
    ScancodeF4 = 61,
    ScancodeF5 = 62,
    ScancodeF6 = 63,
    ScancodeF7 = 64,
    ScancodeF8 = 65,
    ScancodeF9 = 66,
    ScancodeF10 = 67,
    ScancodeF11 = 68,
    ScancodeF12 = 69,

    ScancodePRINTSCREEN = 70,
    ScancodeSCROLLLOCK = 71,
    ScancodePAUSE = 72,
    ScancodeINSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    ScancodeHOME = 74,
    ScancodePAGEUP = 75,
    ScancodeDELETE = 76,
    ScancodeEND = 77,
    ScancodePAGEDOWN = 78,
    ScancodeRIGHT = 79,
    ScancodeLEFT = 80,
    ScancodeDOWN = 81,
    ScancodeUP = 82,

    ScancodeNUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    ScancodeKP_DIVIDE = 84,
    ScancodeKP_MULTIPLY = 85,
    ScancodeKP_MINUS = 86,
    ScancodeKP_PLUS = 87,
    ScancodeKP_ENTER = 88,
    ScancodeKP_1 = 89,
    ScancodeKP_2 = 90,
    ScancodeKP_3 = 91,
    ScancodeKP_4 = 92,
    ScancodeKP_5 = 93,
    ScancodeKP_6 = 94,
    ScancodeKP_7 = 95,
    ScancodeKP_8 = 96,
    ScancodeKP_9 = 97,
    ScancodeKP_0 = 98,
    ScancodeKP_PERIOD = 99,

    ScancodeNONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    ScancodeAPPLICATION = 101, /**< windows contextual menu, compose */
    ScancodePOWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    ScancodeKP_EQUALS = 103,
    ScancodeF13 = 104,
    ScancodeF14 = 105,
    ScancodeF15 = 106,
    ScancodeF16 = 107,
    ScancodeF17 = 108,
    ScancodeF18 = 109,
    ScancodeF19 = 110,
    ScancodeF20 = 111,
    ScancodeF21 = 112,
    ScancodeF22 = 113,
    ScancodeF23 = 114,
    ScancodeF24 = 115,
    ScancodeEXECUTE = 116,
    ScancodeHELP = 117,
    ScancodeMENU = 118,
    ScancodeSELECT = 119,
    ScancodeSTOP = 120,
    ScancodeAGAIN = 121,   /**< redo */
    ScancodeUNDO = 122,
    ScancodeCUT = 123,
    ScancodeCOPY = 124,
    ScancodePASTE = 125,
    ScancodeFIND = 126,
    ScancodeMUTE = 127,
    ScancodeVOLUMEUP = 128,
    ScancodeVOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     ScancodeLOCKINGCAPSLOCK = 130,  */
/*     ScancodeLOCKINGNUMLOCK = 131, */
/*     ScancodeLOCKINGSCROLLLOCK = 132, */
    ScancodeKP_COMMA = 133,
    ScancodeKP_EQUALSAS400 = 134,

    ScancodeINTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    ScancodeINTERNATIONAL2 = 136,
    ScancodeINTERNATIONAL3 = 137, /**< Yen */
    ScancodeINTERNATIONAL4 = 138,
    ScancodeINTERNATIONAL5 = 139,
    ScancodeINTERNATIONAL6 = 140,
    ScancodeINTERNATIONAL7 = 141,
    ScancodeINTERNATIONAL8 = 142,
    ScancodeINTERNATIONAL9 = 143,
    ScancodeLANG1 = 144, /**< Hangul/English toggle */
    ScancodeLANG2 = 145, /**< Hanja conversion */
    ScancodeLANG3 = 146, /**< Katakana */
    ScancodeLANG4 = 147, /**< Hiragana */
    ScancodeLANG5 = 148, /**< Zenkaku/Hankaku */
    ScancodeLANG6 = 149, /**< reserved */
    ScancodeLANG7 = 150, /**< reserved */
    ScancodeLANG8 = 151, /**< reserved */
    ScancodeLANG9 = 152, /**< reserved */

    ScancodeALTERASE = 153, /**< Erase-Eaze */
    ScancodeSYSREQ = 154,
    ScancodeCANCEL = 155,
    ScancodeCLEAR = 156,
    ScancodePRIOR = 157,
    ScancodeRETURN2 = 158,
    ScancodeSEPARATOR = 159,
    ScancodeOUT = 160,
    ScancodeOPER = 161,
    ScancodeCLEARAGAIN = 162,
    ScancodeCRSEL = 163,
    ScancodeEXSEL = 164,

    ScancodeKP_00 = 176,
    ScancodeKP_000 = 177,
    ScancodeTHOUSANDSSEPARATOR = 178,
    ScancodeDECIMALSEPARATOR = 179,
    ScancodeCURRENCYUNIT = 180,
    ScancodeCURRENCYSUBUNIT = 181,
    ScancodeKP_LEFTPAREN = 182,
    ScancodeKP_RIGHTPAREN = 183,
    ScancodeKP_LEFTBRACE = 184,
    ScancodeKP_RIGHTBRACE = 185,
    ScancodeKP_TAB = 186,
    ScancodeKP_BACKSPACE = 187,
    ScancodeKP_A = 188,
    ScancodeKP_B = 189,
    ScancodeKP_C = 190,
    ScancodeKP_D = 191,
    ScancodeKP_E = 192,
    ScancodeKP_F = 193,
    ScancodeKP_XOR = 194,
    ScancodeKP_POWER = 195,
    ScancodeKP_PERCENT = 196,
    ScancodeKP_LESS = 197,
    ScancodeKP_GREATER = 198,
    ScancodeKP_AMPERSAND = 199,
    ScancodeKP_DBLAMPERSAND = 200,
    ScancodeKP_VERTICALBAR = 201,
    ScancodeKP_DBLVERTICALBAR = 202,
    ScancodeKP_COLON = 203,
    ScancodeKP_HASH = 204,
    ScancodeKP_SPACE = 205,
    ScancodeKP_AT = 206,
    ScancodeKP_EXCLAM = 207,
    ScancodeKP_MEMSTORE = 208,
    ScancodeKP_MEMRECALL = 209,
    ScancodeKP_MEMCLEAR = 210,
    ScancodeKP_MEMADD = 211,
    ScancodeKP_MEMSUBTRACT = 212,
    ScancodeKP_MEMMULTIPLY = 213,
    ScancodeKP_MEMDIVIDE = 214,
    ScancodeKP_PLUSMINUS = 215,
    ScancodeKP_CLEAR = 216,
    ScancodeKP_CLEARENTRY = 217,
    ScancodeKP_BINARY = 218,
    ScancodeKP_OCTAL = 219,
    ScancodeKP_DECIMAL = 220,
    ScancodeKP_HEXADECIMAL = 221,

    ScancodeLCTRL = 224,
    ScancodeLSHIFT = 225,
    ScancodeLALT = 226, /**< alt, option */
    ScancodeLGUI = 227, /**< windows, command (apple), meta */
    ScancodeRCTRL = 228,
    ScancodeRSHIFT = 229,
    ScancodeRALT = 230, /**< alt gr, option */
    ScancodeRGUI = 231, /**< windows, command (apple), meta */

    ScancodeMODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    ScancodeAUDIONEXT = 258,
    ScancodeAUDIOPREV = 259,
    ScancodeAUDIOSTOP = 260,
    ScancodeAUDIOPLAY = 261,
    ScancodeAUDIOMUTE = 262,
    ScancodeMEDIASELECT = 263,
    ScancodeWWW = 264,
    ScancodeMAIL = 265,
    ScancodeCALCULATOR = 266,
    ScancodeCOMPUTER = 267,
    ScancodeAC_SEARCH = 268,
    ScancodeAC_HOME = 269,
    ScancodeAC_BACK = 270,
    ScancodeAC_FORWARD = 271,
    ScancodeAC_STOP = 272,
    ScancodeAC_REFRESH = 273,
    ScancodeAC_BOOKMARKS = 274,

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    ScancodeBRIGHTNESSDOWN = 275,
    ScancodeBRIGHTNESSUP = 276,
    ScancodeDISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    ScancodeKBDILLUMTOGGLE = 278,
    ScancodeKBDILLUMDOWN = 279,
    ScancodeKBDILLUMUP = 280,
    ScancodeEJECT = 281,
    ScancodeSLEEP = 282,

    ScancodeAPP1 = 283,
    ScancodeAPP2 = 284,

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    ScancodeAUDIOREWIND = 285,
    ScancodeAUDIOFASTFORWARD = 286,

    /* @} *//* Usage page 0x0C (additional media keys) */

    /* Add any other keys here. */

    NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                                 for array bounds */
} Scancode;



class AbstractEventHandler
{
public:
    virtual bool exitFlag() const = 0;
    virtual bool keyHolded(Scancode key) const = 0;
    virtual bool keySinglePressed(Scancode key) const = 0;
    virtual void update() = 0;
    virtual Vector mousePosition() const = 0;
    AbstractEventHandler();
    virtual ~AbstractEventHandler();
};





}
#endif // ABSTRACTEVENTHANDLER_H
