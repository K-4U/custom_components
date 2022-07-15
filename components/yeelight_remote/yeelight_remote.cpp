
#include "yeelight_remote.h"
#include "esphome/core/log.h"

namespace esphome {
    namespace yeelight_remote {

        static const char *TAG = "yeelight-remote";

        void YeelightRemote::dump_config() {
            ESP_LOGCONFIG(TAG, "");
        }

        void YeelightRemote::loop() {
            while (available()) {
                uint8_t readByte = read();
                this->handle_char_(readByte);
            }
        }

        void YeelightRemote::handle_char_(uint8_t readByte) {
            if (readByte == 0x5A && !inMessage) {
                //New packet
                inMessage = true;
                inMessageCount = 0;
                parity = 0;
            }
            if (inMessage) {
                if (inMessageCount == 1) {
                    ESP_LOGD(TAG, "Found message id: %d", readByte);
                    if (previousMessageId == readByte) {
                        ESP_LOGD(TAG, "This is the same as the previous message, so skipping this.");
                        inMessage = false;
                    }
                    previousMessageId = readByte;

                } else if (inMessageCount == 3) {
                    ESP_LOGD(TAG, "Found command: %d", readByte);
                    command = readByte;
                } else if (inMessageCount == 7) {
                    ESP_LOGD(TAG, "Parity got of: %d", readByte);
                    ESP_LOGD(TAG, "Calculated parity of: %d", parity % 255);
                    if (parity % 255 == readByte) {
                        ESP_LOGD(TAG, "Parity is correct. Executing!");
                        switch (command) {
                            case 0x01:
                                this->handlePress();
                                break;
                            case 0x02:
                                this->handlePressAndTwistRight();
                                break;
                            case 0x03:
                                this->handlePressAndTwistLeft();
                                break;
                            case 0x04:
                                this->handleTwistRight();
                                break;
                            case 0x05:
                                this->handleTwistLeft();
                                break;
							case 0x06:
								this->handleLongPress();
								break;
                        }
                    }
                    inMessage = false;
                }

                parity += readByte;
                inMessageCount++;
            }
        }

        //TODO: Double push?
        void YeelightRemote::handlePress() {
            ESP_LOGD(TAG, "Press!");
            this->press_trigger_->trigger();
        }
		void YeelightRemote::handleLongPress() {
            ESP_LOGD(TAG, "Long press!");
            this->long_press_trigger_->trigger();
        }

        void YeelightRemote::handleTwistLeft() {
            ESP_LOGD(TAG, "Left!");
            this->left_trigger_->trigger();
        }

        void YeelightRemote::handleTwistRight() {
            ESP_LOGD(TAG, "Right!");
            this->right_trigger_->trigger();
        }

        void YeelightRemote::handlePressAndTwistLeft() {
            ESP_LOGD(TAG, "Press Left!");
            this->press_left_trigger_->trigger();
        }

        void YeelightRemote::handlePressAndTwistRight() {
            ESP_LOGD(TAG, "Press Right!");
            this->press_right_trigger_->trigger();
        }
    }
}