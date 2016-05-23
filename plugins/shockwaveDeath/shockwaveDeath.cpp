// shockwaveDeath.cpp : Defines the entry point for the DLL application.
//

#include "bzfsAPI.h"

// event handler callback
class SWDeathHandler : public bz_Plugin
{
public:
  virtual const char* Name (){return "Shockwave Death";}
  virtual void Init ( const char* config);
  virtual void	Event ( bz_EventData *eventData );
};

BZ_PLUGIN(SWDeathHandler)

void SWDeathHandler::Init( const char* /*commandLine*/ )
{
  bz_debugMessage(4,"shockwaveDeath plugin loaded");

  // Register our event
  Register(bz_ePlayerDieEvent);
}

void SWDeathHandler::Event ( bz_EventData *eventData )
{
  // We only handle the player death event, so bail out otherwise
  if (eventData->eventType != bz_ePlayerDieEvent)
    return;

  // Cast our event data so we can access the death position
  bz_PlayerDieEventData_V1 *dieData = (bz_PlayerDieEventData_V1*)eventData;

  // Retrieve the current reload time value
  float reloadTime = (float)bz_getBZDBDouble("_reloadTime");

  // If _swDeathReloadFactor is defined and greater than zero, multiply the
  // reload time by this factor
  if (bz_BZDBItemExists("_swDeathReloadFactor") && bz_getBZDBDouble("_swDeathReloadFactor") > 0)
    reloadTime *= (float)bz_getBZDBDouble("_swDeathReloadFactor");

  // Fire a shockwave where the player died
  bz_fireWorldWep("SW", reloadTime, BZ_SERVER, dieData->state.pos, 0, 0, 0, 0.0f);
}

// Local Variables: ***
// mode:C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
