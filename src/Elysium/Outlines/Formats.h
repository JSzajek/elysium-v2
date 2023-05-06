#pragma once

#include "Elysium/Math/iVec2.h"
#include "Elysium/Core/UUIDs.h"

#include <string>

namespace Elysium
{
#pragma region Texture Format Region
	enum class TextureType : unsigned char
	{
		Default = 0, NormalMap, Sprite
	};

	enum class TextureShape : unsigned char
	{
		Flat = 0, Cube
	};

	enum class AlphaSource : unsigned char
	{
		None = 0, InputTextureAlpha, FromGrayScale
	};

	enum class WrapMode : unsigned char
	{
		Repeat = 0, ClampEdge, ClampBorder, Mirror, MirrorOnce
	};

	enum class FilterMode : unsigned char
	{
		Linear = 0, Nearest
	};

	struct TextureFormat
	{
	public:
		std::string FilePath;
		UUID Uuid;

		Math::iVec2 Size;
		TextureType Type = TextureType::Default;
		TextureShape Shape = TextureShape::Flat;
		bool sRGB = true;
		bool Flipped = true;
		AlphaSource Source = AlphaSource::InputTextureAlpha;
		bool AlphaTransparency = true;
		WrapMode Wrap = WrapMode::Repeat;
		FilterMode Filter = FilterMode::Linear;
		unsigned int PixelFormat = 4;
	public:
		TextureFormat() = default;
		TextureFormat(const std::string& filepath, TextureType type = TextureType::Default, TextureShape shape = TextureShape::Flat, bool srgb = true, bool flipped = true, AlphaSource source = AlphaSource::InputTextureAlpha, bool transparency = true, WrapMode wrap = WrapMode::Repeat, FilterMode filter = FilterMode::Linear)
			: FilePath(filepath), Type(type), Shape(shape), Source(source), Wrap(wrap), Filter(filter), sRGB(srgb), AlphaTransparency(transparency), Flipped(flipped)
		{
		}
	};
#pragma endregion

	struct MeshFormat
	{
	public:
		std::string FilePath;
		UUID Uuid;

		std::string Name;

		bool CombineVertices = true;
		bool CalculateTangents = true;

	public:
		MeshFormat() = default;
		MeshFormat(const std::string& filepath, bool combineVerts = true, bool calcTangents = true)
			: FilePath(filepath), CombineVertices(combineVerts), CalculateTangents(calcTangents)
		{
		}
	};
}