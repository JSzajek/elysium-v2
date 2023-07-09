#pragma once

#include "Elysium/Graphics/RenderObject.h"
#include "Elysium/Graphics/Texture.h"

#include <memory>
#include <vector>

namespace Elysium
{
	/// <summary>
	/// Enum class representing a frame buffer texture format.
	/// </summary>
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

	/// <summary>
	/// Struct representing a frame buffer texture specification.
	/// </summary>
	struct FrameBufferTextureSpecification
	{
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		FrameBufferTextureSpecification()
			: TextureFormat(FrameBufferTextureFormat::None), TextureOverride(nullptr),
			  TextureArray(false)
		{
		}

		/// <summary>
		/// Constructor initializing a FrameBufferTextureSpecification.
		/// </summary>
		/// <param name="format">The texture format</param>
		FrameBufferTextureSpecification(FrameBufferTextureFormat format)
			: TextureFormat(format), TextureOverride(nullptr), TextureArray(false)
		{
		}

		/// <summary>
		/// Constructor initializing a FrameBufferTextureSpecification.
		/// </summary>
		/// <param name="format">The texture format</param>
		/// <param name="textureOverride">A texture override</param>
		FrameBufferTextureSpecification(FrameBufferTextureFormat format, std::shared_ptr<Texture2D> textureOverride)
			: TextureFormat(format), TextureOverride(textureOverride), TextureArray(false)
		{
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="copy">The object to copy</param>
		FrameBufferTextureSpecification(const FrameBufferTextureSpecification& copy)
			: TextureFormat(copy.TextureFormat), TextureOverride(copy.TextureOverride), 
			  TextureArray(copy.TextureArray)
		{
		}
	public:
		FrameBufferTextureFormat TextureFormat;
		std::shared_ptr<Texture2D> TextureOverride;
		bool TextureArray;
	};

	/// <summary>
	/// Struct representing a frame buffer attachment specification.
	/// </summary>
	struct FrameBufferAttachementSpecification
	{
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		FrameBufferAttachementSpecification() = default;

		/// <summary>
		/// Constructor initializing a FrameBufferAttachementSpecification.
		/// </summary>
		/// <param name="attachments">The attachment specifications</param>
		FrameBufferAttachementSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments)
			: Attachments(attachments)
		{
		}

		/// <summary>
		/// Constructor initializing a FrameBufferAttachementSpecification.
		/// </summary>
		/// <param name="attachments">The attachment specifications</param>
		FrameBufferAttachementSpecification(const std::vector<FrameBufferTextureSpecification>& attachments)
			: Attachments(attachments)
		{
		}
	public:
		std::vector<FrameBufferTextureSpecification> Attachments;
	};

	/// <summary>
	/// Struct representing a the required parameters
	/// to setup a frame buffer.
	/// </summary>
	struct FrameBufferSpecification
	{
	public:
		uint32_t Width = 0;
		uint32_t Height = 0;

		FrameBufferAttachementSpecification Attachments;

		uint16_t Samples = 1;

		bool SwapChainTarget = false;
	};

	/// <summary>
	/// Class representing a graphics frame buffer.
	/// </summary>
	class FrameBuffer : public BindableRenderObject
	{
	public:
		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~FrameBuffer() = default;

		/// <summary>
		/// Resizes the frame buffer.
		/// </summary>
		/// <param name="width">The new width size</param>
		/// <param name="height">The new height size</param>
		virtual void Resize(unsigned int width, unsigned int height) = 0;

		/// <summary>
		/// Updates frame buffer specification.
		/// </summary>
		/// <param name="specification">The specification to update to</param>
		virtual void UpdateSpecification(const FrameBufferSpecification& specification) = 0;

		/// <summary>
		/// Reads a int pixel from the frame buffer.
		/// </summary>
		/// <param name="attachmentIndex">The attachment texture index</param>
		/// <param name="x">The x offset to read</param>
		/// <param name="y">The y offset to read</param>
		/// <returns>The int pixel value</returns>
		virtual int ReadPixel(uint32_t attachmentIndex, unsigned int x, unsigned int y) = 0;
		
		/// <summary>
		/// Reads a float pixel from the frame buffer.
		/// </summary>
		/// <param name="attachmentIndex">The attachment texture index</param>
		/// <param name="x">The x offset to read</param>
		/// <param name="y">The y offset to read</param>
		/// <returns>The float pixel value</returns>
		virtual float ReadPixelF(uint32_t attachmentIndex, unsigned int x, unsigned int y) = 0;

		/// <summary>
		/// Reads the buffer for the pixel values at the passed region.
		/// </summary>
		/// <param name="attachmentIndex">The attachment texture index</param>
		/// <param name="x">The x offset to start reading</param>
		/// <param name="y">The y offset to start reading</param>
		/// <param name="width">The height of the buffer to read</param>
		/// <param name="height">The height of the buffer to read</param>
		/// <returns>The pixels data read</returns>
		virtual uint8_t* ReadPixelBuffer(uint32_t attachmentIndex, uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		/// <summary>
		/// Clears the attachment at the passed index with the passed int value.
		/// </summary>
		/// <param name="attachmentIndex">The attachment texture index</param>
		/// <param name="value">The int value</param>
		virtual void ClearAttachmentI(uint32_t attachmentIndex, int value) = 0;
		
		/// <summary>
		/// Clears the attachment at the passed index with the passed float value.
		/// </summary>
		/// <param name="attachmentIndex">The attachment texture index</param>
		/// <param name="value">The float value</param>
		virtual void ClearAttachmentF(uint32_t attachmentIndex, const float* value) = 0;

		/// <summary>
		/// Retrieves the pointer to the color attachment texture.
		/// </summary>
		/// <param name="index">The color attachment texture index</param>
		/// <returns>The pointer to the color attachment texture</returns>
		virtual std::shared_ptr<Texture2D> GetColorAttachment(uint32_t index = 0) const = 0;
		
		/// <summary>
		/// Retrieves the color attachment at the passed index.
		/// </summary>
		/// <param name="index">The color attachment texture index</param>
		/// <returns>The color attachment render id</returns>
		virtual uint32_t GetColorAttachementRendererID(uint32_t index = 0) const = 0;

		/// <summary>
		/// Retrieves the pointer to the depth attachment texture.
		/// </summary>
		/// <returns>The pointer to the depth attachment texture</returns>
		virtual std::shared_ptr<Texture2D> GetDepthAttachment() const = 0;

		/// <summary>
		/// Retrieve the depth attachment render id.
		/// </summary>
		/// <returns>The depth attachment render id</returns>
		virtual uint32_t GetDepthAttachmentRendererID() const = 0;
		
		/// <summary>
		/// Sets the depth attachment.
		/// </summary>
		/// <param name="attachment">The depth attachment to set</param>
		virtual void SetDepthAttachment(const std::shared_ptr<Texture2D>& attachment) = 0;
		
		/// <summary>
		/// Retrieves a copy of the frame buffer specification.
		/// </summary>
		/// <returns>The texture specification</returns>
		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		/// <summary>
		/// Retrieves the reference to the frame buffer specification.
		/// </summary>
		/// <returns>The texture specification</returns>
		virtual FrameBufferSpecification& GetSpecification() = 0;

		/// <summary>
		/// Retrieves the depth texture specification.
		/// </summary>
		/// <returns>The texture specification</returns>
		virtual FrameBufferTextureSpecification& GetDepthSpecification() = 0;

		/// <summary>
		/// Draws the frame buffer to the passed frame buffer.
		/// </summary>
		/// <param name="output">The output frame buffer</param>
		/// <param name="index">The attachment index to read from</param>
		/// <param name="linearInterp">Whether to linear interpolate to the output</param>
		virtual void DrawTo(const std::shared_ptr<FrameBuffer>& output, uint32_t index = 0, bool linearInterp = false) = 0;
	public:
		/// <summary>
		/// Creates a frame buffer.
		/// </summary>
		/// <param name="specification">frame buffer specification to use</param>
		/// <returns>The created frame buffer</returns>
		static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpecification& specification);
	};
}