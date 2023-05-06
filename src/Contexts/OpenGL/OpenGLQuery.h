#pragma once

#include "Elysium/Graphics/Query.h"

namespace Elysium
{
	class OpenGLQuery : public Query
	{
	public:
		OpenGLQuery(uint32_t type);
		virtual ~OpenGLQuery() override;

		virtual void Begin() const override;
		virtual void End() const override;

		virtual void Result(int32_t* result) override;
	private:
		uint32_t m_id;
		uint32_t m_type;
	};
}