#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
#define YP A3
#define XM A2
#define YM 9
#define XP 8
#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920
#define RED 0x8800
#define BLACK 0x0000
#define LIGHTBLACK 0x4a69
#define WHITE 0xFFFF
#define SKYBLUE 0x265f
#define DARKTHEME 0x65ba
#define THEME 0x0436
#define GREEN 0x2589
#define LIGHTGREEN 0x6650
#define BACKGROUND 0xdfbf
#define YELLOW 0xfe8b
#define BROWN 0x9a86
#define DARKBROWN 0x4965
#define DARKYELLOW 0xfe47
#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define MAX_STARS 150
#define EEPROM_MONEY_ADDR 0
#define EEPROM_HEALTH_ADDR 8
#define EEPROM_HAPPY_ADDR 16

int numStars = 0;
int starX[MAX_STARS];
int starY[MAX_STARS];
bool starVisible[MAX_STARS];
unsigned long starTimers[MAX_STARS];
unsigned long starIntervals[MAX_STARS];
unsigned long lastStarUpdate = 0;
const int minStarInterval = 1000;
const int maxStarInterval = 20000;

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int state = 1;
int homeState = 1;
bool blink = false;
unsigned long previousMillis = 0;
unsigned long blinkStartTime = 0;
unsigned long nextBlinkTime = 0;
const long blinkDuration = 200;
const long minBlinkInterval = 1000;
const long maxBlinkInterval = 5000;
unsigned long lastButtonPressTime = 0;
unsigned long previousTimeUpdate = 0;
unsigned long lastChangedHealth = 0;
unsigned long lastChangedHappy = 0;
const unsigned long second = 1000;
int timerSeconds = 0;
int timerMinutes = 0;
int lastStudyMinutes = 0;
int lastFocusMinutes = 0;

const long buttonCooldown = 500;
uint32_t seed = 12345;

uint16_t fastRandom(uint16_t minVal, uint16_t maxVal) {
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return minVal + (seed % (maxVal - minVal));
}
