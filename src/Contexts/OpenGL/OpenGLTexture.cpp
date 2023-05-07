#include "elysium_pch.h"
#include "Contexts/OpenGL/OpenGLTexture.h"

#include "Elysium/Core/Asserts.h"
#include "Elysium/Logging/Instrumentor.h"

#include "Elysium/Utils/FileUtils.h"

#include <stb_image.h>
#include <gl/glew.h>

namespace Elysium
{
	static GLenum ConvertWrapMode(WrapMode mode)
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

	static GLenum ConvertFilterMode(FilterMode mode)
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

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, nullptr);

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

		int width, height, nrComponents;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = NULL;
		{
			ELYSIUM_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
			data = stbi_load(solvedFilepath.c_str(), &width, &height, &nrComponents, 0);
		}
		ELYSIUM_CORE_ASSERT(data, "Failed to load image texture.");
		
		m_width = width;
		m_height = height;
		
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		
		//TODO::Determine correct formats for nrComponents 2 (aka Grey and Alpha)
		// Example image is within .default_assets/textures/Test_NR2.png
		// https://www.khronos.org/opengl/wiki/Image_Format
		
		GLenum internalFormat = nrComponents == 1 ? GL_RGB8 : nrComponents == 3 ? GL_RGB8 : GL_RGBA8;
		GLenum format = nrComponents == 1 ? GL_RED : nrComponents == 3 ? GL_RGB : GL_RGBA;

		m_dataFormat = format;
		m_internalFormat = internalFormat;

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
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
	
		m_width = format.Size.x;
		m_height = format.Size.y;

		ELYSIUM_PROFILE_FUNCTION();

		if (format.PixelFormat != 4)
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		auto nrComponents = format.PixelFormat != 4 ? 1 : 4; // Move to parameter?
		GLenum internalFormat = nrComponents == 1 ? GL_R8 : nrComponents == 3 ? GL_RGB8 : GL_RGBA8;
		GLenum dataFormat = nrComponents == 1 ? GL_RED : nrComponents == 3 ? GL_RGB : GL_RGBA;

		m_dataFormat = dataFormat;
		m_internalFormat = internalFormat;

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		
		// Filter Mode
		auto filtermode = ConvertFilterMode(format.Filter);
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, filtermode);
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, filtermode);

		// Wrap Mode
		auto wrapmode = ConvertWrapMode(format.Wrap);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, wrapmode);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, wrapmode);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, wrapmode);

		if (format.PixelFormat != 4)
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Reset unpacking alignment to default

		glBindTexture(GL_TEXTURE_2D, 0);
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

		if (!format.FilePath.size())
		{
			m_width = format.Size.x;
			m_height = format.Size.y;

			nrComponents = 4; // Move to parameter?
		}
		else
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

		if (format.PixelFormat != 4)
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		GLenum internalFormat;
		if (format.sRGB)
		{
			internalFormat = nrComponents == 1 ? GL_SRGB8 : nrComponents == 3 ? GL_SRGB8 : GL_SRGB8_ALPHA8;
		}
		else
		{
			internalFormat = nrComponents == 1 ? GL_RGB8 : nrComponents == 3 ? GL_RGB8 : GL_RGBA8;
		}
		GLenum dataformat = nrComponents == 1 ? GL_RED : nrComponents == 3 ? GL_RGB : GL_RGBA;

		m_dataFormat = dataformat;
		m_internalFormat = internalFormat;

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, dataformat, GL_UNSIGNED_BYTE, data);

		// Filter Mode
		auto filtermode = ConvertFilterMode(format.Filter);
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, filtermode);
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, filtermode);

		// Wrap Mode
		auto wrapmode = ConvertWrapMode(format.Wrap);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, wrapmode);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, wrapmode);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, wrapmode);

		if (format.PixelFormat != 4)
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Reset unpacking alignment to default

		glBindTexture(GL_TEXTURE_2D, 0);

		if (data)
			stbi_image_free(data);
	}

	void OpenGLTexture2D::Initialize(const Texture2DOutline* mData)
	{
		int width, height, nrComponents;
		void* data = nullptr;

		if (!mData->Filepath.size())
		{
			m_width = mData->Size.x;
			m_height = mData->Size.y;

			nrComponents = 4; // Move to parameter?
		}
		else
		{
			stbi_set_flip_vertically_on_load(mData->Flipped);
			{
				ELYSIUM_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
				data = stbi_load(mData->Filepath.c_str(), &width, &height, &nrComponents, 0);
			}
			ELYSIUM_CORE_ASSERT(data, "Failed to load image texture.");

			m_width = width;
			m_height = height;
		}

		if (mData->PixelFormat != 4)
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		GLenum internalFormat;
		if (mData->sRGB)
		{
			internalFormat = nrComponents == 1 ? GL_SRGB8 : nrComponents == 3 ? GL_SRGB8 : GL_SRGB8_ALPHA8;
		}
		else
		{
			internalFormat = nrComponents == 1 ? GL_RGB8 : nrComponents == 3 ? GL_RGB8 : GL_RGBA8;
		}
		GLenum dataformat = nrComponents == 1 ? GL_RED : nrComponents == 3 ? GL_RGB : GL_RGBA;

		m_dataFormat = dataformat;
		m_internalFormat = internalFormat;

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, dataformat, GL_UNSIGNED_BYTE, data);

		// Filter Mode
		auto filtermode = ConvertFilterMode((FilterMode)mData->FilterMode);
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, filtermode);
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, filtermode);

		// Wrap Mode
		auto wrapmode = ConvertWrapMode((WrapMode)mData->WrapMode);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, wrapmode);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, wrapmode);
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, wrapmode);

		if (mData->PixelFormat != 4)
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Reset unpacking alignment to default

		glBindTexture(GL_TEXTURE_2D, 0);

		if (data)
			stbi_image_free(data);
	}

	void OpenGLTexture2D::Resize(uint32_t width, uint32_t height)
	{
		m_width = width;
		m_height = height;
		
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

		unsigned int bpp = m_dataFormat == GL_RED ? 1 : m_dataFormat == GL_RGB ? 3 : 4;
		ELYSIUM_CORE_ASSERT(size == m_width * m_height * bpp, "Data Does Not Cover Entire Texture.");

		glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture2D::Bind(uint8_t slot) const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_id);
	}
}