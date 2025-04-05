#include <M5StickCPlus2.h>
#include <WiFi.h>
#include <SD.h>

// Глобальні змінні
String ssid;
String passwords[] = {"12345678", "password", "admin123"};
int menuIndex = 0;
int menuMaxIndex = 4;  // Кількість елементів в меню (від 0 до 4)
int menuOffset = 0;    // Зміщення меню, щоб можна було прокручувати вліво/вправо
bool needRedraw = true;

// Відображення відсотка заряду
void displayBatteryPercentage() {
    float voltage = M5.Power.getBatteryVoltage();
    M5.Lcd.setCursor(10, 5);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.print("Battery: ");
    M5.Lcd.print(voltage);
    M5.Lcd.print("V");
}

// Відображення меню з прокручуванням вліво/вправо
void showMenu() {
    if (!needRedraw) return;
    needRedraw = false;

    M5.Lcd.fillScreen(TFT_BLACK);
    displayBatteryPercentage();
    M5.Lcd.setTextSize(2);

    String menuItems[] = {"Scan WiFi", "Bruteforce WiFi", "Settings", "Run Scripts", "Packet Sniffer"};
    
    // Відображаємо меню, прокручуючи вліво/вправо
    for (int i = menuOffset; i < menuOffset + 1; i++) {  // Ось тут тільки одне меню відображається на екрані
        M5.Lcd.setCursor(10, 30);
        if (i == menuIndex) {
            M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
        } else {
            M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
        }
        M5.Lcd.print(menuItems[i]);
    }
}

// Функція сканування WiFi
void scanWifi() {
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Scanning WiFi...");
    delay(2000);
}

// Функція для брутфорсу WiFi
void bruteforceWifi() {
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Bruteforcing WiFi...");
    delay(2000);
}

// Функція налаштувань
void settings() {
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Settings...");
    delay(2000);
}

// Виконання скриптів
void runScripts() {
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Running Scripts...");
    delay(2000);
}

// Функція перехоплення пакетів
void packetSniffer() {
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Sniffing Packets...");
    delay(2000);
}

// Функція обробки кнопок
void handleButtons() {
    if (M5.BtnA.wasPressed()) {  // Вибір і виконання обраної функції
        switch (menuIndex) {
            case 0: scanWifi(); break;
            case 1: bruteforceWifi(); break;
            case 2: settings(); break;
            case 3: runScripts(); break;
            case 4: packetSniffer(); break;
        }
        needRedraw = true;
    }

    if (M5.BtnB.wasPressed()) {  // Прокрутка меню вправо
        if (menuIndex < menuMaxIndex) {
            menuIndex++;
        }
        needRedraw = true;
    }

    if (M5.BtnC.wasPressed()) {  // Прокрутка меню вліво
        if (menuIndex > 0) {
            menuIndex--;
        }
        needRedraw = true;
    }
}

void setup() {
    M5.begin();
    M5.Lcd.setRotation(3);
    showMenu();
}

void loop() {
    M5.update();
    handleButtons();
    showMenu();
}