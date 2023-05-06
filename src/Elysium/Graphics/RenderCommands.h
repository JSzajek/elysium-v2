#pragma once

#include "Elysium/Core/Memory.h"

#include "Elysium/Graphics/FrameBuffer.h"
#include "Elysium/Graphics/Texture.h"
#include "Elysium/Graphics/Shader.h"

namespace Elysium
{
	enum class TextureDrawType : unsigned char
	{
		Color = 0,
	};

	class RenderCommands
	{
	private:
		friend class Application;
	public:
		static void DrawTexture(const Shared<FrameBuffer>& output, TextureDrawType type, uint32_t textureAttachment);
		static void DrawTexture(const Shared<FrameBuffer>& output, TextureDrawType type, const Shared<Texture2D>& texture);
		static void DrawShader(const Shared<FrameBuffer>& output, const Shared<Shader>& shader);
	private:
		static void InitializeDependencies();
	};
}