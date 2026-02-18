// User_Setup.h - Configured for ER-TFTM1.54-1 (ST7789) on ESP32-S3-N16R8

#define USER_SETUP_INFO "User_Setup"

// =============================================================
// 1. DRIVER CONFIGURATION
// =============================================================
#define ST7789_DRIVER
#define TFT_WIDTH  240
#define TFT_HEIGHT 240
#define TFT_RGB_ORDER TFT_BGR
#define TFT_INVERSION_ON

// =============================================================
// 2. PIN CONFIGURATION (ESP32-S3-N16R8)
// =============================================================
// SAFE PINS ONLY - avoids:
//   Flash pins:     6,7,8,9,10,11
//   OPI PSRAM pins: 33,34,35,36,37  (R8 specific!)
//   USB pins:       19,20
//   Strapping pins: 0,3,45,46

#define TFT_MOSI 21
#define TFT_SCLK 18
#define TFT_CS   17
#define TFT_DC   16
#define TFT_RST  15
#define TFT_BL   38
#define TFT_BACKLIGHT_ON HIGH
#define TFT_MISO -1

// Required for ESP32-S3 - forces correct SPI peripheral
#define USE_HSPI_PORT

// =============================================================
// 3. FONTS
// =============================================================
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT

// =============================================================
// 4. SPI FREQUENCY
// =============================================================
#define SPI_FREQUENCY       27000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000
