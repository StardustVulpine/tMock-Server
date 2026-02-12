//
// Created by stardustvulpine on 2/1/26.
//

#include "Player.hpp"

namespace tmockserver::gamestate {
    Player::Player(const std::byte playerID) : m_player_ID(playerID)
    {

    }

    networking::Socket& Player::GetSocket() {return m_socket;}
    
    std::byte Player::GetID() const {return m_player_ID;}
    std::byte Player::GetSkinVariant() const {return m_skin_variant;}
    std::byte Player::GetVoiceVariant() const {return m_voice_variant;}
    float Player::GetVoicePitchOffset() const {return m_voice_pitch_offset;}
    std::byte Player::GetHair() const {return m_hair;}
    const std::string& Player::GetName() const {return m_name;}
    std::byte Player::GetHairDye() const {return m_hair_dye;}
    std::byte Player::GetHideVisuals() const {return m_hide_visuals;}
    std::byte Player::GetHideVisuals2() const {return m_hide_visuals_2;}
    std::byte Player::GetHideMisc() const {return m_hide_misc;}
    Color Player::GetHairColor() const {return m_hair_color;}
    Color Player::GetSkinColor() const {return m_skin_color;}
    Color Player::GetEyeColor() const {return m_eye_color;}
    Color Player::GetShirtColor() const {return m_shirt_color;}
    Color Player::GetUnderShirtColor() const {return m_under_shirt_color;}
    Color Player::GetPantsColor() const {return m_pants_color;}
    Color Player::GetShoesColor() const {return m_shoes_color;}
    std::byte Player::GetDifficultyFlags() const {return m_difficulty_flags;}
    std::byte Player::GetTorchFlags() const {return m_torch_flags;}

    void Player::SetSocket(networking::Socket socket) {
        m_socket = std::move(socket);
    }

    void Player::SetID(const std::byte id) {
        m_player_ID = id;
    }

    void Player::SetSkinVariant(const std::byte variant) {
        m_skin_variant = variant;
    }

    void Player::SetVoiceVariant(const std::byte variant) {
        m_voice_variant = variant;
    }

    void Player::SetVoicePitchOffset(const float offset) {
        m_voice_pitch_offset = offset;
    }

    void Player::SetHair(const std::byte hair) {
        m_hair = hair;
    }

    void Player::SetName(const std::string& name) {
        m_name = name;
    }

    void Player::SetHairDye(const std::byte dye) {
        m_hair_dye = dye;
    }

    void Player::SetHideVisuals(const std::byte flags) {
        m_hide_visuals = flags;
    }

    void Player::SetHideVisuals2(const std::byte flags) {
        m_hide_visuals_2 = flags;
    }

    void Player::SetHideMisc(const std::byte flags) {
        m_hide_misc = flags;
    }

    void Player::SetHairColor(const Color color) {
        m_hair_color = color;
    }

    void Player::SetSkinColor(const Color color) {
        m_skin_color = color;
    }

    void Player::SetEyeColor(const Color color) {
        m_eye_color = color;
    }

    void Player::SetShirtColor(const Color color) {
        m_shirt_color = color;
    }

    void Player::SetUnderShirtColor(const Color color) {
        m_under_shirt_color = color;
    }

    void Player::SetPantsColor(const Color color) {
        m_pants_color = color;
    }

    void Player::SetShoesColor(const Color color) {
        m_shoes_color = color;
    }

    void Player::SetDifficultyFlags(const std::byte flags) {
        m_difficulty_flags = flags;
    }

    void Player::SetTorchFlags(const std::byte flags) {
        m_torch_flags = flags;
    }

} // tmockserver