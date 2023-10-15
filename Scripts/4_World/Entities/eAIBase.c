modded class eAIBase
{

	override bool eAI_HandleAiming(float pDt, bool hasLOS = false)
	{
		string TargetBone = "Neck";
		eAITarget target = m_eAI_Targets[0];

		bool isServer = GetGame().IsServer();

		if (target)
		{
			vector aimPosition = target.GetPosition(this, !isServer) + target.GetAimOffset(this);
			if (isServer)
			{
				bool lookDirectionRecalculate;
				if (m_eAI_CurrentThreatToSelfActive > 0.1 && hasLOS)
					lookDirectionRecalculate = true;
				LookAtPosition(aimPosition, lookDirectionRecalculate);
				if (!m_eAI_LookDirection_Recalculate)
					LookAtDirection("0 0 1");
			}
			bool aimDirectionRecalculate;
			if (!isServer || m_eAI_CurrentThreatToSelfActive > 0.15)
				aimDirectionRecalculate = true;
			AimAtPosition(aimPosition, aimDirectionRecalculate);
			TargetBone = eAI_GetTargetBone(target, isServer);
		}
		else
		{
			if (isServer && m_eAI_LookDirection_Recalculate)
				LookAtDirection("0 0 1");

			if (m_eAI_AimDirection_Recalculate)
				AimAtDirection("0 0 1");
		}
		

		vector neck = GetBonePositionWS(GetBoneIndexByName(TargetBone));

		if (isServer && m_eAI_LookDirection_Recalculate)
		{
			m_eAI_LookDirectionTarget_ModelSpace = vector.Direction(neck, m_eAI_LookPosition_WorldSpace).Normalized().InvMultiply3(m_ExTransformPlayer);
		}

		if (m_eAI_AimDirection_Recalculate)
		{
			m_eAI_AimDirectionTarget_ModelSpace = vector.Direction(neck, m_eAI_AimPosition_WorldSpace).Normalized().InvMultiply3(m_ExTransformPlayer);
		}

		if (target)
			return true;
		return false;
	}

	string eAI_GetTargetBone(eAITarget target, bool isServer)
	{
		EntityAI weapon = GetItemInHands();
		if (weapon)
		{
			if (weapon.IsInherited(Rifle_Base) || weapon.IsInherited(Pistol_Base))
			{
				if (vector.Distance(this.GetPosition(), target.GetPosition(this, !isServer)) > m_eAI_SniperProneDistanceThreshold)
					return "Head";
				return "Pelvis";
			}
			if (weapon.IsInherited(Container_Base)) 
				return "Pelvis";

			if (weapon.IsInherited(ToolBase)) 
				return "Head";
		}
		return "Neck";
	}
}