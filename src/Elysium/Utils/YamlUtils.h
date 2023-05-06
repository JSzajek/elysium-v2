#pragma once

#include "Elysium/Math/Maths.h"
#include "Elysium/Core/UUIDs.h"

#include <yaml-cpp/yaml.h>
#include <functional>

namespace YAML
{
	template<>
	struct convert<Elysium::Math::iVec2>
	{
		static Node encode(const Elysium::Math::iVec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Elysium::Math::iVec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<int>();
			rhs.y = node[1].as<int>();
			return true;
		}
	};

	template<>
	struct convert<Elysium::Math::iVec4>
	{
		static Node encode(const Elysium::Math::iVec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Elysium::Math::iVec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<int>();
			rhs.y = node[1].as<int>();
			rhs.z = node[2].as<int>();
			rhs.w = node[3].as<int>();
			return true;
		}
	};

	template<>
	struct convert<Elysium::Math::Vec2>
	{
		static Node encode(const Elysium::Math::Vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Elysium::Math::Vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Elysium::Math::Vec3>
	{
		static Node encode(const Elysium::Math::Vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Elysium::Math::Vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Elysium::Math::Vec4>
	{
		static Node encode(const Elysium::Math::Vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Elysium::Math::Vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Elysium::Math::Quat>
	{
		static Node encode(const Elysium::Math::Quat& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Elysium::Math::Quat& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Elysium::UUID>
	{
		static Node encode(const Elysium::UUID& rhs)
		{
			Node node;
			node.push_back(rhs.GetString());
			return node;
		}

		static bool decode(const Node& node, Elysium::UUID& rhs)
		{
			auto t = node.as<std::string>();
			rhs.Set(t);
			return true;
		}
	};
}

namespace Elysium
{
	struct YamlUtils
	{
		static void CreateTo(const std::string& filepath, std::function<void(YAML::Emitter&)> writeFunc);
	};

	YAML::Emitter& operator<<(YAML::Emitter& out, const Math::iVec2& vector);
	YAML::Emitter& operator<<(YAML::Emitter& out, const Math::iVec4& vector);
	
	YAML::Emitter& operator<<(YAML::Emitter& out, const Math::Vec2& vector);
	YAML::Emitter& operator<<(YAML::Emitter& out, const Math::Vec3& vector);
	YAML::Emitter& operator<<(YAML::Emitter& out, const Math::Vec4& vector);
	
	YAML::Emitter& operator<<(YAML::Emitter& out, const Math::Quat& quat);

	YAML::Emitter& operator<<(YAML::Emitter& out, const UUID& uuid);
}