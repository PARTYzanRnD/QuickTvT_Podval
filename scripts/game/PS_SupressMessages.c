modded class SCR_PlayerLoadoutComponent
{
	override protected void OnFactionChanged(FactionAffiliationComponent owner, Faction old, Faction current)
	{
		// If a faction changes, as the authority, always clear this player's
		// loadout as there is no guarantee that new faction will
		if (old != current && !m_RplComponent || !m_RplComponent.IsProxy())
		{
			SCR_LoadoutManager loadoutManager = GetGame().GetLoadoutManager();
			if (!loadoutManager)
			{
				return;
			}

			int previous = loadoutManager.GetLoadoutIndex(m_Loadout);	
			
			// Loadout is existant, see whether it is possible to be kept,
			// or whether this loadout is no longer available after faction change
			if (previous != -1)
			{
				// If it cannot be assigned (not part of faction, etc)
				if (!CanAssignLoadout_S(previous))
				{
					// Directly clear loadout of target player,
					// for previous loadout can no longer be deemed valid
					AssignLoadout_S(-1);
					SendRequestLoadoutResponse_S(-1, true);
				}
			}
		}
	}
}