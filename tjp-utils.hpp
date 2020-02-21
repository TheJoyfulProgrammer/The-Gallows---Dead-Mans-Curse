#ifndef TJPUTILS_H
#define TJPUTILS_H 1

#include <windows.h>

namespace tjpUtils
{
    const unsigned int MouseScrollWheelDown{7864320};
    const unsigned int MouseScrollWheelUp{4287102976};

    const unsigned char vkReturn{13};
    const unsigned char vkEsc{27};
    const unsigned char vkSpace{32};
    const unsigned char vkArrowLeft{37};
    const unsigned char vkArrowUp{38};
    const unsigned char vkArrowRight{39};
    const unsigned char vkArrowDown{40};
    const unsigned char vkCapA{65};
    const unsigned char vkCapN{78};
    const unsigned char vkCapY{89};
    const unsigned char vkCapZ{90};
    const unsigned char vkApostraphy{96};

    const unsigned char vkF1{112};
    const unsigned char vkF2{113};
    const unsigned char vkF3{114};
    const unsigned char vkF4{115};
    const unsigned char vkF5{116};
    const unsigned char vkF6{117};
    const unsigned char vkF7{118};
    const unsigned char vkF8{119};
    const unsigned char vkF9{120};
    const unsigned char vkF10{121};
    const unsigned char vkF11{122};
    const unsigned char vkF12{123};

    const unsigned char vkLeftCurlyBracket{123};

    const unsigned char ExtendedASCII_127{127};
    const unsigned char ExtendedASCII_128{128};
    const unsigned char ExtendedASCII_129{129};
    const unsigned char ExtendedASCII_130{130};
    const unsigned char ExtendedASCII_131{131};
    const unsigned char ExtendedASCII_132{132};
    const unsigned char ExtendedASCII_133{133};
    const unsigned char ExtendedASCII_134{134};
    const unsigned char ExtendedASCII_135{135};
    const unsigned char ExtendedASCII_136{136};
    const unsigned char ExtendedASCII_137{137};
    const unsigned char ExtendedASCII_138{138};
    const unsigned char ExtendedASCII_139{139};
    const unsigned char ExtendedASCII_140{140};
    const unsigned char ExtendedASCII_141{141};
    const unsigned char ExtendedASCII_142{142};
    const unsigned char ExtendedASCII_143{143};
    const unsigned char ExtendedASCII_144{144};
    const unsigned char ExtendedASCII_145{145};
    const unsigned char ExtendedASCII_146{146};
    const unsigned char ExtendedASCII_147{147};
    const unsigned char ExtendedASCII_148{148};
    const unsigned char ExtendedASCII_149{149};
    const unsigned char ExtendedASCII_150{150};
    const unsigned char ExtendedASCII_151{151};
    const unsigned char ExtendedASCII_152{152};
    const unsigned char ExtendedASCII_153{153};
    const unsigned char ExtendedASCII_154{154};
    const unsigned char ExtendedASCII_155{155};
    const unsigned char ExtendedASCII_156{156};
    const unsigned char ExtendedASCII_157{157};
    const unsigned char ExtendedASCII_158{158};
    const unsigned char ExtendedASCII_159{159};
    const unsigned char ExtendedASCII_160{160};
    const unsigned char ExtendedASCII_161{161};
    const unsigned char ExtendedASCII_162{162};
    const unsigned char ExtendedASCII_163{163};
    const unsigned char ExtendedASCII_164{164};
    const unsigned char ExtendedASCII_165{165};
    const unsigned char ExtendedASCII_166{166};
    const unsigned char ExtendedASCII_167{167};
    const unsigned char ExtendedASCII_168{168};
    const unsigned char ExtendedASCII_169{169};
    const unsigned char ExtendedASCII_170{170};
    const unsigned char ExtendedASCII_171{171};
    const unsigned char ExtendedASCII_172{172};
    const unsigned char ExtendedASCII_173{173};
    const unsigned char ExtendedASCII_174{174};
    const unsigned char ExtendedASCII_175{175};
    const unsigned char ExtendedASCII_176{176};
    const unsigned char ExtendedASCII_177{177};
    const unsigned char ExtendedASCII_178{178};
    const unsigned char ExtendedASCII_179{179};
    const unsigned char ExtendedASCII_180{180};
    const unsigned char ExtendedASCII_181{181};
    const unsigned char ExtendedASCII_182{182};
    const unsigned char ExtendedASCII_183{183};
    const unsigned char ExtendedASCII_184{184};
    const unsigned char ExtendedASCII_185{185};
    const unsigned char ExtendedASCII_186{186};
    const unsigned char ExtendedASCII_187{187};
    const unsigned char ExtendedASCII_188{188};
    const unsigned char ExtendedASCII_189{189};
    const unsigned char ExtendedASCII_190{190};
    const unsigned char ExtendedASCII_191{191};
    const unsigned char ExtendedASCII_192{192};
    const unsigned char ExtendedASCII_193{193};
    const unsigned char ExtendedASCII_194{194};
    const unsigned char ExtendedASCII_195{195};
    const unsigned char ExtendedASCII_196{196};
    const unsigned char ExtendedASCII_197{197};
    const unsigned char ExtendedASCII_198{198};
    const unsigned char ExtendedASCII_199{199};
    const unsigned char ExtendedASCII_200{200};
    const unsigned char ExtendedASCII_201{201};
    const unsigned char ExtendedASCII_202{202};
    const unsigned char ExtendedASCII_203{203};
    const unsigned char ExtendedASCII_204{204};
    const unsigned char ExtendedASCII_205{205};
    const unsigned char ExtendedASCII_206{206};
    const unsigned char ExtendedASCII_207{207};
    const unsigned char ExtendedASCII_208{208};
    const unsigned char ExtendedASCII_209{209};
    const unsigned char ExtendedASCII_210{210};
    const unsigned char ExtendedASCII_211{211};
    const unsigned char ExtendedASCII_212{212};
    const unsigned char ExtendedASCII_213{213};
    const unsigned char ExtendedASCII_214{214};
    const unsigned char ExtendedASCII_215{215};
    const unsigned char ExtendedASCII_216{216};
    const unsigned char ExtendedASCII_217{217};
    const unsigned char ExtendedASCII_218{218};
    const unsigned char ExtendedASCII_219{219};
    const unsigned char ExtendedASCII_220{220};
    const unsigned char ExtendedASCII_221{221};
    const unsigned char ExtendedASCII_222{222};
    const unsigned char ExtendedASCII_223{223};
    const unsigned char ExtendedASCII_224{224};
    const unsigned char ExtendedASCII_225{225};
    const unsigned char ExtendedASCII_226{226};
    const unsigned char ExtendedASCII_227{227};
    const unsigned char ExtendedASCII_228{228};
    const unsigned char ExtendedASCII_229{229};
    const unsigned char ExtendedASCII_230{230};
    const unsigned char ExtendedASCII_231{231};
    const unsigned char ExtendedASCII_232{232};
    const unsigned char ExtendedASCII_233{233};
    const unsigned char ExtendedASCII_234{234};
    const unsigned char ExtendedASCII_235{235};
    const unsigned char ExtendedASCII_236{236};
    const unsigned char ExtendedASCII_237{237};
    const unsigned char ExtendedASCII_238{238};
    const unsigned char ExtendedASCII_239{239};
    const unsigned char ExtendedASCII_240{240};
    const unsigned char ExtendedASCII_241{241};
    const unsigned char ExtendedASCII_242{242};
    const unsigned char ExtendedASCII_243{243};
    const unsigned char ExtendedASCII_244{244};
    const unsigned char ExtendedASCII_245{245};
    const unsigned char ExtendedASCII_246{246};
    const unsigned char ExtendedASCII_247{247};
    const unsigned char ExtendedASCII_248{248};
    const unsigned char ExtendedASCII_249{249};
    const unsigned char ExtendedASCII_250{250};
    const unsigned char ExtendedASCII_251{251};
    const unsigned char ExtendedASCII_252{252};
    const unsigned char ExtendedASCII_253{253};
    const unsigned char ExtendedASCII_254{254};
    const unsigned char ExtendedASCII_255{255};

    extern UINT8 CurrentWinColor;

    extern COORD CursorCoords;

    extern HHOOK KeyboardHook;

    extern HANDLE hstdout;
    extern HANDLE StdInHandle;

    extern CONSOLE_SCREEN_BUFFER_INFOEX csbiEX;

    extern void Color(uint8_t);
    extern void Color(uint8_t, uint8_t);
    extern void ClearConsoleToEndOfLine();
    extern void ClearScreen();
    extern void SetCursor(SHORT, SHORT);
    extern void DrawInfoBox(unsigned int, unsigned int, std::string, std::string);
    extern void DisplayInfo(unsigned int, unsigned int, unsigned int, std::string);
    extern void ShowConsoleCursor(bool);

    extern COORD GetCursor();

    extern unsigned int GetKey();

    extern LRESULT CALLBACK  Keyboard(int, WPARAM, LPARAM);

    extern std::string rtrim(std::string, std::string);
    extern std::string ltrim(std::string, std::string);
    extern std::string  trim(std::string, std::string);

    extern std::string Get_File_Contents(const std::string);
    extern std::vector<std::string_view> SplitStringToVector(std::string_view, std::string_view);
}

#endif
