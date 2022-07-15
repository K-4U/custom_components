#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace yeelight_remote {
    class YeelightRemote : public Component, public uart::UARTDevice {

    public:
        void dump_config() override;
        void loop() override;

        Trigger<> *get_press_trigger() const { return press_trigger_; }
        Trigger<> *get_long_press_trigger() const { return long_press_trigger_; }
        Trigger<> *get_left_trigger() const { return left_trigger_; }
        Trigger<> *get_right_trigger() const { return right_trigger_; }
        Trigger<> *get_press_left_trigger() const { return press_left_trigger_; }
        Trigger<> *get_press_right_trigger() const { return press_right_trigger_; }

    protected:
        uint16_t parity = 0;
		uint8_t previousMessageId = 0;
        uint8_t inMessageCount = 0;
		uint8_t command = 0;
		bool inMessage = false;

        void handle_char_(uint8_t readByte);
		void handlePress();
		void handleLongPress();
		void handleTwistLeft();
		void handleTwistRight();
		void handlePressAndTwistLeft();
		void handlePressAndTwistRight();
		
		
		Trigger<> *press_trigger_ = new Trigger<>();
		Trigger<> *long_press_trigger_ = new Trigger<>();
		Trigger<> *left_trigger_ = new Trigger<>();
		Trigger<> *right_trigger_ = new Trigger<>();
		Trigger<> *press_left_trigger_ = new Trigger<>();
		Trigger<> *press_right_trigger_ = new Trigger<>();
    };
}
}