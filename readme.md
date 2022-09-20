# Unreal Engine Automation Testing Sandbox

Unreal engine 4 project that includes the necessary code to show how the UE Automation Test system works (Automation Testing) in unison with the engine. It includes a set of Functional tests that show how to include tests using Blueprints.

This sample project includes some failing tests to show how and why those tests fail. In every case a warning or error message explains why it failed.


To run the tests in the editor the following plugins must be enabled:
  * Runtime Tests
  * Functional Testing Editor


Though this project has been created for UE4.27, all the tests are compatible with UE5.
  * Functional tests in 5.03 take a lot of time to prepare, so they will fail before being run (from <1s in UE4.27 to >100s in UE5.03).


## Running Tests
Those tests can be run from the Session Front-end Window (*Automation* tab), selecting *TestingSanbox* rows for the unit tests, and *Project. Functional Tests* for the Functional Tests (Blueprint tests).

Also, Automated Tests (not functional) can be run in Rider IDE (bottom tab, *Unit Tests*), but complex tests will show an error and won't run.


To run the *Automation Tests* from the command line:
```
{ue4 editor path}\UE4Editor.exe" {project path}\TestingSandbox.uproject" -ExecCmds="Automation RunTests TestingSandbox" -Unattended -NullRHI -TestExit="Automation Test Queue Empty" -ReportOutputPath={ruta al proyecto}\Saved\TestReport\Automation" -Log -Log=RunTests.log
```

To run the *Functional Tests* from the command line:
```
{ue4 editor path}\UE4Editor.exe" {project path}\TestingSandbox.uproject" -ExecCmds="Automation RunTests Functional Tests" -Unattended -NullRHI -TestExit="Automation Test Queue Empty" -ReportOutputPath={ruta al proyecto}\Saved\TestReport\Functional" -Log -Log=RunTests.log
```


On UE5 the editor executable filename have changed:
```
{ue5 editor path}\UnrealEditor.exe" {project path}\TestingSandbox.uproject" -ExecCmds="Automation RunTests TestingSandbox" -Unattended -NullRHI -TestExit="Automation Test Queue Empty" -ReportOutputPath={project path}\Saved\TestReport\Automation" -Log -Log=RunTests.log
```

```
{ue5 editor path}\UnrealEditor.exe" {project path}\TestingSandbox.uproject" -ExecCmds="Automation RunTests Functional Tests" -Unattended -NullRHI -TestExit="Automation Test Queue Empty" -ReportOutputPath={project path}\Saved\TestReport\Automation" -Log -Log=RunTests.log
```


### Command line parameters ### 
Those execution parameters will run the tests without loading the Unreal Engine Editor, and will save the test results inside `{project path}\Saved\TestReport\Automation}` and `{project path}\Saved\TestReport\Functional}` respectively.

Inside this directory will be 2 files: a json file with the text and an HTML file what will load it (a web server is required to serve those files because you can open a json file locally from a browser, but for CI servers you only need to parse the JSON file).