#pragma once

#include "Elysium/Graphics/Texture.h"

#include <memory>
#include <vector>

namespace Elysium
{
	enum class FrameBufferTextureFormat
	{
		None = 0,

		RGBA8,
		RGBA16F,
		RED_INT,
		RED_F,
		DEPTH24STENCIL8,

		// Simplified Format
		Depth = DEPTH24STENCIL8
	};

	struct FrameBufferTextureSpecification
	{
	public:
		FrameBufferTextureSpecification() = default;
		FrameBufferTextureSpecification(FrameBufferTextureFormat format)
			: TextureFormat(format), TextureOverride(NULL)
		{
		}
		FrameBufferTextureSpecification(FrameBufferTextureFormat format, std::shared_ptr<Texture2D> textureOverride)
			: TextureFormat(format), TextureOverride(textureOverride)
		{
		}

		FrameBufferTextureSpecification(const FrameBufferTextureSpecification& other)
			: TextureFormat(other.TextureFormat), TextureOverride(other.TextureOverride)
		{
		}
	public:
		FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::None;
		std::shared_ptr<Texture2D> TextureOverride = NULL;
		bool TextureArray = false;
	};

	struct FrameBufferAttachementSpecification
	{
	public:
		FrameBufferAttachementSpecification() = default;
		FrameBufferAttachementSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments)
			: Attachments(attachments)
		{
		}
		FrameBufferAttachementSpecification(const std::vector<FrameBufferTextureSpecification>& attachments)
			: Attachments(attachments)
		{
		}
	public:
		std::vector<FrameBufferTextureSpecification> Attachments;
	};

	struct FrameBufferSpecification
	{
	public:
		uint32_t Width = 0, Height = 0;

		FrameBufferAttachementSpecification Attachments;

		uint16_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetRenderID() const = 0;

		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void UpdateSpecification(const FrameBufferSpecification& specification) = 0;

		virtual int ReadPixel(uint32_t attachmentIndex, unsigned int x, unsigned int y) = 0;
		virtual float ReadPixelF(uint32_t attachmentIndex, unsigned int x, unsigned int y) = 0;

		virtual uint8_t* ReadPixelBuffer(uint32_t attachmentIndex, uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void ClearAttachmentI(uint32_t attachmentIndex, int value) = 0;
		virtual void ClearAttachmentF(uint32_t attachmentIndex, const float* value) = 0;

		virtual std::shared_ptr<Texture2D> GetColorAttachment(uint32_t index = 0) const = 0;
		virtual uint32_t GetColorAttachementRendererID(uint32_t index = 0) const = 0;
		virtual std::shared_ptr<Texture2D> GetDepthAttachment() const = 0;
		virtual uint32_t GetDepthAttachmentRendererID() const = 0;
		
		virtual void SetDepthAttachment(const std::shared_ptr<Texture2D>& attachment) = 0;
		
		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		virtual FrameBufferSpecification& GetSpecification() = 0;

		virtual FrameBufferTextureSpecification& GetDepthSpecification() = 0;

		virtual void DrawTo(const std::shared_ptr<FrameBuffer>& output, uint32_t index = 0, bool linearInterp = false) = 0;
	public:
		static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpecification& specification);
	};
}