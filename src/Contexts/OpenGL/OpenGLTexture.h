#pragma once

#include "Elysium/Graphics/Texture.h"

namespace Elysium
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(uint32_t m_id, uint32_t width, uint32_t height)
			: m_id(m_id), m_width(width), m_height(height)
		{
		}
		OpenGLTexture2D(uint32_t m_id, uint32_t width, uint32_t height, uint32_t internalFormat, uint32_t dataFormat, uint32_t type, uint32_t m_samples);
		OpenGLTexture2D(const std::string& filepath);
		OpenGLTexture2D(const TextureFormat& format);
		OpenGLTexture2D(const TextureFormat& format, const void* data);
		~OpenGLTexture2D() override;
	public:
		virtual uint32_t GetRenderID() const override { return m_id; }
		inline virtual uint32_t& GetRenderIDRef() override { return m_id; };

		void Initialize(const TextureFormat& format);
		void Initialize(const TextureFormat& format, const void* data);
		void Initialize(const Texture2DOutline* mData);

		inline virtual uint32_t GetWidth() const override { return m_width; }
		inline virtual uint32_t GetHeight() const override { return m_height; }
		inline virtual uint32_t GetDepth() const override { return 0; }

		inline virtual PixelFormat GetPixelFormat() const override { return m_pixelFormat; }
		inline virtual PixelBitDepth GetBitDepth() const override { return m_pixelBitDepth; }

		inline virtual std::string GetName() const override { return m_debugpath; }

		inline virtual UUID GetID() const override { return m_uuid; }

		virtual void Resize(uint32_t width, uint32_t height, PixelAlignment alignment = PixelAlignment::NotSpecified) override;

		virtual void Import(const TextureFormat& format) override;
		virtual void Import(const Texture2DOutline* mData) override;

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint8_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override { return m_id == ((const OpenGLTexture2D&)other).m_id; }
	private:
		std::string m_debugpath;
		uint32_t m_width, m_height;
		UUID m_uuid;
		uint32_t m_id;

		uint32_t m_type;
		uint32_t m_dataFormat;
		uint32_t m_internalFormat;

		uint32_t m_samples;

		PixelAlignment m_pixelAlignment = PixelAlignment::Byte;

		PixelFormat m_pixelFormat;
		PixelBitDepth m_pixelBitDepth;
	};
}