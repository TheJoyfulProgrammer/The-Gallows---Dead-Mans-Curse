#ifndef GALLOWS_H
#define GALLOWS_H

#include <windows.h>

namespace Gallows
{
    extern const char BlankFiller;

    extern const unsigned char MaxNumOfPalettes;

    enum {
        CategoryMenu,
        PlayScreen,
        EndScreen
    };

    struct WordList{
        std::string FileName;
        std::string DisplayName;
    };

    extern bool PlayScreenEnd;
    extern bool RefreshCatList;

    extern int NumberOfElementsMissingOnLastRow;
    extern int CategoryListOutSideMargins;
    extern int CategoryIndexMaxWidth;
    extern int CategoryIndexWidthMargin;
    extern int ScreenIndex;

    extern long int WordListChosen;
    extern long int WordListChosenTemp;
    extern long int MaxCategoryRows;
    extern long int TopLeftSelection;
    extern long int LastIndexOnScreen;
    extern long int MaxColumns;
    extern long int CurrentCodePage;

    extern long long int CurrentWordIndex;
    extern long long int SelectedWordIndex;

    extern COORD CursorAfterHeader;
    extern COORD CursorNumberOfGuesses;
    extern COORD CursorSecretWord;
    extern COORD CursorSelectALetter;
    extern COORD CursorLetterList;
    extern COORD CursorAfterLetterList;
    extern COORD CursorSecretMessage;
    extern COORD CursorAfterCatHeader;
    extern COORD NewConsoleBufferDimensions;
    extern COORD MaximumConsoleWindowSize;

    extern char ConsoleTitle[];
    extern char CurrentPalette;

    extern unsigned char LetterWheel[26];

    extern COLORREF ColorTable[3][16];

    extern std::string IntroductionBoxTitle;
    extern std::string BoxMessage;
    extern std::string SelectALetterMessage;
    extern std::string Filler;
    extern std::string SecretMessageTitle;
    extern std::string CategoryDirectory;

    extern void SetPalette(UINT8 PaletteNum);
    extern void EnhanceHiddenMessage(std::string, COORD);
    extern void ShowLetterStrip(COORD);
    extern void DrawLetterBox(COORD, unsigned int);
    extern void PrintExecutionMessage();
    extern void LoadCategoryLists();
    extern void DrawCategoryMenuItem(long int, bool);
    extern void DrawCategoryMenuList();
    extern void SortCategoryList();

    extern int letterFill(char, std::string, std::string &);

    extern std::vector<WordList> WordLists;

}

#endif

