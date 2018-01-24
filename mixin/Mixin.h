#pragma once

namespace template_bullshit
{
	template<template<typename Accessor>class User, typename Derived>
	class Accessor : public Derived
	{
	public:
		friend User<Accessor>;

		using Derived::Derived;
	};

	template<typename Derived, template<typename Accessor>class...OtherComponents>
	class MixinBuilder;

	template<typename Derived, template<typename Accessor>class Component, template<typename Accessor>class...OtherComponents>
	class MixinBuilder<Derived, Component, OtherComponents...> : public Component<Accessor<Component, Derived>>, public MixinBuilder<Accessor<Component, Derived>, OtherComponents...>
	{
	};

	template<typename Derived>
	class MixinBuilder<Derived>
	{
	public:
		using FinalBuild = Derived;
	};

	template<template<typename Accessor> class MasterComponent, template<typename Accessor> class...OtherComponents>
	class MasterMixinBuilder : public MixinBuilder<MasterMixinBuilder<MasterComponent, OtherComponents...>, OtherComponents...>, public MasterComponent<MasterMixinBuilder<MasterComponent, OtherComponents...>>
	{
	public:
		using Master = MasterComponent<MasterMixinBuilder>;

		friend Master;
		using Master::Master;

	};

	template<template<typename Accessor> class MasterComponent, template<typename Accessor> class...OtherComponents>
	using Mixin = typename MasterMixinBuilder<MasterComponent, OtherComponents...>::FinalBuild;
}