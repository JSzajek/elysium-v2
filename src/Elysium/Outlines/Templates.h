#pragma once

#include "Elysium/Core/Base.h"

#include "Elysium/Math/Vec2.h"
#include "Elysium/Math/Vec4.h"
#include "Elysium/Math/iVec4.h"

#include "Elysium/Core/UUIDs.h"

#include <string>
#include <filesystem>

namespace Elysium
{
	struct ResourceOutline
	{
		UUID Id;

		virtual ~ResourceOutline() = default;
	};

	struct MaterialOutline : public ResourceOutline
	{
		virtual ~MaterialOutline() override = default;

		UUID ShaderId;

		int RenderingMode;

		// Albedo ----------------
		UUID AlbedoTextureId;
		Math::Vec4 AlbedoTint;

		// Metallic --------------
		UUID MetallicMapId;
		float Smoothness;
		int MetallicSource;

		// Normal Map ------------
		UUID NormalMapId;
		float NormalModifier;

		// Height Map ------------
		UUID HeightMapId;
		float HeightModifier;

		// Overall Modifiers -----
		Math::Vec2 Tiling;
		Math::Vec2 Offset;
	};

	struct Texture2DOutline : public ResourceOutline
	{
		virtual ~Texture2DOutline() override = default;

		std::string Filepath;

		Math::iVec2 Size;

		int TextureType;
		int TextureShape;

		bool sRGB;
		bool Flipped;

		int AlphaSource;
		bool AlphaTransparency;

		int WrapMode;
		int FilterMode;

		unsigned int PixelFormat = 4;
	};

	struct ShaderOutline : public ResourceOutline
	{
		virtual ~ShaderOutline() override = default;

		std::string Filepath;

		std::unordered_map<unsigned int, std::vector<uint32_t>> Cache;

		bool Compiled;
		int64_t LastCompileDate;
		std::list<std::filesystem::path> CachePaths;
	};

	struct FontOutline : public ResourceOutline
	{
		virtual ~FontOutline() override = default;

		uint16_t Size;
		UUID FontDataId;

		uint16_t OutlineSize;
		Math::Vec4 OutlineColor;

		Math::iVec4 Spacing;
	};

	struct FontDataOutline : public ResourceOutline
	{
		virtual ~FontDataOutline() override = default;

		std::string Filepath;

		bool AntiAliasing;
	};

	template<typename T>
	std::shared_ptr<T> ConvertInfoTo(const std::string& filepath);
}