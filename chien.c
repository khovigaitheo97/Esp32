#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "rc522.h"

// fallback nếu thư viện không define
#ifndef PICC_REQIDL
#define PICC_REQIDL 0x26
#endif

#ifndef MI_OK
#define MI_OK 0
#endif

static const char *TAG = "RC522_TEST";

void app_main(void)
{
    
    ESP_LOGI(TAG, "RC522 test started");

    // Khởi tạo RC522
    rc522_init();

    uint8_t status;
    uint8_t uid[5];   // UID 4 byte + checksum

    while (1) {
        // 1. Check có thẻ không
        status = rc522_request(PICC_REQIDL, uid);

        if (status == MI_OK) {
            // 2. Đọc UID
            status = rc522_anticoll(uid);
            if (status == MI_OK) {
                ESP_LOGI(TAG,
                         "Card detected! UID: %02X %02X %02X %02X",
                         uid[0], uid[1], uid[2], uid[3]);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(300));
    }
}
