// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Player1, Log, All);

# define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

# define PRINT_CALLINFO() UE_LOG(LogTemp, Warning, TEXT(%s), *CALLINFO)

# define PRINT_LOG(Format, ...) UE_LOG(LogTemp, Warning, TEXT("%s " Format), *CALLINFO, ##__VA_ARGS__)