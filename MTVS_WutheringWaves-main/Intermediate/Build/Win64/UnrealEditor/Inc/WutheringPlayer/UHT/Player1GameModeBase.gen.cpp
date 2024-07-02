// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WutheringPlayer/Public/Player1GameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePlayer1GameModeBase() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_WutheringPlayer();
WUTHERINGPLAYER_API UClass* Z_Construct_UClass_APlayer1GameModeBase();
WUTHERINGPLAYER_API UClass* Z_Construct_UClass_APlayer1GameModeBase_NoRegister();
// End Cross Module References

// Begin Class APlayer1GameModeBase
void APlayer1GameModeBase::StaticRegisterNativesAPlayer1GameModeBase()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APlayer1GameModeBase);
UClass* Z_Construct_UClass_APlayer1GameModeBase_NoRegister()
{
	return APlayer1GameModeBase::StaticClass();
}
struct Z_Construct_UClass_APlayer1GameModeBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Player1GameModeBase.h" },
		{ "ModuleRelativePath", "Public/Player1GameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APlayer1GameModeBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_APlayer1GameModeBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_WutheringPlayer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlayer1GameModeBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APlayer1GameModeBase_Statics::ClassParams = {
	&APlayer1GameModeBase::StaticClass,
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
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APlayer1GameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_APlayer1GameModeBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APlayer1GameModeBase()
{
	if (!Z_Registration_Info_UClass_APlayer1GameModeBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APlayer1GameModeBase.OuterSingleton, Z_Construct_UClass_APlayer1GameModeBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APlayer1GameModeBase.OuterSingleton;
}
template<> WUTHERINGPLAYER_API UClass* StaticClass<APlayer1GameModeBase>()
{
	return APlayer1GameModeBase::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APlayer1GameModeBase);
APlayer1GameModeBase::~APlayer1GameModeBase() {}
// End Class APlayer1GameModeBase

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_Player1GameModeBase_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APlayer1GameModeBase, APlayer1GameModeBase::StaticClass, TEXT("APlayer1GameModeBase"), &Z_Registration_Info_UClass_APlayer1GameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APlayer1GameModeBase), 4241849239U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_Player1GameModeBase_h_3310591098(TEXT("/Script/WutheringPlayer"),
	Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_Player1GameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_Player1GameModeBase_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
