#include "elysium_pch.h"

#include "Contexts/OpenGL/OpenGLFrameBuffer.h"

#include <gl/glew.h>

namespace Elysium
{
	static const unsigned int s_maxFramebufferSize = 8192; // TODO: Render cap

	namespace FBUtils
	{
		static GLenum TextureTarget(bool multisampled) { return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D; }

		static void CreateTextures(bool multisampled, uint32_t* id, uint32_t count) { glCreateTextures(TextureTarget(multisampled), count, id); }

		static void BindTexture(bool multisampled, uint32_t id) { glBindTexture(TextureTarget(multisampled), id); }
	
		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, unsigned int width, unsigned int height, unsigned int index, GLenum type)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, NULL);

				// TODO: Add parameters to allow for variability
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}

		static void ReAttachColorTexture(uint32_t id, int samples, unsigned int index)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				// Multi sampling texture parameters?
			}
			else
			{
				// TODO: Add parameters to allow for variability
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}

		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, unsigned int width, unsigned int height)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
		}

		static void ReAttachDepthTexture(uint32_t id, int samples, GLenum attachmentType)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				// Multi sampling texture parameters?
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
		}

		static bool IsDepthFormat(FrameBufferTextureFormat format)
		{
			switch (format)
			{
				case FrameBufferTextureFormat::DEPTH24STENCIL8: return true;
			}
			return false;
		}

		static GLenum TextureFormatToGLFormat(FrameBufferTextureFormat format)
		{
			switch (format)
			{
				case FrameBufferTextureFormat::RGBA8:	return GL_RGBA;
				case FrameBufferTextureFormat::RGBA16F: return GL_RGBA;
				case FrameBufferTextureFormat::RED_INT:	return GL_RED_INTEGER;
				case FrameBufferTextureFormat::RED_F:   return GL_RED;
			}
			ELYSIUM_CORE_ASSERT(false);
			return 0;
		}

		static GLenum TextureFormatToGLInternalFormat(FrameBufferTextureFormat format)
		{
			switch (format)
			{
				case FrameBufferTextureFormat::RGBA8:	return GL_RGBA8;
				case FrameBufferTextureFormat::RGBA16F:	return GL_RGBA16F;
				case FrameBufferTextureFormat::RED_INT:	return GL_R32I;
				case FrameBufferTextureFormat::RED_F:	return GL_R8;
			}
			ELYSIUM_CORE_ASSERT(false);
			return 0;
		}
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& specification)
		: m_specification(specification), m_id(0)
	{
		for (auto specification : m_specification.Attachments.Attachments)
		{
			if (!FBUtils::IsDepthFormat(specification.TextureFormat))
			{
				m_colorAttachmentSpecs.emplace_back(specification);
			}
			else
			{
				m_depthAttachmentSpecs = specification; // Only one depth texture attachment currently
			}
		}

		Invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_id);

		if (m_colorAttachments.size() > 0)
			m_colorAttachments.clear();
			//glDeleteTextures(static_cast<uint32_t>(m_colorAttachments.size()), m_colorAttachments.data());
		
		if (m_depthAttachment)
			m_depthAttachment = nullptr;
			//glDeleteTextures(1, &m_depthAttachment);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);

		if (!m_specification.SwapChainTarget)
			glViewport(0, 0, m_specification.Width, m_specification.Height); //TODO: Check this? Currently necessary for resizing
	}

	void OpenGLFrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Invalidate()
	{
		if (m_id)
		{
			glDeleteFramebuffers(1, &m_id);

			m_colorAttachments.clear();
			m_depthAttachment = nullptr;
		}

		glCreateFramebuffers(1, &m_id);
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);

		bool multisampled = m_specification.Samples > 1;

		if (!m_colorAttachmentSpecs.empty())
		{
			m_colorAttachments.resize(m_colorAttachmentSpecs.size(), NULL);
			
			for (uint32_t i = 0; i < m_colorAttachments.size(); ++i)
			{
				if (m_colorAttachmentSpecs[i].TextureOverride == NULL && m_colorAttachments[i] == NULL)
				{
					uint32_t id;
					FBUtils::CreateTextures(multisampled, &id, 1);
					m_colorAttachments[i] = Texture2D::Create(id, m_specification.Width, m_specification.Height, 
															  (uint32_t)FBUtils::TextureFormatToGLInternalFormat(m_colorAttachmentSpecs[i].TextureFormat),
															  (uint32_t)FBUtils::TextureFormatToGLFormat(m_colorAttachmentSpecs[i].TextureFormat),
															  (uint32_t)(m_colorAttachmentSpecs[i].TextureFormat == FrameBufferTextureFormat::RED_F ? GL_FLOAT : GL_UNSIGNED_BYTE),
															  (uint32_t)m_specification.Samples);

					FBUtils::BindTexture(multisampled, m_colorAttachments[i]->GetRenderID());
					FBUtils::AttachColorTexture(m_colorAttachments[i]->GetRenderID(),
												(uint32_t)m_specification.Samples,
												(uint32_t)FBUtils::TextureFormatToGLInternalFormat(m_colorAttachmentSpecs[i].TextureFormat),
												(uint32_t)FBUtils::TextureFormatToGLFormat(m_colorAttachmentSpecs[i].TextureFormat),
												m_specification.Width,
												m_specification.Height, i,
												(uint32_t)(m_colorAttachmentSpecs[i].TextureFormat == FrameBufferTextureFormat::RED_F ? GL_FLOAT : GL_UNSIGNED_BYTE));
				}
				else
				{
					m_colorAttachments[i] = m_colorAttachmentSpecs[i].TextureOverride;
					FBUtils::BindTexture(multisampled, m_colorAttachments[i]->GetRenderID());
					//glBindTexture(GL_TEXTURE_2D, m_colorAttachments[i]->GetRenderID());

					FBUtils::ReAttachColorTexture(m_colorAttachments[i]->GetRenderID(), m_specification.Samples, i);
				}
			}
		}

		if (m_depthAttachmentSpecs.TextureFormat != FrameBufferTextureFormat::None)
		{
			if (m_depthAttachmentSpecs.TextureOverride == NULL && m_depthAttachment == NULL)
			{
				uint32_t id;
				FBUtils::CreateTextures(multisampled, &id, 1);
				m_depthAttachment = Texture2D::Create(id, m_specification.Width, m_specification.Height, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, m_specification.Samples);
				//m_depthAttachment->Bind();

				//FBUtils::CreateTextures(multisampled, &m_depthAttachment, 1);
				FBUtils::BindTexture(multisampled, m_depthAttachment->GetRenderID());
				switch (m_depthAttachmentSpecs.TextureFormat)
				{
				case FrameBufferTextureFormat::DEPTH24STENCIL8:
					FBUtils::AttachDepthTexture(m_depthAttachment->GetRenderID(), m_specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_specification.Width, m_specification.Height);
					break;
				}
			}
			else
			{
				m_depthAttachment = m_depthAttachmentSpecs.TextureOverride;
				FBUtils::BindTexture(multisampled, m_depthAttachment->GetRenderID());

				switch (m_depthAttachmentSpecs.TextureFormat)
				{
				case FrameBufferTextureFormat::DEPTH24STENCIL8:
					FBUtils::ReAttachDepthTexture(m_depthAttachment->GetRenderID(), m_specification.Samples, GL_DEPTH_STENCIL_ATTACHMENT);
					break;
				}
			}
		}

		if (m_colorAttachments.size() > 1)
		{
			ELYSIUM_CORE_ASSERT(m_colorAttachments.size() <= 8, "Currently Only Supporting a Maximum of 8 Color Attachments");

			std::vector<GLenum> buffers;
			buffers.reserve(m_colorAttachments.size());
			for (uint32_t i = 0; i < static_cast<uint32_t>(m_colorAttachments.size()); ++i)
				buffers.push_back(GL_COLOR_ATTACHMENT0 + i);

			glDrawBuffers(static_cast<uint32_t>(m_colorAttachments.size()), buffers.data());
		}
		else if (m_colorAttachments.empty())
		{
			// Depth Pass Only
			glDrawBuffer(GL_NONE);
		}
		
		auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		ELYSIUM_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is Incomplete.");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::UpdateSpecification(const FrameBufferSpecification& specification)
	{
		if (specification.Width == 0 || specification.Height == 0 || specification.Width > s_maxFramebufferSize || specification.Height > s_maxFramebufferSize)
		{
			ELYSIUM_CORE_WARN("Attempted Resize Framebuffer to {0}, {1}", specification.Width, specification.Height);
			return;
		}

		Invalidate();
	}

	void OpenGLFrameBuffer::Resize(unsigned int width, unsigned int height)
	{
		if (width == 0 || height == 0 || width > s_maxFramebufferSize || height > s_maxFramebufferSize)
		{
			ELYSIUM_CORE_WARN("Attempted Resize Framebuffer to {0}, {1}", width, height);
			return;
		}

		m_specification.Width = width;
		m_specification.Height = height;

		for (auto color : m_colorAttachments)
		{
			color->Resize(m_specification.Width, m_specification.Height);
		}

		if (m_depthAttachment)
			m_depthAttachment->Resize(m_specification.Width, m_specification.Height);
		
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		if (m_colorAttachments.size() > 1)
		{
			ELYSIUM_CORE_ASSERT(m_colorAttachments.size() <= 8, "Currently Only Supporting a Maximum of 8 Color Attachments");
		
			std::vector<GLenum> buffers;
			buffers.reserve(m_colorAttachments.size());
			for (uint32_t i = 0; i < static_cast<uint32_t>(m_colorAttachments.size()); ++i)
				buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
		
			glDrawBuffers(static_cast<uint32_t>(m_colorAttachments.size()), buffers.data());
		}
		else if (m_colorAttachments.empty())
		{
			// Depth Pass Only
			glDrawBuffer(GL_NONE);
		}
		ELYSIUM_CORE_ASSERT(glCheckNamedFramebufferStatus(m_id, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is Incomplete.");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//Invalidate();
	}

	int OpenGLFrameBuffer::ReadPixel(uint32_t attachmentIndex, unsigned int x, unsigned int y)
	{
		ELYSIUM_CORE_ASSERT(attachmentIndex < m_colorAttachments.size());
		
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData); // TODO: Expand to read more than just red integer
		
		return pixelData;
	}

	float OpenGLFrameBuffer::ReadPixelF(uint32_t attachmentIndex, unsigned int x, unsigned int y)
	{
		ELYSIUM_CORE_ASSERT(attachmentIndex < m_colorAttachments.size());

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		float pixelData;
		glReadPixels(x, y, 1, 1, GL_RED,  GL_FLOAT, &pixelData); // TODO: Expand to read more than just red integer

		return pixelData;
	}

	uint8_t* OpenGLFrameBuffer::ReadPixelBuffer(uint32_t attachmentIndex, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		ELYSIUM_CORE_ASSERT(attachmentIndex < m_colorAttachments.size());
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);

		uint32_t dataFormat = 0;
		uint32_t dataType = 0;
		uint32_t nChannels = 1;
		switch (m_colorAttachmentSpecs[attachmentIndex].TextureFormat)
		{
		case FrameBufferTextureFormat::RED_INT:
			dataFormat = GL_RED;
			dataType = GL_INT;
			nChannels = 1;
			break;
		case FrameBufferTextureFormat::RED_F:
			dataFormat = GL_RED;
			dataType = GL_FLOAT;
			nChannels = 1;
			break;
		case FrameBufferTextureFormat::RGBA8:
			dataFormat = GL_RGBA;
			dataType = GL_UNSIGNED_BYTE;
			nChannels = 4;
			break;
		}

		uint8_t* pixelData = new uint8_t[width * height * nChannels];
		glReadPixels(x, y, width, height, dataFormat, dataType, pixelData);
		return pixelData;
	}

	void OpenGLFrameBuffer::ClearAttachmentI(uint32_t attachmentIndex, int value)
	{
		ELYSIUM_CORE_ASSERT(attachmentIndex < m_colorAttachments.size());

		glClearTexImage(m_colorAttachments[attachmentIndex]->GetRenderID(), 0, FBUtils::TextureFormatToGLFormat(m_colorAttachmentSpecs[attachmentIndex].TextureFormat), GL_INT, &value);
	}

	void OpenGLFrameBuffer::ClearAttachmentF(uint32_t attachmentIndex, const float* value)
	{
		ELYSIUM_CORE_ASSERT(attachmentIndex < m_colorAttachments.size());
	
		glClearTexImage(m_colorAttachments[attachmentIndex]->GetRenderID(), 0, 
			FBUtils::TextureFormatToGLFormat(m_colorAttachmentSpecs[attachmentIndex].TextureFormat), 
			m_colorAttachmentSpecs[attachmentIndex].TextureFormat == FrameBufferTextureFormat::RED_F ? GL_FLOAT : GL_UNSIGNED_BYTE, value);
	}

	void OpenGLFrameBuffer::DrawTo(const std::shared_ptr<FrameBuffer>& output, uint32_t index, bool linearInterp)
	{
		//TODO: Expand to allow for drawing from non-color buffers

		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, output->GetRenderID());

		glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
		glDrawBuffer(GL_COLOR_ATTACHMENT0 + index);
		glBlitFramebuffer(0, 0, m_specification.Width, m_specification.Height, 
						  0, 0, output->GetSpecification().Width, output->GetSpecification().Height, GL_COLOR_BUFFER_BIT, linearInterp ? GL_LINEAR : GL_NEAREST);
	
#if 0
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			ELYSIUM_CORE_ASSERT(false);
		}
#endif

		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}
}