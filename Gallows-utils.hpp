#ifndef GALLOWS_H
#define GALLOWS_H

#include <windows.h>

namespace Gallows
{
    enum {
        CategoryMenu,
        PlayScreen,
        EndScreen
    };

    extern bool PlayScreenEnd;
    extern int NumberOfElementsMissingOnLastRow;
    extern int CategoryListOutSideMargins;
    extern int CategoryIndexMaxWidth;
    extern int CategoryIndexWidthMargin;

    extern long int WordListChosen;
    extern long int WordListChosenTemp;
    extern long long int CurrentWordIndex;
    extern long long int SelectedWordIndex;

    extern COORD CursorAfterHeader;
    extern COORD CursorNumberOfGuesses;
    extern COORD CursorSecretWord;
    extern COORD CursorSelectALetter;
    extern COORD CursorLetterList;
    extern COORD CursorAfterLetterList;
    extern COORD CursorSecretMessage;

    extern bool RefreshCatList;
    extern int ScreenIndex;

    extern long int MaxCategoryRows;
    extern long int TopLeftSelection;
    extern long int LastIndexOnScreen;
    extern long int MaxColumns;
    extern COORD CursorAfterCatHeader;

    extern const char BlankFiller;
    extern char ConsoleTitle[];

    extern COORD NewConsoleBufferDimensions;
    extern SMALL_RECT NewsrWindow;
    extern COORD MaximumConsoleWindowSize;

    extern char CurrentPalette;
    extern const unsigned char MaxNumOfPalettes;

    extern long int CurrentCodePage;

    extern COLORREF ColorTable[3][16];
    extern unsigned char LetterWheel[26];

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
    extern int letterFill(char, std::string, std::string &);

    extern void PrintExecutionMessage();

    struct WordList{
        std::string FileName;
        std::string DisplayName;
    };

    extern std::vector<WordList> WordLists;

    extern void LoadCategoryLists();
    extern void DrawCategoryMenuItem(long int, bool);
    extern void DrawCategoryMenuList();
    extern void SortCategoryList();
}

#endif

