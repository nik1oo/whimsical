main:
	Build.bat Win64 Development -TargetType=Editor -Project="$(shell pwd)./whimsical.uproject"
#	UnrealEditor-Cmd.exe "$(shell pwd)/whimsical.uproject" -run=resavepackages -buildlighting -AllowCommandletRendering -unattended -Map=/Content/Map

pack:
	RunUAT.bat BuildCookRun -project="$(shell pwd)./whimsical.uproject" -platform=Win64 -clientconfig=Shipping -build -cook -pak -stage -archive -archivedirectory="C:/Output"
