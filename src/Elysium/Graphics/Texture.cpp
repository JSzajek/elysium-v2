#include "elysium_pch.h"

#include "Elysium/Core/Asserts.h"

#include "Elysium/Graphics/Texture.h"
#include "Elysium/Graphics/GraphicsAPI.h"

#include "Contexts/OpenGL/OpenGLTexture.h"

namespace Elysium
{
	template<class ...Args>
	static constexpr std::shared_ptr<Texture2D> CreateTexture(Args&&... args)
	{
		switch (GraphicsAPI::GetAPI())
		{
		case API::None:
			ELYSIUM_CORE_ASSERT(false, "Renderer API currently not set.");
			return NULL;
		case API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(std::forward<Args>(args)...);
			return NULL;
		}

		ELYSIUM_CORE_ASSERT(false, "Unknown Renderer API");
		return NULL;
	}

	std::shared_ptr<Elysium::Texture2D> Texture2D::Create(uint32_t id, uint32_t width, uint32_t height)
	{
		return CreateTexture(id, width, height);
	}

	std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		return CreateTexture(width, height);
	}

	std::shared_ptr<Texture2D> Texture2D::Create(uint32_t id, uint32_t width, uint32_t height, unsigned int internalFormat, unsigned int dataFormat, unsigned int type, unsigned int samples)
	{
		return CreateTexture(id, width, height, internalFormat, dataFormat, type, samples);
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		return CreateTexture(filepath);
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const TextureFormat& format)
	{
		return CreateTexture(format);
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const TextureFormat& format, const void* data)
	{
		return CreateTexture(format, data);
	}

	void Texture2D::WriteToFile(const Texture2DOutline* mData, const std::string& outputFilepath)
	{
		YamlUtils::CreateTo(outputFilepath, [&](YAML::Emitter& out)
		{
			out << YAML::Key << "Id"				<< YAML::Value << mData->Id;
			out << YAML::Key << "Filepath"			<< YAML::Value << mData->Filepath;
			out << YAML::Key << "TextureType"		<< YAML::Value << mData->TextureType;
			out << YAML::Key << "TextureShape"		<< YAML::Value << mData->TextureShape;
			out << YAML::Key << "sRGB"				<< YAML::Value << mData->sRGB;
			out << YAML::Key << "Flipped"			<< YAML::Value << mData->Flipped;
			out << YAML::Key << "AlphaSource"		<< YAML::Value << mData->AlphaSource;
			out << YAML::Key << "AlphaTransparency" << YAML::Value << mData->AlphaTransparency;
			out << YAML::Key << "WrapMode"			<< YAML::Value << mData->WrapMode;
			out << YAML::Key << "FilterMode"		<< YAML::Value << mData->FilterMode;
		});
	}
}