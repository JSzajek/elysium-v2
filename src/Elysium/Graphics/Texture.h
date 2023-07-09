#pragma once

#include "Elysium/Core/Memory.h"
#include "Elysium/Core/UUIDs.h"
#include "Elysium/Graphics/RenderObject.h"

#include "Elysium/Math/iVec2.h"

#include "Elysium/Outlines/Formats.h"
#include "Elysium/Outlines/Templates.h"

#include "Elysium/Utils/YamlUtils.h"

#include <string>

namespace Elysium
{
	/// <summary>
	/// A generic graphics texture object.
	/// </summary>
	class Texture : public IRenderObject
	{
	public:
		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~Texture() = default;

		/// <summary>
		/// Retrieves the width of the texture.
		/// </summary>
		/// <returns>The width</returns>
		virtual uint32_t GetWidth() const = 0;

		/// <summary>
		/// Retrieves the height of the texture.
		/// </summary>
		/// <returns>The height</returns>
		virtual uint32_t GetHeight() const = 0;

		/// <summary>
		/// Retrieves the depth of the texture.
		/// </summary>
		/// <returns>The depth</returns>
		virtual uint32_t GetDepth() const = 0;

		/// <summary>
		/// Retrieves the unique id of the shader.
		/// </summary>
		/// <returns>The unique id</returns>
		virtual UUID GetID() const = 0;
		
		/// <summary>
		/// Retrieves the name of the texture.
		/// </summary>
		/// <returns>The name</returns>
		virtual std::string GetName() const = 0;

		/// <summary>
		/// Retrieves the pixel format of the texture.
		/// </summary>
		/// <returns>The pixel format</returns>
		virtual PixelFormat GetPixelFormat() const = 0;

		/// <summary>
		/// Retrieves the pixel depth of the texture.
		/// </summary>
		/// <returns>The pixel bit depth</returns>
		virtual PixelBitDepth GetBitDepth() const = 0;

		/// <summary>
		/// Re-imports the settings of the texture from the passed texture format.
		/// </summary>
		/// <param name="format">The new texture format</param>
		virtual void Import(const TextureFormat& format) = 0;
		
		/// <summary>
		/// Sets the pixel data of the texture.
		/// </summary>
		/// <param name="data">The pixel data</param>
		/// <param name="size">The total pixel data size</param>
		virtual void SetData(void* data, uint32_t size) = 0;
		
		/// <summary>
		/// Binds the texture to the passed slot index.
		/// </summary>
		/// <param name="slot">The index to bind to</param>
		virtual void Bind(uint8_t slot = 0) const = 0;
		
		/// <summary>
		/// Equality operator override.
		/// </summary>
		/// <param name="other">The comparing texture</param>
		/// <returns>True if the textures are equal</returns>
		virtual bool operator==(const Texture& other) const = 0;
	};

	/// <summary>
	/// Class representing a 2-dimensional texture
	/// </summary>
	class Texture2D : public Texture
	{
	public:
		/// <summary>
		/// Resizes the texture.
		/// </summary>
		virtual void Resize(uint32_t width, uint32_t height, PixelAlignment alignment = PixelAlignment::NotSpecified) = 0;

		/// <summary>
		/// Imports the texture with the outline data. 
		/// 
		/// NOTE: This will cause texture re-initialization 
		/// if the texture is already initialized.
		/// </summary>
		/// <param name="mData">The outline data</param>
		/// <param name="outputFilepath">The texture filepath</param>
		void Import(const Texture2DOutline* mData, const std::string& outputFilepath) 
		{ 
			Import(mData); 
			WriteToFile(mData, outputFilepath); 
		}

	public:
		/// <summary>
		/// Imports the texture with the outline data. 
		/// 
		/// NOTE: This will cause texture re-initialization 
		/// if the texture is already initialized.
		/// </summary>
		/// <param name="mData">The outline data</param>
		virtual void Import(const Texture2DOutline* mData) = 0;
		
		/// <summary>
		/// Writes the texture data to the provided output filepath.
		/// </summary>
		/// <param name="mData">The outline data</param>
		/// <param name="outputFilepath">The output filepath</param>
		static void WriteToFile(const Texture2DOutline* mData, const std::string& outputFilepath);

		/// <summary>
		/// Creates a 2-dimensional texture.
		/// </summary>
		/// <param name="id">The outline data</param>
		/// <param name="width">The outline data</param>
		/// <param name="height">The outline data</param>
		/// <returns>The created texture</returns>
		static Shared<Texture2D> Create(uint32_t id, uint32_t width, uint32_t height);

		/// <summary>
		/// Creates a 2-dimensional texture.
		/// </summary>
		/// <param name="width">The outline data</param>
		/// <param name="height">The outline data</param>
		/// <returns>The created texture</returns>
		static Shared<Texture2D> Create(uint32_t width, uint32_t height);

		/// <summary>
		/// Creates a 2-dimensional texture.
		/// </summary>
		/// <param name="id">The outline data</param>
		/// <param name="width">The outline data</param>
		/// <param name="height">The outline data</param>
		/// <param name="internalFormat">The internal format</param>
		/// <param name="dataFormat">The data format</param>
		/// <param name="type">The data type</param>
		/// <param name="samples">The number of samples</param>
		/// <returns>The created texture</returns>
		static Shared<Texture2D> Create(uint32_t id, uint32_t width, uint32_t height,
										uint32_t internalFormat, uint32_t dataFormat, 
										uint32_t type, uint32_t samples);

		/// <summary>
		/// Creates a 2-dimensional texture.
		/// </summary>
		/// <param name="path">The texture filepath</param>
		/// <returns>The created texture</returns>
		static Shared<Texture2D> Create(const std::string& path);

		/// <summary>
		/// Creates a 2-dimensional texture.
		/// </summary>
		/// <param name="path">The texture format</param>
		/// <returns>The created texture</returns>
		static Shared<Texture2D> Create(const TextureFormat& format);

		/// <summary>
		/// Creates a 2-dimensional texture.
		/// </summary>
		/// <param name="path">The texture format</param>
		/// <param name="path">The texture data</param>
		/// <returns>The created texture</returns>
		static Shared<Texture2D> Create(const TextureFormat& format, const void* data);
	};
}
