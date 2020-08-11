#ifndef ABSTRACTEVENTHANDLER_H
#define ABSTRACTEVENTHANDLER_H

#include <engine/math/vector.h>



namespace e172 {

/**
 *  \brief These values are taken from SDL library
 *
 */
typedef enum
{
    ScancodeUnknown = 0,

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

    ScancodeReturn = 40,
    ScancodeEscape = 41,
    ScancodeBackSpace = 42,
    ScancodeTab = 43,
    ScancodeSpace = 44,

    ScancodeMinus = 45,
    ScancodeEquals = 46,
    ScancodeLeftBracket = 47,
    ScancodeRightBracket = 48,
    ScancodeBackslash = 49, /**< Located at the lower left of the return
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
    ScancodeNonushash = 50, /**< ISO USB keyboards actually use this code
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
    ScancodeSemicolon = 51,
    ScancodeApostrophe = 52,
    ScancodeGrave = 53, /**< Located in the top left corner (on both ANSI
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
    ScancodeComma = 54,
    ScancodePeriod = 55,
    ScancodeSlash = 56,

    ScancodeCapsLock = 57,

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

    ScancodePrintScreen = 70,
    ScancodeScrollLock = 71,
    ScancodePause = 72,
    ScancodeInsert = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    ScancodeHome = 74,
    ScancodePageUp = 75,
    ScancodeDelete = 76,
    ScancodeEnd = 77,
    ScancodePageDown = 78,
    ScancodeRight = 79,
    ScancodeLeft = 80,
    ScancodeDown = 81,
    ScancodeUp = 82,

    ScancodeNumLockClear = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    ScancodeKpDivide = 84,
    ScancodeKpMultiply = 85,
    ScancodeKpMinus = 86,
    ScancodeKpPlus = 87,
    ScancodeKpEnter = 88,
    ScancodeKp1 = 89,
    ScancodeKp2 = 90,
    ScancodeKp3 = 91,
    ScancodeKp4 = 92,
    ScancodeKp5 = 93,
    ScancodeKp6 = 94,
    ScancodeKp7 = 95,
    ScancodeKp8 = 96,
    ScancodeKp9 = 97,
    ScancodeKp0 = 98,
    ScancodeKpPeriod = 99,

    ScancodeNonUsBackSlash = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    ScancodeApplication = 101, /**< windows contextual menu, compose */
    ScancodePower = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    ScancodeKPEquals = 103,
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
    ScancodeExecute = 116,
    ScancodeHelp = 117,
    ScancodeMenu = 118,
    ScancodeSelect = 119,
    ScancodeStop = 120,
    ScancodeAgain = 121,   /**< redo */
    ScancodeUndo = 122,
    ScancodeCut = 123,
    ScancodeCopy = 124,
    ScancodePaste = 125,
    ScancodeFind = 126,
    ScancodeMute = 127,
    ScancodeVolumeUp = 128,
    ScancodeVolumeDown = 129,
/* not sure whether there's a reason to enable these */
/*     ScancodeLOCKINGCAPSLOCK = 130,  */
/*     ScancodeLOCKINGNUMLOCK = 131, */
/*     ScancodeLOCKINGSCROLLLOCK = 132, */
    ScancodeKPComma = 133,
    ScancodeKPEqualSas400 = 134,

    ScancodeInternational1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    ScancodeInternational2 = 136,
    ScancodeInternational3 = 137, /**< Yen */
    ScancodeInternational4 = 138,
    ScancodeInternational5 = 139,
    ScancodeInternational6 = 140,
    ScancodeInternational7 = 141,
    ScancodeInternational8 = 142,
    ScancodeInternational9 = 143,
    ScancodeLang1 = 144, /**< Hangul/English toggle */
    ScancodeLang2 = 145, /**< Hanja conversion */
    ScancodeLang3 = 146, /**< Katakana */
    ScancodeLang4 = 147, /**< Hiragana */
    ScancodeLang5 = 148, /**< Zenkaku/Hankaku */
    ScancodeLang6 = 149, /**< reserved */
    ScancodeLang7 = 150, /**< reserved */
    ScancodeLang8 = 151, /**< reserved */
    ScancodeLang9 = 152, /**< reserved */

    ScancodeAlterase = 153, /**< Erase-Eaze */
    ScancodeSysREQ = 154,
    ScancodeCancel = 155,
    ScancodeClear = 156,
    ScancodePrior = 157,
    ScancodeReturn2 = 158,
    ScancodeSeparator = 159,
    ScancodeOut = 160,
    ScancodeOper = 161,
    ScancodeClearAgain = 162,
    ScancodeCrsel = 163,
    ScancodeExsel = 164,

    ScancodeKP00 = 176,
    ScancodeKP000 = 177,
    ScancodeThousandsSeparator = 178,
    ScancodeDecimalSeparator = 179,
    ScancodeCurrencyUnit = 180,
    ScancodeCurrencySubunit = 181,
    ScancodeKpLeftParen = 182,
    ScancodeKpRightParen = 183,
    ScancodeKpLeftBrace = 184,
    ScancodeKpRightBrace = 185,
    ScancodeKpTab = 186,
    ScancodeKpBackspace = 187,
    ScancodeKpA = 188,
    ScancodeKpB = 189,
    ScancodeKpC = 190,
    ScancodeKpD = 191,
    ScancodeKpE = 192,
    ScancodeKpF = 193,
    ScancodeKpXor = 194,
    ScancodeKpPower = 195,
    ScancodeKpPercent = 196,
    ScancodeKpLess = 197,
    ScancodeKpGreater = 198,
    ScancodeKpAmpersand = 199,
    ScancodeKpDblAmpersand = 200,
    ScancodeKpVerticalBar = 201,
    ScancodeKpDblVerticalBar = 202,
    ScancodeKpColon = 203,
    ScancodeKpHash = 204,
    ScancodeKpSpace = 205,
    ScancodeKpAt = 206,
    ScancodeKpExclam = 207,
    ScancodeKpMemStore = 208,
    ScancodeKpMemRecall = 209,
    ScancodeKpMemClear = 210,
    ScancodeKpMemAdd = 211,
    ScancodeKpMemSubtract = 212,
    ScancodeKpMemMultiply = 213,
    ScancodeKpMemDivide = 214,
    ScancodeKpPlusMinus = 215,
    ScancodeKpClear = 216,
    ScancodeKpClearEntry = 217,
    ScancodeKpBinary = 218,
    ScancodeKpOctal = 219,
    ScancodeKpDecimal = 220,
    ScancodeKpHexadecimal = 221,

    ScancodeLCtrl = 224,
    ScancodeLShift = 225,
    ScancodeLAlt = 226, /**< alt, option */
    ScancodeLGui = 227, /**< windows, command (apple), meta */
    ScancodeRCtrl = 228,
    ScancodeRShift = 229,
    ScancodeRAlt = 230, /**< alt gr, option */
    ScancodeRGui = 231, /**< windows, command (apple), meta */

    ScancodeMode = 257,    /**< I'm not sure if this is really not covered
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

    ScancodeAudioNext = 258,
    ScancodeAudioPrev = 259,
    ScancodeAudioStop = 260,
    ScancodeAudioPlay = 261,
    ScancodeAudioMute = 262,
    ScancodeMediaSelect = 263,
    ScancodeWWW = 264,
    ScancodeMail = 265,
    ScancodeCalculator = 266,
    ScancodeComputer = 267,
    ScancodeAcSearch = 268,
    ScancodeAcHome = 269,
    ScancodeAcBack = 270,
    ScancodeAcForward = 271,
    ScancodeAcStop = 272,
    ScancodeAcRefresh = 273,
    ScancodeAcBookmarks = 274,

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    ScancodeBrightnessDown = 275,
    ScancodeBrightnessUp = 276,
    ScancodeDisplaySwitch = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    ScancodeKbDillumToggle = 278,
    ScancodeKbDillumDown = 279,
    ScancodeKbDillumUp = 280,
    ScancodeEject = 281,
    ScancodeSleep = 282,

    ScancodeApp1 = 283,
    ScancodeApp2 = 284,

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    ScancodeAudioRewind = 285,
    ScancodeAudioFastForward = 286,

    /* @} *//* Usage page 0x0C (additional media keys) */

    /* Add any other keys here. */

    ScancodesCount = 512 /**< not a key, just marks the number of scancodes
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
