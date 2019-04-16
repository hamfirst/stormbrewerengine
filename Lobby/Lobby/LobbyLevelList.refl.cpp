
#include "Lobby/LobbyLevelList.refl.meta.h"

#include "Runtime/Map/MapDef.refl.meta.h"

#include "GameShared/GameLevelListAsset.refl.meta.h"

#include "StormRefl/StormReflJsonStd.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

LobbyLevelList g_LobbyLevelList;

LobbyLevelList::LobbyLevelList()
{
  auto ReadFileAsString = [](const std::string_view & file_name) -> std::string
  {
    auto fp = fopen(file_name.data(), "rb");
    if(fp == nullptr)
    {
      return "" ;
    }

    fseek(fp, 0, SEEK_END);
    auto len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    std::string data;
    data.resize(len + 1);
    fread(data.data(), len, 1, fp);
    data[len] = 0;
    fclose(fp);

    while(isspace(data.back()) || data.back() == 0)
    {
      data.pop_back();
    }

    return data;
  };

  auto asset_dir = ReadFileAsString("asset_dir.txt");
  auto level_list_path = asset_dir + '/' + "LevelList.txt";

  auto level_list_data = ReadFileAsString(level_list_path);

  GameLevelListAsset level_list;
  StormReflParseJson(level_list, level_list_data.c_str());

  for(auto & level : level_list.m_Levels)
  {
    auto level_data_path = asset_dir + '/' + level.m_Path;
    auto level_data = ReadFileAsString(level_data_path);

    std::vector<LobbyMapHeaderElem> header;

    const char * result = nullptr;
    StormReflParseJson(header, level_data.c_str(), result);

    MapDefPropertiesOnly map_info;
    StormReflParseJson(map_info, result);

    m_Levels.emplace_back(*map_info.m_PropertiesInfo.m_MapProperties.GetValue());
    m_LevelNames.emplace_back(level.m_Name);
  }
}

int LobbyLevelList::GetNumLevels() const
{
  return (int)m_Levels.size();
}

const std::string & LobbyLevelList::GetLevelName(int level_index) const
{
  return m_LevelNames[level_index];
}

const MapPropertiesDef & LobbyLevelList::GetLevelInfo(int level_index) const
{
  return m_Levels[level_index];
}
