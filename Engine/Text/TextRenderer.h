#pragma once

#include "Foundation/Allocator/Allocator2D.h"

#include "Engine/Asset/FontAsset.h"
#include "Engine/Rendering/Texture.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Text/TextBackupFont.h"

struct GlyphInfo
{
  bool m_Valid;
  bool m_Rotated;
  int m_X, m_Y;
  int m_Width, m_Height;
  int m_BufferLeft;
  int m_BufferTop;
  int m_Advance;
};

class TextRenderer
{
public:
  TextRenderer(const AssetReference<FontAsset> & asset_ref, int font_size, std::vector<std::unique_ptr<TextBackupFont>> & backup_fonts);
  ~TextRenderer();

  std::pair<std::size_t, std::size_t> CreateVertexBufferForString(czstr utf8_str, std::size_t len, std::vector<Box> & glyph_positions,
    const Color & text_color, const Color & selection_color, const Color & selection_bkg_color,
    VertexBuffer & text_vertex_buffer, VertexBuffer & selection_vertex_buffer, int sel_start, int sel_end, int cursor_pos);

  void BindGlyphTexture(int texture_stage);
  Box GetTextSize(czstr utf8_str, std::size_t len);

  bool Loaded() { return m_Loaded; }
  
private:

  void FinalizeAssetLoad(FontAsset * asset, bool success);

  void AddString(czstr utf8_str, std::size_t len);
  void AddGlyph(char32_t character_code);

  FT_GlyphSlot LoadGlyph(char32_t character_code);
  FT_GlyphSlot LoadBackupGlyph(char32_t character_code);

private:

  AssetReference<FontAsset> m_Font;
  std::vector<std::unique_ptr<TextBackupFont>> & m_BackupFonts;

  bool m_Loaded;
  FT_Face m_Face;

  int m_FontSize;

  Texture m_Texture;

  std::unordered_map<char32_t, GlyphInfo> m_GlyphMap;
  Allocator2D m_Alloc;

  FontAsset::LoadCallbackLink m_LoadLink;
};
