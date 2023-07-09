#pragma once

/// <summary>
/// Interface class representing a graphic bind-able.
/// </summary>
class IBindable
{
public:
	/// <summary>
	/// Default destructor.
	/// </summary>
	virtual ~IBindable() { }

	/// <summary>
	/// Binds the graphics object.
	/// </summary>
	virtual void Bind() const = 0;

	/// <summary>
	/// Unbinds the graphics object.
	/// </summary>
	virtual void Unbind() const = 0;
};

/// <summary>
/// Interface class representing an abstract render-able object.
/// </summary>
class IRenderObject
{
public:
	/// <summary>
	/// Default destructor.
	/// </summary>
	virtual ~IRenderObject() { }

	/// <summary>
	/// Retrieves the render id.
	/// </summary>
	/// <returns>The render id</returns>
	virtual uint32_t GetRenderID() const = 0;

	/// <summary>
	/// Retrieves a reference to the render id.
	/// </summary>
	/// <returns>The reference to the render id</returns>
	virtual uint32_t& GetRenderIDRef() = 0;
};

class BindableRenderObject : public IRenderObject, public IBindable
{
public:
	/// <summary>
	/// Default destructor.
	/// </summary>
	virtual ~BindableRenderObject() { }
};