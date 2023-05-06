#pragma once

#include "Elysium/Math/iVec2.h"
#include "Elysium/Outlines/Formats.h"
#include "Elysium/Outlines/Templates.h"

#include "Elysium/Core/UUIDs.h"
#include "Elysium/Utils/YamlUtils.h"

#include <string>

namespace Elysium
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		
		virtual UUID GetID() const = 0;
		virtual uint32_t GetRenderID() const = 0;
		
		virtual std::string GetName() const = 0;

		virtual void Reimport(const TextureFormat& format) = 0;
		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint8_t slot = 0) const = 0;
		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height);
		static std::shared_ptr<Texture2D> Create(uint32_t id, uint32_t width, uint32_t height, unsigned int internalFormat, unsigned int dataFormat, unsigned int type, unsigned int samples);
		static std::shared_ptr<Texture2D> Create(const std::string& path);
		static std::shared_ptr<Texture2D> Create(const TextureFormat& format);
		static std::shared_ptr<Texture2D> Create(const TextureFormat& format, const void* data);

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		void Reimport(const Texture2DOutline* mData, const std::string& outputFilepath) { Reimport(mData); WriteToFile(mData, outputFilepath); }
		virtual void Reimport(const Texture2DOutline* mData) = 0;
		static void WriteToFile(const Texture2DOutline* mData, const std::string& outputFilepath);
	};
}