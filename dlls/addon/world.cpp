#include "extdll.h"
#include "util.h"
#include "cbase.h"

#include <string>
#include <istream>
#include <sstream>
#include <vector>

static void handle_ent_fire(void) {
	const char* target = CVAR_GET_STRING("ent_fire");
	if (strlen(target) == 0) {
		return;
	}
	CVAR_SET_STRING("ent_fire", "");

	auto player = UTIL_GetLocalPlayer();
	FireTargets(target, player, player, USE_TOGGLE, 0);
}

// I miss Go.
// https://stackoverflow.com/a/46931770
static std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

static void handle_ent_set(void) {
	const char* args = CVAR_GET_STRING("ent_set");
	if (strlen(args) == 0) {
		return;
	}
	CVAR_SET_STRING("ent_set", "");

	const auto tokens = split(std::string(args), ' '); // target prop value
	if (tokens.size() != 3) {
		ALERT(at_error, "could not parse: %s\n", args);
		return;
	}

	const int value = std::atoi(tokens[2].c_str());
	edict_t* target = NULL;
	for (;;) {
		target = FIND_ENTITY_BY_TARGETNAME(target, tokens[0].c_str());
		if (FNullEnt(target)) {
			break;
		}

		entvars_t* pev = VARS(target);
		if (tokens[1] == "renderamt") {
			pev->renderamt = value;
		} else if (tokens[1] == "renderfx") {
			pev->renderfx = value;
		} else if (tokens[1] == "rendermode") {
			pev->rendermode = value;
		}
	}
}

void CWorld::Think(void) {
	CBaseEntity::Think();

	handle_ent_fire();
	handle_ent_set();
	pev->nextthink = pev->ltime + .001f;
}
