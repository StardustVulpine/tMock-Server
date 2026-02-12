//
// Created by stardustvulpine on 2/1/26.
//

#pragma once
#include <cstddef>
#include <string>
#include "Color.hpp"
#include <Socket.hpp>

namespace tmockserver::gamestate {
    class Player {
        public:
        explicit Player(std::byte playerID);

        [[nodiscard]] networking::Socket& GetSocket();

        [[nodiscard]] std::byte GetID() const;
        [[nodiscard]] std::byte GetSkinVariant() const;
        [[nodiscard]] std::byte GetVoiceVariant() const;
        [[nodiscard]] float GetVoicePitchOffset() const;
        [[nodiscard]] std::byte GetHair() const;
        [[nodiscard]] const std::string& GetName() const;
        [[nodiscard]] std::byte GetHairDye() const;
        [[nodiscard]] std::byte GetHideVisuals() const;
        [[nodiscard]] std::byte GetHideVisuals2() const;
        [[nodiscard]] std::byte GetHideMisc() const;
        [[nodiscard]] Color GetHairColor() const;
        [[nodiscard]] Color GetSkinColor() const;
        [[nodiscard]] Color GetEyeColor() const;
        [[nodiscard]] Color GetShirtColor() const;
        [[nodiscard]] Color GetUnderShirtColor() const;
        [[nodiscard]] Color GetPantsColor() const;
        [[nodiscard]] Color GetShoesColor() const;
        [[nodiscard]] std::byte GetDifficultyFlags() const;
        [[nodiscard]] std::byte GetTorchFlags() const;

        void SetSocket(networking::Socket socket);
        
        void SetID(std::byte id);
        void SetSkinVariant(std::byte variant);
        void SetVoiceVariant(std::byte variant);
        void SetVoicePitchOffset(float offset);
        void SetHair(std::byte hair);
        void SetName(const std::string& name);
        void SetHairDye(std::byte dye);
        void SetHideVisuals(std::byte flags);
        void SetHideVisuals2(std::byte flags);
        void SetHideMisc(std::byte flags);
        void SetHairColor(Color color);
        void SetSkinColor(Color color);
        void SetEyeColor(Color color);
        void SetShirtColor(Color color);
        void SetUnderShirtColor(Color color);
        void SetPantsColor(Color color);
        void SetShoesColor(Color color);
        void SetDifficultyFlags(std::byte flags);
        void SetTorchFlags(std::byte flags);

        private:
        networking::Socket m_socket{};

        std::byte m_player_ID;
        std::byte m_skin_variant{};
        std::byte m_voice_variant{};
        float m_voice_pitch_offset{}; // Supposed range from 0.00 to 1.00 (not confirmed)
        std::byte m_hair{};     // If >162 then Set To 0 (for 1.4.9.x, on 1.4.5 update there are new hair types added)
        std::string m_name{};
        std::byte m_hair_dye{};
        std::byte m_hide_visuals{};
        std::byte m_hide_visuals_2{};
        std::byte m_hide_misc{};
        Color m_hair_color{};
        Color m_skin_color{};
        Color m_eye_color{};
        Color m_shirt_color{};
        Color m_under_shirt_color{};
        Color m_pants_color{};
        Color m_shoes_color{};
        std::byte m_difficulty_flags{}; // BitFlags: 0 = Softcore, 1 = Mediumcore, 2 = Hardcore, 4 = ExtraAccessory, 8 = Creative
        std::byte m_torch_flags{}; // BitFlags: 1 = UsingBiomeTorches, 2 = HappyFunTorchTime, 4 = unlockedBiomeTorches
    };
}