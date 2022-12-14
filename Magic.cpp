// Magic.cpp: implementation of the CMagic class.
//
//////////////////////////////////////////////////////////////////////

#include "Magic.h"

extern void PutLogList(char* cMsg);
extern char G_cTxt[512];
extern char	G_cData50000[50000];
extern void PutLogFileList(char* cStr);
extern void PutAdminLogFileList(char* cStr);
extern void PutItemLogFileList(char* cStr);
extern void PutLogEventFileList(char* cStr);
extern void PutHackLogFileList(char* cStr);
extern void PutPvPLogFileList(char* cStr);
extern FILE* pLogFile;
extern HWND	G_hWnd;

#pragma warning (disable : 4996)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMagic::CMagic()
{
	ZeroMemory(m_cName, sizeof(m_cName));
	m_iAttribute = 0;
}

CMagic::~CMagic()
{										    

}

/*********************************************************************************************************************
**  int CGame::iGetWhetherMagicBonusEffect(short sType, char cWheatherStatus)										**
**  description			:: checks for a weather bonus when magic is cast											**
**  last updated		:: November 20, 2004; 10:34 PM; Hypnotoad													**
**	return value		:: int																						**
*********************************************************************************************************************/
int CGame::iGetWhetherMagicBonusEffect(short sType, char cWheatherStatus)
{
	int iWheatherBonus;

	iWheatherBonus = 0;
	switch (cWheatherStatus) {
	case 0: break;
	case 1:
	case 2:
	case 3:
		switch (sType) {
		case 10:
		case 37:
		case 43:
		case 51:
			iWheatherBonus = 1;
			break;

		case 20:
		case 30:
			iWheatherBonus = -1;
			break;
		}
		break;
	}
	return iWheatherBonus;
}

/*********************************************************************************************************************
**  void CGame::SetInvisibilityFlag(short sOwnerH, char cOwnerType, bool bStatus)									**
**  description			:: changes the status of the player to show invisibility aura								**
**  last updated		:: November 20, 2004; 9:30 PM; Hypnotoad													**
**	return value		:: void																						**
*********************************************************************************************************************/
void CGame::SetInvisibilityFlag(short sOwnerH, char cOwnerType, bool bStatus)
{
	switch (cOwnerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x00000010;
		else m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xFFFFFFEF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus | 0x00000010;
		else m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus & 0xFFFFFFEF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;
	}
}

/*********************************************************************************************************************
**  void CGame::SetInhibitionCastingFlag(short sOwnerH, char cOwnerType, bool bStatus)								**
**  description			:: changes the status of the player to show inhibit casting aura							**
**  last updated		:: November 20, 2004; 9:33 PM; Hypnotoad													**
**	return value		:: void																						**
*********************************************************************************************************************/
void CGame::SetInhibitionCastingFlag(short sOwnerH, char cOwnerType, bool bStatus)
{
	switch (cOwnerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x00100000;
		else m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xFFEFFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus | 0x00100000;
		else m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus & 0xFFEFFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;
	}
}

/*********************************************************************************************************************
**  void void CGame::SetBerserkFlag(short sOwnerH, char cOwnerType, bool bStatus)									**
**  description			:: changes the status of the player to show berserk aura									**
**  last updated		:: November 20, 2004; 9:35 PM; Hypnotoad													**
**	return value		:: void																						**
*********************************************************************************************************************/
void CGame::SetBerserkFlag(short sOwnerH, char cOwnerType, bool bStatus)
{
	switch (cOwnerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x00000020;
		else m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xFFFFFFDF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus | 0x00000020;
		else m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus & 0xFFFFFFDF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;
	}
}

/*********************************************************************************************************************
**  void void CGame::SetIceFlag(short sOwnerH, char cOwnerType, bool bStatus)										**
**  description			:: changes the status of the player to show frozen aura										**
**  last updated		:: November 20, 2004; 9:35 PM; Hypnotoad													**
**	return value		:: void																						**
*********************************************************************************************************************/
void CGame::SetIceFlag(short sOwnerH, char cOwnerType, bool bStatus)
{
	switch (cOwnerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x00000040;
		else m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xFFFFFFBF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus | 0x00000040;
		else m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus & 0xFFFFFFBF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;
	}
}

/*********************************************************************************************************************
**  void void CGame::SetPoisonFlag(short sOwnerH, char cOwnerType, bool bStatus)									**
**  description			:: changes the status of the player to show poison aura										**
**  last updated		:: November 20, 2004; 9:36 PM; Hypnotoad													**
**	return value		:: void																						**
*********************************************************************************************************************/
void CGame::SetPoisonFlag(short sOwnerH, char cOwnerType, bool bStatus)
{
	switch (cOwnerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x00000080;
		else m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xFFFFFF7F;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus | 0x00000080;
		else m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus & 0xFFFFFF7F;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;
	}
}

/*********************************************************************************************************************
**  void void CGame::SetIllusionFlag(short sOwnerH, char cOwnerType, bool bStatus)									**
**  description			:: changes the status of the player to show illusion aura									**
**  last updated		:: November 20, 2004; 9:36 PM; Hypnotoad													**
**	return value		:: void																						**
*********************************************************************************************************************/
void CGame::SetIllusionFlag(short sOwnerH, char cOwnerType, bool bStatus)
{
	switch (cOwnerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x01000000;
		else m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xFEFFFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus | 0x01000000;
		else m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus & 0xFEFFFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;
	}
}

/*********************************************************************************************************************
**  void void CGame::SetHeroFlag(short sOwnerH, char cOwnerType, bool bStatus)										**
**  description			:: changes the status of the player to show hero item aura									**
**  last updated		:: November 20, 2004; 9:37 PM; Hypnotoad													**
**	return value		:: void																						**
*********************************************************************************************************************/
void CGame::SetHeroFlag(short sOwnerH, char cOwnerType, bool bStatus)
{
	switch (cOwnerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x00020000;
		else m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xFFFDFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus | 0x00020000;
		else m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus & 0xFFFDFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;
	}
}

/*********************************************************************************************************************
**  void void CGame::SetDefenseShieldFlag(short sOwnerH, char cOwnerType, bool bStatus)								**
**  description			:: changes the status of the player to show defense aura									**
**  last updated		:: November 20, 2004; 9:37 PM; Hypnotoad													**
**	return value		:: void																						**
*********************************************************************************************************************/
void CGame::SetDefenseShieldFlag(short sOwnerH, char cOwnerType, bool bStatus)
{
	switch (cOwnerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x02000000;
		else m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xFDFFFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus | 0x02000000;
		else m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus & 0xFDFFFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;
	}
}

/*********************************************************************************************************************
**  void void CGame::SetMagicProtectionFlag(short sOwnerH, char cOwnerType, bool bStatus)							**
**  description			:: changes the status of the player to show magic protect aura								**
**  last updated		:: November 20, 2004; 9:38 PM; Hypnotoad													**
**	return value		:: void																						**
*********************************************************************************************************************/
void CGame::SetMagicProtectionFlag(short sOwnerH, char cOwnerType, bool bStatus)
{
	switch (cOwnerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x04000000;
		else m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xFBFFFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus | 0x04000000;
		else m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus & 0xFBFFFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;
	}
}

/*********************************************************************************************************************
**  void void CGame::SetProtectionFromArrowFlag(short sOwnerH, char cOwnerType, bool bStatus)						**
**  description			:: changes the status of the player to show arrow protect aura								**
**  last updated		:: November 20, 2004; 9:39 PM; Hypnotoad													**
**	return value		:: void																						**
*********************************************************************************************************************/
void CGame::SetProtectionFromArrowFlag(short sOwnerH, char cOwnerType, bool bStatus)
{
	switch (cOwnerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x08000000;
		else m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xF7FFFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus | 0x08000000;
		else m_pNpcList[sOwnerH]->m_iStatus = m_pNpcList[sOwnerH]->m_iStatus & 0xF7FFFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;
	}
}

/*********************************************************************************************************************
**  void void CGame::SetIllusionMovementFlag(short sOwnerH, char cOwnerType, bool bStatus)							**
**  description			:: changes the status of the player to show illusion movement aura							**
**  last updated		:: November 20, 2004; 9:39 PM; Hypnotoad													**
**	return value		:: void																						**
*********************************************************************************************************************/
void CGame::SetIllusionMovementFlag(short sOwnerH, char cOwnerType, bool bStatus)
{
	switch (cOwnerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sOwnerH] == 0) return;
		if (bStatus == true)
			m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x00200000;
		else m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xFFDFFFFF;
		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
		break;
	}
}

/*********************************************************************************************************************
**  void CGame::PlayerMagicHandler(int iClientH, int dX, int dY, short sType, bool bItemEffect, int iV1)			**
**  description			:: handles all magic related items/spells													**
**  last updated		:: November 22, 2004; 5:45 PM; Hypnotoad													**
**	return value		:: void																						**
**  commentary			::	-	added 3.51 casting detection														**
**							-	updated it so civilians can only cast certain spells on players and vice versa		**
**							-	fixed bug causing spell to be cast when mana is below required amount				**
**********************************************************************************************************************/
int  _tmp_iMCProb[] = { 0, 300, 250, 200, 150, 100, 80, 70, 60, 50, 40 };
int  _tmp_iMLevelPenalty[] = { 0,   5,   5,   8,   8,  10, 14, 28, 32, 36, 40 };
void CGame::PlayerMagicHandler(int iClientH, int dX, int dY, short sType, bool bItemEffect, int iV1, bool bIgnoreOwnerLimits)
{
	short* sp, sX, sY, sOwnerH, sMagicCircle, rx, ry, sLevelMagic, sTemp;
	char* cp, cData[120], cDir, cOwnerType, cName[11], cItemName[21], cNpcWaypoint[11], cName_Master[11], cNpcName[21], cRemainItemColor;
	double dV1, dV2, dV3, dV4;
	int    i, iErr, iRet, ix, iy, iResult, iDiceRes, iNamingValue, iFollowersNum, iEraseReq, iWhetherBonus;
	int    tX, tY, iManaCost, iMagicAttr;
	class  CItem* pItem;
	DWORD* dwp, dwTime, dwRemainItemAttr;
	WORD* wp, wWeaponType;
	short sEqStatus = -1, sRemainItemID;

	dwTime = timeGetTime();

	if (m_pClientList[iClientH] == 0) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == false) return;

	if ((dX < 0) || (dX >= m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_sSizeX) ||
		(dY < 0) || (dY >= m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_sSizeY)) return;

	if (((dwTime - m_pClientList[iClientH]->m_dwRecentAttackTime) < 1000) && (bItemEffect == 0)) {
		wsprintf(G_cTxt, "(!) 3.51 Detection: (%s) Player: (%s) - Magic casting speed is too fast! Hack?", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
		PutHackLogFileList(G_cTxt);
		//DeleteClient(iClientH, true, true);
		return;
	}
	m_pClientList[iClientH]->m_dwRecentAttackTime = dwTime;
	m_pClientList[iClientH]->m_dwLastActionTime = dwTime;//m_pClientList[iClientH]->m_dwAFKCheckTime = dwTime;
	m_pClientList[iClientH]->m_bMagicConfirm = true; 
	if (m_pClientList[iClientH]->m_cMapIndex < 0) return;
	if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex] == 0) return;

	if ((sType < 0) || (sType >= 100))     return;
	if (m_pMagicConfigList[sType] == 0) return;

	//Magn0S:: Set Map Restrictions
	if ((sType == 32) && (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bMapInvi == false) && (m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
		SendNotifyMsg(0, iClientH, DEF_NOTIFY_IPACCOUNTINFO, 0, 0, 0, "Invisibility Effect is disabled in this map.");
		return;
	}
	if ((sType == 65) && (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bMapAMP == false) && (m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
		SendNotifyMsg(0, iClientH, DEF_NOTIFY_IPACCOUNTINFO, 0, 0, 0, "AMP Effect is disabled in this map.");
		return;
	}

	if ((bItemEffect == false) && (m_pClientList[iClientH]->m_cMagicMastery[sType] != 1)) return;

	if ((m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsAttackEnabled == false) && (m_pClientList[iClientH]->m_iAdminUserLevel == 0)) return;

	if (!bIgnoreOwnerLimits) {
		if (((m_pClientList[iClientH]->m_iStatus & 0x100000) != 0) && (bItemEffect != true)) {
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, -1, 0);
			return;
		}

		if (m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND] != -1) {
			wWeaponType = ((m_pClientList[iClientH]->m_sAppr2 & 0x0FF0) >> 4);
			if ((wWeaponType < 34) || (wWeaponType > 39))
				return;
		}

		if ((m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND] != -1) ||
			(m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1)) return;

		if ((m_pClientList[iClientH]->m_iSpellCount > 1) && (bItemEffect == false)) {
			wsprintf(G_cTxt, "TSearch Spell Hack: (%s) Player: (%s) - casting magic without precasting.", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
			PutHackLogFileList(G_cTxt);
			//DeleteClient(iClientH, true, true);
			return;
		}

		//Magn0S:: Add to decreased the endurace of wands.
		if (m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1)
			sEqStatus = m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
		else sEqStatus = m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];

		if (sEqStatus != -1) {

			if ((m_pClientList[iClientH]->m_pItemList[sEqStatus] != 0) &&
				(m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wMaxLifeSpan != 0)) {

				if (m_pClientList[iClientH]->m_cSide != 0) {
					if (m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wCurLifeSpan <= 0)
						m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wCurLifeSpan = 0;
					else m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wCurLifeSpan--;
					SendNotifyMsg(0, iClientH, DEF_NOTIFY_CURLIFESPAN, sEqStatus, m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wCurLifeSpan, 0, 0);
				}

				if (m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wCurLifeSpan == 0) {
					SendNotifyMsg(0, iClientH, DEF_NOTIFY_ITEMLIFESPANEND, m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_cEquipPos, sEqStatus, 0, 0);
					ReleaseItemHandler(iClientH, sEqStatus, true);
				}
			}
		}

		if (m_pClientList[iClientH]->m_bInhibition == true) {
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, -1, 0);
			return;
		}

		if (m_pMagicConfigList[sType]->m_sType == 32) { // Invisiblity
			sEqStatus = m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
			if ((sEqStatus != -1) && (m_pClientList[iClientH]->m_pItemList[sEqStatus] != 0)) {
				if ((m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_sIDnum == 865) || (m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_sIDnum == 866)) {
					bItemEffect = true;
				}
			}
		}
	}

	sX = m_pClientList[iClientH]->m_sX;
	sY = m_pClientList[iClientH]->m_sY;

	sMagicCircle = (sType / 10) + 1;
	if (m_pClientList[iClientH]->m_cSkillMastery[4] == 0)
		dV1 = 1.0f;
	else dV1 = (double)m_pClientList[iClientH]->m_cSkillMastery[4];

	if (bItemEffect == true) dV1 = (double)100.0f;
	dV2 = (double)(dV1 / 100.0f);
	dV3 = (double)_tmp_iMCProb[sMagicCircle];
	dV1 = dV2 * dV3;
	iResult = (int)dV1;

	if ((m_pClientList[iClientH]->m_iInt) > 50)
		iResult += ((m_pClientList[iClientH]->m_iInt) - 50) / 2;

	sLevelMagic = ((m_pClientList[iClientH]->m_iLevel) / 10);
	if (sMagicCircle != sLevelMagic) {
		if (sMagicCircle > sLevelMagic) {
			dV1 = (double)((m_pClientList[iClientH]->m_iLevel) - sLevelMagic * 10);
			dV2 = (double)abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle];
			dV3 = (double)abs(sMagicCircle - sLevelMagic) * 10;
			dV4 = (dV1 / dV3) * dV2;
			iResult -= abs(abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle] - (int)dV4);
		}
		else {
			iResult += 5 * abs(sMagicCircle - sLevelMagic);
		}
	}

	switch (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cWhetherStatus) {
	case 0: break;
	case 1: iResult = iResult - (iResult / 24); break;
	case 2:	iResult = iResult - (iResult / 12); break;
	case 3: iResult = iResult - (iResult / 5);  break;
	}

	if (m_pClientList[iClientH]->m_iSpecialWeaponEffectType == 10) {
		dV1 = (double)iResult;
		dV2 = (double)(m_pClientList[iClientH]->m_iSpecialWeaponEffectValue * 3);
		dV3 = dV1 + dV2;
		iResult = (int)dV3;
	}

	if (iResult <= 0) iResult = 1;

	iWhetherBonus = iGetWhetherMagicBonusEffect(sType, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cWhetherStatus);

	iManaCost = m_pMagicConfigList[sType]->m_sValue1;
	if ((m_pClientList[iClientH]->m_bIsSafeAttackMode == true) &&
		(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsFightZone == false)) {
		//SNOOPY: Spell in safe mode only cost 10% more	
		iManaCost += (iManaCost / 10);
	}

	if (m_pClientList[iClientH]->m_iManaSaveRatio > 0) {
		dV1 = (double)m_pClientList[iClientH]->m_iManaSaveRatio;
		dV2 = (double)(dV1 / 100.0f);
		dV3 = (double)iManaCost;
		dV1 = dV2 * dV3;
		dV2 = dV3 - dV1;
		iManaCost = (int)dV2;

		if (iManaCost <= 0) iManaCost = 1;
	}

	wWeaponType = ((m_pClientList[iClientH]->m_sAppr2 & 0x0FF0) >> 4);
	if (wWeaponType == 34) {
		iManaCost += 20;
	}

	if (iResult < 100) {
		iDiceRes = iDice(1, 100);
		if (iResult < iDiceRes) {
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, -1, 0);
			return;
		}
	}

	if (((m_pClientList[iClientH]->m_iHungerStatus <= 10) || (m_pClientList[iClientH]->m_iSP <= 0)) && (iDice(1, 1000) <= 100)) {
		SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, -1, 0);
		return;
	}

	if (!bIgnoreOwnerLimits && m_pClientList[iClientH]->m_iMP < iManaCost) {
		return;
	}

	iResult = m_pClientList[iClientH]->m_cSkillMastery[4];
	if ((m_pClientList[iClientH]->m_iMag) > 50) iResult += ((m_pClientList[iClientH]->m_iMag) - 50);

	sLevelMagic = ((m_pClientList[iClientH]->m_iLevel) / 10);
	if (sMagicCircle != sLevelMagic) {
		if (sMagicCircle > sLevelMagic) {
			dV1 = (double)((m_pClientList[iClientH]->m_iLevel) - sLevelMagic * 10);
			dV2 = (double)abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle];
			dV3 = (double)abs(sMagicCircle - sLevelMagic) * 10;
			dV4 = (dV1 / dV3) * dV2;

			iResult -= abs(abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle] - (int)dV4);
		}
		else {
			iResult += 5 * abs(sMagicCircle - sLevelMagic); 
		}
	}

	iResult += m_pClientList[iClientH]->m_iMagicHitRatio_ItemEffect; // snoopy
	iResult += m_pClientList[iClientH]->m_iAddAR;
	if (iResult <= 0) iResult = 1;

	if (sType >= 80) iResult += 10000;

	if (m_pMagicConfigList[sType]->m_sType == 28) {
		iResult += 10000;
	}

	if (m_pMagicConfigList[sType]->m_cCategory == 1) {
		if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->iGetAttribute(sX, sY, 0x00000005) != 0) return;
	}

	iMagicAttr = m_pMagicConfigList[sType]->m_iAttribute;
	if ((m_pClientList[iClientH]->m_iStatus & 0x10) != 0 && !bIgnoreOwnerLimits) {
		SetInvisibilityFlag(iClientH, DEF_OWNERTYPE_PLAYER, false);
		bRemoveFromDelayEventList(iClientH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INVISIBILITY);
		m_pClientList[iClientH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
	}

	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
	if ((m_bIsCrusadeMode == false) && (cOwnerType == DEF_OWNERTYPE_PLAYER)) {
		if ((m_pClientList[iClientH]->m_bIsPlayerCivil != true) && (m_pClientList[sOwnerH]->m_bIsPlayerCivil == true)) {
			if (m_pClientList[iClientH]->m_cSide != m_pClientList[sOwnerH]->m_cSide) return;
		}
		else if ((m_pClientList[iClientH]->m_bIsPlayerCivil == true) && (m_pClientList[sOwnerH]->m_bIsPlayerCivil == false)) {
			switch (m_pMagicConfigList[sType]->m_sType) {
			case 1:  // DEF_MAGICTYPE_DAMAGE_SPOT
			case 4:  // DEF_MAGICTYPE_SPDOWN_SPOT 4
			case 8:  // DEF_MAGICTYPE_TELEPORT 8
			case 10: // DEF_MAGICTYPE_CREATE 10
			case 11: // DEF_MAGICTYPE_PROTECT 11
			case 12: // DEF_MAGICTYPE_HOLDOBJECT 12
			case 16: // DEF_MAGICTYPE_CONFUSE
			case 17: // DEF_MAGICTYPE_POISON
			case 24: // DEF_MAGICTYPE_RESURRECTION
				goto MAGIC_NOEFFECT;

			}
		}
	}

	if (m_pMagicConfigList[sType]->m_dwDelayTime == 0) {
		switch (m_pMagicConfigList[sType]->m_sType) {

		case DEF_MAGICTYPE_DAMAGE_SPOT:
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}
			break;

		case DEF_MAGICTYPE_HPUP_SPOT:
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			Effect_HpUp_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6);
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA:
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}

			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_SPDOWN_SPOT:
			break;

		case DEF_MAGICTYPE_SPDOWN_AREA:
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6);
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
				}
			break;

		case DEF_MAGICTYPE_POLYMORPH: // [20] Polymorph
			/*
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			switch (cOwnerType) {
			case DEF_OWNERTYPE_PLAYER:
				if (m_pClientList[iClientH] == 0) goto MAGIC_NOEFFECT;
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[iClientH] != m_pClientList[sOwnerH])) break;
				if (m_pClientList[iClientH]->m_cMagicEffectStatus[DEF_MAGICTYPE_POLYMORPH] != 0) goto MAGIC_NOEFFECT;
				m_pClientList[iClientH]->m_sOriginalType = m_pClientList[sOwnerH]->m_sType;
				switch (iDice(1, 8)) {
				case 1: m_pClientList[iClientH]->m_sType = 29; break;
				case 2: m_pClientList[iClientH]->m_sType = 14; break;
				case 3: m_pClientList[iClientH]->m_sType = 11; break;
				case 4: m_pClientList[iClientH]->m_sType = 18; break;
				case 5: m_pClientList[iClientH]->m_sType = 12; break;
				case 6: m_pClientList[iClientH]->m_sType = 23; break;
				case 7: m_pClientList[iClientH]->m_sType = 28; break;
				case 8: m_pClientList[iClientH]->m_sType = 13; break;
				}
				m_pClientList[sOwnerH]->m_bIsPolymorph = true;
				ToggleCombatModeHandler(iClientH);
				break;
			}
			SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
			bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_POLYMORPH, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime * 1000),
				sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);
			if (cOwnerType == DEF_OWNERTYPE_PLAYER)	SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_POLYMORPH, m_pMagicConfigList[sType]->m_sValue4, 0, 0);
			*/
			goto MAGIC_NOEFFECT;
			break;

		case DEF_MAGICTYPE_HELLFIRE:
			iMagicAttr = 3;
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			ShowSpellEffect2(sOwnerH, 99, cOwnerType);
			
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, 23, 24, 0 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, 23, 24, 0 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break; //end hellfire

		case DEF_MAGICTYPE_FURYOFTHOR:
			sX = m_pClientList[iClientH]->m_sX;
			sY = m_pClientList[iClientH]->m_sY;

			for (i = 2; i < 10; i++) {
				iErr = 0;
				m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx-1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);

						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);

						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx+1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx, ty-1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx, ty+1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);

								}
								break;
							}
							//
						}
					}
				}

			// dX, dY
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
					}
					break;
				}
				//
			}

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);

						}
						break;
					}
					//
				}
			}
			break;

		

			// 05/20/2004 - Hypnotoad - Cancellation
		case DEF_MAGICTYPE_CANCELLATION:
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0) && (m_pClientList[sOwnerH]->m_iAdminUserLevel == 0)) {

				// Removes Invisibility Flag 0x0010
				SetInvisibilityFlag(sOwnerH, cOwnerType, false);

				// Removes Illusion Flag 0x01000000
				SetIllusionFlag(sOwnerH, cOwnerType, false);

				// Removes Defense Shield Flag 0x02000000
				// Removes Great Defense Shield Flag 0x02000000
				SetDefenseShieldFlag(sOwnerH, cOwnerType, false);

				// Removes Absolute Magic Protection Flag 0x04000000	
				// Removes Protection From Magic Flag 0x04000000
				SetMagicProtectionFlag(sOwnerH, cOwnerType, false);

				// Removes Protection From Arrow Flag 0x08000000
				SetProtectionFromArrowFlag(sOwnerH, cOwnerType, false);

				// Removes Illusion Movement Flag 0x00200000
				SetIllusionMovementFlag(sOwnerH, cOwnerType, false);

				// Removes Berserk Flag 0x0020
				SetBerserkFlag(sOwnerH, cOwnerType, false);

				if (m_pClientList[iClientH]->m_bInhibition == true)
					bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INHIBITION);
				bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_INHIBITION, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if (m_pClientList[iClientH]->m_iStatus & 0x0010)
					bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INVISIBILITY);
				bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_INVISIBILITY, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if (m_pClientList[iClientH]->m_iStatus & 0x0020)
					bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_BERSERK);
				bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_BERSERK, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if ((m_pClientList[iClientH]->m_iStatus & 0x08000000) || (m_pClientList[iClientH]->m_iStatus & 0x04000000) || (m_pClientList[iClientH]->m_iStatus & 0x02000000))
					bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_PROTECT);
				bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_PROTECT, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if ((m_pClientList[iClientH]->m_iStatus & 0x01000000) || (m_pClientList[iClientH]->m_iStatus & 0x00200000))
					bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_CONFUSE);
				bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_CONFUSE, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime),
					sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				// Update Client
				SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
			}
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT_SPDOWN:
			// 직격은 처리하지 않는다.
			// 주변 공격 효과 
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// 자신도 피폭될 수 있으니 주의.
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
						Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
					}

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						// 죽은 척하고 있는 플레이어다.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
					}
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_LINEAR:
			// 횄�궗횄혧횄혖횄쨌횂쩌횂짹 횂쨩횄쨀횂쩔횂징 횄�궗횄��벭궰늘꺿�� 횂쨍횄짹횄��≥궰Γ궰맡궰� 횂쨍횄째횂쨉횄탐 횂째횄쨍횂째횄혶횄��≥꺿�샖궰늘꺿꽓.
			sX = m_pClientList[iClientH]->m_sX;
			sY = m_pClientList[iClientH]->m_sY;

			for (i = 2; i < 10; i++) {
				iErr = 0;
				m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx-1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx+1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx, ty-1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				// tx, ty+1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			// 횄혖횄��벭궰봤궰� 횂째횄쨍횂째횄혶 횄�녍궰올궰걘꺜� 
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// 횄�궗횄큄횂쩍횄��┚궰돤궰� 횄��≥꺿�≥꺿�졗꺜맡궰돤꺿�� 횂쩌횄쨋 횄�궗횄��벭꺿궗횂쨍횂쨈횄혧 횄혖횄��벭꺿궗횄���.
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}

			// dX, dY
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
			}
			break;

			// v2.16 2002-5-23 횂째횄짯횂짹횂짚횄��≥꺜� 
		case DEF_MAGICTYPE_ICE_LINEAR:
			// 횄�궗횄혧횄혖횄쨌횂쩌횂짹 횂쨩횄쨀횂쩔횂징 횄�궗횄��벭궰늘꺿�� 횂쨍횄짹횄��≥궰Γ궰맡궰� 횂쨍횄째횂쨉횄탐 횂쩐횄쨀횂쨍횂짰횂쨍횄짠 횂째횄쨍횂째횄혶횄��≥꺿�샖궰늘꺿꽓.
			sX = m_pClientList[iClientH]->m_sX;
			sY = m_pClientList[iClientH]->m_sY;

			for (i = 2; i < 4; i++) { 
				iErr = 0;
				m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (m_pClientList[sOwnerH]->m_iHP < 0) goto MAGIC_NOEFFECT;
						// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}
				}

				// tx-1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}
				}

				// tx+1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}
				}

				// tx, ty-1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}
				}

				// tx, ty+1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			// 횄혖횄��벭궰봤궰� 횂째횄쨍횂째횄혶 횄�녍궰올궰걘꺜� 
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// 횄�궗횄큄횂쩍횄��┚궰돤궰� 횄��≥꺿�≥꺿�졗꺜맡궰돤꺿�� 횂쩌횄쨋 횄�궗횄��벭꺿궗횂쨍횂쨈횄혧 횄혖횄��벭꺿궗횄���.
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
						//
					}

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
							// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
								if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
									if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
										m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
										SetIceFlag(sOwnerH, cOwnerType, true);
										// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
										bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
											sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
										// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
										SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
									}
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
									if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
										m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
										SetIceFlag(sOwnerH, cOwnerType, true);
										// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
										bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
											sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									}
								}
								break;
							}
							//
						}
					}
				}

			// dX, dY
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
				// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
					if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
						if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
							m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							SetIceFlag(sOwnerH, cOwnerType, true);
							// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
							bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
								sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
							SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
						}
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
						if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
							m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							SetIceFlag(sOwnerH, cOwnerType, true);
							// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
							bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
								sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
						}
					}
					break;
				}
				//
			}

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
					// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
					//
				}
			}
			break;


		case DEF_MAGICTYPE_INHIBITION:
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			switch (cOwnerType) {
			case DEF_OWNERTYPE_PLAYER:
				if ((m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 5) || (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 2)) goto MAGIC_NOEFFECT; // juan - ic fix para que no pegue si tiene AMP o PFM .
				if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
				if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INHIBITION] != 0) goto MAGIC_NOEFFECT;
				if (memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;
				m_pClientList[sOwnerH]->m_bInhibition = true;
				bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_INHIBITION, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				break;
			}
			break;


		case DEF_MAGICTYPE_TREMOR: // v1.4 횄혖횄��벭궰봤궰� 횂째횄쨍횂째횄혶 횄�녍궰올궰걘꺜봤궰올궰� 횄�궗횄흸횂쩐횄짰 횄�궗횄흹횂쨌횄쨔 횄�녍궰올궰걘꺜봤궰걘궰� 횄�궗횄��벭궰늘꺿꽓.
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}

			// 횄혖횄��벭궰봤궰� 횂째횄쨍횂째횄혶 횄�녍궰올궰걘꺜� 
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// 횄�궗횄큄횂쩍횄��┚궰돤궰� 횄��≥꺿�≥꺿�졗꺜맡궰돤꺿�� 횂쩌횄쨋 횄�궗횄��벭꺿궗횂쨍횂쨈횄혧 횄혖횄��벭꺿궗횄���.
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT:
			// 횄혖횄쨌횂째횄혶횄�궗횂쨘 횄�뮼궰냉궰맡궰�횄��≥꺜뤓꺜겷꺜� 횂쩐횄힋횂쨈횄��싀궰늘꺿꽓.
			// 횄혖횄��벭궰봤궰� 횂째횄쨍횂째횄혶 횄�녍궰올궰걘꺜� 
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// 횄�궗횄큄횂쩍횄��┚궰돤궰� 횄��≥꺿�≥꺿�졗꺜맡궰돤꺿�� 횂쩌횄쨋 횄�궗횄��벭꺿궗횂쨍횂쨈횄혧 횄혖횄��벭꺿궗횄���.
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_SPUP_AREA:
			// Sp횂째횂징 횂쨩횄쨀횂쩍횄��싀꺿�≥꺿�샖궰늘꺿꽓.
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			// 횂쨍횂쨋횂쨔횄쩍 횄�궗횄쨘횄��≥꺿�붌꺿궗횄흸 횄��≥꺟졗궰올꺜ㅓ궰씹꺜맡궰늘꺿꽓. 
			Effect_SpUp_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6);
			// 횄혖횄��벭궰봤궰� 횂째횄쨍횂째횄혶 횄�녍궰올궰걘꺜� 
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// 횄�궗횄큄횂쩍횄��┚궰돤궰� 횄��≥꺿�≥꺿�졗꺜맡궰돤꺿�� 횂쩌횄쨋 횄�궗횄��벭꺿궗횂쨍횂쨈횄혧 횄혖횄��벭꺿궗횄���.
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					// 횂쨍횂쨋횂쨔횄쩍횄�궗횄쨘횄��≥꺿�붌꺿궗횄흸 횄��≥꺟졗궰올꺜� 횂쩐횄쨍횂쨈횄�꽓.
					Effect_SpUp_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_LINEAR_SPDOWN:
			// ��횕횁첨쩌짹 쨩처쩔징 ��횜쨈횂 쨍챰횉짜쨍짝 쨍챨쨉횓 쩐처쨍짰쨍챌 째첩째횦횉횗쨈횢.
			sX = m_pClientList[iClientH]->m_sX;
			sY = m_pClientList[iClientH]->m_sY;

			for (i = 2; i < 4; i++) {
				iErr = 0;
				m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횁횞��쨘 횄쨈횉횕째챠 ��횜쨈횂 횉횄쨌쨔��횑쩐챤쨈횢.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx-1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);

						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);

						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횁횞��쨘 횄쨈횉횕째챠 ��횜쨈횂 횉횄쨌쨔��횑쩐챤쨈횢.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx+1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횁횞��쨘 횄쨈횉횕째챠 ��횜쨈횂 횉횄쨌쨔��횑쩐챤쨈횢.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx, ty-1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횁횞��쨘 횄쨈횉횕째챠 ��횜쨈횂 횉횄쨌쨔��횑쩐챤쨈횢.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx, ty+1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					// 횁횞��쨘 횄쨈횉횕째챠 ��횜쨈횂 횉횄쨌쨔��횑쩐챤쨈횢.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			// 횁횜쨘짱 째첩째횦 횊쩔째첬 
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					// ��횣쩍횇쨉쨉 횉횉횈첩쨉횋 쩌철 ��횜��쨍쨈횕 횁횜��횉.
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						// 횁횞��쨘 횄쨈횉횕째챠 ��횜쨈횂 횉횄쨌쨔��횑쩐챤쨈횢.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
							// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
								if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);

								}
								break;
							}
							//
						}
					}
				}

			// dX, dY
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
				// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
					}
					break;
				}
				//
			}

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				// 횁횞��쨘 횄쨈횉횕째챠 ��횜쨈횂 횉횄쨌쨔��횑쩐챤쨈횢.
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
					// 쩐처쩐챤쩌짯 쨉쩔��횤��횑 쨈횎쩐챤횁철쨈횂 횊쩔째첬
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						// 횇쨍째횢��횑 쨩챙쩐횈��횜째챠 쩐처��쩍 ��첬횉횞쩔징 쩍횉횈횖횉횩쨈횢쨍챕 쩐처쩐챤쨘횢쨈횂쨈횢.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);

						}
						break;
					}
					//
				}
			}
			break;

		case DEF_MAGICTYPE_TELEPORT:
			// 횄��┚꺟≥궰련궰뮨꺿�졗꺜련꺿�졗궰� 횂쨍횂쨋횂쨔횄쩍. sValue 4횂쩔횂징 횂쨉횄쨩횂쨋횄쨀횂쩌횂짯 횄��┚꺟≥궰련궰뮨꺿�졗꺜련꺿�졗궰� 횂쨍횄짹횄�궗횄쨩횄혖횄쨋횂째횂징 횂째횄징횄혖횂짚횂쨉횄�녍궰늘꺿꽓.
			
			//50Cent - Capture The Flag
			if (m_bIsCTFEvent && (m_pClientList[iClientH]->m_iStatus & 0x80000) != 0)
			{
				ShowClientMsg(iClientH, "You can not use that magic being a flag carrier.");
				goto MAGIC_NOEFFECT;
			}

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

			switch (m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				// Centuu : Aresden cant recall in elvine & Elvine cant recall in aresden - Fixed
				if (m_pClientList[iClientH]->m_cSide == 2 && strcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "aresden") == 0) goto MAGIC_NOEFFECT;
				if (m_pClientList[iClientH]->m_cSide == 1 && strcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "elvine") == 0) goto MAGIC_NOEFFECT;

				// 횄�궗횄큄횂쩍횄��┚꺿궗횄흸 횂쩌횄��쇒궰셌꺿�쑦궰돤꺥� 횂쨍횂쨋횄�궗횂쨩횂쨌횄탐 횄��┚꺟≥궰련궰뮨꺿�졗꺜련꺿�졗궰�. Recall횄�궗횄흸횂쨈횄�꽓.
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (sOwnerH == iClientH)) {
					if (m_pClientList[iClientH]->IsInMap("team"))
					{
						if (m_pClientList[iClientH]->IsLocation("elvine"))
							RequestTeleportHandler(iClientH, "2", "elvine", -1, -1, true);
						else
							RequestTeleportHandler(iClientH, "2", "aresden", -1, -1, true);
					}
					else
					{
						RequestTeleportHandler(iClientH, "1   ");
					}
				}
				break;
			}
			break;

		case DEF_MAGICTYPE_SUMMON:
			// 횂쩌횄��쇒꺥녍궰�횂쨍횂쨋횂쨔횄쩍 

			// 횂쨩횄짠횄��┚꺜돤꺿궗횄짜 횂쨀횂쨩횂쩔횂징횂쩌횂짯횂쨈횄��� 횂쩌횄��쇒꺥녍궰�횂쨍횂쨋횂쨔횄쩍횄�궗횄흸 횂쨘횄��쇒궰걘궰≥궰늘꺿��.
			if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsFightZone == true) return;

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			// 횄혖횄쨋횄혖횂짚횂쨉횄�� Owner횂째횂징 Master횂째횂징 횂쨉횄�녍궰늘꺿꽓. 
			if ((sOwnerH != 0) && (cOwnerType == DEF_OWNERTYPE_PLAYER)) {
				// Master횂쨌횄탐 횄혖횄쨋횄혖횂짚횂쨉횄�� 횂쨈횄짬횂쨩횄쨀횄�궗횂쨩 횂쨉횄쨩횂쨋횄쨀횂쨈횄�꽓횂쨈횄혧횂째횄짯 횄�궗횄��벭궰늘꺿�� 횂째횂쨈횄�뮼궰� 횂쩌횄쨋횂쨍횂짝 횂째횄짢횂쨩횄짧횄��≥꺿�샖궰늘꺿꽓. 
				iFollowersNum = iGetFollowerNumber(sOwnerH, cOwnerType);

				// 횂쩌횄��쇒꺥녍궰�횂쨍횂쨋횂쨔횄쩍횄�궗횂쨩 Casting횄��≥꺿�� 횄�궗횄큄횄�궗횄��� Magery/20 횂쨍횂쨍횄��┚궰�횄�궗횄��� 횂쨍횄쨀횂쩍횂쨘횄��┚꺜띊궰맡궰� 횂쩌횄��쇒꺥녍궰�횄��≥꺿�� 횂쩌횄쨋 횄�궗횄��벭궰늘꺿꽓.
				if (iFollowersNum >= (m_pClientList[iClientH]->m_cSkillMastery[4] / 20)) break;

				iNamingValue = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->iGetEmptyNamingValue();
				if (iNamingValue != -1) {
					// 횂쨈횄쨉횄�궗횄흸횂쨩횄쨀 횄�궗횄흸 횂쨍횄힋횂쩔횂징 NPC횂쨍횂짝 횂쨍횂쨍횂쨉횄짤횂쩌횄쨋 횂쩐횄쨍횂쨈횄�꽓. 횄�궗횄흸횂쨍횂짠횄�궗횂쨩 횄��≥꺿�쇒궰늘꺜㎴꺿�≥꺿�� 횂쩌횄쨋 횂쩐횄쨍횂짹횄짖 횂쨋횂짠횂쨔횂짰.

					// NPC횂쨍횂짝 횂쨩횄쩍횂쩌횂쨘횄��≥꺿�샖궰늘꺿꽓.
					ZeroMemory(cName, sizeof(cName));
					wsprintf(cName, "XX%d", iNamingValue);
					cName[0] = '_';
					cName[1] = m_pClientList[iClientH]->m_cMapIndex + 65;

					// Magery횂쩔횂징 횂쨉횄쨩횂쨋횄쨀 횂쩌횄��쇒꺥녍궰�횂쨉횄��≥궰늘꺿�� 횂쨍횄쨀횂쩍횂쨘횄��┚꺜띊꺿궗횄��� 횂쨉횄짰횂짹횄탑횄�궗횄흸 횂쨈횄탑횂쨋횄쨀횄혖횄쨍횂쨈횄�꽓.
					ZeroMemory(cNpcName, sizeof(cNpcName));

					switch (iV1) {
					case 0: // 횄�궗횄혧횂쨔횄혶횄�궗횄쨩횄�궗횄탐 횂째횄짝횂쩔횄짭 
						iResult = iDice(1, m_pClientList[iClientH]->m_cSkillMastery[4] / 10);

						// v1.42 횄�뮼꺿�벭꺿궗횄쨘 횂쨍횄쨌 횂쨌횂쨔횂쨘횂짠횄�궗횂쨩 횄�궗횄��씳궰련꺿�� 
						if (iResult < m_pClientList[iClientH]->m_cSkillMastery[4] / 20)
							iResult = m_pClientList[iClientH]->m_cSkillMastery[4] / 20;

						switch (iResult) {
						case 1: strcpy(cNpcName, "Slime"); break;
						case 2: strcpy(cNpcName, "Giant-Ant"); break;
						case 3: strcpy(cNpcName, "Amphis"); break;
						case 4: strcpy(cNpcName, "Orc"); break;
						case 5: strcpy(cNpcName, "Skeleton"); break;
						case 6:	strcpy(cNpcName, "Clay-Golem"); break;
						case 7:	strcpy(cNpcName, "Stone-Golem"); break;
						case 8: strcpy(cNpcName, "Orc-Mage"); break;
						case 9:	strcpy(cNpcName, "Hellbound"); break;
						case 10:strcpy(cNpcName, "Cyclops"); break;
						}
						break;

					case 1:	strcpy(cNpcName, "Orc"); break;
					case 2: strcpy(cNpcName, "Skeleton"); break;
					case 3: strcpy(cNpcName, "Clay-Golem"); break;
					case 4: strcpy(cNpcName, "Stone-Golem"); break;
					case 5: strcpy(cNpcName, "Hellbound"); break;
					case 6: strcpy(cNpcName, "Cyclops"); break;
					case 7: strcpy(cNpcName, "Troll"); break;
					case 8: strcpy(cNpcName, "Orge"); break;
					case 9: // SummonScroll(SOR)
						switch (m_pClientList[iClientH]->m_cSide) {
						case 1:  strcpy(cNpcName, "Sor-Aresden"); break;
						case 2:  strcpy(cNpcName, "Sor-Elvine"); break;
						}
						break;
					case 10: // SummonScroll(ATK)
						switch (m_pClientList[iClientH]->m_cSide) {
						case 1:  strcpy(cNpcName, "ATK-Aresden"); break;
						case 2:  strcpy(cNpcName, "ATK-Elvine"); break;
						}
						break;
					case 11: // SummonScroll(ELF)
						switch (m_pClientList[iClientH]->m_cSide) {
						case 1:  strcpy(cNpcName, "Elf-Aresden"); break;
						case 2:  strcpy(cNpcName, "Elf-Elvine"); break;
						}
						break;
					case 12: // SummonScroll(DSK)	
						switch (m_pClientList[iClientH]->m_cSide) {
						case 1:  strcpy(cNpcName, "DSK-Aresden"); break;
						case 2:  strcpy(cNpcName, "DSK-Elvine"); break;
						}
						break;
					case 13: // SummonScroll(HBT)
						switch (m_pClientList[iClientH]->m_cSide) {
						case 1:  strcpy(cNpcName, "HBT-Aresden"); break;
						case 2:  strcpy(cNpcName, "HBT-Elvine"); break;
						}
						break;
					case 14: // SummonScroll(BAR)
						switch (m_pClientList[iClientH]->m_cSide) {
						case 1:  strcpy(cNpcName, "Bar-Aresden"); break;
						case 2:  strcpy(cNpcName, "Bar-Elvine"); break;
						}
						break;
					}

					if (bCreateNewNpc(cNpcName, cName, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, 0, 0, DEF_MOVETYPE_RANDOM, &dX, &dY, cNpcWaypoint, 0, 0, m_pClientList[iClientH]->m_cSide, false, true) == false) {
						// 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡꺿궗횂쨍횂쨔횄��≥궰련꺟� 횂쩔횂쨔횂쩐횄혻횂쨉횄�� NameValue횂쨍횂짝 횄��≥꺥쑦꺜겷궰┚궰시꺠뮼꺿�┚궰꼴궰늘꺿꽓.
						m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetNamingValueEmpty(iNamingValue);
					}
					else {
						ZeroMemory(cName_Master, sizeof(cName_Master));
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							memcpy(cName_Master, m_pClientList[sOwnerH]->m_cCharName, 10);
							break;
						case DEF_OWNERTYPE_NPC:
							memcpy(cName_Master, m_pNpcList[sOwnerH]->m_cName, 5);
							break;
						}
						bSetNpcFollowMode(cName, cName_Master, cOwnerType);
					}
				}
			}
			break;

		case DEF_MAGICTYPE_CREATE:
			// 횂쨔횂짬횂쩐횄째횂째횂징횂쨍횂짝 횂쨩횄쩍횂쩌횂쨘횂쩍횄�뮼꺿�┚궰걘궰늘꺿�� 횂쨍횂쨋횂쨔횄쩍 

			// 횄�궗횂짠횄��왗궰≥꺿�≥꺿�� 횂쩌횄쨋 횂쩐횄쨍횂쨈횄��� 횂째횄쨌횂쩔횂징횂쨈횄��� 횂쨩횄쩍횂짹횄짖횄혖횄쨋 횂쩐횄힋횂쨈횄��싀궰늘꺿꽓. 
			if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bGetIsMoveAllowedTile(dX, dY) == false)
				goto MAGIC_NOEFFECT;

			pItem = new class CItem;

			switch (m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				// Food
				if (iDice(1, 2) == 1)
					wsprintf(cItemName, "Meat");
				else wsprintf(cItemName, "Baguette");
				break;
			}

			_bInitItemAttr(pItem, cItemName);

			// v2.15 횂쨍횂쨋횂쨔횄쩍횄�궗횂쨍횂쨌횄탐 횂쨩횄쩍횂짹횄짚 횂쩐횄��졗꺿궗횄흸횄��┚꺿�봤궰올궰� 횂째횄짯횄�궗횂짱횂쨔횄쨍횄�녍궰� 횄�궗횄쨘횄�궗횄짜 
			pItem->m_sTouchEffectType = DEF_ITET_ID;
			pItem->m_sTouchEffectValue1 = iDice(1, 100000);
			pItem->m_sTouchEffectValue2 = iDice(1, 100000);
			pItem->m_sTouchEffectValue3 = (short)timeGetTime();

			// 횂쩐횄��졗꺿궗횄흸횄��┚꺿�봤꺿궗횂쨩 횂쩌횂짯횄�궗횄��벭궰늘꺿�� 횄�궗횂짠횄��왗궰≥궰올궰� 횂쨔횄쨋횂쨍횂째횂쨈횄�꽓. 
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bSetItem(dX, dY, pItem);

			// v1.41 횄�녍꺜궁궰궁꺜� 횂쩐횄��졗꺿궗횄흸횄��┚꺿�봤꺿궗횂쨩 횂쨋횂쨀횂쩐횄짰횂쨋횄타횂쨍횂째 횂째횄혥횄�궗횄흸횂쨋횄쨀횂쨍횄짤 횂쨌횄탐횂짹횄��붌궰맡궰� 횂쨀횂짼횂짹횄짚횂쨈횄�꽓. 
			_bItemLog(DEF_ITEMLOG_DROP, iClientH, (int)-1, pItem);

			// 횂쨈횄�꽓횂쨍횂짜 횄��┚궰�횂쨋횄쨀횄�궗횄흸횂쩐횄째횄��졗궰�횂쩔횂징횂째횄��� 횂쩐횄��졗꺿궗횄흸횄��┚꺿�봤꺿궗횄흸 횂쨋횂쨀횂쩐횄짰횄혖횄쨍 횂째횄혥횄�궗횂쨩 횂쩐횄��뮨궰맡궰걘궰늘꺿꽓. 
			//SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_ITEMDROP, m_pClientList[iClientH]->m_cMapIndex,
			//	dX, dY, pItem->m_sSprite, pItem->m_sSpriteFrame, pItem->m_cItemColor); // v1.4 color
			SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_ITEMDROP, m_pClientList[iClientH]->m_cMapIndex,
				dX, dY, pItem->m_sIDnum, pItem->m_sSpriteFrame, pItem->m_cItemColor, pItem->m_dwAttribute);
			break;

		case DEF_MAGICTYPE_CREATEPOTION:
			// esto define el tipo de magia

			/*
			if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bGetIsMoveAllowedTile(dX, dY) == false)
				goto MAGIC_NOEFFECT;

			pItem = new class CItem;

			switch (m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				// Potion
				if (iDice(1, 2) == 1)
					wsprintf(cItemName, "RedCandy");
				else wsprintf(cItemName, "BlueCandy");
				break;
			}

			_bInitItemAttr(pItem, cItemName);

			pItem->m_sTouchEffectType = DEF_ITET_ID;
			pItem->m_sTouchEffectValue1 = iDice(1, 100000);
			pItem->m_sTouchEffectValue2 = iDice(1, 100000);
			pItem->m_sTouchEffectValue3 = (short)timeGetTime();

			//indica las cordenadas en donde estas
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bSetItem(dX, dY, pItem);

			_bItemLog(DEF_ITEMLOG_DROP, iClientH, (int)-1, pItem);
			// Aca dice que tire el item abajo tullo
			SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_ITEMDROP, m_pClientList[iClientH]->m_cMapIndex,
				dX, dY, pItem->m_sSprite, pItem->m_sSpriteFrame, pItem->m_cItemColor); // v1.4 color
			*/
			goto MAGIC_NOEFFECT;
			break;

		case DEF_MAGICTYPE_PROTECT:
			// 횂쨘횂쨍횄�녍궰� 횂쨍횂쨋횂쨔횄쩍 
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

			// 횂쨘횂쨍횄�녍궰� 횂쨩횄쨀횄��┚꺿�싀궰뗐꺜냉궰늘꺿�� 횂째횄혥횄�궗횂쨩 횂쩌횂쨀횄혖횂짚횄��≥꺜뤓궰궁꺜� 횄�궗횄쩌횂쩔횂징 횄�궗횄흸횂쨔횄흸 횄��≥꺥쑦궰늘꺜� 횂쨘횂쨍횄�녍궰Ｃ궰걘궰� 횂째횄��걘궰련꺜겷꺿궗횄��벭궰늘꺿�싀꺜겷꺜� 횄�녍궰�횄�궗횄탐횄��≥꺜뤓궰걘꺜� 횂째횄��걘궰련꺜겷꺿궗횄��벭궰늘꺿꽓횂쨍횄짤 횂쨍횂쨋횂쨔횄쩍횄�궗횂쨘 횂쨔횂짬횂쩍횄�뮼궰돤꺥녍궰늘꺿꽓. 
			switch (cOwnerType) {
			case DEF_OWNERTYPE_PLAYER:
				if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
				if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] != 0) goto MAGIC_NOEFFECT;
				// v1.4334 횄혖횄타횂쨍횂쨀횄�궗횂쨘 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쩔횂징횂째횄��� 횂쨍횂쨋횂쨔횄짝횄�궗횂쨩 횂쨍횄쨍횄��≥꺜뤓궰걘꺿�� 횂쩌횄쨋횄혖횂짚
				if (memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;

				m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] = (char)m_pMagicConfigList[sType]->m_sValue4;
				switch (m_pMagicConfigList[sType]->m_sValue4) {
				case 1:
					SetProtectionFromArrowFlag(sOwnerH, DEF_OWNERTYPE_PLAYER, true);
					break;
				case 2:
				case 5:
					SetMagicProtectionFlag(sOwnerH, DEF_OWNERTYPE_PLAYER, true);
					break;
				case 3:
				case 4:
					SetDefenseShieldFlag(sOwnerH, DEF_OWNERTYPE_PLAYER, true);
					break;
				}
				break;

			case DEF_OWNERTYPE_NPC:
				if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
				if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] != 0) goto MAGIC_NOEFFECT;
				// 횄혖횂짚횄�궗횄쨩 NPC횂쨉횄짤횄�궗횂쨘 횂쨘횂쨍횄�녍궰� 횂쨍횂쨋횂쨔횄쩍 횄�궗횄쨩횂쩔횄짬 횂쩐횄�녍궰돤꺟�.				
				if (m_pNpcList[sOwnerH]->m_cActionLimit != 0) goto MAGIC_NOEFFECT;
				m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] = (char)m_pMagicConfigList[sType]->m_sValue4;

				switch (m_pMagicConfigList[sType]->m_sValue4) {
				case 1:
					SetProtectionFromArrowFlag(sOwnerH, DEF_OWNERTYPE_NPC, true);
					break;
				case 2:
				case 5:
					SetMagicProtectionFlag(sOwnerH, DEF_OWNERTYPE_NPC, true);
					break;
				case 3:
				case 4:
					SetDefenseShieldFlag(sOwnerH, DEF_OWNERTYPE_NPC, true);
					break;
				}
				break;
			}

			// 횂쨘횂쨍횄�녍궰� 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
			bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_PROTECT, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime * 1000),
				sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

			// 횄�녍궰올궰걘꺜봤궰걘궰� 횂쨩횄쩍횂째횄짜횄�궗횂쩍횄�궗횂쨩 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
			if (cOwnerType == DEF_OWNERTYPE_PLAYER)
				SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_PROTECT, m_pMagicConfigList[sType]->m_sValue4, 0, 0);
			break;


		case DEF_MAGICTYPE_SCAN:
			/*ZeroMemory(cScanMessage, sizeof(cScanMessage));
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					wsprintf(cScanMessage, "Player: %s HP:%d MP:%d.", m_pClientList[sOwnerH]->m_cCharName, m_pClientList[sOwnerH]->m_iHP, m_pClientList[sOwnerH]->m_iMP);

					SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, 0, 0, 0, cScanMessage);
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					wsprintf(cScanMessage, "NPC: %s HP:%d MP:%d", m_pNpcList[sOwnerH]->m_cNpcName, m_pNpcList[sOwnerH]->m_iHP, m_pNpcList[sOwnerH]->m_iMana);

					SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, 0, 0, 0, cScanMessage);
					break;
				}
				SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex,
					m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY, dX, dY, 10, 10);
			}*/
			goto MAGIC_NOEFFECT;
			break;

		case DEF_MAGICTYPE_HOLDOBJECT:
			// 횂쩔횄�궗횂쨘횄짧횄혖횂짠횄��졗궰�횄�궗횄��� 횂쩔횄짼횄혖횄쨌횄�궗횄��쑦꺿궗횂쨩 횂쨘횄�궗횂쩌횄짖횄��≥꺿�샖궰늘꺿꽓. 
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) goto MAGIC_NOEFFECT;
					if (m_pClientList[sOwnerH]->m_iAddPR >= 500) goto MAGIC_NOEFFECT;
					// v1.4334 횄혖횄타횂쨍횂쨀횄�궗횂쨘 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쩔횂징횂째횄��� 횄��졗꺜먄궰련궰꼴꺿궗횂쨩 횂쨍횄쨍횄��≥꺜뤓궰걘꺿�� 횂쩌횄쨋횄혖횂짚
					if (memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;
					// 2002-09-10 #2 횂쩐횄�녍꺿궗횄쩌횄혖횄쨋횂쨈횄짬(No-Attack-Area) 횄��졗꺜먄궰련궰� 횂쨍횂쨋횂쨔횄쩍 횂쩐횄�녍궰돤꺿�≥궰걘꺿�� 횄��≥꺿��
					if (cOwnerType == DEF_OWNERTYPE_PLAYER) {

						if (m_pMapList[m_pClientList[sOwnerH]->m_cMapIndex]->iGetAttribute(sX, sY, 0x00000006) != 0) goto MAGIC_NOEFFECT;
						if (m_pMapList[m_pClientList[sOwnerH]->m_cMapIndex]->iGetAttribute(dX, dY, 0x00000006) != 0) goto MAGIC_NOEFFECT;
					}

					// 2002-09-10 #3 횄�궗횄쩌횂쨍횄짤횄�궗횄쩌횂쩍횄�뮼궰올꺜� 횂쨔횄흸횂쨉횄짤횂쨌횂짙횂쨉횄짜횂쩔횂징횂쩌횂짯횂쨍횂짝 횄혖횂짝횂쩔횄흹횄��≥꺜뤓궰걘꺜� 횂째횂째횄�궗횂쨘 횄��졗꺜�횂쩔횂징횂째횄��씳궰늘꺿�� 횄��졗꺜먄궰련궰� 횂쩐횄�녍궰돤꺟�
					if (strcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "middleland") != 0 &&
						m_bIsCrusadeMode == false &&
						m_pClientList[iClientH]->m_cSide == m_pClientList[sOwnerH]->m_cSide)
						goto MAGIC_NOEFFECT;

					m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = (char)m_pMagicConfigList[sType]->m_sValue4;
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_cMagicLevel >= 6) goto MAGIC_NOEFFECT; // v1.4 횂쨍횂쨋횂쨔횄쩍 횂쨌횂쨔횂쨘횂짠 6횄�궗횄흸횂쨩횄쨀횄�궗횄탐 횂쨍횂짰횄��왗궰≥궰궁꺟� 횄�궗횄흸횂쨩횄쨀횄�궗횄��� 횂쨍횂쨋횂쨔횄쩍 횂쨍횄쨀횂쩍횂쨘횄��┚꺜띊궰올궰≥궰걘꺿�씳궰늘꺿�� 횂쨍횂쨋횂쨘횄짹 횂쨍횂쨋횂쨔횄쩍 횄��┚꺜ッ꺿�≥꺜뤓꺜겷꺜� 횂쩐횄힋횂쨈횄��싀궰늘꺿꽓.
					if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) goto MAGIC_NOEFFECT;
					m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = (char)m_pMagicConfigList[sType]->m_sValue4;
					break;
				}

				// 횂쨘횂쨍횄�녍궰� 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
				bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_HOLDOBJECT, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				// 횄�녍궰올궰걘꺜봤궰걘궰� 횂쨩횄쩍횂째횄짜횄�궗횂쩍횄�궗횂쨩 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_HOLDOBJECT, m_pMagicConfigList[sType]->m_sValue4, 0, 0);
			}
			break;

		case DEF_MAGICTYPE_INVISIBILITY:
			//50Cent - Capture The Flag
			if (m_bIsCTFEvent && (m_pClientList[iClientH]->m_iStatus & 0x80000) != 0)
			{
				ShowClientMsg(iClientH, "You can not use that magic being a flag carrier.");
				goto MAGIC_NOEFFECT;
			}
			switch (m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) goto MAGIC_NOEFFECT;
					if (memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;

					//50Cent - Capture The Flag
					if (m_bIsCTFEvent && (m_pClientList[sOwnerH]->m_iStatus & 0x80000) != 0)
					{
						ShowClientMsg(iClientH, "You can not use that magic on a flag carrier.");
						goto MAGIC_NOEFFECT;
					}

					m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = (char)m_pMagicConfigList[sType]->m_sValue4;
					SetInvisibilityFlag(sOwnerH, cOwnerType, true);
					RemoveFromTarget(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INVISIBILITY);
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) goto MAGIC_NOEFFECT;

					if (m_pNpcList[sOwnerH]->m_cActionLimit == 0) {
						// 횄�궗횄흸횂쨉횂쩔횄��≥꺜뤓꺜겷꺜� 횂쩐횄힋횂쨈횄��� NPC횂쨈횄��� 횄��┚꺜돤궰맡꺜� 횂쨍횂쨋횂쨔횄쩍횄�궗횂쨩 횂째횄��� 횂쩌횄쨋 횂쩐횄쨍횂쨈횄�꽓.
						m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = (char)m_pMagicConfigList[sType]->m_sValue4;
						SetInvisibilityFlag(sOwnerH, cOwnerType, true);
						// 횄�궗횄흸 NPC횂쨍횂짝 횄�뮼꺟맡꺿궗횄쨩횄��≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺜� 횂쨍횄쨀횂쩍횂쨘횄��┚꺜띊궰맡궰� 횄��≥꺥쑦꺜겷궰┚궰시꺠뮼꺿�┚궰꼴궰늘꺿꽓.
						RemoveFromTarget(sOwnerH, DEF_OWNERTYPE_NPC, DEF_MAGICTYPE_INVISIBILITY);
					}
					break;
				}

				// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
				bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_INVISIBILITY, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_INVISIBILITY, m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				break;

			case 2:
				// v1.4334 횄혖횄타횂쨍횂쨀횄�궗횂쨘 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쩔횂징횂째횄��� 횄혖횄타횂쨉횂쨋횄�궗횂쨩 횂쨍횄쨍횄��≥꺜뤓궰걘꺿�� 횂쩌횄쨋횄혖횂짚
				if (memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;

				// dX, dY 횂쨔횄혶횂째횄짝 8 횄혖횄��벭궰봤궰�횄�궗횄��� Invisibility 횂쨩횄쨀횄��┚꺿�싀꺿궗횄탐 Object횂째횂징 횄�궗횄��벭꺿궗횂쨍횂쨍횄짤 횄��≥꺥쑦꺜겷궰� 횂쩍횄�뮼꺿�┚궰꼴궰늘꺿꽓.
				for (ix = dX - 8; ix <= dX + 8; ix++)
					for (iy = dY - 8; iy <= dY + 8; iy++) {
						m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (sOwnerH != 0) {
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
									SetInvisibilityFlag(sOwnerH, cOwnerType, false);
									bRemoveFromDelayEventList(sOwnerH, cOwnerType, DEF_MAGICTYPE_INVISIBILITY);
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
									SetInvisibilityFlag(sOwnerH, cOwnerType, false);
									bRemoveFromDelayEventList(sOwnerH, cOwnerType, DEF_MAGICTYPE_INVISIBILITY);
								}
								break;
							}
						}
					}
				break;
			}
			break;

		case DEF_MAGICTYPE_CREATE_DYNAMIC:
			// Dynamic Object횂쨍횂짝 횂쨩횄쩍횂쩌횂쨘횄��≥꺜뤓궰걘꺜� 횄�녍궰올궰련꺿�싀꺿궗횄흸 횄혖횄쨋횂쩌횄��쑦궰돤꺿�≥궰늘꺿�� 횄��┚궰맡꺿궗횄���.

			// v2.1 횂쨍횂쨋횄�궗횂쨩 횂쨀횂쨩횂쩔횂징횂쩌횂짯횂쨈횄��� 횄��≥꺟졗궰돤꺜� 횂쨍횂쨋횂쨔횄쩍 횂짹횄혶횄혖횄쨋(횄�궗횄쩌횂쨍횄짤횄�궗횄쩌횂쩍횄�� 횄혖횂짝횂쩔횄흹)
			if (m_bIsCrusadeMode == false) {
				if (strcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "aresden") == 0) return;
				if (strcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "elvine") == 0) return;
				// v2.14
				if (strcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "arefarm") == 0) return;
				if (strcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "elvfarm") == 0) return;
			}

			switch (m_pMagicConfigList[sType]->m_sValue10) {
			case DEF_DYNAMICOBJECT_PCLOUD_BEGIN: // 횂쨉횂쨋횂짹횂쨍횂쨍횂짠

			case DEF_DYNAMICOBJECT_FIRE:   // Fire 횄�궗횄흸횂쨈횄�꽓.
			case DEF_DYNAMICOBJECT_SPIKE:  // Spike

				switch (m_pMagicConfigList[sType]->m_sValue11) {
				case 1:
					// wall - type
					cDir = m_Misc.cGetNextMoveDir(m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY, dX, dY);
					switch (cDir) {
					case 1:	rx = 1; ry = 0;   break;
					case 2: rx = 1; ry = 1;   break;
					case 3: rx = 0; ry = 1;   break;
					case 4: rx = -1; ry = 1;  break;
					case 5: rx = 1; ry = 0;   break;
					case 6: rx = -1; ry = -1; break;
					case 7: rx = 0; ry = -1;  break;
					case 8: rx = 1; ry = -1;  break;
					}

					iAddDynamicObjectList(iClientH, DEF_OWNERTYPE_PLAYER_INDIRECT, m_pMagicConfigList[sType]->m_sValue10, m_pClientList[iClientH]->m_cMapIndex,
						dX, dY, m_pMagicConfigList[sType]->m_dwLastTime * 1000);

					bAnalyzeCriminalAction(iClientH, dX, dY);

					for (i = 1; i <= m_pMagicConfigList[sType]->m_sValue12; i++) {
						iAddDynamicObjectList(iClientH, DEF_OWNERTYPE_PLAYER_INDIRECT, m_pMagicConfigList[sType]->m_sValue10, m_pClientList[iClientH]->m_cMapIndex,
							dX + i * rx, dY + i * ry, m_pMagicConfigList[sType]->m_dwLastTime * 1000);
						bAnalyzeCriminalAction(iClientH, dX + i * rx, dY + i * ry);

						iAddDynamicObjectList(iClientH, DEF_OWNERTYPE_PLAYER_INDIRECT, m_pMagicConfigList[sType]->m_sValue10, m_pClientList[iClientH]->m_cMapIndex,
							dX - i * rx, dY - i * ry, m_pMagicConfigList[sType]->m_dwLastTime * 1000);
						bAnalyzeCriminalAction(iClientH, dX - i * rx, dY - i * ry);
					}
					break;

				case 2:
					// Field - Type
					bool bFlag = false;
					int cx, cy;
					for (ix = dX - m_pMagicConfigList[sType]->m_sValue12; ix <= dX + m_pMagicConfigList[sType]->m_sValue12; ix++)
						for (iy = dY - m_pMagicConfigList[sType]->m_sValue12; iy <= dY + m_pMagicConfigList[sType]->m_sValue12; iy++) {
							iAddDynamicObjectList(iClientH, DEF_OWNERTYPE_PLAYER_INDIRECT, m_pMagicConfigList[sType]->m_sValue10, m_pClientList[iClientH]->m_cMapIndex,
								ix, iy, m_pMagicConfigList[sType]->m_dwLastTime * 1000, m_pMagicConfigList[sType]->m_sValue5);

							// 횂쨍횂쨍횂쩐횄혻 횂쨍횂쨋횄�궗횂쨩횂쩔횂징횂쩌횂짯 횄��≥꺟졗궰돤꺜Γ궰맡궰� 횂짹횄짹 횂째횄쨌횂쩔횂징 횂쨔횂짬횂째횄짯횄��≥꺿�� 횄�궗횄큄횂째횂징 횄�궗횄��벭궰씹꺜봤궰늘꺿꽓횂쨍횄짤 횂째횄쨍횂째횄혶횄�궗횄큄횂쨈횄��� 횂째횂징횂쨉횄짜횄�궗횄��� 횂째횄쨍횂째횄혶횄�궗횂쨩 횂쨔횄탑횂째횄��� 횂쨉횄�녍궰늘꺿꽓. 
							if (bAnalyzeCriminalAction(iClientH, ix, iy, true) == true) {
								bFlag = true;
								cx = ix;
								cy = iy;
							}
						}
					// 횄��≥꺟졗궰돤꺜Γ꺿궗횄탐 횂째횄짝횂쩔횄짭 횂째횄짝횂쨘횄짹횂쨍횂짝 1횂쨍횄짯횂쨍횂쨍 횂쩌횄��쇒꺥녍궰�횄��≥꺜뤓궰궁꺜� 횄�궗횂짠횄��≥꺿��.
					if (bFlag == true) bAnalyzeCriminalAction(iClientH, cx, cy);
					break;
				}
				//
				break;

			case DEF_DYNAMICOBJECT_ICESTORM:
				// Ice-Storm Dynamic Object 
				iAddDynamicObjectList(iClientH, DEF_OWNERTYPE_PLAYER_INDIRECT, m_pMagicConfigList[sType]->m_sValue10, m_pClientList[iClientH]->m_cMapIndex,
					dX, dY, m_pMagicConfigList[sType]->m_dwLastTime * 1000,
					m_pClientList[iClientH]->m_cSkillMastery[4]);
				break;

			default:
				break;
			}
			break;

		case DEF_MAGICTYPE_POSSESSION:
			// 횂쩔횄쨍횂째횄��┚궰맡궰�횂쩔횂징 횂쨋횂쨀횂쩐횄짰횄혖횂짰 횄�궗횄��벭궰늘꺿�� 횂쨔횂째횂째횄��≥꺿궗횂쨩 횄혖횄쩍횂쩐횄짰횂쩔횄�궗횂쨈횄��� 횂쨍횂쨋횂쨔횄쩍횄�궗횄흸횂쨈횄�꽓. 
			// v2.12 횄혖횄타횂쨍횂쨀횄�궗횂쨘 횄��졗꺜련꺜겷궰┚궰셌꺿�� 횂쨍횂쨋횂쨔횄쩍 횂쨩횄짠횂쩔횄짬 횂쨘횄��쇒궰걘궰� 
			if (m_pClientList[iClientH]->m_cSide == 0) goto MAGIC_NOEFFECT;

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (sOwnerH != 0) break; // v1.41 횄��졗꺜련꺜겷궰┚궰셌꺿�� 횂쨍횂쨋횂쨔횄쩍횄�궗횂쨘 횂쨩횄짠횂쨋횄쨌횄�궗횄흸 횂쩌횂짯 횄�궗횄��벭궰늘꺿�� 횄�궗횂짠횂쩔횂징횂쨈횄��� 횄�녍궰올궰련꺿�싀꺿궗횄흸 횂쩐횄쨍횂쨈횄�꽓. 

			//pItem = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->pGetItem(dX, dY, &sRemainItemSprite, &sRemainItemSpriteFrame, &cRemainItemColor);
			pItem = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->pGetItem(dX, dY, &sRemainItemID/*, &sRemainItemSprite, &sRemainItemSpriteFrame*/, &cRemainItemColor, &dwRemainItemAttr);
			if (pItem != 0) {
				// 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂째횂징 횂쩐횄��졗꺿궗횄흸횄��┚꺿�봤꺿궗횂쨩 횄�녍궰뮨궰돤꺜┚꺿�≥꺜뤓궰올궰늘궰늘꺿꽓. 
				if (_bAddClientItemList(iClientH, pItem, &iEraseReq) == true) {
					// 횂쩐횄��졗꺿궗횄흸횄��┚꺿�봤꺿궗횂쨩 횄�녍궰뮨궰돤꺜┚꺿�≥꺟맡궰늘꺿꽓.

					// v1.411 횂쨌횄탐횂짹횄��� 횂쨀횂짼횂짹횄짚횂쨈횄�꽓.
					_bItemLog(DEF_ITEMLOG_GET, iClientH, (int)-1, pItem);

					dwp = (DWORD*)(cData + DEF_INDEX4_MSGID);
					*dwp = MSGID_NOTIFY;
					wp = (WORD*)(cData + DEF_INDEX2_MSGTYPE);
					*wp = DEF_NOTIFY_ITEMOBTAINED;

					cp = (char*)(cData + DEF_INDEX2_MSGTYPE + 2);

					// 1횂째횂쨀 횄�녍궰뮨궰돤꺜┚꺿�≥꺟맡궰늘꺿꽓. <- 횂쩔횂짤횂짹횄짖횂쩌횂짯 1횂째횂쨀횂쨋횄쨉 횄��왗궰ッ궰올꺜�횄��졗궰�횂쨍횂짝 횂쨍횂쨩횄��≥꺜뤓궰늘꺿�� 횂째횄혥횄�궗횄흸 횂쩐횄��졗궰늘꺜뤓궰늘꺿꽓
					*cp = 1;
					cp++;

					memcpy(cp, pItem->m_cName, 20);
					cp += 20;

					dwp = (DWORD*)cp;
					*dwp = pItem->m_dwCount;
					cp += 4;

					*cp = pItem->m_cItemType;
					cp++;

					*cp = pItem->m_cEquipPos;
					cp++;

					*cp = (char)0; // 횂쩐횄짼횄�궗횂쨘 횂쩐횄��졗꺿궗횄흸횄��┚꺿�봤꺿궗횄흸횂쨔횄��≥궰련꺟� 횄�궗횄짜횄��싀꺜맡궰돤꺿�≥꺜겷꺜� 횂쩐횄힋횂쩐횄��쇒궰늘꺿꽓.
					cp++;

					sp = (short*)cp;
					*sp = pItem->m_sLevelLimit;
					cp += 2;

					*cp = pItem->m_cGenderLimit;
					cp++;

					wp = (WORD*)cp;
					*wp = pItem->m_wCurLifeSpan;
					cp += 2;

					wp = (WORD*)cp;
					*wp = pItem->m_wWeight;
					cp += 2;

					sp = (short*)cp;
					*sp = pItem->m_sSprite;
					cp += 2;

					sp = (short*)cp;
					*sp = pItem->m_sSpriteFrame;
					cp += 2;

					*cp = pItem->m_cItemColor;
					cp++;

					*cp = (char)pItem->m_sItemSpecEffectValue2; // v1.41 
					cp++;

					dwp = (DWORD*)cp;
					*dwp = pItem->m_dwAttribute;
					cp += 4;


					if (iEraseReq == 1) delete pItem;

					// 횂쩐횄��졗꺿궗횄흸횄��┚꺿�봤꺿궗횂쨩 횄혖횄혶횂째횄짯횂쨀횂짯 횄�녍꺿�� 횂쨀횂짼횄�궗횂쨘 횂쩐횄��졗꺿궗횄흸횄��┚꺿�봤꺿궗횂쨩 횂쨈횄�꽓횂쨍횂짜 횄��┚궰�횂쨋횄쨀횄�궗횄흸횂쩐횄째횄��졗궰�횂쩔횂징횂째횄��� 횂쩐횄��뮨궰맡궰걘궰늘꺿꽓. 
					//SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_SETITEM, m_pClientList[iClientH]->m_cMapIndex,
					//	dX, dY, sRemainItemSprite, sRemainItemSpriteFrame, cRemainItemColor); // v1.4

					SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_SETITEM, m_pClientList[iClientH]->m_cMapIndex,
						dX, dY, sRemainItemID, 0, cRemainItemColor, dwRemainItemAttr);

					// 횂쩐횄��졗꺿궗횄흸횄��┚꺿�� 횄혖횂짚횂쨘횂쨍 횄�궗횄쩌횂쩌횄��� 
					iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 53);

					switch (iRet) {
					case DEF_XSOCKEVENT_QUENEFULL:
					case DEF_XSOCKEVENT_SOCKETERROR:
					case DEF_XSOCKEVENT_CRITICALERROR:
					case DEF_XSOCKEVENT_SOCKETCLOSED:
						// 횂쨍횄탑횂쩍횄�뮼꺜겷꺜뗐궰맡궰� 횂쨘횂쨍횂쨀횂쩐횂쨋횂짠 횂쩔횂징횂쨌횂짱횂째횂징 횂쨔횄타횂쨩횄쩍횄��≥꺟맡궰늘꺿꽓횂쨍횄짤 횄혖횂짝횂째횄��┚꺿�≥꺿�샖궰늘꺿꽓.
						DeleteClient(iClientH, true, true);
						break;
					}
				}
				else
				{
					// 횂째횄쨍횂째횂짙횄�궗횄흸 횂쨘횄탐횄혖횂쨌횄��≥꺜뤓궰걘꺿�┚궰냉궰� 횄��≥꺿�샖궰걘꺜㉲꺜겷꺟맡궰련궰�횄�궗횂쨩 횄�뮼꺟졗궰걘꺜봤꺿�≥꺟맡궰늘꺿꽓. 횂쩐횄��졗꺿궗횄흸횄��┚꺿�봤꺿궗횂쨩 횂쩐횄짼횄�궗횂쨩 횂쩌횄쨋 횂쩐횄쨍횂쨈횄�꽓.

					// 횂째횂징횄혖횂짰횂쩔횄��씳궰늘꺜� 횂쩐횄��졗꺿궗횄흸횄��┚꺿�봤꺿궗횂쨩 횂쩔횄쨍횂쨩횄쨀횄�녍궰맡궰봤궰뮨궰시꺠뮼꺿�┚궰꼴궰늘꺿꽓. 
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bSetItem(dX, dY, pItem);

					dwp = (DWORD*)(cData + DEF_INDEX4_MSGID);
					*dwp = MSGID_NOTIFY;
					wp = (WORD*)(cData + DEF_INDEX2_MSGTYPE);
					*wp = DEF_NOTIFY_CANNOTCARRYMOREITEM;

					iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 6);
					switch (iRet) {
					case DEF_XSOCKEVENT_QUENEFULL:
					case DEF_XSOCKEVENT_SOCKETERROR:
					case DEF_XSOCKEVENT_CRITICALERROR:
					case DEF_XSOCKEVENT_SOCKETCLOSED:
						// 횂쨍횄탑횂쩍횄�뮼꺜겷꺜뗐궰맡궰� 횂쨘횂쨍횂쨀횂쩐횂쨋횂짠 횂쩔횂징횂쨌횂짱횂째횂징 횂쨔횄타횂쨩횄쩍횄��≥꺟맡궰늘꺿꽓횂쨍횄짤 횄혖횂짝횂째횄��┚꺿�≥꺿�샖궰늘꺿꽓.
						DeleteClient(iClientH, true, true);
						break;
					}
				}
			}
			//
			break;

		case DEF_MAGICTYPE_CONFUSE:
			// if the caster side is the same as the targets side, no effect occurs
			switch (m_pMagicConfigList[sType]->m_sValue4) {
			case 1: // confuse Language횄짭횂혶횂쨈횄짬창�궗쨔횂짚. 
			case 2: // Confusion, Mass Confusion 	
				for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
					for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
						// 횄짭횇쩐횂혨횄짭창�궗쨔횂혻횄짬횂혧창�궗탑 횄짯창�궗혶횂쩌횄짯횂혧횂짯횄짬횂혨횂혻 횄짭횏��졗떺� 횄짭횇쩐횏��졗꺜�횇��쑦궰셌꺜ッ™궗쨔횏��� 횄짭횂짙횂쩌횄짭횂혶횏흹.
						m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (cOwnerType == DEF_OWNERTYPE_PLAYER) {
							// 횄짯창�궗짖횂쨈횄짬창�궗쨔횂쨔 횄짭횇��쑦™궗탑횄짭횂쨔횏흹횄짭창�궗��씳궰� 횄짭횂쨘횂혨횄짬횂짝횂짯횄짯창�궗탑횂째횄짧횂째창��슿� 횄짭횇쩐횏��졗꺜ッ™궗쨔횂짚.
							// snoopy debugged: must continue and not exit !
							if (m_pClientList[sOwnerH] == 0) continue;
							// donnot confuse self
							if (sOwnerH == iClientH) continue;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								// 횄짭횈��쇒궰겷꺜ッ끸�쇒™�슿�횄짬횂째횂짤횄짭횂혶횂쨈 횄짬횂짠횏��졗꺜ッ궰꼴™궗짖 횄짭횂혻창��슿�횄짯창�궗짖횂짯횄짭창�궗��씳궰� 횄짭창�궗쨔횂짚횄짯횇��쇒궰㉲꺜�창�궗��쑦뗢�졗꺜ッ™궗쨔횂짚.
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] != 0) break; //횄짭횂혶횂쨈횄짬횂짱횂쨍 횄짬창�궗쨔횂짚횄짬횂짜횂쨍 Confuse횄짯횇징횂짢횄짧횂쨀횂쩌횄짧횂째창��슿� 횄짭횇쩐횏��졗꺜ッ™궗쨔횂짚횄짬횂짤횂쨈 횄짬횂짭횂쨈횄짭창�궗쨔횇��쑦꺜ッ궰먄끸�쑦꺜ッ™궗쨔횂짚.
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] = (char)m_pMagicConfigList[sType]->m_sValue4;

								// 횄짯횇징횂짢횄짧횂쨀횂쩌횄짧횂째창��슿� 횄짯창�궗짖횂쨈횄짭횂혻횇��쑦꺜ッ궰먄궰� 횄짬창�궗짖횇��� 횄짬횂째횇��쑦꺜�횈��쇒궰씳꺜�창�궗짖횂혻 횄짬창�궗혶횇��쑦꺜ッ궰졗뗢�졗꺜�횂혶횂쨈 횄짭횂혶횂쨈횄짬횂짼횂짚횄짯횇혻횂쨍횄짬횂짜횂쩌 횄짬창�궗흹횂짹횄짬횂징횂혶횄짯창�궗짖횇��쑦꺜ッ™궗쨔횂짚.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_CONFUSE, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

								// 횄짬횂짠횏��졗꺜ッ궰꼴™궗짖횄짭창�궗��씳궰� 횄짧횂짹횂쨍횄짬횂혻횂쨍횄짭횂혶횇��쇒꺜�횂혶창�궗탑 횄짭창�궗짖횇��쇒꺜ッ궰┚궰걘꺜ッ™궗쨔횂짚.
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_CONFUSE, m_pMagicConfigList[sType]->m_sValue4, 0, 0);
							}
						}
					}
				break;

			case 3: // Ilusion, Mass-Ilusion
				for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
					for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
						// 횄짭횇쩐횂혨횄짭창�궗쨔횂혻횄짬횂혧창�궗탑 횄짯창�궗혶횂쩌횄짯횂혧횂짯횄짬횂혨횂혻 횄짭횏��졗떺� 횄짭횇쩐횏��졗꺜�횇��쑦궰셌꺜ッ™궗쨔횏��� 횄짭횂짙횂쩌횄짭횂혶횏흹.
						m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (cOwnerType == DEF_OWNERTYPE_PLAYER) {
							// 횄짯창�궗짖횂쨈횄짬창�궗쨔횂쨔 횄짭횇��쑦™궗탑횄짭횂쨔횏흹횄짭창�궗��씳궰� 횄짭횂쨘횂혨횄짬횂짝횂짯횄짯창�궗탑횂째횄짧횂째창��슿� 횄짭횇쩐횏��졗꺜ッ™궗쨔횂짚.
							// snoopy debugged: must continue and not exit !
							if (m_pClientList[sOwnerH] == 0) continue;
							// donnot confuse self
							if (sOwnerH == iClientH) continue;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								// 횄짭횈��쇒궰겷꺜ッ끸�쇒™�슿�횄짬횂째횂짤횄짭횂혶횂쨈 횄짬횂짠횏��졗꺜ッ궰꼴™궗짖 횄짭횂혻창��슿�횄짯창�궗짖횂짯횄짭창�궗��씳궰� 횄짭창�궗쨔횂짚횄짯횇��쇒궰㉲꺜�창�궗��쑦뗢�졗꺜ッ™궗쨔횂짚.
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] != 0) break; //횄짭횂혶횂쨈횄짬횂짱횂쨍 횄짬창�궗쨔횂짚횄짬횂짜횂쨍 Confuse횄짯횇징횂짢횄짧횂쨀횂쩌횄짧횂째창��슿� 횄짭횇쩐횏��졗꺜ッ™궗쨔횂짚횄짬횂짤횂쨈 횄짬횂짭횂쨈횄짭창�궗쨔횇��쑦꺜ッ궰먄끸�쑦꺜ッ™궗쨔횂짚.
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] = (char)m_pMagicConfigList[sType]->m_sValue4;

								switch (m_pMagicConfigList[sType]->m_sValue4) {
								case 3:
									// Centuu : Same side no illusion by KahBur
									//if ((strcmp(m_pClientList[sOwnerH]->m_cLocation, m_pClientList[iClientH]->m_cLocation)) == 0) goto MAGIC_NOEFFECT;
									SetIllusionFlag(sOwnerH, DEF_OWNERTYPE_PLAYER, true);
									break;
								}

								// 횄짯횇징횂짢횄짧횂쨀횂쩌횄짧횂째창��슿� 횄짯창�궗짖횂쨈횄짭횂혻횇��쑦꺜ッ궰먄궰� 횄짬창�궗짖횇��� 횄짬횂째횇��쑦꺜�횈��쇒궰씳꺜�창�궗짖횂혻 횄짬창�궗혶횇��쑦꺜ッ궰졗뗢�졗꺜�횂혶횂쨈 횄짭횂혶횂쨈횄짬횂짼횂짚횄짯횇혻횂쨍횄짬횂짜횂쩌 횄짬창�궗흹횂짹횄짬횂징횂혶횄짯창�궗짖횇��쑦꺜ッ™궗쨔횂짚.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_CONFUSE, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

								// 횄짬횂짠횏��졗꺜ッ궰꼴™궗짖횄짭창�궗��씳궰� 횄짧횂짹횂쨍횄짬횂혻횂쨍횄짭횂혶횇��쇒꺜�횂혶창�궗탑 횄짭창�궗짖횇��쇒꺜ッ궰┚궰걘꺜ッ™궗쨔횂짚.
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_CONFUSE, m_pMagicConfigList[sType]->m_sValue4, iClientH, 0);
							}
						}
					}
				break;

			case 4: // Ilusion Movement
				if (m_pClientList[iClientH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) break;
				for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
					for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
						m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (cOwnerType == DEF_OWNERTYPE_PLAYER) {
							// snoopy debugged: must continue and not exit !
							if (m_pClientList[sOwnerH] == 0) continue;
							// donnot confuse self
							if (sOwnerH == iClientH) continue;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] != 0) break;
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE] = (char)m_pMagicConfigList[sType]->m_sValue4;
								switch (m_pMagicConfigList[sType]->m_sValue4) {
								case 4:
									// Centuu : Same side no illusion movement by KahBur
									//if ((strcmp(m_pClientList[sOwnerH]->m_cLocation, m_pClientList[iClientH]->m_cLocation)) == 0) goto MAGIC_NOEFFECT;
									SetIllusionMovementFlag(sOwnerH, DEF_OWNERTYPE_PLAYER, true);
									break;
								}

								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_CONFUSE, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_CONFUSE, m_pMagicConfigList[sType]->m_sValue4, iClientH, 0);
							}
						}
					}
			}
			break;


		case DEF_MAGICTYPE_POISON:
			// 횄혖횄타횂쨉횂쨋 횂쨍횂쨋횂쨔횄쩍. 횂쨍횄��▣꺿궗횄쨘 횂쨍횂쨋횂쨔횄쩍 횄�궗횄쨘횄��≥꺿�붌꺿궗횂쨩 횂짹횂쩌횂쨍횂짰횂째횄짯 횂쨈횄�꽓횄�궗횂쩍횄�궗횂쨍횂쨌횄탐 횂쨉횂쨋횂쩌횂쨘횄�궗횄쨘횄��≥꺿�붌꺿궗횂쨩 횄��≥꺿�샖궰뮨꺜� 횂쨈횄쨉 횂짹횂쩌횂쨍횂째횂쨈횄�꽓. 
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

			if (m_pMagicConfigList[sType]->m_sValue4 == 1) {
				// 횄혖횄타횂쨉횂쨋횄�궗횂쨩 횂째횄��┚궰늘꺿�� 횂쨍횂쨋횂쨔횄쩍 
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					// v1.4334 횄혖횄타횂쨍횂쨀횄�궗횂쨘 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쩔횂징횂째횄��� 횄혖횄타횂쨉횂쨋횄�궗횂쨩 횂쨍횄쨍횄��≥꺜뤓궰걘꺿�� 횂쩌횄쨋횄혖횂짚
					if (memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) goto MAGIC_NOEFFECT;

					// 횂쨔횄쩌횄혖횄��뮨꺿�≥꺜졗꺿궗횂짠횂쨋횄쨀횂쨍횄짤 
					bAnalyzeCriminalAction(iClientH, dX, dY);

					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						// 횂쨍횂쨋횂쨔횄쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓. 횂쨉횂쨋횂쩌횂쨘횄�궗횄쨘횄��≥꺿�붌꺿궗횂쨩 횂째횄짢횂쨩횄짧횄��≥꺿�샖궰늘꺿꽓.
						if (bCheckResistingPoisonSuccess(sOwnerH, cOwnerType) == false) {
							// 횄혖횄타횂쨉횂쨋횂쨉횄��≥궰씹꺜봤궰늘꺿꽓.
							m_pClientList[sOwnerH]->m_bIsPoisoned = true;
							m_pClientList[sOwnerH]->m_iPoisonLevel = m_pMagicConfigList[sType]->m_sValue5;
							m_pClientList[sOwnerH]->m_dwPoisonTime = dwTime;
							// 05/06/2004 - Hypnotoad - poison aura appears when cast Poison
							SetPoisonFlag(sOwnerH, cOwnerType, true);
							// 횄혖횄타횂쨉횂쨋횂쨉횄��≥궰씹꺜봤꺿궗횂쩍횄�궗횂쨩 횂쩐횄��뮨궰맡궰걘궰늘꺿꽓. 
							SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_POISON, m_pMagicConfigList[sType]->m_sValue5, 0, 0);
#ifdef DEF_TAIWANLOG
							_bItemLog(DEF_ITEMLOG_POISONED, sOwnerH, (char*)0, 0);
#endif
						}
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_iHP <= 0) goto MAGIC_NOEFFECT;
					if (bCheckResistingPoisonSuccess(sOwnerH, cOwnerType) == false)
					{	// SNOOPY: Add support for ncp been poisonned
						if (m_pNpcList[sOwnerH]->m_iPoisonLevel < 100)
							m_pNpcList[sOwnerH]->m_iPoisonLevel = 100;
						SetPoisonFlag(sOwnerH, DEF_OWNERTYPE_NPC, true);
					}
					break;
				}
			}
			else if (m_pMagicConfigList[sType]->m_sValue4 == 0) {
				// 횄혖횄타횂쨉횂쨋횄�궗횂쨩 횄��≥궰っ궰늘꺿�� 횂쨍횂쨋횂쨔횄쩍 
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;

					if (m_pClientList[sOwnerH]->m_bIsPoisoned == true) {
						// 횄혖횄타횂쨉횂쨋횂쨉횄�� 횂쨩횄쨀횄��┚꺿�싀궰올궰늘궰늘꺿꽓횂쨍횄짤 횄혖횄타횂쨉횂쨋횄�궗횂쨩 횄��≥궰�횂쨈횄�꽓.
						m_pClientList[sOwnerH]->m_bIsPoisoned = false;
						// 05/06/2004 - Hypnotoad - poison aura removed when cure cast
						SetPoisonFlag(sOwnerH, cOwnerType, false);
						// 횄혖횄타횂쨉횂쨋횄�궗횄흸 횄��≥궰�횂쨌횄�녍꺿궗횂쩍횄�궗횂쨩 횂쩐횄��뮨궰맡궰걘궰늘꺿꽓. 
						SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_POISON, 0, 0, 0);
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_iPoisonLevel > 0)
					{
						m_pNpcList[sOwnerH]->m_iPoisonLevel = 0;
						SetPoisonFlag(sOwnerH, DEF_OWNERTYPE_NPC, false);
					}
					break;
				}
			}
			break;

		case DEF_MAGICTYPE_BERSERK:
			switch (m_pMagicConfigList[sType]->m_sValue4) {
			case 1:
				// 횂쨔횄쨋횂쩌횂짯횄��왗궰� 횂쨍횄째횂쨉횄짜횂쨌횄탐 횄�궗횄쩌횄�녍궰�횂쨉횄�녍궰늘꺿꽓.
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_BERSERK] != 0) goto MAGIC_NOEFFECT;
					m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_BERSERK] = (char)m_pMagicConfigList[sType]->m_sValue4;
					SetBerserkFlag(sOwnerH, cOwnerType, true);
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_BERSERK] != 0) goto MAGIC_NOEFFECT;
					// 횄혖횂짚횄�궗횄쨩 NPC횂쨉횄짤횄�궗횂쨘 횂짹횂짚횂쨘횄혨 횂쩐횄�녍궰돤꺟�				
					if (m_pNpcList[sOwnerH]->m_cActionLimit != 0) goto MAGIC_NOEFFECT;
					// 2002-09-11 #3 횄�궗횄쨩 횂쨍횄쨀횂쩍횂쨘횄��┚꺜띊궰늘꺿�� 횂짹횂짚횂쨘횄혨횂쨉횄��≥꺜겷꺜� 횂쩐횄힋횄�궗횂쩍
					if (m_pClientList[iClientH]->m_cSide != m_pNpcList[sOwnerH]->m_cSide) goto MAGIC_NOEFFECT;

					if (strcmp(m_pNpcList[sOwnerH]->m_cNpcName, "Guard-Aresden")) goto MAGIC_NOEFFECT; // centu: no effect on guards
					if (strcmp(m_pNpcList[sOwnerH]->m_cNpcName, "Guard-Elvine")) goto MAGIC_NOEFFECT; // centu: no effect on guards

					m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_BERSERK] = (char)m_pMagicConfigList[sType]->m_sValue4;
					SetBerserkFlag(sOwnerH, cOwnerType, true);
					break;
				}

				// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
				bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_BERSERK, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);

				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_BERSERK, m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				break;
			}
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA_ARMOR_BREAK: //28 m_sValue10 is used for armor decrement					
			switch (cOwnerType) {
			// For Player. 
			case DEF_OWNERTYPE_PLAYER:
				for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
					for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
						m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
							ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10);
						}

						m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
						if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
							(m_pClientList[sOwnerH]->m_iHP > 0)) {
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
								ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10);
							}
						}
					}
				break;
			case DEF_OWNERTYPE_NPC:
				goto MAGIC_NOEFFECT;
				break;
			}
			break;

			// Resurrection Magic. 
		case DEF_MAGICTYPE_RESURRECTION:
			// 10 Mins once
			if (m_pClientList[iClientH]->m_iSpecialAbilityTime != 0) goto MAGIC_NOEFFECT;
			m_pClientList[iClientH]->m_iSpecialAbilityTime = DEF_SPECABLTYTIMESEC / 2;
			// Get the ID of the dead Player/NPC on coords dX, dY. 
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			switch (cOwnerType) {
				// For Player. 
			case DEF_OWNERTYPE_PLAYER:
				// Centuu : Can't use with enemys
				if ((strcmp(m_pClientList[sOwnerH]->m_cLocation, m_pClientList[iClientH]->m_cLocation)) != 0) goto MAGIC_NOEFFECT;
				// The Player has to exist. 
				if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
				// Resurrection is not for alive Players. 
				if (m_pClientList[sOwnerH]->m_bIsKilled == false) goto MAGIC_NOEFFECT;
				// Set Deadflag to Alive. 
				m_pClientList[sOwnerH]->m_bIsKilled = false;
				// Player's HP becomes half of the Max HP. 
				m_pClientList[sOwnerH]->m_iHP = iGetMaxHP(sOwnerH, false) / 2;
				// Send new HP to Player. 
				SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_HP, 0, 0, 0, 0);
				// Make Player stand up. (Currently, by a fake damage). 
				m_pMapList[m_pClientList[sOwnerH]->m_cMapIndex]->ClearDeadOwner(dX, dY);
				m_pMapList[m_pClientList[sOwnerH]->m_cMapIndex]->SetOwner(sOwnerH, DEF_OWNERTYPE_PLAYER, dX, dY);
				SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, 0, 0);
				
				break;
				// Resurrection is not for NPC's. 
			case DEF_OWNERTYPE_NPC:
				goto MAGIC_NOEFFECT;
				break;
			}
			break;

		case DEF_MAGICTYPE_ICE:
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						// 횂쨈횄짬횂쨔횄흸횄혖횄쨋횂쩔횄혥 횄��≥꺿�씳궰꼴궰�
						//Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// 횄��┚궰맡궰걘꺿꽓횄�궗횄흸 횂쨩횄짭횂쩐횄��졗꺿궗횄��벭궰걘꺜� 횂쩐횄쨀횄�궗횂쩍 횄�궗횄쨘횄��≥꺿�붌궰올궰� 횂쩍횄��≥꺿�졗꺜먄꺿�≥꺟맡궰늘꺿꽓횂쨍횄짤 횂쩐횄쨀횂쩐횄짰횂쨘횄�꽓횂쨈횄��싀궰늘꺿꽓.
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									// 횂쨈횄짬횂쨩횄쨀횄�궗횄흸 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횄�궗횄탐 횂째횄짝횂쩔횄짭 횂쩐횄��뮨궰련꺜겷꺜겷꺥쑦궰늘꺿꽓.
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}

					}

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						// 횄혖횄��붌꺿궗횂쨘 횄�뮼궰늘꺿�≥꺜뤓궰걘꺜� 횄�궗횄��벭궰늘꺿�� 횄��≥꺠뮼궰련궰뮨꺿궗횄흸횂쩐횄짰횂쨈횄�꽓.
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

							//Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							// 횂쩐횄쨀횂쩐횄짰횂쩌횂짯 횂쨉횂쩔횄�궗횄��봤꺿궗횄흸 횂쨈횄힋횂쩐횄짰횄혖횄쨋횂쨈횄��� 횄�녍궰올궰걘꺜�. 횄혖횄��붌꺜겷꺜� 횂쩐횄힋횂쩐횄��쇒꺿궗횂쨍횂쨍횄짤 횄�궗횄쨩횂쩔횄짬 
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									// 횄�녍궰올궰걘꺜봤궰걘궰� 횄��≥꺥쑦꺜겷궰┚궰돤꺿�� 횂쨋횂짠 횂쨔횄타횂쨩횄쩍횄��≥꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸 횄�궗횄흸횂쨘횂짜횄��졗궰�횂쨍횂짝 횂쨉횄짰횂쨌횄혧횄��≥꺿�샖궰늘꺿꽓.
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);

									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
						}
					}
				}
			break;

		default:
			break;
		}
	}
	else {
		// Casting 횄�녍꺿�� 횂쨉횄쨈횂쨌횂쨔횄�궗횄흸횂째횂징 횂째횄��걘궰맡궰�횂쨈횄��� 횂쨍횂쨋횂쨔횄쩍
		// Resurrection wand(MS.10) or Resurrection wand(MS.20)

		if (m_pMagicConfigList[sType]->m_sType == DEF_MAGICTYPE_RESURRECTION) {
			//Check if player has resurrection wand
			if (m_pClientList[iClientH] != 0 && m_pClientList[iClientH]->m_iSpecialAbilityTime == 0 &&
				m_pClientList[iClientH]->m_bIsSpecialAbilityEnabled == false) {
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
				if (m_pClientList[sOwnerH] != 0) {

					if ((m_pClientList[iClientH]->m_iAdminUserLevel < 1) &&
						(m_pClientList[sOwnerH]->m_cSide != m_pClientList[iClientH]->m_cSide)) {
						return;
					}
					if (cOwnerType == DEF_OWNERTYPE_PLAYER && m_pClientList[sOwnerH] != 0 &&
						m_pClientList[sOwnerH]->m_iHP <= 0) {
						m_pClientList[sOwnerH]->m_bIsBeingResurrected = true;
						SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_RESURRECTPLAYER, 0, 0, 0, 0);
						if (m_pClientList[iClientH]->m_iAdminUserLevel < 2) {
							m_pClientList[iClientH]->m_bIsSpecialAbilityEnabled = true;
							m_pClientList[iClientH]->m_dwSpecialAbilityStartTime = dwTime;
							m_pClientList[iClientH]->m_iSpecialAbilityLastSec = 0;
							m_pClientList[iClientH]->m_iSpecialAbilityTime = m_pMagicConfigList[sType]->m_dwDelayTime;

							sTemp = m_pClientList[iClientH]->m_sAppr4;
							sTemp = 0xFF0F & sTemp;
							sTemp = sTemp | 0x40;
							m_pClientList[iClientH]->m_sAppr4 = sTemp;
						}
						SendNotifyMsg(0, iClientH, DEF_NOTIFY_SPECIALABILITYSTATUS, 1, m_pClientList[iClientH]->m_iSpecialAbilityType, m_pClientList[iClientH]->m_iSpecialAbilityLastSec, 0);
						SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, 0, 0, 0);
					}
				}
			}
		}
	}

MAGIC_NOEFFECT:;

	if (m_pClientList[iClientH] == 0) return;

	//Mana Slate
	if ((m_pClientList[iClientH]->m_iStatus & 0x800000) != 0) {
		iManaCost = 0;
	}

	if (!bIgnoreOwnerLimits) {
		//Magn0S:: Remove mana cost for GM's
		if (m_pClientList[iClientH]->m_iAdminUserLevel > 0)
			iManaCost = 0;
		else iManaCost = iManaCost;

		m_pClientList[iClientH]->m_iMP -= iManaCost; // Mana Cost
		if (m_pClientList[iClientH]->m_iMP < 0)
			m_pClientList[iClientH]->m_iMP = 0;

		CalculateSSN_SkillIndex(iClientH, 4, 1);

		SendNotifyMsg(0, iClientH, DEF_NOTIFY_MP, 0, 0, 0, 0);
	}
	SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex,
		m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);

}


void CGame::NpcMagicHandler(int iNpcH, short dX, short dY, short sType)
{
	short  sOwnerH;
	char   cOwnerType;
	int i, iErr, ix, iy, sX, sY, tX, tY;
	int iResult, iIceAtkRatio, iWhetherBonus, iMagicAttr;
	DWORD  dwTime = timeGetTime();

	if (m_pNpcList[iNpcH] == 0) return;
	if ((dX < 0) || (dX >= m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_sSizeX) ||
		(dY < 0) || (dY >= m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_sSizeY)) return;

	if ((sType < 0) || (sType >= 100))     return;
	if (m_pMagicConfigList[sType] == 0) return;

	if (m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_bIsAttackEnabled == false) return;

	iResult = m_pNpcList[iNpcH]->m_iMagicHitRatio;
	iIceAtkRatio = iResult / 8;
	iWhetherBonus = iGetWhetherMagicBonusEffect(sType, m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->m_cWhetherStatus);
	iMagicAttr = m_pMagicConfigList[sType]->m_iAttribute;

	// sX, sY is Caster position
	sX = m_pNpcList[iNpcH]->m_sX;
	sY = m_pNpcList[iNpcH]->m_sY;
	if (m_pMagicConfigList[sType]->m_dwDelayTime == 0)
	{
		switch (m_pMagicConfigList[sType]->m_sType) {
		
		case DEF_MAGICTYPE_HELLFIRE:
			iMagicAttr = 3;
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			ShowSpellEffect2(sOwnerH, 99, cOwnerType);

			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, 23, 24, 0 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, 23, 24, 0 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break; //end hellfire

		case DEF_MAGICTYPE_FURYOFTHOR:
			sX = m_pNpcList[iNpcH]->m_sX;
			sY = m_pNpcList[iNpcH]->m_sY;

			for (i = 2; i < 10; i++) {
				iErr = 0;
				m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
				}

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx-1, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);

						}
						break;
					}
					//
				}

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx+1, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
					//
				}

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx, ty-1
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
					//
				}

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				// tx, ty+1
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
					//
				}

				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
							}
							break;
						}
						//
					}

					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
								if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
									Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
								}
								break;
							}
							//
						}
					}
				}

			// dX, dY
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
				Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
					}
					break;
				}
				//
			}

			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) break;//goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_ManaDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
						break;
					}
					//
				}
			}
			break;

		case DEF_MAGICTYPE_DAMAGE_SPOT: // 1
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult + 50) == false)
				Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0)
				&& (m_pClientList[sOwnerH]->m_iHP > 0))
			{
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
			}
			break;

		case DEF_MAGICTYPE_HPUP_SPOT: // 2
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			Effect_HpUp_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6);
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA: // 3 (will fly from spell center point)
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);

			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0)
				&& (m_pClientList[sOwnerH]->m_iHP > 0))
			{
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
			}
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++)
				{
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0)
						&& (m_pClientList[sOwnerH]->m_iHP > 0))
					{
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_SPDOWN_AREA: // 5
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6);
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
				}
			break;

		case DEF_MAGICTYPE_SPUP_AREA: // 7
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			Effect_SpUp_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6);
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					Effect_SpUp_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
				}
			break;

		case DEF_MAGICTYPE_HOLDOBJECT: // 12
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
			{
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) goto NMH_NOEFFECT;
					// Give a chance anti-Para if very good PR... 
					if (((m_pClientList[sOwnerH]->m_cSkillMastery[23] + m_pClientList[sOwnerH]->m_iAddPR + iDice(1, 100)) >= 250)
						&& (m_pClientList[sOwnerH]->m_iSpecialAbilityType != 3)) goto NMH_NOEFFECT;
					m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = (char)m_pMagicConfigList[sType]->m_sValue4;
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_cMagicLevel >= 6) goto NMH_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) goto NMH_NOEFFECT;
					m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = (char)m_pMagicConfigList[sType]->m_sValue4;
					break;
				}
				bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_HOLDOBJECT, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
				{
					short cParaLevel = m_pMagicConfigList[sType]->m_sValue4;
					if (cParaLevel > 1) cParaLevel = 2;
					SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_HOLDOBJECT, cParaLevel, 0, 0);
				}
			}
			break;

		case DEF_MAGICTYPE_INVISIBILITY: //13
			switch (m_pMagicConfigList[sType]->m_sValue4) {
			case 1:	// Invisibility
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) goto NMH_NOEFFECT;
					m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = (char)m_pMagicConfigList[sType]->m_sValue4;
					SetInvisibilityFlag(sOwnerH, cOwnerType, true);
					RemoveFromTarget(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INVISIBILITY);
					break;
				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto NMH_NOEFFECT;
					if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0) goto NMH_NOEFFECT;
					m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = (char)m_pMagicConfigList[sType]->m_sValue4;
					SetInvisibilityFlag(sOwnerH, cOwnerType, true);
					RemoveFromTarget(sOwnerH, DEF_OWNERTYPE_NPC, DEF_MAGICTYPE_INVISIBILITY);
					break;
				}
				bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_INVISIBILITY, dwTime + (m_pMagicConfigList[sType]->m_dwLastTime * 1000),
					sOwnerH, cOwnerType, 0, 0, 0, m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				if (cOwnerType == DEF_OWNERTYPE_PLAYER)
					SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_INVISIBILITY, m_pMagicConfigList[sType]->m_sValue4, 0, 0);
				break;
			case 2:	// Detect Invisibility
				for (ix = dX - 8; ix <= dX + 8; ix++)
					for (iy = dY - 8; iy <= dY + 8; iy++) {
						m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if (sOwnerH != 0) {
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pClientList[sOwnerH] == 0) continue;
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0)
								{
									if (m_pClientList[sOwnerH]->m_sType != 66)
									{
										m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
										SetInvisibilityFlag(sOwnerH, cOwnerType, false);
										bRemoveFromDelayEventList(sOwnerH, cOwnerType, DEF_MAGICTYPE_INVISIBILITY);
									}
								}
								break;
							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[sOwnerH] == 0) continue;
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != 0)
								{
									if (m_pClientList[sOwnerH]->m_sType != 66)
									{
										m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
										SetInvisibilityFlag(sOwnerH, cOwnerType, false);
										bRemoveFromDelayEventList(sOwnerH, cOwnerType, DEF_MAGICTYPE_INVISIBILITY);
									}
								}
								break;
							}
						}
					}
				break;
			}
			break;

		case DEF_MAGICTYPE_DAMAGE_LINEAR: // 19 BloodyShockWave, LightningBolt
			for (i = 2; i < 10; i++)
			{
				iErr = 0;
				m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);
				// tx, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}
				// tx-1, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}
				// tx+1, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}
				// tx, ty-1
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}
				// tx, ty+1
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
				}
				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}
			// Damage Area
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++)
				{
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
					{
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			// Target damage dX, dY
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
			{
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
			}
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT:  //21 (fly from caster)
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0)
						&& (m_pClientList[sOwnerH]->m_iHP > 0))
					{
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_ICE:  //23 (don't fly target) Added by Snoopy
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++)
				{
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) 
					{
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) continue; // Snoopy: replaced goto MAGIC_NOEFFECT by continue...
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) continue; // Snoopy: replaced goto MAGIC_NOEFFECT by continue...
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
					// Will not ice is not discovered pretencorpse		
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0)
						&& (m_pClientList[sOwnerH]->m_iHP > 0))
					{
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
					}
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT_SPDOWN: //25 // EWS (will fly in random position)
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++)
				{	// SNOOPY: Damage is on 456, Special SPdown on 789
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						if ((iy == dY) && (ix == dX))
						{	// Will fly random direction // 10 more damage if targetted.
							Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, ix, iy, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, 10 + m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
							Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, 10 + m_pMagicConfigList[sType]->m_sValue9);
						}
						else
						{	// Will fly random direction
							Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, ix, iy, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
							Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9);
						}
					}
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0)
						&& (m_pClientList[sOwnerH]->m_iHP > 0))
					{
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						{
							Effect_Damage_Spot_DamageMove(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, ix, iy, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, 10 + m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
							Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, 10 + m_pMagicConfigList[sType]->m_sValue9);
						}
					}
				}
			break;

		case DEF_MAGICTYPE_ICE_LINEAR: //26 Added by Snoopy
			// SNOOPY: used iMagicAttr, to send info to damage procedures, not to add bonus for Berzerk Liche Wands
			iMagicAttr += 100;
			for (i = 2; i < 10; i++)
			{
				iErr = 0;
				m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);
				// tx, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) break;
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) break;
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
					}
				}

				// tx-1, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) break;
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) break;
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
					}
				}

				// tx+1, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) break;
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) break;
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
					}
				}

				// tx, ty-1
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) break;
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) break;
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
					}
				}

				// tx, ty+1
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) break;
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) break;
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
						{
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
							{
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
					}
				}
				// Exit if reaching the Target
				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			// Area damage: depends on X/Y settings in the spell and m_sValue789, same as linear damge
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++)
				{
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) break;
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
								{
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;
						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) break;
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
								{
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
					}
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
					{
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						{
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, false, iMagicAttr);
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
							{
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
								{
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
						}
					}
				}

			// Target Damage: depends on m_sValue456
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
			{
				Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) break;
					if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
					{
						if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
						{
							m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							SetIceFlag(sOwnerH, cOwnerType, true);
							bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
								sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
						}
					}
					break;
				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) break;
					if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
					{
						if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
						{
							m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							SetIceFlag(sOwnerH, cOwnerType, true);
							bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
								sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
						}
					}
					break;
				}
			}
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
			{
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
					if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(-1, sOwnerH, cOwnerType, iIceAtkRatio) == false))
					{
						if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0)
						{
							m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							SetIceFlag(sOwnerH, cOwnerType, true);
							bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
								sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
						}
					}
				}
			}
			break;

		case DEF_MAGICTYPE_DAMAGE_LINEAR_SPDOWN: //30 ESW
			//  m_sValue4 5 6 used for damage target
			//  m_sValue7 8 9 used for damage Linear, Area 
			//  m_sValue10 11 12 used for SP down
			// SNOOPY: used iMagicAttr, to send info to damage procedures, not to add bonus for Berzerk Liche Wands
			iMagicAttr += 100;
			for (i = 2; i < 10; i++)
			{
				iErr = 0;
				m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);
				// tx, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) continue;
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) continue;
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						break;
					}
				}
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (m_pClientList[sOwnerH] == 0) continue;
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
					}
				}

				// tx-1, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) continue;
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) continue;
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						break;
					}
				}
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (m_pClientList[sOwnerH] == 0) continue;
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
					}
				}

				// tx+1, ty
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) continue;
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) continue;
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						break;
					}
				}
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (m_pClientList[sOwnerH] == 0) continue;
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
					}
				}

				// tx, ty-1
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) continue;
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) continue;
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						break;
					}
				}
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (m_pClientList[sOwnerH] == 0) continue;
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
					}
				}

				// tx, ty+1
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) continue;
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) continue;
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						break;
					}
				}
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
				{
					if (m_pClientList[sOwnerH] == 0) continue;
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
					}
				}
				// Do not strike again if target is close to caster
				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}
			// Area Damage
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
			{
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++)
				{
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
					{
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) continue;
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
							break;
						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) continue;
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
							break;
						}
					}
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
					{
						if (m_pClientList[sOwnerH] == 0) break;
						if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
						{
							Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8, m_pMagicConfigList[sType]->m_sValue9 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
						}
					}
				}
			}
			// Damage on Target m_sValue456
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
			{
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
					Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
					break;
				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) break;
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
					break;
				}
			}
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) && (m_pClientList[sOwnerH]->m_iHP > 0))
			{
				if (m_pClientList[sOwnerH] == 0) break;
				if (bCheckResistingMagicSuccess(-1, sOwnerH, cOwnerType, iResult) == false)
				{
					Effect_Damage_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
					Effect_SpDown_Spot(iNpcH, DEF_OWNERTYPE_NPC, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10, m_pMagicConfigList[sType]->m_sValue11, m_pMagicConfigList[sType]->m_sValue12);
				}
			}
			break;

		}
	}
NMH_NOEFFECT:;
	// Mana
	m_pNpcList[iNpcH]->m_iMana -= m_pMagicConfigList[sType]->m_sValue1; // sValue1이 Mana Cost
	if (m_pNpcList[iNpcH]->m_iMana < 0)
		m_pNpcList[iNpcH]->m_iMana = 0;
	SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pNpcList[iNpcH]->m_cMapIndex,
		m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, dX, dY, (sType + 100), m_pNpcList[iNpcH]->m_sType);
}

/*********************************************************************************************************************
**  int bool CGame::bCheckResistingMagicSuccess(char cAttackerDir, short sTargetH, char cTargetType, int iHitRatio) **
**  description			:: calculates if a player resists magic														**
**  last updated		:: November 20, 2004; 8:42 PM; Hypnotoad													**
**	return value		:: bool																						**
**  commentary			::	-	hero armor for target mages adds 50 magic resistance								**
**							-	10000 or more it ratio will deduct 10000 hit ratio									**
**							-	invincible tablet is 100% magic resistance											**
**********************************************************************************************************************/
bool CGame::bCheckResistingMagicSuccess(char cAttackerDir, short sTargetH, char cTargetType, int iHitRatio)
{
	double dTmp1, dTmp2, dTmp3;
	int    iTargetMagicResistRatio, iDestHitRatio;
	char   cTargetDir, cProtect;

	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sTargetH] == 0) return false;
		if (m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->m_bIsAttackEnabled == false) return false;
		if (m_pClientList[sTargetH]->m_iAdminUserLevel > 0) return true;
		if ((m_pClientList[sTargetH]->m_iStatus & 0x400000) != 0) return true;
		cTargetDir = m_pClientList[sTargetH]->m_cDir;
		iTargetMagicResistRatio = m_pClientList[sTargetH]->m_cSkillMastery[3] + m_pClientList[sTargetH]->m_iAddMR;
		if ((m_pClientList[sTargetH]->m_iMag) > 50)
			iTargetMagicResistRatio += ((m_pClientList[sTargetH]->m_iMag) - 50);
		iTargetMagicResistRatio += m_pClientList[sTargetH]->m_iAddResistMagic;
		cProtect = m_pClientList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT];
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sTargetH] == 0) return false;
		cTargetDir = m_pNpcList[sTargetH]->m_cDir;
		iTargetMagicResistRatio = m_pNpcList[sTargetH]->m_cResistMagic;
		cProtect = m_pNpcList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT];
		break;
	}

	if (cProtect == 5) return true;
	if ((iHitRatio < 1000) && (cProtect == 2)) return true;
	if (iTargetMagicResistRatio < 1) iTargetMagicResistRatio = 1;
	/*if (m_pClientList[sTargetH]->m_cHeroArmourBonus == 2) { // Centuu - crash point
		iHitRatio += 50;
	}*/

	dTmp1 = (double)(iHitRatio);
	dTmp2 = (double)(iTargetMagicResistRatio);
	dTmp3 = (dTmp1 / dTmp2) * 50.0f;
	iDestHitRatio = (int)(dTmp3);
	if (iDestHitRatio >= 100) return false;

	if (iDice(1, 100) <= iDestHitRatio) return false;

	if (cTargetType == DEF_OWNERTYPE_PLAYER)
		CalculateSSN_SkillIndex(sTargetH, 3, 1);

	return true;
}

bool CGame::bCheckResistingTremorSuccess(short sTargetH, char cTargetType)
{
	int  iStability;
	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sTargetH] == 0) return false;
		if (m_pClientList[sTargetH]->m_iAdminUserLevel > 0) return true;
		// Max load is lvl150*500 + str250*500 = 200 000 (=>2000)
		iStability = 1300 - (m_pClientList[sTargetH]->m_iCurWeightLoad / 100);
		iStability += m_pClientList[sTargetH]->m_iAddAbsEarth;
		if (iDice(1, 100) < iStability) return true;
		else return false;
		break;

	case DEF_OWNERTYPE_NPC:
		return false;
		break;
	}
	return false;
}
bool CGame::bCheckResistingIceSuccess(char cAttackerDir, short sTargetH, char cTargetType, int iHitRatio)
{
	int iTargetIceResistRatio;

	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sTargetH] == 0) return false;
		if (m_pClientList[sTargetH]->m_iAdminUserLevel > 0) return true;
		iTargetIceResistRatio = m_pClientList[sTargetH]->m_iAddAbsWater * 2;
		if (m_pClientList[sTargetH]->m_dwWarmEffectTime != 0) {
			if ((timeGetTime() - m_pClientList[sTargetH]->m_dwWarmEffectTime) < 30000) return true;
		}
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sTargetH] == 0) return false;
		if (m_pNpcList[sTargetH]->m_sType == 91) return true; // new
		iTargetIceResistRatio = (m_pNpcList[sTargetH]->m_cResistMagic) - (m_pNpcList[sTargetH]->m_cResistMagic / 3); // 여기에 얼음 방어 수치 입력. NPC의 경우 마법 저항의 70% 수준 
		break;
	}
	if (iDice(1, 100) <= iTargetIceResistRatio) return true;
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////
//  int CGame::iClientMotion_Magic_Handler(int iClientH, short sX, short sY, char cDir)
//  description			:: checks if player is casting magic
//  last updated		:: October 29, 2004; 6:51 PM; Hypnotoad
//	return value		:: int
/////////////////////////////////////////////////////////////////////////////////////
int CGame::iClientMotion_Magic_Handler(int iClientH, short sX, short sY, char cDir)
{
	char  cData[100];
	DWORD* dwp;
	WORD* wp;
	int     iRet;

	if (m_pClientList[iClientH] == 0) return 0;
	if (m_pClientList[iClientH]->m_bIsKilled == true) return 0;
	if (m_pClientList[iClientH]->m_bIsInitComplete == false) return 0;

	if ((sX != m_pClientList[iClientH]->m_sX) || (sY != m_pClientList[iClientH]->m_sY)) return 2;

	int iStX, iStY;
	if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex] != 0)
	{
		iStX = m_pClientList[iClientH]->m_sX / 20;
		iStY = m_pClientList[iClientH]->m_sY / 20;
		m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stTempSectorInfo[iStX][iStY].iPlayerActivity++;
		switch (m_pClientList[iClientH]->m_cSide) {
		case 1: m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stTempSectorInfo[iStX][iStY].iAresdenActivity++; break;
		case 2: m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stTempSectorInfo[iStX][iStY].iElvineActivity++;  break;
		case 0:
		default: m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stTempSectorInfo[iStX][iStY].iNeutralActivity++; break;
		}
	}

	ClearSkillUsingStatus(iClientH);

	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->ClearOwner(0, iClientH, DEF_OWNERTYPE_PLAYER, sX, sY);
	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetOwner(iClientH, DEF_OWNERTYPE_PLAYER, sX, sY);

	if ((m_pClientList[iClientH]->m_iStatus & 0x10) != 0) {
		SetInvisibilityFlag(iClientH, DEF_OWNERTYPE_PLAYER, false);
		bRemoveFromDelayEventList(iClientH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INVISIBILITY);
		m_pClientList[iClientH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
	}

	m_pClientList[iClientH]->m_cDir = cDir;

	dwp = (DWORD*)(cData + DEF_INDEX4_MSGID);
	*dwp = MSGID_RESPONSE_MOTION;
	wp = (WORD*)(cData + DEF_INDEX2_MSGTYPE);
	*wp = DEF_OBJECTMOTION_CONFIRM;

	iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 6);
	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		DeleteClient(iClientH, true, true);
		return 0;
	}

	return 1;
}

bool CGame::_bDecodeMagicConfigFileContents(char* pData, DWORD dwMsgSize)
{
	char* pContents, * token, cTxt[120];
	char seps[] = "= \t\n";
	char cReadModeA = 0;
	char cReadModeB = 0;
	int  iMagicConfigListIndex = 0;
	class CStrTok* pStrTok;

	pContents = new char[dwMsgSize + 1];
	ZeroMemory(pContents, dwMsgSize + 1);
	memcpy(pContents, pData, dwMsgSize);

	pStrTok = new class CStrTok(pContents, seps);
	token = pStrTok->pGet();
	while (token != 0) {
		if (cReadModeA != 0) {
			switch (cReadModeA) {
			case 1:
				switch (cReadModeB) {
				case 1:
					// 쨍쨋쨔첵 쨔첩횊짙 
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}

					if (m_pMagicConfigList[atoi(token)] != 0) {
						// ��횑쨔횑 횉횘쨈챌쨉횊 쨔첩횊짙째징 ��횜쨈횢. 쩔징쨌짱��횑쨈횢.
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Duplicate magic number.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[atoi(token)] = new class CMagic;
					iMagicConfigListIndex = atoi(token);

					cReadModeB = 2;
					break;

				case 2:
					// 쨍쨋쨔첵 ��횑쨍짠 
					ZeroMemory(m_pMagicConfigList[iMagicConfigListIndex]->m_cName, sizeof(m_pMagicConfigList[iMagicConfigListIndex]->m_cName));
					memcpy(m_pMagicConfigList[iMagicConfigListIndex]->m_cName, token, strlen(token));
					cReadModeB = 3;
					break;

				case 3:
					// 쨍쨋쨔첵 횁쩐쨌첫 m_sType
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sType = atoi(token);
					cReadModeB = 4;
					break;

				case 4:
					// 쨍쨋쨔첵 쨉척쨌쨔��횑 쩍횄째짙 m_dwDelayTime
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_dwDelayTime = atoi(token);
					cReadModeB = 5;
					break;

				case 5:
					// 쨍쨋쨔첵 횁철쩌횙쩍횄째짙 m_dwLastTime
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_dwLastTime = atoi(token);
					cReadModeB = 6;
					break;

				case 6:
					// m_sValue1
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue1 = atoi(token);
					cReadModeB = 7;
					break;

				case 7:
					// m_sValue2
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue2 = atoi(token);
					cReadModeB = 8;
					break;

				case 8:
					// m_sValue3
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue3 = atoi(token);
					cReadModeB = 9;
					break;

				case 9:
					// m_sValue4
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue4 = atoi(token);
					cReadModeB = 10;
					break;

				case 10:
					// m_sValue5
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue5 = atoi(token);
					cReadModeB = 11;
					break;

				case 11:
					// m_sValue6
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue6 = atoi(token);
					cReadModeB = 12;
					break;

				case 12:
					// m_sValue7
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue7 = atoi(token);
					cReadModeB = 13;
					break;

				case 13:
					// m_sValue8
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue8 = atoi(token);
					cReadModeB = 14;
					break;

				case 14:
					// m_sValue9
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue9 = atoi(token);
					cReadModeB = 15;
					break;

				case 15:
					// m_sValue10
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue10 = atoi(token);
					cReadModeB = 16;
					break;

				case 16:
					// m_sValue11
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue11 = atoi(token);
					cReadModeB = 17;
					break;

				case 17:
					// m_sValue12
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sValue12 = atoi(token);
					cReadModeB = 18;
					break;

				case 18:
					// m_sIntLimit
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_sIntLimit = atoi(token);
					cReadModeB = 19;
					break;

				case 19:
					// m_iGoldCost
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_iGoldCost = atoi(token);

					cReadModeB = 20;
					break;

				case 20:
					// m_cCategory
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_cCategory = atoi(token);
					cReadModeB = 21;
					break;

				case 21:
					// m_iAttribute
					if (_bGetIsStringIsNumber(token) == false) {
						PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file error - Wrong Data format.");
						delete[] pContents;
						delete pStrTok;
						return false;
					}
					m_pMagicConfigList[iMagicConfigListIndex]->m_iAttribute = atoi(token);
					cReadModeA = 0;
					cReadModeB = 0;
					break;
				}
				break;

			default:
				break;
			}
		}
		else {
			if (memcmp(token, "magic", 5) == 0) {
				cReadModeA = 1;
				cReadModeB = 1;
			}

		}
		token = pStrTok->pGet();

	}

	delete pStrTok;
	delete[] pContents;
	if ((cReadModeA != 0) || (cReadModeB != 0)) {
		PutLogList("(!!!) CRITICAL ERROR! MAGIC configuration file contents error!");
		return false;
	}

	wsprintf(cTxt, "(!) MAGIC(Total:%d) configuration - success!", iMagicConfigListIndex);
	PutLogList(cTxt);

	return true;

}

bool CGame::RequestStudyMagicHandler(int iClientH, char* pName, bool bSucces, bool bIsPurchase)
{
	char* cp, cMagicName[31], cData[100];
	DWORD* dwp, dwGoldCount = 0;
	WORD* wp;
	int* ip, iReqInt, iCost, iRet, iTempInt;
	bool bMagic = true;
	iTempInt = m_pClientList[iClientH]->m_iInt;
	// SNOOPY: Angelic allow to buy Spell but not to read manual.

	if (m_pClientList[iClientH] == 0) return false;
	if (m_pClientList[iClientH]->m_bIsInitComplete == false) return false;

	ZeroMemory(cData, sizeof(cData));
	ZeroMemory(cMagicName, sizeof(cMagicName));
	memcpy(cMagicName, pName, 30);
	iRet = _iGetMagicNumber(cMagicName, &iReqInt, &iCost);

	if (iRet != -1)
	{
		
		if (bIsPurchase == true)
		{
			if (m_pMagicConfigList[iRet]->m_iGoldCost < 0) bMagic = false;
			dwGoldCount = dwGetItemCount(iClientH, "Gold");
			if ((DWORD)iCost > dwGoldCount) bMagic = false;
			//iTempInt += m_pClientList[iClientH]->m_iAngelicInt;
			// SNOOPY: Was Buggy couldn't leran a Spell Book outside Magic Tower !
			if (m_pClientList[iClientH]->m_bIsInsideWizardTower == false) bMagic = false; //return false;
		}

		if (m_pClientList[iClientH]->m_cMagicMastery[iRet] != 0) bMagic = false; //return false;

		if ((iReqInt <= iTempInt) && (bMagic == true))
		{
			if (bIsPurchase == true) 
				SetItemCount(iClientH, "Gold", (dwGoldCount - iCost));

			iCalcTotalWeight(iClientH);

			m_pClientList[iClientH]->m_cMagicMastery[iRet] = 1;
			// Snoopy: notify sender function off the succes.
			bSucces = true;
			dwp = (DWORD*)(cData + DEF_INDEX4_MSGID);
			*dwp = MSGID_NOTIFY;
			wp = (WORD*)(cData + DEF_INDEX2_MSGTYPE);
			*wp = DEF_NOTIFY_MAGICSTUDYSUCCESS;
			cp = (char*)(cData + DEF_INDEX2_MSGTYPE + 2);
			*cp = iRet;
			cp++;
			memcpy(cp, cMagicName, 30);
			cp += 30;
			iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 37);
			switch (iRet) {
			case DEF_XSOCKEVENT_QUENEFULL:
			case DEF_XSOCKEVENT_SOCKETERROR:
			case DEF_XSOCKEVENT_CRITICALERROR:
			case DEF_XSOCKEVENT_SOCKETCLOSED:
				DeleteClient(iClientH, true, true);
				break;
			}
			return true;
		}
		else
		{
			bSucces = false;
			dwp = (DWORD*)(cData + DEF_INDEX4_MSGID);
			*dwp = MSGID_NOTIFY;
			wp = (WORD*)(cData + DEF_INDEX2_MSGTYPE);
			*wp = DEF_NOTIFY_MAGICSTUDYFAIL;
			cp = (char*)(cData + DEF_INDEX2_MSGTYPE + 2);
			*cp = 1;
			cp++;
			*cp = iRet;
			cp++;
			memcpy(cp, cMagicName, 30);
			cp += 30;
			ip = (int*)cp;
			*ip = iCost;
			cp += 4;
			ip = (int*)cp;
			*ip = iReqInt;
			cp += 4;
			iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 46);
			switch (iRet) {
			case DEF_XSOCKEVENT_QUENEFULL:
			case DEF_XSOCKEVENT_SOCKETERROR:
			case DEF_XSOCKEVENT_CRITICALERROR:
			case DEF_XSOCKEVENT_SOCKETCLOSED:
				DeleteClient(iClientH, true, true);
				break;
			}
		}
	}
	return false;
}


int CGame::_iGetMagicNumber(char* pMagicName, int* pReqInt, int* pCost)
{
	int i;
	char cTmpName[31];

	ZeroMemory(cTmpName, sizeof(cTmpName));
	strcpy(cTmpName, pMagicName);

	for (i = 0; i < DEF_MAXMAGICTYPE; i++)
		if (m_pMagicConfigList[i] != 0) {
			if (memcmp(cTmpName, m_pMagicConfigList[i]->m_cName, 30) == 0) {
				// 째째��쨘 ��횑쨍짠��쨩 째징횁첩 쨍쨋쨔첵 쩌쨀횁짚��쨩 횄짙쩐횘쨈횢. 쨍쨋쨔첵 쨔첩횊짙쨍짝 쨔횦횊짱횉횗쨈횢.
				*pReqInt = (int)m_pMagicConfigList[i]->m_sIntLimit;
				*pCost = (int)m_pMagicConfigList[i]->m_iGoldCost;

				return i;
			}
		}

	return -1;
}

// 2003-04-21 ��횓횈짰쩔징 쨉청쨍짜 쨍쨋쨔첵��쨩 쨩챔횁짝 쩍횄횆횗횁횠쨈횢...
/////////////////////////////////////////////////////////////////////////////////////
//  bool CGame::bCheckMagicInt(int iClientH)  //another retarded korean function
//  desc		 :: ��횓횈짰째징 쨀쨩쨌횁째짭��쨩쨋짠 쨩챔횁짝횉횘 쨍쨋쨔첵��쨩 횄쨀쨍짰횉횗쨈횢... 횄쩌횇짤쨍쨍...
//	return value :: 쨔짬횁쨋째횉 true   // ....dumbass koreans
//  date		 :: 2003-04-21
/////////////////////////////////////////////////////////////////////////////////////
void CGame::bCheckMagicInt(int iClientH)
{

	for (int i = 0;i < DEF_MAXMAGICTYPE;i++)
	{
		if (m_pMagicConfigList[i] != 0) {
			if (m_pMagicConfigList[i]->m_sIntLimit > (m_pClientList[iClientH]->m_iInt))
			{
				m_pClientList[iClientH]->m_cMagicMastery[i] = 0;
			}
		}
	}
}

//Magn0S:: Battle Staffs coded by Magn0S for Helbreath Friend's 02/2012
void CGame::BattleMageMagicHandler(int iClientH, int dX, int dY, short sType, bool bItemEffect, int iV1)
{
	short  sX, sY, sOwnerH, sMagicCircle, sLevelMagic, sAppr2, sEqStatus;
	char   cOwnerType;
	double dV1, dV2, dV3, dV4;
	int    i, iErr, ix, iy, iResult, iWhetherBonus;
	int    tX, tY, iManaCost, iMagicAttr, iDmgBonus, iBonusDmgTwo;
	DWORD dwTime = timeGetTime();
	WORD  wWeaponType;


	if (m_pClientList[iClientH] == 0) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == false) return;

	if ((dX < 0) || (dX >= m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_sSizeX) ||
		(dY < 0) || (dY >= m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_sSizeY)) return;


	if (m_pClientList[iClientH]->m_cMapIndex < 0) return;
	if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex] == 0) return;

	if ((sType < 0) || (sType >= 100))     return;
	if (m_pMagicConfigList[sType] == 0) return;
	if ((bItemEffect == false) && (m_pClientList[iClientH]->m_cMagicMastery[sType] != 1)) return;

	if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsAttackEnabled == false) return;

	//Magn0S:: Change to only uses magic if is weapon type 35. (LLF-MS30WANDS...)
	if (m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1) {
		wWeaponType = ((m_pClientList[iClientH]->m_sAppr2 & 0x0FF0) >> 4);
		if (wWeaponType != 51) return;
	}

	//Magn0S:: One Handed or Shield equiped dont uses magic item attack!
	if ((m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND] != -1) ||
		(m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND] != -1)) return;

	//Magn0S:: Magic Attack itens cant be used with IMC!
	if (m_pClientList[iClientH]->m_bInhibition == true) {
		SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, -1, 0);
		return;
	}

	//Magn0S:: Update 07/03/2012 - Cant "attack" in peace mode.
	sAppr2 = (short)((m_pClientList[iClientH]->m_sAppr2 & 0xF000) >> 12);
	if (sAppr2 == 0) return;


	//Magn0S:: Add to decreased the endurace of wands.
	if (m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1)
		sEqStatus = m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
	else sEqStatus = m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];

	if (sEqStatus != -1) {

		if ((m_pClientList[iClientH]->m_pItemList[sEqStatus] != 0) &&
			(m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wMaxLifeSpan != 0)) {

			if (m_pClientList[iClientH]->m_cSide != 0) {
				if (m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wCurLifeSpan <= 0)
					m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wCurLifeSpan = 0;
				else m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wCurLifeSpan --;
				SendNotifyMsg(0, iClientH, DEF_NOTIFY_CURLIFESPAN, sEqStatus, m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wCurLifeSpan, 0, 0);
			}

			if (m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_wCurLifeSpan == 0) {
				SendNotifyMsg(0, iClientH, DEF_NOTIFY_ITEMLIFESPANEND, m_pClientList[iClientH]->m_pItemList[sEqStatus]->m_cEquipPos, sEqStatus, 0, 0);
				ReleaseItemHandler(iClientH, sEqStatus, true);
			}
		}
	}

	//Magn0S:: Set extra dmg's increaseting the values.
	switch (iV1) {
	case 0: // Normal attack
		iBonusDmgTwo = 15; // 1�
		iDmgBonus = 30; // 2�
		break;
	case 1: // Critical attack
		iBonusDmgTwo = 30; // 1�
		iDmgBonus = 40;
		break;
	default:
		iBonusDmgTwo = 0; // 1�
		iDmgBonus = 0;
		PutLogList("Diffent iV1 received in PlayerMagicItensHander...");
		break;
	}

	/*if (iV1 == 1)
		iDmgBonus = 10;
	else iDmgBonus = 5;*/

	//iBonusDmgTwo = 0; // 1�

	sX = m_pClientList[iClientH]->m_sX;
	sY = m_pClientList[iClientH]->m_sY;


	iWhetherBonus = iGetWhetherMagicBonusEffect(sType, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cWhetherStatus);

	//Battle Staffs cost 50% of normal MP cost
	iManaCost = m_pMagicConfigList[sType]->m_sValue1 / 2;
	//Magn0S:: Cancelado Extra mana cost em safe-mode
	/*if ((m_pClientList[iClientH]->m_bIsSafeAttackMode == true) &&
		(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsFightZone == false)) {
		iManaCost += (iManaCost / 2) - (iManaCost / 10);
	}*/
	if (m_pClientList[iClientH]->m_iManaSaveRatio > 0) {
		dV1 = (double)m_pClientList[iClientH]->m_iManaSaveRatio;
		dV2 = (double)(dV1 / 100.0f);
		dV3 = (double)iManaCost;
		dV1 = dV2 * dV3;
		dV2 = dV3 - dV1;
		iManaCost = (int)dV2;
		if (iManaCost <= 0) iManaCost = 1;
	}

	//Magn0S:: Hungers status chances of failed magic weapons attacks.
	if (((m_pClientList[iClientH]->m_iHungerStatus <= 10) || (m_pClientList[iClientH]->m_iSP <= 0)) && (iDice(1, 1000) <= 100)) {
		SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, 0, -1, 0);
		return;
	}

	// Mana 
	if (m_pClientList[iClientH]->m_iMP < iManaCost) {
		return;
	}

	iResult = m_pClientList[iClientH]->m_cSkillMastery[4];

	if (m_pClientList[iClientH]->m_iMag > 50) iResult += ((m_pClientList[iClientH]->m_iMag) - 50);

	sMagicCircle = (sType / 10) + 1;
	sLevelMagic = (m_pClientList[iClientH]->m_iLevel / 10);
	if (sMagicCircle != sLevelMagic) {
		if (sMagicCircle > sLevelMagic) {
			dV1 = (double)(m_pClientList[iClientH]->m_iLevel - sLevelMagic * 10);
			dV2 = (double)abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle];
			dV3 = (double)abs(sMagicCircle - sLevelMagic) * 10;
			dV4 = (dV1 / dV3) * dV2;

			iResult -= abs(abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle] - (int)dV4);
		}
		else {
			iResult += 5 * abs(sMagicCircle - sLevelMagic);
		}
	}

	// Magn0S::2020 Adicionado iMag/2 como extra hit-ratio
	iResult += m_pClientList[iClientH]->m_iAddAR + ((m_pClientList[iClientH]->m_iMag) / 2);

	if (iResult <= 0) iResult = 1;
	if (sType >= 80) iResult += 10000;


	if (m_pMagicConfigList[sType]->m_cCategory == 1) {

		if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->iGetAttribute(sX, sY, 0x00000005) != 0) return;
	}
	iMagicAttr = m_pMagicConfigList[sType]->m_iAttribute;

	//Magn0S:: If player is INV, turns no inv.
	if ((m_pClientList[iClientH]->m_iStatus & 0x10) != 0) {
		SetInvisibilityFlag(iClientH, DEF_OWNERTYPE_PLAYER, false);
		bRemoveFromDelayEventList(iClientH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INVISIBILITY);
		m_pClientList[iClientH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = 0;
	}

	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

	if (m_pMagicConfigList[sType]->m_dwDelayTime == 0) {
		switch (m_pMagicConfigList[sType]->m_sType) {

		case DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT: // Meteor!
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)

				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);

					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, (m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo), (m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus) + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);

					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, (m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo), (m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus) + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_SPOT:
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}
			break;

		case DEF_MAGICTYPE_SPDOWN_SPOT: // DEF_MAGICTYPE_DAMAGE_SPOT_SPDOWN
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
				Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
			}

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
					Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
				}
			}
			break;


			//Magn0S:: Add para ter dmg igual esw mas sem tirar SP
		case DEF_MAGICTYPE_DAMAGE_LINEAR:
			sX = m_pClientList[iClientH]->m_sX;
			sY = m_pClientList[iClientH]->m_sY;

			for (i = 2; i < 10; i++) {
				iErr = 0;
				m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;
					}
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
						//
					}
				}

				// tx-1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);

						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);

						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
					}
				}

				// tx+1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
						//
					}
				}

				// tx, ty-1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
						//
					}
				}

				// tx, ty+1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
						//
					}
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
						//
					}

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);

								}
								break;
							}
							//
						}
					}
				}

			// dX, dY
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
					}
					break;
				}
			}

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);

						}
						break;
					}
				}
			}
			break;

			// v2.16 2002-5-23  
			//Magn0S:: Changed Ice Damge Linear to equal dmg's beetwen blizz/esw
		case DEF_MAGICTYPE_ICE_LINEAR:
			sX = m_pClientList[iClientH]->m_sX;
			sY = m_pClientList[iClientH]->m_sY;

			for (i = 2; i < 10; i++) {
				iErr = 0;
				m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						}
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						}
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//	Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//	Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
					}
				}

				// tx-1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//	Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//	Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
					}
				}

				// tx+1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//	Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//			Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
					}
				}

				// tx, ty-1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//			Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//	Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
					}
				}

				// tx, ty+1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//			Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);

								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//	Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
					}
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			//    
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}
					}

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									//	Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
								}
								if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
									if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
										m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
										SetIceFlag(sOwnerH, cOwnerType, true);
										bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
											sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
										SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
									}
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
								}
								if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
									if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
										m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
										SetIceFlag(sOwnerH, cOwnerType, true);

										bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
											sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									}
								}
								break;
							}
						}
					}
				}

			// dX, dY
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false 
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						//	Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
					}
					if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
						if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
							m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							SetIceFlag(sOwnerH, cOwnerType, true);
							bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
								sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
						}
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
					}
					if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
						if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
							m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
							SetIceFlag(sOwnerH, cOwnerType, true);
							bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
								sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
						}
					}
					break;
				}
			}

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {

				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false 
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							//		Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(sOwnerH, cOwnerType, true);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
									sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
							}
						}
						break;
					}
				}
			}
			break;

		case DEF_MAGICTYPE_HPUP_SPOT:
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			Effect_HpUp_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5, m_pMagicConfigList[sType]->m_sValue6);
			break;

		case DEF_MAGICTYPE_TREMOR: // v1.4    
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}

			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA:
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
			}

			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					}
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT_SPDOWN:
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
						Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
					}

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, false, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
					}
				}
			break;

			// v2.16 2002-5-23  
		case DEF_MAGICTYPE_DAMAGE_AREA_ARMOR_BREAK:
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10);
					}

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
							ArmorLifeDecrement(iClientH, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue10);
						}
					}
				}
			break;

		case DEF_MAGICTYPE_ICE:
			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						//Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							// v2.19 2002-11-17     
							if (m_pClientList[sOwnerH]->m_bIsPlayerCivil == true) goto MAGIC_NOEFFECT;
							if (m_pClientList[sOwnerH]->m_cSide == DEF_NETURAL) goto MAGIC_NOEFFECT;
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if ((m_pNpcList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									//    
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);
								}
							}
							break;
						}

					}

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

							//Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							if ((m_pClientList[sOwnerH]->m_iHP > 0) && (bCheckResistingIceSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false)) {
								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
									SetIceFlag(sOwnerH, cOwnerType, true);
									bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (m_pMagicConfigList[sType]->m_sValue10 * 1000),
										sOwnerH, cOwnerType, 0, 0, 0, 1, 0, 0);

									SendNotifyMsg(0, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, 0, 0);
								}
							}
						}
					}
				}
			break;

		case DEF_MAGICTYPE_DAMAGE_LINEAR_SPDOWN:

			sX = m_pClientList[iClientH]->m_sX;
			sY = m_pClientList[iClientH]->m_sY;

			for (i = 2; i < 10; i++) {
				iErr = 0;
				m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i);

				// tx, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;
					}
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
						//
					}
				}

				// tx-1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);

						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {

							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);

						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX - 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
					}
				}

				// tx+1, ty
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX + 1, tY);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
						//
					}
				}

				// tx, ty-1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY - 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
						//
					}
				}

				// tx, ty+1
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, sX, sY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;
					}
					//
				}

				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, tX, tY + 1);
				if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
					(m_pClientList[sOwnerH]->m_iHP > 0)) {
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
						//
					}
				}

				if ((abs(tX - dX) <= 1) && (abs(tY - dY) <= 1)) break;
			}

			for (iy = dY - m_pMagicConfigList[sType]->m_sValue3; iy <= dY + m_pMagicConfigList[sType]->m_sValue3; iy++)
				for (ix = dX - m_pMagicConfigList[sType]->m_sValue2; ix <= dX + m_pMagicConfigList[sType]->m_sValue2; ix++) {
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
						switch (cOwnerType) {
						case DEF_OWNERTYPE_PLAYER:
							if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;

						case DEF_OWNERTYPE_NPC:
							if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
							if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
								Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
								Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
							}
							break;
						}
						//
					}

					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
						(m_pClientList[sOwnerH]->m_iHP > 0)) {
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot_DamageMove(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, dX, dY, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus + iWhetherBonus, false, iMagicAttr);
							switch (cOwnerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
								if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
									Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
									Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);

								}
								break;
							}
							//
						}
					}
				}

			// dX, dY
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
				Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
					if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
						Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
						Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
					}
					break;
				}
			}

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, dX, dY);
			if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != 0) &&
				(m_pClientList[sOwnerH]->m_iHP > 0)) {
				if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
					Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr); // v1.41 false
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == 0) goto MAGIC_NOEFFECT;
						if (bCheckResistingMagicSuccess(m_pClientList[iClientH]->m_cDir, sOwnerH, cOwnerType, iResult) == false) {
							Effect_Damage_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue4, m_pMagicConfigList[sType]->m_sValue5 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue6 + iWhetherBonus, true, iMagicAttr);
							Effect_SpDown_Spot(iClientH, DEF_OWNERTYPE_PLAYER, sOwnerH, cOwnerType, m_pMagicConfigList[sType]->m_sValue7, m_pMagicConfigList[sType]->m_sValue8 + iBonusDmgTwo, m_pMagicConfigList[sType]->m_sValue9 + iDmgBonus);

						}
						break;
					}
				}
			}
			break;
		default:
			break;
		}
	}
	else {

	}

MAGIC_NOEFFECT:;
	if (m_pClientList[iClientH] == 0) return;

	// Magn0S:: Put to dont decreased mp of gm's.
	if (m_pClientList[iClientH]->m_iAdminUserLevel > 0)
		iManaCost = 0;
	else iManaCost = iManaCost;

	//Mana Slate
	if ((m_pClientList[iClientH]->m_iStatus & 0x800000) != 0) {
		iManaCost = 0;
	}

	m_pClientList[iClientH]->m_iMP -= iManaCost;
	if (m_pClientList[iClientH]->m_iMP < 0)
		m_pClientList[iClientH]->m_iMP = 0;

	CalculateSSN_SkillIndex(iClientH, 4, 1);

	SendNotifyMsg(0, iClientH, DEF_NOTIFY_MP, 0, 0, 0, 0);
	SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex,
		m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);

}

void CGame::ShowSpellEffect2(int iClientH, short sType, int ownertype)
{
	int iX, iY;
	if (sType == 0) return;
	if (sType <= 0)	sType = 1;
	if (sType > 100) sType = 100;

	switch (ownertype) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[iClientH] == 0) return;
		iX = m_pClientList[iClientH]->m_sX;
		iY = m_pClientList[iClientH]->m_sY;
		SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex,
			m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY, iX, iY, (sType + 100), m_pClientList[iClientH]->m_sType);
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[iClientH] == 0) return;
		iX = m_pNpcList[iClientH]->m_sX;
		iY = m_pNpcList[iClientH]->m_sY;
		SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pNpcList[iClientH]->m_cMapIndex,
			m_pNpcList[iClientH]->m_sX, m_pNpcList[iClientH]->m_sY, iX, iY, (sType + 100), m_pNpcList[iClientH]->m_sType);
		break;

	}
}