#pragma once

#include "Elysium/Core/Memory.h"

#include "Elysium/Graphics/FrameBuffer.h"
#include "Elysium/Graphics/Texture.h"
#include "Elysium/Graphics/Shader.h"

namespace Elysium
{
	class RenderCommands
	{
	public:
		/// <summary>
		/// Enum class representing a way to draw the texture.
		/// </summary>
		enum class TextureDrawType : unsigned char
		{
			Color = 0,
		};
	private:
		friend class Application;
	public:
		/// <summary>
		/// Helper render command to draw a texture to a buffer.
		/// </summary>
		/// <param name="output">The output buffer</param>
		/// <param name="type">The texture draw type</param>
		/// <param name="textureAttachment">The render id of the texture to draw</param>
		static void DrawTexture(const Shared<FrameBuffer>& output, TextureDrawType type, uint32_t textureId);

		/// <summary>
		/// Helper render command to draw a texture to a buffer.
		/// </summary>
		/// <param name="output">The output buffer</param>
		/// <param name="type">The texture draw type</param>
		/// <param name="texture">The texture to draw</param>
		/// <param name="drawShader">The shader override to use</param>
		static void DrawTexture(const Shared<FrameBuffer>& output, TextureDrawType type, const Shared<Texture2D>& texture, 
								const Shared<Shader>& drawShader = nullptr);

		/// <summary>
		/// Helper render command to draw textures to a buffer.
		/// </summary>
		/// <param name="output">The output buffer</param>
		/// <param name="drawShader">The shader to use</param>
		/// <param name="textures">The textures to draw</param>
		static void DrawTextures(const Shared<FrameBuffer>& output, const Shared<Shader>& drawShader, const std::vector<Shared<Texture2D>>& textures);

		/// <summary>
		/// Helper render command to draw a screen shader to a buffer.
		/// </summary>
		/// <param name="output">The output buffer</param>
		/// <param name="shader">The shader to draw</param>
		static void DrawScreenShader(const Shared<FrameBuffer>& output, const Shared<Shader>& shader);
	private:
		/// <summary>
		/// Initializes the dependencies for the render commands.
		/// </summary>
		static void InitializeDependencies();
	};
}