/**
 * ===============================================================
 * SourceMod (C)2004-2007 AlliedModders LLC.  All rights reserved.
 * ===============================================================
 *
 * This file is not open source and may not be copied without explicit
 * written permission of AlliedModders LLC.  This file may not be redistributed 
 * in whole or significant part.
 * For information, see LICENSE.txt or http://www.sourcemod.net/license.php
 *
 * Version: $Id$
 */

#ifndef _INCLUDE_SOURCEMOD_GLOBALHEADER_H_
#define _INCLUDE_SOURCEMOD_GLOBALHEADER_H_

#include "sm_globals.h"
#include <ISourceMod.h>
#include <sh_stack.h>
#include "CDataPack.h"

using namespace SourceHook;

/**
 * @brief Implements SourceMod's global overall management, API, and logic
 */

class SourceModBase : public ISourceMod
{
public:
	SourceModBase();
public:
	/**
	 * @brief Initializes SourceMod, or returns an error on failure.
	 */
	bool InitializeSourceMod(char *error, size_t err_max, bool late);

	/** 
	 * @brief Starts everything SourceMod needs to run
	 */
	void StartSourceMod(bool late);

	/** 
	 * @brief Shuts down all SourceMod components
	 */
	void CloseSourceMod();

	/**
	 * @brief Map change hook
	 */
	bool LevelInit(char const *pMapName, char const *pMapEntities, char const *pOldLevel, char const *pLandmarkName, bool loadGame, bool background);

	/**
	 * @brief Level shutdown hook
	 */
	void LevelShutdown();

	/** 
	 * @brief Returns whether or not a map load is in progress
	 */
	bool IsMapLoading() const;

	/** 
	 * @brief Stores the global target index.
	 */
	void SetGlobalTarget(unsigned int index);

	/** 
	 * @brief Returns the global target index.
	 */
	unsigned int GetGlobalTarget() const;
	
	/** 
	* @brief Sets whether if SoureMod needs to check player auths.
	*/
	void SetAuthChecking(bool set);
public: //ISourceMod
	const char *GetModPath() const;
	const char *GetSourceModPath() const;
	size_t BuildPath(PathType type, char *buffer, size_t maxlength, char *format, ...);
	void LogMessage(IExtension *pExt, const char *format, ...);
	void LogError(IExtension *pExt, const char *format, ...);
	size_t FormatString(char *buffer, size_t maxlength, IPluginContext *pContext, const cell_t *params, unsigned int param);
	IDataPack *CreateDataPack();
	void FreeDataPack(IDataPack *pack);
	HandleType_t GetDataPackHandleType(bool readonly=false);
private:
	/**
	 * @brief Loading plugins
	 */
	void DoGlobalPluginLoads();
	void GameFrame(bool simulating);
private:
	CStack<CDataPack *> m_freepacks;
	char m_SMBaseDir[PLATFORM_MAX_PATH];
	char m_SMRelDir[PLATFORM_MAX_PATH];
	bool m_IsMapLoading;
	bool m_ExecPluginReload;
	unsigned int m_target;
	bool m_CheckingAuth;
};

extern SourceModBase g_SourceMod;
extern HandleType_t g_WrBitBufType;
extern HandleType_t g_RdBitBufType;

#endif //_INCLUDE_SOURCEMOD_GLOBALHEADER_H_
