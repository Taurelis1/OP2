[Setup]
AppName=Tauras-Petrauskas
AppVersion=1.0
DefaultDirName={pf}\VU\Tauras-Petrauskas
DefaultGroupName=VU\Tauras-Petrauskas
OutputDir=.
OutputBaseFilename=Setup
PrivilegesRequired=admin
DisableProgramGroupPage=yes

[Files]
Source: "main.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "Studentas.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "Studentas.h"; DestDir: "{app}"; Flags: ignoreversion
Source: "Mylib.h"; DestDir: "{app}"; Flags: ignoreversion
Source: "Vector.h"; DestDir: "{app}"; Flags: ignoreversion
Source: "Zmogus.h"; DestDir: "{app}"; Flags: ignoreversion
Source: "studentai10000.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "studentai100000.txt"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Tauras-Petrauskas"; Filename: "{app}\main.exe"
Name: "{commondesktop}\Tauras-Petrauskas"; Filename: "{app}\main.exe"

[Run]
Filename: "{app}\main.exe"; Description: "Paleisti programą"; Flags: nowait postinstall runascurrentuser