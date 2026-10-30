#include <nlohmann/json.hpp>

#include "soh/Network/Anchor/Anchor.h"
#include "soh/Network/Anchor/JsonConversions.hpp"

/**
 * BUDDY_HIT
 *
 * Harkinian Buddy combat: an enemy, boss or hazard in this game hit a buddy's dummy player.
 * Sent to that buddy's client (the Harkinian Buddy app), which takes the hearts off, plays the
 * hurt and knock-back, and knocks the buddy out at zero. The game only reports the hit.
 */

void Anchor::SendPacket_BuddyHit(u32 clientId, u8 damage, u8 damageEffect, s16 attackerActorId, Vec3f attackerPos) {
    if (!IsSaveLoaded()) {
        return;
    }

    nlohmann::json payload;
    payload["type"] = BUDDY_HIT;
    payload["targetClientId"] = clientId;
    payload["damage"] = damage;             // the attack's own damage (Link's units: 16 = one heart)
    payload["damageEffect"] = damageEffect; // 0 normal, 1 fire, 2 ice, 3 electric, 4 knockback...
    payload["attackerActorId"] = attackerActorId;
    payload["attackerPos"] = attackerPos;
    payload["quiet"] = true;

    SendJsonToRemote(payload);
}
