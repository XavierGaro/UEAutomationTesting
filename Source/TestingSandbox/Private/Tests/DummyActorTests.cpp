#include "Misc/AutomationTest.h"

/**
 * This is a demostration for Unreal Engine 5 Atutomation Testing. It includes fail and pass tests to show
 * how it works in different cases.
 */


/*
 * Dummy classe used to show object comparison and null values
 */
class DummyObject
{
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestSuccess, "TestingSandbox.DummyActorTest.AlwaysSuccess",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestSuccess::RunTest(const FString& Parameters)
{
	AddInfo(TEXT("This test will always succeed, because it returns true"));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestFail, "TestingSandbox.DummyActorTest.AlwaysFail",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestFail::RunTest(const FString& Parameters)
{
	AddInfo(TEXT("This test will always fail, because it returns false "));
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestFailBecasueAddError,
                                 "TestingSandbox.DummyActorTest.AlwaysFailBecauseAddError",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestFailBecasueAddError::RunTest(const FString& Parameters)
{
	AddError(TEXT("This test will always fail becasue we have used AddError()"));
	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestFailBecasueAddErrorIfFalse,
                                 "TestingSandbox.DummyActorTest.SuccessAddErrorIftrue",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestFailBecasueAddErrorIfFalse::RunTest(const FString& Parameters)
{
	bool isConnected = true;
	AddErrorIfFalse(isConnected,
	                TEXT(
		                "This message only is shown if the expression is false, so it won't be shown and the test will pass"),
	                isConnected);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestFailBecasueAddErrorIfTrue,
                                 "TestingSandbox.DummyActorTest.FailAddErrorIfFalse",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestFailBecasueAddErrorIfTrue::RunTest(const FString& Parameters)
{
	bool isConnected = false;
	AddErrorIfFalse(isConnected, TEXT("In theis case the expression is false, so the test will fail"), isConnected);
	return true;
}


/**
 * Test battery to show how work some of the assert() variants.
 *
 * WARNING! A test must only fail because a reason, and each test only must test a single concept.
 *
 * This tests exists only as a demonstration to show how asserts work for Automation Tests.
 *
 */
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestBatch, "TestingSandbox.DummyActorTest.Batch",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestBatch::RunTest(const FString& Parameters)
{
	int a = 42;
	int b = 42;
	TestEqual(TEXT("a & b must be equal"), a, b);

	FString text1 = "foobar";
	FString text2 = "foobar";
	TestEqual(TEXT("text1 & text2 must be equal"), text1, text2);
	TestNotSame("text1 and tex2 are equal, but they arent the same string", text1, text2);

	FString text3 = "FooBar";
	TestEqualInsensitive(TEXT("text1 and text3 must be equal when ignorin casing"), *text1, *text3);

	bool isConnected = false;
	TestFalse("isConnected must be false", isConnected);
	TestTrue("!isConnected must be true", !isConnected);

	UObject* player = nullptr;
	TestNull("The player must be null", player);

	DummyObject* object1 = new DummyObject();
	TestNotNull("object1 can't be null", object1);

	DummyObject* object2 = new DummyObject();
	TestNotEqual("object1 isn't object2", object1, object2);

	DummyObject* objectB = object1;
	TestNotSame("object1 and objectB can't be the same (memory position)", object1, objectB);
	TestEqual("object1 and objectB must be equal", object1, objectB);

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestExpectedError, "TestingSandbox.DummyActorTest.ExpectedErrorContains",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestExpectedError::RunTest(const FString& Parameters)
{
	AddExpectedError(TEXT("Destination square is not valid"), EAutomationExpectedErrorFlags::MatchType::Contains, 0);
	UE_LOG(LogTemp, Error,
	       TEXT(
		       "As we hace defined the flat MathcType:Contains, this test will pass thoug it includes the estring 'Destination square is not valid'"
	       ));

	AddInfo(TEXT("This test will pass becasue the error is intercepted"));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestExpectedErrorExactFail,
                                 "TestingSandbox.DummyActorTest.ExpectedErrorExactFail",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestExpectedErrorExactFail::RunTest(const FString& Parameters)
{
	AddExpectedError(TEXT("Destination square is not valid"), EAutomationExpectedErrorFlags::MatchType::Exact, 0);
	UE_LOG(LogTemp, Error,
	       TEXT(
		       "As we hace defined the flat MathcType:Exact, this test will fail thoug it includes the estring 'Destination square is not valid'"
	       ));
	AddWarning(TEXT("This test will fail because it expected to match the exact string"));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestExpectedErrorExactSuccess,
                                 "TestingSandbox.DummyActorTest.ExpectedErrorExactSuccess",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestExpectedErrorExactSuccess::RunTest(const FString& Parameters)
{
	AddExpectedError(TEXT("Destination square is not valid"), EAutomationExpectedErrorFlags::MatchType::Exact, 0);
	UE_LOG(LogTemp, Error, TEXT("Destination square is not valid"));


	// Esto no aparece
	AddInfo(TEXT("This test passes becasue the expected string is exactly matched by the error message"));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestExpectedErrorRegex,
                                 "TestingSandbox.DummyActorTest.ExpectedErrorRegexSuccess",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestExpectedErrorRegex::RunTest(const FString& Parameters)
{
	AddExpectedError(TEXT("\\d{4}"), EAutomationExpectedErrorFlags::MatchType::Contains, 0);
	UE_LOG(LogTemp, Error, TEXT("SecretCode 1234"));

	AddInfo(
		TEXT("This test passes becasue the regular expression looks for an error message with 4 consecutive digits"));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestExpectedErrorRegexFail,
                                 "TestingSandbox.DummyActorTest.ExpectedErrorRegexFail",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestExpectedErrorRegexFail::RunTest(const FString& Parameters)
{
	AddExpectedError(TEXT("\\d{4}"), EAutomationExpectedErrorFlags::MatchType::Contains, 0);
	UE_LOG(LogTemp, Error, TEXT("Secret Code ABCDE"));

	AddWarning(TEXT("This tests fails because the regex match 4 numbers and the error message don't have them"));
	return true;
}

/*
 * All complex tests must implement those two functions: GetTestst and RunTests. On GetTests the testes are
 * prepared with a different command (paràmeter) and optionally a pretty name.
 * 
 * WARNING! Those tests don't run on Rider!
 */
IMPLEMENT_COMPLEX_AUTOMATION_TEST(FComplexTest, "TestingSandbox.DummyActorTest.Complex",
                                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

void FComplexTest::GetTests(TArray<FString>& OutBeautifiedNames, TArray<FString>& OutTestCommands) const
{
	for (int i = 0; i < 10; i++)
	{
		FString num = FString::FromInt(i);
		OutBeautifiedNames.Add("Test " + num);
		OutTestCommands.Add(num);
	}
}

/*
 * All the paràmeters must be included as a single string, and processed as needed
 */
bool FComplexTest::RunTest(const FString& Parameters)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *Parameters);
	int32 i = FCString::Atoi(*Parameters);

	// Only even numbers will pass the test
	// Solo pararan los números pares
	TestEqual("It's odd", i % 2, 0);


	//ADD_LATENT_AUTOMATION_COMMAND(FEnqueuePerformanceCaptureCommands());

	return true;
}
