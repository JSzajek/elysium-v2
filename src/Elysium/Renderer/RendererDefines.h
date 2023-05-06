#pragma once

#include "Elysium/Math/Vec2.h"
#include "Elysium/Math/Vec3.h"

namespace Elysium
{
	#define QUAD_VERTEX_COUNT			4
	#define DEFAULT_TILING_FACTOR		Math::Vec2::One

	static const Math::Vec2 s_defaultTextureCoords[4] = { Math::Vec2(1.0f, 1.0f),
														  Math::Vec2(1.0f, 0.0f),
														  Math::Vec2(0.0f, 0.0f),
														  Math::Vec2(0.0f, 1.0f) };

	static const Math::Vec3 s_defaultQuadCoords[4] = { Math::Vec3(0, 0, 0),
													   Math::Vec3(1, 0, 0),
													   Math::Vec3(1, 1, 0),
													   Math::Vec3(0, 1, 0) };
	/*
	static const Math::Vec3 s_defaultQuadCoords[4] = { Math::Vec3(1, 1, 0),
													   Math::Vec3(1, 0, 0),
													   Math::Vec3(0, 0, 0),
													   Math::Vec3(0, 1, 0) };
	 */

	struct RendererCaps
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const unsigned int MaxTextureSlots = 16; // TODO: Fetch Render Caps
	};
}