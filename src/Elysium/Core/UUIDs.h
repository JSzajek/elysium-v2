#pragma once

#include <string>

#include <uuid.h>

namespace Elysium
{
	/// <summary>
	/// Struct representing a unique id.
	/// </summary>
	struct UUID
	{
	public:
		static const UUID nil;
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		UUID()
			: m_id(uuids::uuid_system_generator{}())
		{
		}

		/// <summary>
		/// Constructor initializing a UUID.
		/// </summary>
		/// <param name="id">the id</param>
		UUID(const uuids::uuid& id)
			: m_id(id)
		{
		}

		/// <summary>
		/// Constructor initializing a UUID.
		/// </summary>
		/// <param name="string">The string to create the UUID from</param>
		UUID(const std::string string)
			: m_id(uuids::uuid::from_string(string))
		{
		}

		/// <summary>
		/// Default copy constructor.
		/// </summary>
		/// <param name="copy">The UUID to copy</param>
		UUID(const UUID& copy)
			: m_id(copy.m_id)
		{
		}
	public:
		/// <summary>
		/// Sets the uuid from a string.
		/// </summary>
		/// <param name="string">The string to use</param>
		inline void Set(const std::string& string) { m_id = uuids::uuid::from_string(string); }

		/// <summary>
		/// Retrieves the representative string of the uuid.
		/// </summary>
		/// <returns>The string of the uuid</returns>
		inline const std::string GetString() const { return uuids::to_string(m_id); }

		/// <summary>
		/// The boolean conversion operator.
		/// </summary>
		/// <returns>Whether the uuid is nil</returns>
		inline operator bool() const { return !m_id.is_nil(); }

		/// <summary>
		/// Equality operator override.
		/// </summary>
		/// <param name="r_val">The comparing uuid</param>
		/// <returns>True if the uuids are equal</returns>
		inline bool operator==(const UUID& r_val) const { return m_id == r_val.m_id; }

		/// <summary>
		/// Not equality operator override.
		/// </summary>
		/// <param name="r_val">The comparing uuid</param>
		/// <returns>True if the uuids aren't equal</returns>
		inline bool operator!=(const UUID& r_val) const { return m_id != r_val.m_id; }
	private:
		uuids::uuid m_id;
	};
}