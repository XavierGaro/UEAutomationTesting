# Unreal Engine Automation Testing Sandbox

Projecto para Unreal Engine 5 en el que se incluyen los scripts necesarios para demostrar el funcionamiento del sistema  de tests automatizados (Automation Testing) integrado en el motor.

Se incluyen ejemplos de tests que se pasan con éxito y tests que fallan indicando los motivos por los que fallan.

## Uso con Unreal Engine 4
Aunque el proyecto está configurado para Unreal Engine 5 el código es completamente compatible con UE4, aunque en ese caso será necesario activar los plugins de automatización (en UE5 estan activados por defecto)

## Ejecución de los tests
Los tests pueden ejectuarse desde la ventana *Session Frontend* (pestaña *Automation*), desde Rider (pestaña inferior, *Unit Tests*) o desde la línea de comandos. Para UE5:

```
{ruta al editor de ue5}\UnrealEditor.exe" {ruta al proyecto}\TestingSandbox.uproject" -ExecCmds="Automation RunTests TestingSandbox" -Unattended -NullRHI -TestExit="Automation Test Queue Empty" -ReportOutputPath={ruta al proyecto}\Saved\TestReport" -Log -Log=RunTests.log
```
Para UE4 hay que cambiar el nombre del editor:
```
{ruta al editor de ue4}\UE4Editor.exe" {ruta al proyecto}\TestingSandbox.uproject" -ExecCmds="Automation RunTests TestingSandbox" -Unattended -NullRHI -TestExit="Automation Test Queue Empty" -ReportOutputPath={ruta al proyecto}\Saved\TestReport" -Log -Log=RunTests.log
```

Estos parámetros de ejecución lanzaran los tests sin cargar la interficie de Unreal Engine y guardaran el resultado de los tests en la carpeta `{ruta al proyecto}\Saved\TestReport`. Dentro encontraréis dos archivos, un archivo con los resultados en formato JSON y un archivo HTML para visualziarlos (**requiere un servidor web**).
