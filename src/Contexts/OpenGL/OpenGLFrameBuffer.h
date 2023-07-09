#pragma once

#include "Elysium/Core/Asserts.h"

#include "Elysium/Graphics/FrameBuffer.h"

namespace Elysium
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& specification);
		OpenGLFrameBuffer(uint32_t id, const std::shared_ptr<Texture2D>& depthAttachment)
			: m_id(id), m_depthAttachment(depthAttachment)
		{
			m_specification.Attachments = { FrameBufferTextureFormat::Depth };
		}
		virtual ~OpenGLFrameBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual uint32_t GetRenderID() const override { return m_id; }
		inline virtual uint32_t& GetRenderIDRef() override { return m_id; };

		void Invalidate();
		void UpdateSpecification(const FrameBufferSpecification& specification) override;

		virtual void Resize(unsigned int width, unsigned int height) override;
		virtual int ReadPixel(uint32_t attachmentIndex, unsigned int x, unsigned int y) override;
		virtual float ReadPixelF(uint32_t attachmentIndex, unsigned int x, unsigned int y) override;

		virtual uint8_t* ReadPixelBuffer(uint32_t attachmentIndex, uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void ClearAttachmentI(uint32_t attachmentIndex, int value) override;
		virtual void ClearAttachmentF(uint32_t attachmentIndex, const float* value) override;

		virtual void DrawTo(const std::shared_ptr<FrameBuffer>& output, uint32_t index, bool linearInterp) override;

		virtual inline std::shared_ptr<Texture2D> GetColorAttachment(uint32_t index) const override { ELYSIUM_CORE_ASSERT(index < m_colorAttachments.size()); return m_colorAttachments[index]; }
		virtual inline uint32_t GetColorAttachementRendererID(uint32_t index) const override { ELYSIUM_CORE_ASSERT(index < m_colorAttachments.size()); return m_colorAttachments[index]->GetRenderID(); }
		virtual std::shared_ptr<Texture2D> GetDepthAttachment() const override { ELYSIUM_CORE_ASSERT(m_depthAttachmentSpecs.TextureFormat != FrameBufferTextureFormat::None); return m_depthAttachment; }
		virtual inline uint32_t GetDepthAttachmentRendererID() const override { ELYSIUM_CORE_ASSERT(m_depthAttachmentSpecs.TextureFormat != FrameBufferTextureFormat::None); return m_depthAttachment->GetRenderID(); }

		virtual inline void SetDepthAttachment(const std::shared_ptr<Texture2D>& attachment) override { m_depthAttachment = attachment; }

		const FrameBufferSpecification& GetSpecification() const override { return m_specification; }
		FrameBufferSpecification& GetSpecification() { return m_specification; }

		FrameBufferTextureSpecification& GetDepthSpecification() { return m_depthAttachmentSpecs; }
	private:
		uint32_t m_id;
		FrameBufferSpecification m_specification;

		std::vector<FrameBufferTextureSpecification> m_colorAttachmentSpecs;
		FrameBufferTextureSpecification m_depthAttachmentSpecs = FrameBufferTextureFormat::None;

		std::vector<std::shared_ptr<Texture2D>> m_colorAttachments;
		std::shared_ptr<Texture2D> m_depthAttachment;
	};
}