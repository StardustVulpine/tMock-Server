//
// Created by stardustvulpine on 2/1/26.
//

#pragma once
#include <cstddef>
#include <string>

#include "Color.hpp"

namespace tmockserver {
    class Player {
    public:
        explicit Player(std::byte playerID);

    private:
        std::byte m_player_ID;
        std::byte m_skin_variant;
        std::byte m_voice_variant;
        float m_voice_pitch_offset; // Supposed range from 0.00 to 1.00 (not confirmed)
        std::byte m_hair;     // If >162 then Set To 0 (for 1.4.9.x, on 1.4.5 update there are new hair types added)
        std::string m_name;
        std::byte m_hair_dye;
        std::byte m_hide_visuals;
        std::byte m_hide_visuals_2;
        std::byte m_hide_misc;
        Color m_hair_color;
        Color m_skin_color;
        Color m_eye_color;
        Color m_shirt_color;
        Color m_under_shirt_color;
        Color m_pants_color;
        Color m_shoes_color;
        std::byte m_difficulty_flags; // BitFlags: 0 = Softcore, 1 = Mediumcore, 2 = Hardcore, 4 = ExtraAccessory, 8 = Creative
        std::byte m_torch_flags; // BitFlags: 1 = UsingBiomeTorches, 2 = HappyFunTorchTime, 4 = unlockedBiomeTorches
    };
} // tmockserver