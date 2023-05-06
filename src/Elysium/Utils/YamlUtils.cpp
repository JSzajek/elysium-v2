#include "elysium_pch.h"
#include "Elysium/Utils/YamlUtils.h"

#include "Elysium/Core/Base.h"

#include <fstream>

namespace Elysium
{
	void YamlUtils::CreateTo(const std::string& filepath, std::function<void(YAML::Emitter&)> writeFunc)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;

		writeFunc(out);

		out << YAML::EndMap;
		std::ofstream stream(filepath);
		stream << out.c_str();
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Math::iVec2& vector)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << vector.x << vector.y << YAML::EndSeq;
		return out;
	}
	
	YAML::Emitter& operator<<(YAML::Emitter & out, const Math::iVec4 & vector)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << vector.x << vector.y << vector.z << vector.w << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Math::Vec2& vector)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << vector.x << vector.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Math::Vec3& vector)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << vector.x << vector.y << vector.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Math::Vec4& vector)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << vector.x << vector.y << vector.z << vector.w << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Math::Quat& quat)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << quat.x << quat.y << quat.z << quat.w << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const UUID& uuid)
	{
		out << uuid.GetString();
		return out;
	}
}