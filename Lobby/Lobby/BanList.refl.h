#pragma once

#include <HurricaneDDS/DDSDataObject.h>

<<<<<<< HEAD
=======
#include "LobbyConfig.h"

#ifdef ENABLE_BAN_LIST

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
enum STORM_REFL_ENUM class BanType
{
  kRemoteIp,
  kRemoteHost,
  kPlatformId,
};

struct BanListElement
{
  STORM_DATA_DEFAULT_CONSTRUCTION(BanListElement);

  REnum<BanType> m_Type;
  RString m_Data;
  RInt m_Expiration;
  RString m_Message;
};

struct BanList
{
public:
  DDS_SHARED_OBJECT;

  BanList(DDSObjectInterface & obj_interface);

  void Initialize();

  void STORM_REFL_FUNC Ban(BanType type, std::string data, int duration, std::string message);
  void STORM_REFL_FUNC Unban(int ban_index);
  void STORM_REFL_FUNC UnbanMatch(std::string match_str);

  void STORM_REFL_FUNC GetInfo(DDSResponder & responder);

public:

  bool CheckBanList(const char * remote_ip, const char * remote_host, uint64_t platform_id) const;


private:
  void SaveBanList();
  void CleanupExpiredBans();

public:

  RMergeList<BanListElement> m_List;

private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
};
<<<<<<< HEAD
=======

#endif
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
