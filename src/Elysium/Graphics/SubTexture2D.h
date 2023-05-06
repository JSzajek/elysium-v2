#pragma once

#include "Elysium/Graphics/Texture.h"

#include "Elysium/Math/Vec2.h"

namespace Elysium
{
	class SubTexture2D
	{
	public:
		SubTexture2D(const std::shared_ptr<Texture2D>& texture, const Math::Vec2& minBounds, const Math::Vec2& maxBounds);

		const uint32_t GetRenderID() const { return m_texture->GetRenderID(); }

		const std::shared_ptr<Texture2D>& GetTexture() const { return m_texture; }
		const Math::Vec2* GetTextureCoordinates() const { return m_textureCoords; }

		static std::shared_ptr<SubTexture2D> CreateFromCoords(const std::shared_ptr<Texture2D>& texture, float x, float y, float cellWidth, float cellHeight, float spriteWidth, float spriteHeight);
		static std::shared_ptr<SubTexture2D> CreateFromCoords(const std::shared_ptr<Texture2D>& texture, float xPos, float yPos, float spriteWidth, float spriteHeight);
	private:
		std::shared_ptr<Texture2D> m_texture;
		Math::Vec2 m_textureCoords[4];
	};
}