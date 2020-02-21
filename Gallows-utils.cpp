#include <algorithm>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <vector>
#include <windows.h>
#include "Gallows-utils.hpp"
#include "tjp-utils.hpp"

namespace Gallows
{
    const char BlankFiller = tjpUtils::ExtendedASCII_177;
    const unsigned char MaxNumOfPalettes{2};

    bool PlayScreenEnd;
    bool RefreshCatList{true};

    char ConsoleTitle[] = "The Gallows - Dead Mans Curse";
    char CurrentPalette = 0;

    unsigned char LetterWheel[26]{0};

    int NumberOfElementsMissingOnLastRow;
    int CategoryListOutSideMargins{2};
    int CategoryIndexMaxWidth;
    int CategoryIndexWidthMargin{2};
    int ScreenIndex;

    long int WordListChosen{0};
    long int WordListChosenTemp{0};
    long int MaxCategoryRows;
    long int TopLeftSelection{0};
    long int LastIndexOnScreen;
    long int MaxColumns{3};
    long int CurrentCodePage{0};

    long long int CurrentWordIndex{0};
    long long int SelectedWordIndex;

    COORD CursorAfterHeader;
    COORD CursorNumberOfGuesses;
    COORD CursorSecretWord;
    COORD CursorSelectALetter;
    COORD CursorLetterList;
    COORD CursorAfterLetterList;
    COORD CursorSecretMessage;
    COORD CursorAfterCatHeader;
    COORD NewConsoleBufferDimensions = {130, 40};
    COORD MaximumConsoleWindowSize = {130, 40};

    SMALL_RECT NewConsoleWindowRect = {0, 0, 130, 40};

    COLORREF ColorTable[3][16] =
    {
        {
            RGB(   0,  16,   0),
            RGB(   0,  32,   0),
            RGB(   0,  48,   0),
            RGB(   0,  64,   0),
            RGB(   0,  80,   0),
            RGB(   0,  96,   0),
            RGB(   0, 112,   0),
            RGB(   0, 128,   0),
            RGB(   0, 144,   0),
            RGB(   0, 160,   0),
            RGB(   0, 176,   0),
            RGB(   0, 192,   0),
            RGB(   0, 208,   0),
            RGB(   0, 224,   0),
            RGB(   0, 240,   0),
            RGB( 240, 255, 240)
        },
        {
            RGB(  16,  16,  16),
            RGB(  32,  32,  32),
            RGB(  48,  48,  48),
            RGB(  64,  64,  64),
            RGB(  80,  80,  80),
            RGB(  96,  96,  96),
            RGB( 112, 112, 112),
            RGB( 128, 128, 128),
            RGB( 144, 144, 144),
            RGB( 160, 160, 160),
            RGB( 176, 176, 176),
            RGB( 192, 192, 192),
            RGB( 208, 208, 208),
            RGB( 224, 224, 224),
            RGB( 240, 240, 240),
            RGB( 255, 255, 255)
        },
        {
            RGB(  42,  12,   0),
            RGB(  56,  18,   0),
            RGB(  70,  24,   0),
            RGB(  83,  30,   0),
            RGB(  97,  36,   0),
            RGB( 111,  42,   0),
            RGB( 124,  48,   0),
            RGB( 138,  54,   0),
            RGB( 151,  60,   0),
            RGB( 205,  84,   0),
            RGB( 178,  72,   0),
            RGB( 192,  78,   0),
            RGB( 205,  84,   0),
            RGB( 219,  90,   0),
            RGB( 233,  96,   0),
            RGB( 247, 102,   0)
        }
    };

    std::string IntroductionBoxTitle = "The Gallows - Dead Mans Curse";
    std::string BoxMessage;
    std::string SelectALetterMessage{"  SELECT A LETTER FROM THE HIGHLIGHTED BOXES BELOW  "};
    std::string Filler;
    std::string SecretMessageTitle{"YOUR SECRET MESSAGE"};
    std::string CategoryDirectory{"CategoryWordLists/"};
    std::string CategoryListFileName{CategoryDirectory + "CategoryList.gcl"};

    std::vector<WordList> WordLists;



    void DrawCategoryMenuList()
    {
        long long int Iterator1;
        int XCoord;
        int YCoord;

        for(Iterator1 = Gallows::TopLeftSelection; Iterator1 <= Gallows::LastIndexOnScreen; Iterator1++)
        {
            Gallows::DrawCategoryMenuItem(Iterator1, false);
        }

        if((Gallows::LastIndexOnScreen % Gallows::MaxCategoryRows + 1) < Gallows::MaxCategoryRows)
        {
            Gallows::Filler.clear();
            Gallows::Filler.resize(Gallows::CategoryIndexMaxWidth, tjpUtils::vkSpace);

            XCoord = Gallows::CategoryIndexMaxWidth * (Gallows::MaxColumns - 1) + Gallows::CursorAfterCatHeader.X;

            for(Iterator1 = Gallows::LastIndexOnScreen % Gallows::MaxCategoryRows + 1; Iterator1 < Gallows::MaxCategoryRows; Iterator1++)
            {
                YCoord = Iterator1 + Gallows::CursorAfterCatHeader.Y;

                tjpUtils::SetCursor(XCoord, YCoord);
                std::cout << Gallows::Filler;
            }
        }

        Gallows::RefreshCatList = false;
    }



    void DrawCategoryMenuItem(long int ItemSelection, bool Highlighted)
    {
        int XCoord;
        int YCoord;
        int MessageLength;
        int MaxMessageLength;

        MaxMessageLength = (Gallows::CategoryIndexMaxWidth - (Gallows::CategoryIndexWidthMargin * 2));

        Gallows::Filler.clear();
        Gallows::Filler.resize(Gallows::CategoryIndexMaxWidth, tjpUtils::vkSpace);

        if((int)Gallows::WordLists[ItemSelection].DisplayName.size() > MaxMessageLength)
        {
            MessageLength = MaxMessageLength - 3;
            Gallows::Filler.replace(MessageLength + 2, 3, "...");
        } else {
            MessageLength = Gallows::WordLists[ItemSelection].DisplayName.size();
        }

        Gallows::Filler.replace(Gallows::CategoryIndexWidthMargin, MessageLength, Gallows::WordLists[ItemSelection].DisplayName, 0, MessageLength);

        if(Highlighted == true)
        {
            Gallows::Filler[0] = '[';
            Gallows::Filler[Gallows::CategoryIndexMaxWidth - 1] = ']';
        }

        XCoord = (((ItemSelection - Gallows::TopLeftSelection) / Gallows::MaxCategoryRows) * Gallows::CategoryIndexMaxWidth) + Gallows::CursorAfterCatHeader.X;
        YCoord = ItemSelection % Gallows::MaxCategoryRows + Gallows::CursorAfterCatHeader.Y;

        tjpUtils::SetCursor(XCoord, YCoord);

        Highlighted != true ? tjpUtils::Color(0, 7) : tjpUtils::Color(1, 14);

        std::cout << Gallows::Filler;
    }



    void LoadCategoryLists()
    {
        int FirstFind;
        long long unsigned int Iterator1;

        std::string SplitDelimiters{","};
        std::string SplitSTVDelimiters{"\r\n"};
        std::string TrimDelimiters{" \t"};
        std::string FileName;
        std::string DisplayName;
        std::string TempTextFileHolder;
        std::vector<std::string_view> TempSplitTextFileHolder;

        TempTextFileHolder.clear();
        TempTextFileHolder = tjpUtils::Get_File_Contents(CategoryListFileName);
        TempSplitTextFileHolder = tjpUtils::SplitStringToVector(TempTextFileHolder, SplitSTVDelimiters);

        for(Iterator1 = 0; Iterator1 < TempSplitTextFileHolder.size(); Iterator1++)
        {
            FirstFind = TempSplitTextFileHolder[Iterator1].find_first_of(SplitDelimiters, 0);

            FileName = TempSplitTextFileHolder[Iterator1].substr(0, FirstFind);
            DisplayName = TempSplitTextFileHolder[Iterator1].substr(FirstFind + 1, std::string::npos);

            Gallows::WordLists.push_back(Gallows::WordList{tjpUtils::trim(FileName, TrimDelimiters), tjpUtils::trim(DisplayName, TrimDelimiters)});
        }
    }



    int letterFill(char guess, std::string secretword, std::string &guessword){

        int matches=0;

        for (int i = 0; i < (int)secretword.length(); i++)
        {

            if (guess == guessword[i])
            {
                matches--;
            } else if (guess == secretword[i]) {
                guessword[i] = guess;
                matches++;
            }
        }
        return matches;
    }




    void SetPalette(UINT8 PaletteNum)
    {
        std::size_t i;

        tjpUtils::csbiEX.cbSize = sizeof(tjpUtils::csbiEX);
        GetConsoleScreenBufferInfoEx(tjpUtils::hstdout, &tjpUtils::csbiEX);

        for(i = 0; i < 16; i++)
        {
            tjpUtils::csbiEX.ColorTable[i] = Gallows::ColorTable[PaletteNum][i];
        }

        tjpUtils::csbiEX.dwSize = Gallows::NewConsoleBufferDimensions;
        tjpUtils::csbiEX.srWindow = Gallows::NewConsoleWindowRect;
        tjpUtils::csbiEX.dwMaximumWindowSize = Gallows::MaximumConsoleWindowSize;

        SetConsoleScreenBufferInfoEx(tjpUtils::hstdout, &tjpUtils::csbiEX);
    }



    void EnhanceHiddenMessage(std::string HiddenMessage, COORD CursorPos)
    {
        unsigned int Iterator1;

        tjpUtils::Color(0, 3);

        tjpUtils::SetCursor(CursorPos.X, CursorPos.Y - 1);
        std::cout << tjpUtils::ExtendedASCII_218;

        tjpUtils::SetCursor(CursorPos.X, CursorPos.Y + 1);
        std::cout << tjpUtils::ExtendedASCII_192;

        for(Iterator1 = 0; Iterator1 < HiddenMessage.length() - 1; Iterator1++)
        {
            tjpUtils::SetCursor(CursorPos.X + Iterator1 * 2 + 1, CursorPos.Y - 1);
            std::cout << tjpUtils::ExtendedASCII_196 << tjpUtils::ExtendedASCII_194;

            tjpUtils::SetCursor(CursorPos.X + Iterator1 * 2 + 1, CursorPos.Y + 1);
            std::cout << tjpUtils::ExtendedASCII_196 << tjpUtils::ExtendedASCII_193;
        }

        tjpUtils::SetCursor(CursorPos.X + Iterator1 * 2 + 1, CursorPos.Y - 1);
        std::cout << tjpUtils::ExtendedASCII_196 << tjpUtils::ExtendedASCII_191;

        tjpUtils::SetCursor(CursorPos.X + Iterator1 * 2 + 1, CursorPos.Y + 1);
        std::cout << tjpUtils::ExtendedASCII_196 << tjpUtils::ExtendedASCII_217;

        tjpUtils::SetCursor(CursorPos.X, CursorPos.Y);
        std::cout << tjpUtils::ExtendedASCII_179;

        for(Iterator1 = 0; Iterator1 < HiddenMessage.length(); Iterator1++)
        {
            HiddenMessage[Iterator1] == Gallows::BlankFiller ? tjpUtils::Color(0, 4) : tjpUtils::Color(0, 15);
            std::cout << HiddenMessage[Iterator1];
            if(Iterator1 < (HiddenMessage.length() - 1)) std::cout << " ";
        }

        tjpUtils::Color(0, 3);
        std::cout << tjpUtils::ExtendedASCII_179;
    }



    void ShowLetterStrip(COORD CursorPos)
    {
        unsigned int Iterator1;

        for(Iterator1 = 0; Iterator1 < 26; Iterator1++)
        {
            Gallows::LetterWheel[Iterator1] == 1 ? tjpUtils::Color(0, 2) : tjpUtils::Color(1, 10);
            DrawLetterBox(CursorPos, Iterator1);
        }
    }



    void DrawLetterBox(COORD CursorPos, unsigned int CurrentLetter)
    {
        std::string LetterButtonTop{"\xDA\xC4\xC4\xC4\xBF"};
        std::string LetterButtonMiddle{"\xB3   \xB3"};
        std::string LetterButtonBottom{"\xC0\xC4\xC4\xC4\xD9"};

        tjpUtils::SetCursor(CursorPos.X + CurrentLetter * 5, CursorPos.Y);
        std::cout << LetterButtonTop;

        tjpUtils::SetCursor(CursorPos.X + CurrentLetter * 5, CursorPos.Y + 1);
        std::cout << LetterButtonMiddle;

        tjpUtils::SetCursor(CursorPos.X + CurrentLetter * 5, CursorPos.Y + 2);
        std::cout << LetterButtonBottom;

        tjpUtils::SetCursor(CursorPos.X + CurrentLetter * 5 + 2, CursorPos.Y + 1);
        std::cout << char(CurrentLetter + tjpUtils::vkCapA);
    }




    bool SortCategories(const WordList &lhs, const WordList &rhs) { return lhs.DisplayName < rhs.DisplayName; }

    void SortCategoryList()
    {
        sort(WordLists.begin(), WordLists.end(), SortCategories);
    }




    void PrintExecutionMessage()
    {
        tjpUtils::Color(0, 15);

        std::cout << R"( __   __                    _    _                           _____                                _                _   _   _   _ )" << "\n";
        std::cout << R"( \ \ / /                   | |  | |                         |  ___|                              | |              | | | | | | | |)" << "\n";
        std::cout << R"(  \ V /   ___    _   _     | |  | |   ___   _ __    ___     | |__   __  __   ___    ___   _   _  | |_    ___    __| | | | | | | |)" << "\n";
        std::cout << R"(   \ /   / _ \  | | | |    | |/\| |  / _ \ | '__|  / _ \    |  __|  \ \/ /  / _ \  / __| | | | | | __|  / _ \  / _` | | | | | | |)" << "\n";
        std::cout << R"(   | |  | (_) | | |_| |    \  /\  / |  __/ | |    |  __/    | |___   >  <  |  __/ | (__  | |_| | | |_  |  __/ | (_| | |_| |_| |_|)" << "\n";
        std::cout << R"(   \_/   \___/   \__,_|     \/  \/   \___| |_|     \___|    \____/  /_/\_\  \___|  \___|  \__,_|  \__|  \___|  \__,_| (_) (_) (_))" << "\n";
     }

}
