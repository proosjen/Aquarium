#include "stdafx.h"
#include "CppUnitTest.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

#include "Aquarium.h"
#include "FishBeta.h"
#include "FishAngelfish.h"
#include "FishCarp.h"
#include "FishMolly.h"
#include "DecorSkull.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

const unsigned int RandomSeed = 1238197374;

namespace Testing
{
	TEST_CLASS(CAquariumTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCAquariumConstruct)
		{
			CAquarium aquarium;
		}

		TEST_METHOD(TestCAquariumHitTest)
		{
			CAquarium aquarium;

			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty aquarium");

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(100, 200);
			aquarium.Add(fish1);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish1,
				L"Testing fish at 100, 200");

			shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(&aquarium);
			fish2->SetLocation(100, 200);
			aquarium.Add(fish2);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish2,
				L"Testing overlapping fish at 100, 200");

			Assert::IsTrue(aquarium.HitTest(50, 100) == nullptr,
				L"Testing nullptr hit with fish in aquarium");

			Assert::IsFalse(aquarium.HitTest(100, 200) == nullptr,
				L"Testing nullptr hit with fish in aquarium");
		}

		/**
		* Create a path to a place to put temporary files
		*/
		wstring TempPath()
		{
			// Create a path to temporary files
			wchar_t path_nts[MAX_PATH];
			GetTempPath(MAX_PATH, path_nts);

			// Convert null terminated string to wstring
			return wstring(path_nts);
		}

		/**
		* Read a file into a wstring and return it.
		* \param filename Name of the file to read
		* \return File contents
		*/
		wstring ReadFile(const wstring &filename)
		{
			ifstream t(filename);
			wstring str((istreambuf_iterator<char>(t)),
				istreambuf_iterator<char>());

			return str;
		}

		TEST_METHOD(TestCAquariumSave)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create an aquarium
			CAquarium aquarium;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";
			aquarium.Save(file1);

			TestEmpty(file1);

			//
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);

			TestThreeBetas(file2);

			//
			// Test all types
			//
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);

			TestAllTypes(file3);
		}

		TEST_METHOD(TestCAquariumLoad)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create two aquariums
			CAquarium aquarium, aquarium2;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";

			aquarium.Save(file1);
			TestEmpty(file1);

			aquarium2.Load(file1);
			aquarium2.Save(file1);
			TestEmpty(file1);

			//
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);
			TestThreeBetas(file2);

			aquarium2.Load(file2);
			aquarium2.Save(file2);
			TestThreeBetas(file2);

			//
			// Test all types
			//
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);
			TestAllTypes(file3);

			aquarium2.Load(file3);
			aquarium2.Save(file3);
			TestAllTypes(file3);
		}

		TEST_METHOD(TestCAquariumClear)
		{
			CAquarium aquarium;
			PopulateAllTypes(&aquarium);

			aquarium.Clear();

			// Angel fish was at 220, 420
			Assert::IsTrue(aquarium.HitTest(220, 420) == nullptr,
				L"Testing for nullptr after Clear function");
			// Beta fish was at 650, 310
			Assert::IsTrue(aquarium.HitTest(650, 310) == nullptr,
				L"Testing for nullptr after Clear function");
			// Carp fish was at 10, 20
			Assert::IsTrue(aquarium.HitTest(10, 20) == nullptr,
				L"Testing for nullptr after Clear function");
			// Molly fish was at 740, 660
			Assert::IsTrue(aquarium.HitTest(740, 660) == nullptr,
				L"Testing for nullptr after Clear function");
			// Skull decor was at 370, 180
			Assert::IsTrue(aquarium.HitTest(370, 180) == nullptr,
				L"Testing for nullptr after Clear function");

		}

		/**
		* Test to ensure an aquarium .aqua file is empty
		*/
		void TestEmpty(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			Assert::IsTrue(regex_search(xml, wregex(L"<\?xml.*\?>")));
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua/>")));

		}

		/**
		*  Populate an aquarium with three Beta fish
		*/
		void PopulateThreeBetas(CAquarium *aquarium)
		{
			srand(RandomSeed);

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(aquarium);
			fish1->SetLocation(100, 200);
			aquarium->Add(fish1);

			shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(aquarium);
			fish2->SetLocation(400, 400);
			aquarium->Add(fish2);

			shared_ptr<CFishBeta> fish3 = make_shared<CFishBeta>(aquarium);
			fish3->SetLocation(600, 100);
			aquarium->Add(fish3);
		}
		/**
		* Test three Beta fish
		*/
		void TestThreeBetas(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure three items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

			// Ensure the speeds are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item.* speedX=\"29\\.706719.*\" speedY=\"36\\.506247.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item.* speedX=\"25\\.042311.*\" speedY=\"64\\.034044.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item.* speedX=\"4\\.740212.*\" speedY=\"15\\.965334.*\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml,
				wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
		}

		/**
		*  Populate an aquarium with all types of fish and decor item
		*/
		void PopulateAllTypes(CAquarium *aquarium)
		{
			srand(RandomSeed);

			shared_ptr<CFishAngelfish> angelfish = make_shared<CFishAngelfish>(aquarium);
			angelfish->SetLocation(220, 420);
			aquarium->Add(angelfish);

			shared_ptr<CFishBeta> betafish = make_shared<CFishBeta>(aquarium);
			betafish->SetLocation(650, 310);
			aquarium->Add(betafish);

			shared_ptr<CFishCarp> carpfish = make_shared<CFishCarp>(aquarium);
			carpfish->SetLocation(10, 20);
			aquarium->Add(carpfish);

			shared_ptr<CFishMolly> mollyfish = make_shared<CFishMolly>(aquarium);
			mollyfish->SetLocation(740, 660);
			aquarium->Add(mollyfish);

			shared_ptr<CDecorSkull> skulldecor = make_shared<CDecorSkull>(aquarium);
			skulldecor->SetLocation(370, 180);
			aquarium->Add(skulldecor);
		}

		/**
		* Test all fish types and decor item
		*/
		void TestAllTypes(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure five items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"220\" y=\"420\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"650\" y=\"310\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"10\" y=\"20\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"740\" y=\"660\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"370\" y=\"180\"")));

			// Ensure the speeds are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item.* speedX=\"30\\.969571.*\" speedY=\"29\\.714362.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item.* speedX=\"25\\.042311.*\" speedY=\"64\\.034044.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item.* speedX=\"5\\.827327.*\" speedY=\"6\\.506867.*\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item.* speedX=\"26\\.917704.*\" speedY=\"43\\.247465.*\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml,
				wregex(L"<aqua><item.* type=\"angelfish\"/><item.* type=\"beta\"/><item.* type=\"carp\"/><item.* type=\"molly\"/><item.* type=\"scull\"/></aqua>")));
		}
	};
}