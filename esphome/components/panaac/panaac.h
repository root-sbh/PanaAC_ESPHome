/*
 * Copyright 2025 Hoang Minh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 #pragma once

#include "definitions.h"
#include "extra.h"
#include "esphome/components/switch/switch.h"
#include <cinttypes>

namespace esphome
{
    namespace panaac
    {
        class PanaACClimate : public climate_ir::ClimateIR
        {
        public:
            PanaACClimate() : climate_ir::ClimateIR(
                                  PANAAC_TEMP_MIN, PANAAC_TEMP_MAX, 1.0f, true, true,
                                  {climate::CLIMATE_FAN_AUTO,
                                   climate::CLIMATE_FAN_LOW,
                                   climate::CLIMATE_FAN_MEDIUM,
                                   climate::CLIMATE_FAN_HIGH,
                                   climate::CLIMATE_FAN_QUIET},
                                  {climate::CLIMATE_SWING_OFF,
                                   climate::CLIMATE_SWING_BOTH,
                                   climate::CLIMATE_SWING_VERTICAL,
                                   climate::CLIMATE_SWING_HORIZONTAL},
                                  {})
                                  {}

            void set_swing_horizontal(bool swing_horizontal) { this->swing_horizontal_ = swing_horizontal; }
            void set_temp_step(float temp_step) { this->temp_step_ = temp_step; }
            void set_supports_quiet(bool supports_quiet) { this->supports_quiet_ = supports_quiet; }
            void set_supports_fan_only(bool supports_fan_only) { this->supports_fan_only_ = supports_fan_only; }
            void set_fan_level_steps(int fan_level_steps) { this->fan_level_steps_ = fan_level_steps; }
            void set_ir_control(bool ir_control) { this->ir_control_ = ir_control; }

            void set_supports_nanoex(switch_::Switch *supports_nanoex);
            void set_supports_econavi(switch_::Switch *supports_econavi);
            void set_supports_cool_with_dry(switch_::Switch *supports_cool_with_dry);
            void set_supports_clothes_dry(switch_::Switch *supports_clothes_dry);

            // void set_fanlevel(PanaACFanLevel *fanlevel) { this->fanlevel_ = fanlevel; }
            void set_swingv(PanaACSwingV *swingv) { this->swingv_ = swingv; }
            void set_swingh(PanaACSwingH *swingh) { this->swingh_ = swingh; }

            void update_state();
            void transmit_data();

            ClimateState ac_state;
            bool swing_horizontal_;

        protected:
            void setup() override;
            void transmit_state() override;
            bool on_receive(remote_base::RemoteReceiveData data) override;
            climate::ClimateTraits traits() override;

            bool decode_data(remote_base::RemoteReceiveData data, std::vector<uint8_t>& state_bytes);
            bool decode_state(std::vector<uint8_t> state_bytes, ClimateState& state);
            
            float temp_step_;
            bool supports_quiet_;
            bool supports_powerful_;
            int fan_level_steps_;
            bool ir_control_;
            bool supports_fan_only_;
            switch_::Switch *supports_nanoex_ = nullptr;
            switch_::Switch *supports_econavi_ = nullptr;
            switch_::Switch *supports_cool_with_dry_ = nullptr;
            switch_::Switch *supports_clothes_dry_ = nullptr;

            // PanaACFanLevel *fanlevel_{nullptr};
            PanaACSwingV *swingv_{nullptr};
            PanaACSwingH *swingh_{nullptr};
        };


    } // namespace panaac
} // namespace esphome
