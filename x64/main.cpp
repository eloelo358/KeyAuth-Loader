#include <Windows.h>
#include "auth.hpp"
#include <string>
#include <thread>
#include <windows.h>
#include "utils.hpp"
#include "skStr.h"
#include <iostream>
#include <dwmapi.h>  
#pragma comment(lib, "Dwmapi.lib") 
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);
void sessionStatus();

using namespace KeyAuth;

std::string name = skCrypt("xz").decrypt(); 
std::string ownerid = skCrypt("kDYIH9k7j7").decrypt(); 
std::string version = skCrypt("1.0").decrypt(); 
std::string url = skCrypt("https://keyauth.win/api/1.3/").decrypt(); 
std::string path = skCrypt("").decrypt(); 



api KeyAuthApp(name, ownerid, version, url, path);

void makeConsoleTransparent(int opacity) {
    HWND hwnd = GetConsoleWindow(); // Pobranie uchwytu do okna konsoli
    if (hwnd == NULL) return;       // Sprawdzenie, czy okno istnieje

    // Ustawienie stylu okna, aby obsługiwało przezroczystość
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    // Ustawienie przezroczystości
    SetLayeredWindowAttributes(hwnd, 0, (BYTE)opacity, LWA_ALPHA);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printAscii() {

    makeConsoleTransparent(180);
    setColor(8);
    std::cout << R"(
    /$$                                 /$$                    
   | $$                                | $$                    
   | $$        /$$$$$$   /$$$$$$   /$$$$$$$  /$$$$$$   /$$$$$$ 
   | $$       /$$__  $$ |____  $$ /$$__  $$ /$$__  $$ /$$__  $$
   | $$      | $$  \ $$  /$$$$$$$| $$  | $$| $$$$$$$$| $$  \__/
   | $$      | $$  | $$ /$$__  $$| $$  | $$| $$_____/| $$      
   | $$$$$$$$|  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$| $$      
   |________/ \______/  \_______/ \_______/ \_______/|__/      
     )";
    setColor(7);

}

void spoof() {
    makeConsoleTransparent(180);
    setColor(13); // Jasnoróżowy
    std::cout << "\n[+] Spoofing in progress...\n";
    Sleep(2000); // Symulacja działania przez 2 sekundy
    setColor(10); // Zielony
    std::cout << "[+] Spoofing completed successfully!\n";
    setColor(7); // Przywrócenie domyślnego koloru
    Sleep(5000);
    system("cls");
    
}

void loadingScreen() {
    makeConsoleTransparent(180);
    setColor(10);
    std::cout << skCrypt("\n[");
    setColor(7);
    std::cout << skCrypt("+");
    setColor(10);
    std::cout << ("]");
    setColor(7);
    std::cout << " Initializing Program:\n";
    const std::string spinner = "|/-\\";
    for (int i = 0; i <= 100; i += 5) {
        std::cout << "\r[" << spinner[(i / 5) % spinner.size()] << "] Loading... " << i << "%";
        std::cout.flush();
        Sleep(150); // 150 ms opóźnienia
    }
    KeyAuthApp.init();
    if (!KeyAuthApp.response.success)
    {
        std::cout << skCrypt("\n Status: ") << KeyAuthApp.response.message;
        Sleep(1500);
        exit(1);
    }
    setColor(14);
    std::cout << skCrypt("\n[");
    setColor(7);
    std::cout << skCrypt("+");
    setColor(14);
    std::cout << ("]");
    setColor(7);
    std::cout << " Initialization Complete!\n";
    setColor(7); // Przywrócenie domyślnego koloru
    Sleep(3500);
    system("cls");
}

int main()
{
    makeConsoleTransparent(180);
    std::string consoleTitle = skCrypt("Loader - Built at:  ").decrypt() + compilation_date + " " + compilation_time;
    SetConsoleTitleA(consoleTitle.c_str());
    loadingScreen();


    if (std::filesystem::exists("test.json")) //change test.txt to the path of your file :smile:
    {
        if (!CheckIfJsonKeyExists("test.json", "username"))
        {
            std::string key = ReadFromJson("test.json", "license");
            KeyAuthApp.license(key);
            if (!KeyAuthApp.response.success)
            {
                std::remove("test.json");
                std::cout << skCrypt("\n Status: ") << KeyAuthApp.response.message;
                Sleep(1500);
                exit(1);
            }
            std::cout << skCrypt("\n\n Successfully Automatically Logged In\n");
        }
        else
        {
            std::string username = ReadFromJson("test.json", "username");
            std::string password = ReadFromJson("test.json", "password");
            KeyAuthApp.login(username, password);
            if (!KeyAuthApp.response.success)
            {
                std::remove("test.json");
                std::cout << skCrypt("\n Status: ") << KeyAuthApp.response.message;
                Sleep(1500);
                exit(1);
            }
            std::cout << skCrypt("\n\n Successfully Automatically Logged In\n");
        }
    }
    else
    {
        makeConsoleTransparent(180);
        printAscii();
        std::cout << skCrypt("\n\n [1] License key only\n\n Choose option: ");

        int option;
        std::string username, password, key, TfaCode;

        std::cin >> option;
        switch (option)
        {
        case 1:
            system("cls");
            printAscii();
            std::cout << skCrypt("\n Enter license: ");
            std::cin >> key;
            KeyAuthApp.license(key);
            system("cls");
            break;
        default:
            system("cls");
            printAscii();
            std::cout << skCrypt("\n\n Status: Failure: Invalid Selection");
            Sleep(3000);
            exit(1);
        }

        if (KeyAuthApp.response.message.empty()) exit(11);
        if (!KeyAuthApp.response.success)
        {
            std::cout << skCrypt("\n Status: ") << KeyAuthApp.response.message;
            Sleep(1500);
            exit(1);
        }

        if (username.empty() || password.empty())
        {
            WriteToJson("test.json", "license", key, false, "", "");
            std::cout << skCrypt("Successfully Created File For Auto Login");
        }
        else
        {
            WriteToJson("test.json", "username", username, true, "password", password);
            std::cout << skCrypt("Successfully Created File For Auto Login");
        }
    }

    std::thread run(checkAuthenticated, ownerid);
    std::thread check(sessionStatus); 

    makeConsoleTransparent(180);
    system("cls");
    printAscii();
    if (KeyAuthApp.user_data.username.empty()) exit(10);
    for (int i = 0; i < KeyAuthApp.user_data.subscriptions.size(); i++) {
        auto sub = KeyAuthApp.user_data.subscriptions.at(i);
        setColor(7);
        std::cout << skCrypt("\n[");
        setColor(8);
        std::cout << skCrypt("/");
        setColor(7);
        std::cout << ("]");
        std::cout << skCrypt(" expiry: ") << tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry)));
    }
    setColor(7);
    std::cout << skCrypt("\n[");
    setColor(8);
    std::cout << skCrypt("/");
    setColor(7);
    std::cout << ("]");
    std::cout << skCrypt(" Last login: ") << tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.user_data.lastlogin)));
    setColor(7);
    std::cout << skCrypt("\n[");
    setColor(8);
    std::cout << skCrypt("/");
    setColor(7);
    std::cout << ("]");
    std::cout << skCrypt(" Last Update: 15/02/2025 \n\n");
 
    int choice;
    do {
        setColor(8);
        std::cout << skCrypt("\n[");
        setColor(7);
        std::cout << skCrypt("1");
        setColor(8);
        std::cout << ("]");
        setColor(7);
        std::cout << " Spoof";
        setColor(8);
        std::cout << skCrypt("\n[");
        setColor(7);
        std::cout << skCrypt("2");
        setColor(8);
        std::cout << ("]");
        setColor(7);
        std::cout << " Exit\n";
        setColor(10);
        std::cout << skCrypt("\n[");
        setColor(7);
        std::cout << skCrypt("+");
        setColor(10);
        std::cout << ("]");
        setColor(7);
        std::cout << " Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            spoof();
            break;
        case 2:
            setColor(12); 
            std::cout << "Exiting...\n";
            setColor(7); 
            Sleep(1000);
            ExitProcess(0);
            break;
        default:
            setColor(4); 
            std::cout << "Invalid choice. Try again.\n";
            setColor(7); 
        }
    } while (choice != 2);
}

void sessionStatus() {
    KeyAuthApp.check(true); // do NOT specify true usually, it is slower and will get you blocked from API
    if (!KeyAuthApp.response.success) {
        exit(0);
    }

    if (KeyAuthApp.response.isPaid) {
        while (true) {
            Sleep(20000); // this MUST be included or else you get blocked from API
            KeyAuthApp.check();
            if (!KeyAuthApp.response.success) {
                exit(0);
            }
        }
    }
}

std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%m/%d/%y", &ctx);

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    auto cv = strtol(timestamp.c_str(), NULL, 10); // long

    return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
    std::tm context;

    localtime_s(&context, &timestamp);

    return context;
}
