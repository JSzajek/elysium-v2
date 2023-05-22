#include "elysium_pch.h"
#include "Contexts/OpenGL/OpenGLTexture.h"

#include "Elysium/Core/Asserts.h"
#include "Elysium/Logging/Instrumentor.h"

#include "Elysium/Utils/FileUtils.h"

#include <stb_image.h>
#include <gl/glew.h>

namespace Elysium
{
	namespace TexUtils
	{
		GLenum ConvertWrapMode(WrapMode mode)
		{
			switch (mode)
			{
			case WrapMode::Repeat:
				return GL_REPEAT;
			case WrapMode::ClampBorder:
				return GL_CLAMP_TO_BORDER;
			case WrapMode::ClampEdge:
				return GL_CLAMP_TO_EDGE;
			case WrapMode::Mirror:
				return GL_MIRRORED_REPEAT;
			case WrapMode::MirrorOnce:
				return GL_MIRROR_CLAMP_TO_EDGE;
			}
			ELYSIUM_CORE_ASSERT(false);
			return 0;
		}

		GLenum ConvertFilterMode(FilterMode mode)
		{
			switch (mode)
			{
			case FilterMode::Linear:
				return GL_LINEAR;
			case FilterMode::Nearest:
				return GL_NEAREST;
			}
			ELYSIUM_CORE_ASSERT(false);
			return 0;
		}

		PixelAlignment TextureWidthToPixelAlignment(uint32_t width)
		{
			// NOTE:: 8 byte alignment is too specialized of a use case to utilize.

			if (width % 4 == 0)
				return PixelAlignment::WordAligned;
			else if (width % 2 == 0)
				return PixelAlignment::RowAligned;
			else
				return PixelAlignment::Byte;
		}
	}

	

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_debugpath(), m_width(width), m_height(height), m_uuid()
	{
		ELYSIUM_PROFILE_FUNCTION();

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		auto nrComponents = 4; // Move to parameter?
		GLenum internalFormat = nrComponents == 1 ? GL_RGB8 : nrComponents == 3 ? GL_RGB8 : GL_RGBA8;
		GLenum format = nrComponents == 1 ? GL_RED : nrComponents == 3 ? GL_RGB : GL_RGBA;

		m_dataFormat = format;
		m_internalFormat = internalFormat;

		m_type = GL_UNSIGNED_BYTE;

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, m_type, nullptr);

		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t id, uint32_t width, uint32_t height, unsigned int internalFormat, unsigned int dataFormat, unsigned int type, unsigned int samples)
		: m_id(id), m_width(width), m_height(height), m_internalFormat(internalFormat), m_dataFormat(dataFormat), m_type(type), m_samples(samples)
	{
		ELYSIUM_PROFILE_FUNCTION();
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
		: m_debugpath(filepath), m_width(0), m_height(0), m_uuid()
	{
		ELYSIUM_PROFILE_FUNCTION();

		const std::string solvedFilepath = FileUtils::GetAssetPath_Str(filepath);

		TextureFormat format;
		format.FilePath = solvedFilepath;

		Initialize(format);
	}

	OpenGLTexture2D::OpenGLTexture2D(const TextureFormat& format)
		: m_uuid(format.Uuid)
	{
		ELYSIUM_PROFILE_FUNCTION();
		
		m_debugpath = format.FilePath;

		Initialize(format);
	}

	OpenGLTexture2D::OpenGLTexture2D(const TextureFormat& format, const void* data)
		: m_uuid(format.Uuid)
	{
		m_debugpath = format.FilePath;
	
		Initialize(format, data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		ELYSIUM_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_id);
	}

	void OpenGLTexture2D::Initialize(const TextureFormat& format)
	{
		int width, height, nrComponents;
		void* data = nullptr;

		if (!format.FilePath.empty())
		{
			stbi_set_flip_vertically_on_load(format.Flipped);
			{
				ELYSIUM_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
				data = stbi_load(format.FilePath.c_str(), &width, &height, &nrComponents, 0);
			}
			ELYSIUM_CORE_ASSERT(data, "Failed to load image texture.");

			m_width = width;
			m_height = height;
		}

		Initialize(format, data);

		if (data)
			stbi_image_free(data);
	}

	void OpenGLTexture2D::Initialize(const TextureFormat& format, const void* data)
	{
		m_width = format.Size.x;
		m_height = format.Size.y;

		ELYSIUM_PROFILE_FUNCTION();

		if (format.Alignment != PixelAlignment::NotSpecified)
			m_pixelAlignment = format.Alignment;
		else
			m_pixelAlignment = TexUtils::TextureWidthToPixelAlignment(m_width);

		glPixelStorei(GL_UNPACK_ALIGNMENT, m_pixelAlignment);

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		// NOTE:: Assumed only 8-bit formats
		m_type = GL_UNSIGNED_BYTE;

		switch (format.Format)
		{
			case PixelFormat::R_8:
			{
				m_internalFormat = GL_R8;
				m_dataFormat = GL_RED;
				break;
			}
			case PixelFormat::R8G8:
			{
				m_internalFormat = GL_RG8;
				m_dataFormat = GL_RG;
				break;
			}
			case PixelFormat::R8G8B8:
			{
				m_internalFormat = GL_RGB8;
				m_dataFormat = GL_RGB;
				break;
			}
			case PixelFormat::RGBA_8:
			{
				m_internalFormat = GL_RGBA8;
				m_dataFormat = GL_RGBA;
				break;
			}
		}

		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_dataFormat, m_type, data);

		// Filter Mode
		auto filtermode = TexUtils::ConvertFilterMode(format.Filter);
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, filtermode);
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, filtermode);

		// Wrap Mode
		auto wrapmode = TexUtils::ConvertWrapMode(format.Wrap);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, wrapmode);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, wrapmode);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, wrapmode);

		// Reset unpacking alignment to default
		glPixelStorei(GL_UNPACK_ALIGNMENT, (uint8_t)PixelAlignment::WordAligned);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture2D::Initialize(const Texture2DOutline* mData)
	{
		TextureFormat format;
		format.FilePath = mData->Filepath;
		format.Size = mData->Size;

		format.Type = static_cast<TextureType>(mData->TextureType);
		format.Shape = static_cast<TextureShape>(mData->TextureShape);

		format.sRGB = mData->sRGB;
		format.Flipped = mData->Flipped;
		format.Source = static_cast<AlphaSource>(mData->AlphaSource);
		format.AlphaTransparency = mData->AlphaTransparency;
		format.Wrap = static_cast<WrapMode>(mData->WrapMode);
		format.Filter = static_cast<FilterMode>(mData->FilterMode);
		
		format.Format = static_cast<PixelFormat>(mData->PixelFormat);

		Initialize(format);
	}

	void OpenGLTexture2D::Resize(uint32_t width, uint32_t height, PixelAlignment alignment)
	{
		m_width = width;
		m_height = height;

		if (alignment != PixelAlignment::NotSpecified)
			m_pixelAlignment = alignment;
		else
			m_pixelAlignment = TexUtils::TextureWidthToPixelAlignment(m_width);

		if (m_samples > 1)
		{
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_id);
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_samples, m_internalFormat, width, height, GL_FALSE);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, m_id);
			glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_dataFormat, m_type, NULL);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	void OpenGLTexture2D::Reimport(const TextureFormat& format)
	{
		//TODO::Determine if it is possible to update texture without deletion and re-initialization
		glDeleteTextures(1, &m_id);
		Initialize(format);
	}

	void OpenGLTexture2D::Reimport(const Texture2DOutline* mData)
	{
		//TODO::Determine if it is possible to update texture without deletion and re-initialization
		glDeleteTextures(1, &m_id);
		Initialize(mData);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindTexture(GL_TEXTURE_2D, m_id);

		glPixelStorei(GL_UNPACK_ALIGNMENT, m_pixelAlignment);

		const uint32_t bpp = m_dataFormat == GL_RED ? 1 : m_dataFormat == GL_RGB ? 3 : 4;
		ELYSIUM_CORE_ASSERT(size == m_width * m_height * bpp, "Data Does Not Cover Entire Texture.");

		glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat, m_type, data);
		
		glPixelStorei(GL_UNPACK_ALIGNMENT, PixelAlignment::WordAligned);
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture2D::Bind(uint8_t slot) const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_id);
	}
}