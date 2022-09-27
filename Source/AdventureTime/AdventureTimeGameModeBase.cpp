// Copyright Epic Games, Inc. All Rights Reserved.


#include "AdventureTimeGameModeBase.h"

FQuest AAdventureTimeGameModeBase::FindQuest_Implementation(FName QuestID, bool& Success)
{
	Success = false;

	FQuest Quest;
	if (QuestDatabase == nullptr) { return Quest; }

	for (int i = 0; i < QuestDatabase->QuestData.Num(); i++)
	{
		if (QuestDatabase->QuestData[i].QuestID == QuestID)
		{
			Success = true;
			return QuestDatabase->QuestData[i];

		}
	}

	return Quest;
}

