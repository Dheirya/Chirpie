#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"
#include "graphics.h"
#include "constants.h"
#include <EEPROM.h>

void drawColorBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h, float scale = 1.0) {
  for (int16_t origY = 0; origY < h; origY++) {
    int16_t yStart = round(y + origY * scale);
    int16_t yEnd = round(y + (origY + 1) * scale);
    int16_t height = max(1, yEnd - yStart);
    for (int16_t origX = 0; origX < w; origX++) {
      int16_t xStart = round(x + origX * scale);
      int16_t xEnd = round(x + (origX + 1) * scale);
      int16_t width = max(1, xEnd - xStart);
      uint16_t color = pgm_read_word(&bitmap[origY * w + origX]);
      tft.fillRect(xStart, yStart, width, height, color);
    }
  }
}

void blinkFunc() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= nextBlinkTime) {
    previousMillis = currentMillis;
    nextBlinkTime = random(minBlinkInterval, maxBlinkInterval);
    blinkStartTime = currentMillis;
    tft.fillRect(201, 59, 8, 4, DARKYELLOW);
    tft.fillRect(220, 55, 8, 4, DARKYELLOW);
  }
  if (blinkStartTime > 0 && currentMillis - blinkStartTime >= blinkDuration) {
    tft.fillRect(201, 59, 8, 4, BLACK);
    tft.fillRect(220, 55, 8, 4, BLACK);
    blinkStartTime = 0;
  }
}

void updateMoney() {
  tft.setCursor(27, 7);
  tft.setTextSize(2);
  drawColorBitmap(6, 5, coin, 20, 20, 0.9);
  tft.fillRect(27, 7, 60, 14, THEME);
  tft.println(String(loadMoneyFromEEPROM()));
}

void drawPercent() {
  tft.fillRect(12, 37, 86, 120, BACKGROUND);
  tft.drawRoundRect(12, 37, 30, 120, 5, THEME);
  tft.drawRoundRect(56, 37, 30, 120, 5, THEME);
  tft.fillRoundRect(12, 37, 30, loadHappyFromEEPROM() * 1.2, 5, DARKTHEME);
  tft.fillRoundRect(56, 37, 30, loadHealthFromEEPROM() * 1.2, 5, DARKTHEME);
}

void drawTopBar() {
  tft.fillRect(0, 0, 320, 30, THEME);
  tft.setCursor(100, 3);
  tft.setTextSize(3);
  tft.println(F("CHIRPIE"));
  updateMoney();
}

void drawBar(int color) {
  tft.fillRect(0, 0, 320, 30, color);
  tft.setTextSize(3);
}

void drawBookShelf() {
  tft.fillRect(0, 30, 320, 160, BROWN);
  for (int i = 0; i < 8; i++) {
    tft.drawRect(i, 30 + i, 320 - (2 * i), 160 - (2 * i), DARKBROWN);
  }
  for (int i = 0; i < 8; i++) {
    tft.drawRect(i, 30 + i, 164 - (2 * i), 160 - (2 * i), DARKBROWN);
  }
  drawColorBitmap(11, 72, book1, 13, 10, 11);
  drawColorBitmap(167, 72, book2, 13, 10, 11);
}

void initStars() {
  for (int i = 0; i < MAX_STARS; i++) {
    starX[i] = fastRandom(5, 315);
    starY[i] = fastRandom(35, 185);
    starVisible[i] = fastRandom(0, 2);
    starTimers[i] = millis();
    starIntervals[i] = fastRandom(minStarInterval, maxStarInterval);
  }
}

void updateTwinklingStars() {
  unsigned long currentMillis = millis();
  for (int i = 0; i < MAX_STARS; i++) {
    if (currentMillis - starTimers[i] >= starIntervals[i]) {
      starTimers[i] = currentMillis;
      starIntervals[i] = fastRandom(minStarInterval, maxStarInterval);
      if (starVisible[i]) {
        tft.fillRect(starX[i], starY[i], 2, 2, BLACK);
        starVisible[i] = false;
      } else {
        tft.fillRect(starX[i], starY[i], 2, 2, WHITE);
        starVisible[i] = true;
      }
    }
  }
}

void drawStarsBack() {
  tft.fillRect(0, 30, 320, 160, BLACK);
  tft.drawRect(0, 30, 320, 160, WHITE);
  tft.drawRect(0, 0, 320, 240, WHITE);
  initStars();
  for (int i = 0; i < MAX_STARS; i++) {
    if (starVisible[i]) {
      tft.fillRect(starX[i], starY[i], 2, 2, WHITE);
    }
  }
}

void changeBottom(int color, int lightColor) {
  tft.fillRect(0, 190, 320, 240, color);
  tft.fillRect(290, 0, 30, 30, lightColor);
  tft.setTextSize(3);
  tft.setCursor(298, 1);
  tft.print("x");
  drawTime();
}

void drawTime() {
  tft.setTextSize(4);
  tft.setCursor(102, 200);
  tft.print("00:00");
}

void drawButtons() {
  tft.fillRect(290, 0, 30, 30, DARKTHEME);
  tft.fillRoundRect(7, 195, 70, 40, 10, THEME);
  tft.fillRoundRect(86, 195, 70, 40, 10, THEME);
  tft.fillRoundRect(164, 195, 70, 40, 10, THEME);
  tft.fillRoundRect(243, 195, 70, 40, 10, THEME);
  drawColorBitmap(16, 160, smile, 15, 15, 1.5);
  drawColorBitmap(58, 158, health_symbol, 15, 15, 1.7);
  drawColorBitmap(32, 200, food, 13, 18, 1.7);
  drawColorBitmap(107, 200, pet, 14, 13, 2.1);
  drawColorBitmap(174, 200, book, 25, 15, 2);
  drawColorBitmap(263, 200, sleep, 35, 35, 0.8);
  drawColorBitmap(100, 40, chirpie, 59, 38, 3.75);
  tft.setTextSize(3);
  tft.setCursor(298, 5);
  tft.println(F("+"));
}

void setHome() {
  tft.drawRect(0, 29, 100, 162, THEME);
  tft.drawRect(0, 190, 320, 50, THEME);
  tft.fillRect(100, 30, 220, 160, SKYBLUE);
  drawPercent();
  drawButtons();
}

void drawHabits() {
  tft.fillRoundRect(7, 35, 150, 97, 5, DARKTHEME);
  tft.fillRoundRect(162, 35, 150, 97, 5, DARKTHEME);
  tft.fillRoundRect(7, 137, 150, 97, 5, DARKTHEME);
  tft.fillRoundRect(162, 137, 150, 97, 5, DARKTHEME);
  tft.setTextSize(2);
  tft.setCursor(50, 45);
  tft.print(F("Clean"));
  tft.setCursor(197, 45);
  tft.print(F("Mindful"));
  tft.setCursor(40, 147);
  tft.print(F("Reading"));
  tft.setCursor(193, 147);
  tft.print(F("Exercise"));
  tft.setTextSize(6);
  tft.setCursor(65, 63);
  tft.print(F("+"));
  tft.setCursor(222, 63);
  tft.print(F("+"));
  tft.setCursor(65, 165);
  tft.print(F("+"));
  tft.setCursor(222, 165);
  tft.print(F("+"));
  tft.setTextSize(1);
  tft.setCursor(27, 111);
  tft.print(F("For 10m of cleaning"));
  tft.setCursor(176, 111);
  tft.print(F("For 5m of mindfulness"));
  tft.setCursor(30, 213);
  tft.print(F("For 15m of reading"));
  tft.setCursor(182, 213);
  tft.print(F("For 20m of exercise"));
}

void setStore() {
  tft.fillRect(0, 30, 320, 240, BACKGROUND);
  drawColorBitmap(294, 4, home, 11, 11, 2);
  drawHabits();
}

bool canPressButton() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastButtonPressTime >= buttonCooldown) {
    lastButtonPressTime = currentMillis;
    return true;
  }
  return false;
}

void updateTime(uint16_t color) {
  tft.setTextSize(4);
  tft.setCursor(102, 200);
  String minutesStr = String(timerMinutes);
  String secondsStr = timerSeconds < 10 ? "0" + String(timerSeconds) : String(timerSeconds);
  if (minutesStr.length() == 1) {
    minutesStr = "0" + minutesStr;
  }
  if (secondsStr.length() == 1) {
    secondsStr = "0" + secondsStr;
  }
  tft.fillRect(102, 200, 120, 28, color);
  tft.print(minutesStr + ":" + secondsStr);
}

void menuTimer(unsigned long currentMillis, uint16_t color) {
  if (currentMillis - previousTimeUpdate >= second) {
    previousTimeUpdate = currentMillis;
    timerSeconds++;
    if (timerSeconds >= 60) {
      timerSeconds = 0;
      timerMinutes++;
    }
    updateTime(color);
  }
}

void saveMoneyToEEPROM(int money) {
  EEPROM.put(EEPROM_MONEY_ADDR, money);
}

void saveHealthToEEPROM(int health) {
  EEPROM.put(EEPROM_HEALTH_ADDR, health);
}

void saveHappyToEEPROM(int happy) {
  EEPROM.put(EEPROM_HAPPY_ADDR, happy);
}

int loadMoneyFromEEPROM() {
  int money;
  EEPROM.get(EEPROM_MONEY_ADDR, money);
  if (money <= 0 || money > 99999) {
    money = 0;
    saveMoneyToEEPROM(money);
  }
  return money;
}

int loadHealthFromEEPROM() {
  int health;
  EEPROM.get(EEPROM_HEALTH_ADDR, health);
  if (health <= 0 || health > 100) {
    health = 100;
    saveHealthToEEPROM(health);
  }
  return health;
}

int loadHappyFromEEPROM() {
  int happy;
  EEPROM.get(EEPROM_HAPPY_ADDR, happy);
  if (happy <= 0 || happy > 100) {
    happy = 100;
    saveHappyToEEPROM(happy);
  }
  return happy;
}

void shortError() {
  tft.fillRect(0, 0, 320, 30, RED);
  tft.setTextSize(3);
  tft.setCursor(120, 3);
  tft.println(F("ERROR"));
  delay(2000);
  drawTopBar();
  drawButtons();
}

void setup() {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(-1);
  tft.fillScreen(BACKGROUND);
  tft.setTextColor(WHITE);
  drawTopBar();
  setHome();
  saveHealthToEEPROM(37);
  saveHappyToEEPROM(94);
}

void loop() {
  digitalWrite(13, HIGH);
  unsigned long currentMillis = millis();
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (currentMillis - lastChangedHealth >= 15 * 60 * second) {
    lastChangedHealth = currentMillis;
    int health_value = loadHealthFromEEPROM();
    if (health_value > 1) {
      saveHealthToEEPROM(loadHealthFromEEPROM() - 1);
      if (state == 1) {
        drawPercent();
      }
    }
  }
  if (currentMillis - lastChangedHappy >= 15 * 60 * second) {
    lastChangedHappy = currentMillis;
    int happy_value = loadHappyFromEEPROM();
    if (happy_value > 1) {
      saveHappyToEEPROM(loadHappyFromEEPROM() - 1);
      if (state == 1) {
        drawPercent();
      }
    }
  }
  if (state == 1) {
    blinkFunc();
  }
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    p.x = tft.height() - map(p.x, TS_MINX, TS_MAXX, 0, tft.height());
    p.y = tft.width() - map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
    Serial.println(String(p.x) + ", " + String(p.y));
    if (state == 1) {
      if (p.y > 6 && p.y < 78 && p.x > 194 && p.x < 236) {
        if ((loadHealthFromEEPROM() + 10 <= 100) && (loadMoneyFromEEPROM() - 50 >= 0)) {
          if (canPressButton()) {
            saveMoneyToEEPROM(loadMoneyFromEEPROM() - 50);
            updateMoney();
            saveHealthToEEPROM(loadHealthFromEEPROM() + 10);
            drawPercent();
          }
        } else if ((loadHealthFromEEPROM() + 10 < 110 && loadHealthFromEEPROM() + 10 > 100) && (loadMoneyFromEEPROM() - 50 >= 0)) {
          if (canPressButton()) {
            saveMoneyToEEPROM(loadMoneyFromEEPROM() - 50);
            updateMoney();
            saveHealthToEEPROM(100);
            drawPercent();
          }
        } else {
          if (canPressButton()) {
            shortError();
          }
        }
      }
      if (p.y > 85 && p.y < 157 && p.x > 194 && p.x < 236) {
        if ((loadHappyFromEEPROM() + 10 <= 100) && (loadMoneyFromEEPROM() - 50 >= 0)) {
          if (canPressButton()) {
            saveMoneyToEEPROM(loadMoneyFromEEPROM() - 50);
            updateMoney();
            saveHappyToEEPROM(loadHappyFromEEPROM() + 10);
            drawPercent();
          }
        } else if ((loadHappyFromEEPROM() + 10 < 110 && loadHappyFromEEPROM() + 10 > 100)  && (loadMoneyFromEEPROM() - 50 >= 0)) {
          if (canPressButton()) {
            saveMoneyToEEPROM(loadMoneyFromEEPROM() - 50);
            updateMoney();
            saveHappyToEEPROM(100);
            drawPercent();
          }
        } else {
          if (canPressButton()) {
            shortError();
          }
        }
      }
      if (p.y > 289 && p.x < 31) {
        if (canPressButton()) {
          setStore();
          state = 2;
        }
      }
      if (p.y > 163 && p.y < 235 && p.x > 194 && p.x < 236) {
        if (canPressButton()) {
          drawBar(GREEN);
          tft.setCursor(119, 3);
          tft.println(F("STUDY"));
          changeBottom(GREEN, LIGHTGREEN);
          drawBookShelf();
          state = 3;
        }
      }
      if (p.y > 242 && p.y < 314 && p.x > 194 && p.x < 236) {
        if (canPressButton()) {
          drawBar(BLACK);
          tft.setCursor(100, 3);
          tft.println(F("FOCUSED"));
          changeBottom(BLACK, LIGHTBLACK);
          drawStarsBack();
          state = 4;
        }
      }
    }
    if (state == 2) {
      if (p.y > 6 && p.y < 158 && p.x > 34 && p.x < 133) {
        if (canPressButton()) {
          saveMoneyToEEPROM(loadMoneyFromEEPROM() + 20);
          updateMoney();
        }
      }
      if (p.y > 161 && p.y < 313 && p.x > 34 && p.x < 133) {
        if (canPressButton()) {
          saveMoneyToEEPROM(loadMoneyFromEEPROM() + 15);
          updateMoney();
        }
      }
      if (p.y > 6 && p.y < 158 && p.x > 136 && p.x < 235) {
        if (canPressButton()) {
          saveMoneyToEEPROM(loadMoneyFromEEPROM() + 25);
          updateMoney();
        }
      }
      if (p.y > 161 && p.y < 313 && p.x > 136 && p.x < 235) {
        if (canPressButton()) {
          saveMoneyToEEPROM(loadMoneyFromEEPROM() + 30);
          updateMoney();
        }
      }
    }
    if (state == 2 || state == 3 || state == 4) {
      if (p.y > 289 && p.x < 31) {
        if (canPressButton()) {
          tft.fillRect(0, 30, 320, 240, BACKGROUND);
          drawTopBar();
          setHome();
          state = 1;
          timerSeconds = 0;
          timerMinutes = 0;
          lastStudyMinutes = 0;
          lastFocusMinutes = 0;
        }
      }
    }
  }
  if (state == 3) {
    menuTimer(currentMillis, GREEN);
    if (timerMinutes > lastStudyMinutes) {
      lastStudyMinutes = timerMinutes;
      saveMoneyToEEPROM(loadMoneyFromEEPROM() + 1);
    }
  }
  if (state == 4) {
    updateTwinklingStars();
    menuTimer(currentMillis, BLACK);
    if (timerMinutes >= lastFocusMinutes + 2) {
      lastFocusMinutes = timerMinutes;
      saveMoneyToEEPROM(loadMoneyFromEEPROM() + 1);
    }
  }
}
