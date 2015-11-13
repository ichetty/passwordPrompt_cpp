// Written by Patrick S. Avery -- 2015
// Hides the console input while the user inputs the password

#include <iostream>
#include <string>

// Include Windows header for Windows
#ifdef _WIN32
#include <windows.h>
#else // Include Unix headers for Unix
#include <termios.h>
#include <unistd.h>
#endif

#include "passwordPrompt.h"

std::string PasswordPrompt::getPassword()
{
// For Windows
#ifdef _WIN32
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode = 0;
  GetConsoleMode(hStdin, &mode);
  SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
#else // For Unix
  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif

  std::string s;
  std::cout << "Enter password:";
  getline(std::cin, s);

// Cleanup
#ifdef _WIN32
  SetConsoleMode(hStdin, mode);
#endif
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return s;
}
