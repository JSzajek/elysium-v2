#include "elysium_pch.h"

#include "Elysium/Graphics/SubTexture2D.h"

namespace Elysium
{
	SubTexture2D::SubTexture2D(const std::shared_ptr<Texture2D>& texture, const Math::Vec2& minBounds, const Math::Vec2& maxBounds)
		: m_texture(texture)
	{
		m_textureCoords[0] = {minBounds.x, minBounds.y};
		m_textureCoords[1] = {maxBounds.x, minBounds.y};
		m_textureCoords[2] = {maxBounds.x, maxBounds.y};
		m_textureCoords[3] = {minBounds.x, maxBounds.y};
	}

	std::shared_ptr<SubTexture2D> SubTexture2D::CreateFromCoords(const std::shared_ptr<Texture2D>& texture, float x, float y, float cellWidth, float cellHeight, float spriteWidth, float spriteHeight)
	{
		auto min = Math::Vec2((x * cellWidth) / texture->GetWidth(), (y * cellHeight) / texture->GetHeight());
		auto max = Math::Vec2(((x + spriteWidth) * cellWidth) / texture->GetWidth(), ((y + spriteHeight) * cellHeight) / texture->GetHeight());
		return std::make_shared<SubTexture2D>(texture, min, max);
	}

	std::shared_ptr<SubTexture2D> SubTexture2D::CreateFromCoords(const std::shared_ptr<Texture2D>& texture, float xPos, float yPos, float spriteWidth, float spriteHeight)
	{
		auto min = Math::Vec2(xPos / texture->GetWidth(), yPos / texture->GetHeight());
		auto max = Math::Vec2((xPos + spriteWidth) / texture->GetWidth(), (yPos + spriteHeight) / texture->GetHeight());
		return std::make_shared<SubTexture2D>(texture, min, max);
	}
}