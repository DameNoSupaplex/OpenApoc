#pragma once
#include "library/sp.h"
#include "library/vec.h"
#include <vector>

namespace OpenApoc
{

class Vehicle;
class Agent;
class GameState;
class VehicleTileInfo;
class AgentInfo;
class Image;
class BitmapFont;
class Control;
class Graphic;
enum class Rank;

enum class CityUnitState
{
	InBase = 0,
	InVehicle = 1,
	InBuilding = 2,
	InMotion = 3,
};

enum class UnitSelectionState
{
	NA = -1,
	Unselected = 0,
	Selected = 1,
	FirstSelected = 2
};

class ControlGenerator
{
  private:
	static ControlGenerator singleton;
	void init(GameState &state);
	bool initialised = false;

	sp<BitmapFont> labelFont;
	sp<Image> healthImage;
	sp<Image> shieldImage;
	sp<Image> stunImage;
	sp<Image> iconShade;
	sp<Image> iconFatal;
	sp<Image> iconPsiIn;
	sp<Image> iconPsiOut;
	std::vector<sp<Image>> unitRanks;
	std::vector<sp<Image>> battleSelect;
	std::vector<sp<Image>> citySelect;
	std::vector<sp<Image>> vehiclePassengerCountIcons;
	std::vector<sp<Image>> icons;

  public:
	static VehicleTileInfo createVehicleInfo(GameState &state, sp<Vehicle> v);
	static sp<Control> createVehicleControl(GameState &state, const VehicleTileInfo &info);
	static sp<Control> createVehicleControl(GameState &state, sp<Vehicle> v);
	static AgentInfo
	createAgentInfo(GameState &state, sp<Agent> a,
	                UnitSelectionState forcedSelectionState = UnitSelectionState::NA,
	                bool forceFade = false);
	static void fillAgentControl(GameState &state, sp<Graphic> baseControl, const AgentInfo &info);
	static sp<Control> createAgentControl(GameState &state, const AgentInfo &info);
	static sp<Control>
	createAgentControl(GameState &state, sp<Agent> a,
	                   UnitSelectionState forcedSelectionState = UnitSelectionState::NA,
	                   bool forceFade = false);
	static sp<Control> createLargeAgentControl(GameState &state, const AgentInfo &info,
	                                           bool addSkill = false, bool labMode = false);
	static sp<Control>
	createLargeAgentControl(GameState &state, sp<Agent> a, bool addSkill = false,
	                        UnitSelectionState forcedSelectionState = UnitSelectionState::NA,
	                        bool forceFade = false, bool labMode = false);

	static int getFontHeight(GameState &state);
};

// All the info required to draw a single vehicle info chunk, kept together to make it easier to
// track when something has changed and requires a re-draw
class VehicleTileInfo
{
  public:
	sp<Vehicle> vehicle;
	UnitSelectionState selected;
	float healthProportion;
	bool shield;
	bool faded;     // Faded when they enter the alien dimension?
	int passengers; // 0-13, 0-12 having numbers, 13+ being '+'
	CityUnitState state;
	bool operator==(const VehicleTileInfo &other) const;
	bool operator!=(const VehicleTileInfo &other) const;
};

class AgentInfo
{
  public:
	sp<Agent> agent;
	Rank rank;
	bool useRank;
	CityUnitState state;
	bool useState;
	UnitSelectionState selected;

	float healthProportion;
	float stunProportion;
	bool shield;
	bool faded; // Faded when stunned or lowmorale

	bool psiOut;
	bool psiIn;
	bool fatal;

	bool operator==(const AgentInfo &other) const;
	bool operator!=(const AgentInfo &other) const;
};
}