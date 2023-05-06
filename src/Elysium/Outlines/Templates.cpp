#include "elysium_pch.h"

#include "Templates.h"

#include "Elysium/Utils/YamlUtils.h"

namespace Elysium
{
	template<>
	std::shared_ptr<MaterialOutline> ConvertInfoTo<MaterialOutline>(const std::string& filepath)
	{
		auto info = std::make_shared<MaterialOutline>();
		
		auto filedata = YAML::LoadFile(filepath + ".meta");
		info->Id				= filedata["Id"].as<UUID>();

		filedata = YAML::LoadFile(filepath);
		info->ShaderId			= filedata["Shader"].as<UUID>();
		info->RenderingMode		= filedata["RenderingMode"].as<int>();
		
		info->AlbedoTextureId	= filedata["AlbedoTexture"].as<UUID>();
		info->AlbedoTint		= filedata["AlbedoTint"].as<Math::Vec4>();

		info->MetallicMapId		= filedata["MetallicMap"].as<UUID>();
		info->Smoothness		= filedata["Smoothness"].as<float>();
		info->MetallicSource	= filedata["MetallicSource"].as<int>();

		info->NormalMapId		= filedata["NormalMap"].as<UUID>();
		info->NormalModifier	= filedata["NormalModifier"].as<float>();

		info->HeightMapId		= filedata["HeightMap"].as<UUID>();
		info->HeightModifier	= filedata["HeightModifier"].as<float>();

		info->Tiling			= filedata["Tiling"].as<Math::Vec2>();
		info->Offset			= filedata["Offset"].as<Math::Vec2>();

		return info;
	}

	template<>
	std::shared_ptr<Texture2DOutline> ConvertInfoTo<Texture2DOutline>(const std::string& filepath)
	{
		auto info = std::make_shared<Texture2DOutline>();

		auto filedata = YAML::LoadFile(filepath + ".meta");
		info->Id				= filedata["Id"].as<UUID>();
		info->Filepath			= filedata["Filepath"].as<std::string>();

		info->TextureType		= filedata["TextureType"].as<int>();
		info->TextureShape		= filedata["TextureShape"].as<int>();

		info->sRGB				= filedata["sRGB"].as<bool>();
		info->Flipped			= filedata["Flipped"].as<bool>();

		info->AlphaSource		= filedata["AlphaSource"].as<int>();
		info->AlphaTransparency = filedata["AlphaTransparency"].as<bool>();

		info->WrapMode			= filedata["WrapMode"].as<int>();
		info->FilterMode		= filedata["FilterMode"].as<int>();

		return info;
	}

	template<>
	std::shared_ptr<ShaderOutline> ConvertInfoTo<ShaderOutline>(const std::string& filepath)
	{
		auto info = std::make_shared<ShaderOutline>();
		
		auto filedata = YAML::LoadFile(filepath + ".meta");
		info->Id				= filedata["Id"].as<UUID>();
		info->Filepath			= filedata["Filepath"].as<std::string>();
		info->Compiled			= filedata["Compiled"].as<bool>();
		info->LastCompileDate	= filedata["LastCompileDate"].as<int64_t>();

		if (auto cachePaths = filedata["CachePaths"])
		{
			for (auto path : cachePaths)
				info->CachePaths.push_back(path["Path"].as<std::string>());
		}
		return info;
	}

	template<>
	std::shared_ptr<FontOutline> ConvertInfoTo<FontOutline>(const std::string& filepath)
	{
		auto info = std::make_shared<FontOutline>();

		auto filedata = YAML::LoadFile(filepath + ".meta");
		info->Id			= filedata["Id"].as<UUID>();

		filedata = YAML::LoadFile(filepath);
		info->Size			= filedata["Size"].as<uint16_t>();
		info->FontDataId	= filedata["Resource"].as<UUID>();

		info->OutlineSize	= filedata["OutlineSize"].as<uint16_t>();
		info->OutlineColor	= filedata["OutlineColor"].as<Math::Vec4>();

		info->Spacing		= filedata["Spacing"].as<Math::iVec4>();

		return info;
	}

	template<>
	std::shared_ptr<FontDataOutline> ConvertInfoTo<FontDataOutline>(const std::string& filepath)
	{
		auto info = std::make_shared<FontDataOutline>();

		auto filedata = YAML::LoadFile(filepath + ".meta");
		info->Id			= filedata["Id"].as<UUID>();
		info->Filepath		= filedata["Filepath"].as<std::string>();
		info->AntiAliasing	= filedata["AntiAliasing"].as<bool>();

		return info;
	}
}