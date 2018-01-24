#include <iostream>
#include "Mixin.h"

template<typename Accessor>
class Template1
{
protected:
	void Func1 ( )
	{
		std::cout << "Func1 called!\n";
		static_cast< Accessor* >( this )->Func2 ( );
	}
};
template<typename Accessor>
class Template2
{
protected:
	void Func2 ( )
	{
		std::cout << "Func2 called!\n";
		static_cast< Accessor* >( this )->Func3 ( );
	}
};
template<typename Accessor>
class Template3
{
protected:
	void Func3 ( )
	{
		std::cout << "Func3 called!\n";
		static_cast< Accessor* >( this )->FinalFunc ( );
	}
};
template<typename Accessor>
class MasterTemplate
{
public:
	MasterTemplate ( const int num ) : num_ { num }
	{

	}

	void MasterFunc ( )
	{
		std::cout << "Func chain start!\n";
		static_cast< Accessor* >( this )->Func1 ( );
	}

protected:
	void FinalFunc ( )
	{
		std::cout << "Success! Here's your number: " << num_ << "\n";
	}

private:
	int num_;
};

int main ( )
{
	using namespace template_bullshit;

	std::cout << "Enter a number: ";
	int input;
	std::cin >> input;

	Mixin <MasterTemplate, Template1, Template2, Template3> mixin { input };
	mixin.MasterFunc ( );

	system ( "pause" );
	return 0;
}