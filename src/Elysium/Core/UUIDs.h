#pragma once

#include <string>

#include <uuid.h>

namespace Elysium
{
	struct UUID
	{
	public:
		static const UUID nil;
	public:
		UUID()
			: m_id(uuids::uuid_system_generator{}())
		{
		}

		UUID(const uuids::uuid& id)
			: m_id(id)
		{
		}

		UUID(const std::string str)
			: m_id(uuids::uuid::from_string(str))
		{
		}

		UUID(const UUID& copy)
			: m_id(copy.m_id)
		{
		}
	public:
		inline void Set(const std::string& str) { m_id = uuids::uuid::from_string(str); }

		inline const std::string GetString() const { return uuids::to_string(m_id); }

		inline operator bool() const { return !m_id.is_nil(); }

		inline bool operator==(const UUID& r_val) const { return m_id == r_val.m_id; }
		inline bool operator!=(const UUID& r_val) const { return m_id != r_val.m_id; }
	private:
		uuids::uuid m_id;
	};
}