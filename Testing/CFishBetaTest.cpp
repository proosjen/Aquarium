#include "stdafx.h"
#include "CppUnitTest.h"

#include "FishBeta.h"
#include "Aquarium.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	/** Mock class for testing CFishBeta */
	class CFishBetaMock : public CFishBeta
	{
	public:
		CFishBetaMock(CAquarium *aquarium) : CFishBeta(aquarium) {}
	}; 

	TEST_CLASS(CFishBetaTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCFishBetaConstruct)
		{
			CAquarium aquarium;
			CFishBetaMock item(&aquarium);
		}

	};
}