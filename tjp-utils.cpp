/*
    tjpUtils: Various utilities written by The Joyful Programmer
*/

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <windows.h>
#include "tjp-utils.hpp"
#include "Gallows-utils.hpp"

namespace tjpUtils
{
    UINT8 CurrentWinColor;

    COORD CursorCoords = {0, 0};

    HHOOK KeyboardHook;

    HANDLE StdInHandle = GetStdHandle( STD_INPUT_HANDLE );
    HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

    CONSOLE_SCREEN_BUFFER_INFOEX csbiEX;



    void Color(UINT8 Foreground)
    {
        tjpUtils::CurrentWinColor = (tjpUtils::CurrentWinColor & 0xF0) | (Foreground & 0x0F);
        SetConsoleTextAttribute(tjpUtils::hstdout, tjpUtils::CurrentWinColor);
    }



    void Color(uint8_t ForegroundColor, uint8_t BackgroundColor)
    {
        tjpUtils::CurrentWinColor = ((ForegroundColor & 0x0F) << 4) | (BackgroundColor & 0x0F);
        SetConsoleTextAttribute(tjpUtils::hstdout, tjpUtils::CurrentWinColor);
    }



    void ClearScreen()
    {
        DWORD cellCount;
        DWORD counter;

        cellCount = tjpUtils::csbiEX.dwSize.X * tjpUtils::csbiEX.dwSize.Y;

        FillConsoleOutputAttribute(tjpUtils::hstdout, tjpUtils::CurrentWinColor, cellCount, tjpUtils::CursorCoords, &counter);
        FillConsoleOutputCharacter(tjpUtils::hstdout, (TCHAR) ' ', cellCount, tjpUtils::CursorCoords, &counter);
        SetConsoleCursorPosition(tjpUtils::hstdout, tjpUtils::CursorCoords );

        tjpUtils::SetCursor(0, 0);
    }



    std::string Get_File_Contents(const std::string FileName)
    {
        std::ifstream CurrentFile(FileName, std::ios::in | std::ios::binary);

        if (CurrentFile)
        {
            std::string FileContents;

            CurrentFile.seekg(0, std::ios::end);

            FileContents.resize(CurrentFile.tellg());

            CurrentFile.seekg(0, std::ios::beg);
            CurrentFile.read(&FileContents[0], FileContents.size());
            CurrentFile.close();

            return(FileContents);
        } else {
            std::cout << "ERROR: Unable to load the dictionary file \"" << FileName << "\"!\n\n";
            tjpUtils::GetKey();

            exit(EXIT_FAILURE);
        }
    }



    std::vector<std::string_view> SplitStringToVector(std::string_view StringToConvert, std::string_view Delimiters)
    {
        std::vector<std::string_view> OutputVector;
        size_t FirstFind = 0;

        while (FirstFind < StringToConvert.size())
        {
            const auto SecondFind = StringToConvert.find_first_of(Delimiters, FirstFind);

            if (FirstFind != SecondFind) OutputVector.push_back(StringToConvert.substr(FirstFind, SecondFind - FirstFind));
            if (SecondFind == std::string_view::npos) break;

            FirstFind = SecondFind + 1;
        }

        return OutputVector;
    }





    std::string rtrim(std::string StringToTrim, std::string WhiteSpace)
    {
        StringToTrim.erase(StringToTrim.find_last_not_of(WhiteSpace) + 1);
        return StringToTrim;
    }

    std::string ltrim(std::string StringToTrim, std::string WhiteSpace)
    {
        StringToTrim.erase(0, StringToTrim.find_first_not_of(WhiteSpace));
        return StringToTrim;
    }

    std::string  trim(std::string StringToTrim, std::string WhiteSpace)
    {
        return ltrim(rtrim(StringToTrim, WhiteSpace), WhiteSpace);
    }



    VOID ErrorExit (std::string Message)
    {
        std::cout << Message << "\n";
        ExitProcess(0);
    }



    unsigned int GetKey()
    {
        COORD LetterBoxCoordinates;

        DWORD NumberOfEventsToRead;
        DWORD InOutModeToSet{ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_EXTENDED_FLAGS | ENABLE_INSERT_MODE};
        DWORD fdwSaveOldMode;
        DWORD Iterator1;

        INPUT_RECORD InputBuffer[128];

        long int CurrentCatMouseX;
        long int CurrentCatMouseY;

        short CurrentLetterBox{-1};
        short PreviousLetterBox{-1};

        int counter{0};

        unsigned int Key{0};

        LetterBoxCoordinates.X = 0;
        LetterBoxCoordinates.Y = Gallows::CursorLetterList.Y;

        if (! GetConsoleMode(tjpUtils::StdInHandle, &fdwSaveOldMode)) ErrorExit("Unable to Get Windows Console Mode");
        if (! SetConsoleMode(tjpUtils::StdInHandle, InOutModeToSet)) ErrorExit("Unable to Set Windows Console Mode");

        while (counter <= 1)
        {
            if (! ReadConsoleInput(tjpUtils::StdInHandle, InputBuffer, 128, &NumberOfEventsToRead)) ErrorExit("Unable to Read Windows Console Input");

            for (Iterator1 = 0; Iterator1 < NumberOfEventsToRead; Iterator1++)
            {
                switch(InputBuffer[Iterator1].EventType)
                {
                    case KEY_EVENT:

                        if(InputBuffer[Iterator1].EventType == KEY_EVENT && ((KEY_EVENT_RECORD&)InputBuffer[Iterator1].Event).bKeyDown)
                        {
                            Key = ((KEY_EVENT_RECORD&)InputBuffer[Iterator1].Event).wVirtualKeyCode;
                        }

                        FlushConsoleInputBuffer(tjpUtils::StdInHandle);

                        break;

                    case MOUSE_EVENT:

                        switch(Gallows::ScreenIndex)
                        {
                            case Gallows::CategoryMenu:

                                if((InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X >= Gallows::CategoryListOutSideMargins) &
                                   (InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X < (Gallows::CategoryIndexMaxWidth * Gallows::MaxColumns + Gallows::CategoryListOutSideMargins)) &
                                   (InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.Y >= Gallows::CursorAfterCatHeader.Y) &
                                   (InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.Y < (Gallows::CursorAfterCatHeader.Y + Gallows::MaxCategoryRows)))
                                {
                                    if((InputBuffer[Iterator1].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) & (Gallows::WordListChosen < (int)Gallows::WordLists.size())) Key = tjpUtils::vkReturn;

                                    if(InputBuffer[Iterator1].Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
                                    {
                                        CurrentCatMouseY = InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.Y - Gallows::CursorAfterCatHeader.Y;
                                        CurrentCatMouseX = (InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X - Gallows::CategoryListOutSideMargins) / Gallows::CategoryIndexMaxWidth;

                                        Gallows::WordListChosenTemp = CurrentCatMouseY + (CurrentCatMouseX * Gallows::MaxCategoryRows) + Gallows::TopLeftSelection;

                                        if(Gallows::WordListChosenTemp != Gallows::WordListChosen)
                                        {
                                            Gallows::DrawCategoryMenuItem(Gallows::WordListChosen, false);

                                            Gallows::WordListChosen = Gallows::WordListChosenTemp;
                                            if(Gallows::WordListChosen >= (long int)Gallows::WordLists.size()) Gallows::WordListChosen = (long int)Gallows::WordLists.size() - 1;

                                            Gallows::DrawCategoryMenuItem(Gallows::WordListChosen, true);
                                        }
                                    }
                                }

                                if(((InputBuffer[Iterator1].Event.MouseEvent.dwButtonState == tjpUtils::MouseScrollWheelDown) & (Gallows::TopLeftSelection > 0)) |
                                   ((InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.Y == (Gallows::MaximumConsoleWindowSize.Y - 2)) &
                                    ((InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X > 3) & (InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X < 14)) &
                                    (InputBuffer[Iterator1].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) & (Gallows::TopLeftSelection > 0)))
                                {
                                    tjpUtils::Color(4, 14);
                                    tjpUtils::SetCursor(4, Gallows::MaximumConsoleWindowSize.Y - 2);
                                    std::cout << "<== MORE";

                                    Gallows::NumberOfElementsMissingOnLastRow = Gallows::MaxCategoryRows - (Gallows::LastIndexOnScreen % Gallows::MaxCategoryRows + 1);

                                    Gallows::TopLeftSelection -= Gallows::MaxCategoryRows;
                                    Gallows::LastIndexOnScreen -= Gallows::MaxCategoryRows;
                                    Gallows::LastIndexOnScreen += Gallows::NumberOfElementsMissingOnLastRow;

                                    Gallows::WordListChosen -= Gallows::MaxCategoryRows;

                                    Gallows::DrawCategoryMenuList();
                                    Gallows::DrawCategoryMenuItem(Gallows::WordListChosen, true);

                                    Key = 1;
                                }

                                if(((InputBuffer[Iterator1].Event.MouseEvent.dwButtonState == tjpUtils::MouseScrollWheelUp) & (Gallows::LastIndexOnScreen < (int)Gallows::WordLists.size())) |
                                   ((InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.Y == (Gallows::MaximumConsoleWindowSize.Y - 2)) &
                                    (InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X > (Gallows::MaximumConsoleWindowSize.X - 12)) & (InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X < ((Gallows::MaximumConsoleWindowSize.X - 4))) &
                                    (InputBuffer[Iterator1].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) & (Gallows::LastIndexOnScreen < (int)Gallows::WordLists.size())))
                                {
                                    tjpUtils::Color(4, 14);
                                    tjpUtils::SetCursor(Gallows::MaximumConsoleWindowSize.X - 12, Gallows::MaximumConsoleWindowSize.Y - 2);
                                    std::cout << "MORE ==>";

                                    Gallows::TopLeftSelection += Gallows::MaxCategoryRows;
                                    Gallows::LastIndexOnScreen += Gallows::MaxCategoryRows;

                                    if(Gallows::LastIndexOnScreen >= (long int)Gallows::WordLists.size()) Gallows::LastIndexOnScreen = (long int)Gallows::WordLists.size();

                                    Gallows::WordListChosen += Gallows::MaxCategoryRows;
                                    if(Gallows::WordListChosen > Gallows::LastIndexOnScreen) Gallows::WordListChosen = Gallows::LastIndexOnScreen;

                                    Gallows::DrawCategoryMenuList();
                                    Gallows::DrawCategoryMenuItem(Gallows::WordListChosen, true);

                                    Key = 1;
                                }
                                break;

                            case Gallows::PlayScreen:

                                if(Gallows::PlayScreenEnd == false)
                                {
                                    PreviousLetterBox = CurrentLetterBox;

                                    if((InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.Y >= Gallows::CursorLetterList.Y) &
                                       (InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.Y < (Gallows::CursorLetterList.Y + 3)))
                                    {
                                        CurrentLetterBox = InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X / 5;

                                        if((PreviousLetterBox != CurrentLetterBox) & (Gallows::LetterWheel[PreviousLetterBox] == 0) & (PreviousLetterBox >= 0))
                                        {
                                            tjpUtils::Color(1, 10);
                                            Gallows::DrawLetterBox(LetterBoxCoordinates, (unsigned)PreviousLetterBox);

                                        }
                                    } else {

                                        CurrentLetterBox = -1;

                                        if((PreviousLetterBox != CurrentLetterBox) & (Gallows::LetterWheel[PreviousLetterBox] == 0) & (PreviousLetterBox >= 0))
                                        {
                                            tjpUtils::Color(1, 10);
                                            Gallows::DrawLetterBox(LetterBoxCoordinates, (unsigned)PreviousLetterBox);
                                            PreviousLetterBox = CurrentLetterBox;
                                        }
                                    }

                                    if((CurrentLetterBox >= 0) & (InputBuffer[Iterator1].Event.MouseEvent.dwEventFlags == MOUSE_MOVED) & (Gallows::LetterWheel[CurrentLetterBox] == 0))
                                    {
                                        tjpUtils::Color(4, 15);
                                        Gallows::DrawLetterBox(LetterBoxCoordinates, (unsigned)CurrentLetterBox);
                                    }

                                    if((InputBuffer[Iterator1].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) & (CurrentLetterBox >= 0))
                                    {
                                        Key = tjpUtils::vkCapA + CurrentLetterBox;
                                    }
                                } else {
                                    if((InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.Y == (Gallows::MaximumConsoleWindowSize.Y - 2)))
                                    {
                                        if((InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X > (Gallows::MaximumConsoleWindowSize.X - 11)) &
                                           (InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X < (Gallows::MaximumConsoleWindowSize.X - 8)) &
                                           (InputBuffer[Iterator1].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
                                        {
                                            Key = vkCapY;
                                        }
                                        if((InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X > (Gallows::MaximumConsoleWindowSize.X - 5)) &
                                           (InputBuffer[Iterator1].Event.MouseEvent.dwMousePosition.X < (Gallows::MaximumConsoleWindowSize.X - 2)) &
                                           (InputBuffer[Iterator1].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
                                        {
                                            Key = vkCapN;
                                        }

                                    }
                                }
                                break;
                        }
                        break;

                    case WINDOW_BUFFER_SIZE_EVENT:
                        Gallows::SetPalette(Gallows::CurrentPalette);
                        break;

                    case FOCUS_EVENT:
                        break;

                    case MENU_EVENT:
                        break;

                    default:
                        break;
                }
            }

            switch(Key)
            {
                case vkF5:
                    Gallows::CurrentPalette--;
                    if(Gallows::CurrentPalette < 0) Gallows::CurrentPalette = Gallows::MaxNumOfPalettes;
                    Gallows::SetPalette(Gallows::CurrentPalette);
                    Key = 0;
                    break;

                case vkF6:
                    Gallows::CurrentPalette++;
                    if(Gallows::CurrentPalette > Gallows::MaxNumOfPalettes) Gallows::CurrentPalette = 0;
                    Gallows::SetPalette(Gallows::CurrentPalette);
                    Key = 0;
                    break;
            }

            if(Key > char(0)) break;
        }

        SetConsoleMode(tjpUtils::StdInHandle, fdwSaveOldMode);

        return Key;
    }





    void DrawInfoBox(unsigned int Width, unsigned int Margin, std::string Title, std::string Message)
    {
        COORD CurrentPosition = GetCursor();

        size_t FirstFind = 0;
        size_t Position;
        size_t Iterator1;

        std::vector<std::string> MessageTokens;

        std::string Delimeters = "\n ";
        std::string BoxLineMessage;
        std::string LineTopMessage;
        std::string LineMiddleMessage;
        std::string LineBottomMessage;
        std::string NewTitle;

        LineTopMessage.resize(Width, ExtendedASCII_205);
        LineTopMessage[0] = ExtendedASCII_201;
        LineTopMessage[Width - 1] = ExtendedASCII_187;

        LineMiddleMessage.resize(Width, vkSpace);
        LineMiddleMessage[0] = ExtendedASCII_186;
        LineMiddleMessage[Width - 1] = ExtendedASCII_186;

        LineBottomMessage.resize(Width, ExtendedASCII_205);
        LineBottomMessage[0] = ExtendedASCII_200;
        LineBottomMessage[Width - 1] = ExtendedASCII_188;

        while (FirstFind < Message.size())
        {
            const auto SecondFind = Message.find_first_of(Delimeters, FirstFind);

            if ((FirstFind == SecondFind) && (Message[SecondFind] == '\n'))
            {
                MessageTokens.push_back(Message.substr(SecondFind, 1));
            }

            if (FirstFind != SecondFind)
            {
                MessageTokens.push_back(Message.substr(FirstFind, SecondFind - FirstFind));

                if (SecondFind < Message.size())
                {
                    if (Message.substr(SecondFind, 1) == "\n")
                    {
                        MessageTokens.push_back(Message.substr(SecondFind, 1));
                    }
                }
            }

            if (SecondFind == std::string::npos) break;

            FirstFind = SecondFind + 1;
        }

        NewTitle = " " + Title + " ";

        BoxLineMessage = LineTopMessage;

        Position = (Width - NewTitle.size()) / 2;
        BoxLineMessage.replace(Position, NewTitle.size(), NewTitle);

        SetCursor(CurrentPosition.X, CurrentPosition.Y);
        CurrentPosition.Y ++;
        std::cout << BoxLineMessage;

        BoxLineMessage = LineMiddleMessage;

        for (Iterator1 = 0; Iterator1 < Margin; Iterator1++)
        {
            SetCursor(CurrentPosition.X, CurrentPosition.Y);
            CurrentPosition.Y ++;
            std::cout << BoxLineMessage;
        }

        Position = 2 + Margin;

        for (Iterator1 = 0; Iterator1 < MessageTokens.size(); Iterator1++)
        {
            if((MessageTokens[Iterator1] == "\n") | ((MessageTokens[Iterator1].size() + Position) > (Width - Margin - 1)))
            {
                SetCursor(CurrentPosition.X, CurrentPosition.Y);
                CurrentPosition.Y ++;
                std::cout << BoxLineMessage;

                BoxLineMessage = LineMiddleMessage;
                Position = 2 + Margin;
            }

            if (MessageTokens[Iterator1] != "\n")
            {
                BoxLineMessage.replace(Position, MessageTokens[Iterator1].size(), MessageTokens[Iterator1]);
                Position += 1 + MessageTokens[Iterator1].size();
            }
        }

        SetCursor(CurrentPosition.X, CurrentPosition.Y);
        CurrentPosition.Y ++;
        std::cout << BoxLineMessage;

        for (Iterator1 = 0; Iterator1 < Margin; Iterator1++)
        {
            SetCursor(CurrentPosition.X, CurrentPosition.Y);
            CurrentPosition.Y ++;
            std::cout << LineMiddleMessage;
        }

        SetCursor(CurrentPosition.X, CurrentPosition.Y);
        CurrentPosition.Y ++;
        std::cout << LineBottomMessage;
    }



    void DisplayInfo(unsigned int Width, unsigned int MarginTopBottom, unsigned int MarginLeftRight, std::string Message)
    {
        COORD CurrentPosition = GetCursor();

        size_t FirstFind = 0;
        size_t Position, Iterator1;

        std::vector<std::string> MessageTokens;

        std::string Delimeters = "\n ";
        std::string LineMessage;
        std::string LineMessageTemp;

        LineMessage.resize(Width, vkSpace);

        while (FirstFind < Message.size())
        {
            const auto SecondFind = Message.find_first_of(Delimeters, FirstFind);

            if ((FirstFind == SecondFind) && (Message[SecondFind] == '\n'))
            {
                MessageTokens.push_back(Message.substr(SecondFind, 1));
            }

            if (FirstFind != SecondFind)
            {
                MessageTokens.push_back(Message.substr(FirstFind, SecondFind - FirstFind));

                if (SecondFind < Message.size())
                {
                    if (Message.substr(SecondFind, 1) == "\n")
                    {
                        MessageTokens.push_back(Message.substr(SecondFind, 1));
                    }
                }
            }

            if (SecondFind == std::string::npos) break;

            FirstFind = SecondFind + 1;
        }

        LineMessageTemp = LineMessage;

        for (Iterator1 = 0; Iterator1 < MarginTopBottom; Iterator1++)
        {
            SetCursor(CurrentPosition.X, CurrentPosition.Y);
            CurrentPosition.Y ++;
            std::cout << LineMessageTemp;
        }

        Position = MarginLeftRight;

        for (Iterator1 = 0; Iterator1 < MessageTokens.size(); Iterator1++)
        {
            if((MessageTokens[Iterator1] == "\n") | ((MessageTokens[Iterator1].size() + Position) > (Width - MarginLeftRight - 1)))
            {
                SetCursor(CurrentPosition.X, CurrentPosition.Y);
                CurrentPosition.Y ++;
                std::cout << LineMessageTemp;

                LineMessageTemp = LineMessage;
                Position = MarginLeftRight;
            }

            if (MessageTokens[Iterator1] != "\n")
            {
                LineMessageTemp.replace(Position, MessageTokens[Iterator1].size(), MessageTokens[Iterator1]);
                Position += 1 + MessageTokens[Iterator1].size();
            }
        }

        SetCursor(CurrentPosition.X, CurrentPosition.Y);
        CurrentPosition.Y ++;
        std::cout << LineMessageTemp;

        for (Iterator1 = 0; Iterator1 < MarginTopBottom; Iterator1++)
        {
            SetCursor(CurrentPosition.X, CurrentPosition.Y);
            CurrentPosition.Y ++;
            std::cout << LineMessage;
        }
    }



    void ShowConsoleCursor(bool shFlag)
    {
        bool Success;

        DWORD LastError;

        CONSOLE_CURSOR_INFO cursorInfo;

        GetConsoleCursorInfo(tjpUtils::hstdout, &cursorInfo);
        cursorInfo.bVisible = shFlag;
        Success = SetConsoleCursorInfo(tjpUtils::hstdout, &cursorInfo);

        if(Success == false)
        {
            LastError = GetLastError();

            if(shFlag == true)
            {
                std::cout << "Error (" << LastError << "): Unable to turn on the console cursor.";
            } else
            {
                std::cout << "Error (" << LastError << "): Unable to turn off the console cursor.";
            }
        }
    }




    COORD GetCursor()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbInfo;

        if (! GetConsoleScreenBufferInfo(tjpUtils::hstdout, &csbInfo))
        {
            return {0, 0};
        }

        return csbInfo.dwCursorPosition;
    }



    void SetCursor(SHORT x, SHORT y)
    {
        SetConsoleCursorPosition(tjpUtils::hstdout, {x, y} );
    }

}

