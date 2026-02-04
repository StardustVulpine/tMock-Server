//
// Created by stardustvulpine on 2/1/26.
//

#include "Player.hpp"

namespace tmockserver {
    Player::Player(const std::byte playerID) :
        m_player_ID(playerID),
        m_skin_variant(),
        m_hair(),
        m_hair_dye(),
        m_hide_visuals(),
        m_hide_visuals_2(),
        m_hide_misc(),
        m_hair_color(),
        m_skin_color(),
        m_eye_color(), m_shirt_color(),
        m_under_shirt_color(),
        m_pants_color(),
        m_shoes_color(),
        m_difficulty_flags(),
        m_torch_flags()
    {}
} // tmockserver