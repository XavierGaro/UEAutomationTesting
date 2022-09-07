#include "Misc/AutomationTest.h"

/**
 * Demostración del funcionamiento del sistema de test automatizados de UE4 (Automation Testing), incluyendo tests
 * que se pasan con éxito y tests que fallan y los motivos por los que fallan.
 */


// Clase vacía utilizado para demostrar la diferencia entre objetos y comprobaciones de valores nulos.
class DummyObject
{
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestSuccess, "TestingSandbox.DummyActorTest.AlwaysSuccess",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestSuccess::RunTest(const FString& Parameters)
{
	AddInfo(TEXT("Este test siempre pasa"));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestFail, "TestingSandbox.DummyActorTest.AlwaysFail",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestFail::RunTest(const FString& Parameters)
{
	AddInfo(TEXT("Este test siempre falla "));
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestFailBecasueAddError,
                                 "TestingSandbox.DummyActorTest.AlwaysFailBecauseAddError",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestFailBecasueAddError::RunTest(const FString& Parameters)
{
	AddError(TEXT("Este test siempre falla porque se ha usado AddError()"));
	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestFailBecasueAddErrorIfFalse,
                                 "TestingSandbox.DummyActorTest.SuccessAddErrorIftrue",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestFailBecasueAddErrorIfFalse::RunTest(const FString& Parameters)
{
	bool isConnected = true;
	AddErrorIfFalse(isConnected,
	                TEXT("El mensaje solo se muestra si la expresión es falsa, por lo tanto se pasará el test"),
	                isConnected);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestFailBecasueAddErrorIfTrue,
                                 "TestingSandbox.DummyActorTest.FailAddErrorIfFalse",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestFailBecasueAddErrorIfTrue::RunTest(const FString& Parameters)
{
	bool isConnected = false;
	AddErrorIfFalse(isConnected, TEXT("En este caso la expresión es falsa, por lo tanto el test fallará"), isConnected);
	return true;
}


/**
 * Bateria de pruebas para demostrar el uso de los métodos equivalentes a assert() en otros frameworks.
 *
 * ALERTA! Un test solo debe fallar por una única razón, y cada test solo debe testear un concepto por test.
 * En este caso de manera excepcional se ha creado una batería de pruebas para simplificar la demostración de su
 * funcionamiento.
 *
 * Si se modifica el ejemplo para hacer que alguno de los ejemplos falle se mostrará el mensaje que acompaña
 * a la comparación que ha fallado.
 */
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestBatch, "TestingSandbox.DummyActorTest.Batch",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestBatch::RunTest(const FString& Parameters)
{
	int a = 42;
	int b = 42;
	TestEqual(TEXT("Comprobamos que a y b són iguales"), a, b);

	FString text1 = "foobar";
	FString text2 = "foobar";
	TestEqual(TEXT("Comprobamos que los textos són iguales"), text1, text2);
	TestNotSame("Comprobamos que los textos no són la misma cadena de texto", text1, text2);

	FString text3 = "FooBar";
	TestEqualInsensitive(TEXT("Comprobamos que los textos són iguales (ignora majúsculas)"), *text1, *text3);

	bool isConnected = false;
	TestFalse("Comprobamos que el valor es falso", isConnected);
	TestTrue("Comprobamos que el valor es verdadero", !isConnected);

	UObject* player = nullptr;
	TestNull("Comprobamos que el jugador es null", player);

	DummyObject* object1 = new DummyObject();
	TestNotNull("Comprobamos que el objeto no es null", object1);

	DummyObject* object2 = new DummyObject();
	TestNotEqual("Comprobamos que el objeto1 no es el objeto2", object1, object2);
	TestNotSame("Comprobamos que el objeto1 no es el objeto2 (posición de memória)", object1, object2);

	DummyObject* objectB = object1;
	TestNotSame("Comprobamos que el objeto1 no es el objetoB (posición de memória)", object1, objectB);
	TestEqual("Comprobamos que el objeto1 es el objetoB", object1, objectB);

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestExpectedError, "TestingSandbox.DummyActorTest.ExpectedErrorContains",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestExpectedError::RunTest(const FString& Parameters)
{
	AddExpectedError(TEXT("La casilla de destino no es válida"), EAutomationExpectedErrorFlags::MatchType::Contains, 0);
	UE_LOG(LogTemp, Error,
	       TEXT(
		       "Como se ha definido el flag MatchType:Contains solo hace falta que el mensaje de error se encuentre contenido en esta frase: La casilla de destino no es válida sin importar lo que haya delante o detrás"
	       ));

	AddWarning(TEXT("Este test va a pasar, porque se intercepta el error"));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestExpectedErrorExactFail,
                                 "TestingSandbox.DummyActorTest.ExpectedErrorExactFail",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestExpectedErrorExactFail::RunTest(const FString& Parameters)
{
	AddExpectedError(TEXT("La casilla de destino no es válida"), EAutomationExpectedErrorFlags::MatchType::Exact, 0);
	UE_LOG(LogTemp, Error,
	       TEXT(
		       "En este caso se ha definido el flag MatchType:Exact por lo tanto no coincidirá con lo esperado: La casilla de destino no es válida, ahora sí importa lo que haya delante o detrás"
	       ));
	AddWarning(TEXT("Este test va a fallar porque se espera encontrar la cadena exacta"));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestExpectedErrorExactSuccess,
                                 "TestingSandbox.DummyActorTest.ExpectedErrorExactSuccess",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDummyActorTestExpectedErrorExactSuccess::RunTest(const FString& Parameters)
{
	AddExpectedError(TEXT("casilla de destino no es válida"), EAutomationExpectedErrorFlags::MatchType::Exact, 0);
	UE_LOG(LogTemp, Error, TEXT("casilla de destino no es válida"));


	// Esto no aparece
	AddWarning(TEXT("Este test va a pasar porque la cadena es la esperada"));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestExpectedErrorRegex,
								 "TestingSandbox.DummyActorTest.ExpectedErrorRegexSuccess",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDummyActorTestExpectedErrorRegex::RunTest(const FString& Parameters)
{
	AddExpectedError(TEXT("\\d{4}"), EAutomationExpectedErrorFlags::MatchType::Contains, 0);
	UE_LOG(LogTemp, Error, TEXT("Código secreto 1234"));

	AddWarning(TEXT("Este test pasa porque la expresión regular indica que se buscan 4 dígitos consecutivos"));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDummyActorTestExpectedErrorRegexFail,
								 "TestingSandbox.DummyActorTest.ExpectedErrorRegexFail",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FDummyActorTestExpectedErrorRegexFail::RunTest(const FString& Parameters)
{
	AddExpectedError(TEXT("\\d{4}"), EAutomationExpectedErrorFlags::MatchType::Contains, 0);
	UE_LOG(LogTemp, Error, TEXT("Código secreto ABCDE"));
	
	AddWarning(TEXT("Este test falla porque la expresión regular indica que se buscan 4 dígitos consecutivos y el mensaje de error solo cotiene letras"));
	return true;
}


// TODO: COMPLEX

// TODO: LATENT