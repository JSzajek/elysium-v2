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

	enum class PixelFormat : unsigned char
	{
		R = 0,
		RG,
		RGB,
		RGBA
	};

	enum class PixelBitDepth : unsigned char
	{
		Bit8U,
		Bit8S,
		Bit16U,
		Bit16S,
		Bit16F,
		Bit32U,
		Bit32S,
		Bit32F
	};

	enum PixelAlignment : unsigned char
	{
		NotSpecified = 0,
		Byte = 1,
		RowAligned = 2,
		WordAligned = 4,
		DoubleWordBoundaries = 8
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
		PixelFormat Format = PixelFormat::RGBA;
		PixelBitDepth BitDepth = PixelBitDepth::Bit8U;
		PixelAlignment Alignment = PixelAlignment::Byte;
	public:
		TextureFormat() = default;
		TextureFormat(const std::string& filepath, TextureType type = TextureType::Default, 
					  TextureShape shape = TextureShape::Flat, bool srgb = true, bool flipped = true, 
					  AlphaSource source = AlphaSource::InputTextureAlpha, bool transparency = true, 
					  WrapMode wrap = WrapMode::Repeat, FilterMode filter = FilterMode::Linear)
			: FilePath(filepath), Type(type), Shape(shape), Source(source), Wrap(wrap), Filter(filter), 
			  sRGB(srgb), AlphaTransparency(transparency), Flipped(flipped)
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