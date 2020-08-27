<!--
GENERATED FILE - DO NOT EDIT
This file was generated by [MarkdownSnippets](https://github.com/SimonCropp/MarkdownSnippets).
Source File: /docs/mdsource/tray.source.md
To change this file edit the source file and then run MarkdownSnippets.
-->

# DiffEngineTray

DiffEngineTray sits in the Windows tray. For supported snapshot testing libraries, it monitors pending changes in snapshots, and provides a mechanism for accepting those changes. It is intended as a alternative to using the clipboard as an approval mechanism.


## NuGet package

 * https://www.nuget.org/packages/DiffEngineTray


## Running

Install the tool via `dotnet tool` then run `diffenginetray` to start the app.


## UI

<img src="..\src\DiffEngineTray.Tests\MenuBuilderTest.Full.verified.png">


### Moves

"Pending Moves" will accept the changes to file3 and file4.

Clicking "file3" or "file4" will accept the changes to  "file3" or "file4" respectively. Hover over the menu item to see the full path of both files.


### Deletes

A test can produce multiple resulting snapshots. If the accepted versions has a different number of snapshots to the current test run, then some of those snapshots need to be deleted. The delete functionality in the tray tool handles this scenario.

"Pending Deletes" will delete file1 and file2.

Clicking "file1" or "file2" will delete "file1" or "file2" respectively. Hover over the menu item to see the full path.


### Accept all

"Accept all" will accept all pending moves and all pending deletes.


### Clear

Clear will clear all currently tracked items.


## Currently supported in

 * [Verify](https://github.com/VerifyTests/Verify) v6.10 and above