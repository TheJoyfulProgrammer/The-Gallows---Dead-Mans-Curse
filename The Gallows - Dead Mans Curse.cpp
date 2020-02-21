//  GNU General Public License v3.0
//  The Gallows - Dead Mans Curse
//  DBT & Walter Whitman (The Joyful Programmer)

#include <algorithm>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>
#include <windows.h>
#include "Gallows-utils.hpp"
#include "tjp-utils.hpp"

void SetUpGame();
void Category_List_Check_Arrow_Up(unsigned int);
void Category_List_Check_Arrow_Down(unsigned int);
void Category_List_Check_Arrow_Left(unsigned int);
void Category_List_Check_Arrow_Right(unsigned int);
void DrawCategoryInfoBox();
void PlayGame();
void EndGame();

long int ShowCategoryMenu();

int main(){

    bool ExitGame{false};

    SetUpGame();

    do
    {
        switch(Gallows::ScreenIndex)
        {
            case Gallows::CategoryMenu:

                ShowCategoryMenu();
                break;

            case Gallows::PlayScreen:

                PlayGame();
                break;

            case Gallows::EndScreen:

                EndGame();
                ExitGame = true;
                break;
        }
    } while(ExitGame == false);

    return 0;
}



void SetUpGame()
{
    srand (time(NULL));

    if (! SetConsoleMode(tjpUtils::StdInHandle, ENABLE_EXTENDED_FLAGS | ENABLE_INSERT_MODE))
    {
        std::cout << "Unable to Set Windows Console Mode";
        ExitProcess(0);
    }

    tjpUtils::ShowConsoleCursor(false);

    Gallows::SetPalette(Gallows::CurrentPalette);

    SetConsoleTitle(Gallows::ConsoleTitle);

    Gallows::LoadCategoryLists();
    Gallows::SortCategoryList();
}


long int ShowCategoryMenu()
{
    bool CategoryExit{false};
    unsigned int Key;

    tjpUtils::Color(0, 8);
    tjpUtils::ClearScreen();

    Gallows::ScreenIndex = Gallows::CategoryMenu;

    DrawCategoryInfoBox();

    Gallows::MaxCategoryRows = Gallows::MaximumConsoleWindowSize.Y - 3 - Gallows::CursorAfterCatHeader.Y;
    Gallows::CategoryIndexMaxWidth = (Gallows::MaximumConsoleWindowSize.X - (Gallows::CategoryListOutSideMargins * 2)) / Gallows::MaxColumns;
    Gallows::RefreshCatList = true;

    do
    {
        Gallows::LastIndexOnScreen = Gallows::MaxCategoryRows * Gallows::MaxColumns + Gallows::TopLeftSelection - 1;

        if(Gallows::LastIndexOnScreen > (int)Gallows::WordLists.size()) Gallows::LastIndexOnScreen = (int)Gallows::WordLists.size();
        if(Gallows::RefreshCatList == true) Gallows::DrawCategoryMenuList();

        Gallows::DrawCategoryMenuItem(Gallows::WordListChosen, true);

        Gallows::TopLeftSelection == 0 ? tjpUtils::Color(0, 4) : tjpUtils::Color(0, 14);
        tjpUtils::SetCursor(4, Gallows::MaximumConsoleWindowSize.Y - 2);
        std::cout << "<== MORE";

        Gallows::LastIndexOnScreen < ((int)Gallows::WordLists.size() - 1) ? tjpUtils::Color(0, 14) : tjpUtils::Color(0, 4);
        tjpUtils::SetCursor(Gallows::MaximumConsoleWindowSize.X - 12, Gallows::MaximumConsoleWindowSize.Y - 2);
        std::cout << "MORE ==>";

        Key = tjpUtils::GetKey();

        if((Key >= tjpUtils::vkArrowLeft) & (Key <= tjpUtils::vkArrowDown))
        {
            Gallows::DrawCategoryMenuItem(Gallows::WordListChosen, false);
            Gallows::NumberOfElementsMissingOnLastRow = Gallows::MaxCategoryRows - (Gallows::LastIndexOnScreen % Gallows::MaxCategoryRows + 1);

            Category_List_Check_Arrow_Up(Key);
            Category_List_Check_Arrow_Down(Key);
            Category_List_Check_Arrow_Left(Key);
            Category_List_Check_Arrow_Right(Key);
        }

        if(Key == tjpUtils::vkEsc)
        {
            CategoryExit = true;
            Gallows::ScreenIndex = Gallows::EndScreen;

            break;
        }

        if(Key == tjpUtils::vkReturn)
        {
            CategoryExit = true;
            Gallows::ScreenIndex = Gallows::PlayScreen;
        }

    } while ( CategoryExit == false );

    return 0;
}




void Category_List_Check_Arrow_Up(unsigned int Key)
{
    if((Key == tjpUtils::vkArrowUp) & (Gallows::WordListChosen > 0))
    {
        if((Gallows::WordListChosen == Gallows::TopLeftSelection) & (Gallows::TopLeftSelection > 0))
        {
            Gallows::TopLeftSelection -= Gallows::MaxCategoryRows;
            Gallows::LastIndexOnScreen -= (Gallows::MaxCategoryRows - Gallows::NumberOfElementsMissingOnLastRow);
            Gallows::RefreshCatList = true;
        }

        Gallows::WordListChosen--;
    }
}



void Category_List_Check_Arrow_Down(unsigned int Key)
{
    if((Key == tjpUtils::vkArrowDown) & (Gallows::WordListChosen < (int)Gallows::WordLists.size() - 1))
    {
        if((Gallows::WordListChosen == Gallows::LastIndexOnScreen) & (Gallows::LastIndexOnScreen < (int)Gallows::WordLists.size() - 1))
        {
            Gallows::TopLeftSelection += Gallows::MaxCategoryRows;
            Gallows::LastIndexOnScreen += Gallows::MaxCategoryRows;

            if(Gallows::LastIndexOnScreen > ((int)Gallows::WordLists.size() - 1))
            {
                Gallows::LastIndexOnScreen = Gallows::WordLists.size() - 1;
            }

            Gallows::RefreshCatList = true;
        }

        Gallows::WordListChosen++;
    }
}



void Category_List_Check_Arrow_Left(unsigned int Key)
{
    if(Key == char(tjpUtils::vkArrowLeft))
    {
        if(((Gallows::WordListChosen - Gallows::MaxCategoryRows) < Gallows::TopLeftSelection) & (Gallows::TopLeftSelection > 0))
        {
            Gallows::TopLeftSelection -= Gallows::MaxCategoryRows;
            Gallows::LastIndexOnScreen -= Gallows::MaxCategoryRows;
            Gallows::LastIndexOnScreen += Gallows::NumberOfElementsMissingOnLastRow;
            Gallows::RefreshCatList = true;
        }

        Gallows::WordListChosen -= Gallows::MaxCategoryRows;

        if(Gallows::WordListChosen < 0) Gallows::WordListChosen = 0;
    }
}




void Category_List_Check_Arrow_Right(unsigned int Key)
{
    if(Key == char(tjpUtils::vkArrowRight))
    {
        if(((Gallows::WordListChosen + Gallows::MaxCategoryRows) > Gallows::LastIndexOnScreen) & (Gallows::LastIndexOnScreen < ((int)Gallows::WordLists.size() - 1)))
        {
            Gallows::TopLeftSelection += Gallows::MaxCategoryRows;
            Gallows::LastIndexOnScreen += Gallows::MaxCategoryRows;

            if(Gallows::LastIndexOnScreen > ((int)Gallows::WordLists.size() - 1)) Gallows::LastIndexOnScreen = (int)Gallows::WordLists.size() - 1;

            Gallows::RefreshCatList = true;
        }

        Gallows::WordListChosen += Gallows::MaxCategoryRows;

        if(Gallows::WordListChosen > (int)Gallows::WordLists.size() - 1)
        {
            Gallows::WordListChosen = Gallows::WordLists.size() - 1;
        }
    }
}



void DrawCategoryInfoBox()
{
        Gallows::BoxMessage = "Hello, you cursed death row inmate! I have " + std::to_string(Gallows::WordLists.size()) + " mystery boxes of messages to chose from. "
                              "Which one would you like to try your luck with?\n\nTo move through the selections, simply use the arrow keys on your keyboard, "
                              "or use your mouse. ";

        if((int)Gallows::WordLists.size() > Gallows::MaxCategoryRows * Gallows::MaxColumns) Gallows::BoxMessage += "If your mouse has a scroll wheel, you can use it to scroll the category list. ";

        Gallows::BoxMessage += "To play a particular mystery box, press <return>/<enter>, or click on it with your mouse.\n\nYou can press <ESC> to end the game.";

        tjpUtils::Color(4, 15);
        tjpUtils::DrawInfoBox(Gallows::MaximumConsoleWindowSize.X, 1, "PICK A CATEGORY", Gallows::BoxMessage);

        Gallows::CursorAfterCatHeader = tjpUtils::GetCursor();
        Gallows::CursorAfterCatHeader.X = Gallows::CategoryListOutSideMargins;
        Gallows::CursorAfterCatHeader.Y += 1;
}



void PlayGame()
{
    bool StillPlaying{true};
    bool DidWin{false};
    bool Replay{true};

    int NumberOfGuessesLeft;
    int LetterMatches;

    unsigned int Key;

    long long int Iterator1;

    std::string word;
    std::string HiddenMessage;
    std::string ClearLine;
    std::string LoadedWordList;
    std::vector<std::string_view> Words;

    ClearLine.resize(Gallows::MaximumConsoleWindowSize.X, tjpUtils::vkSpace);

    Words.clear();
    LoadedWordList = tjpUtils::Get_File_Contents(Gallows::CategoryDirectory + Gallows::WordLists[Gallows::WordListChosen].FileName);
    Words = tjpUtils::SplitStringToVector(LoadedWordList, "\r\n");

    do
    {
        StillPlaying = true;
        Gallows::PlayScreenEnd = false;

        Gallows::ScreenIndex = Gallows::PlayScreen;

        for(Iterator1 = 0; Iterator1 < 26; Iterator1++) Gallows::LetterWheel[Iterator1] = 0;

        NumberOfGuessesLeft = 6;

        if(Gallows::CurrentWordIndex == (int)Words.size())
        {
            for(Gallows::CurrentWordIndex = 0; Gallows::CurrentWordIndex < (int)Words.size(); Gallows::CurrentWordIndex++)
            {
                Gallows::SelectedWordIndex = rand() % (Words.size() - Gallows::CurrentWordIndex) + Gallows::CurrentWordIndex;
                std::swap(Words[Gallows::CurrentWordIndex], Words[Gallows::SelectedWordIndex]);
            }
            Gallows::CurrentWordIndex = 0;
        }

        Gallows::SelectedWordIndex = rand() % (Words.size() - Gallows::CurrentWordIndex) + Gallows::CurrentWordIndex;
        word = Words[Gallows::SelectedWordIndex];

        tjpUtils::Color(0, 8);
        tjpUtils::ClearScreen();

        std::swap(Words[Gallows::CurrentWordIndex], Words[Gallows::SelectedWordIndex]);

        Gallows::CurrentWordIndex++;

        transform(word.begin(), word.end(), word.begin(), ::toupper);
        HiddenMessage.clear();
        HiddenMessage.resize (word.length(), Gallows::BlankFiller);

        // SHOW ALL NON-LETTERS SINCE USERS CAN'T SELECT THEM
        for(Iterator1 = 0; Iterator1 < (int)word.length(); Iterator1++)
        {
            if((word[Iterator1] < tjpUtils::vkCapA) | (word[Iterator1] > tjpUtils::vkCapZ))
            {
                HiddenMessage[Iterator1] = word[Iterator1];
            }
        }

        Gallows::BoxMessage = "December 31st, 1877 (A day that repeats forever)\n\nYou have been convicted of cattle theft, which is punishable by death, and today is "
                                     "your day of execution. You are the last execution of the year and many people have come to watch.\n\n"
                                     "As the hangman leads you to the gallows, a mysterious cloaked figure approaches and speaks to your executioner, "
                                     "who takes a step back so the stranger can talk to you. \"I know you are innocent and I can prove it, but only if you "
                                     "solve one little mystery for me.\" says the stranger. \"In this mystical box, there are " + std::to_string(Words.size()) + " "
                                     "magical parchments with writing on them. You must select one and solve the message by guessing the letters within. If "
                                     "you guess incorrectly " + std::to_string(NumberOfGuessesLeft) + " times, then you will be hanged.\"\n\n"
                                     "You place your hand into the mysterious box and after shuffling through the parchments, you finally grab one.\n\n"
                                     "Your only clue: The secret message has " + std::to_string(word.length()) + " characters in it.";

        tjpUtils::Color(4, 15);
        tjpUtils::DrawInfoBox(Gallows::MaximumConsoleWindowSize.X, 1, "(CATEGORY: " + Gallows::WordLists[Gallows::WordListChosen].DisplayName + ")", Gallows::BoxMessage);

        Gallows::CursorAfterHeader = tjpUtils::GetCursor();

        Gallows::CursorSecretWord.X = (Gallows::MaximumConsoleWindowSize.X - Gallows::SecretMessageTitle.length()) / 2;
        Gallows::CursorSecretWord.Y = Gallows::CursorAfterHeader.Y + 2;

        Gallows::CursorSecretMessage.X = (Gallows::MaximumConsoleWindowSize.X - word.length() * 2 - 2) / 2;
        Gallows::CursorSecretMessage.Y = Gallows::CursorSecretWord.Y + 2;

        Gallows::CursorSelectALetter.X = 0;
        Gallows::CursorSelectALetter.Y = Gallows::CursorSecretWord.Y + 6;

        Gallows::CursorLetterList.X = 0;
        Gallows::CursorLetterList.Y = Gallows::CursorSelectALetter.Y + 1;

        Gallows::CursorAfterLetterList.X = 0;
        Gallows::CursorAfterLetterList.Y = Gallows::CursorLetterList.Y + 3;

        Gallows::CursorNumberOfGuesses.X = 2;
        Gallows::CursorNumberOfGuesses.Y = Gallows::CursorAfterLetterList.Y + 1;

        Gallows::ShowLetterStrip(Gallows::CursorLetterList);

        do
        {
            tjpUtils::Color(0, 13);
            tjpUtils::SetCursor(Gallows::CursorNumberOfGuesses.X, Gallows::CursorNumberOfGuesses.Y);

            std::cout << "You have " << NumberOfGuessesLeft << " guess";
            if(NumberOfGuessesLeft > 1) std::cout << "es";
            std::cout << " left. Choose your next letter wisely!  ";

            tjpUtils::Color(0, 8);
            tjpUtils::SetCursor(Gallows::CursorSecretWord.X, Gallows::CursorSecretWord.Y);
            std::cout << Gallows::SecretMessageTitle;

            tjpUtils::SetCursor(Gallows::CursorSecretMessage.X, Gallows::CursorSecretMessage.Y);
            Gallows::EnhanceHiddenMessage(HiddenMessage, tjpUtils::GetCursor());

            Gallows::Filler.clear();
            Gallows::Filler.resize(Gallows::MaximumConsoleWindowSize.X, tjpUtils::ExtendedASCII_223);
            tjpUtils::SetCursor(0, Gallows::CursorLetterList.Y + 3);
            tjpUtils::Color(0, 3);
            std::cout << Gallows::Filler;

            Gallows::Filler.clear();
            Gallows::Filler.resize(Gallows::MaximumConsoleWindowSize.X, tjpUtils::ExtendedASCII_220);
            tjpUtils::SetCursor(0, Gallows::CursorSelectALetter.Y);
            tjpUtils::Color(0, 3);
            std::cout << Gallows::Filler;

            tjpUtils::Color(3, 14);
            tjpUtils::SetCursor(Gallows::CursorSelectALetter.X, Gallows::CursorSelectALetter.Y);
            std::cout << Gallows::SelectALetterMessage;

            do
            {
                do
                {
                    tjpUtils::SetCursor(0, Gallows::MaximumConsoleWindowSize.Y - 1);
                    Key = tjpUtils::GetKey();
                    if((Key > tjpUtils::vkApostraphy) & (Key < tjpUtils::vkLeftCurlyBracket)) Key -= tjpUtils::vkSpace;
                } while((Key < tjpUtils::vkCapA) | (Key > tjpUtils::vkCapZ));
            } while (Gallows::LetterWheel[Key - tjpUtils::vkCapA]);

            Gallows::LetterWheel[Key - tjpUtils::vkCapA] = 1;
            Gallows::LetterWheel[Key - tjpUtils::vkCapA] == 1 ? tjpUtils::Color(0, 2) : tjpUtils::Color(1, 10);
            Gallows::DrawLetterBox(Gallows::CursorLetterList, Key - tjpUtils::vkCapA);

            LetterMatches = Gallows::letterFill(Key, word, HiddenMessage);

            if(LetterMatches == 0)
            {
                NumberOfGuessesLeft--;
            }

            if (word == HiddenMessage)
            {
                DidWin = true;
                StillPlaying = false;
            }

            if (NumberOfGuessesLeft < 1)
            {
                DidWin = false;
                StillPlaying = false;
            }

        } while (StillPlaying == true);

        tjpUtils::Color(0, 8);
        tjpUtils::SetCursor(Gallows::CursorSecretWord.X, Gallows::CursorSecretWord.Y);
        std::cout << Gallows::SecretMessageTitle;

        tjpUtils::SetCursor(Gallows::CursorSecretMessage.X, Gallows::CursorSecretMessage.Y);
        Gallows::EnhanceHiddenMessage(HiddenMessage, tjpUtils::GetCursor());

        tjpUtils::SetCursor(Gallows::CursorNumberOfGuesses.X, Gallows::CursorNumberOfGuesses.Y);
        tjpUtils::Color(0, 13);
        std::cout << ClearLine;

        if(DidWin == true)
        {
            tjpUtils::SetCursor(Gallows::CursorAfterLetterList.X, Gallows::CursorAfterLetterList.Y + 1);

            Gallows::BoxMessage = "Very impressive! Since you solved this clue, I will turn myself in and inform the guards that it "
                                  "was I who stole the cows. Yes, they will arrest me and place me in prison, but when midnight comes, "
                                  "I will be a free man and you will be back in prison awaiting your execution. You see, this day "
                                  "resets itself at midnight, and it will continue to do so until you help me solve all the clues in "
                                  "these chests. If you are executed, the day will restart and you get to try again to save your life.";

            tjpUtils::DisplayInfo(Gallows::MaximumConsoleWindowSize.X, 1, 2, Gallows::BoxMessage);

        } else {

            tjpUtils::SetCursor(Gallows::CursorNumberOfGuesses.X, Gallows::CursorNumberOfGuesses.Y);

            std::cout << "You failed! But, for condolences, the message is: ";
            tjpUtils::Color(0, 15);
            std::cout << word;

            tjpUtils::SetCursor(Gallows::CursorAfterLetterList.X, Gallows::CursorAfterLetterList.Y + 2);
            Gallows::PrintExecutionMessage();
        }

        tjpUtils::Color(0, 10);
        tjpUtils::SetCursor(2, Gallows::MaximumConsoleWindowSize.Y - 2);
        std::cout << "Your day restarted. Would you like to continue playing this category from this mysterious box?: ";

        tjpUtils::SetCursor(Gallows::MaximumConsoleWindowSize.X - 10, Gallows::MaximumConsoleWindowSize.Y - 2);
        std::cout << "YES / NO";

        Gallows::PlayScreenEnd = true;

        do
        {
            Key = tjpUtils::GetKey();
            if((Key > tjpUtils::vkApostraphy) & (Key < 123)) Key -= 32;
        } while((Key != tjpUtils::vkCapN) & (Key != tjpUtils::vkCapY));

        Replay = true;

        if(Key == tjpUtils::vkCapN)
        {
            Replay = false;
            Gallows::ScreenIndex = Gallows::CategoryMenu;
        }

    } while(Replay == true);
}



void EndGame()
{
    tjpUtils::Color(0, 4);
    tjpUtils::ClearScreen();

    Gallows::BoxMessage = "You have chosen to wake up and come back to reality, so, you have been released from your never ending, always repeating "
                          "day of your execution. Go enjoy real life stuff, but don't forget about our adventures.\n\nThank you for playing another "
                          "great adventure by David Taylor and Walter Whitman (The Joyful Programmer)";

    tjpUtils::Color(4, 15);
    tjpUtils::SetCursor(2, 1);
    tjpUtils::DrawInfoBox(Gallows::MaximumConsoleWindowSize.X - 4, 1, "The Gallows (PC Game)", Gallows::BoxMessage);

    Gallows::CursorAfterHeader = tjpUtils::GetCursor();

    tjpUtils::SetCursor(2, Gallows::CursorAfterHeader.Y + 3);

    Gallows::BoxMessage = "Official YouTube Channel:\n"
                          "https://www.youtube.com/channel/UCMaZHJ05rj2F640hD6nOb4g\n\n"
                          "Official GitHub Page:\n"
                          "https://github.com/Notfromthisworld\n\n"
                          "Be sure to keeping checking my YouTube channel for new videos, and my GitHub page for updates to The Gallows (PC Game)";

    tjpUtils::Color(1, 8);
    tjpUtils::DrawInfoBox(Gallows::MaximumConsoleWindowSize.X - 4, 1, "David Taylor's - The Gallows (PC Game) - Links", Gallows::BoxMessage);

    Gallows::CursorAfterHeader = tjpUtils::GetCursor();

    tjpUtils::SetCursor(2, Gallows::CursorAfterHeader.Y + 3);

    Gallows::BoxMessage = "My YouTube Channel:\n"
                          "https://www.youtube.com/thejoyfulprogrammer\n\n"
                          "My GitHub Page:\n"
                          "https://github.com/TheJoyfulProgrammer\n\n"
                          "My Website:\n"
                          "https://www.TheJoyfulProgrammer.com/\n\n"
                          "Be sure to keeping checking my YouTube channel for new videos, and my GitHub page for updates to The Gallows (PC Game)";

    tjpUtils::DrawInfoBox(Gallows::MaximumConsoleWindowSize.X - 4, 1, "Walter Whitman's (aka The Joyful Programmer) - Links", Gallows::BoxMessage);

    tjpUtils::GetKey();
}
