#include "commands.h"
#include "dependencies/FloppyLib/include/FloppyLib.h"
#include <iostream>

using namespace std;

void dir(string path)
{
	Disk disk = Disk();
	int loadResult = disk.LoadFromImd(path);
	if (loadResult == 0)
	{
		disk.Identify();
		switch (disk.GetType())
		{
		case 0: printf("Error: Unknown disk type\n"); break;
		case 1:
		case 58:
		{
			InterchangeDisk interchange = InterchangeDisk(disk);
			vector<InterchangeFile> files = interchange.GetFiles();
			if (files.size() == 0)
			{
				printf("Disk is empty\n");
			}
			else
			{
				for (int file = 0; file < files.size(); file++)
				{
					cout << files[file].GetFileIdentifier() << endl;
				}
			}
		}; break;
		default: printf("Error: Wrong disk type\n");
		}
	}
}

void statistics(string path)
{
	Disk disk = Disk();
	int loadResult = disk.LoadFromImd(path);
	if (loadResult == 0)
	{
		DiskStatistics stats = disk.GetStatistics();
		printf("Tracks: %d\n", stats.GetTracks());
		printf("Heads: %d\n", stats.GetHeads());
		printf("Sectors: %d\n", stats.GetSectors());
		printf("Errors: %d\n", stats.GetErrors());
	}
}

void volume(string path)
{
	Disk disk = Disk();
	int loadResult = disk.LoadFromImd(path);
	if (loadResult == 0)
	{
		disk.Identify();
		if (disk.GetType() == 1 || disk.GetType() == 58)
		{
			InterchangeDisk interchange = InterchangeDisk(disk);
			InterchangeVolume volume = interchange.GetVolume();
			cout << "Volume Identifier: " + volume.GetIdentifier() << endl;
			printf("Accessibility: %c\n", volume.GetAccessibility());
			cout << "Machine: " + volume.GetMachine() << endl;
			cout << "Owner: " + volume.GetOwner() << endl;
			printf("Surface Indicator: %c\n", volume.GetSurfaceIndicator());
			printf("Extent Arrangement Constraint: %s\n", volume.HasExtentArrangementConstraint() ? "true" : "false");
			printf("Non-Sequential Recording: %s\n", volume.HasNonSequentialRecording() ? "true" : "false");
			printf("Sector Size: %d\n", volume.GetSectorSize());
			cout << "Sector Sequence Code: " + volume.GetSectorSequenceCode() << endl;
			printf("Label Standard: %c\n", volume.GetLabelStandard());
		}	
	}
}

void extractAll(string path, string savePath)
{
	Disk disk = Disk();
	int loadResult = disk.LoadFromImd(path);
	if (loadResult == 0)
	{
		disk.Identify();
		InterchangeDisk interchange = InterchangeDisk(disk);
		vector<InterchangeFile> files = interchange.GetFiles();
		for (int file = 0; file < files.size(); file++)
		{
			files[file].SaveToFile(savePath);
		}
		printf("%d files extracted", files.size());
	}
}

void help()
{
	printf("======== Arion ========\n");
	printf("\n");
	printf("Syntax:\tarion command path1 path2\n");
	printf("\n");
	printf("Commands:\n");
	printf("dir / ls -> List files in floppy image\n");
	printf("statistics / stats -> Display disk statistics\n");
	printf("volume / vol -> Display volume metadata\n");
	printf("extract-all / all -> extract all files in floppy\n");
	printf("help -> Displays help for this application\n");
	printf("\n");
	printf("Paths:\n");
	printf("path1: must be the path to the image FILE\n");
	printf("path2: must be the path to the DIRECTORY where the files are to be extracted\n");
	printf("\n");
}