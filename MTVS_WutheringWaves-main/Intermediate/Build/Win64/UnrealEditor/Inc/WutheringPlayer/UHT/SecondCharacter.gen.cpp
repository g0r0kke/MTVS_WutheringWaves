// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WutheringPlayer/Public/SecondCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSecondCharacter() {}

// Begin Cross Module References
UPackage* Z_Construct_UPackage__Script_WutheringPlayer();
WUTHERINGPLAYER_API UClass* Z_Construct_UClass_APlayer1();
WUTHERINGPLAYER_API UClass* Z_Construct_UClass_ASecondCharacter();
WUTHERINGPLAYER_API UClass* Z_Construct_UClass_ASecondCharacter_NoRegister();
// End Cross Module References

// Begin Class ASecondCharacter
void ASecondCharacter::StaticRegisterNativesASecondCharacter()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASecondCharacter);
UClass* Z_Construct_UClass_ASecondCharacter_NoRegister()
{
	return ASecondCharacter::StaticClass();
}
struct Z_Construct_UClass_ASecondCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "SecondCharacter.h" },
		{ "ModuleRelativePath", "Public/SecondCharacter.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASecondCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ASecondCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayer1,
	(UObject* (*)())Z_Construct_UPackage__Script_WutheringPlayer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASecondCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASecondCharacter_Statics::ClassParams = {
	&ASecondCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASecondCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_ASecondCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASecondCharacter()
{
	if (!Z_Registration_Info_UClass_ASecondCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASecondCharacter.OuterSingleton, Z_Construct_UClass_ASecondCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASecondCharacter.OuterSingleton;
}
template<> WUTHERINGPLAYER_API UClass* StaticClass<ASecondCharacter>()
{
	return ASecondCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASecondCharacter);
ASecondCharacter::~ASecondCharacter() {}
// End Class ASecondCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_SecondCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASecondCharacter, ASecondCharacter::StaticClass, TEXT("ASecondCharacter"), &Z_Registration_Info_UClass_ASecondCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASecondCharacter), 3626005334U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_SecondCharacter_h_1349286409(TEXT("/Script/WutheringPlayer"),
	Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_SecondCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_SecondCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
