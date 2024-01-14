#include "extdll.h"
#include "util.h"
#include "cbase.h"

static void handle_ent_fire(void) {
	const char* target = CVAR_GET_STRING("ent_fire");
	if (strlen(target) == 0) {
		return;
	}
	CVAR_SET_STRING("ent_fire", "");

	auto player = UTIL_GetLocalPlayer();
	FireTargets(target, player, player, USE_TOGGLE, 0);
}

void CWorld::Think(void) {
	CBaseEntity::Think();

	handle_ent_fire();
	pev->nextthink = pev->ltime + .001f;
}
