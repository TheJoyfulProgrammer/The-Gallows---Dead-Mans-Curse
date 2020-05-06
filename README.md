# The Gallows - Dead Man's Curse
A Windows Console hangman like game, written in C++ version 17 with the MingW compiler. This version was compiled with the Code::Blocks IDE, so the associated files are included.

# The Story behind The Gallows - Dead Man's Curse:
While the game play of The Gallows - Dead Man's Curse may seem simple enough, there is a lot of power going on behind the scenes. When we play a simple game like this one, many of us don't take the time to think about how much time, energy, creativity, crafting, researching, and testing goes on during development. I, myself, am guilty of this, time and time again, even if I look at the source code.

What we don't see are all the deleted code and functions created during the development, all the logic changes, or complete rewrites that had taken place before we were introduced to the project. This is all true to this game, The Gallows - Dead Man's Curse. A friend of mine, David Taylor, created the first incarnation of this game, which he just called, The Gallows. It was a much simpler game then this latest version.

He had asked me to help him touch it up a little, which I did, but when I started, I couldn't stop. I started out helping him fix the palette color system, but then I started making suggestions on other things he should do with the game. The biggest thing was to be able to load the word dictionary at run time, instead of implementing them in the code itself. So, I created the functions that loads and splits the dictionary.

As time went on, I realized that this game needed a major overhaul, so unbeknowest to David, I stopped work on the first incarnation, and started on the one you see here.

The first thing I did was to separate a lot of the code to external files, and into their own namespaces. There were a lot of reasons that I did that, and here are a few of them:

  * The code and data needed to be in their own libraries for modularity purposes, and removed from global space.
  * The game utility code & data needed to be separated from the main components, as-well-as from the generic components.
  * I wanted those who read the code to see how easy it is to create their own libraries with namespaces, and without classes.

Eventually I shared my changes with David, and he loved them. So the rest, as they say, is history.

# Features:
Here is a list of features you will find in the game:

  * **Automatically formatted boxed messages.** The function which displays these message boxes accepts two strings, the title for the box, and the message. Since the message is in a single string, the function captures the "\n" to perform a new line, and it automatically word wraps the message so it all stays in the box.
  * **Category & Dictionary loading and splitting.** The category list and the selected dictionary list are loaded into memory as a whole, and then split into vector array's. This function was tested on a nearly 500K word dictionary, which only a fraction of a second. I was stunned at the speed, especially since I was coding it in Windows 10, which was running in a Oracle VM VirtualBox window on a Linux Mint system.
  * **A custom GetKey() function.** This function is the powerhouse and backbone of the entire game. Without it, most of the game would not be possible. Instead of creating a GUI thread in Windows just capture keyboard (and mouse) events, I simply used the Windows console API. With this method, I was able to read the keyboard and the mouse at the same time. This function has dual purposes and fits well with the game. While this function started out as a generic function, I incorporated parts of the game in it, so it is specific to this game. However, those parts can be deleted and it can be used as a generic function for your own projects.
  * **Scrollable and selected category list.** With the advent of the powerful new GetKey() function, I was able to allow the user to either use the arrow keys to go through the list, or use the mouse. If your mouse has a scrollwheel, it can be used to scroll the category list left and right, if there are more categories then what will fit on the screen. Then you can either use the return/enter key, or click on a category item with the left mouse button. You can even click on the left & right "MORE" messages at the bottom left & right of the screen.
  * **Turned off the console cursor.** After all the beta testing I did while I was adding my touches to David's game, I found the console cursor to be distracting and annoying, rather it was blinking in one spot, or shown shooting across the screen while it was drawing parts of the game. So I used the Windows Console API to turn it off. In doing so, the game seemed to run faster by perception, but I didn't time it to find out.
  * **SetCursor() / GetCursor() functions.** I made two little functions that made it easy for the developer to get the current console cursor position, or set it. Again using Windows Console API.
  * **Set the console window to a fixed size.** The one thing this game did not need, in my opinion, was scrolling console window. This wasn't a game that needed it. But, that idea posed several problems. How do we let the player know what letters were chosen already while keeping everything on screen. My solution to the problem was to create the letterboxes you see in the game play now. Another issue was where would we tell the player how many chances were left, we they won, or when they lost. Since there was still room underneath the letterboxes, I decided the messages would be perfect there. On a side note, the console is set to 130 characters wide by 40 characters high. The console buffer is also set to that size so the scrollbars would not appear.
  * **Setting the console palette colors.** Unlike the Linux terminal with 256 available colors, the Windows console only offers 16. However, like the Linux terminal, we can modify the color palette of the Windows console. With the Windows API, we can can quickly, and easily set each palette color to any RGB value we choose. This is how we achieved the green color you see by default in the game, which is not the only you can pick from. We currently have two other color palettes to choose from, a grayscale and burnt orange. All three color palettes emulate old computer monochrome monitors from the dawn of personal computers.
  * **Color() function.** This overloaded function allows the developer to select the current color from the palette to be used next. You can change the text color only (i.e. Color(ForegroundColor)), or the text and background color (i.e Color(ForegroundColor, BackgroundColor)).
  * **ClearScreen() function** Clearing the screen is very easy to with this function.
  * **Game Loop in a console game** The game code in the main() function demonstrates how to use a game loop in a Windows console game.
  
# My final thoughts
While The Gallows - Dead Man's Curse is a fun game to play (for a short time if your like me), what I would like for you to walk away with is all the knowledge this game internally (through code) offers to you. There are a lot of different aspects to learn, from setting up C++ code in external files, creating libraries with just namespaces (no classes required), properly formatting your code, properly naming functions and variables, to using the Windows Console API.

Thank you,
Walter Whitman
A.K.A. Waltersmind
A.K.A. The Joyful Programmer

![Screenshot 1](https://github.com/TheJoyfulProgrammer/The-Gallows---Dead-Mans-Curse/blob/master/ScreenshotsOfTheGame/Screenshot%20from%202020-05-06%2007-45-02.png)

![Screenshot 2](https://github.com/TheJoyfulProgrammer/The-Gallows---Dead-Mans-Curse/blob/master/ScreenshotsOfTheGame/Screenshot%20from%202020-05-06%2007-52-53.png)

![Screenshot 3](https://github.com/TheJoyfulProgrammer/The-Gallows---Dead-Mans-Curse/blob/master/ScreenshotsOfTheGame/Screenshot%20from%202020-05-06%2007-53-50.png)

![Screenshot 4](https://github.com/TheJoyfulProgrammer/The-Gallows---Dead-Mans-Curse/blob/master/ScreenshotsOfTheGame/Screenshot%20from%202020-05-06%2007-54-39.png)

![Screenshot 5](https://github.com/TheJoyfulProgrammer/The-Gallows---Dead-Mans-Curse/blob/master/ScreenshotsOfTheGame/Screenshot%20from%202020-05-06%2007-55-16.png)

![Screenshot 6](https://github.com/TheJoyfulProgrammer/The-Gallows---Dead-Mans-Curse/blob/master/ScreenshotsOfTheGame/Screenshot%20from%202020-05-06%2007-55-49.png)
